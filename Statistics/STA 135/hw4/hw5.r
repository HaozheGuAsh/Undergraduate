library(rstudioapi)
library(ellipse)
this.dir <- dirname(rstudioapi::getActiveDocumentContext()$path)
setwd(this.dir)

##### DATA #####

################

##### 8.3 ######
eigen(as.matrix(rbind(c(2,0,0),c(0,4,0),c(0,0,4))))


##### 8.6 #####
s = as.matrix(cbind(c(7476.45,303.62),c(303.62,26.19)))
eigen = eigen(s)

xbar =c(155.6,14.7)
plot(ellipse(s,centre =xbar),type = 'l',xlim=c(-100,400),ylim=c(0,30),xlab = "X1",ylab = "X2",main = "constant density ellipse")
points(xbar[1],xbar[2],pch = 17)
c = sqrt(1.4)
ax1=c*sqrt(eigen$values[1])*eigenS$vectors[,1]
ax2=c*sqrt(eigen$values[2])*eigenS$vectors[,2]
lines(c(xbar[1]-ax1[1],xbar[1]+ax1[1]),c(xbar[2]-ax1[2],xbar[2]+ax1[2]),lty=1)
lines(c(xbar[1]-ax2[1], xbar[1]+ax2[1]),c(xbar[2]-ax2[2],xbar[2]+ax2[2]),lty=2)
legend(x = "topleft", c("y1","y2"), lty = c(1,2))	

##### 8.7 #####
p  = cov2cor(s)
eigen = eigen(p)

##### 8.18 #####
e8_18 = read.table("e8_18.txt",header = TRUE)
#assuming PCA output is based on correlation matrix (or variables of unit variance)
pc_correlations <- function(pca_output) { 
  p <- ncol(pca_output$rotation)
  pccor=matrix(NA, nrow=p, ncol=p)
  for(i in 1:p){
    for(k in 1:p){
      pccor[k,i]=pca_output$rotation[k,i]*pca_output$sdev[i] 
    }
  }
  colnames(pccor) <- paste0("PC", 1:p)
  rownames(pccor) <- rownames(pca_output$rotation)
  pccor
}
data("iris")
pca <- prcomp(iris[,1:4])
summary(pca)
pc_correlations(pca)