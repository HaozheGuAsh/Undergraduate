library(ggplot2)
library(ggmap)
library(maps)
library(maptools)
library(sp)
library(rstudioapi)
library(readr)
library(tigris)
library(rgeos)
library(igraph)
library(rgdal) 
library(leaflet)
library(stringr)
library(RCurl)
library(geosphere)
library(XML)
#library(devtools)
#install_version("ggplot2", version = "2.1.0", repos = "http://cran.us.r-project.org")

###################################################### MODE ##########################################################################
mode = 0; #Need to Calculate data
mode = 1; #Already finished with data
#####################################################################################################################################

#######################################################  DATA ########################################################################
this.dir <- dirname(rstudioapi::getActiveDocumentContext()$path)
setwd(this.dir)
datapath= paste(this.dir,c("/rdata"),sep = "")
filepath = paste(this.dir,c("/file"),sep = "")

if(!dir.exists("rdata"))
{
  directory= paste(this.dir,c("/rdata"),sep = "")
  dir.create(directory)
  setwd(datapath)
  dcmap = get_map("Washington DC",zoom=12,maptype="terrain",source = "osm")
  save(dcmap,file = "dcmap.Rdata")
}
setwd(datapath)
load("dcmap.Rdata")
ggmap(dcmap)

setwd(filepath)
if(mode==1)
{
  crime <- read_csv("crimes.csv")
  crime = crime[,2:length(crime)]
  estate <- read_csv("estate.csv")
  estate = estate[,2:length(estate)]
  estate$price[3511] = 9.95e8
  estate$price[4709] = 6.4e7
  #estate$lon = 0;estate$lat = 0;
}


#somePlace <-ggmap::geocode("Washington,DC") 
#leaflet(somePlace) %>% addTiles() %>%
#addTiles() %>% addMarkers()

#dc_urban = urban_areas(cb = F,detailed = TRUE)


if(mode==0)
{
  dummy = sapply(1:3306,function(i){
    tmp = geocode(paste(crime$BLOCK[i],"Washington DC USA"),output="latlon")
    crime$lon[i] <<- tmp$lon
    crime$lat[i] <<- tmp$lat
    return(tmp)
  })
  
  
  #Convert Day and Night for Date ( So 7:00 AM to 7:00 PM are defined as Day where daylight is available)
  #crime$Day_Night = " " 
  regex.time = "(\\d){1,2}(:(\\d){1,2})(:(\\d){1,2})"
  regex.ampm = "(AM|PM)"
  dummy = sapply(1:3306,function(i){
    hour = str_sub(unlist(str_extract_all(crime$START_DATE[i],regex.time)),1,-7)
    ampm = unlist(str_extract_all(crime$START_DATE[i],regex.ampm))
    if(ampm=="PM")
    {
      ifelse(as.numeric(hour)<7,crime$Day_Night[i] <<-"DAY",crime$Day_Night[i] <<- "NIGHT")
      
    }else#AM
    {
      ifelse(as.numeric(hour)> 7,crime$Day_Night[i] <<-"DAY",crime$Day_Night[i] <<- "NIGHT")
    }
  })
  write.csv(crime,file = "crimes.csv")
  
  ## Real estate price, 56 html files
  estate = data.frame(address = character(),place=character(),price=double(),stringsAsFactors = F)
  regex.all = ">.+(</td)"
  for (num in 1:56)
  {
    link = paste(filepath,"/",as.character(num),".html",sep='')
    doc = htmlTreeParse(link,encoding = "UTF-8")
    whole = doc$children$html[[2]]
    whole = whole[[17]]
    doc.content = getNodeSet(whole,path="//tr")
    address = sapply(7:106, function(i) capture.output(doc.content[[i]],file = NULL)[5])
    place =  sapply(7:106, function(i) capture.output(doc.content[[i]],file = NULL)[7])
    price = sapply(7:106, function(i) capture.output(doc.content[[i]],file = NULL)[12]) 
    for(i in 1:100)
    {
      row_address=str_sub(unlist(str_extract_all(address[i],regex.all)),2,-5)
      row_place=str_sub(unlist(str_extract_all(place[i],regex.all)),2,-5)
      row_price=as.double(str_replace_all(str_sub(unlist(str_extract_all(price[i],regex.all)),3,-5),',',''))
      if(!is.na(row_price))
      {
        estate[nrow(estate)+1,] <- c(row_address,row_place,row_price)
      }
    }
  }
  
  dummy = sapply(3989:4000,function(i){
    tmp = geocode(paste(estate$address[i],"Washington DC USA"),output="latlon")
    estate$lon[i] <<- tmp$lon
    estate$lat[i] <<- tmp$lat
    return(tmp)
  })
  
  write.csv(estate,file = "estate.csv")
}


############################################ Analysis #############################################################################
#crime1 = crime[1:2400,]
#murder = subset(crime, crime$OFFENSE == "murder")

ggmap(dcmap)+stat_bin2d(
  aes(x = lon, y = lat, colour = OFFENSE, fill = OFFENSE),
  size = .05, bins = 30, alpha = 1/2,
  data = crime
)

ggmap(dcmap) +
  stat_density2d(
    aes(x = lon, y = lat, fill = ..level.., alpha = ..level..),
    size = 2, bins = 8, data = crime,
    geom = "polygon"
  )
overlay <- stat_density2d(
  aes(x = lon, y = lat, fill = ..level.., alpha = ..level..),
  bins = 16, geom = "polygon",
  data = crime
)
ggmap(dcmap) + overlay 

## all Offence area ##
ggmap(dcmap)+geom_point(aes(color=factor(OFFENSE)),data=crime,size=2,alpha=I(3/5)) + facet_wrap(~OFFENSE)


## contour plot of kernel density
ggmap(dcmap) + stat_density2d(aes(x=lon,y=lat),data=crime)

## Happened in Night or Day
assault = subset(crime, crime$OFFENSE == "ASSAULT W/DANGEROUS WEAPON")
robbery = subset(crime, crime$OFFENSE == "ROBBERY")
ggmap(dcmap)+geom_point(aes(color=factor(Day_Night)),data=assault,size=2,alpha=I(3/5)) 
ggmap(dcmap)+geom_point(aes(color=factor(Day_Night)),data=robbery,size=2,alpha=I(3/5)) 

## Method of Offence
ggmap(dcmap)+geom_point(aes(color=factor(METHOD)),data=assault,size=2,alpha=I(3/5))
ggmap(dcmap)+geom_point(aes(color=factor(METHOD)),data=robbery,size=2,alpha=I(3/5))

## Real Estate price 
all_place = unique(estate$place)
estate$avg_price = 0
dummy = sapply(1:length(all_place),function(i)
  {
    estate$avg_price[which(estate$place==all_place[i])]<<-as.double(mean(estate$price[which(estate$place==all_place[i]&estate$price<1000000)]))
})
estate$avg_price = round(estate$avg_price,-5)


ggmap(dcmap)+geom_point(aes(color=factor(avg_price)),data=estate,size=2,alpha=I(1/5))
ggmap(dcmap) + stat_density2d(aes(x=lon,y=lat,color=factor(avg_price)),data=estate)
ggmap(dcmap)+   stat_density2d(
  aes(x = lon, y = lat, fill = factor(avg_price), alpha =factor(avg_price)),
  size = 1, bins = 8, data = estate,
  geom = "polygon"
)
###
ggmap(dcmap)+stat_bin2d(
  aes(x = lon, y = lat, colour = factor(avg_price), fill =factor(avg_price)),
  size = .05, bins = 20, alpha = 1/2,
  data = estate
)
###
ggmap(dcmap) +stat_density2d(
  aes(x = lon, y = lat, fill = ..level.., alpha = ..level..),
  bins = 16, geom = "polygon",
  data = crime
) +stat_bin2d(
  aes(x = lon, y = lat, colour = factor(avg_price), fill = factor(avg_price)),
  size = .05, bins = 40, alpha = 1/2,
  data = estate
)
###
ggmap(dcmap) + stat_density2d(aes(x=lon,y=lat),size=1,data=crime)+stat_bin2d(
  aes(x = lon, y = lat, colour = factor(avg_price), fill =factor(avg_price)),
  size = .05, bins = 40, alpha = 2/5,
  data = estate
)
###

theft = subset(crime, crime$OFFENSE == "THEFT/OTHER"|crime$OFFENSE == "THEFT F/AUTO")
ggmap(dcmap) + stat_density2d(aes(x=lon,y=lat),data=theft)+stat_bin2d(
  aes(x = lon, y = lat, colour = factor(avg_price), fill =factor(avg_price)),
  size = .05, bins = 40, alpha = 2/5,
  data = estate
)




