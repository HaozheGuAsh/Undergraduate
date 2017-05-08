library(rstudioapi)
library(readr)
library(stringr)
library(gtools)
this.dir <- dirname(rstudioapi::getActiveDocumentContext()$path)
directory= paste(this.dir,c("/CarAdvert"),sep = "")
setwd(this.dir)

#Q1
filelist = mixedsort(list.files(path = directory,pattern = "*.txt"))     #get all filename
output <- data.frame(filename = character(),model=character(),model_year = character(),vin = character(), price = character(), mileage = character(), color = character(), transmission = character(), #set dataframe
                    engine_displacement = character(),name_seller = character(),street = character(),phone = character(), website= character(),stringsAsFactors = F)

########### Regular Expression ##############################################################
regex.model= "^(\\d{4})[\\s0-9a-zA-Z-\\.]+"
regex.vin = "^(VIN:\\s)[0-9A-Z]{17}"
regex.price = "\\$[\\d,]+"
regex.mileage = "(UsedMileage:\\s)[\\d,]+"
regex.color = "((Exterior:\\s)[0-9-a-zA-Z\\s]+)((Interior:\\s)[0-9-a-zA-Z\\s]+|Body|Transmission)"
regex.transmission = "(Transmission:\\s)[a-zA-Z0-9\\s-]+(Engine)?"
regex.engine = "(Engine:\\s)(\\d)+(.)?(\\d)*(L)?"
regex.seller = "(Offered\\sby:\\s)[a-zA-Z0-9\\s'&]+"
regex.address = "(Address:\\s)[a-zA-Z0-9,\\s]+(Phone)?"
regex.phone = "(Phone:\\s)(\\(\\d{3}\\))(\\s\\d{3})(-\\d{4})"
regex.website = "(Website:\\s)[a-zA-Z0-9.\\/-~]+(Address)"
##############################################################################################

############ Helper Function ################################################################
emp<-function(x) 
{
  if(length(x)==0)
  {
    x = NA
  }
  if(length(x)>1)
  {
    x = x[1]
  }
  return(x)
}
##############################################################################################

########## Iteration Through Folder###########################################################


dummy = sapply(1:length(filelist),function(i)
  {

    filename = paste(directory,"/",filelist[i],sep = "")
    content <-as.vector(na.omit(unlist(read_delim(filename,"\t", escape_double = FALSE, col_names = FALSE,trim_ws = TRUE))))
    model = str_sub(unlist(str_extract_all(content,regex.model)),5)
    modelyear = str_sub(unlist(str_extract_all(content,regex.model)),1,5)
    vin = str_sub(unlist(str_extract_all(content,regex.vin)),6)
    price = unlist(str_extract_all(content,regex.price))
    mileage = str_sub(unlist(str_extract_all(content,regex.mileage)),14)
    if(i==77)
    {
      print("dfd")
    }
    if(grepl("Body",emp(unlist(str_extract_all(content,regex.color)))))
    {
      color = str_sub(unlist(str_extract_all(content,regex.color)),1,-5) 
    }else if (grepl("Transmission",emp(unlist(str_extract_all(content,regex.color)))))
    {
      color = str_sub(unlist(str_extract_all(content,regex.color)),1,-13)
    }else
    {
      color = str_sub(unlist(str_extract_all(content,regex.color)),1)
    }
    
    transmission = ifelse(grepl("Engine",unlist(str_extract_all(content,regex.transmission))),
                          str_sub(unlist(str_extract_all(content,regex.transmission)),15,-7),str_sub(unlist(str_extract_all(content,regex.transmission)),15))
    engine_displacement = ifelse(grepl("L",unlist(str_extract_all(content,regex.engine))),
                                 str_sub(unlist(str_extract_all(content,regex.engine)),9,-2),str_sub(unlist(str_extract_all(content,regex.engine)),9))
    
    seller =  str_sub(unlist(str_extract_all(content,regex.seller)),13)
    
    address = ifelse(grepl("Phone",unlist(str_extract_all(content,regex.address))),
                     str_sub(unlist(str_extract_all(content,regex.address)),10,-6),str_sub(unlist(str_extract_all(content,regex.address)),10))
    phone = str_sub(unlist(str_extract_all(content,regex.phone)),8)
    
    website = str_sub(unlist(str_extract_all(content,regex.website)),10,-8)
    

    output[i,]<<-c(emp(filelist[i]),emp(model),emp(modelyear),emp(vin),emp(price),emp(mileage),emp(color),emp(transmission),emp(engine_displacement)
                   ,emp(seller),emp(address),emp(phone),emp(website))
  })

write.csv(output,file = "Q1.csv")
Q1 <-as.data.frame(read_csv("Q1.csv")) 
################################## Statistics ###################################################
modellist = sort(unique(output$model))
#modify misspelled model name
output$model[which(output$model==modellist[20])]=modellist[22] #" Acura TL Type-S"  and " Acura TL Type S"
#output$model[which(output$model==modellist[53])]=modellist[54]
#output$model[which(output$model==modellist[68])]=modellist[49]
#output$model[which(output$model==modellist[71])]=modellist[60]
#output$model[which(output$model==modellist[70])]=modellist[48]

#Do a make number check
make = c("Acura","Audi","BMW","Buick","Cadillac","Chevrolet","Chrysler","Dodge","Ford","GMC","Honda","Hyundai","Infiniti","Jeep","Kia","Lexus","Land Rover",
         "Mazda","Mercedes-Benz","Mitsubishi","Nissan","Porsche","Subaru","Toyota","Volkswagen")
makecount = vector()
for(i in 1: length(make))
{
  makecount = rbind(makecount,length(unlist(str_extract_all(output$model,make[i]))))
}
statistic = data.frame(makecount)
rownames(statistic) = make;


################################################################################################

#file.remove("Q1.csv")
#################################################################################################

#Q2
library(RCurl)
library(XML)
library(ggplot2)
link = "http://anson.ucdavis.edu/~mueller/cveng13.html"

doc1 = htmlParse(link)
whole=getNodeSet(doc1,path="//p[contains(.,'(')]")
url=getNodeSet(doc1,path="//p[contains(.,'(')]//a[@href]")
content = sapply(1:length(whole), function(i) str_replace_all(xmlValue(whole[[i]]), "[\r\n]" , ""))
txtwhole = sapply(1:length(whole),function(i) capture.output(whole[[i]],file = NULL))
################################# Setup data frame #################################################
output2 <- data.frame(Year_of_publication = numeric(),
                     Authors = character(),
                     titile_publication = character(),
                     title_journal = character(),
                     volume= character(),
                     url= character(),stringsAsFactors = F)

###################################################################################################
###################### Regex to extract content ##################################################
regex.weburl = "(href=\\\").+(\\\")"
regex.webauthor = ".+(\\([0-9]+\\))"
regex.webtitle = "(\\([0-9]+\\)[\\.,]+).+(.)"
regex.webjournal = "(<em>).+(<\\/em>)"
regex.webvolume = "(<strong>).+(<\\/strong>)"
regex.weburlcheck = "(\\([a-zA-Z\\s]+\\))"
##################################################################################################


###################### Iteration #################################################################
dummy = sapply(1:length(whole),function(i)
{
  year = as.numeric(str_sub(unlist(str_extract_all(content[[i]],regex.webauthor)),-5,-2))
  author = str_sub(unlist(str_extract_all(content[[i]],regex.webauthor)),1,-7)
  title = str_split(str_sub(unlist(str_extract_all(content[[i]],regex.webtitle)),8),"\\.")[[1]][1]
  journal = str_sub(unlist(str_extract_all(txtwhole[[i]],regex.webjournal)),5,-6)
  volume = str_sub(unlist(str_extract_all(txtwhole[[i]],regex.webvolume)),9,-10)
  web = str_sub(unlist(str_extract_all(txtwhole[[i]],regex.weburl)),7,-2)
  output2[i,]<<-c(emp(year),emp(author),emp(title),emp(journal),emp(volume),emp(web))
})
write.csv(output2,file = "Q2.csv")
Q2 <-as.data.frame(read_csv("Q2.csv"),locale = locale(encoding = "ASCII")) 

############################# Statistics ########################################################
years = sort(unique(output2$Year_of_publication))
paper_per_year = vector()
for(i in 1:length(years))
{
  paper_per_year = c(paper_per_year,length(which(output2$Year_of_publication == years[i])))
}
paper_per_year = data.frame(paper_per_year)
paper_per_year$year = years

ggplot(output2, aes(x=as.numeric(output2$Year_of_publication)))+ geom_histogram(bins=length(years)) 


#co-author
num_coauthor = vector()
dummy = sapply(1:nrow(output2),function(i){num_coauthor[i] <<- 1+length(unlist(str_extract_all(output2$Authors[i],',')))})
num_coauthor=floor(num_coauthor/2)-1
index = which(num_coauthor==max(num_coauthor))
result = t(output2[index,])

#journal
jour = unique(output2$title_journal)
pubjour = vector()
for(i in 1:length(jour))
{
  pubjour = c(pubjour,length(which(output2$title_journal == jour[i])))
}
pubjour = data.frame(pubjour)
pubjour$journal = jour
#################################################################################################

#file.remove("Q2.csv")
##################################################################################################




