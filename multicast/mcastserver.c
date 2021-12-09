/* Send Multicast Datagram code example. */
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct in_addr localInterface;
struct sockaddr_in groupSock;
int sd;
char databuf[1024] = "Multicast test message lol!";
int datalen = sizeof(databuf);

int main (int argc, char *argv[ ])
{
    if (argc < 4) {
        printf("Usage: %s groupAddr port localIfAddr\n", argv[0]);
        return 0;
    }
    char *grpAddr = argv[1];
    int  port = atoi(argv[2]);
    char *localIfAddr = argv[3]; 

    /* Create a datagram socket on which to send. */
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sd < 0)
    {
        perror("Opening datagram socket error");
        exit(1);
    }
    else
        printf("Opening the datagram socket...OK.\n");

    /* Initialize the group sockaddr structure with a */
    /* group address of 225.1.1.1 and port 5555. */
    memset((char *) &groupSock, 0, sizeof(groupSock));
    groupSock.sin_family = AF_INET;
    /*groupSock.sin_addr.s_addr = inet_addr("226.1.1.1");*/
    /*groupSock.sin_port = htons(4321);*/
    groupSock.sin_addr.s_addr = inet_addr(grpAddr);
    groupSock.sin_port = htons(port);

    /* Set local interface for outbound multicast datagrams. */
    /* The IP address specified must be associated with a local, */
    /* multicast capable interface. */
    localInterface.s_addr = inet_addr(localIfAddr);
    if(setsockopt(sd, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface, sizeof(localInterface)) < 0)
    {
        perror("Setting local interface error");
        exit(1);
    }
    else
        printf("Setting the local interface...OK\n");

    /* 测试是否可以调用connect函数连接组播地址 */
    connect(sd, (const struct sockaddr *)&groupSock, sizeof(groupSock));

    /* Send a message to the multicast group specified by the*/
    /* groupSock sockaddr structure. */
    /*int datalen = 1024;*/
    if(write(sd, databuf, datalen) < 0)
    {
        perror("Sending datagram message error");
    }
    /*
    if(sendto(sd, databuf, datalen, 0, (struct sockaddr*)&groupSock, sizeof(groupSock)) < 0)
    {
        perror("Sending datagram message error");
    }
    */
    else
        printf("Sending datagram message...OK\n");

    /* Try the re-read from the socket if the loopback is not disable
       if(read(sd, databuf, datalen) < 0)
       {
       perror("Reading datagram message error\n");
       close(sd);
       exit(1);
       }
       else
       {
       printf("Reading datagram message from client...OK\n");
       printf("The message is: %s\n", databuf);
       }
       */
    return 0;
}
