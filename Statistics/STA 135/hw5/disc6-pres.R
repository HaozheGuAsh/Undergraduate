#' ---	
#' title: "Discussion 6"	
#' author: "Chris Conley"	
#' date: "February 14, 2017"	
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
#' 	
#' ## Exercise 8.28 	
#' 	
#' Read in the data.	
#' 	
#' 	
mali <- read.table(file = "~/../Box Sync/sta135-winter17/textbook_data/T8-7.DAT",	
                   col.names = c("Family", "DistRd", "Cotton", 	
                                 "Maize", "Sorg", "Millet", "Bull", 	
                                 "Cattle", "Goats"))	
kable(head(mali))	
#' 	
#' 	
#' ### (a) Outlier removal	
#' 	
#' Remove the outliers through scatter plots. 	
#' 	
#' 	
#identify outliers through subsetting the data.	
outliers <- subset(mali, DistRd > 400 | Family  >100 | Cattle > 80)	
#obtain the indices of outlying values	
outliers$index <- as.integer(row.names(outliers))	
suppressPackageStartupMessages(library(ggplot2))	
#scatter plots	
ggplot(data = mali, aes(x = DistRd, y = Family)) + geom_point() + 	
   geom_text(data=outliers,	
            aes(x = DistRd, y = Family, label = index)) + 	
  theme_bw()	
ggplot(data = mali, aes(y = DistRd, x = Cattle)) + geom_point() + 	
   geom_text(data=outliers,	
            aes(y = DistRd, x = Cattle, label = index)) + 	
  theme_bw()	
#' 	
#' 	
#' Dropping observations 25, 34, 69, and 72 from the Mali Farm Data. 	
#' 	
#' 	
mali2 <- mali[-outliers[,"index"],]	
#' 	
#' 	
#' ### (b)	
#' 	
#' The `stats::prcomp` function comes with base R and performs a numerically accurate PCA through the SVD of the data matrix instead of evaluating `eigen` on the covariance matrix. It is highly recommended to evaluate PCA under unit variance for all variables through the `scale.` parameter.  We also elect to return the PC scores $\{y_{ij}: i , \dots, n, j = 1, \dots, p\}$ with the `retx` option.  	
#' 	
#' 	
pca_mali <- prcomp(x = mali2, retx = TRUE, center = TRUE, scale. = TRUE)	
summary(pca_mali)	
#' 	
#' 	
#' Note that the standard deviations $\sqrt{\hat\lambda_i)}$ for $i = 1\dots, p$ are reported from this function. If we retain 5 principle components, approx. 90% of the variation is maintained. That is $\frac{1}{p}\sum^5_{i=1} \hat{\lambda_i} = .90043$. The scree plot confirms that this is a suitable number of PCs to maintain due to limited total variance contribution offered by PCs 6-9. 	
#' 	
#' 	
screeplot(pca_mali, type = "lines", pch = 19,	
          main = "Screeplot of Mali Farm Data")	
#' 	
#' 	
#' ### (c)	
#' 	
#' The eigen vectors (or PC loadings) yield limited insight into the correlation structure of the data. Note that the assignment of a particular sign (+/-) to the PC loadings are arbitrary and are mostly helpful to identify contrasting variables. PC1 has roughly equal positive loadings  for most variables related to farm size. Hence, PC1 is a suitable farm size index. PC2 has a contrast between Maize and DistRd vs. Sorghum and Millet. PC3 is basically a DistRd and Goats component due to their relatively large loadings. PC4 is another contrast between Goat and Cattle vs. DistRd and Millet. PC5 is a contrast between DistRd, Cotton, and Sorghum vs. Millet, Cattle, and Goat. PC2-5 are not easily interpreted and reveal the complex correlation structure of the Mali Farm data. 	
#' 	
#' 	
kable(pca_mali$rotation, digits = 3)	
#' 	
#' 	
#' 	
#' Note that we can obtain the correlation coefficients between each PC and the variables, but there is disagreement among statisticians of their overall value when it comes to interpretation of PCs. Basically, the correlation coeffificent $\rho_{Y_i,X_k}$ measure the contribution of $X_k$ to the component $Y_i$ without accounting for the other $X_{j\neq k}$. Interpretation of the $e_{ik}$ do account for all variables, which may be the best way to rank the importance of each variables' contribution to a component. See pgs 433-434 of your textbook for more discussion. 	
#' 	
#' ## Exercise 8.10	
#' 	
#' 	
stocks <- read.table(file = "~/../Box Sync/sta135-winter17/textbook_data/T8-4.DAT",	
                   col.names = c("JPMorgan", "Citibank", "WellsFargo", "RoyalDutchSchell", "ExxonMobil"))	
kable(head(stocks))	
#' 	
#' 	
#' Perform PCA under the correlation matrix in spite of them telling you otherwise in the exercise. 	
#' 	
#' 	
pca_stocks <- prcomp(x = stocks, retx = TRUE, center =  TRUE, scale. = TRUE)	
summary(pca_stocks)	
#' 	
#' 	
#' 	
screeplot(pca_stocks, type = "lines", pch = 19,	
          main = "Screeplot of Weekly Stock Returns")	
#' 	
#' 	
#' 	
#' ### (b)	
#' 	
#' The elbow of the screeplot is at the thrird component. So we keep the first PCs.	
#' 	
#' $\frac{1}{p}\sum^5_{i=1} \hat{\lambda_i} = 0.8690$	
#' 	
#' ### (c)	
#' 	
#' A large sample $100(1 - \alpha)\%$ percentile (formula 8-33) when $m$ variances are being estimated is: 	
#' 	
#' $$	
#' \frac{\hat{\lambda_i}}{1 + z(\alpha/2m)\sqrt{2/n}} \leq \lambda_i \leq \frac{\hat{\lambda_i}}{1 - z(\alpha/2m)\sqrt{2/n}}	
#' $$	
#' 	
#' 	
#' And in code it is: 	
#' 	
#' 	
ci_lambda <- function(hatlambda, alpha, m, n) { 	
  z <- qnorm(p = 1 - (alpha/(2*m)))	
  c(hatlambda/(1 + z*sqrt(2/n)), hatlambda/(1 - z*sqrt(2/n)))	
}	
#' 	
#' 	
#' We evaluate the 95% simultaneous confidence intervals for the first three eigenvalues (variances of the PC1-3). 	
#' 	
#' 	
hatlambdas <- pca_stocks$sdev[1:3]^2	
cil <- t(sapply(hatlambdas, ci_lambda, alpha = 0.05, 	
                m = length(hatlambdas), n = nrow(stocks)))	
colnames(cil) <- c("lower", "upper")	
rownames(cil) <- paste0("lambda",1:3)	
kable(cil)	
#' 	
#' 	
#' 	
#' ### (c)	
#' 	
#' PC1 represents a market index since all the loadings are roughly equally distributed across the variables. The PC scores $\bf \hat{y}_1 = (X - \frac{1}{n}11^TX)\hat{e}_1$ would give you a weekly index for these companies market's performance. Note the negative loadings in PC1 are totally arbitrary. PC2 represents an industry-specific component, independent of the market component. The negative loadings are on the oil companies and the positive loadings are on the banks. PC3 is beyond my interpretation. Most of the variation is due to general market forces and also industry-specific trends. 	
#' 	
#' 	
kable(pca_stocks$rotation, digits = 3)	
#' 	
#' 	
#' 	
#' ## PCA diagnostics	
#' 	
#' Often there can be categorical variables in addition to multivariate continuous variables. When classification is not the goal, PCA can be a useful dimension reduction technique to see how the categories (i.e. classes) cluster without any constraint coming from the classes. This is an especially helpful diagnostic in large-scale experiments when we want to confirm that samples have been appropriately labeled and cluster with their respective treatment. If we see problematic samples that appear to cluster with the wrong treatment, we ought to be suspicious. When classification is the goal, partial least squares regression (PLS) is a more appropriate dimension reduction technique because it maximizes the variation while accounting for the class label structure. 	
#' 	
#' Let's take a look at the classic iris data set to illustrate this diagnostic application of PCA.	
#' 	
#' 	
data("iris")	
kable(head(iris))	
	
#' 	
#' 	
#' Perform PCA on the iris measurements. Notice if we don't use the correlation matrix, then the first PC dominates almost all of the variation. 	
#' 	
#' 	
pca_iris <- prcomp(iris[,1:4], center = T, scale. = F)	
summary(pca_iris)	
#' 	
#' 	
#' Whereas the PCA under the correlation matrix balances out the variation across more PCs. 	
#' 	
#' 	
pca_iris <- prcomp(iris[,1:4], center = T, scale. = T)	
summary(pca_iris)	
#' 	
#' 	
#' 	
#' 	
#' The PCA shows that PC1-2 capture the majority of the variation. Let's look at the PC scores by species (class label). But first, let's misslabel a few of the class labels to see if we can pick them out in a PC score scatter plot. 	
#' 	
#' 	
ggiris <- cbind(as.data.frame(pca_iris$x), species = iris$Species)	
ggiris$species[91] <- "setosa"	
ggiris$species[37] <- "virginica"	
#' 	
#' 	
#' Sure enough, we see mislabel in the first scatter plot very clearly by virtue of the strange grouping of one verginica sample with the  setosa samples and one setosa sample with the versicolor samples. 	
#' 	
#' 	
library(ggplot2)	
ggplot(data = ggiris, aes(x=PC1, y=PC2, group = species, colour = species)) + geom_point() + scale_color_brewer(type = "qual")	
#' 	
#' 	
#' Same thing in this projection of PC1 and PC3. 	
#' 	
#' 	
ggplot(data = ggiris, aes(x=PC1, y=PC3, group = species, colour = species)) + geom_point() + scale_color_brewer(type = "qual")	
#' 	
