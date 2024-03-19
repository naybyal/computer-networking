#include <stdio.h>

int min(int x, int y) {
    if (x < y) {
        return x;
    }
    return y;
}

int main() {
    int drop = 0, mini, msec, cap, count = 0;
    int i, inp[25], process;

    printf("Enter the bucket size: ");
    scanf("%d", &cap);
    printf("Enter the output rate: ");
    scanf("%d", &process);
    printf("Enter the number of seconds you need to stimulate: ");
    scanf("%d", &msec);

    for (i = 0; i < msec; i++) {
        printf("Enter the size of the packet entering at %d sec: ", i + 1);
        scanf("%d", &inp[i]);
    }

    printf("Time | Packet received | Packet sent from bucket | Packet left in bucket | Packet drop\n");
    for (i = 0; i < msec; i++) {
        count += inp[i];
        if (count > cap) {
            drop = count - cap;
            count = cap;
        } else if (count <= cap) {
            printf("%d", i + 1);
            printf("\t%d", inp[i]);
            mini = min(count, process);
            printf(" \t\t%d", mini);
            count = count - mini;
            printf(" \t\t%d", count);
            printf(" \t\t%d\n", drop);
            drop = 0;
        }
    }

    for (; count != 0; i++) {
        if (count > cap) {
            drop = count - cap;
            count = cap;
        }
        printf("%d", i + 1);
        printf("\t0");
        mini = min(count, process);
        printf(" \t\t%d", mini);
        count = count - mini;
        printf(" \t\t%d", count);
        printf(" \t\t%d\n", drop);
    }

    return 0;
}

