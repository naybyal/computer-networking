#include<stdio.h>

void main() {
	int incoming, outgoing, buck_size, n, store = 0;
	printf("Enter bucket size, outgoing rate and number of inputs: ");
	scanf("%d %d %d", & buck_size, & outgoing, & n);
	while (n != 0) {
		printf("Enter incoming packet size: ");
		scanf("%d", & incoming);
		printf("Incoming packet size is %d\n", incoming);
		
		if (incoming <= (buck_size-store)) {
			store += incoming;
			printf("Bucket buffer size is %d out of %d\n", store, buck_size);
		} else {
			printf("Dropped %d no of packets\n",
			incoming - (buck_size - store));
			store = buck_size;
			printf("Bucket buffer size is %d out of %d\n", store, buck_size);
		}
		
		store = store-outgoing;
		
		if (store < 0)
			store = 0;
			printf("After outgoing, %d packets left out of %d in buffer\n", store, buck_size);
		n--;
	}
}
