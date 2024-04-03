#include <stdio.h>
void main() {
    int bucket_capacity, output_rate, simulation_duration, i;
    int bucket_size = 0, packet_count = 0;
    printf("Enter the bucket capacity (in packets): ");
    scanf("%d", &bucket_capacity);
    printf("Enter the output rate (packets per second): ");
    scanf("%d", &output_rate);
    printf("Enter the simulation duration (in seconds): ");
    scanf("%d", &simulation_duration);
    printf("\nTime \t Packet received \t Packet sent \t Packet exp in bucket \t Packet drop\n");
    for (i = 1; i <= simulation_duration; i++) {
        int incoming_packets;
        printf("\nEnter the number of packets entering at %d second: ", i);
        scanf("%d", &incoming_packets);

        bucket_size += incoming_packets;
        if (bucket_size > bucket_capacity) {
            printf("\n%d \t %d \t\t\t - \t\t\t %d \t\t\t %d\n", i, incoming_packets, bucket_size, bucket_size - bucket_capacity);
            bucket_size = bucket_capacity; 
            packet_count += bucket_size - bucket_capacity; 
        } else {
            int packets_sent = (bucket_size < output_rate) ? bucket_size : output_rate; 
            bucket_size -= packets_sent; 
            printf("\n%d \t %d \t\t\t %d \t\t\t %d \t\t\t -\n", i, incoming_packets, packets_sent, bucket_size);
        }
    }
    while (bucket_size > 0) {
        int packets_sent = (bucket_size < output_rate) ? bucket_size : output_rate; 
        bucket_size -= packets_sent; 
        printf("\n%d \t 0 \t\t\t %d \t\t\t %d \t\t\t -\n", i, packets_sent, bucket_size);
        i++;
    }
    printf("\nTotal packets dropped: %d\n", packet_count);
}

