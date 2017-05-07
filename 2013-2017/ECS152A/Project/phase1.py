# Haozhe Gu 999200555
# ECS 152A Project I Phase I

import simpy
import matplotlib.pyplot as plt
import math
import random
import numpy as np
Lambda = [0.1,0.25,0.4,0.55,0.65,0.80,0.90]
Mu = 1
Max_Buffer = [1,20,50]
Max_Time = 100000

##def Negative_Exponentially_Distributed_Time( rate)

print("---------------Starting Phase I---------------\n")

class Global_Event_list(object):
    def __init__(self,env,Lambda,Mu,Max_Buffer,mode):
        self.env = env
        self.Lambda = Lambda
        self.Packet_Loss = 0
        self.Total_Packet = 0
        self.Sum_Queue_Length = 0
        self.mode = mode
        self.Queue = Queue(self.env,Mu,Max_Buffer)
        # Start the run process everytime an instance is created.
        self.action = env.process(self.run())

    def run(self):
        while True:

            if(self.Total_Packet!=0):
                self.Sum_Queue_Length = self.Sum_Queue_Length+self.Queue.Length
            self.Total_Packet = self.Total_Packet+1

            if(self.Queue.Length < self.Queue.Capacity):
                self.Queue.Length = self.Queue.Length +1
            else:
                self.Packet_Loss = self.Packet_Loss+1

            if(self.mode==1):
                Time = random.expovariate(self.Lambda)
            else:
                Time = np.random.pareto(self.Lambda)

            yield env.timeout(Time)

class Queue(object):
    def __init__(self,env,Mu,Max_Buffer):
        self.env = env
        self.Capacity = Max_Buffer
        self.Length = 0
        self.Mu = Mu
        self.action = env.process(self.run())

    def run(self):
        while True:
            if (self.Length>0): #Service the first Packet in the Queue
                self.Length = self.Length-1
                Time = random.expovariate(self.Mu)
                yield env.timeout(Time)
            else: #IDLE,No Packet,Let the time run
                yield env.timeout(1)



#MAIN
#PART1
j=100000
Utilization = []
Mean_Queue_Length=[]
Number_Packet_Dropped=[]
for i in Lambda:
    env = simpy.Environment()
    Test = Global_Event_list(env,i,Mu,j,0)
    env.run(until=Max_Time)
    Utilization.append(Test.Total_Packet/Max_Time)
    Mean_Queue_Length.append(Test.Sum_Queue_Length/Test.Total_Packet)
    Number_Packet_Dropped.append(Test.Packet_Loss/Test.Total_Packet)
    print("Lambda is: "+str(i)+"Max_Buffer: "+str(j)+"\n")
    print("Mean_Queue_Length: "+str(Test.Sum_Queue_Length/Test.Total_Packet)+"\n")
    print("Total Package Loss: "+str(Test.Packet_Loss)+"\n")
    print("Utilization: "+str(Test.Total_Packet/Max_Time)+"\n-------------------------------------------------\n")
fig = plt.figure()
plt.plot(Lambda,Utilization)
plt.xlabel("Arrival Rate Lambda (Packets/Second)")
plt.ylabel("Utilization")
plt.title("Utilization VS Arrival Rate When Max_Buffer="+str(j))
plt.savefig("Utilization_Max_Buffer="+str(j)+ ".png")

fig = plt.figure()
plt.plot(Lambda,Mean_Queue_Length)
plt.xlabel("Arrival Rate Lambda (Packets/Second)")
plt.ylabel("Mean_Queue_Length")
plt.title("Mean_Queue_Length VS Arrival Rate When Max_Buffer="+str(j))
plt.savefig("Mean_Queue_Length_Max_Buffer="+str(j)+ ".png")

fig = plt.figure()
plt.plot(Lambda,Number_Packet_Dropped)
plt.xlabel("Arrival Rate Lambda (Packets/Second)")
plt.ylabel("Number_Packet_Dropped Probability")
plt.title("Number_Packet_Dropped Probability VS Arrival Rate When Max_Buffer ="+str(j))
plt.savefig("Number_Packet_Dropped_Max_Buffer="+str(j)+ ".png")


#Part2
Lambda1 = [0.2,0.4,0.6,0.8,0.9]
j=1
Utilization1 = []
Mean_Queue_Length1=[]
Number_Packet_Dropped1=[]
for i in Lambda1:
    env = simpy.Environment()
    Test = Global_Event_list(env,i,Mu,j,0)
    env.run(until=Max_Time)
    Utilization1.append(Test.Total_Packet/Max_Time)
    Mean_Queue_Length1.append(Test.Sum_Queue_Length/Test.Total_Packet)
    Number_Packet_Dropped1.append(Test.Packet_Loss/Test.Total_Packet)
    print("Lambda is: "+str(i)+"Max_Buffer: "+str(j)+"\n")
    print("Mean_Queue_Length: "+str(Test.Sum_Queue_Length/Test.Total_Packet)+"\n")
    print("Total Package Loss: "+str(Test.Packet_Loss)+"\n")
    print("Utilization: "+str(Test.Total_Packet/Max_Time)+"\n-------------------------------------------------\n")
j=20
Utilization2 = []
Mean_Queue_Length2=[]
Number_Packet_Dropped2=[]
for i in Lambda1:
    env = simpy.Environment()
    Test = Global_Event_list(env,i,Mu,j,0)
    env.run(until=Max_Time)
    Utilization2.append(Test.Total_Packet/Max_Time)
    Mean_Queue_Length2.append(Test.Sum_Queue_Length/Test.Total_Packet)
    Number_Packet_Dropped2.append(Test.Packet_Loss/Test.Total_Packet)
    print("Lambda is: "+str(i)+"Max_Buffer: "+str(j)+"\n")
    print("Mean_Queue_Length: "+str(Test.Sum_Queue_Length/Test.Total_Packet)+"\n")
    print("Total Package Loss: "+str(Test.Packet_Loss)+"\n")
    print("Utilization: "+str(Test.Total_Packet/Max_Time)+"\n-------------------------------------------------\n")
j=50
Utilization3 = []
Mean_Queue_Length3=[]
Number_Packet_Dropped3=[]
for i in Lambda1:
    env = simpy.Environment()
    Test = Global_Event_list(env,i,Mu,j,0)
    env.run(until=Max_Time)
    Utilization3.append(Test.Total_Packet/Max_Time)
    Mean_Queue_Length3.append(Test.Sum_Queue_Length/Test.Total_Packet)
    Number_Packet_Dropped3.append(Test.Packet_Loss/Test.Total_Packet)
    print("Lambda is: "+str(i)+"Max_Buffer: "+str(j)+"\n")
    print("Mean_Queue_Length: "+str(Test.Sum_Queue_Length/Test.Total_Packet)+"\n")
    print("Total Package Loss: "+str(Test.Packet_Loss)+"\n")
    print("Utilization: "+str(Test.Total_Packet/Max_Time)+"\n-------------------------------------------------\n")
print(Utilization1)
print(Utilization2)
print(Utilization3)
fig = plt.figure()
line1 = plt.plot(Lambda1,Utilization1,'bo-',label = "Max_Buffer= 1")
line2 = plt.plot(Lambda1,Utilization2,'go-',label = "Max_Buffer= 20")
line3 = plt.plot(Lambda1,Utilization3,'ro-',label = "Max_Buffer= 50")
lines = line1+line2+line3
labels = [l.get_label() for l in lines]
plt.legend(labels,loc='upper left')
plt.xlabel("Arrival Rate Lambda (Packets/Second)")
plt.ylabel("Utilization")
plt.title("Utilization VS Arrival Rate When Max_Buffer")
plt.savefig("Utilization_Max_Buffer.png")

fig = plt.figure()
line1 = plt.plot(Lambda1,Mean_Queue_Length1,'bo-',label = "Max_Buffer= 1")
line2 = plt.plot(Lambda1,Mean_Queue_Length2,'go-',label = "Max_Buffer= 20")
line3 = plt.plot(Lambda1,Mean_Queue_Length3,'ro-',label = "Max_Buffer= 50")
lines = line1+line2+line3
labels = [l.get_label() for l in lines]
plt.legend(labels,loc='upper left')
#plt.plot(Lambda,Mean_Queue_Length)
plt.xlabel("Arrival Rate Lambda (Packets/Second)")
plt.ylabel("Mean_Queue_Length")
plt.title("Mean_Queue_Length VS Arrival Rate When Max_Buffer")
plt.savefig("Mean_Queue_Length_Max_Buffer.png")

fig = plt.figure()
line1 = plt.plot(Lambda1,Number_Packet_Dropped1,'bo-',label = "Max_Buffer= 1")
line2 = plt.plot(Lambda1,Number_Packet_Dropped2,'go-',label = "Max_Buffer= 20")
line3 = plt.plot(Lambda1,Number_Packet_Dropped3,'ro-',label = "Max_Buffer= 50")
lines = line1+line2+line3
labels = [l.get_label() for l in lines]
plt.legend(labels,loc='upper left')
#plt.plot(Lambda,Number_Packet_Dropped)
plt.xlabel("Arrival Rate Lambda (Packets/Second)")
plt.ylabel("Number_Packet_Dropped Probability")
plt.title("Number_Packet_Dropped Probability VS Arrival Rate When Max_Buffer ")
plt.savefig("Number_Packet_Dropped_Max_Buffer.png")
