#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/if_ether.h>
#include <arpa/inet.h>

#define BUFFER_LEN	65536

int main() {

	/* receive buffer */
	unsigned char *buffer = (unsigned char *) malloc(BUFFER_LEN);
	memset(buffer, 0, BUFFER_LEN);
	struct sockaddr saddr;
	int saddr_len = sizeof(saddr);

	/* capture all packets through raw socket */
	int sd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (sd < 0) {
		fprintf(stderr, "Error openning raw socket! Make sure this is launched with root priviliges\n");
		return -1;
	}

	/* receive network packet into buffer (will block until a packet is received) */
	int rcv_len = recvfrom(sd, buffer, BUFFER_LEN, 0, &saddr, (socklen_t *)&saddr_len);
	if (rcv_len < 0) {
		fprintf(stderr, "Error receiving packet!\n");
		return -1;
	}

	/* parse Ethernet header */
	struct ethhdr *eth = (struct ethhdr *)(buffer);
	printf("\nEthernet Header\n");
	printf("\t|-Source Address : %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\n", eth->h_source[0], eth->h_source[1], eth->h_source[2], eth->h_source[3], eth->h_source[4], eth->h_source[5]);
	printf("\t|-Destination Address : %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\n", eth->h_dest[0], eth->h_dest[1], eth->h_dest[2], eth->h_dest[3], eth->h_dest[4], eth->h_dest[5]);
	printf("\t|-Protocol : %d\n", eth->h_proto);

	for (int i=0; i < rcv_len; i++) {
		if(i!=0 && i%16==0)
			printf("\n");
		printf("%.2X ", buffer[i]);
	}
	printf("\n");

	close(sd);

	free(buffer);

	return 0;
}
