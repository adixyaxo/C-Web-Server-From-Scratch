#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main() {

    char* ip = "142.250.72.14"; // the ip address 
    char* googleip = "142.250.72.14"; // ip add of google and port is 443 

    int socketFD = socket(AF_INET,SOCK_STREAM,0); // socket file descriptor 
    
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address)); 
    address.sin_port = htons(80); // to convert port from int to unsigned short integer 


    /*In Named Data Networking (NDN), the standard representation for multi-byte integers (such as Type and Length fields in TLV packets) uses network byte order, which is big-endian.  This means the most significant byte is stored at the lowest memory address, ensuring consistency across different hardware architectures. 

    For variable-length integers in NDN TLV encoding:

    If the value is $\le 252$ ($0xFC$), it is encoded in a single byte. 
    If the value is $> 252$ and $\le 65535$ ($0xFFFF$), the first byte is $253$ ($0xFD$), followed by the 2-byte big-endian representation of the number. 
    If the value is $> 65535$ and $\le 4294967295$ ($0xFFFFFFFF$), the first byte is $254$ ($0xFE$), followed by the 4-byte big-endian representation. 
    If the value is $> 4294967295$, the first byte is $255$ ($0xFF$), followed by the 8-byte big-endian representation. 
    This big-endian convention aligns with standard network protocols, facilitating interoperability between systems that may internally use little-endian storage (like most x86 processors). 

    */


    address.sin_family = AF_INET;
    // address.sin_addr.s_addr ; this reffers to the converted ip address variable that we need to put the ip address into after converting the ip address into a integer from a character 
    inet_pton(AF_INET,ip,&address.sin_addr.s_addr);


    //while looking at ip addresses we see that the port for http is 80 and the port for https is 443 in most of the sites 


    int result = connect(socketFD, (struct sockaddr*)&address, sizeof(address));

    if (result == 0 )
    {
        printf("The connection was successful");
    }
    



    return 0;
}