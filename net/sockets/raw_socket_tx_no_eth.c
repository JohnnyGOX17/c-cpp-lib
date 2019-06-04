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
				"\t$ raw_socket_tx_no_eth eth0\n");
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

	printf("Netdev index for %s: %d\n", argv[1], ifreq_i.ifr_ifindex);

	/* TX buffer */
	unsigned char *buffer = (unsigned char *) malloc(BUFFER_LEN);
	memset(buffer, 0, BUFFER_LEN);
	size_t pkt_len = 0;

	/* Dest MAC */
	buffer[pkt_len++] = 0xFF;
	buffer[pkt_len++] = 0xFF;
	buffer[pkt_len++] = 0xFF;
	buffer[pkt_len++] = 0xFF;
	buffer[pkt_len++] = 0xFF;
	buffer[pkt_len++] = 0xFF;

	/* Src MAC */
	buffer[pkt_len++] = 0x01;
	buffer[pkt_len++] = 0x02;
	buffer[pkt_len++] = 0x03;
	buffer[pkt_len++] = 0x04;
	buffer[pkt_len++] = 0x05;
	buffer[pkt_len++] = 0x06;

	/* IPv4 EtherType */
	buffer[pkt_len++] = 0x08;
	buffer[pkt_len++] = 0x00;

	/* Completely arbitrary pkt data */
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
