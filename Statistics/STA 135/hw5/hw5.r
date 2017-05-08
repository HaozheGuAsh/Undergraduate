library(rstudioapi)
library(ellipse)
library(ggplot2)
this.dir <- dirname(rstudioapi::getActiveDocumentContext()$path)
setwd(this.dir)

##### 8.3 ######
eigen(as.matrix(rbind(c(2,0,0),c(0,4,0),c(0,0,4))))


##### 8.6 #####
s = as.matrix(cbind(c(7476.45,303.62),c(303.62,26.19)))
eigen = eigen(s)

xbar =c(155.6,14.7)
plot(ellipse(s,centre =xbar),type = 'l',xlim=c(-100,400),ylim=c(0,30),xlab = "X1",ylab = "X2",main = "constant density ellipse")
points(xbar[1],xbar[2],pch = 17)
c = sqrt(1.4)
ax1=c*sqrt(eigen$values[1])*eigen$vectors[,1]
ax2=c*sqrt(eigen$values[2])*eigen$vectors[,2]
lines(c(xbar[1]-ax1[1],xbar[1]+ax1[1]),c(xbar[2]-ax1[2],xbar[2]+ax1[2]),lty=1)
lines(c(xbar[1]-ax2[1], xbar[1]+ax2[1]),c(xbar[2]-ax2[2],xbar[2]+ax2[2]),lty=2)
legend(x = "topleft", c("y1","y2"), lty = c(1,2))	

##### 8.7 #####
p  = cov2cor(s)
eigen = eigen(p)

##### 8.18 #####
library(readr)
e8_18 <- read_delim("e8_18.txt", " ", escape_double = FALSE, trim_ws = TRUE)
nation = e8_18[,1]
X = as.matrix(e8_18[,2:8])
r = cor(X)
eigen = eigen(r)
firstpc = -1*eigen$vectors[,1]
stdX  <- scale(X)
new = stdX%*%firstpc
nation[(sort.int(new,index.return = TRUE))$ix,]

##### 8.27 #####
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
e8_27 <- read_delim("e8_27.txt",
                    " ", escape_double = FALSE, trim_ws = TRUE)
X = scale(as.matrix(e8_27))
pca <- prcomp(x = X, retx = TRUE, center = TRUE, scale. = TRUE)
summary(pca)
pc_correlations(pca)
screeplot(pca, type = "lines", pch = 19,
          main = "Screeplot of pulp and paper properties Data")
e8_27$y1 = X%*%pca$rotation[,1]
e8_27$y2 = X%*%pca$rotation[,2]
ggplot(data = e8_27, aes(x = y2, y = y1)) + geom_point()+ggtitle("Scatterplot of Y1hat and Y2hat")
