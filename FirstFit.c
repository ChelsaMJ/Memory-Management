#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MEMORY_SIZE 1000
int memory[MEMORY_SIZE] = {0};

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
memory[k] = process_id;
}
return i;
}
}
}
return -1;
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
int simulation_time;
printf("Enter the simulation time: ");
scanf("%d", &simulation_time);

int fragmentation[10] = {0};
int wasted_memory[10] = {0};

for (int time_unit = 0; time_unit < simulation_time; time_unit++) {
int allocated_processes[5][3] = {{0}};
int deallocated_processes[3][3] = {{0}};


for (int process_id = 1; process_id <= 5; process_id++) {
int process_size;
printf("Enter process size for Process %d (between 10 and 100): ", process_id);
scanf("%d", &process_size);

int allocation_result = allocateFirstFit(process_id, process_size);
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
