#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcap.h>

int main(int argc, char* argv[])
{
	char *dev = NULL;
	char errbuf[PCAP_ERRBUF_SIZE];
	memset(errbuf, 0, sizeof(errbuf));

	dev = pcap_lookupdev(errbuf);
	printf("capture dev:%s\r\n", dev);
	return 0;
}
