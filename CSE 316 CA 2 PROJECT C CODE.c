#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NAME_SIZE 3
#define MAX_PROCESSES 15

struct process {
    char name[MAX_NAME_SIZE];
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
};

typedef struct process Process;

int compare(const void* a, const void* b) {
    Process* pa = (Process*) a;
    Process* pb = (Process*) b;

    if (pa->priority == pb->priority) {
        return pa->arrival_time - pb->arrival_time;
    }

    return pa->priority - pb->priority;
}

void two_level_scheduling(Process processes[], int num_processes) {
    int time = 0;
    Process* current_process = NULL;
    Process* completed_processes[MAX_PROCESSES] = { NULL };
    int completed_count = 0;

    qsort(processes, num_processes, sizeof(Process), compare);

    Process queue1[MAX_PROCESSES] = { 0 };
    int queue1_count = 0;
    Process queue2[MAX_PROCESSES] = { 0 };
    int queue2_count = 0;

    for (int i = 0; i < num_processes; i++) {
        queue1[queue1_count++] = processes[i];
    }

    while (queue1_count > 0 || queue2_count > 0 || current_process != NULL) {
        if (queue1_count > 0) {
            Process next_process = queue1[0];
            for (int i = 1; i < queue1_count; i++) {
                if (next_process.priority > queue1[i].priority) {
                    next_process = queue1[i];
                }
            }

            if (current_process == NULL || next_process.priority < current_process->priority) {
                if (current_process != NULL) {
                    printf("Process named %s preempted and has been enqueued in Queue 2\n", current_process->name);
                    queue2[queue2_count++] = *current_process;
                }

                current_process = &queue1[0];
                for (int i = 1; i < queue1_count; i++) {
                    if (current_process->priority > queue1[i].priority) {
                        current_process = &queue1[i];
                    }
                }

                printf("Executing process %s from Queue 1\n", current_process->name);
                time += 2;
                current_process->remaining_time -= 2;

                if (current_process->remaining_time <= 0) {
                    completed_processes[completed_count++] = current_process;
                    printf("Process %s completed\n", current_process->name);
                    current_process = NULL;
                    queue1[0] = queue1[--queue1_count];
                }
                else {
                    printf("Process named %s preempted and has been enqueued in Queue 2\n", current_process->name);
                    queue2[queue2_count++] = *current_process;
                    current_process = NULL;
                    queue1[0] = queue1[--queue1_count];
                }

                if (queue1_count > 1) {
                    qsort(queue1, queue1_count, sizeof(Process), compare);
                }
            }
            else {
                for (int i = 1; i < queue1_count; i++) {
                    if (queue1[i].priority < current_process->priority) {
                        Process temp = *current_process;
                        *current_process = queue1[i];
                        queue1[i] = temp;
                    }
                }
            }
        }
        else {
            if (current_process == NULL && queue2_count > 0) {
Process next_process = queue2[0];
for (int i = 1; i < queue2_count; i++) {
if (next_process.priority > queue2[i].priority) {
next_process = queue2[i];
}
}

            current_process = &queue2[0];
            for (int i = 1; i < queue2_count; i++) {
                if (current_process->priority > queue2[i].priority) {
                    current_process = &queue2[i];
                }
            }

            printf("Executing process %s from Queue 2\n", current_process->name);
            time += current_process->remaining_time;
            current_process->remaining_time = 0;

            completed_processes[completed_count++] = current_process;
            printf("Process %s completed\n", current_process->name);
            current_process = NULL;
            queue2[0] = queue2[--queue2_count];

            if (queue2_count > 1) {
                qsort(queue2, queue2_count, sizeof(Process), compare);
            }
        }
        else if (current_process != NULL) {
            printf("Executing process %s from Queue 1\n", current_process->name);
            time += current_process->remaining_time;
            current_process->remaining_time = 0;

            completed_processes[completed_count++] = current_process;
            printf("Process %s completed\n", current_process->name);
            current_process = NULL;

            if (queue1_count > 1) {
                queue1[0] = queue1[--queue1_count];
                qsort(queue1, queue1_count, sizeof(Process), compare);
            }
            else {
                queue1_count--;
            }
        }
        else {
            time++;
        }
    }
}

printf("All processes have completed.\n");
printf("Process Name\tArrival Time\tBurst Time\tPriority\n");

for (int i = 0; i < completed_count; i++) {
    printf("%s\t\t%d\t\t%d\t\t%d\n", completed_processes[i]->name, completed_processes[i]->arrival_time, completed_processes[i]->burst_time, completed_processes[i]->priority);
}
}

int main() {
srand(time(NULL));
Process processes[MAX_PROCESSES] = { 0 };
int num_processes = rand() % MAX_PROCESSES + 1;

printf("Number of processes: %d\n", num_processes);

for (int i = 0; i < num_processes; i++) {
    sprintf(processes[i].name, "P%d", i);
    processes[i].arrival_time = rand() % 10;
    processes[i].burst_time = rand() % 20 + 1;
    processes[i].priority = rand() % 5;
    processes[i].remaining_time = processes[i].burst_time;
    printf("Process %s -- Arrival Time: %d, Burst Time: %d, Priority: %d\n", processes[i].name, processes[i].arrival_time, processes[i].burst_time, processes[i].priority);
}

two_level_scheduling(processes, num_processes);

return 0;
}
