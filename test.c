#include <stdio.h>

int main() {


    
    int p = 7;
    int *pt = p;
    int* ptt = pt;
    
    
    printf(pt,p,ptt,*pt,*ptt,&pt,&p,&ptt);

    return 0;
}