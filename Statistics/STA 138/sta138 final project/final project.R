library(MASS)
library(rstudioapi)
library(leaps)
library(ResourceSelection)
this.dir <- dirname(rstudioapi::getActiveDocumentContext()$path)
setwd(this.dir)
data <- read_csv("C:/Users/Ash/Desktop/sta138 final project/data.txt")
mydata = data.frame(stringsAsFactors = F,dav = numeric(),pcs=numeric(),mcs = numeric(),beck = numeric(),pgend = numeric(),age=numeric(),educat = numeric() )
for(i in 1: nrow(data))
{
  tmp = unlist(strsplit(as.character(data[i,])," "))
   mydata[i,]<- as.numeric(tmp[tmp!=""])
}
write.csv(mydata,file = "mydata.csv")
mydata <- read_csv("C:/Users/Ash/Desktop/sta138 final project/mydata.csv")
mydata$dav <- factor(mydata$dav)
mydata$pgend <- factor(mydata$pgend)

full=glm(dav~.,data = mydata,family = "binomial" )
null=glm(dav~1,data = mydata,family = "binomial" )
step1 <-step(full, data=mydata, direction="backward")
summary(step1)

step2 <-step(null, scope=list(lower=null, upper=full), direction="forward")

summary(step2)

fit = glm(dav~mcs+beck+pgend+age+educat,data = mydata,family = "binomial" )
summary(fit)

a = c(AIC(fit),AIC(null))
a = rbind(a,c(BIC(fit),BIC(null)))
rownames(a)=c("Intercept and Covariates","Intercept Only")
colnames(a) = c("AIC","BIC")
hoslem.test(fit$y, fitted(fit), g=8)
stdpearson = resid(fit, type='pearson')/sqrt(1 - hatvalues(fit))
plot(x = mydata$age, stdpearson, main = "Standardized Pearson Residual VS AGE")


