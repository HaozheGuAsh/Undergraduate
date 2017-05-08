library(rstudioapi)
library(boot)
this.dir <- dirname(rstudioapi::getActiveDocumentContext()$path)
setwd(this.dir)


dataVoice <- read.csv('voice.csv')
# permute the  data 
sampleSize <- dim(dataVoice)[1]
voice <- dataVoice[sample( seq(sampleSize) , sampleSize),]
voice$meanfun = voice$meanfun*1000
logist <- glm(label ~meanfun , family = "binomial" , data=voice )
summary(logist)

pFull <- predict(logist,voice, type='response')
fullL <- voice$label
levels(fullL)[1] = 0
levels(fullL)[2] = 1
print(mean( round(pFull) == fullL) )

b0=coef(logist)[1]       
b1=coef(logist)[2] 
estprob=function(x){    
  z=exp(b0+b1*x)/(1+exp(b0+b1*x))
  return(z)
}
curve(estprob,from=min(voice$meanfun),to=max(voice$meanfun),xlim=c(50,260),ylim=c(-0.1,1),ylab="Gender(0=female,1=male)",
      xlab="Mean Fundamental Frequency",main = "Logistic Regression Curve")



sum(residuals(logist, type = "pearson")^2)

deviance(logist)

1 - pchisq(deviance(logist), df.residual(logist))

pearson <- residuals(logist, "pearson")
stdpearson = resid(logist, type='pearson')/sqrt(1 - hatvalues(logist))
stddeviance = rstandard(logist)
likelihood = rstudent(logist)
which(abs(pearson)>1.96)
which(abs(stdpearson)>1.96)
which(abs(stddeviance)>1.96)
which(abs(likelihood)>1.96)
