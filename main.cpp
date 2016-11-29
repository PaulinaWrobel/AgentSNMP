#include <stdio.h>
#include <unistd.h>
#include <cstring>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "SNMPServer.h"
#include "SNMPDeserializer.h"
#include "MIBParser.h"
#include "defines.h"

int main(int argc, char **argv) {
    DEBUG("Agent SNMP\n");
    MIBParser parser1;
    std::string fn = "mibs/RFC1213-MIB.txt";
    parser1.parseFile(fn);

    for (int i=0; i<argc; ++i) {
        printf("%d: %s, ",i,argv[i]);
    }
    printf("\n");

    if (argc == 2) {
        if ((!strcmp(argv[1], "--print_tree")) || (!strcmp(argv[1], "-t"))) {
            parser1.tree.print_tree();
        }
    } else if (argc == 3) {
        if ((!strcmp(argv[1], "--print_node")) || (!strcmp(argv[1], "-n"))) {
            std::string name(argv[2]);
            parser1.tree.print_node(name);
        }
    }
    // SNMPServer serv1;
    // serv1.initConnection();
    // serv1.receiveMessage();




    // int sockfd, newsockfd, portno, clilen;
    // struct sockaddr_in serv_addr, cli_addr;
    // char buf_read[1024];

    // sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    // if (sockfd < 0){
    //     perror("ERROR opening socket\n");
    //     return 1;
    // }
    // printf("Socket opened\n");
    // memset(&serv_addr, 0, sizeof serv_addr);
    // portno = 161;
    // serv_addr.sin_family = AF_INET;
    // serv_addr.sin_addr.s_addr = INADDR_ANY;
    // serv_addr.sin_port = htons(portno);

    // if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
    //     perror("ERROR on binding\n");
    //     return 1;
    // }
    // printf("Bind ok\n");
    // listen(sockfd,5);
    // printf("Listening\n");
    // clilen = sizeof(cli_addr);

    // while(1){
    //     printf("\nWaiting\n");
    //     int buf_l;
    //     buf_l = recvfrom(sockfd,buf_read,1024,0,(struct sockaddr *)&cli_addr, (socklen_t*)&clilen);
    //     printf("%d", buf_l);
    //     for (int i = 0; i < buf_l; ++i)
    //     {
    //         printf("%d ", buf_read[i]);
    //     }
    //     printf("\n");
    //     char send_data[] = "Response";
    //     sendto(sockfd,send_data,strlen(send_data),0,(struct sockaddr *)&cli_addr,sizeof(struct sockaddr));
    //     fflush(stdout);


    // }

    return 0;
}
