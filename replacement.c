
//include header files

#include <stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <time.h>

//Structure of input data from user
typedef struct
{
	int total_frames;	//total no. of frames
	int total_pages;	//total no. of pages
	int pages[25];	//values of reference string
} parm;

//The maximum number of threads
#define MAX_THREADS 3

//Least Frequently Used Algorithm Implementation
void *LFU(void *arg)
{
	time_t start, end;
	start = time(NULL);	//timer starts
	parm *p = (parm *) arg;		//structure pointer

	int hit = 0;
	int frame[10], arr[25], ti[25];
	int m, n, page, flag, k, minimum_time, temp;


	FILE *f = fopen("LFU.txt", "w");	//open file for writing output
	if(f==NULL)	//if condition for file does not exist
	{
		printf("Error");
	}
	else
	{
		printf("\n*************LFU****************\n");
		fprintf(f,"\n*************LFU****************\n");

		for(m = 0; m < p->total_frames; m++)
		{
			frame[m] = -1;	//initially -1 is assigned to all frames
	 	}
 		for(m = 0; m < 25; m++)
 		{
       		arr[m] = 0;
 		}

		for(m = 0; m < p->total_pages; m++)	//traverse from starting to total no. of pages
 		{
			arr[p->pages[m]]++;
			ti[p->pages[m]] = m;
			flag = 1;
			k = frame[0];

			for(n = 0; n < p->total_frames; n++)	//traverse from strating to total no. of frames
			{
				if(frame[n] == -1 || frame[n] == p->pages[m])
				{
				    if(frame[n] != -1)	//if particular frame is not empty then increment hit
				    {
						hit++;
				    }
				    flag = 0;
				    frame[n] = p->pages[m];
				    break;
				}
				if(arr[k] > arr[frame[n]])
				{
				k = frame[n];
			}
		}
		if(flag)
		{
			minimum_time = 25;
			for(n = 0; n < p->total_frames; n++)
			{
				if(arr[frame[n]] == arr[k] && ti[frame[n]] < minimum_time)
				{
					temp = n;
					minimum_time = ti[frame[n]];
				}
			}
			arr[frame[temp]] = 0;
			frame[temp] = p->pages[m];
		}
		for(n = 0; n < p->total_frames; n++)	//traverse from starting to total no. of frames
		{
			printf("%d\t", frame[n]);
			fprintf(f, "%d\t", frame[n]);
		}
		printf("\n");
		fprintf(f, "\n");
        }
	printf("The No Of Page Faults:\t%d\n", ((p->total_pages)-(hit)-(p->total_frames)));	//calculate Page Fault
	fprintf(f, "The No Of Page Faults:\t%d", ((p->total_pages)-(hit)-(p->total_frames)));
	printf("\n");
	}
	end = time(NULL);	//timer ends
	fprintf(f, "\n\nExecution Starts at %s", ctime(&start));
	fprintf(f, "\nExecution Ends at %s", ctime(&end));
	fprintf(f, "\nTotal execution time: %f seconds", difftime(end, start));	//finding total execution time
	fclose(f);	//close file for writing output
}

//Least Recently Used Algorithm Implementation
void *LRU(void *arg)
{

	sleep(10);
	time_t start, end;
	start = time(NULL);	//timer starts
	parm *p = (parm *) arg;	//structure pointer

	int q[25],c=0,c1,d,i,j,k=0,r,t,b[20],c2[20], m;


	for(m = 0; m < p->total_frames; m++)
	{
	       q[m] = -1;	//initially -1 is assigned to all frames
	}

	FILE *f = fopen("LRU.txt", "w");	//open file for writing output

	printf("\n\n*************LRU****************\n");
	fprintf(f,"\n*************LRU****************\n");
	q[k]=p->pages[k];
	printf("\n\t%d\n",q[k]);
	fprintf(f, "\n\t%d\n", q[k]);
	c++;
	k++;

	for(i=1;i<p->total_pages;i++)	//traverse from starting to total no. of pages
	{
		c1=0;
		for(j=0;j<p->total_frames;j++)	//traverse from strating to total no. of frames
		{
			 if(p->pages[i]!=q[j])
				 c1++;
		}
		if(c1==p->total_frames)
		{
			c++;
			if(k<p->total_frames)	//there is atleast one place that is empty
			{
				q[k]=p->pages[i];
				k++;
				for(j=0;j<k;j++)
				{
					printf("\t%d",q[j]);
					fprintf(f, "\t%d", q[j]);
				}
				printf("\n");
				fprintf(f, "\n");
			}
			else	//all frames are allocated, means no space to allocate one more reference
			{
				for(r=0;r<p->total_frames;r++)	//traverse from strating to total no. of frames
				{
					c2[r]=0;
					for(j=i-1;j<p->total_pages;j--)
					{
						if(q[r]!=p->pages[j])
						{
							c2[r]++;
						}
						else
						{
							break;
						}
					}
				}
				for(r=0;r<p->total_frames;r++)	//traverse from strating to total no. of frames
					b[r]=c2[r];
				for(r=0;r<p->total_frames;r++)	//traverse from strating to total no. of frames
				{
					for(j=r;j<p->total_frames;j++)
					{
						if(b[r]<b[j])
						{
							t=b[r];
							b[r]=b[j];
							b[j]=t;
						}
					}
				}
				for(r=0;r<p->total_frames;r++)	//traverse from strating to total no. of frames
				{
					if(c2[r]==b[0])
					{
						q[r]=p->pages[i];
					}
					printf("\t%d",q[r]);
					fprintf(f, "\t%d", q[r]);
				}
				printf("\n");
				fprintf(f, "\n");
			}
		}
	}
	printf("\nThe No Of Page Faults:%d",c-p->total_frames);	//calculate Page Faults
	fprintf(f, "\nThe No Of Page Faults:%d", c-p->total_frames);
	printf("\n");
	end = time(NULL);	//timer ends
	fprintf(f, "\n\nExecution Starts at %s", ctime(&start));
	fprintf(f, "\nExecution Ends at %s", ctime(&end));
	fprintf(f, "\nTotal execution time: %f seconds", difftime(end, start));	//finding total execution time
	fclose(f);	//close file for writing
}

//First In First Out Algorithm Implementation
void *FIFO(void *arg)
{
	sleep(5);
	time_t start, end;
	start = time(NULL);	//timer starts
	parm *p = (parm *) arg;	//structure pointer
	int i,j,frame[25],k,avail,count=0;

	FILE *f= fopen("FIFO.txt", "w");	//open file for writing output


	printf("\n***********FIFO************\n");
	fprintf(f,"\n***********FIFO************\n");
	for(i=0;i<p->total_frames;i++)
		frame[i]= -1;	//initially -1 is assigned to all frames
	j=0;
	for(i=0;i<p->total_pages;i++)	//traverse from starting to total no. of pages
	{
		avail=0;
		for(k=0;k<p->total_frames;k++)	//traverse from starting to total no. of frames
		{
			if(frame[k]==p->pages[i])	//if atleast one frame is empty
			{
				avail=1;
			}
		}
		if (avail==0)	//if all frames are allocated
		{
			frame[j]=p->pages[i];
			j=(j+1)%p->total_frames;
			count++;
			for(k=0;k<p->total_frames;k++)
			{
				printf("%d\t",frame[k]);
				fprintf(f, "%d\t",frame[k]);
			}
		}
		printf("\n");
		fprintf(f,"\n");
	}
	printf("The No Of Page Faults: %d",count-(p->total_frames));	//calculate Page Fault
	fprintf(f, "The No Of Page Faults: %d",count-(p->total_frames));
	end = time(NULL);	//timer ends
	fprintf(f, "\n\nExecution Starts at %s", ctime(&start));
	fprintf(f, "\nExecution Ends at %s", ctime(&end));
	fprintf(f, "\nTotal execution time: %f seconds", difftime(end, start));	//finding total execution time
	fclose(f);	//close file for writing
}

//main function
int main() {
	int       i;
	pthread_t threads[3];	//array of thread
	parm      p;	//reference of structure

	int total_frames, total_pages, hit = 0;
	int pages[25];
	int m;
    	int choice;
	char filename[30];
	char ch;
	FILE *f;	//file pointer

	printf("\n\n***********  Welcome to the Memory Management System!  ***********\n");
	printf("\n\n***********  Here we introduce some replacement policies!  ***********\n");

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
				printf("Enter Total Number of Pages:\t");
				scanf("%d", &p.total_pages);
				printf("Enter Total Number of Frames:\t");
				scanf("%d", &p.total_frames);

				printf("Enter Values of Reference String\n");
				for(m = 0; m < p.total_pages; m++)
				{
				    printf("Enter Value No.[%d]:\t", m + 1);
				    scanf("%d", &p.pages[m]);
				}
				printf("\n");

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
					p.total_pages=ch-'0';	//converting character into integer

					//Displaying data of file 
					printf("\nNo. of Pages: %d",p.total_pages);
					printf("%c",getc(f));

					ch=getc(f);
					p.total_frames=ch-'0';

					printf("\nNo. of References: %d\n",p.total_frames);
					printf("%c",getc(f));

					for(ch=getc(f),i=0;ch!='\n';ch=getc(f))
					{
						if(ch!='\t')
						{
							p.pages[i]=ch-'0';
							printf("Reference value[%d]: %d", i, p.pages[i]);
							printf("\n");
							i++;
						}
					}
					fclose(f);	//closing file

				}
			break;

			case 3:	/*Implementation of algorithms*/

				//Implementation of algorithm using thread
				printf("The process is generating %d threads.\n", MAX_THREADS);

				//Generating threads
				pthread_create(&threads[0], NULL, LFU, (void *)&p);
				pthread_create(&threads[1], NULL, FIFO, (void *)&p);
				pthread_create(&threads[2], NULL, LRU, (void *)&p);

				/* Synchronize the completion of each thread.   */
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
					Line 1: No. of Pages
					Line 2:	No. of Frames
					Line 3:	Reference values
					*/

					fprintf(f, "%d", p.total_pages);
					fprintf(f, "\n");
                    			fprintf(f, "%d", p.total_frames);
					fprintf(f, "\n");
					for(i=0; i<p.total_pages; i++)
					{
						fprintf(f, "%d	", p.pages[i]);
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
