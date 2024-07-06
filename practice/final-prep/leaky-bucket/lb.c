#include <stdio.h>

void main() {

  int incoming, outgoing, bucketSize, n, store = 0, dropped;

  printf("Reading the bucket size, outgoing rate and the number of inputs... \n");
  scanf("%d%d%d", &bucketSize, &outgoing, &n);

  while (n-- != 0) {
    printf("Reading the incoming packet size: ");
    scanf("%d", &incoming);

    printf("The incoming packet size is %d\n", incoming);

    if (incoming <= bucketSize-store) {
      store += incoming;
      printf("Bucket buffer size is %d out of %d\n", store, bucketSize);
    } else {
      dropped = incoming - (bucketSize - store);
      printf("Dropped %d packets.", dropped);
      store = bucketSize;
      printf("Bucket buffer size is %d out of %d\n", store, bucketSize);
    }

    store -= outgoing;

    if (store < 0) {
      store = 0;
      printf("No packets left in the buffer");
    }

  }
}
