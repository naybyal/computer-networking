#include <stdio.h>

int main() {
    int incoming, outgoing, bucketSize, n, store=0;
    printf("Reading the bucket size, outgoing rate and number of inputs.. \n");
    scanf("%d%d%d", &bucketSize, &outgoing, &n);

    while (n-- != 0) {
        printf("Reading the incoming packet size : ");
        scanf("%d", &incoming);

        printf("Incoming packet size is %d\n", incoming);

        if (incoming <= (bucketSize-store)) {
            store += incoming;
            printf("Bucket buffer size is %d out of %d\n", store, bucketSize);
        } else {
            int dropped = incoming - (bucketSize-store);
            printf("Dropped %d no. of packets\n", dropped);
            store = bucketSize;
            printf("Bucket buffer size is %d out of %d\n", store, bucketSize);
        }

        store -= outgoing;

        if (store < 0) {
            store = 0;
            printf("After outgoing, 0 packets left out of %d in buffer\n", bucketSize);
        }
    }
}
