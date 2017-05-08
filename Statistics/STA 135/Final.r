library(rstudioapi)
library(CCA)
library(ggplot2)
library(readr)
library(knitr)
this.dir <- dirname(rstudioapi::getActiveDocumentContext()$path)
setwd(this.dir)

################# 2 ################# 
two_markets <- read_delim("two-markets.DAT", " ", escape_double = FALSE, trim_ws = TRUE)
Bio = two_markets[,1:3]
Energy = two_markets[,4:5]
ccal<-cc(X=Bio,Y = Energy)
matcor(Bio,Energy)
ccal$cor  
#Test
ev <- (1 - ccal$cor^2)
n <- dim(Bio)[1]
p <- length(Bio)
q <- length(Energy)
k <- min(p, q)
m <- n - 3/2 - (p + q)/2
w <- rev(cumprod(rev(ev)))
df = (p-1+1)*(q-1+1)
t1stat = -log(w[1])*(m)
t1critical = qchisq(1-0.05,df)


m <- n - 3/2 - (p + q)/2
t2stat = -log(w[2])*m
p = p-1;q=q-1
df = (p-1+1)*(q-1+1)
t2critical = qchisq(1-0.05,df)


colnames(ccal$xcoef) <- paste0("U", 1:2)
kable(ccal$xcoef)
colnames(ccal$ycoef) <- paste0("V", 1:2) 
kable(ccal$ycoef)


rho_u_x2 <- ccal$scores$corr.Y.xscores
colnames(rho_u_x2) <- paste0("U", 1:2) 
kable(rho_u_x2)

rho_v_x1 <- ccal$scores$corr.X.yscores 
colnames(rho_v_x1) <- paste0("V", 1:2) 
kable(rho_v_x1)
#########  3  ################
x1 = c(12, 18)
x2 = c(36, 24)
sp = matrix(c(2.4,1.7,1.7,3.4), ncol=2)
d = x1-x2
n1 = 400
n2 = 133
T2 = d%*%solve((1/n1+1/n2)*sp)%*%d # 29455.07
p = 2
critical = ((n1+n2-2)*p/(n1+n2-p-1))*qf(1-0.05,2,n1+n2-p-1)

l = t(x1-x2)%*%solve(sp)
r = 0.5*t(x1-x2)%*%solve(sp)%*%(x1+x2)
R = log((1/2)*(1/3))
RR=R+r

t(t(l))%*%c(18,24)>=RR

############  5  ##################
p = 4;n = 61
d= as.matrix(c(0.6,-8.4,-0.1,-10.7))
sd = as.matrix(rbind(c(5,0,1,0),c(0,2,-1,1),c(1,-1,4,1),c(0,1,1,4)))
T2 =n*t(d)%*%solve(sd)%*%d
qf(1-0.05, p, n-p)*(n-1)*p/(n-p)

cv = qt(1-0.05/8, 60)
#Drama
s1 = sd[1,1]
c(d[1]-cv*sqrt(s1/n),d[1]+cv*sqrt(s1/n))
#Horror
s2 = sd[2,2]
c(d[2]-cv*sqrt(s2/n),d[2]+cv*sqrt(s2/n))
#Action
s3 = sd[3,3]
c(d[3]-cv*sqrt(s3/n),d[3]+cv*sqrt(s3/n))
#Comedy
s4 = sd[4,4]
c(d[4]-cv*sqrt(s4/n),d[4]+cv*sqrt(s4/n))
