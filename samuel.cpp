#include<stdio.h>
#include<pthread.h>
struct all_time
{
       int process,arrival_time,burst_time,waiting_time,turn_time,run_time;
};
void arriavl_bhim(struct all_time a[],int pro)
{
       int i,j;
       struct all_time temp;
       for(i=0;i<pro;i++)
       {
              for(j=i+1;j<pro;j++)
              {
                     if(a[i].arrival_time > a[j].arrival_time)
                     {
                           temp = a[i];
                           a[i] = a[j];
                           a[j] = temp;
                     }
              }
       }
       return;
}
int main()
{
       int i,j,pro,time,left,flag=0,slice;
       struct all_time a[100];
       float avg_wait=0,avg_turn=0;
       printf("\t......................Round Robin Scheduling................\n");
       printf("\n\n\nEnter Number Of Processes : ");
       scanf("%d",&pro);
       left=pro;
       for(i=0;i<pro;i++)
       {
              printf("\n\nEnter arrival time for Process P%d : ",i);
              scanf("%d",&a[i].arrival_time);
              printf("\n\nEnter Burst time for process p%d : ",i);
              scanf("%d",&a[i].burst_time);
              a[i].process = i;
              a[i].run_time = a[i].burst_time;
       }
       arriavl_bhim(a,pro);
       printf("\n\nEnter Time Slice  : ");
       scanf("%d",&slice);
       printf("\n_______________________________________\n");
       printf("\n\n\t\tGantt Chart\n");
       printf("0");
       for(time=0,i=0;left!=0;)
       {
              if(a[i].run_time<=slice && a[i].run_time>0)
              {
                     time = time + a[i].run_time;
                     printf(" ||[P%d]|| %d",a[i].process,time);
                     a[i].run_time=0;
                     flag=1;
              }
              else if(a[i].run_time > 0)
              {
                     a[i].run_time = a[i].run_time - slice;
                     time = time + slice;
                     printf(" ||[P%d]|| %d",a[i].process,time);
              }
              if(a[i].run_time==0 && flag==1)
              {
                     left--;
                     a[i].turn_time = time-a[i].arrival_time;
                     a[i].waiting_time = time-a[i].arrival_time-a[i].burst_time;
                     avg_wait = avg_wait + time-a[i].arrival_time-a[i].burst_time;
                     avg_turn = avg_turn + time-a[i].arrival_time;
                     flag=0;
              }
              if(i==pro-1)
                     i=0;
              else if(a[i+1].arrival_time <= time)
                     i++;
              else
                     i=0;
       }
       printf("\n\n");
       printf("__________________________________________________________________________________________\n");
       printf("Process\tArrival_Time\tBurst_Time\tTurnaround_Time\t\tWaiting_Time\n");
       printf("___________________________________________________________________________________________\n");
       for(i=0;i<pro;i++)
       {
              printf("P%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n",a[i].process,a[i].arrival_time,a[i].burst_time,a[i].turn_time,a[i].waiting_time);
       }
       printf("_____________________________________________________________________________________________\n\n\n\n");
       avg_wait = avg_wait/pro;
       avg_turn = avg_turn/pro;
       printf("\n\nAverage Waiting Time : %.2f\n",avg_wait);
       printf("\n\nAverage Turnaround Time : %.2f\n",avg_turn);
       return 0;
}

