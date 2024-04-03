#include <stdio.h>

void main() {
    int bucketCapacity, outputRate, simulationDuration;
    int i, packetsReceived, packetsSent, packetsLeft, packetsDropped, bucketSize;
    printf("Enter the bucket capacity (in packets): ");
    scanf("%d", &bucketCapacity);
    printf("Enter the output rate (in packets/second): ");
    scanf("%d", &outputRate);
    printf("Enter the simulation duration (in seconds): ");
    scanf("%d", &simulationDuration);
    bucketSize = 0;
    packetsDropped = 0;
    printf("Time \t Packets Received \t Packets Sent \t Packets Left \t Packets Dropped\n");
    for (i=1; i<=simulationDuration; i++) {
        printf("Enter the number of packets received at time %d: ", i);
        scanf("%d", &packetsReceived);
        bucketSize += packetsReceived;
        packetsSent = (bucketSize < outputRate) ? bucketSize : outputRate;
        bucketSize -= packetsSent;
        packetsLeft = bucketSize;
        if (bucketSize > bucketCapacity) {
            packetsDropped += (bucketSize - bucketCapacity);
            bucketSize = bucketCapacity;  
        }
        printf("%d \t %d \t\t\t %d \t\t %d \t\t\t %d\n", i, packetsReceived, packetsSent, packetsLeft, packetsDropped);
    }
}

