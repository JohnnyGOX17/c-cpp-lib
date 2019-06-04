#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/if_ether.h>
#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>

#define BUFFER_LEN	64

int main(int argc, char *argv[]){

	if (argc != 2) {
		printf("Error: Must pass one net interface name. Example:\n"
				"\t$ raw_socket_tx eth0\n");
		return -1;
	}

	/* send a packet through raw socket */
	int sd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (sd < 0) {
		fprintf(stderr, "Error openning raw socket! Make sure this is launched with root priviliges\n");
		return -1;
	}

	/* Get index of interface to send packet over */
	struct ifreq ifreq_i;
	memset(&ifreq_i, 0, sizeof(ifreq_i));
	strncpy(ifreq_i.ifr_name, argv[1], IFNAMSIZ-1);

	if (ioctl(sd, SIOCGIFINDEX, &ifreq_i) < 0) {
		fprintf(stderr, "Error trying to find net device index\n");
		return -1;
	}

	struct ifreq ifreq_c;
	memset(&ifreq_c, 0, sizeof(ifreq_c));
	strncpy(ifreq_c.ifr_name, argv[1], IFNAMSIZ-1);
	if (ioctl(sd, SIOCGIFHWADDR, &ifreq_c) < 0) {
		fprintf(stderr, "Error trying to find net device MAC Address\n");
		return -1;
	}

	/* TX buffer */
	unsigned char *buffer = (unsigned char *) malloc(BUFFER_LEN);
	memset(buffer, 0, BUFFER_LEN);

	struct ethhdr *eth = (struct ethhdr *)(buffer);

	printf("Netdev index for %s: %d\n\tMAC Addr: ", argv[1], ifreq_i.ifr_ifindex);
	for(int i=0; i<6; i++) {
		printf("%.2X:", (unsigned char)ifreq_c.ifr_hwaddr.sa_data[i]);
		eth->h_source[i] = (unsigned char)(ifreq_c.ifr_hwaddr.sa_data[i]);
		eth->h_dest[i] = 0xFF;
	}
	printf("\n");

	eth->h_proto = htons(ETH_P_IP);
	size_t pkt_len = sizeof(struct ethhdr);

	buffer[pkt_len++] = 0xAA;
	buffer[pkt_len++] = 0xBB;
	buffer[pkt_len++] = 0xCC;
	buffer[pkt_len++] = 0xDD;

	struct sockaddr_ll saddr_ll;
	saddr_ll.sll_ifindex = ifreq_i.ifr_ifindex;
	saddr_ll.sll_halen = ETH_ALEN;
	/* man pages says we _should_ specify destination MAC address member
	 * .sll_addr[0-5] but so far it hasn't negatively affected sending
	 * any data */

	/* send network packet */
	int send_len = sendto(sd, buffer, pkt_len, 0, (const struct sockaddr*)&saddr_ll, sizeof(struct sockaddr_ll));
	if (send_len < 0) {
		fprintf(stderr, "Error sending packet!\n");
		return -1;
	}

	close(sd);
	free(buffer);

	return 0;
}
