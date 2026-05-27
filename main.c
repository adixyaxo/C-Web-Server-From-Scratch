// we will be making a web server from scratch in this
#include <fcntl.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/sendfile.h>
#include <unistd.h>
#include <stdlib.h>



int main() {

    // A server describes a role, purpose or behaviour || CENTER OF INFORMATION
    // A server is nothing but a programme running on remote which supplies information on demand to the client
    // A client is a programme which asks for the information from the server using networking protocols
    // Even when runnning of the same machines the server and the client would communicate using the networking protocols only

    int socketSD;
    // AF_INET is used for IPv4 Internet protocols
    // this function will return a file descriptor of a socket

    if ((socketSD = socket(AF_INET,SOCK_STREAM,0))<0)
    {
        printf("There is problem in setting the Socket DF");
        exit(EXIT_FAILURE);
    }


    // We will create a socket address
    // in port we need to pass in the hex function for the port number using python to find out to the hex of the port
    // hex(8080) = 0x1f90

       struct sockaddr_in socketADDR;
       socketADDR.sin_family = AF_INET6;
       socketADDR.sin_addr.s_addr = 0;
       socketADDR.sin_port = 0x1f90;

    // now we are going to bind the socket
    int b = bind(socketSD,(struct sockaddr*)&socketADDR,sizeof(socketADDR));
    if (b<0)
    {
        printf("Bind failed");
        exit(EXIT_FAILURE);
    }

    int l = listen(socketSD,10);
    if (b<0)
    {
        printf("Listen failed");
        exit(EXIT_FAILURE);
    }



    int clientFD = accept(socketSD,0,0);// this is going to return the client fd
    char buffer[256] = {0};


    recv(clientFD,buffer,256,0);

    //GET /file.html ..............

    char* file = buffer+5;
    *strchr(file,' ') = 0;
    int openedFD = open(file,O_RDONLY);

    sendfile(clientFD,openedFD,0,256);


    close(clientFD);
    close(socketSD);
    close(openedFD);



    return 0;
}
