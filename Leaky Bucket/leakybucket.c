#include <stdio.h>

// Function to calculate minimum of two numbers
int min(int x, int y) {
    if (x < y) {
        return x;
    }
    return y;
}

int main() {
    int drop = 0, mini, msec, cap, count = 0;
    int i, inp[25], process;

    // User input: Bucket size, output rate, and simulation duration
    printf("Enter the bucket size: ");
    scanf("%d", &cap);
    printf("Enter the output rate: ");
    scanf("%d", &process);
    printf("Enter the number of seconds you need to stimulate: ");
    scanf("%d", &msec);

    // Input packet sizes for each second of the simulation
    for (i = 0; i < msec; i++) {
        printf("Enter the size of the packet entering at %d sec: ", i + 1);
        scanf("%d", &inp[i]);
    }

    // Print table header for simulation output
    printf("Time | Packet received | Packet sent from bucket | Packet left in bucket | Packet drop\n");

    // Simulation loop for each second
    for (i = 0; i < msec; i++) {
        // Add incoming packets to the bucket
        count += inp[i];

        // Check if bucket overflow occurs
        if (count > cap) {
            drop = count - cap;  // Calculate dropped packets
            count = cap;         // Limit bucket size
        } else if (count <= cap) {
            // Calculate tokens to be sent based on output rate
            mini = min(count, process);

            // Update remaining tokens in the bucket
            count = count - mini;

            // Print simulation output for the current second
            printf("%d", i + 1);     // Time
            printf("\t%d", inp[i]);  // Packets received
            printf(" \t\t%d", mini); // Packets sent from bucket
            printf(" \t\t%d", count); // Packets left in bucket
            printf(" \t\t%d\n", drop); // Packets dropped

            drop = 0; // Reset dropped packets
        }
    }

    // Continue simulation until the bucket is empty
    for (; count != 0; i++) {
        // Check if bucket overflow occurs
        if (count > cap) {
            drop = count - cap;  // Calculate dropped packets
            count = cap;         // Limit bucket size
        }

        // Calculate tokens to be sent based on output rate
        mini = min(count, process);

        // Update remaining tokens in the bucket
        count = count - mini;

        // Print simulation output for emptying the bucket
        printf("%d", i + 1);     // Time
        printf("\t0");           // No packets received
        printf(" \t\t%d", mini); // Packets sent from bucket
        printf(" \t\t%d", count); // Packets left in bucket
        printf(" \t\t%d\n", drop); // Packets dropped
    }

    return 0; // End of program
}

