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
Time_Out = [5*0.001,10*0.001,15*0.001]
Trans_Rate = 8/(11*10**6)  #second per byte
### Helper Function ######
def Time_Transmission():
    return random.randint(1,1544)*Trans_Rate

def Time_Backoff(n):
    return random.randint(1,n*T)

class Packet(object):
    def __init__(self,env,From,To,Collision,ACK):
        self.env = env
        self.Start_Time = self.env.now
        self.Collision = 0
        self.From = From #Which Host create this Packet
        self.To = random.randint(1,N-1) #Randomly send
        if(ACK==1):#Specify ACK Receiver
            self.To =To
        self.Type = ACK  # 1 for ACK Packet
        if(self.Type==0): # Normal Packet
            self.Size = random.randint(1,1544)
        else: # ACK
            self.Size = 64

class Host(object):
    def __init__(self,env,ID,Lambda):
        self.env = env
        self.queue = list()
        self.Ready = 0
        self.ID = ID
        self.ACKed = 0
        self.Waiting_ACK = 0
        self.Failed_ACK = 0
        self.Host_ACK_Timeout = 0
        self.Backoff = Time_Backoff(1)
        self.Lambda = Lambda
        self.Time_Arrival = round(random.expovariate(self.Lambda),3)

    def Check_Ready(self):
        #Check Arrival
        if(self.Time_Arrival<=self.env.now):
            self.queue.insert(0,Packet(self.env,self.ID,-1,0,0))#-1, Normal PKT will Overwrite
            self.Time_Arrival = self.env.now+round(random.expovariate(self.Lambda),3)

        #Waiting for ACK, Stop Transmitting
        if(self.Waiting_ACK==1):
            if(self.Host_ACK_Timeout>self.env.now):
                #Time_Out for ACK
                self.Failed_ACK=self.Failed_ACK+1
                self.Backoff =Time_Backoff(self.Failed_ACK)
                self.Waiting_ACK =0
                self.queue[len(self.queue)-1].Collision = 0 #Reset collision
                Num_Timeout = Num_Timeout+1
            elif(self.Failed_ACK>=3):
                #Abort Packet
                self.queue.pop()
                self.Backoff = Time_Backoff(1)
            elif(self.ACKed==1):
                #Got ACK in Time
                tmp = self.queue.pop()
                self.Backoff = Time_Backoff(1)
                Total_Packet = Total_Packet+1
                Total_Byte = Total_Byte+tmp.size+64
                Total_Delay = self.env.now - tmp.start_time

        else: #Not Waiting for ACK
            #Count_Down
            if(self.Backoff==0 and len(self.queue)>=1):
                self.Ready = 1;
            elif(self.Backoff>=1 and len(self.queue)>=1):
                self.Backoff = self.Backoff-1
            #else:
                #print("Should not happen")

    def Collision(self):
        Num_Collision = Num_Collision+1
        self.queue[len(self.queue)-1].Collision = 1

    def Transfer(self,Hosts):
        PKT = self.queue[len(self.queue)-1]
        Receiver = Hosts[PKT.To]
        if(PKT.Type==0):# Normal PKT
            self.Waiting_ACK=1
            yield self.env.timeout(DIFS+Trans_Rate*PKT.Size)
            if(PKT.Collision==0):#No Collision
                Receiver.queue.insert(0,Packet(self.env,Receiver.ID,self.ID,0,1))
            else:#Collision
                Receiver.queue.insert(0,Packet(self.env,Receiver.ID,self.ID,1,1))
        else: # ACK PKT
            if(PKT.Collision==0)
            #ONLY Send ACK if no Collision
            # Collision at sender make Data.Collision==1 and ACK.Collision==1
            # Collision at Receiver(ACK) also make ACK.Collision ==1
                Receiver.ACKed=1
                yield self.env.timeout(SIFS+Trans_Rate*64)


class WIFI(object):
    def __init__(self,env,N,Lambda):
        self.env = env
        self.N = N
        self.Hosts = [Host(env,i,Lambda) for i in range(N)]
        self.Busy = 0
        #self.Collision_Count = [0 for i in range(self.N)]
        self.action = env.process(self.run())


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
                            self.Hosts[i].Collision()
                            self.self.Hosts[i].Transfer(Hosts)
                            # Collision solved via ACK

                if(Ready_Num ==1 and Ready_Index!=-1):#Do Transfer
                    self.Hosts[Ready_Index].Transfer()
                    #yield self.env.timeout(Tmp+DIFS+SIFS+64*Trans_Rate)
                    #self.Ack_Num=Ready_Index
                    #self.Waiting=SIFS+self.env.now

            #else:            #BUSY
            yield self.env.timeout(0.001*0.01)


#MAIN
Max_Time = 20
N = 10
env = simpy.Environment()
ACK_Timeout = Time_Out[1]
Total_Packet = 0
Total_Byte = 0
Num_Collision= 0
Num_Timeout = 0
Total_Delay = 0

wifi = WIFI(env,N,0.9)

env.run(until=Max_Time)
