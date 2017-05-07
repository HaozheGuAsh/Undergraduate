# Haozhe Gu 999200555 & (Your Name)
# ECS 152A Project  Phase II

import simpy
import matplotlib.pyplot as plt
import math
import random
import numpy as np


##Sense the channel every 0.01 msec
N = 10     #Number of Hosts
Lambdas = [0.01,0.05,0.1,0.3,0.6,0.8,0.9]
SIFS = 0.05*0.001
DIFS = 0.1*0.001
T = 100
Trans_Rate = 8/(11*10**6)  #second per byte
### Helper Function ######
def Time_Transmission():
    return random.randint(1,1544)*Trans_Rate

def Time_Backoff(n):
    return random.randint(1,n*T)

class Host(object):
    def __init__(self,env,Index,Lambda):
        self.Length = 0
        self.env = env
        self.Ready = 0
        self.Index = Index
        self.Backoff = Time_Backoff(1)
        self.Length  = 0
        self.Lambda = Lambda
        self.Time_Arrival = round(random.expovariate(self.Lambda),3)

    def Collision(self,Count):
        if(Count>=16):
            #Abort the packet
            self.Length = self.Length-1
            return 1

        else:
            if(Count>10):
                Count=10
            self.Backoff = Time_Backoff(Count)
            self.Ready = 0
            return 0
    def Check_Ready(self):
        #Check Arrival
        if(self.Time_Arrival<=self.env.now):
            self.Length= self.Length+1
            self.Time_Arrival = self.env.now+round(random.expovariate(self.Lambda),3)
        #Count_Down
        if(self.Backoff==0 and self.Length>=1):
            self.Ready = 1;
        elif(self.Backoff>=1 and self.Length>=1):
            self.Backoff = self.Backoff-1
        #else:
            #print("Should not happen")

    def Transfer(self):
        self.Length = self.Length-1
        self.Ready = 0
        self.Backoff = Time_Backoff(1)


class WIFI(object):
    def __init__(self,env,N,Lambda):
        self.env = env
        self.N = N
        self.Hosts = [Host(env,i,Lambda) for i in range(N)]
        self.Busy = 0
        self.Collision_Count = [0 for i in range(self.N)]
        self.action = env.process(self.run())
        self.Total_Packet = 0
        self.Total_Byte = 0
        self.Num_Collision= 0

    def run(self):
        while True:
            Ready_Index = -1
            Ready_Num = 0
            if(self.Busy==0):#IDLE
                for i in range(self.N):
                    self.Hosts[i].Check_Ready()
                    if(self.Hosts[i].Ready == 1):
                        Ready_Num = Ready_Num+1
                        Ready_Index = self.Hosts[i].Index

                if(Ready_Num>1):#CHECK COLLISION
                    for i in range(self.N):
                        if(self.Hosts[i].Ready==1):
                            self.Collision_Count[i] = self.Collision_Count[i]+1
                            status = self.Hosts[i].Collision(self.Collision_Count[i])
                            #return 0 means okey, 1 means abort Packet
                            if(status==1):
                                self.Collision_Count[i] = 0
                                #Add Time needed before ACK now received reveals
                    self.Num_Collision=self.Num_Collision+1
                    Tmp = max([Time_Transmission() for i in range(Ready_Num)])
                    yield self.env.timeout(Tmp)
                if(Ready_Num ==1 and Ready_Index!=-1):#Do Transfer
                    self.Hosts[Ready_Index].Transfer()
                    self.Total_Packet = self.Total_Packet+1
                    Tmp = Time_Transmission()
                    self.Total_Byte = self.Total_Byte+(Tmp/Trans_Rate)+64
                    yield self.env.timeout(Tmp+DIFS+SIFS+64*Trans_Rate)
                    #self.Ack_Num=Ready_Index
                    #self.Waiting=SIFS+self.env.now

            #else:            #BUSY
            yield self.env.timeout(0.001*0.01)




#MAIN
Max_Time = 100
env = simpy.Environment()

wifi = WIFI(env,20,0.9)

env.run(until=Max_Time)
print("Total Packet is: "+str(wifi.Total_Packet))
print("Throughput  is: "+str((8*wifi.Total_Byte)/Max_Time))
print("Total Number of Collision is: "+str(wifi.Num_Collision))
