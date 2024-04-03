#include <stdio.h>
#include <unistd.h> // for sleep function

int main() {
    int bucketCapacity, outputRate, simulationDuration;
    int i, packetsReceived, packetsSent, packetsLeft, packetsDropped, bucketSize;

    // User input: Bucket capacity, output rate, and simulation duration
    printf("Enter the bucket capacity (in packets): ");
    scanf("%d", &bucketCapacity);
    printf("Enter the output rate (in packets/second): ");
    scanf("%d", &outputRate);
    printf("Enter the simulation duration (in seconds): ");
    scanf("%d", &simulationDuration);

    // Initialize variables
    bucketSize = 0;
    packetsDropped = 0;

    // Print table header for simulation output
    printf("Time \t Packets Received \t Packets Sent \t Packets Left \t Packets Dropped\n");

    // Simulation loop for each second
    for (i = 1; i <= simulationDuration; i++) {
        // Prompt user to enter packets received at this second
        printf("Enter the number of packets received at time %d: ", i);
        scanf("%d", &packetsReceived);

        // Calculate new bucket size after receiving packets
        bucketSize += packetsReceived;

        // Send packets from the bucket at the constant output rate
        packetsSent = (bucketSize < outputRate) ? bucketSize : outputRate;
        bucketSize -= packetsSent;

        // Calculate packets left in the bucket
        packetsLeft = bucketSize;

        // Calculate packets dropped if bucket overflows
        if (bucketSize > bucketCapacity) {
            packetsDropped += (bucketSize - bucketCapacity);
            bucketSize = bucketCapacity;  // Limit bucket size
        }

        // Print simulation output for the current second
        printf("%d \t %d \t\t\t %d \t\t %d \t\t\t %d\n", i, packetsReceived, packetsSent, packetsLeft, packetsDropped);

        // Sleep for 1 second to simulate real-time operation
        sleep(1);
    }

    return 0; // End of program
}

