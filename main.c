#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Initialize memory with a certain size
#define MEMORY_SIZE 1000
int memory[MEMORY_SIZE] = {0};

// Function to allocate memory using First-Fit
int allocateFirstFit(int process_id, int process_size) {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i] == 0) {
            int j = i;
            while (j < i + process_size) {
                if (memory[j] == 1) {
                    break;
                }
                j++;
            }
            if (j == i + process_size) {
                for (int k = i; k < i + process_size; k++) {
                    memory[k] = process_id;  // Assign process ID to allocated memory
                }
                return i;
            }
        }
    }
    return -1;  // Allocation failed
}

// Function to deallocate memory
void deallocate(int process_id, int start_index, int process_size) {
    for (int i = start_index; i < start_index + process_size; i++) {
        if (memory[i] == process_id) {
            memory[i] = 0;  // Deallocate memory by setting it to 0
        }
    }
}

int main() {
    srand(time(NULL));  // Seed the random number generator

    // Simulation parameters
    int simulation_time = 10;  // Number of time units
    int fragmentation[10] = {0};
    int wasted_memory[10] = {0};

    // Main simulation loop
    for (int time_unit = 0; time_unit < simulation_time; time_unit++) {
        int allocated_processes[5][3] = {{0}};  // Process ID, start_index, process_size
        int deallocated_processes[3][3] = {{0}};  // Process ID, start_index, process_size

        // Simulate processes requesting memory
        for (int process_id = 1; process_id <= 5; process_id++) {
            int process_size = rand() % 91 + 10;  // Random process size between 10 and 100
            int allocation_result = allocateFirstFit(process_id, process_size);
            if (allocation_result != -1) {
                allocated_processes[process_id - 1][0] = process_id;
                allocated_processes[process_id - 1][1] = allocation_result;
                allocated_processes[process_id - 1][2] = process_size;
            }
        }

        // Simulate processes completing and deallocating memory
        for (int i = 0; i < 3; i++) {
            int process_index = rand() % 5;
            int process_id = allocated_processes[process_index][0];
            int start_index = allocated_processes[process_index][1];
            int process_size = allocated_processes[process_index][2];
            if (process_id != 0) {
                deallocate(process_id, start_index, process_size);
                deallocated_processes[i][0] = process_id;
                deallocated_processes[i][1] = start_index;
                deallocated_processes[i][2] = process_size;
            }
        }

        // Calculate fragmentation and wasted memory
        for (int i = 0; i < MEMORY_SIZE; i++) {
            if (memory[i] == 0) {
                fragmentation[time_unit]++;
                wasted_memory[time_unit]++;
            }
        }

        // Print allocation and deallocation details for this time unit
        printf("Time Unit %d:\n", time_unit + 1);
        printf("Allocated Processes:\n");
        for (int i = 0; i < 5; i++) {
            if (allocated_processes[i][0] != 0) {
                printf("  Process %d allocated %d units of memory at index %d\n",
                       allocated_processes[i][0], allocated_processes[i][2], allocated_processes[i][1]);
            }
        }
        printf("Deallocated Processes:\n");
        for (int i = 0; i < 3; i++) {
            if (deallocated_processes[i][0] != 0) {
                printf("  Process %d deallocated %d units of memory starting from index %d\n",
                       deallocated_processes[i][0], deallocated_processes[i][2], deallocated_processes[i][1]);
            }
        }
    }

    // Print simulation results
    for (int t = 0; t < simulation_time; t++) {
        printf("Time Unit %d:\n", t + 1);
        printf("Average Fragmentation: %.2f\n", (float)fragmentation[t] / MEMORY_SIZE);
        printf("Number of Wasted Memory Blocks: %d\n", wasted_memory[t]);
    }

    return 0;
}