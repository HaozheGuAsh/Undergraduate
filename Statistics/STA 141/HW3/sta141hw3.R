library(ggplot2)
library(ggmap)
library(maps)
library(maptools)
library(sp)
library(rstudioapi)
library(readr)
library(igraph)

this.dir <- dirname(rstudioapi::getActiveDocumentContext()$path)
setwd(this.dir)

#import the data file
rank <- read_csv("UC_US_News_ranking_2017.txt", col_names = FALSE)
colnames(rank) = c("Name","Rank","Enrollment","Percentage")


#Q1 i)
#get Satellite map
ca = get_map("California",zoom=6,maptype="satellite")
#get boarder of CA
shape = readShapeSpatial("tl_2016_us_state")
states=fortify(shape)
california=subset(states,states$id=="13")
#extract data from csv
schoolname = sapply(1:nrow(rank),function(i){return(as.character(rank[i,1]))})
schoolrank = sapply(1:nrow(rank),function(i){return(as.numeric(rank[i,2]))})
schoolenroll = sapply(1:nrow(rank),function(i){return(as.numeric(rank[i,3]))})
schoolpercent = sapply(1:nrow(rank),function(i){return(as.numeric(rank[i,4]))})
#search for long and lat for address of university
school = sapply(1:nrow(rank),function(i)
  {
    if(i==5)
    {
      tmp = geocode(paste(as.character(rank[i,1]),",USA"),output="latlon")
    }
    else
    {
      tmp = geocode(paste(as.character(rank[i,1]),",CA,USA"),output="latlon")
    }
    
    return (tmp)
  })
school = data.frame(matrix(unlist(school), nrow=9, byrow=T),stringsAsFactors=FALSE)
school = cbind(school,schoolname,schoolrank,schoolenroll,schoolpercent)
colnames(school) = c("lon","lat","schoolname","Rank","Enrollment","Percentage")
graph = ggmap(ca)+geom_polygon(aes(x = long, y = lat,group=group), data = california, color = "blue",size=1,fill=NA)
#plot the satellite graph with state boarder and university
graph1=graph+geom_point(data = school,aes(x=lon,y=lat),color="black",size=5,alpha=0.8)+geom_text(data=school,aes(label=schoolname),size=3,color="white")
graph1

#Q1 ii)
#Text front depend on Rank negatively, Point color depend on Enrollment, transparenty depend on Percentage accepted
graph2=graph+geom_point(data = school,aes(x=lon,y=lat,color=Enrollment,alpha=Percentage),size=10)+geom_text(data=school,aes(label=schoolname,size=-Rank),color="white")
graph2

#Q1 iii)
#address of university set by city
city = c("berkeley,california","Los angeles,california","santa barbara,california","irvine,california",
         "davis.california","san diego,california","santa cruz,california","riverside,california","merced,california")
all_comb = t(combn(city,2))
colnames(all_comb) = c("from","to")
graph3 = graph2
#adding path for each pair of city
for(i in 1: nrow(all_comb))
{
  tmp = route(as.character(all_comb[i,1]),as.character(all_comb[i,2]),mode = "bicycling",structure = "route")
  graph3 = graph3+ geom_path(data = tmp, aes(x=lon, y=lat),color="white",size=1)
}
graph3


#Q2 i)
#calculate all distance for each pair
alldistance = mapdist(all_comb[,1],all_comb[,2], mode = "driving")
#Q2 ii)
gr1 = graph.formula()
dummy=sapply(1:length(schoolname),function(i){gr1<<-gr1+vertices(as.character(schoolname[i]))})

dummy = sapply(1:nrow(alldistance),function(i)
  {
    if(alldistance$miles[i]<=100)
    {
      gr1<<-gr1+edges(c(which(city==alldistance$from[i]),which(city==alldistance$to[i])))
    }
    
  })
#Q2 iii)
plot(gr1)

#Q2 iv) red color means student enrollment is greater than, blue color means student enrollment is less than
dummy = sapply(1:length(schoolenroll),function(i)
{
  if(schoolenroll[i]>20000)
  {
    V(gr1)[i]$color <<- "salmon"
  }
  else
  {
    V(gr1)[i]$color <<- "light blue"
  }
  
})
plot(gr1)
