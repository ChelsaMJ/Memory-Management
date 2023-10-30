#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MEMORY_SIZE 1000
int memory[MEMORY_SIZE] = {0};

int allocateBestFit(int process_id, int process_size) {
int best_fit_index = -1;
int best_fit_size = MEMORY_SIZE;

for (int i = 0; i < MEMORY_SIZE; i++) {
if (memory[i] == 0) {
int block_size = 0;
int j = i;

while (j < MEMORY_SIZE && memory[j] == 0) {
block_size++;
j++;
}

if (block_size >= process_size && block_size < best_fit_size) {
best_fit_index = i;
best_fit_size = block_size;
}
}
}

if (best_fit_index != -1) {
for (int k = best_fit_index; k < best_fit_index + process_size; k++) {
memory[k] = process_id;
}
return best_fit_index;
}

return -1; // Allocation failed
}

void deallocate(int process_id, int start_index, int process_size) {
for (int i = start_index; i < start_index + process_size; i++) {
if (memory[i] == process_id) {
memory[i] = 0;
}
}
}

int main() {
srand(time(NULL));
int simulation_time = 10;
int fragmentation[10] = {0};
int wasted_memory[10] = {0};

for (int time_unit = 0; time_unit < simulation_time; time_unit++) {
int allocated_processes[5][3] = {{0}};
int deallocated_processes[3][3] = {{0}};

for (int process_id = 1; process_id <= 5; process_id++) {
int process_size = rand() % 91 + 10;
int allocation_result = allocateBestFit(process_id, process_size);
if (allocation_result != -1) {
allocated_processes[process_id - 1][0] = process_id;
allocated_processes[process_id - 1][1] = process_size;
allocated_processes[process_id - 1][2] = allocation_result;
}
}

for (int i = 0; i < 3; i++) {
int process_index = rand() % 5;
int process_id = allocated_processes[process_index][0];
int start_index = allocated_processes[process_index][2];
int process_size = allocated_processes[process_index][1];
if (process_id != 0) {
deallocate(process_id, start_index, process_size);
deallocated_processes[i][0] = process_id;
deallocated_processes[i][1] = process_size;
deallocated_processes[i][2] = start_index;
}
}

for (int i = 0; i < MEMORY_SIZE; i++) {
if (memory[i] == 0) {
fragmentation[time_unit]++;
wasted_memory[time_unit]++;
}
}

printf("--------------------------------------------------\n");
printf("Time Unit %d:\n", time_unit + 1);
printf("Allocated Processes:\n");
printf(" Process No.\tProcess Size\tBlock No.\n");
for (int i = 0; i < 5; i++) {
if (allocated_processes[i][0] != 0) {
printf(" %d\t\t%d\t\t%d\n", allocated_processes[i][0], allocated_processes[i][1], allocated_processes[i][2]);
}
}
printf("Deallocated Processes:\n");
printf(" Process No.\tProcess Size\tBlock No.\n");
for (int i = 0; i < 3; i++) {
if (deallocated_processes[i][0] != 0) {
printf(" %d\t\t%d\t\t%d\n", deallocated_processes[i][0], deallocated_processes[i][1], deallocated_processes[i][2]);
}
}
printf("Average Fragmentation: %.2f\n", (float)fragmentation[time_unit] / MEMORY_SIZE);
printf("Number of Wasted Memory Blocks: %d\n", wasted_memory[time_unit]);
printf("--------------------------------------------------\n");
}

return 0;
}
