#Import Data and Trim
car <- read.csv("~/Desktop/car.data", header=FALSE)
car = subset(car,select = c("V7" ,"V1","V6" ))

#Concatenation data into categories
#Car Acceptability : Unacceptible (Unacceptible) & Acceptible ( Good, V-good, Acceptible)
#Bying Price: High(V-high , High) & Low(Low, Medium)
#Safety:  Low & Medium & High
cardata = vector()
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
cartable = table(car)
car = data.frame(expand.grid(PR = factor(c("low","high")),SA = factor(c("low","medium", "high")), AC = 
                               factor(c("Acc", "Unacc"))) , count = c(1,1,154,65,184,115,288,288,134,223,104,173))

library(MASS)
model1 = glm(count~SA+AC+PR+SA:AC+PR:AC,family = poisson,data = car)
model11 = loglm(count~SA+AC+PR+SA:AC+PR:AC,data = car, param=T)
#model11
#summary(model1)

model2 = glm(count~.^2,data = car, family = poisson)
model22 = loglm(count~.^2,data = car,param=T)
#model22
#summary(model2)

model33 = loglm(count~.^3,data = car,param=T)

model3 = glm(count~SA+AC+PR+SA:AC+PR:AC+SA:PR+SA:PR:AC,family = poisson,data = car)
#summary(model3)

rbind(model1$aic,model2$aic,model3$aic)
coef = (summary(model2)$coefficient)
model_ci = vector()

for(i in 6:10)
{
  model_ci = rbind(model_ci,c(exp(coef[i,1]-1.96*coef[i,2]),exp(coef[i,1]+1.96*coef[i,2])))
  
}
rownames(model_ci) = rownames(coef)[6:10]
colnames(model_ci) = c("CI_lower","CI_higher")


