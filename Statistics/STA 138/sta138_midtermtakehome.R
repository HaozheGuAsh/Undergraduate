library(rstudioapi)
library(stringr)
library(MASS)
this.dir <- dirname(rstudioapi::getActiveDocumentContext()$path)
setwd(this.dir)
#Q9.5
qchisq(0.95,48)
#Q9.7
car = data.frame(expand.grid( injury= factor(c("Nonfatal","fatal")),eject = factor(c("yes","no")), safety = 
                               factor(c("seltbelt", "none"))) , count = c(1105,14,411111,483,4624,497,157342,1008))

model1 = glm(count~.^2,data = car,family = poisson)
model11 = loglm(count~.^2,data = car,param=T)
summary(model1)
index = sum(abs(model1$fitted.values- car$count))/(2*sum(car$count))

#Q9.8
injury = data.frame(expand.grid( injury= factor(c("No","Yes")),seatbelt = factor(c("no","yes")), location = 
                                   factor(c("urban", "rural")),gender = factor(c("female","male"))) , 
                    count = c(7287,996,11587,759,3246,973,6134,757,10381,812,10969,380,6123,1084,6693,513))
model2 = glm(count~.^2,data = injury,family = poisson)
model22 = glm(count~injury+seatbelt+location+gender+gender:injury+injury:location+injury:seatbelt+
                gender:location:seatbelt,data = injury,family = poisson)
summary(model2)

injury2 = injury
injury2$count = model22$fitted.values
summary(model22)
injury2

#Q4.11
rates = c(2/18.793,32/52.407,12/10.673,104/43.248,28/5710,206/28.612,28/2.585,186/12.663,31/1.462,102/5.317)
rates = c(2/18.793,12/10.673,28/5.710,28/2.585,31/1.462,32/52.407,104/43.248,206/28.612,186/12.663,102/5.317)
doctor = data.frame(expand.grid( age= factor(c("35-44","45-54","55-64","65-74","75-84")),smoke = factor(c("Nonsmoker","Smoker")) ) , 
count = as.numeric(rates))
doctor$count[1:5]/doctor$count[6:10]
model1 = glm(log(count)~.,data = doctor,family = poisson)
model11 = loglm(count~.,data = doctor,param=T)
summary(model1)
model2 = glm(count~.^2,data = doctor,family = poisson)
summary(model2)
#5.3
basketball<- read_csv("sta138_5.3",col_names = FALSE)
colnames(basketball) = c("WL","AST")
dummy=sapply(1:nrow(basketball),function(i){basketball$WL[i] <<- sub("W","1",basketball$WL[i]); 
basketball$WL[i] <<- sub("L","0",basketball$WL[i]);basketball$WL[i]<<-substr(basketball$WL[i],1,1)})
basketball$WL = as.numeric(basketball$WL)
model1=glm(WL~AST,data=basketball,family=binomial)
summary(model1)
b0 = as.numeric(model1$coefficients[1]);b1=as.numeric(model1$coefficients[2])
py = c((exp(b0+b1*3))/(1+exp(b0+b1*3)),(exp(b0+b1*24))/(1+exp(b0+b1*24)))
zb1=0.29378/0.08325
b1ci = c(b1-1.96*0.08325,b1+1.96*0.08325)
deltaodd = c(exp(b1ci[1]),exp(b1ci[2]))

#5.6
disaster = data.frame(Temp = c(66,70,69,68,67,72,73,70,57,63,70,78,67,53,67,75,70,81,76,79,75,76,58),
                      TD=c(0,1,0,0,0,0,0,0,1,1,1,0,0,1,0,0,0,0,0,0,1,0,1))
model2=glm(TD~Temp,data=disaster,family=binomial)
summary(model2)
b0=coef(model2)[1]       
b1=coef(model2)[2] 
estprob=function(x){    
  z=exp(b0+b1*x)/(1+exp(b0+b1*x))
  return(z)
}
curve(estprob,from=min(disaster$Temp),to=max(disaster$Temp),xlim=c(50,85),ylim=c(0,1),ylab="probability",
      xlab="Temp")
points(disaster$Temp,disaster$TD,pch=3)


preddis=predict(model2,data.frame(Temp=c(31)),type="response")

b1ci = c(b1-1.96*0.1082,b1+1.96*0.1082)
deltaodd = c(exp(b1ci[1]),exp(b1ci[2]))
