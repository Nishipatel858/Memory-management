//include header files
#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <time.h>

//Structure to store input data
typedef struct
{
	int np;	//no. of processes
	int nb;	//no.of blocks
	int p[20];	//array of processees size 
	int b[20];	//array of blocks size
} parm;

// The maximum number of threads
#define MAX_THREADS 3

//Nextfit Algorithm Implementation
void *nextfit(void *arg)
{
	time_t start, end;
	start = time(NULL);	//timer starts

	//structure pointer
	parm *p = (parm *) arg;

	int current, i, j;
	int frag[20];	//array to fragmentation


	FILE *f = fopen("nextfit.txt", "w");	//file pointer

	printf("\n enter current position:");
	scanf("%d",&current);	//place where last trasaction occured

	if(f==NULL)	//if condition for file does not exist
	{
		printf("Error");
	}
	else
	{
		printf("**********NEXT FIT************");
		if(current == p->nb)
		{
			printf("\nEnable to Allocate Process");
			fprintf(f, "Enable to Allocate Process");
		}
		else	//file opened successfully
		{
			char *string = "Process No.		Process Size			Block No.			Block Size			Fragmentation";
			fprintf(f, "****Process Allocation****\n\n");
			printf("\nProcess_no\tProcess_size\tBlock_no\tBlock_size\tFragment\n");
			fprintf(f, "%s", string);
			for(i=1; i<=p->np; i++)	//traverse from starting to no. of processes
			{
				for(j=current+1;j<=p->nb;j++)
				{
					if(p->p[i]<=p->b[j])	//if process size is less or equal to the block size then assigning block to that process
					{
						frag[j]=p->b[j]-p->p[i];	//calculating fragmentation
						printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", i, p->p[i], j, p->b[j], frag[j]);
						fprintf(f, "\n%d\t\t\t\t%d\t\t\t\t%d\t\t\t\t%d\t\t\t\t%d", i, p->p[i], j, p->b[j], frag[j]);
						break;
					}
					else		//if no compatible block size available then that process remains unallocated
					{
						printf("\n%d\t\t%d\t\tNot Allocated", i, p->p[i]);
						fprintf(f, "\n%d\t\t\t\t%d\t\t\t\tNot Allocated", i, p->p[i]);
					}
				}
				current=j;
			}
			end = time(NULL);	//timer ends
			fprintf(f, "\n\nExecution Starts at %s", ctime(&start));
			fprintf(f, "\nExecution Ends at %s", ctime(&end));
			fprintf(f, "\nTotal execution time: %f seconds", difftime(end, start));	//finding total execution time
			fclose(f);	//closing file
		}
	}
	printf("\n");
}

//Bestfit Algorithm Implementation
void *bestfit(void *arg)
{
	sleep(10);
	time_t start, end;
	start = time(NULL);	//timer starts

	//structure pointer
	parm *p = (parm *) arg;

	int i,j;
	static int barray[20],parray[20];
	int temp,lowest=9999;
	int fragment[20];	//array to store fragmentation

	FILE *f = fopen("bestfit.txt", "w");	//file pointer

	if(f==NULL)
	{
		printf("Error");
	}
	else	//file opned successfully
	{

		for(i=1;i<=p->np;i++)
		{
			for(j=1;j<=p->nb;j++)
			{
				if(barray[j]!=1)	//checking if block is allocted to any process or not
				{
					temp=p->b[j]-p->p[i];	//calculating  fragmentation
					if(temp>=0)
					{
						if(lowest>temp)	//checking if fragmentation is least or not
						{
							parray[i]=j;	//block with minimum fragmentation
							lowest=temp;
						}
					}
				}
			}

		fragment[i]=lowest;		//storing fragmentation
		barray[parray[i]]=1;	//allocating block to process
		lowest=10000;
		}

		char *string = "Process No.		Process Size			Block No.			Block Size			Fragmentation";
		fprintf(f, "****Process Allocation****\n\n");
		fprintf(f, "%s", string);
		printf("******BEST FIT************");
		printf("\nProcess_no\tProcess_size\tBlock_no\tBlock_size\tFragment");
		for(i=1;i<=p->np;i++)
		{
			if(parray[i]==0)
			{
 				printf("\n%d\t\t%d\t\tNot Allocated", i,p->p[i]);
				fprintf(f, "\n%d\t\t\t\t%d\t\t\t\tNot Allocated", i,p->p[i]);
			}
			else
			{
				printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d",i,p->p[i],parray[i],p->b[parray[i]],fragment[i]);
				fprintf(f, "\n%d\t\t\t\t%d\t\t\t\t%d\t\t\t\t%d\t\t\t\t%d",i,p->p[i],parray[i],p->b[parray[i]],fragment[i]);
			}
		}
		end = time(NULL);	//stopping timer
		fprintf(f, "\n\nExcecution Starts at %s", ctime(&start));
		fprintf(f, "\nExecution Ends at %s", ctime(&end));
		fprintf(f, "\nTotal Execution time: %f seconds", difftime(end, start));	//finding total execution time
		fclose(f);	//closing file
	}
	printf("\n");
}

//Firstfit Algorithm Implemlemetation
void *firstfit(void *arg)
{
	sleep(15);
	time_t start, end;
	start = time(NULL);	//starting timer

	//structure pointer
	parm *p = (parm *) arg;
	int i,j,flags[10], allocation[10];
	int frag[10];	//array to store fragmentation


	/*Add fragmentation*/

	FILE *f = fopen("firstfit.txt", "w");	//file pointer

	if(f==NULL)
	{
		printf("Error!");
	}
	else	//file opened successfully
	{

		for(i = 1; i <= 10; i++)
		{
			flags[i] = 0;
			allocation[i] = -1;
		}
		for(i = 1; i <= p->np; i++)
		{
			for(j = 1; j <= p->nb; j++)
			{
				if(flags[j] == 0 && p->b[j] >= p->p[i])	//checking whether block is allocated or not and block size is greater than process size or not
				{
					allocation[j] = i;	//allocating process to block
					flags[j] = 1;
					frag[j] = p->b[j]-p->p[i];
					break;
				}
			}
		}
		fprintf(f, "****Process Allocation****\n\n");
		char *string = "Block No.		Block Size			Process No.			Process Size			Fragmentation";
		fprintf(f, "%s", string);

		printf("******FIRST FIT************");
		printf("\nBlock no.\tsize\t\tprocess no.\t\tsize\t\tFragment");
		for(i = 1; i <= p->nb; i++)
		{
			printf("\n%d\t\t%d\t\t", i, p->b[i]);
			fprintf(f, "\n%d\t\t\t\t%d\t\t\t\t", i, p->b[i]);
			if(flags[i] == 1)	//checking whether any process in allocated to block or not
			{
				printf("%d\t\t\t%d\t\t%d",allocation[i],p->p[allocation[i]], frag[i]);
				fprintf(f, "%d\t\t\t\t%d\t\t\t\t%d", allocation[i],p->p[allocation[i]], frag[i]);
			}
			else
			{
				printf("Not allocated");
				fprintf(f, "Not Allocated");
			}
		}
		end = time(NULL);	//stoping timer
		fprintf(f, "\n\nExecution Starts at %s", ctime(&start));
		fprintf(f, "\nExecution Ends at %s", ctime(&end));
		fprintf(f, "\nTotal Execution time: %f seconds", difftime(end, start));	//finding total execution time
		fclose(f);	//closing file
	}
}

//main function
int main()
{
	int       i;
	pthread_t threads[3];	//array of thread
	parm      p;	//reference of structure
	int choice;
	char filename[30];
	char ch;
	FILE *f;	//file pointer

	printf("\n\n***********  Welcome to the Memory Management System!  ***********\n");
	printf("\n\n***********  Here we introduce some placement policies!  ***********\n");

	//Choice Menu
	while(1)
	{
		printf("\n\nChoice Menu: ");
		printf("\n1. Manual Input");
		printf("\n2. Input from a file");
		printf("\n3. Apply Memory Management Algorithms on Input data");
		printf("\n4. Generate New Input File from given data");
		printf("\n0. Exit");
		printf("\n\nEnter Your Choice: ");
		scanf("%d", &choice);

		switch(choice)
		{
			case 0:	//Exit
				return(0);

			case 1:	//Taking data from user (Manual Data)
				printf("\nEnter the number of blocks:");
				scanf("%d",&p.nb);
				printf("Enter the number of processes:");
				scanf("%d",&p.np);

				printf("\nEnter the size of the blocks:-\n");
				for(i=1;i<=p.nb;i++)
				{
					printf("Block no.%d:",i);
					scanf("%d",&p.b[i]);
				}

				printf("\nEnter the size of the processes :-\n");
				for(i=1;i<=p.np;i++)
				{
					printf("Process no.%d:",i);
					scanf("%d",&p.p[i]);
				}
			break;

			case 2:	//Taking data from file
				printf("Enter file name: ");
				scanf("%s", filename);

				f = fopen(filename, "r");
				if(f==NULL)
				{
					printf("Error Opening File!");
				}
				else	//file opned successfully
				{
					ch=getc(f);
					p.nb=ch-'0';	//converting character into integer

					//Displaying data of file 
					printf("\nNo. of Blocks: %d",p.nb);
					printf("%c",getc(f));

					for(ch=getc(f),i=1;ch!='\n';ch=getc(f))
					{
						if(ch!='\t')
						{
							p.b[i]=ch-'0';
							printf("Block[%d] size: %d", i, p.b[i]);
							printf("\n");
							i++;
						}
					}
					
					ch=getc(f);
					p.np=ch-'0';

					printf("\nNo. of Processes: %d\n",p.np);
					getc(f);
					for(ch=getc(f),i=1;ch!='\n';ch=getc(f))
					{
						if(ch!='\t')
						{
							p.p[i]=ch-'0';
							printf("Process[%d] size: %d", i, p.p[i]);
							printf("\n");
							i++;
						}
					}
					fclose(f);	//closing file

				}
			break;

			case 3:	/*Implementation of algorithms*/

				//Implementation of algorithm using thread
				printf("The process is generating %d threads to implement algorithm.\n", MAX_THREADS);

				//Generating threads
				pthread_create(&threads[0], NULL, nextfit, (void *)&p);
				pthread_create(&threads[1], NULL, bestfit, (void *)&p);
				pthread_create(&threads[2], NULL, firstfit, (void *)&p);

				//Synchronization of threads
				for (i = 0; i < MAX_THREADS; i++)
				{
					pthread_join(threads[i], NULL);
				}
			break;

			case 4:	//Storing input data in new file
				printf("\nEnter file name: ");
				scanf("%s",filename);

				f = fopen(filename, "w");

				if(f==NULL)
				{
					printf("Error Opening File!");
				}
				else		//file opened successfully (FILE STRUCTRE)
				{
					/*
					FILE STRUCTURE
					Line 1:	No. of blocks
					Line 2:	Size of each block
					Line 3:	No. of processes
					Line 4:	Size of each process
					*/

					fprintf(f, "%d", p.nb);
					fprintf(f, "\n");

					for(i=1; i<=p.nb; i++)
					{
						fprintf(f, "%d	", p.b[i]);
					}
					fprintf(f, "\n");
					fprintf(f, "%d", p.np);
					fprintf(f, "\n");

					for(i=1; i<=p.np; i++)
					{
						fprintf(f, "%d	", p.p[i]);
					}
					fclose(f);	//closing file
					printf("\nInput data entered successfully into file!!!\n");
				}

			break;

			default:
				printf("\nInvalid Choice");
			break;
		}
	}
}
