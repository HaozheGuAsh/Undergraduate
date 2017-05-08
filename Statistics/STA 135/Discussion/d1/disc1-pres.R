#' ---	
#' title: "STA 135: Discussion 1"	
#' author: "Chris Conley"	
#' date: "Jan. 11, 2017"	
#' output:	
#'   beamer_presentation:	
#'     fig_width: 7	
#'     fig_height: 5	
#' fontsize: 10pt	
#' ---	
#' 	
#' 	
knitr::opts_chunk$set(echo = TRUE, warning = F, digits = 2)	
#' 	
#' 	
#' ## Basic Descriptive Statistics	
#' 	
#' Suppose that we have an $n\times p$ data array $\bf X$. That is, we have $n$ measurements on $p$ variables. We can compute statistics that describe basic properties of center, scale, and linear association between variables. For the $i$th and $k$th variables, we have	
#' 	
#' - Sample means $\bar{x}_k = \frac{1}{n}\sum_{j=1}^n x_{jk} \hspace{1cm} k = 1, \dots, p$	
#' 	
#' - Sample variances $s_{kk} = \frac{1}{n}\sum_{j=1}^n (x_{jk} - \bar{x}_k)^2 \hspace{1cm} k = 1, \dots, p$	
#' 	
#' - Sample covariance $s_{ik} = \frac{1}{n}\sum_{j=1}^n (x_{ji} - \bar{x}_i)(x_{jk} - \bar{x}_k) \hspace{1cm} i  = 1, \dots, p \text{    } k = 1, \dots, p$	
#' 	
#' - Sample correlations (Pearson's product moment correlation coefficient) 	
#' 	
#' $r_{ik} = \frac{s_{ik}}{\sqrt{s_{ii}s_{kk}}} \hspace{1cm} i  = 1, \dots, p \text{    } k = 1, \dots, p$	
#' 	
#' ## Exercise 1.3 Computing Array of Statistics	
#' 	
#' Store $5 \times 3$ data array. 	
#' 	
#' 	
X <- matrix(c(9,2,6,5,8,	
             12,8,6,4,10,	
              3,4,0,2,1),5,3)	
colnames(X) <- paste0("x", 1:3)	
rownames(X) <- paste0("n", 1:5)	
X	
#' 	
#' 	
#' 	
#' On an exam, you may be required to compute these descriptive statistics by hand. In chapter 3, we will learn some matrix representations of how to compute the array of descriptive statistics. 	
#' 	
#' ## Exercise 1.3 Computing Mean Vector	
#' 	
#' Using the apply function, we can compute the basic statistics over each variable (i.e. column) in the data array $\bf X$ by specifying the 2nd margin and telling what function to apply. First we compute the mean vector $\bar{\bf x}$.   	
#' 	
#' 	
#' 	
xbar <- apply(X = X, MARGIN = 2, FUN = mean)	
xbar	
#' 	
#' 	
#' 	
#' ## Exercise 1.3 Computing Sample Variances 	
#' 	
#' Now compute the sample variances, $s_{kk}$'s. Note that R's \texttt{var} function will use the $n - 1$ divisor instead of $n$. So multiply the output of \texttt{var} by $\frac{n - 1}{n}$	
#' 	
#' 	
n <- nrow(X)	
skk <- ( (n - 1) / n ) * apply(X = X, MARGIN = 2, 	
                               FUN = var)	
skk	
#' 	
#' 	
#' 	
#' ## Exercise 1.3 Computing Covariance, $\bf S_n$	
#' 	
#' R has a built in function to compute the sample covariance of the data array. 	
#' 	
#' 	
Sn <- ( (n - 1) / n ) * cov(X)	
Sn	
#' 	
#' 	
#' Let's confirm the $s_{12}$ entry by hand . 	
#' 	
#' 	
#' ## Exercise 1.3 Computing Correlation $\bf R$	
#' 	
#' 	
cov2cor(Sn)	
#' 	
#' 	
#' Let's confirm the $r_{12}$ entry by hand. 	
#' 	
#' ## Exercise 1.6 Read in the data	
#' 	
#' Read in the 42 measurements on air-pollution variables recorded at 12:00 noon in Los Angelos on different days. 	
#' 	
#' 	
file <- "~/../Box Sync/sta135-winter17/discussion/air-pollution.txt"	
ap <- read.table(file, header = T)	
X <- as.matrix(ap)	
head(X)	
#' 	
#' 	
#' ## Exercise 1.6 Scatter plot matrix	
#' 	
#' Pairwise relationships can quickly be visualized in R. The following command generates all pairwise scatter plots for the pollutants CO, NO, NO2, HC. Also it shows the marginal distribution of each variable along the diagonal. 	
#' 	
library(GGally)	
ggpairs(ap[,c("CO", "NO", "NO2", "HC")])	
#' 	
#' 	
#' ## Exercise 1.6 Scatter plot matrix	
#' 	
#' 	
library(GGally)	
ggpairs(ap[,c("CO", "NO", "NO2", "HC")])	
#' 	
#' 	
#' 	
#' ## Statistical distance	
#' 	
#' - How might it differ from regular euclidean distance in p dimensions? 	
#' 	
#' ## Statistical distance	
#' 	
#' - How might it differ from regular euclidean distance in p dimensions? 	
#' 	
#' Differences in scale of the variables matter. 	
#' 	
#' Correlation among variables has meaningful impact on distance. Need to rotate our coordinate system to adjust for correlation structure. 	
#' 	
#' ## Exercise 1.9 	
#' 	
#' 	
X <- matrix(c(-6, -3, -2, 1, 2, 5, 6, 8,	
              -2, -3, 1, -1, 2, 1, 5, 3), 8, 2)	
X	
#' 	
#' 	
#' 	
#' 	
#' ## Exercise 1.9 (a) Plot the data	
#' 	
#' 	
	
plot(X[,1], X[,2], xlab = "x1", ylab = "x2", pch = 19)	
abline(h = 0, v = 0)	
#' 	
#' 	
#' ## Exercise 1.9 (a)	
#' 	
#' Obtain $s_{11}, s_{22}, s_{12}$	
#' 	
#' 	
Sn <- cov(X)	
Sn	
#' 	
#' 	
#' 	
#' ## Exercise 1.9 (b)	
#' 	
#' Rotate the data vectors $(x_1, x_2)$ about the new axes to obtain ($\tilde x_1, \tilde x_2$), where 	
#' 	
#' $$	
#' \tilde x_1 = x_1 cos(\theta) + x_2 sin(\theta)	
#' $$	
#' 	
#' $$	
#' \tilde x_1 = -x_1 sin(\theta) + x_2 cos(\theta)	
#' $$	
#' 	
#' 	
#' Under an angle of $\theta = 26$. 	
#' 	
#' 	
theta <- 26	
#rotate x1 axis	
rotx1 <- function(theta, x1, x2) x1*cos(theta) + x2*sin(theta) 	
rx1 <- rotx1(26, X[,1], X[,2])	
#rotate x2 axis	
rotx2 <- function(theta, x1, x2) -x1*sin(theta) + x2*cos(theta) 	
rx2 <- rotx2(26, X[,1], X[,2])	
#' 	
#' 	
#' ## Exercise 1.9 (c)	
#' 	
#' Compute $\tilde s_{11}, \tilde s_{22}$. 	
#' 	
#' 	
rs11 <- var(rx1)	
rs11	
rs22 <- var(rx2)	
rs22	
#' 	
#' 	
#' ## ## Exercise 1.9 (d)	
#' 	
#' Compute the distance of the new point $(x_1, x_2) = (4,-2)$ by transforming into $(\tilde x_1, \tilde x_2)$ and evaluating. 	
#' 	
#' $$	
#' d(O,P) = \sqrt{\frac{\tilde{x^2_1}}{\tilde{s_{11}}} + \frac{\tilde{x^2_2}}{\tilde{s_{22}}}}	
#' $$	
#' 	
#' 	
#' 	
rx1_new <- rotx1(26, 4, -2)	
rx2_new  <- rotx2(26, 4, -2)	
d <- sqrt(rx1_new^2/rs11 + rx2_new^2/rs22)	
d	
#' 	
#' 	
