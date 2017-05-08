library(rstudioapi)
library(ellipse)
library(ggplot2)
library(readr)
library(psych)
library(nFactors)
library(polycor)
this.dir <- dirname(rstudioapi::getActiveDocumentContext()$path)
setwd(this.dir)

####### 9.28 ##########
e8_18 <- read_delim("e8_18.txt", " ", escape_double = FALSE, trim_ws = TRUE)
nation = e8_18[,1]
X = as.matrix(e8_18[,2:8])
R = cor(X)
S = cov(X)
# Number of Factor for covariance
ev <- eigen(S) # get eigenvalues
ap <- parallel(subject=nrow(X),var=ncol(X),
               rep=100,cent=.05)
nS <- nScree(x=ev$values, aparallel=ap$eigen$qevpea)
plotnScree(nS)

# Number of Factor for correlation
ev <- eigen(R) # get eigenvalues
ap <- parallel(subject=nrow(X),var=ncol(X),
               rep=100,cent=.05)
nS <- nScree(x=ev$values, aparallel=ap$eigen$qevpea)
plotnScree(nS)


## Unrotated PC Analysis with S
fit1 <- principal(S, nfactors=2, rotate="none",scores = TRUE,covar = TRUE)
fit1  

## Varimax Rotation PC Analysis with S
fit2 <- principal(S, nfactors=2, rotate="varimax",scores = TRUE,covar = TRUE)
fit2  

## Unrotated PC Analysis with R
fit3 <- principal(R, nfactors=2, rotate="none",scores = TRUE,covar = TRUE)
fit3  
score <- factor.scores(X,fit3)
score$weights
## Varimax Rotation PC Analysis with R
fit4 <- principal(R, nfactors=2, rotate="varimax",scores = TRUE,covar = TRUE)
fit4 
score <- factor.scores(X,fit4)
score$weights
## Outlier
score <- factor.scores(X,fit4)
plotscore = as.data.frame(score$scores)
ggplot(data = plotscore, aes(x = RC1, y = RC2)) + geom_point()+ggtitle("Scatterplot of Factor Score of PC")+
  geom_text(aes(label=nation),hjust=0, vjust=0)
## ML Unrotated PC Analysis with R
fit5 <- factanal(X, 2, rotation="none")
fit5  
## ML Varimax Rotation PC Analysis with R
fit6 <- factanal(X, 2, rotation="varimax")
fit6 
score <- factor.scores(X,fit6)
score$weights
## Outlier
score <- factor.scores(X,fit6)
plotscore = as.data.frame(score$scores)
ggplot(data = plotscore, aes(x = Factor1, y = Factor2)) + geom_point()+ggtitle("Scatterplot of Factor Score of Maximum Likelihood")+
  geom_text(aes(label=nation),hjust=0, vjust=0)

####### 9.34 ##########
T7_7 <- read_delim("T7-7.dat", "\t", escape_double = FALSE, col_names = FALSE, trim_ws = TRUE)
X = T7_7[1:62,1:4]
colnames(X) = c("BL","EM","SF","BS")
X = as.matrix(X)
R = cor(X)
S = cov(X)

# Number of Factor for covariance
ev <- eigen(S) # get eigenvalues
ap <- parallel(subject=nrow(X),var=ncol(X),
               rep=100,cent=.05)
nS <- nScree(x=ev$values, aparallel=ap$eigen$qevpea)
plotnScree(nS)

# Number of Factor for correlation
ev <- eigen(R) # get eigenvalues
ap <- parallel(subject=nrow(X),var=ncol(X),
               rep=100,cent=.05)
nS <- nScree(x=ev$values, aparallel=ap$eigen$qevpea)
plotnScree(nS)
## Unrotated PC Analysis with S
fit1 <- principal(S, nfactors=1, rotate="none",scores = TRUE,covar = TRUE)
fit1  


fit2 <- principal(R, nfactors=1, rotate="none",scores = TRUE,covar = TRUE)
fit2  


fit3 <- factanal(X, 1, rotation="none")
fit3 


fit4 <- principal(R, nfactors=2, rotate="varimax",scores = TRUE,covar = TRUE)
fit4 
score <- factor.scores(X,fit4)
score$weights
## Outlier
score <- factor.scores(X,fit4)
plotscore = as.data.frame(score$scores)
ggplot(data = plotscore, aes(x = RC1, y = RC2)) + geom_point()+ggtitle("Scatterplot of Factor Score of PC")+
  geom_text(aes(label=c(1:62)),hjust=0, vjust=0)


####### 9.35 ##########
X = T7_7[1:62,5:8]
colnames(X) = c("AFL","LFF","FFF","ZST")
X = as.matrix(X)
R = cor(X)
S = cov(X)

# Number of Factor for covariance
ev <- eigen(S) # get eigenvalues
ap <- parallel(subject=nrow(X),var=ncol(X),
               rep=100,cent=.05)
nS <- nScree(x=ev$values, aparallel=ap$eigen$qevpea)
plotnScree(nS)

# Number of Factor for correlation
ev <- eigen(R) # get eigenvalues
ap <- parallel(subject=nrow(X),var=ncol(X),
               rep=100,cent=.05)
nS <- nScree(x=ev$values, aparallel=ap$eigen$qevpea)
plotnScree(nS)

## Unrotated PC Analysis with S
fit1 <- principal(S, nfactors=1, rotate="none",scores = TRUE,covar = TRUE)
fit1  


fit2 <- principal(R, nfactors=1, rotate="none",scores = TRUE,covar = TRUE)
fit2  


fit3 <- factanal(X, 1, rotation="none")
fit3 


fit4 <- principal(R, nfactors=2, rotate="varimax",scores = TRUE,covar = TRUE)
fit4 
score <- factor.scores(X,fit4)
score$weights
## Outlier
score <- factor.scores(X,fit4)
plotscore = as.data.frame(score$scores)
ggplot(data = plotscore, aes(x = RC1, y = RC2)) + geom_point()+ggtitle("Scatterplot of Factor Score of PC")+
  geom_text(aes(label=c(1:62)),hjust=0, vjust=0)



