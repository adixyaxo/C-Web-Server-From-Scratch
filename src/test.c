#include <stdio.h>
#include <string.h>
int main()
{

  char *request = "POST /api/users HTTP/1.1"
                  "Host: example.com"
                  "Content-Type: application/json"
                  "Content-Length: 27"
                  "{\"name\": \"Alice\", \"role\": \"admin\"}";

 


  return 0;
}