#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
 
int getservice( unsigned int portnr )
{
  
        struct servent *service;
    service = getservbyport(htons(portnr),NULL );
            
 
    if (!(service == NULL))
        {
        printf("\t (%s | %s)\n", service->s_name, service->s_proto);
    }
    else
    {
        printf("\n");
    }
    return 0;
}
 
int main(int argc, char *argv[])
{
 
        int sockfd;
    unsigned int port;
        struct hostent *he;
 
 
        if (argc != 2)
        {
            fprintf(stderr,"usage: client hostname\n");
            exit(1);
        }
 
        if ((he=gethostbyname(argv[1])) == NULL)    // get the host info
        {
            perror("gethostbyname");
            exit(1);
        }
        for(port=0; port<=65000; port++)
        {
            struct sockaddr_in their_addr; // connector's address information
            if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
            {
                    perror("socket");
                    exit(1);
            }
 
            their_addr.sin_family = AF_INET;    // host byte order
            their_addr.sin_port = htons(port);  // short, network byte order
            their_addr.sin_addr = *((struct in_addr *)he->h_addr);
            memset(&(their_addr.sin_zero), '\0', 8);  // zero the rest of the struct
 
            if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1)
            {
                    close(sockfd);
            }
            else
            {
            printf("%d",port);
            getservice( port );  
            close(sockfd);
            }
        }
}
