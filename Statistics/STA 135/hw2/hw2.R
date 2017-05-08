t2_stat <- function(dat, mu0) 
{ X <- as.matrix(dat) 
  n <- nrow(X)  
  Xbar<- colMeans(X) 
  d <- (Xbar - mu0) 
  n * t(d) %*%solve(cov(X)) %*% d 
}
critical_value <- function(n,p, alpha) 
{((n - 1)*p / (n - p)) * qf(p = 1 - alpha, df1 = p, df2 = n - p) }


cif <- function(a, dat, alpha,
                method = c("T2", "Bonf"), m = NULL) 
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



library(ellipse)	
ci_ellipse <- function(pw, dat, alpha, mu0) {	
  X <- as.matrix(dat); X <- X[,pw];	
  Xbar <- colMeans(X)	
  crit <- critical_value(n = nrow(X), p = ncol(X), 	
                         alpha = alpha)	
  ell_points <- ellipse(x = cov(X), centre = Xbar,	
                        t = sqrt(crit/n))	
  plot(ell_points,	
       type = "l",	
       main = "Scatter plot of data with T2 confidence ellipse",	
       ylim = c(min(X[,2]), max(X[,2])), 	
       xlim  = c(min(X[,1]), max(X[,1])))	
  #center of ellipse	
  points(Xbar[1], Xbar[2], pch = 19)	
  #proposed mu0	
  points(mu0[1], mu0[2], pch = "*", cex = 3)	
  #data 	
  points(X[,1], X[,2], pch = '+')	

}	



ci_compare <- function(XA, n, p, alpha, 	
                       bonf_rect,  t2_rect, 	
                       xlab = "", 	
                       ylab = "") {	
  Xbar <- colMeans(XA)	
  crit <- critical_value(n = n, p = p, 	
                         alpha = alpha)	
  ell_points <- ellipse(x = cov(XA), centre = Xbar,	
                        t = sqrt(crit/n))	
  plot(ell_points,	
       type = "l",	
       main = "Compare Bonferroni to T^2", 	
       xlab = xlab, 	
       ylab = ylab)	
  #center of ellipse	
  points(Xbar[1], Xbar[2], pch = 19)	
  #bonferroni bonf_rectangle	
  segments(x0 = bonf_rect[1,1], y0 = bonf_rect[2,1], 	
           x1 = bonf_rect[1,1], y1 = bonf_rect[2,2], 	
           lty = 2)	
  segments(x0 = bonf_rect[1,1], y0 = bonf_rect[2,1], 	
           x1 = bonf_rect[1,2], y1 = bonf_rect[2,1], 	
           lty = 2)	
  segments(x0 = bonf_rect[1,2], y0 = bonf_rect[2,1], 	
           x1 = bonf_rect[1,2], y1 = bonf_rect[2,2], 	
           lty = 2)	
  segments(x0 = bonf_rect[1,2], y0 = bonf_rect[2,2], 	
           x1 = bonf_rect[1,1], y1 = bonf_rect[2,2], 	
           lty = 2)	
  #T^2 rectangle	
  segments(x0 = t2_rect[1,1], y0 = t2_rect[2,1], 	
           x1 = t2_rect[1,1], y1 = t2_rect[2,2], 	
           lty = 3)	
  segments(x0 = t2_rect[1,1], y0 = t2_rect[2,1], 	
           x1 = t2_rect[1,2], y1 = t2_rect[2,1], 	
           lty = 3)	
  segments(x0 = t2_rect[1,2], y0 = t2_rect[2,1], 	
           x1 = t2_rect[1,2], y1 = t2_rect[2,2], 	
           lty = 3)	
  segments(x0 = t2_rect[1,2], y0 = t2_rect[2,2], 	
           x1 = t2_rect[1,1], y1 = t2_rect[2,2], 	
           lty = 3)	
  legend(x = "center", c("Bonferroni","T^2"), lty = c(2,3))	
}	


p <- ncol(lumber)	
n <- nrow(lumber)	
ci_bonf <- t(apply(X = diag(p), MARGIN = 1, 	
                   FUN = cif, 	
                   dat = lumber, alpha = 0.05,	
                   method = "Bonf", m = 3))	
ci_t2 <- t(apply(X = diag(p), MARGIN = 1, 	
                 FUN = cif, 	
                 dat = lumber, alpha = 0.05,	
                 method = "T2", m = 3))	
#' 	

ci_compare(X = as.matrix(lumber), n = n, p = p, alpha = 0.05, 	
           bonf_rect = ci_bonf, t2_rect = ci_t2, 	
           xlab = "Stiffness", ylab = "Bending Strength")	
XA = x%*%A
ci_t2 = rbind(cif(A[,1],X,0.05,'T2'),cif(A[,2],X,0.05,'T2'))
ci_bonf = rbind(cif(A[,1],X,0.05,'Bonf',7),cif(A[,2],X,0.05,'Bonf',7))

ci_compare(XA, n = 7, p = 4, alpha = 0.05, 	
           bonf_rect = ci_bonf, t2_rect = ci_t2, 	
           xlab = "mean increase in length from 2 to 3", ylab = "mean increase in length from 4 to 5")	

qqplot.data <- function (vec) # argument: vector of numbers	
{	
  library(ggplot2)	
  # following four lines from base R's qqline()	
  y <- quantile(vec[!is.na(vec)], c(0.25, 0.75))	
  x <- qnorm(c(0.25, 0.75))	
  slope <- diff(y)/diff(x)	
  int <- y[1L] - slope * x[1L]	
  
  d <- data.frame(resids = vec)	
  
  ggplot(d, aes(sample = resids)) + stat_qq() + 	
    geom_abline(slope = slope, intercept = int) + 	
    theme_bw()	
  
}	
ggplot(data = e5_18, aes(y = x1, x = x2)) + 	
  geom_point() + theme_bw()	
ggplot(data = e5_18, aes(y = x1, x = x3)) + 	
  geom_point() + theme_bw()	
ggplot(data = e5_18, aes(y = x2, x = x3)) + 	
  geom_point() + theme_bw()	
