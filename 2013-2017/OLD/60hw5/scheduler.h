#ifndef schedulerH
#define schedulerH

#include "ProjectRunner.h"
#include<stdio.h>

class Scheduler
{
public:
	class job2 :public Job
	{
	public:
		short length;
		short numDependencies;
		int startTime;
		int finishTime;
		short numPeopleUsed;
		int* dependencies;
		short peopleIDs[50];

		//start addon
		short indegree;
		short indegree2;
		int prerequist[50];
		int order;
		//bool finish;
		int ID;
		int duration;
		bool begin ;
		//int lastesttime;
	};//class myjob


class Time
	{
	public:
		bool people[3000];
		int finishjob[100];
		int numfinish;
		bool finish;
	};
  Scheduler(int numJobs, int numWorkers, Job *jobs, int numPeople);
  void run();
  void copyjob(int numJobs, Job *Jobs);
  void toposort(int numJobs);
  int curpeople(int i, int numpeople);

  int numberjobs;
  int numberworkers;
  int numberpeople;
  job2 myjob[8000];
  job2 sortjob[8000];
  Job *jobs2;
  Time time[2000];
}; // class Scheduler



#endif