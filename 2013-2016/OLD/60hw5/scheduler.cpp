#include "scheduler.h"
#include<stdio.h>
#include<iostream>
#include"QueueAr.h"
#include<cmath>
using namespace std;

Scheduler::Scheduler(int numJobs, int numWorkers, Job *jobs, int numPeople)
{
	numberjobs = numJobs;
	numberworkers = numWorkers;
	numberpeople = numPeople;
    copyjob(numJobs,jobs);
    toposort(numJobs);
	jobs2 = jobs;
/*	for (int i =0; i < numberjobs; i++)
	{
		cout<<"  "<<sortjob[i].ID;
	}
	cout << endl;
	for (int i = 0; i < numberjobs; i++)
	{
		cout << "  " << sortjob[i].indegree2;
	}
	for (int i = 0; i < 2000; i++)
	{
		for (int j = 0; j < 2500; j++)
		{
			time[i].people[j] = 0;
		}
		time[i].numfinish = 0;
	}
	*/
	int currentjob = 0;
	for (int current=0; current<2000; current++)
	{
		if (time[current].numfinish > 0)
		{
			for (int i = 0; i < time[current].numfinish; i++)
			{
				for (int k = 0; k < sortjob[time[current].finishjob[i]].numDependencies; k++)
				{
					//cout << "dependency" << sortjob[time[current].finishjob[i]].dependencies[k];
					//cout << " " << myjob[sortjob[time[current].finishjob[i]].dependencies[k]].order;
					sortjob[myjob[sortjob[time[current].finishjob[i]].dependencies[k]].order ].indegree2--;
					//cout << "set indegree " << sortjob[myjob[sortjob[time[current].finishjob[i]].dependencies[k]].order].ID;
				//	cout << "  " << sortjob[myjob[sortjob[time[current].finishjob[i]].dependencies[k]].order].indegree2<<endl;
					
				}
			}
		}//set indegree for sortjob after one job finish
		
	//	cout << "people " << curpeople(current, numberpeople) << "current " << current << "current job "<<currentjob<<"with indegree " 
	//		<< sortjob[currentjob].ID << "  " << sortjob[currentjob].indegree2<<endl;
		while (curpeople(current, numberpeople) >= numberworkers  && currentjob<=numberjobs  &&  sortjob[currentjob].indegree2 == 0 )
		{
			sortjob[currentjob].begin = 1;
			sortjob[currentjob].startTime = current;
			sortjob[currentjob].numPeopleUsed = numberworkers;
			sortjob[currentjob].duration =  ceil(sortjob[currentjob].length / double(sortjob[currentjob].numPeopleUsed));
			sortjob[currentjob].finishTime = sortjob[currentjob].startTime + sortjob[currentjob].duration;
			//set basic job info

			int count = 0;
			for (int i = 0; i < numberpeople; i++)
			{
				if (time[current].people[i] == 0 && count<numberworkers)
				{
					sortjob[currentjob].peopleIDs[count] = i;
					count++;
				}
			}//set job people array

			for (int j = current; j <= current + sortjob[currentjob].duration; j++)
			{
				for (int i = 0; i < sortjob[currentjob].numPeopleUsed; i++)
				{
					time[j].people[sortjob[currentjob].peopleIDs[i]] = 1;
				}
			}//set time people array

			time[current + sortjob[currentjob].duration].finishjob[time[current + sortjob[currentjob].duration].numfinish] = currentjob;
			time[current + sortjob[currentjob].duration].numfinish++;
		//	cout << "ok set job " << sortjob[currentjob].ID << "duration" << sortjob[currentjob].duration<<endl;
			currentjob++;
		}//assign people to available job, update job infomation and the time array

		if (curpeople(current, numberpeople) == numberpeople)
		{
		//	cout << "end!!!!!!!!";
			break;
		}//when after assigning job, still all people available, all job should finished
	}
  
} // Scheduler()


void Scheduler::run()
{
/*	sortjob[0].startTime = 0;
	for (int i = 0; i < numberjobs; i++)
	{
		if (i != 0)
		{
			sortjob[i].startTime = sortjob[i - 1].finishTime;
		}
		sortjob[i].numPeopleUsed = 1;
		sortjob[i].peopleIDs[0] = 0;
		sortjob[i].finishTime = sortjob[i].startTime + int( sortjob[i].length / sortjob[i].numPeopleUsed);
*/		

	for (int i = 0; i < numberjobs;i++)
   {
		(jobs2 + sortjob[i].ID)->numPeopleUsed = sortjob[i].numPeopleUsed;
		(jobs2 + sortjob[i].ID)->finishTime = sortjob[i].finishTime;
		for (int j = 0; j < sortjob[i].numPeopleUsed; j++)
		{
			(jobs2 + sortjob[i].ID)->peopleIDs[j] = sortjob[i].peopleIDs[j];

		}
		(jobs2 + sortjob[i].ID)->startTime = sortjob[i].startTime;

	}
} // run()

void Scheduler::toposort(int numJobs)
{
	Queue<job2> queue(5000);
	int count = 0;

	queue.makeEmpty();
	for (int i = 0; i < numJobs; i++)
	{
		if (myjob[i].indegree == 0)
		{
			queue.enqueue(myjob[i]);
			//cout << "start job" << i << endl;

		}

		while (!queue.isEmpty())
		{
			job2 job = queue.dequeue();
			sortjob[count] = job;
			if (count < numberjobs){ myjob[job.ID].order = count; }
			count++;
		//	cout << "dequeue" <<job.ID<< endl;

			for (int k = 0; k < job.numDependencies; k++)
			{   
				myjob[*(job.dependencies + k)].indegree--;
				if (myjob[*(job.dependencies + k)].indegree == 0)
				{
					queue.enqueue(myjob[*(job.dependencies + k)]);
		//			cout << "enqueue  " << k << endl;
				}
			}
		}

		
	}
	

}
int Scheduler::curpeople(int i,int numpeople)
{
	int count = 0;
	for (int l = 0; l < numpeople; l++)
	{
		if (time[i].people[l] == 0)
		{
			count++;
		}
	}
	return count;
}
void Scheduler::copyjob(int numJobs,Job *Jobs)
{ 
   // cout<<"enter copy"<<endl;
	job2 job;
  for(int i =0;i<numJobs;i++)
  {
	  job.length = (Jobs + i)->length;
	  job.numDependencies = (Jobs + i)->numDependencies;
	//  job.startTime = (Jobs + i)->startTime;
	 // job.finishTime = (Jobs + i)->finishTime;
	 // job.numPeopleUsed = (Jobs + i)->numPeopleUsed;
	  job.dependencies = (Jobs + i)->dependencies;
	 // job.peopleIDs = (Jobs + i)->peopleIDs;
	  job.indegree = 0;
	  job.indegree2 = 0;
	  job.ID = i;
	  job.begin = 0;
	 // job.finish = 0;
	  myjob[i] = job;
    //  cout<<"job"<<i<<"assigned"<<endl;
  }
  for (int i = 0; i != numJobs; i++)
  {
	  if (myjob[i].numDependencies > 0)
	  {
		  for (int k = 0; k < myjob[i].numDependencies; k++)
		  {
			  myjob[*(myjob[i].dependencies + k)].prerequist[k] = i;
			  myjob[*(myjob[i].dependencies + k)].indegree++;
			  myjob[*(myjob[i].dependencies + k)].indegree2++;
			//  cout << "job" << *(myjob[i].dependencies + k) << "has prerequist" << i << endl;
		  }
	  }
  }
}
