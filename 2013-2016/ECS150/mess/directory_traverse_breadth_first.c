#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<ftw.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>



/* My QUEUE*/
typedef struct MyQueue
{
	//int capacity;
	int size;
	int front;
	int rear;
	char element[1000][1000];
}MyQueue;
MyQueue* createQueue()
{
	MyQueue *Q;
	Q = (MyQueue *)malloc(sizeof(MyQueue));

	//Q->elements = (char *)malloc(sizeof(char)*maxElements*1000);
	Q->size = 0;
	//Q->capacity = maxElements;
	Q->front = 0;
	Q->rear = -1;
	/* Return the pointer */
	return Q;
}
char* Dequeue(MyQueue *Q)
{
	//char item[1000];
	if (Q->size == 0)
	{
		printf("dequeue a empty queue");
		exit(0);
	}

	else
	{
		Q->size--;
		//strcpy(item, Q->element[Q->front]);
		Q->front++;
		/* As we fill elements in circular fashion
		if (Q->front == Q->capacity)
		{
		Q->front = 0;
		}*/
	}
	return Q->element[(Q->front)-1];
}
char* front(MyQueue *Q)
{
	if (Q->size == 0)
	{
		printf("Queue is Empty\n");
		exit(0);
	}
	/* Return the element which is at the front*/
	return Q->element[Q->front];
}
void Enqueue(MyQueue *Q, char* element)
{
	/* If the Queue is full, we cannot push an element into it as there is no space for it.*/
	if (Q->size ==1000)
	{
		printf("Queue is Full\n");
	}
	else
	{
		Q->size++;
		Q->rear = Q->rear + 1;

		/* Insert the element in its rear side */
		strcpy(Q->element[Q->rear] , element);
	}
	return;
}
int Empty(MyQueue *Q)
{
	//printf("size is %d\n", Q->size);
	if (Q->size == 0)
	{
		
		return 1;
	}
	return 0;
}

int main2()
{
	MyQueue *Q = createQueue();
	Enqueue(Q, "ab");
	Enqueue(Q, "cd");
	Enqueue(Q, "ef");
	Enqueue(Q, "gh");
	printf("Front element is %s\n", front(Q));
	Enqueue(Q, "ash");
	char str[1000];
	strcpy(str,Dequeue(Q));
	printf("dequeue %s\n", str);
	strcpy(str, Dequeue(Q));
	printf("dequeue %s\n", str);
	strcpy(str, Dequeue(Q));
	printf("dequeue %s\n", str);
	strcpy(str, Dequeue(Q));
	printf("dequeue %s\n", str);
	Enqueue(Q, "jaden");
	printf("Front element is %s\n", front(Q));
	strcpy(str, Dequeue(Q));
	printf("dequeue %s\n", str);
	strcpy(str, Dequeue(Q));
	printf("dequeue %s\n", str);
	printf("is empty? %d", Empty(Q));
	
	char str1[100], str2[100];
	strcpy(str1, "/home/ash");
	strcpy(str2, "ash.cpp");
	strcat(str1, "/");
	strcat(str1, str2);
	printf("final path%s\n", str1);
}

int main(int argc, char** argv)
{
	/*Arguments should be argv[0] program name  argv[1] path of directory argv[2] filename*/
	if (argc < 3)
	{
		printf("Invalid parameters\n");
		exit(0);
	}
	
	MyQueue *Q = createQueue();
	char filename[100];
	strcpy(filename, argv[2]);
	Enqueue(Q, argv[1]);
																									//	printf("file name is %s\n", filename);
																									//	printf("path is %s\n", Dequeue(Q));
																									//	Enqueue(Q, argv[2]);
																									//	printf("file name is %s\n", Dequeue(Q));
	while (!(Empty(Q)))
	{
		struct dirent *d;
		DIR *dp;
		char curpath[1024];
		strcpy(curpath, Dequeue(Q));
		/*open directory*/
		if ((dp = opendir(curpath)) == NULL){ printf("unable to open directory\n"); exit(-1); }

		while (d = readdir(dp))
		{
			char filepath[1024];
			strcpy(filepath, curpath);
			strcat(filepath, "/");
			strcat(filepath, d->d_name);
																									//printf("path is %s\n", filepath);
			/*If file is directory*/
			if (d->d_type == DT_DIR & ((strcmp(d->d_name, ".")) != 0 & (strcmp(d->d_name, "..")) != 0))
			{
				printf("%s\n", filepath);
				Enqueue(Q, filepath);
			}
			/*If file is real file*/
			if (d->d_type == DT_REG)
			{
				printf("%s\n", filepath);															//printf("path file%s\n", filepath);

				/*Found file needed  break*/
				//printf("my path is %s   ", curpath);
				//printf("my file is %s\n", d->d_name);
				//if ((strcmp(curpath, argv[1]) == 0)&(strcmp(filename, d->d_name) == 0)){ printf("Found!!"); exit(0); }
				if (strcmp(filename, d->d_name) == 0){ printf("Found!!"); exit(0); }
			}
		}
	}
}




