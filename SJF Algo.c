#include<stdio.h>
#include<conio.h>

struct process{
    int arrival;
    int burst;
    int waiting;
    int turn_around;

    int p_no;
    int start_tym;
    int end_tym;
    float priority;
    }p[80];

void print()
{    printf("\tINVALID INPUT...\n\tPLEASE ENTER AGAIN\n");
}

int main()
{
    // INPUT FOR NUMBER OF PROCESSES
    int n;
    redo1:
    printf("\nEnter number of processes:");
    scanf("%d",&n);
    if(n<=0)
    {
        print();
        goto redo1;
    }

    // INPUT FOR ARRIVAL AND BURST TIME
    printf("\nEnter the Arrival time and Burst time:\n\n");
    for(int i=0;i<n;i++)
    {
        p[i].p_no=i+1;

        printf("P%d\n",p[i].p_no);
        redo2:
        printf("A.T:");
        scanf("%d",&p[i].arrival);
        if(p[i].arrival<0)
        {
            print();
            goto redo2;
        }
        redo3:
        printf("B.T:");
        scanf("%d",&p[i].burst);
        if(p[i].burst<=0)
        {
            print();
            goto redo3;
        }
    }

    // GIVEN INFORMATION
    printf("\n\nGiven information is:\n");
    printf("\n      Process       Arrival Time        Burst Time\n");
    for(int i=0;i<n;i++)
    {
        printf("\tP%d\t\t%d\t\t    %d\n",p[i].p_no,p[i].arrival,p[i].burst);
    }

    // SORTING PROCESSES ACCORDING TO ARRIVAL TIME
    int temp;
    for(int j=0;j<n-1;j++)
    {
        for(int i=0;i<n-j-1;i++)
        {
            if(p[i].arrival>p[i+1].arrival)
                {
                    //PROCESS ID
                    temp=p[i].p_no;
                    p[i].p_no=p[i+1].p_no;
                    p[i+1].p_no=temp;
                    //ARRIVAL TIME SORT
                    temp=p[i].arrival;
                    p[i].arrival=p[i+1].arrival;
                    p[i+1].arrival=temp;
                    // BURST TIME SORT
                    temp=p[i].burst;
                    p[i].burst=p[i+1].burst;
                    p[i+1].burst=temp;
                }
        }
    }

    // SJF ALGORITHM
    int min,burst_compare=0,x=1;
    for(int i=0;i<n;i++)
    {
        burst_compare=burst_compare+p[i].burst;
        min=p[x].burst;
        for(int j=x;j<n;j++)
        {
            if(p[j].arrival<=burst_compare&&min>p[j].burst)
            {
                temp=p[x].p_no;
                p[x].p_no=p[j].p_no;
                p[j].p_no=temp;
                temp=p[x].arrival;
                p[x].arrival=p[j].arrival;
                p[j].arrival=temp;
                min=p[j].burst;
                temp=p[x].burst;
                p[x].burst=p[j].burst;
                p[j].burst=temp;
            }
        }
        x++;
    }

    // CALCULATION OF START TIME, END TIME AND WAITING TIME
    for(int i=0;i<n;i++)
    {
        if(i==0 || p[i].arrival>p[i-1].end_tym)
        {
            p[i].start_tym=p[i].arrival;
        }
        else
        {
            p[i].start_tym=p[i-1].end_tym;
        }
        p[i].end_tym=p[i].start_tym+p[i].burst;
        p[i].waiting=p[i].start_tym-p[i].arrival;
    }