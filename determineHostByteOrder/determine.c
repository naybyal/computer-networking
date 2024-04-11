//  Author  :   Nabiel
//  Program referenced from the book "Unix Network Programming : The Sockets Networking API (Vol.1)" by W. Richard Stevens and Kevin Kohler

#include "./unp.h"
// requires netinet/sctp.h 
//  install it by running the command `sudo apt install libsctp-dev` in the Terminal
int main(int argc, char **argv) {

    union {
        short s;
        char c[sizeof(short)];
    } un;
    /*
        The line un.s = 0x0102; sets the value of the short integer s to 0x0102, which is equal to 258 in decimal.
        If the system is big-endian, the first byte of s will be 0x01 and the second byte will be 0x02. 
        If the system is little-endian, the first byte of s will be 0x02 and the second byte will be 0x01.

        The reason the decimal value 258 is used in this code is because it is a convenient value that can be used to demonstrate the byte order of a short integer on both big-endian and little-endian systems. 
        The hexadecimal value 0x0102 is easy to recognize in both byte orders, making it a useful value for this purpose.
    */
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