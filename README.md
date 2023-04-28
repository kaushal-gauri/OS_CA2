# OS_CA2
CSC 316 OPERATING SYSTEM CA3 FULL CODE 

EXPLANATION

QUESTION 4
Design a scheduling program to implement a Queue with two levels: 
Level 1: Fixed priority preemptive Scheduling 
Level 2: Shortest Remaining Time First for a Fixed priority preemptive Scheduling (Queue 1), the Priority 0 is highest priority. If one process P1 is scheduled and running, another process P2 with higher priority comes. The New process (high priority) process P2 preempts currently running process P1 and process P1 will go to second level queue. Time for which process will strictly execute must be considered in the multiples of 2. All the processes in second level queue will complete their execution according to SRTF scheduling. 
Consider: 
1. Queue 2 will be processed after Queue 1 becomes empty.
2. Priority of Queue 2 has lower priority than in Queue 1

 
METHODOLOGY USED

The given code implements a two-level scheduling algorithm for process scheduling using priority queue data structure. The goal of the algorithm is to minimize the turnaround time and waiting time of processes. The algorithm is divided into two levels:

Level 1: Fixed priority preemptive Scheduling / Short-term scheduling using a priority queue q1. Processes are enqueued in q1 according to their priority, and the process with the highest priority is executed first. If a new process with higher priority arrives while a process is being executed, the current process is preempted and enqueued in another priority queue q2.
Level 2: Shortest Remaining Time First for a Fixed priority preemptive Scheduling using a priority queue q2. Processes in q2 are enqueued in (a round-robin fashion), (i.e., each process is executed for a time quantum of 1 unit.) If a process completes its execution, it is removed from the queue. If a process still has remaining burst time after the time quantum, it is enqueued again in q2.

The Process class represents a process and its attributes such as name, arrival time, burst time, priority, and remaining time. The __lt__ method is defined to compare two processes based on their priority and arrival time.

The two_level_scheduling function takes a list of Process objects as input and returns a list of completed processes. It initializes two priority queues q1 and q2, enqueues all the processes in q1, and executes them according to the two-level scheduling algorithm described above. The function also keeps track of the completion time of each process and returns a list of completed processes sorted by their completion time.
The no of processes to be processed are determined by the user. It is done through the input taken at the start of the program.
Finally, the code generates a list of random processes and prints their attributes. It calls the two_level_scheduling function to execute the processes and prints the names of completed processes.


C CODE OUTPUT SNAPSHOT
![image](https://user-images.githubusercontent.com/91831558/235073657-befd3101-7895-43ce-8edb-806e5512690b.png)
