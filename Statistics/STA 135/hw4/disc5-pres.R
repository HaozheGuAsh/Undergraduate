#' ---	
#' title: "Discussion 5"	
#' author: "Chris Conley"	
#' date: "February 8, 2017"	
#' output:	
#'   html_document: default	
#'   pdf_document: default	
#' ---	
#' 	
#' 	
library(knitr)	
knitr::opts_chunk$set(echo = TRUE)	
#' 	
#' 	
#' ## Exercise 6.17	
#' 	
#' 	
#' 	
num <- read.table(file = "~/../Box Sync/sta135-winter17/textbook_data/T6-8.DAT",	
                  col.names = c("WordDiff", "WordSame", "ArabicDiff", "ArabicSame"))	
kable(head(num))	
#' 	
#' 	
#' Map the variables in the experiment to the treatment mean parameters $\mu_1, \mu_2, \mu_3, \mu_4$. 	
#' 	
#' 	
meta <- data.frame(treatment = colnames(num), parameter = paste0("mu", 1:4))	
kable(meta)	
#' 	
#' 	
#' ### 6.17(a)	
#' 	
#' There are two factors: (i) number format= (word, arabic) and (ii) parity (even/even, odd/even) which are crossed factorially into 4 treatments in a  repeated measures design. We are interested  in testing the following effects: 	
#' 	
#' 	
#' - main effect: parity affects the speed of correct response	
#' - main effect: number format affects the speed of correct responses 	
#' - interaction effect: are there different response between one factor across levels of the other. 	
#' 	
#' Mathematically we express these hypotheses as: 	
#' 	
#' - parity effect: $(\mu_2 + \mu_4) - (\mu_1 + \mu_3)$	
#' - number format effect: $(\mu_3 + \mu_4) - (\mu_1 + \mu_2)$	
#' - interaction effect: $(\mu_2 + \mu_3) - (\mu_1 + \mu_4)$	
#' 	
#' The contrast matrix is: 	
#' 	
#' 	
C <- matrix(c(-1,1,-1,1,	
              -1,-1,1,1,	
              -1,1,1,-1), nrow = 3, ncol = 4, byrow = T)	
rownames(C) <- c("parity", "format","interaction")	
C	
#' 	
#' 	
#' Now we would like to apply result (6-16), which is the test for equality of treatments in a repeated measures design, but first we need to define some functions to do so. 	
#' 	
#' 	
#' First define the repeated measures design critical value function. 	
#' 	
#' 	
#n: sample size	
#q: number of treatments 	
#alpha: level of significance	
rm_critval <-  function(n,q, alpha) { 		
  ((n - 1)*(q - 1) / (n - q + 1)) * 		
    qf(p = 1 - alpha, df1 = q - 1, df2 = n - q + 1)		
}		
	
#' 	
#' 	
#' The critical value ought to be compared with the test statistic $T^2$ in the repeated measures design context, defined below.	
#' 	
#' 	
#see formula 6-16 in text book	
#dat: A data.frame of dimension n x q	
#C: the contrast matrix of dimension (q - 1) x q.	
rm_t2 <- function(dat, C) { 	
  n <- nrow(dat)	
  X <- as.matrix(dat)	
  xbar <- colMeans(X)	
  S <- cov(X)	
  Cxbar <- C %*% xbar	
  CSCinv <- solve(C %*% S %*% t(C))	
  t2_stat <- n*t(Cxbar) %*% CSCinv %*% Cxbar	
  t2_stat	
}	
#' 	
#' 	
#' 	
#' Test $H_0: C\mu = 0$ vs. $H_a: C\mu \neq 0$.	
#' 	
#' 	
rmc <- rm_critval(n = nrow(num), q = ncol(C), alpha = 0.05)	
rmc	
#undebug(rm_t2)	
rmt2 <- rm_t2(dat = num, C = C)	
rmt2	
#' 	
#' 	
#' Since $T^2 > \frac{(n-1)(q-1)}{n - q + 1}F_{q  -1, n - q + 1}$, we reject the null hypothesis of no treatment effects at the 5% level. 	
#' 	
#' ### 6.17(b)	
#' 	
#' Since we know that at least one effect exists, let's inspect which specific effects are significant. 	
#' Define a simultaneous 95% confidence intervals for number format, parity, and interaction effects.	
#' 	
#' 	
#see formula 6-18 in textbook	
#dat: A data.frame of dimension n x q	
#C: the contrast matrix of dimension (q - 1) x q.	
#alpha: level of significance	
#rmc: repeated measures critical value (see above)	
rm_ci <- function(dat,C, alpha, rmc) { 	
  n <- nrow(dat)	
  X <- as.matrix(dat)	
  xbar <- colMeans(X)	
  S <- cov(X)	
  Cxbar <- C %*% xbar	
  CSC <- C %*% S %*% t(C)	
  #margin of error	
  me <- sqrt(rmc) * sqrt(diag(CSC)/n)	
  ci <- cbind(Cxbar - me, Cxbar + me)	
  colnames(ci) <- c("Lower", "Upper")	
  ci	
}	
#' 	
#' 	
#' Apply the function `rm_ci` to obtain our 95% simultaneous confidence intervals. 	
#' 	
#' 	
rmci <- rm_ci(dat = num, C = C, alpha = 0.05, rmc = rmc)	
kable(rmci, digits = 2)	
#' 	
#' 	
#' We see that parity main effect is a negative interval. What does that mean? It means that it takes someone longer to respond correctly when the numbers are in odd/even pairs than (even/even, odd/odd) pairs. Also, the number format is a negative interval, meaning it takes longer to respond when numbers are shown as words instead of arabic numerals. Since zero is contained in the interaction effect confidence interval, we conclude there is insufficient evidence to say there is an interaction effect. 	
#' 	
#' ### 6.17(c)	
#' 	
#' Model M is supported in this experiment because the absence of an interaction between parity and format. 	
#' 	
#' 	
#' ### 6.17(d)	
#' 	
#' Check multivariate normal assumption through the qq-plot of the  mahalanobis $D^2$ vs. $\chi^2_3$. If the theoretical and the sample points match up well, then we will have approximately a straight line (intercept 0, slope = 1) and can assume normality is sufficiently justified. For more details on this diagnostic plot, consult pgs 183-185 of the textbook. 	
#' 	
#' 	
#compute the scores	
scores <- as.matrix(num) %*% t(C)	
#note: mahalanobis function comes with R by default. 	
#copute distance	
D2 <- mahalanobis(x = scores, center = colMeans(scores), cov = cov(scores))	
#compute qqplot	
qqplot(qchisq(ppoints(length(D2)), df = 3), D2,	
       main = expression("Q-Q plot of Mahalanobis" * ~D^2 *	
                         " vs. quantiles of" * ~ chi[3]^2), 	
       pch = 19)	
qqline(D2, distribution = function(p) qchisq(p, df = 3),	
       prob = c(0.25, 0.75), col = 2)	
#' 	
#' 	
#' In this plot we see that there are some outlying samples that have distances much larger than expected. From the textbook, in chapter 6, we learn that the $T^2$ statistic is robust to a few extreme values as well as deviations from normality when the sample size is large enough. 	
#' 	
#' 	
#' 	
#	
#Verify that the code for repeated measures  is correct 	
#by comparing answers with example 6.2	
# dog <- read.table(file = "~/../Box Sync/sta135-winter17/textbook_data/T6-2.DAT",	
#                   col.names = c("x1", "x2", "x3", "x4"))	
# kable(head(dog))	
# C <- matrix(c(-1,-1,1,1,	
#               1,-1,1,-1,	
#               1,-1,-1,1), nrow = 3, ncol = 4, byrow = T)	
# rownames(C) <- c("main-1", "main-2","interaction")	
# C	
# rmc <- rm_critval(n = nrow(dog), q = ncol(C), alpha = 0.05)	
# rm_t2(dat = dog, C = C)	
# rm_ci(dat = dog, C = C, alpha = 0.05, rmc = rmc)	
#' 	
#' 	
#' 	
#' ## Exercise 6.28	
#' 	
#' Read in the fly data. Note the last column denotes the species type. Separete the two populations (*L. torrens and L. carteri*) into separate matrices `X1` and `X2`, respectively. 	
#' 	
#' 	
fly <- read.table(file = "~/../Box Sync/sta135-winter17/textbook_data/T6-15.dat",	
                  col.names = c(paste0("x", 1:7), "species"))	
X1 <- as.matrix(fly[fly$species == 0,1:7])	
X2 <- as.matrix(fly[fly$species == 1,1:7])	
kable(head(fly))	
#' 	
#' 	
#' We would like to test if these two fly species have significant differences in their morphology through 7 different body measurements. 	
#' 	
#' Test $H_0: \mu_1 - \mu_2 = 0$ vs. $H_a: \mu_1 - \mu_2 \neq 0$	
#' 	
#' First we need to define some functions to evaluate the test statistics and critical values. These functions are based on result 6.2 and formula 6-21 in the textbook.	
#' 	
#' 	
#see result 6.2 in textbook	
#two population critical value	
two_pop_critval <- function(n1, n2, p, alpha) { 	
  ((n1 + n2 - 2)*p)/(n1  + n2 - p - 1) * 	
    qf(p = 1 - alpha, df1 = p, df2 = n1 + n2 - p - 1)	
}	
	
#see formula 6-21 in textbook	
#pooled variance estimator	
fun_Spooled <- function(X1, X2) { 	
  n1 <- nrow(X1)	
  n2 <- nrow(X2)	
  summand <- function(X,n) { 	
    (n - 1)*cov(X)	
  }	
  (1/(n1 + n2 - 2))* (summand(X1,n1) + summand(X2,n2))	
}	
	
#see result 6.2 in textbook	
#two population t2 statstic	
two_pop_t2 <- function(X1,X2) { 	
  n1 <- nrow(X1)	
  n2 <- nrow(X2)	
  Spooled <- fun_Spooled(X1, X2)	
  ss_factor <- 1/n1 + 1/n2	
  d <- colMeans(X1) - colMeans(X2)	
  t(d) %*% solve(ss_factor*Spooled) %*% d	
}	
#' 	
#' 	
#' Now we can evaluate the test under $\alpha = 0.05$	
#' 	
#' 	
two_pop_critval(n1 = nrow(X1), n2 = nrow(X2), 	
                p = ncol(X1), alpha = 0.05)	
two_pop_t2(X1, X2)	
#' 	
#' 	
#' Since $T^2>\frac{(n_1 + n_2 - 2)p}{(n_1 + n_2 - p - 1)}F_{p,(n_1 + n_2 - p - 1}$, we reject $H_0$ at 5% significance level. There exists a real difference of the morphological variables between the two species. The estimated linear combination most responsible for the rejection of $H_0$ is described by the coefficent vector $\hat{a} = S^{-1}_{pooled}(\bar{x_1} - \bar{x_2})$ (See remark on page 189 for more context). In this case, we have: 	
#' 	
#' 	
ahat <- solve(fun_Spooled(X1,X2)) %*%(colMeans(X1) - colMeans(X2))	
round(t(ahat),3)	
#' 	
#' 	
#' Next we can calculate the 95% simultaneous C.I. for the mean of morphological differences between the two flies; that is,  $\mu_1 - \mu_2$. 	
#' 	
#' 	
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
#' 	
#' 	
#' Applying the function we just defined yields: 	
#' 	
#' 	
tpci <- two_pop_ci(A = diag(ncol(X1)), X1,X2, alpha  = 0.05)	
rownames(tpci) <- colnames(X1)	
kable(tpci, digits = 2)	
#' 	
#' 	
#' The third and fourth "palp" length (variables 3 and 5) of the fly are the most prominent difference, where the negative interval indicates species *L. torrens* has smaller mean value than *and L. carteri* at the population level.	
#' 	
