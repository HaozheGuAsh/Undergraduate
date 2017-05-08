scatterplot(mpg ~ wt | cyl, data = mtcars, lwd=2,
            main = "Scatter plot of MPG vs Weight byof Cylinders",
            xlab = "Weight of car (in 1000 lbs)", ylab = "Miles per Gallon",
            legend.plot = TRUE, legend.coords = "topleft",# adds legend and controls its position
            boxplot = "xy", # adds boxplots of wt and mpg on margins of x and y axes
            span = 0.9, # controls degree of smoothing for lowess smoother
            id.method = "identify", # allows us to identify points by their labels
            lty = 2,
            labels=row.names(mtcars)) # row names are to be used as labels


scatterplotMatrix( ~ mpg + disp + drat + wt | cyl , data = mtcars,
                   spread=FALSE, span = 0.8,lty = 2, diagonal = "histogram",
                   main = "Scatter plot matrix grouped by # cylinders")





library(scatterplot3d)
cars.s3d = scatterplot3d(wt, disp, mpg,
                         scale.y = 1, angle = 40, highlight.3d = TRUE, type="h",
                         main = "3D scatter plot of wt (x), disp (y) and mpg (z) with lines and regression plane")
cars.fit = lm(mpg ~ wt + disp)
cars.s3d$plane3d(cars.fit)


library(rgl)
plot3d(wt, disp, mpg, col="red", size=5)


z = 5 * volcano # Exaggerate the relief of a volcano surface (data volcano is part of rgl package)
x =10 * (1:nrow(z)) # 10 meter spacing (S to N)
y = 10 * (1:ncol(z)) # 10 meter spacing (E to W)
persp3d(x, y, z, col = "blue", aspect = "iso") # perspective plot of surface z on the grid of x and y




rad = sqrt(disp/pi)
symbols(wt, mpg, circle=rad, inches=0.3, fg = "white", bg = "lightblue",
        main = "Bubble plot with bubble size proportional to displacement",
        ylab = "Miles per Gallon",xlab = "Weight of car (in 1000 lbs)")




cov(mtcars) # covariance matrix of variables in mtcars
cor(mtcars) # correlation matrix of variables in mtcars
library(corrgram)
corrgram(mtcars, order = TRUE, lower.panel = panel.shade, upper.panel= panel.pie,
         text.panel = panel.txt, main = "Correlogram of mtcars data")



corrgram(mtcars, order = FALSE,
         lower.panel=panel.ellipse, upper.panel = panel.pts,
         text.panel = panel.txt,
         diag.panel = panel.minmax,
         main = "Correlogram of mtcars data")
         


n = 10000
c1 = matrix(rnorm(n, mean=0, sd = 0.5), ncol=2)
c2 = matrix(rnorm(n, mean=3, sd = 2), ncol=2)
datamat = as.data.frame(rbind(c1,c2))
# 10000 observations from mixture of two bivariate normals with equal mixture proportions
names(datamat) = c("x","y")
with(datamat,smoothScatter(x,y, bandwidth = 0.25, main="Scatterplot Colored by Smoothed Densities"))

library(hexbin)
bins = hexbin(datamat$x, datamat$y, xbins=50)
# argument xbins specifies the number of subvisions along x axis, which in turn
# determines the number of hexagonal bins
plot(bins, main = "Hexagonal binning with 10000 observations")




ftable(Titanic) # plot "flattened" table Titanic
library(vcd)
mosaic(Titanic, shade = TRUE, legend = TRUE)
mosaic(~ Class + Sex + Age + Survived, data = Titanic, shade = TRUE, legend = TRUE)
# order of variables (categorical) in the formula above determine the nesting of rectangles
mosaic(~ Class + Age + Survived, data = Titanic, shade = TRUE, legend = TRUE)
# plot corresponding to a subset of variables



data(mtcars) # cars data used earlier
library(ggplot2)
qplot(wt, mpg, data = mtcars, color = I("red"), size = I(2)) # scatterplot of mpg vs wt
qplot(wt, mpg, data = mtcars, color = cyl, size = I(2)) # color values determined by values of # the discrete variable cyl = # of cylinders
qplot(wt, mpg, data = mtcars, colour = factor(cyl), size = I(2)) # cyl used as factor
# add a scatterplot smoother and corresponding confidence band per level of the factor cyl
qplot(wt, mpg, data = mtcars, colour = factor(cyl), geom = c("point","smooth"))
# same as above, but the smoother is added as an additional layer
qplot(wt, mpg, data = mtcars, colour = factor(cyl)) + geom_smooth( )

# add a scatterplot smoother for the whole data but color the points for different levels of cyl
qplot(wt, mpg, data = mtcars, colour = cyl) + geom_smooth(span=2)
# add a scatterplot smoother for each level of cyl, and add corresponding confidence band
qplot(wt, mpg, data = mtcars, colour = factor(cyl)) + geom_smooth(span=2)
# fit regression line and plot confidence bands for the whole data (no subsetting)
qplot(wt, mpg, data = mtcars, colour = cyl) + geom_smooth(method = "lm")
# fit regression line for each level of cyl and plot corresponding confidence bands
qplot(wt, mpg, data = mtcars, colour = factor(cyl)) + geom_smooth(method = "lm")
# also adjust the thickness and transparency of the regression line
qplot(wt, mpg, data = mtcars, colour = cyl) + geom_smooth(method = "lm",size=2,alpha = I(1/5))




mtcars$label=row.names(mtcars)
qplot(wt, mpg, label=label, data = mtcars) +
  geom_point(colour = cyl, size = gear) +
  geom_smooth(method = "lm", alpha = I(1/5)) + geom_text(size=3)




# plot histogram of mpg with specified binwidth
qplot(mpg, data = mtcars, geom="histogram", binwidth=3)
# plot relative frequencies rather than counts by setting ..density.. as an argument
qplot(mpg, ..density.., data = mtcars, geom="histogram",binwidth=3)
# plot relative frequencies rather than counts by setting ..density.. as an argument
qplot(mpg, ..density.., data = mtcars, geom="histogram",binwidth=3)
# histogram subdivided according to the levels of factor(cyl)
qplot(mpg, data = mtcars, geom="histogram", binwidth=3, fill=factor(cyl))
# plot a kernel density estimate for mpg, bandwidth (bw) = 1.5, xlim sets the range of values
qplot(mpg, data = mtcars, geom="density",bw=1.5,xlim=c(5,50))


# plot a kernel density estimate for mpg, bandwidth (bw) = 1.5, xlim sets the range of values
qplot(mpg, data = mtcars, geom="density",bw=1.5,xlim=c(5,50))
# plot the kernel density estimates for mpg for the strata created by levels of factor(cyl)
qplot(mpg, data = mtcars, geom="density",bw=1.5,colour=factor(cyl),xlim=c(5,50))
# plot the density estimates for different strata in separate panels using the argument facets
# the formulate facets = . ~ cyl determines a lattice of plots with
# number of columns corresponding to the number of distinct values of cyl
qplot(mpg, data = mtcars, geom="density",bw=1.5,xlim=c(5,50),facets = . ~ cyl)



library(ggplot2)
data(mpg) # a data set on car milage
pl.mpg = qplot(displ,hwy,data=mpg, color=factor(cyl))
summary(pl.mpg) # gives a summary of pl.mpg as an object
print(pl.mpg) # or, simply pl.mpg , plots the graph
save(pl.mpg, "mpg_plot.Rdata") # you may specify the folder where you want to save
load("mpg_plot.Rdata")
         



data(diamonds)
pl.diam = ggplot(diamonds, aes(carat,price, color=cut))
bestscatter = geom_point(alpha=I(1/2), shape='.', size=I(4))
# controls appearance with specification of transparency, shape and size of the points, apart from color
bestfit = geom_smooth(method="lm", se=F, color=alpha("green",0.5), size=2)
# linear regression fit; se=T will add standard error bands, color and size control the fitted line
pl.diam + bestscatter + bestfit + scale_x_continuous(limits=c(0,4.5)) +scale_y_continuous(limits=c(0,25000))
# plots the points and adds regression fit of price on carat; also changes the scales of x and y axes




# plot the scatter plots corresponding different values of cut
pl.diam + bestscatter + facet_grid(cut ~ .)
# also fit regression line to each stratum
pl.diam + bestscatter + facet_grid(cut ~ .) + bestfit
# allow the scales of the different panels to be different;
# default: scale = "free"; other options "free_x", "free_y"
pl.diam + bestscatter + facet_grid(cut ~ ., scale="free") + bestfit
# perform log10 transform of the variables and add least square fits; also change the labels on the axes
pl.diam + geom_point() + scale_x_log10( ) + scale_y_log10( ) +
  xlab("log10(carat)") + ylab("log10(price)") + bestfit




dfx = data.frame(x=c(3,1,5,4), y=c(2,4,6,8), label=letters[1:4]) # data frame with 4 labeled rows and 2 columns
pl.dfx = ggplot(dfx,aes(x=x,y=y,label=label)) + xlab(NULL) + ylab(NULL)
pl.dfx + geom_bar(stat="identity") + xlab("bar") # bar plot
pl.dfx + geom_point() + xlab("point") # scatter plot
pl.dfx + geom_line() + xlab("line") # line plot (connecting points ordered by x-value)
pl.dfx + geom_area() + xlab("area") # area plot
pl.dfx + geom_path() + xlab("path") # path plot (connecting successive points using the order in which they appear)
pl.dfx + geom_text() + xlab("text") # adding text (label) to points
pl.dfx + geom_tile() + xlab("tile") # tiles around points
pl.dfx + geom_polygon() + xlab("polygon") # polygon formed by connecting successive points



depth.di = ggplot(diamonds,aes(depth)) + xlim(58,68)
# plot relative density histograms of depth stratified by different values of cut
depth.di + geom_histogram(aes(y=..density..), binwidth=0.2) + facet_grid(cut ~ .)
# plot histogram of depth with different colors representing the actual count for different values of cut
depth.di + geom_histogram(aes(fill=cut), binwidth=0.2, position = "stack")
                          # plot relative contribution of different levels of cut to each bin of the histogram for depth
depth.di + geom_histogram(aes(fill=cut), binwidth=0.2, position = "fill")
# plot the histogram of depth for different values of cut separately
depth.di + geom_histogram(aes(fill=cut), binwidth=0.2, position = "dodge")


depcut.di = ggplot(diamonds,aes(x=cut,y=depth))
depcut.di + geom_boxplot( ) # plots boxplots for depth stratified by cut
depcut.di + aes(color=cut) + geom_boxplot( ) # use different colors for different values of cut
depcut.di + aes(color=factor(clarity)) + geom_boxplot( ) # stratify further by categorical variable clarity
depcut.di + aes(color=cut) + geom_boxplot( ) + facet_grid(clarity ~ .) # plots in a column of panels
depcut.di + aes(color=cut) + geom_boxplot( ) + facet_grid(. ~ clarity) # plots in a row of panels
depcut.di + aes(color=cut) + geom_boxplot( ) + facet_wrap(~ clarity) # better arrangement of panels



# in the previous example, we can stratify according to values of clarity rather than cut
depcut.di + geom_boxplot(aes(group=clarity, color=clarity)) + scale_x_discrete("clarity",breaks=c())
# Another example involving a longitudinal data set
library(nlme) # load package nlme
data(Oxboys) # heights of boys in Oxford from the nlme package
boysOx = ggplot(Oxboys, aes(Occasion,height))
boysOx + geom_boxplot( ) # display boxplots stratified by Occasion
# overlay the plot with height trajectories, overriding original grouping by using Subject for grouping
boysOx + geom_boxplot( ) + geom_line(aes(group=Subject),color="steelblue")



# in the previous example, we can stratify according to values of clarity rather than cut
depcut.di + geom_boxplot(aes(group=clarity, color=clarity)) + scale_x_discrete("clarity",breaks=c())
# Another example involving a longitudinal data set
library(nlme) # load package nlme
data(Oxboys) # heights of boys in Oxford from the nlme package
boysOx = ggplot(Oxboys, aes(Occasion,height))
boysOx + geom_boxplot( ) # display boxplots stratified by Occasion
# overlay the plot with height trajectories, overriding original grouping by using Subject for grouping
boysOx + geom_boxplot( ) + geom_line(aes(group=Subject),color="steelblue")



td = ggplot(diamonds,aes(table,depth))
td + geom_point() # scatter plot too crowded because of too many observations
td + geom_jitter() # jitter plot
jit = position_jitter(width=0.1) # creates a position variable that ¡°jitters¡± the points over a specified width
td + geom_jitter(position=jit)
# also add transparency to the points for better visible effect
td + geom_jitter(position=jit,color=alpha("black",1/20))


di = ggplot(diamonds,aes(carat,price)) + xlim(1,3)
di + stat_bin2d(bins=20,na.rm=T) # bivariate histogram using square binning 20 x 20 bins
di + stat_bin2d(bins=20,na.rm=T,color="yellow") # adds yellow border to the bins
di + stat_bin2d(binwidth=c(0.02,200)) # bins are determined by the widths of the rectangular bins
di + stat_bin2d(binwidth=c(0.02,200), aes(fill=..density..)) # use relative frequency instead of count
di + stat_binhex(bins=20, na.rm=T) # use hexagonal binning rather than square bins
di + stat_binhex(binwidth=c(0.02,200), na.rm=T) + scale_fill_gradient(low="blue",high="red")
# changes the shape of the hexagonal bins and changes a color scale

di + geom_density2d(na.rm=T) # contour plot of the density estimator
# contour plot of the density together with scatter plot
di + geom_point(na.rm=T) + stat_density2d(na.rm=T)
di + stat_density2d(na.rm=T,aes(fill=..level..),geom="polygon") # surface plot of the density
# surface plot of the density with added transparency to the surface to make
# the points underneath visible; the points are themselves made transparent
di + geom_point(na.rm=T,size=1,alpha=I(1/10)) +
  stat_density2d(na.rm=T,aes(fill = ..level..,alpha=..level..), geom="polygon") +
  scale_fill_gradient(low="blue",high="red")



