#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

/*
   This program illustrates the Shortest Job First (SJF) CPU Scheduling Algorithm.
*/

// gcc assignment4.c -o assignment4.out
//./assignment4.out

struct Process
{
   char name[20]; // process name
   int art;       //  arrival time
   int brt;       // burst time
   int WT;        // waiting time
   int TAT;       // turnaround time
   int ET;        // end time: the moment when process complete execution
                  // end time = end time of last process executed + burst time
};

int main()
{
   FILE *fptr;

   int caseCount = 0; // test cases count
   int timeCount = 0; // CPU time count
   int arrayCount1, arrayCount3, totalCount, smallest, pos, tempArt, tempBrt;
   float avgWT, avgTAT; // average waiting time and average turnaround time

   char tempName[10];
   char nextProcess[100];
   char processName[1000];
   char readString[100];

   static const struct Process EmptyStruct;

   fptr = fopen("sjf_input.txt", "r");

   while (fgets(readString, sizeof(readString), fptr))
   {
      struct Process processes[100];
      arrayCount1 = 0;
      arrayCount3 = 0;
      avgWT = 0;  // average waiting time
      avgTAT = 0; // average turnaround time
      caseCount += 1;
      nextProcess[0] = '\0';
      processName[0] = '\0';

      printf("\nTest case #%d: %s", caseCount, readString);

      char *word = strtok(readString, " ");
      // loop through the string to extract all the words
      while (word != NULL)
      {
         // each process in the file stores three things: process name, arrival time and burst time
         if (arrayCount1 % 3 == 0)
         {
            for (int i = 0; i < 3; i++)
            {
               switch (i)
               {
               case 0:

                  processes[arrayCount3].name[0] = '\0';
                  word[0] = toupper(word[0]);
                  strcat(processes[arrayCount3].name, word);
                  break;

               case 1:
                  processes[arrayCount3].art = atoi(word);
                  break;

               case 2:
                  processes[arrayCount3].brt = atoi(word);
                  break;
               }

               word = strtok(NULL, " ");
            }

            processes[arrayCount3].WT = 0;  // initialize waiting time
            processes[arrayCount3].TAT = 0; // initialize turnaround time
            arrayCount3 += 1;
         }

         arrayCount1 += 1;
      }

      // total count of process = (arrayCount1 + 2) / 3
      // "+2": arrayCount does not count the final two words
      // "/3": each process stores 3 things in the file
      totalCount = (arrayCount1 + 2) / 3;
      printf("Number of Processes: %d\n", totalCount);
      printf("Process Scheduling Started:\n");

      // sort the process array in an increasing order based on the arrival time and burst time
      for (int i = 0; i < totalCount - 1; i++)
      {
         for (int j = i + 1; j < totalCount; j++)
         {
            if (processes[i].art > processes[j].art)
            {
               // save values
               tempName[0] = '\0';
               strcat(tempName, processes[i].name);
               tempArt = processes[i].art;
               tempBrt = processes[i].brt;

               // swap value for process i and process i+1
               processes[i].name[0] = '\0';
               strcat(processes[i].name, processes[j].name);
               processes[i].art = processes[j].art;
               processes[i].brt = processes[j].brt;

               processes[j].name[0] = '\0';
               strcat(processes[j].name, tempName);
               processes[j].art = tempArt;
               processes[j].brt = tempBrt;
            }
            else if ((processes[i].art == processes[j].art) && (processes[j].brt < processes[i].brt))
            {
               // save values
               tempName[0] = '\0';
               strcat(tempName, processes[i].name);
               tempArt = processes[i].art;
               tempBrt = processes[i].brt;

               // change value for process i
               processes[i].name[0] = '\0';
               strcat(processes[i].name, processes[j].name);
               processes[i].art = processes[j].art;
               processes[i].brt = processes[j].brt;

               // change value for process i+1
               processes[j].name[0] = '\0';
               strcat(processes[j].name, tempName);
               processes[j].art = tempArt;
               processes[j].brt = tempBrt;
            }
         }
      }

      processes[0].TAT = processes[0].brt;                   // calculate turnaround time for the first arrived process
      processes[0].ET = processes[0].brt + processes[0].art; // calculate end time for the first arrived process

      // pick the next avaiable process accroding to SJF
      for (int i = 1; i < totalCount; i++)
      {
         smallest = 1000;
         for (int j = i; j < totalCount; j++)
         {
            if (processes[i].art < processes[i - 1].ET)
            {
               if (processes[j].brt < smallest)
               {
                  smallest = processes[j].brt;
                  pos = j;
               }
            }
         }

         // when a process has smaller burst time, swap it with process i
         // save values
         if (i != pos) // if i = pos (same position), there's no need for swaping
         {
            tempName[0] = '\0';
            strcat(tempName, processes[i].name);
            tempArt = processes[i].art;
            tempBrt = processes[i].brt;

            // swap values
            processes[i].name[0] = '\0';
            strcat(processes[i].name, processes[pos].name);
            processes[i].art = processes[pos].art;
            processes[i].brt = processes[pos].brt;
            processes[pos].name[0] = '\0';
            strcat(processes[pos].name, tempName);
            processes[pos].art = tempArt;
            processes[pos].brt = tempBrt;
         }

         // end time = end time of last process executed + burst time
         processes[i].ET = processes[i - 1].ET + processes[i].brt;
      }

      // calculate turnaround time and waiting time for the rest processes
      for (int i = 1; i < totalCount; i++)
      {
         processes[i].TAT = processes[i].ET - processes[i].art;
         processes[i].WT = processes[i].TAT - processes[i].brt;
      }

      // before the first process arrived
      if (processes[0].art != timeCount)
      {
         for (int i = 0; i < processes[0].art; i++)
         {
            printf("CPU Time %d: None\n", i);
         }
         timeCount = processes[0].art;
      }

      // after the first processes arrived
      for (int i = 0; i < totalCount; i++)
      {
         // CPU time 0: prepare to execute first process in the sorted list

         // if (processes[i].art <= timeCount)
         // {
         for (int k = 0; k < processes[i].brt + 1; k++)
         {
            for (int j = totalCount - 1; j > i - 1; j--)
            {
               // output format:
               // CPU Time 0: [P1 Arrived] P1 [0/3]
               // CPU Time 1: [P2 Arrived] P1 [1/3]
               // CPU Time 2: [P3 Arrived] P1 [2/3]
               // CPU Time 3: P1 [3/3]
               
               // check if a proces arrives at this time and it is not printed out
               if (processes[j].art == timeCount && strstr(processName, processes[j].name) == NULL) 
               { 
                  strcat(nextProcess, " ");
                  strcat(nextProcess, "[");
                  strcat(nextProcess, processes[j].name);
                  strcat(nextProcess, " Arrived]");
                  strcat(processName, processes[j].name);
               }
            }
            strcat(nextProcess, " ");
            printf("CPU Time %d:%s%s [%d/%d]\n", timeCount, nextProcess, processes[i].name, k, processes[i].brt);

            nextProcess[0] = '\0';
            if (k < processes[i].brt)
            {
               timeCount += 1;
            }
         }

         printf("Process %s completed with Turnaround Time: %d, Waiting Time: %d\n", processes[i].name, processes[i].TAT, processes[i].WT);
      }

      //  calculate average waiting time and average turnaround time
      for (int i = 0; i < totalCount; i++)
      {
         avgWT += processes[i].WT;
         avgTAT += processes[i].TAT;
      }
      avgWT /= totalCount;
      avgTAT /= totalCount;

      printf("Process scheduling completed with Avg Turnaround Time: %.2f, Avg Waiting Time: %.2f\n", avgTAT, avgWT);

      // clear readString array each iteration
      readString[0] = '\0';
      // clear struct each iteration
      for (int i = 0; i < totalCount; i++)
      {
         processes[i] = EmptyStruct;
      }
   }

   fclose(fptr);

   return 0;
}
