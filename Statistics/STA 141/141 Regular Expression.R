atxt = "Text processing is here to stay! A new lesson starts here!"

# Use function strsplit() which splits the elements of a character vector
# into substrings according to the matches to substring split within them.

atxt.lines = strsplit(atxt,split="!")
atxt.words = lapply(atxt.lines[[1]],strsplit,split=" ")

# create a vector of words
atxt.wordvec = unlist(atxt.words)
atxt.wordvec = atxt.wordvec[atxt.wordvec !=""]  # remove the blank space ""
###########################################
## First encounter with regular expressions
############################################

loc.txn  = grep("[txn]",atxt.wordvec,ignore.case=T)

grep("[txn]",atxt.wordvec,ignore.case=T,value=T)

atxt.wordvec[loc.txn]

grep("[txn]",atxt.wordvec,ignore.case=T,value=T,invert=T)

#################
## Effect of using quantifiers

grep("[txn]?",atxt.wordvec,ignore.case=T,value=T)

grep("[txn]*",atxt.wordvec,ignore.case=T,value=T)

grep("[txn]+",atxt.wordvec,ignore.case=T,value=T)

grep("[txn]",atxt.wordvec,ignore.case=T,value=T)

## using quantifier {n}

btxt.wordvec = c("Text", "is", "repeated", "here", "Text", "again")
btxt = paste(btxt.wordvec, collapse=" ")

grep("[txn]{0}",btxt.wordvec,ignore.case=T,value=T)
grep("[txn]{1}",btxt.wordvec,ignore.case=T,value=T)
grep("[txn]{2}",btxt.wordvec,ignore.case=T,value=T)
grep("[txn]{3}",btxt.wordvec,ignore.case=T,value=T)

grep("[txn]{1,3}",btxt.wordvec,ignore.case=T,value=T)
#################################################################
# Revisiting some examples of string manipulation from Lecture 13
#################################################################

btxt.wordvec = c("Text", "is", "repeated", "here", ";", "text", "again", ",", "and", "more", "text", "!", "3", "times","!")
btxt = paste(btxt.wordvec, collapse=" ")

loc.txn  = grep("[txn]",atxt.wordvec,ignore.case=T)

grep("[txn]",atxt.wordvec,ignore.case=T,value=T)

atxt.wordvec[loc.txn]

grep("[txn]",atxt.wordvec,ignore.case=T,value=T,invert=T)

#################
## Effect of using quantifiers

grep("[txn]?",btxt.wordvec,ignore.case=T,value=T)

grep("[txn]*",btxt.wordvec,ignore.case=T,value=T)

grep("[txn]+",btxt.wordvec,ignore.case=T,value=T)

grep("[txn]",btxt.wordvec,ignore.case=T,value=T)

## using quantifier {n}

grep("[txn]{0}",btxt.wordvec,ignore.case=T,value=T)
grep("[txn]{1}",btxt.wordvec,ignore.case=T,value=T)
grep("[txn]{2}",btxt.wordvec,ignore.case=T,value=T)
grep("[txn]{3}",btxt.wordvec,ignore.case=T,value=T)

grep("[txn]{1,3}",btxt.wordvec,ignore.case=T,value=T)

#############
# using grouping

grep("(tex)?",btxt.wordvec,ignore.case=T,value=T)

grep("(tex)+",btxt.wordvec,ignore.case=T,value=T)

grep("[(tex)+]",btxt.wordvec,ignore.case=T,value=T)  # notice the implication of putting (tex)+ within []

###########

# find digits
grep("\\d",btxt.wordvec,ignore.case=T,value=T)

# find non-digits
grep("\\D",btxt.wordvec,ignore.case=T,value=T)

# find numeric characters

grep("[0-9]",btxt.wordvec,ignore.case=T)

# find alphabetical characters

grep("[a-zA-Z]",btxt.wordvec,ignore.case=F,value=T)

# find space characters

grep("\\s",btxt.wordvec,ignore.case=T,value=T)

grep("^\\s"," A new day",ignore.case=T,value=T) # finds leading space

grep("\\s$"," A new day",ignore.case=T,value=T) # finds trailing space
grep("\\s$"," A new day ",ignore.case=T,value=T) # finds trailing space

# find non-space  characters

grep("\\S",btxt.wordvec,ignore.case=T,value=T)

# find specific punctuation characters

grep("[(),;.?!%&~]",btxt.wordvec,ignore.case=T,value=T)

###################################
# Finding location of a match using regexpr() and gregexpr()

ctxt = "Gasoline is combustible. More so, when (it is) mixed with nitrate! Skeptical & confused, too?!"

regexpr("[(),;.?!%&~]",btxt)
gregexpr("[(),;.?!%&~]",btxt)

regexpr("[(),;.?!%&~]",ctxt)
gregexpr("[(),;.?!%&~]",ctxt)

######################################
# Introduction to package stringr
#####################################


library(stringr)

######################
## There are three string functions that are closely related to
## their base R equivalents, but with a few enhancements:
#
# str_c() is equivalent to paste(), but it uses the empty string (¡°¡±) as
#         the default separator and silently removes NULL inputs.
#
#	str_length() is equivalent to nchar(), but it preserves NA¡¯s (rather than giving
#         them length 2) and converts factors to characters (not integers).
#
#	str_sub() is equivalent to substr() but it returns a zero length vector if any
#         of its inputs are zero length, and otherwise expands each argument to
#         match the longest. It also accepts negative positions, which are
#         calculated from the left of the last character. The end position
#         defaults to -1, which corresponds to the last character.
#
# str_sub is equivalent to substr , but like str_sub it understands negative
# indices, and replacement strings not do need to be the same length as the
# string they are replacing.
#
## Three functions add new functionality:
#
#	str_dup() to duplicate the characters within a string.
#
#	str_trim() to remove leading and trailing whitespace.
#
#	str_pad() to pad a string with extra whitespace on the left, right, or both sides.
############


## Pattern matching

strings = c("apple", "219 733 8965", "329-293-8753",
            "Work: 579-499-7527; Home: 543.355.3679")
phone = "([2-9][0-9]{2})[- .]([0-9]{3})[- .]([0-9]{4})"

#	str_detect() detects the presence or absence of a pattern and returns a
#             logical vector (similar to grepl()).
#
# str_subset() returns the elements of a character vector that match a
#             regular expression (similar to grep() with value = TRUE).


str_detect(strings, phone)  # which strings contain the phone number

#	str_locate() locates the first position of a pattern and returns a numeric
#            matrix with columns start and end.
#
# str_locate_all() locates all matches, returning a list of numeric matrices.
#            Similar to regexpr() and gregexpr().

str_locate(strings, phone) # Where in the string is the phone number located?

str_locate_all(strings, phone)

#	str_extract() extracts text corresponding to the first match, returning a
#              character vector. str_extract_all() extracts all matches and
#               returns a list of character vectors.

str_extract(strings, phone) # What are the phone numbers?

str_extract_all(strings, phone)

#	str_match() extracts captured groups formed by () from the first match.
#            It returns a character matrix with one column for the complete match
#            and one column for each group.
#
# str_match_all() extracts capture groups from all matches and returns a list of
#            character matrices. Similar to regmatches().

str_match(strings, phone) # Pull out the three components of the match

str_match_all(strings, phone)

#	str_replace() replaces the first matched pattern and returns a character vector.
#
# str_replace_all() replaces all matches. Similar to sub() and gsub().

str_replace(strings, phone, "XXX-XXX-XXXX")

str_replace_all(strings, phone, "XXX-XXX-XXXX")

#	str_split_fixed() splits the string into a fixed number of pieces based on
#             a pattern and returns a character matrix.
#
# str_split() splits a string into a variable number of pieces and returns
#             a list of character vectors.

###########################################
## Regular expression for specific features
###########################################

## US zip code

regex.zip = "\\d{5}(-\\d{4})?"

grepl(regex.zip,c("92045","81234-1240","95618-0020","956182353","95618 "))

regex.zip2 = "^\\d{5}(-\\d{4})?$"    # only the zip code and nothing else

grepl(regex.zip2,c("92045","81234-1240","95618-0020","956182353","95618 "))

## US Currency

regex.curr = "\\$(\\d{1,3}(\\,\\d{3})*|\\d+)(\\.\\d{1,2})?"  ## up to two digits after decimal (optional)

grepl(regex.curr,c("$120","$175,124.11","$202.1","$.95","$100,000,000,000.01"))

## Date: MM/DD/YYYY or MM/DD/YY  or MM-DD-YYYY or MM-DD-YY

regex.date = "(\\d{1,2})[\\/-](\\d{1,2})[\\/-](\\d{2}|\\d{4})"

grepl(regex.date,c("11/08/16","11-08-2016","11/8/16","11-08-16","11-8-16","11/8-16"))
# notice that the last string is also being regarded as a date, which may not be correct

regex.date2 = "(\\d{1,2})(\\/|-)(\\d{1,2})(\\2)(\\d{2}|\\d{4})"  # using back reference option

grepl(regex.date2,c("11/08/16","11-08-2016","11/8/16","11-08-16","11-8-16","11/8-16"))

regex.date3 = "(\\d{1,2})(\\/|-)(\\d{1,2})(\\2)((?!\\d{4})\\d{2}|\\d{4})"
# using back reference together with "negative lookahead", only available with perl=TRUE

grepl(regex.date3,c("11/08/16","11-08-2016","11-08-16","11-08-16","11-8-16","11/8-16"),perl=T)

##################################
## Lookaround
##
## Lookarounds are non-capturing groups that match patterns based on what they
## find either in front or behind a pattern. Lookarounds are also considered zero-width assertions
##
## Positive lookahead : (?=regex1)regex2
##        Match regex2 only if regex1 matches. But after matching regex1, discard that and
##        search for regex2 in the same position.
##
## Negative lookahead : (?!regex1)regex2
##
## Positive lookbehind : (?<=regex1)regex2
##
## Negative lookbehind : (?<!regex1)regex2
################################

## Time:  HR:MIN am (or pm)

regex.time = "([0-9]{1,2}):([0-9]{2})(\\s?)(am|pm|)"

grepl(regex.time,c("9:30 am","12:30 pm","1am","2:22pm","12:00")) # could not match "1am"

regex.time2 = "([0-9]{1,2})(:[0-9]{2})?(\\s?)(am|pm)"  ## make specification of minutes optional

grepl(regex.time2,c("9:30 am","12:30 pm","1am","2:22pm","12:00"))

## Email address

regex.email = "([0-9a-zA-z]+)([-.][0-9a-zA-z]+)*@([0-9a-zA-z]+([-][0-9a-zA-z]+)*\\.)+([a-zA-z]{2,9})"  ## updated version

grepl(regex.email,c("debpaul@ucdavis.edu","aperson-who123@gmail.com","whois99@oxford.ac.uk","is-this-email?@gmail.com"))

## HTTP, HTTPS, FTP or FTPS  URL

regex.url = "(https?|ftps?)(:\\/{2})([0-9a-zA-Z]+[0-9a-zA-Z-]*[0-9a-zA-Z]\\.)+([a-zA-Z]{2,9})"  # updated version

grepl(regex.url,c("https://example.com","http://www.ucdavis.edu","ftp://example.com","http://www-stat.stanford.edu","http://www.bbc.co.uk","http://bad-.com"))

regex.url.ecg = "(https?|ftp)(:\\/{2})([0-9a-zA-Z]+[0-9a-zA-Z-]*[0-9a-zA-Z]\\.)+(edu|com|gov)"  # educational or commerial or government institution in US

grepl(regex.url.ecg,c("https://example.com","http://www.ucdavis.edu","ftp://example.com","http://www-stat.stanford.edu","http://www.bbc.co.uk","http://bad-.com"))


####################################################
## Exercise : Extracting data from a (fictitious) email message
####################################################
## Extract the following information from the text provided below:
## email address, url, dollar amount, date, time, zip code, phone number.
## In each case, please indicate the line of text and the location within
## the line where the pattern occurred.


amsg =
  "Sender: Dxyz123@ucdavis.edu
Recipient: aperson-whois@aol.com
Subject: online transaction

I wanted to inform you that on 11/01/2016 at
6:21 pm I made a wire transaction to your account
through the Bank of
America website at https://www.bankofamerica.com
for the following amount:    $175.06
The payment is for sending me the books I requested
and which were sent to my address on 10/27/16.

DXYZ

5th Street
Davis, CA 95616
Phone 530-000-0001
"
## 11-10-2016
## STA 141A
## Lecture 15 codes

#######################
## Exercise from the last lecture
##################

## Extract the following information from the text provided below:
## email address, url, dollar amount, date, time, zip code, phone number.
## In each case, please indicate the line of text and the location within
## the line where the pattern occurred.


amsg =
  "Sender: Dxyz123@ucdavis.edu
Recipient: aperson-whois@aol.com
Subject: online transaction

I wanted to inform you that on 11/01/2016 at
6:21 pm I made a wire transaction to your account
through the Bank of
America website at https://www.bankofamerica.com
for the following amount:    $175.06
The payment is for sending me the books I requested
and which were sent to my address on 10/27/16.

DXYZ

5th Street
Davis, CA 95616
Phone 530-000-0001
"

###########################################
## Regular expression for specific features
###########################################

## US zip code

regex.zip = "\\d{5}(-\\d{4})?"
regex.zip2 = "^\\d{5}(-\\d{4})?$"    # only the zip code and nothing else

## US Currency

regex.curr = "\\$(\\d{1,3}(\\,\\d{3})*|\\d+)(\\.\\d{1,2})?"  ## (updated) up to two digits after decimal (optional)

strings.cr = c("$120","$175,124.11","$1.29","1a.38","1a .38","$202.1","$.95","$100,000,000.01")
grepl(regex.curr,strings.cr)
grep(regex.curr,strings.cr,value=T)

## Date: MM/DD/YYYY or MM/DD/YY  or MM-DD-YYYY or MM-DD-YY

regex.date = "(\\d{1,2})[\\/-](\\d{1,2})[\\/-](\\d{2}|\\d{4})"

strings.dt = c("11/08/16","11-08-2016","11/8/16","11-08-16","11-8-16","11/8-16")
grepl(regex.date,strings.dt)
# notice that the last string is also being regarded as a date, which may not be correct

regex.date2 = "(\\d{1,2})(\\/|-)(\\d{1,2})(\\2)(\\d{2}|\\d{4})"  # using back reference option
grepl(regex.date2,strings.dt)

regex.date3 = "(\\d{1,2})(\\/|-)(\\d{1,2})(\\2)((?!\\d{4})\\d{2}|\\d{4})"
# using back reference together with "negative lookahead", only available with perl=TRUE

grepl(regex.date3,strings.dt,perl=T)

##################################
## Lookaround
##
## Lookarounds are non-capturing groups that match patterns based on what they
## find either in front or behind a pattern. Lookarounds are also considered zero-width assertions
##
## Positive lookahead : (?=regex1)regex2
##        Match regex2 only if regex1 matches. But after matching regex1, discard that and
##        search for regex2 in the same position.
##
## Negative lookahead : (?!regex1)regex2
##
## Positive lookbehind : (?<=regex1)regex2
##
## Negative lookbehind : (?<!regex1)regex2
################################

## Time:  HR:MIN am (or pm)

regex.time = "([0-9]{1,2}):([0-9]{2})(\\s?)(am|pm|)"
regex.time2 = "([0-9]{1,2})(:[0-9]{2})?(\\s?)(am|pm)"  ## make specification of minutes optional

strings.tm = c("9:30 am","12:30 pm","1am","2:22pm","12:00")
grepl(regex.time,strings.tm)
grepl(regex.time2,strings.tm)

## Email address

regex.email = "([0-9a-zA-z]+)([-.][0-9a-zA-z]+)*@([0-9a-zA-z]+([-][0-9a-zA-z]+)*\\.)+([a-zA-z]{2,9})"  ## updated version

strings.em = c("debpaul@ucdavis.edu","a.student@yahoo.com","a.person-who123@gmail.com",
               "whois99@oxford.ac.uk","is-this-email?@gmail.com","is-this-@gmail.com")
grepl(regex.email,strings.em)

## HTTP, HTTPS, FTP or FTPS  URL

regex.url = "(https?|ftps?)(:\\/{2})([0-9a-zA-Z]+[0-9a-zA-Z-]*[0-9a-zA-Z]\\.)+([a-zA-Z]{2,9})"  # updated version
regex.url.ecg = "(https?|ftp)(:\\/{2})([0-9a-zA-Z]+[0-9a-zA-Z-]*[0-9a-zA-Z]\\.)+(edu|com|gov)"  # educational or commerial or government institution in US

strings.url = c("https://example.com","http://www.ucdavis.edu","ftp://example.com","http://www-stat.stanford.edu","http://www.bbc.co.uk","http://bad-.com")
grepl(regex.url,strings.url)
grepl(regex.url.ecg,strings.url)

## Phone number

regex.phone = "([2-9][0-9]{2})[- .]([0-9]{3})[- .]([0-9]{4})"

###################

amsg.ln = unlist(strsplit(amsg,split="\\n"))

str_extract_all(amsg.ln,regex.url)  # url
str_extract_all(amsg.ln,regex.email) # email
str_extract_all(amsg.ln,regex.curr)  # currency
str_extract_all(amsg.ln,regex.zip) # zipcode
str_extract_all(amsg.ln,regex.phone) # phone
str_extract_all(amsg.ln,regex.time2) # time
str_extract_all(amsg.ln,regex.date2)  # not quite right

regmatches(amsg.ln,gregexpr(regex.date3,amsg.ln,perl=T))

###############################################
## Extracting data from HTML and XML files
############################################

## Several R packages can be used to extract information from html and xml files.
## xml can be seen as a more structured and enhanced version of html.

## RCurl package allows us to download html and xml files directly into R.
## Reference:
## Temple Lang, D. (2007). ``R as web client - the RCurl package.''
##                     (available from http://www.omegahat.net/RCurl/RCurlJSS.pdf)

## XML package allows us to perform manipulations on html and xml files.
## Reference:
## Nolan, D. and Temple Lang, D. (2014). ``XML and Web Technologies for Data
##                                       Sciences with R.'' Springer.


library(RCurl)
library(XML)

#############################################
# Example 1 : Publications list (html)
############################################

# Save the URL of the html file in a variable

dplink = "http://anson.ucdavis.edu/~debashis/techrep/techrep.html"

# Use the htmlTreeParse() function to parse xml file directly from the web

dpdoc = htmlTreeParse(dplink)
class(dpdoc)

# names of different fields of dpdoc

names(dpdoc)
#[1] "file"     "version"  "children"

# names of the field "children" of "dpdoc"

names(dpdoc$children)
#[1] "comment" "html"

dpdoc$children$comment

names.XMLNode(dpdoc$children$html)  # same as names(dpdoc$children$html)
#  head   body
# "head" "body"

dpdoc.head = dpdoc$children$html[[1]]
dpdoc.body = dpdoc$children$html[[2]]

xmlValue(dpdoc.head)

xmlValue(dpdoc.body)

xmlChildren(dpdoc.head)[["meta"]]
xmlChildren(dpdoc.head)[["title"]]

xmlChildren(dpdoc.head)[[1]]
xmlChildren(dpdoc.head)[[2]]
xmlChildren(dpdoc.head)[[3]]


dpdoc.body[[1]]
dpdoc.body[[2]]

###########
## Description
#
# Function getNodeSet() provides a way to find XML nodes that match a particular
# criterion. It uses the XPath syntax and allows very powerful expressions to
# identify nodes of interest within a document both clearly and efficiently.
#
## Usage
#
# getNodeSet(doc, path, namespaces = xmlNamespaceDefinitions(doc, simplify = TRUE),
#                    fun = NULL, sessionEncoding = CE_NATIVE, addFinalizer = NA, ...)
#
## Arguments
#
# doc	: an object of class XMLInternalDocument
# path : a string (character vector of length 1) giving the XPath expression to evaluate.
# namespaces : a named character vector giving the namespace prefix and URI pairs that are
#             to be used in the XPath expression and matching of nodes. XML namespaces are
#             used for providing uniquely named elements and attributes in an XML document.
# fun	: function object, or an expression or call, which is used when the
#       result is a node set and evaluated for each node element in the node set. If this is
#       a call, the first argument is replaced with the current node.
#
## Value
#
# The results can be different (list, numeric, logical or a character string) based
# on the returned value from the XPath expression evaluation:
############

## Get the list of nodes of dpdoc.body that correspond to the filed "h1" (header)

dpdoc.body.headers = getNodeSet(dpdoc.body,path="//h1")  # list of headers

dpdoc.thesis = dpdoc.body[[2]] # thesis
dpdoc.jrl = dpdoc.body[[5]] # journal publications
dpdoc.disc = dpdoc.body[[8]] # discussions
dpdoc.book = dpdoc.body[[11]] # book chapters
dpdoc.conf = dpdoc.body[[14]] # conference proceedings
dpdoc.tech = dpdoc.body[[17]] # technical reports

## NOTE: We could get the same information by the following

dpdoc.fields = getNodeSet(dpdoc.body,path="//ul")

identical(dpdoc.jrl,dpdoc.fields[[2]]) ## TRUE

# extract journal publication information as a list

dpdoc.jrl.pub = getNodeSet(dpdoc.jrl,path="//li")

# extract journal names, volumes, pages of the journal publications

dpdoc.jrl.journal = getNodeSet(dpdoc.jrl,path="//li//i")

dpdoc.jrl.anchor = getNodeSet(dpdoc.jrl,path="//li//a")

# The function getHTMLLinks retrieves links within the html document
#
# Usage
#
# getHTMLLinks(doc, externalOnly = TRUE, xpQuery = "//a/@href",baseURL = docName(doc), relative = FALSE)

docName(dpdoc)
dpdoc.links = getHTMLLinks(dplink, externalOnly = TRUE, xpQuery = "//a/@href")

######################
## To extract the XML-values from the document, use xmlApply() or xmlSApply() together with xmlValue()
#
## NOTE: Description
# xmlApply() and xmlSApply() These methods are simple wrappers for the lapply() and sapply()
# functions. They operate on the sub-nodes of the XML node, and not on the fields
# of the node object itself.
#
## Usage
#
# xmlApply(X, FUN, ...) ## S3 method for class 'XMLNode'
# xmlApply(X, FUN, ...) ## S3 method for class 'XMLDocument'
#
# xmlSApply(X, FUN, ...) ## S3 method for class 'XMLNode'
# xmlSApply(X, FUN, ...) ## S3 method for class 'XMLDocument'
#
## Arguments
#
# X	: the XMLNode on whose children the regular lapply() or sapply() is to be performed
# FUN	: the function to apply to each child node. This is passed directly to the relevant apply function.
# ...	: additional arguments to be given to each invocation of FUN. This is passed directly to the relevant apply function.
#
## Value
#
# The result is that obtained from calling the lapply() or sapply() on xmlChildren(x).
######

# extract the journal names (including volume, pages) as a list

dodoc.journal.ls = sapply(1:length(dpdoc.jrl.journal), function(i) xmlValue(dpdoc.jrl.journal[[i]]))

# extract all the information (title, journal info, additional info) as list of lists

dpdoc.pub.ls = sapply(1:length(dpdoc.jrl.pub), function(i) xmlApply(dpdoc.jrl.pub[[i]],xmlValue))

#############################################
# Example 2 : Plant catalog (xml)
############################################

# save the URL of the xml file in a variable

plantlink = "http://www.w3schools.com/xml/plant_catalog.xml"

# Use the xmlTreeParse() function to parse xml file directly from the web

plantdoc = xmlTreeParse(plantlink)

# the xml file is now saved as an object you can easily work with in R:
class(plantdoc)

# Use the xmlRoot() function to access the top node
plant.top = xmlRoot(plantdoc)

# have a look at the XML-code of the first subnodes:
print(plant.top)[1:2]

# extract the XML-values from the document, use xmlSApply()

plant.catalog = xmlSApply(plant.top, function(x) xmlSApply(x, xmlValue))

plant.catalog.s = sapply(1:length(plant.top), function(i) xmlSApply(plant.top[[i]], xmlValue))  # does not give the intended result

# Finally, get the data in a data-frame and have a look at the first rows and columns

plant.catalog.df = data.frame(t(plant.catalog),row.names=NULL)
