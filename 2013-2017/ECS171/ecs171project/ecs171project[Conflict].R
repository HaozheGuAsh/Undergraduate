library(warbleR)
library(readr)
library(rstudioapi)
this.dir <- dirname(rstudioapi::getActiveDocumentContext()$path)
setwd(this.dir)

######## Processing Voice File####################
setwd("C:/Users/Ash/Desktop/ap/")
setwd("~/Desktop/Google 云端硬盘/ecs171project/ap/")
setwd("~/Downloads/sc/")
file.remove("manualoc_output.csv")

manualoc(flim = c(0,0.28))
a <- data.frame(read_csv("manualoc_output.csv"))
result<- specan(X =a ,threshold = 15,bp = c(0, 0.28))
##################################################



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

logist <- glm(label ~. , family = "binomial" , data=trainSet )
dataVoice$meanfun = dataVoice$meanfun*1000
logist <- glm(label ~meanfun , family = "binomial" ,data = dataVoice)
sum(residuals(logist, type = "pearson")^2)

deviance(logist)

1 - pchisq(deviance(logist), df.residual(logist))

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

# accuracy of full data 
print("Full data")
print(mean( round(pFull) == fullL) )

# accuracy of Training data 
print('Training')
print(mean( round(pTrain) == trainL ))

# accuracy of Testing data 
print('Testing')
print(mean( round(pTest) == testL ))
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


















