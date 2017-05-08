
#Question 1, 3 arguments (Probability of 00; Probability of 10; length of sequence), it return vector of the sequence
Q1<-function(p00,p10,number)
{
  p01 = 1-p00
  p11 = 1-p10
  ary<-sample(c(0,1),size = 1,replace = TRUE, prob = c(0.5,0.5))
  
  for(x in 2:number)
  {
    if(ary[length(ary)]==0)
    {
      ary = append(ary , sample(c(0,1),size = 1,replace = TRUE, prob = c(p00,p01)))
    }
    else if(ary[length(ary)]==1)
    {
      ary = append(ary , sample(c(0,1),size = 1,replace = TRUE, prob = c(p10,p11)))
    }
  }
  return (ary)
}


#Question 2, 2 arguments (vector, length), it return the two dimensional vector with 1st row for 0s 2nd for 1s
#For different length, it will fill with -1
Q2<-function(ary,length)
{
  ary0<-vector()
  ary1<-vector()
  sapply(1:length(ary),function(i)
  {
    if(ary[i]==0)
    {
      count = 1
      while((count<length) && ((count+i)<=length(ary)))
      {
        if(ary[count+i]!=0) {break}
        count = count +1
      }
      
      if(count==length){ary0 <<- append(ary0,i)}
    }
    else if(ary[i] == 1)
    {
      count = 1
      while((count<length) && ((count+i)<=length(ary)))
      {
        if(ary[count+i]!=1) {break}
        count = count +1
      }
      
      if(count==length){ary1 <<- append(ary1,i)}
    }
    #return(rbind(ary0,ary1))
  })
  
  fill = length(ary0)-length(ary1)
  if(fill>0)
  {
    ary1 = append(ary1,rep(c(-1),each = fill))
  }
  else if(fill<0)
  {
    ary0 = append(ary0,rep(c(-1),each = abs(fill)))
  }
  vector = rbind(ary0,ary1)
  return (vector)
}


#Question 3 , 4 arguments (Sequence, start pattern , end pattern, and patternlength(to specify length of pattern, 
#missing will default to find at all length))
#return a n*2 matrix, each row is the starting and ending position of the whole pattern
Q3 = function(ary, start, end, patternlength)
{
  if(missing(patternlength)){patternlength=-1}
  
  len1 = length(start)
  len2 = length(end)
  ary0<-vector()
  ary1<-vector()
  
  sapply(1:length(ary),function(i)
  {
    if(identical(ary[i:(i+len1-1)],start))
    {
      ary0 <<- append(ary0,i)
    }
    if(identical(ary[i:(i+len2-1)],end))
    {
      ary1 <<- append(ary1,i)
    }
    
  })
  
  if(length(ary0)==0 | length(ary1)==0){return(NULL)}
  vec = vector()
  sapply(1:length(ary0),function(i)
  {
    sapply(1:length(ary1),function(j)
    {
      if((ary0[i]+len1-1)<ary1[j])
      {
        if(patternlength==-1 | (ary1[j]+len2-1-ary0[i])==patternlength)
        {
          vec <<- rbind(vec,c(ary0[i],(ary1[j]+len2-1)))
        }
      }
    })
  })
  if(length(vec)==0){return(NULL)}
  return (vec)
}


#Q4 Testing
Q4 = function()
{
  Q4ary1 = Q1(0.5,0.5,10000)
  Q4ary2 = Q1(0.8,0.1,10000)
  Q4summary = c("Length of Runs", "Counts 0's runs in Matrix I","Counts 1's runs in Matrix I", 
                "Counts 0's runs in Matrix II","Counts 1's runs in Matrix II")
  
  sapply(1:10,function(i)
  {
    temp1 = Q2(Q4ary1, i)
    temp2 = Q2(Q4ary2, i)
    row = c(i,length(which(temp1[1,]>0)), length(which(temp1[2,]>0)),length(which(temp2[1,]>0)),length(which(temp2[2,]>0)))
    Q4summary <<- rbind(Q4summary,as.numeric(row))
  })
  
  Q4summary = rbind(Q4summary,rep(c("--------"),5))
  
  Q4summary =rbind(Q4summary,c("Number of Subsequence", "Matrix I", "Matrix II","    ","  "))
  Q4summary =rbind(Q4summary,c("    ",nrow(Q3(Q4ary1,c(0,0,0,0),c(1,1,1,1),200)),nrow(Q3(Q4ary2,c(0,0,0,0),c(1,1,1,1),200)),"  ","  "))
  Q3(Q4ary1,c(0,0,0,0),c(1,1,1,1),200)
  
  return(Q4summary)
}

#Q5 Graph Summary
Q5 = function()
{
  par(mfrow = c(1,1))
  
  par(mar=c(4,4.5,2,1));par(oma=c(0,0,0,0) )
  #Airpassenger
  ts.plot(AirPassengers,main= "AirPassenger")
  
  #EuStockMarket
  plot(EuStockMarkets)
  Euname = c("DAX","SMI","CAC","FTSE")
  par(mfrow = c(4,2))
  for (i in 1:4)
  {
    boxplot(EuStockMarkets[,i],main = c("Histogram of EuStockMarket",Euname[i] ),xlab=Euname[i])
    hist(EuStockMarkets[,i],main = c("Histogram of EuStockMarket",Euname[i] ),xlab=Euname[i])
  }
  par(mfrow = c(1,1))
  
  
  #PlantGrowth
  plot(PlantGrowth,main = "PlantGrowth")
  plantname = c("ctrl","trt1","trt2")
  par(mfrow = c(3,2))
  for(i in 1:3)
  {
    boxplot(PlantGrowth[which(PlantGrowth[,2]==plantname[i]),1],main = c("PlantGrowth",plantname[i]),xlab = plantname[i],ylab = "Weight")
    hist(PlantGrowth[which(PlantGrowth[,2]==plantname[i]),1],main = c("PlantGrowth",plantname[i]),xlab = plantname[i],ylab = "Weight")
  }
  par(mfrow = c(1,1))
  
  
  
  #Trees
  par(mfrow = c(3,3))
  treename = c("Girth","Height","Volumn")
  for (i in 1:3)
  {
    for(j in 1:3)
    {
      if(i!=j)
      {
        plot(trees[,i],trees[,j],xlab = treename[i],ylab = treename[j])
      }
      else
      {
        hist(trees[,i],xlab = treename[i],ylab = treename[j],main = c("Histogram of Trees -- ",treename[i]))
      }
    }
  }
  par(mfrow = c(1,1))
  
  
  #Airquality
  par(mfrow = c(6,6))
  airname = c("Ozone","Solar.R","Wind","Temp","Month","Day")
  for (i in 1:6)
  {
    for(j in 1:6)
    {
      if(i!=j)
      {
        plot(airquality[,i],airquality[,j],xlab = airname[i],ylab = airname[j])
      }
      else
      {
        hist(airquality[,i],xlab = airname[i],ylab = airname[j],main = c("Histogram of AirQuality -- ",airname[i]))
      }
    }
  }
  par(mfrow = c(1,1))
  
}







