library(readr)
library(broom)

resample = function(data) {
  n = nrow(data)
  # Sample row numbers (i) rather than values (e_i)
  idx = sample(n, n, replace = TRUE)
  
  # Use row numbers to get new residuals (e2_i).
  res_samp = data$.resid[idx]
  
  # y2_i =  b_0 + b_1 * x_i    + e2_i
  y_samp =  data$.fitted       + res_samp
  
  # Insert new response (y_i) into data frame, keeping old covariates (x_i)
  data$y2 = y_samp
  
  # Fit the same model with new data (y2_i, x_i).
  new_mod = lm(y2 ~ xi, data)
  
  return (coef(new_mod))
}
problem1 = function(seed){
  set.seed(seed) # only set the seed once, at the beginning
  ## Part I
  error = rnorm(n = 100,mean = 0,sd = 1)
  xi = rchisq(n = 100,df = 6)
  yi = -5+2*xi+error
  
  
  ## Part II
  model = lm(yi~xi)
  b0=as.numeric(coef(model)[1]); b1 = as.numeric(coef(model)[2])
  residual = resid(model)
  SSE = sum(residual^2)
  MSE = SSE/98
  info = summary(model)
  sdb0 = info$coefficients[1,2]; sdb1 = info$coefficients[2,2]
  t = qt(0.975,98)
  theoCI = rbind(c(b0-t*sdb0,b0+t*sdb0),c(b1-t*sdb1,b1+t*sdb1))
  
  ## Part III
  data = augment(model)
  boot = replicate(400, resample(data))
  ci_intercept = quantile(boot[1, ], c(0.025, 0.975))
  ci_slope     = quantile(boot[2, ], c(0.025, 0.975))
  
  
  length = cbind(rbind(theoCI[1,2]-theoCI[1,1],theoCI[2,2]-theoCI[2,1]),rbind(ci_intercept[2]-ci_intercept[1],ci_slope[2]-ci_slope[1]))
  statistic =  cbind(theoCI,rbind(ci_intercept,ci_slope))
  statistic = cbind(statistic,length)
  statistic = cbind(statistic,rbind(b0,b1),rbind(MSE,MSE))
  rownames(statistic) = c("Intercept","Slope")
  colnames(statistic) = c("Theoretical Lower", "Theoretical Upper","Bootstrap Lower","Bootstrap Upper","Length of Theoretical CI","Length of Bootstrap CI","Estimated Value","MSE")
  return (statistic)
}

#################################### Q1 ###############################################################
## Part IV
all_statistic = list()
dummy = sapply(1:10, function(i){all_statistic[[i]]<<-problem1(sample(1:1000,1))})
theo_lenth_b0 = vector()
boot_length_b0 = vector()
theo_lenth_b1 = vector()
boot_length_b1 = vector()
dummy = sapply(1:10,function(i){
  theo_lenth_b0 [i] <<-all_statistic[[i]][1,5] 
  theo_lenth_b1 [i] <<-all_statistic[[i]][2,5]
  boot_length_b0 [i] <<-all_statistic[[i]][1,6]
  boot_length_b1 [i] <<-all_statistic[[i]][2,6]
})
avg = cbind(rbind(mean(theo_lenth_b0),mean(theo_lenth_b1)),rbind(mean(boot_length_b0),mean(boot_length_b1)))
colnames(avg) = c("Average Theoretical CI Length","Average Bootstrap CI Length ")
rownames(avg) = c("Intercept", "Slope")
avg
#######################################################################################################


################################## Q2 #################################################################
library(ROCR)
library(class)
## Part I
dat = subset(iris,iris$Species=="setosa"| iris$Species=="versicolor")
levels(dat$Species)<- list(setosa = "setosa",versicolor = "versicolor")

testsize = ceiling(nrow(dat) * 0.10)

testindex = c(
  sample(which(dat$Species == "setosa"), testsize, replace = FALSE),
  sample(which(dat$Species == "versicolor"), testsize, replace = FALSE)
)

testset = dat[testindex, ]
trainset = dat[-testindex, ]

## Part II
# Fit logistic model on training data. Use family = binomial for logistic.
log_model = glm(Species ~ Sepal.Length, data = trainset,
                family = binomial)

log_pred = predict(log_model, testset, type = "response")
# Convert predictions to 1 or 2, for category 1 or 2 respectively.
log_pred = (log_pred > 0.5) + 1
# Convert predictions to spam or ham, same category order as original data.
log_pred = levels(trainset$Species)[log_pred]

# Make a confusion matrix by tabulating true classes against predicted classes.
log_con = table(true = testset$Species, model = log_pred)

# ROC
logpred = predict(log_model, testset, type = "response")
levels(testset$Species)[1]=0
levels(testset$Species)[2]=1
pr <- prediction(logpred, testset$Species)
prf <- performance(pr, measure = "tpr", x.measure = "fpr")
plot(prf,col='black',main = "ROC of Three classification Method")


## Part III
## linear discriminant analysis
library(MASS)
dat = subset(iris,iris$Species=="setosa"| iris$Species=="versicolor")
levels(dat$Species)<- list(setosa = "setosa",versicolor = "versicolor")

testsize = ceiling(nrow(dat) * 0.10)

testindex = c(
  sample(which(dat$Species == "setosa"), testsize, replace = FALSE),
  sample(which(dat$Species == "versicolor"), testsize, replace = FALSE)
)

testset = dat[testindex, ]
trainset = dat[-testindex, ]
# Fitting LDA
lda_model = lda(Species ~ Sepal.Length, data = trainset)
lda_pred = predict(lda_model, testset, type = "response")$class

# Make a confusion matrix by tabulating true classes against predicted classes.
lda_con = table(true = testset$Species, model = lda_pred)

ldapred = predict(lda_model, testset, type = "response")$posterior[,2]
levels(testset$Species)[1]=0
levels(testset$Species)[2]=1
pr1 <- prediction(ldapred, testset$Species)
prf1 <- performance(pr1, measure = "tpr", x.measure = "fpr")
plot(prf1,add=TRUE,col='red')

## Part IV
## k-NN classification
## KNN  3
dat = subset(iris,iris$Species=="setosa"| iris$Species=="versicolor")
levels(dat$Species)<- list(setosa = "setosa",versicolor = "versicolor")

testsize = ceiling(nrow(dat) * 0.10)

testindex = c(
  sample(which(dat$Species == "setosa"), testsize, replace = FALSE),
  sample(which(dat$Species == "versicolor"), testsize, replace = FALSE)
)

testset = dat[testindex, ]
trainset = dat[-testindex, ]
knn_pred_3 = knn(
  train = trainset["Sepal.Length"], # 1-col data frame
  test  = testset["Sepal.Length"],  # 1-col data frame
  cl    = trainset$Species,                       # vector
  k     = 3,prob = T
)
# Confusion matrix.
knn_con_3 = table(true = testset$Species, model = knn_pred_3)
#ROC
prob<-attr(knn_pred_3,"prob")
levels(testset$Species)[1]=0
levels(testset$Species)[2]=1
pr2 <- prediction(prob, testset$Species)
prf2 <- performance(pr2, measure = "tpr", x.measure = "fpr")
plot(prf2,add=TRUE,col='blue')

## KNN  2
dat = subset(iris,iris$Species=="setosa"| iris$Species=="versicolor")
levels(dat$Species)<- list(setosa = "setosa",versicolor = "versicolor")

testsize = ceiling(nrow(dat) * 0.10)

testindex = c(
  sample(which(dat$Species == "setosa"), testsize, replace = FALSE),
  sample(which(dat$Species == "versicolor"), testsize, replace = FALSE)
)

testset = dat[testindex, ]
trainset = dat[-testindex, ]
knn_pred_2 = knn(
  train = trainset["Sepal.Length"], # 1-col data frame
  test  = testset["Sepal.Length"],  # 1-col data frame
  cl    = trainset$Species,                       # vector
  k     = 2,prob = T
)
# Confusion matrix.
knn_con_2 = table(true = testset$Species, model = knn_pred_2)
#ROC
prob<-attr(knn_pred_2,"prob")
levels(testset$Species)[1]=0
levels(testset$Species)[2]=1
pr3 <- prediction(prob, testset$Species)
prf3 <- performance(pr3, measure = "tpr", x.measure = "fpr")
plot(prf3,add=TRUE,col='green')

## KNN  1
dat = subset(iris,iris$Species=="setosa"| iris$Species=="versicolor")
levels(dat$Species)<- list(setosa = "setosa",versicolor = "versicolor")

testsize = ceiling(nrow(dat) * 0.10)

testindex = c(
  sample(which(dat$Species == "setosa"), testsize, replace = FALSE),
  sample(which(dat$Species == "versicolor"), testsize, replace = FALSE)
)

testset = dat[testindex, ]
trainset = dat[-testindex, ]
knn_pred_1 = knn(
  train = trainset["Sepal.Length"], # 1-col data frame
  test  = testset["Sepal.Length"],  # 1-col data frame
  cl    = trainset$Species,                       # vector
  k     = 1,prob = T
)
# Confusion matrix.
knn_con_1 = table(true = testset$Species, model = knn_pred_1)
#ROC
prob<-attr(knn_pred_1,"prob")
levels(testset$Species)[1]=0
levels(testset$Species)[2]=1
pr4 <- prediction(prob, testset$Species)
prf4 <- performance(pr4, measure = "tpr", x.measure = "fpr")
plot(prf4,add=TRUE,col='purple')

legend('bottomright',c("Logistic Regression","linear discriminant analysis","3-NN classification","2-NN classification","1-NN classification"),lty=c(1,1),lwd=c(1.5,1.5),col=c('black','red','blue','green','purple'))


#######################################################################################################

