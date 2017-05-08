#Import Data and Trim
car <- read.csv("car.data", header=FALSE)
car = subset(car,select = c("V7" ,"V1","V6" ))

#Concatenation data into categories
#Car Acceptability : Unacceptible (Unacceptible) & Acceptible ( Good, V-good, Acceptible)
#Bying Price: High(V-high , High) & Low(Low, Medium)
#Safety:  Low & Medium & High

n = nrow(car)
car = as.data.frame.matrix(car)
for( i in 1: n)
{
  if(identical(car[i,1],"vgood")| identical(car[i,1], "good"))
  {
    car[i,1] = "acc"
  }
  
  if(identical(car[i,2],"vhigh"))
  {
    car[i,2] = "high"
  }
  else if(identical(car[i,2],"med"))
  {
    car[i,2] = "low"
  }
  
}
info = table(car)
car_table = data.frame(expand.grid(Price = factor(c("low","high")),Safety = factor(c("low","medium", "high")), Acceptibility = 
                               factor(c("Acc", "Unacc"))) , count = c(0,0,154,65,184,115,288,288,134,223,104,173))
