library(rstudioapi)
this.dir <- dirname(rstudioapi::getActiveDocumentContext()$path)
setwd(this.dir)
#functions
two_pop_ci_bonf <- function(A, X1, X2, alpha) { 
  n1 <- nrow(X1)
  n2 <- nrow(X2)¡£
  Spooled <- fun_Spooled(X1, X2)
  ss_factor <- 1/n1 + 1/n2
  d <- colMeans(X1) - colMeans(X2)
  center <- A%*%d
  crit <- two_pop_bonfcritval(n1 = n1, n2 = n2, 
                          p = ncol(X1), alpha = alpha)
  S_iia <-  diag(A %*% (ss_factor*Spooled) %*% t(A))
  me <- crit*sqrt(S_iia)
  ci <- cbind(center - me, center + me)
  colnames(ci) <- c("Lower", "Upper")
  ci
}
two_pop_ci <- function(A, X1, X2, alpha) { 
  n1 <- nrow(X1)
  n2 <- nrow(X2)
  Spooled <- fun_Spooled(X1, X2)
  ss_factor <- 1/n1 + 1/n2
  d <- colMeans(X1) - colMeans(X2)
  center <- A%*%d
  crit <- two_pop_critval(n1 = n1, n2 = n2, 
                          p = ncol(X1), alpha = alpha)
  S_iia <-  diag(A %*% (ss_factor*Spooled) %*% t(A))
  me <- sqrt(crit)*sqrt(S_iia)
  ci <- cbind(center - me, center + me)
  colnames(ci) <- c("Lower", "Upper")
  ci
}
#two population critical value
two_pop_critval <- function(n1, n2, p, alpha) { 
  ((n1 + n2 - 2)*p)/(n1  + n2 - p - 1) * 
    qf(p = 1 - alpha, df1 = p, df2 = n1 + n2 - p - 1)
}
two_pop_bonfcritval <- function(n1, n2, p, alpha) { 
    qt(p = 1 - (alpha/(2*p)), df =n1+n2-2)
}
#pooled variance estimator
fun_Spooled <- function(X1, X2) { 
  n1 <- nrow(X1)
  n2 <- nrow(X2)
  summand <- function(X,n) { 
    (n - 1)*cov(X)
  }
  (1/(n1 + n2 - 2))* (summand(X1,n1) + summand(X2,n2))
}
#two population t2 statstic
two_pop_t2 <- function(X1,X2) { 
  n1 <- nrow(X1)
  n2 <- nrow(X2)
  Spooled <- fun_Spooled(X1, X2)
  ss_factor <- 1/n1 + 1/n2
  d <- colMeans(X1) - colMeans(X2)
  t(d) %*% solve(ss_factor*Spooled) %*% d
}
t2_stat <- function(dat, mu0) 
{ X <- as.matrix(dat) 
n <- nrow(X)  
Xbar<- colMeans(X) 
d <- (Xbar - mu0) 
n * t(d) %*%solve(cov(X)) %*% d 
}
critical_value <- function(n,p, alpha) 
{
  ((n - 1)*p / (n - p)) * qf(p = 1 - alpha, df1 = p, df2 = n - p) }
cif <- function(a, dat, alpha,method = c("T2", "Bonf"), m = NULL) 
{
  X <- as.matrix(dat) 
  Xbar <- colMeans(X) 
  n <- nrow(X) 
  if (method == "T2") 
  {
    p <- ncol(X)
    crit <- critical_value(n, p, alpha) 
    me <- sqrt(crit*(t(a) %*% cov(X) %*% a ) / n) 
  } 
  else if (method == "Bonf") 
  { 
    crit <- qt(p = 1 - (alpha/(2*m)), df = n - 1)
    me <- crit*sqrt((t(a) %*% cov(X) %*% a ) / n) 
  }
  center <- a %*% Xbar
  c(lower = center - me, upper = center + me) 
}
#6.2
e6_2 = read.table("e6_2.txt",header = TRUE)
a = rbind(c(1,0,-1,0),c(0,1,0,-1))
X = as.matrix(e6_2)
X = X%*%t(a)
cif(c(1,0),X,0.05,'T2')
cif(c(0,1),X,0.05,'T2')
cif(c(1,0),X,0.05,'Bonf',2)
cif(c(0,1),X,0.05,'Bonf',2)

#6.6
x2 = as.matrix(cbind(c(3,1,2),c(3,6,3)))
x3 = as.matrix(cbind(c(2,5,3,2),c(3,1,1,3)))
xbar2 = colMeans(x2)
xbar3 = colMeans(x3)
s2 = cov(x2)
s3 = cov(x3)
spool = 2/5*s2+3/5*s3
t2 = t(t(t(xbar2))-t(t(xbar3))) %*% solve((1/3+1/4) * spool)%*%(t(t(xbar2))-t(t(xbar3)))
crit = 2.5*qf(1-0.01,2,4)
center = t(t(xbar2))-t(t(xbar3))
me1 = sqrt(crit)*sqrt((1/3+1/4)%*%spool[1,1])
me2= sqrt(crit)*sqrt((1/3+1/4)%*%spool[2,2])
c(lower = center[1] - me1, upper = center[1] + me1) 
c(lower = center[2] - me2, upper = center[2] + me2) 

#6.16
e6_16 = read.table("e6_16.txt",header = TRUE)
x = as.matrix(e6_16[,1:4])
xbar = t(t(colMeans(x)))
contrast = rbind(c(1,-1,0,0),c(0,1,-1,0),c(0,0,1,-1))
s = cov(x)
n = nrow(x)
q = ncol(x)
t2 = n*t(contrast%*%xbar) %*% solve(contrast %*% s %*% t(contrast)) %*% (contrast%*%xbar)
crit = ((n-1)*(q-1)/(n-q+1))*qf(1-0.05,q-1,n-q+1)

a = t(as.matrix(c(1,1,-1,-1)))
center = a%*%xbar
me = sqrt(crit)*sqrt((a%*%s%*%t(a))/n)
c(lower = center - me, upper = center + me) 
#6.18
e6_18 = read.table("e6_18.txt",header = TRUE)
x1 = as.matrix(e6_18[which(e6_18$gender=='male'),])
x1 = x1[,1:3]
mode(x1)<-"numeric"
x1 = log(x1)
x2 = as.matrix(e6_18[which(e6_18$gender=='female'),])
x2 = x2[,1:3]
mode(x2)<-"numeric"
x2 = log(x2)

two_pop_critval(n1 = nrow(x1), n2 = nrow(x2), 
                p = ncol(x1), alpha = 0.05)
two_pop_t2(x1, x2)
#b
ahat <- solve(fun_Spooled(x1,x2)) %*%(colMeans(x1) - colMeans(x2))
round(t(ahat),3)
#c
tpci <- two_pop_ci(A = diag(ncol(x1)), x1,x2, alpha  = 0.05)
rownames(tpci) <- colnames(x1);tpci
bfci <- two_pop_ci_bonf(A = diag(ncol(x1)), x1,x2, alpha  = 0.05)
rownames(bfci) <- colnames(x1);bfci
#6.19
e6_19 = read.table("e6_19.txt",header = TRUE)
x1 = as.matrix(e6_19[which(e6_19$gas_type=='gasoline'),])
x1 = x1[,1:3]
mode(x1)<-"numeric"
x2 = as.matrix(e6_19[which(e6_19$gas_type=='diesel'),])
x2 = x2[,1:3]
mode(x2)<-"numeric"
xbar1 = colMeans(x1)
xbar2 = colMeans(x2)
s1 = cov(x1)
s2 = cov(x2)
n1 = nrow(x1)
n2 = nrow(x2)
spool = ((n1-1)/(n1+n2-2))*s1+((n2-1)/(n1+n2-2))*s2
t2 = t(t(t(xbar1))-t(t(xbar2))) %*% solve((1/n1+1/n2) * spool)%*%(t(t(xbar1))-t(t(xbar2)))
crit = ((n1+n2-2)*3/(n1+n2-3-1))*qf(1-0.01,3,n1+n2-3-1)
#b
ahat <- solve(spool) %*%(colMeans(x1) - colMeans(x2))
round(t(ahat),3)
#c
center = t(t(xbar1))-t(t(xbar2))
me1 = sqrt(crit)*sqrt((1/n1+1/n2)%*%spool[1,1])
me2= sqrt(crit)*sqrt((1/n1+1/n2)%*%spool[2,2])
me3= sqrt(crit)*sqrt((1/n1+1/n2)%*%spool[3,3])
c(lower = center[1] - me1, upper = center[1] + me1) 
c(lower = center[2] - me2, upper = center[2] + me2) 
c(lower = center[3] - me3, upper = center[3] + me3) 
#d delete row 9, 21 for gasoline, x1
x1 = rbind(x1[1:8,],x1[10:20,],x1[22:36,])
xbar1 = colMeans(x1)
xbar2 = colMeans(x2)
s1 = cov(x1)
s2 = cov(x2)
n1 = nrow(x1)
n2 = nrow(x2)
spool = ((n1-1)/(n1+n2-2))*s1+((n2-1)/(n1+n2-2))*s2
t2 = t(t(t(xbar1))-t(t(xbar2))) %*% solve((1/n1+1/n2) * spool)%*%(t(t(xbar1))-t(t(xbar2)))
crit = ((n1+n2-2)*3/(n1+n2-3-1))*qf(1-0.01,3,n1+n2-3-1)
