#include "./unp.h"
// requires netinet/sctp.h 
//  install it by running the command `sudo apt install libsctp-dev` in the Terminal
int main(int argc, char **argv) {

    union {
        short s;
        char c[sizeof(short)];
    } un;

    un.s = 0x0102;
    printf("%s\t->\t", CPU_VENDOR_OS);

    if (sizeof(short) == 2) {
        if (un.c[0] == 1 && un.c[1] == 2) 
            printf("big-endian\n");
        else if (un.c[0] == 2 && un.c[1] == 1) 
            printf("little-endian\n");
        else 
            printf("unknown\n");
    } else 
        printf("sizeof(short) = %d", sizeof(short));
    
    exit(0);
    
}