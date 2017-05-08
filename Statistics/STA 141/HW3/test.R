library(maps)
data(us.cities) # data on major US cities
big.cities= subset(us.cities, name=="WASHINGTON DC") # choose cities with population at least 0.5 million
city.loc= ggplot(big.cities,aes(long,lat)) # borders of states using borders( ) function in ggplot2
city.loc= city.loc+ borders("state",size=0.5,col="green") # plot cities with size determined by population
city.loc+ geom_point(aes(size=pop,color=pop),alpha=I(1/3)) # add the names of the cities as labels
city.loc+ geom_point(aes(size=pop,color=pop),alpha=I(1/3)) + geom_text(aes(label=name),size=2)
ca.state= map_data("county","california") # data on counties in California
# draw the map of each county from the points indicating the boundary of the counties
ggplot(ca.state,aes(long,lat)) + geom_polygon(aes(group=group), fill=NA, col="blue")


library(ggmap)
data(crime) # data frame on incidences of crime in Houston area (part of ggmappackage)
murder = subset(crime, offense == "murder") # extract the part of data frame corresponding to incidences of murder
qmplot(lon, lat, data=murder, color = I("red"), size=I(2), darken=0.3, zoom = 11) # plot the locations of murders
# distinguish the locations by the weekday of occurrence of murder as well as number of murders
qmplot(lon, lat, data=murder, color = factor(day), size=factor(number), darken=0.3, zoom = 11)


geocode("Davis",output="all")
revgeocode(as.numeric(geocode("white house")))
from.loc= c("davis","davis","berkeley");to.loc= c("berkeley","san francisco","santacruz")
mapdist(from.loc, to.loc, mode = "driving") # or "walking" or "bicycling??
from.loc= c("davis, california"); to.loc= c("berkeley, california")
route_df= route(from.loc, to.loc, mode="driving", structure = "route") # returns a data frame containing route


qmap("Davis", zoom =12) # plot map of Davis using Google Maps
qmap("Davis", zoom =12, source = "osm") # using OpenStreetMap
SFO = get_map("san francisco",zoom=12, maptype="roadmap") # default is ??terrain??
ggmap(SFO)
SFO = get_map("san francisco",zoom=12,maptype="satellite") # creates a satellite map



houston= get_map("houston, texas", zoom = 11, maptype= "terrain")
ggmap(houston)
# overlay with incidences of crime (together with number and type of offense)
ggmap(houston) + geom_point(aes(color=factor(day)),data=crime,size=0.2,alpha=I(1/5)) + facet_wrap(~offense)
# draw contour plot of the kernel density estimate of incidences of crime
ggmap(houston) + stat_density2d(aes(x=lon,y=lat),data=crime)
# contour plot of the density of crime subdivided by day of crime (notice the similarity among the contours)
ggmap(houston) + stat_density2d(aes(x=lon,y=lat,color=factor(day)),data=crime)


# draw separate contour plot of the density estimate of crime incidences subdivided by type of crime
ggmap(houston) + stat_density2d(aes(x=lon,y=lat),data=crime) + facet_wrap(~offense)
# instead of the contour plot, use surface plot
overlay = stat_density2d(aes(x=lon,y=lat, fill = ..level.., alpha = ..level..),bins = 5,geom="polygon",data=crime)
# overlay is a ggplotobject to be used as a layer for depicting the density surface
ggmap(houston) + overlay + scale_fill_gradient(low="blue",high="red")
# surface plot of the density of crime subdivided by type of crime
ggmap(houston) + overlay + scale_fill_gradient(low="blue",high="red") + facet_wrap(~offense)



library(igraph)
gr1 = graph.formula(1-2, 1-3, 3-4, 3-5, 4-5, 4-6, 5-6, 6-7)
V(gr1) # returns the set of vertices of gr1
E(gr1) # returns the set of edges of gr1
str(gr1) # expresses the graph in a compact form, listing nodes that each node is connected to
plot(gr1) # visual display of graph gr1
V(gr1)$name # returns the names of nodes of graph gr1

gr2 = graph.formula(a -+ b, a ++ c, c ++ d, d +- e, f++ g)
# the sign + is used to indicate directionality
# the expression a -+ b is interpreted as "there is an edge from node a to node b??
V(gr2) # returns the set of vertices of gr2
E(gr2) # returns the set of directed edges of gr2
V(gr2)$name = c("Alex","Bob","Clo","Dan","Erin","Fang","Guan")
# assign names to the nodes of graph
V(gr2)$gender = c("M","M","F","M","F","M","F") # gender of each node (person)
E(gr2)$distance = c(1,2,1,1,4,4,2,1) # a measure of distance between nodes (persons)
plot(gr2) # visual display of graph gr2 (notice the arrows)

degree(gr1) # distribution of degree of the nodes of graph gr1
degree(gr2,mode="in") # distribution of in-degree of graph gr2
degree(gr2,mode="out") # distribution of out-degree of graph gr2
is.connected(gr1) # check if the graph is connected
clusters(gr2) # find the disconnected subgraphs of the graph gr2
get.edgelist(gr2) # obtain the (directed) edges in matrix format
neighbors(gr2,"Alex") # obtain the neighbors of node Alex
get.adjacency(gr2) # obtain the adjacency matrix of graph gr2 (in a sparse matrix representation)
matrix(get.adjacency(gr2),nrow=vcount(gr2),dimnames=list(V(gr2)$name,V(gr2)$name)) # in standard form


gr3 = induced.subgraph(gr2,1:5)
# extracts induced subgraph of gr2 corresponding to nodes 1 to 5
gr4 = gr2 - vertices(c(1,3)) # removes vertices 1 (Alex) and 3 (Clo) and edges incident to them
gr5 = gr2 + vertices(c("Ron","Mary")) # adds vertices ??Ron?? and ??Mary??
gr6 = gr5 + edges(c(1,4),c(6,8),c(4,9),c(9,4)) # adds four directed edges (indexed by vertex indices)
gr7 = graph.union(gr3,gr4) # union of graphs gr3 and gr4
# (edges are included if they are present an at least one of the graphs)
graph.union(gr1,gr3) # returns error message since gr1 is undirected and gr3 is directed


g2.lat = graph.lattice(c(3,3,3)) # a 3 x 3 x 3 lattice graph (27 vertices)
plot(g2.lat) # usual "lattice" layout
plot(g2.lat, layout = layout.circle) # "circular" layout
plot(g2.lat, layout = layout.star) # "star" layout
plot(g2.lat, layout = layout.kamada.kawai) # "Kamada-Kawai" layout (lattice-like)
plot(g2.lat, layout = layout.reingold.tilford) # "Reingold-Tilford" layout (tree-like)


# Typical usage:
# graph_from_adjacency_matrix(adjmatrix,
# mode = c("directed", "undirected??, "max", "min", "upper", "lower", "plus"), weighted = NULL)
adjm = matrix(sample(0:1, 100, replace=TRUE, prob=c(0.9,0.1)), nc=10)
g1 = graph_from_adjacency_matrix( adjm )
adjm = matrix(sample(0:5, 100, replace=TRUE, prob=c(0.9,0.02,0.02,0.02,0.02,0.02)), nc=10)
g2 = graph_from_adjacency_matrix(adjm, weighted=TRUE)




atxt = "Text processing is here to stay! A new lesson starts here!"
atxt.lines = strsplit(atxt,split="!") # break atxt into two sentences using splitting by ??!??
atxt.words = lapply(atxt.lines[[1]],strsplit,split=" ") # extract individual words
#(including blank space in front of second sentence)
atxt.wordvec = unlist(atxt.words) # creates just a vector of words
atxt.wordvec = atxt.wordvec[atxt.wordvec !=""] # remove the blank space
atxt.nopunc = paste(atxt.wordvec,collapse=" ") # put the words back together (without punctuation)


grep("new", atxt.wordvec) # returns indices of all the words in atxt that match with ??new??
grep("new", atxt) # returns 1 since the word ??new?? appears in atxt
grep("new", atxt.lines[[1]]) # returns 2 since ??new?? only appears in second sentence
grep("new", atxt.lines[[1]], value=T) # returns the matched second sentence
grep("new", atxt.lines[[1]], invert=T, value=T) # returns the non-matched first sentence


sub("new","old",atxt) # replaces ??old?? with ??new?? in atxt
sub("new","old",atxt.lines[[1]]) # replaces in matched string; leaves alone the non-matched string
btxt.wordvec = c("Text", "is", "repeated", "here", ";", "text", "again",
                 ",", "and", "more", "text", "!", "3", "times","!")
btxt = paste(btxt.wordvec, collapse=" ")
sub("text","rain",btxt, ignore.case=T) # only replaces the first occurrence of "text" with "rain??
gsub("text","rain",btxt, ignore.case=T) # replaces all the occurrences of "text" with "rain??
sub("text","rain",btxt, ignore.case=T) # every single word ??text?? in the vector is replaced by ??rain??