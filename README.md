This C program develops CPU Scheduling Algorithms in Linux environment. A
sample input file is provided, which can be used to develop the Shortest Job First (SJF) CPU Scheduling Algorithm.

Format of the Input File:
The input file containsseveral test cases for this program. Every line of the input file represents one individual test case.
For example, if there are four lines inside the input file, it means the program must execute four
different test cases. Every input line consists of several processes and their corresponding
information, such as process name, arrival time (art_1), and burst time (brt_1) which follows the
format below:  

Input format: process_1 art_1 brt_1 process_2 art_2 brt_2 process_n art_n brt_n
Input example: p1 0 23 p2 1 3 p3 2 3
In the example input given above, there are three processes such as p1, p2, and p3. The arrival and
burst time of process p1 is 0 and 23, respectively. The arrival and burst time for process p2 is 1 and
3, respectively. The arrival and burst time of process p3 is 2 and 3, respectively. The individual
entries in the input line are separated by space.

What the program does:
Supply the given sjf_input.txt file to the program. First, parse the input file
line-wise where every line in the input file is a test case. For every test case in the input file, apply
Shortest Job First (SJF) Scheduling and output the process schedule details. The output of the 
program follows the format of the sample output given below. Consider two decimalpoints for printing the fractional number.  

Sample Content in sjf_input.txt :
<li>p1 0 3 p2 1 5 p3 2 3
<li>p1 1 3 p2 2 2 p3 2 1
  
Sample Output:  

Test case #1: p1 0 3 p2 1 5 p3 2 3
<li>Number of Processes: 3
<li>Process Scheduling Started:CPU Time 0: [P1 Arrived] P1 [0/3]
<li>CPU Time 1: [P2 Arrived] P1 [1/3]
<li>CPU Time 2: [P3 Arrived] P1 [2/3]
<li>CPU Time 3: P1 [3/3]
<li>Process P1 completed with Turnaround Time: 3, Waiting Time: 0
<li>CPU Time 3: P3 [0/3]
<li>CPU Time 4: P3 [1/3]
<li>CPU Time 5: P3 [2/3]
<li>CPU Time 6: P3 [3/3]
<li>Process P3 completed with Turnaround Time: 4, Waiting Time: 1
<li>CPU Time 6: P2 [0/5]
<li>CPU Time 7: P2 [1/5]
<li>CPU Time 8: P2 [2/5]
<li>CPU Time 9: P2 [3/5]
<li>CPU Time 10: P2 [4/5]
<li>CPU Time 11: P2 [5/5]
<li>Process P2 completed with Turnaround Time: 10, Waiting Time: 5
<li>Process scheduling completed with Avg Turnaround Time: 5.67, Avg Waiting Time:2.00  
  
Test case #2: p1 1 3 p2 2 2 p3 2 1
<li>Number of Processes: 3
<li>Process Scheduling Started:
<li>CPU Time 0: None
<li>CPU Time 1: [P1 Arrived] P1 [0/3]
<li>CPU Time 2: [P2 Arrived] [P3 Arrived] P1 [1/3]
<li>CPU Time 3: P1 [2/3]
<li>CPU Time 4: P1 [3/3]
<li>Process P1 completed with Turnaround Time: 3, Waiting Time: 0
<li>CPU Time 4: P3 [0/1]
<li>CPU Time 5: P3 [1/1]
<li>Process P3 completed with Turnaround Time: 3, Waiting Time: 2
<li>CPU Time 5: P2 [0/2]
<li>CPU Time 6: P2 [1/2]
<li>CPU Time 7: P2 [2/2]
<li>Process P2 completed with Turnaround Time: 5, Waiting Time: 3
<li>Process scheduling completed with Avg Turnaround Time: 3.67, Avg Waiting Time:1.67
