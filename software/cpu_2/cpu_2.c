#include <stdio.h>
#include <string.h>
#include "system.h"
#include "nios2.h"
#include <unistd.h>
//defines the performance counter peripheral


//defines the shared memory
#define shared_mem ONCHIP_MEMORY2_0_BASE

//create a shared memory structure
//variables status_start and status_done will be shared variables used for synchronization.
typedef struct
{
    int M1s[10][10];
    int M2s[10][10];
    int Cs[10][10];
    int status_start;
    int status_done;
}   shared_mem_struct;

int main()
{
    printf("Hello\n");
   //initialize the message buffer location
   shared_mem_struct *message;
   message = (shared_mem_struct*)shared_mem;

  volatile int i,j,k; //i = row, j = column,

  int count;
  int M1[10][10]={  0,0,0,0,0,0,0,0,0,0,
                    32,32,33,34,32,32,33,34,32,32,
                    32,32,33,34,32,32,33,34,32,32,
                    32,32,33,34,32,32,33,34,32,32,
                    32,32,33,34,32,32,33,34,32,32,
                    19,32,33,34,32,32,33,34,32,32,
                    32,32,33,34,32,32,33,34,32,32,
                    32,32,33,34,32,32,33,34,32,32,
                    32,32,33,34,32,32,33,34,32,32,
                    19,32,33,34,32,32,33,34,32,32};

  int M2[10][10]={  32,32,33,34,32,32,33,34,32,32,
                    32,32,33,34,32,32,33,34,32,32,
                    32,32,33,34,32,32,33,34,32,32,
                    32,32,33,34,32,32,33,34,32,32,
                    32,32,33,34,32,32,33,34,32,32,
                    19,32,33,34,32,32,33,34,32,32,
                    32,32,33,34,32,32,33,34,32,32,
                    32,32,33,34,32,32,33,34,32,32,
                    32,32,33,34,32,32,33,34,32,32,
                    19,32,33,34,32,32,33,34,32,32};
  int C[10][10]= {0};

  for( i=0; i<10; i++)
  {
    for (j=0; j<10; j++)
    {
        (message)->M1s[i][j]=M1[i][j];
        (message)->M2s[i][j]=M2[i][j];
    }
  }
  (message)->status_start++;
     // (message)->status_done++;

  while((message)->status_start!=3);
  count = 0;
  while(count < 1000)
  {
    count++;
    for (i=0;i<=4;i++)
    {
      for (j=0;j<=9;j++)
      {
        (message)-> Cs[i][j] = 0;
         for (k=0;k<=9;k++)
	  {
            (message)->Cs[i][j]+=(message)->M1s[i][k]*(message)->M2s[k][j];
          }
          //printf("%f ", C[i][j]);
      }
    }
  }

  (message)->status_done++;
    //CPU stops the performance_count and print performance_count result and matrix C from 1000th iteration on the terminal.




  return 0;
}
