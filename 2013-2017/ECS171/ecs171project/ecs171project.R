library(warbleR)
library(readr)
library(rstudioapi)
library(ROCR)
library(ggplot2)
this.dir <- dirname(rstudioapi::getActiveDocumentContext()$path)
setwd(this.dir)

######## Processing Voice File####################
setwd("C:/Users/Ash/Desktop//")
setwd("~/Desktop/Google 云端硬盘/ecs171project/ap/")
setwd("~/Downloads/presentation/")
file.remove("manualoc_output.csv")

manualoc(flim = c(0,0.28))
a <- data.frame(read_csv("manualoc_output.csv"))
result<- specan(X =a ,threshold = 15,bp = c(0, 0.28))
##################################################
newsample = result[,4:length(result)]
pred <- as.data.frame(predict(logist,newsample, type='response'))
rownames(pred)= result[,1]
colnames(pred) = "Predicted(0->female 1->male)"
pred$Gender = " ";
for(i in 1:nrow(pred)){
  if(pred$`Predicted(0->female 1->male)`[i]<0.5)
  {pred$Gender[i]<-"Female"}
  else{pred$Gender[i]<- "Male"}}
pred
######## Logistic ################################
setwd(this.dir)
dataVoice <- read.csv('voice.csv')
sampleSize <- dim(dataVoice)[1]

# permute the  data 
dataVoice_shuffle <- dataVoice[sample( seq(sampleSize) , sampleSize),]

# percent and size of training set will be
n <- 0.70
trainSize <- round(sampleSize*n)


# split from the full data for training 
trainSet <-  dataVoice_shuffle[1:trainSize,]

# use the remaining data for testing
testSet <- dataVoice_shuffle[ (trainSize + 1): sampleSize, ]

logist <- glm(label ~ ., family = "binomial" , data=trainSet )


pFull <- predict(logist,dataVoice, type='response')
pTrain <- predict(logist, trainSet , type='response')
pTest <- predict(logist,testSet, type='response')


fullL <- dataVoice$label
trainL <- trainSet$label
testL <- testSet$label

levels(fullL)[1] = 0
levels(fullL)[2] = 1

levels(trainL)[1] = 0
levels(trainL)[2] = 1

levels(testL)[1] = 0
levels(testL)[2] = 1

pr <- prediction(pTest, testL)
prf <- performance(pr, measure = "tpr", x.measure = "fpr")
plot(prf,main = "ROC of Logistic Regression Testing")

# accuracy of full data 
print("Full data")
print(mean( round(pFull) == fullL) )

# accuracy of Training data 
print('Training')
print(mean( round(pTrain) == trainL ))

# accuracy of Testing data 
print('Testing')
print(mean( round(pTest) == testL ))
pearson <- residuals(logist, "pearson")
which(abs(pearson)>1.96)
#plot(logist)
p1<-ggplot(logist, aes(.fitted, pearson,color = pearson>0))+geom_point()
p1<-p1+guides(color=guide_legend(title="Is Male"))
p1<-p1+stat_smooth(method="loess")+geom_hline(yintercept=0, col="red", linetype="dashed")
p1<-p1+xlab("Fitted values")+ylab("Pearson Residule")
p1<-p1+ggtitle("Pearson Residual vs Fitted Plot")+theme_bw()
p1
####################################################


########### CART ###################################
library(rpart)
library(rpart.plot)
library(rattle)
library(RColorBrewer)

# Create classification tree
tree <-rpart(label~.,method="class",data = trainSet)

# Result
printcp(tree)

# prune the tree and visualize
#Each node show three lines: 1) Predicted Class 
#                            2)Conditional probability for each class 
#                            3) Percentage observation at that node

mincp <- tree$cptable[which.min(tree$cptable[,"xerror"]),"CP"]
pruned.tree <- prune(tree, cp = mincp)
fancyRpartPlot(pruned.tree)


# Visualize Tree(complex)
complex.tree <-rpart(label~.,method="class",data = trainSet,control = rpart.control(cp = 1e-04))
fancyRpartPlot(complex.tree)


# Statistics for simple tree
predtrain <- round(predict(tree, trainSet))[,2] #Taking Whether is Male as lable, so 0 for Female, 1 For Male
predtest <- round(predict(tree, testSet))[,2]
predfull <- round(predict(tree, dataVoice))[,2]


fullL <- dataVoice$label
trainL <- trainSet$label
testL <- testSet$label

levels(fullL)[1] = 0
levels(fullL)[2] = 1

levels(trainL)[1] = 0
levels(trainL)[2] = 1

levels(testL)[1] = 0
levels(testL)[2] = 1

statistic = c(mean( predfull == fullL),mean( predtrain == trainL ),mean( predtest == testL ))

# Statistics for complex tree
predtrain <- round(predict(complex.tree, trainSet))[,2] #Taking Whether is Male as lable, so 0 for Female, 1 For Male
predtest <- round(predict(complex.tree, testSet))[,2]
predfull <- round(predict(complex.tree, dataVoice))[,2]


fullL <- dataVoice$label
trainL <- trainSet$label
testL <- testSet$label

levels(fullL)[1] = 0
levels(fullL)[2] = 1

levels(trainL)[1] = 0
levels(trainL)[2] = 1

levels(testL)[1] = 0
levels(testL)[2] = 1

statistic = rbind(statistic,c(mean( predfull == fullL),mean( predtrain == trainL ),mean( predtest == testL )))
rownames(statistic) = c("Simple Tree","Complex Tree")
colnames(statistic) = c("Full Accuracy","Trainning Accuracy","Testing Accuracy")
statistic

#######################################################



library(ROCR)

crossV<- function(data,k=10){
  # shuffling the data
  data = data[sample(nrow(data)), ]
  # split the size samples of the data into k parts
  folds <- cut(1:nrow(data),breaks=k,labels=F )
  
  generalAcc <- 0
  xtpr <- 0
  yfpr <- 0
  
  auc_k <- 0
  
  for(i in 1:k){
    # the sequence of indices pertaining to the testing set
    testSeq = which(folds == i)
    # k data set left to test the training
    testSet = data[testSeq,]
    # All other data no used for testing used for training
    trainSet = data[-testSeq,]
    
    model <- glm(label~. , family ='binomial', data=trainSet)
    
    # prediction the testing set
    p <- predict(model,testSet,type='response')
    # computing the accuracy of the testing set
    accuracy <- mean( round(p) == testSet$label)
    # culminating the accuracy for the generalization accuracy
    generalAcc <- generalAcc + accuracy  
    
    # computing the ROC of the prediction vs actual 
    pr <- prediction(p,testSet$label)
    # gives the values of the true positive rate and false positive rate
    prf <- performance(pr,measure='tpr',x.measure='fpr')
    # culminating both rates
    xtpr <- xtpr + prf@x.values[[1]]
    yfpr <- yfpr + prf@y.values[[1]]
    # gives the area under the curve
    auc <- performance(pr,measure= 'auc')
    plot(prf,main = "ROC of Logistic Regression Testing")
    # culminating the auc
    auc_k <- auc_k + auc@y.values[[1]]
    
    
  }
  # average ROC for the k times
  avgRoc <- list(x= xtpr/k , y = xtpr/k)
  result = list(roc=avgRoc,genAcc= generalAcc/k, auc=auc_k/k);
  return(result)
  
}

dataVoice <- read.csv('voice.csv')
sampleSize <- dim(dataVoice)[1]

levels(dataVoice$label)[1] = 0
levels(dataVoice$label)[2] = 1



logist <- glm(label ~. , family = "binomial" , data=trainSet )

# Does k-fold cross validation and average of ROC 
results <- crossV(dataVoice,10)


plot( results$roc )

print("Average auc")
print(results$auc)
print('Generalizatin Accuracy for 10-fold ')
print(results$genAcc)













