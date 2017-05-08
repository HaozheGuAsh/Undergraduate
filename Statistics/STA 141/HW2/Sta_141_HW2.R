#load library, data
library(vcd)
library(ggplot2)
library(corrgram)
library(car)
load("NHANES.Rdata")
load("C:/Users/Ash/Google Drive/Undergraduate/Junior & Senior/Fall 2016/STA 141/NHANES.Rdata")
attach(NHANES)
#check null condition
sapply(NHANES,function(var) sum(is.na(var)))
#make levels more infomative
NHANES$Ed = factor(Ed,levels = c(0,1), labels = c("non-college","college"))
NHANES$Race = factor(Race,level = c(0,1), labels = c("Caucasian","non-Caucasian"))
attach(NHANES)
#Q1 Natural Clusters, Relation between categorical  Smoke Ed Race Sex and Cancer Incedence
mosaic(~  Cancer.Incidence +Smoke, data = NHANES, shade = TRUE, legend = TRUE)
mosaic(~ Cancer.Incidence+Sex,data=NHANES, shade = TRUE, legend = TRUE)
mosaic(~ Cancer.Incidence+Ed,data=NHANES, shade = TRUE, legend = TRUE)
mosaic(~ Cancer.Incidence+Race,data=NHANES, shade = TRUE, legend = TRUE)

mosaic(~ Smoke + Sex , data = NHANES, shade = TRUE, legend = TRUE)
mosaic(~ Ed + Sex , data = NHANES, shade = TRUE, legend = TRUE)
mosaic(~ Ed + Race , data = NHANES, shade = TRUE, legend = TRUE)


#Q2 Find relationship among continuous variable 
corrgram(NHANES, order = FALSE, lower.panel = panel.shade, upper.panel= panel.pie,
         text.panel = panel.txt, main = "Correlogram of NHANES data")

scatterplot(BMI ~ Weight | Smoke, data = NHANES, lwd=2,
            main = "Scatter plot of MPG vs Weight byof Cylinders",
            xlab = "Weight of car (in 1000 lbs)", ylab = "Miles per Gallon",
            legend.plot = TRUE, legend.coords = "topleft",# adds legend and controls its position
            boxplot = "xy", # adds boxplots of wt and mpg on margins of x and y axes
            span = 0.9, # controls degree of smoothing for lowess smoother
            id.method = "identify", # allows us to identify points by their labels
            lty = 2,
            labels=row.names(NHANES)) # row names are to be used as labels

weight_bmi = ggplot(NHANES, aes(log(BMI),log(Weight)))
bestscatter = geom_point(alpha=I(1), shape='*', size=I(3))
bestfit = geom_smooth(method="lm", se=F, color="blue",size=1)
weight_bmi + bestscatter + bestfit 

iron_tran = ggplot(NHANES,aes(log(Serum.Iron),log(Transferin)))
bestscatter1 = geom_point(alpha=I(1), shape='*', size=I(3))
bestfit1 = geom_smooth(method= "lm",se = F,color = "blue",size = 1)
iron_tran+bestscatter1+bestfit1


#Q3 find relationship between weight, smoke conditioned on other variables and age, smoke conditioned on other variables
wei_smo = ggplot(NHANES,aes(x = Smoke,y= Weight))
wei_smo + aes(color=Smoke) + geom_boxplot( )
wei_smo + aes(color=Smoke) + geom_boxplot( ) + facet_grid(.~ Sex)
wei_smo + aes(color=Smoke) + geom_boxplot( ) + facet_grid(.~ Ed)

age_smo = ggplot(NHANES,aes(x = Smoke,y= Age))
age_smo + aes(color=Smoke) + geom_boxplot( )
age_smo + aes(color=Smoke) + geom_boxplot( ) + facet_grid(.~ Sex)
age_smo + aes(color=Smoke) + geom_boxplot( ) + facet_grid(.~ Ed)


#Q4 Fit log-linear model to investigate associations among Cancer Incidence, 
tbl = as.data.frame(ftable(Cancer.Incidence,Smoke,Sex))
model1 = glm(Freq~.^3,data = tbl,family = poisson)  
summary(model1)  
c(exp(0.600136-1.96*0.140490),exp(0.600136+1.96*0.140490))  
  
