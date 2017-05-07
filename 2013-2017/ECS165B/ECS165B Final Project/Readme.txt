Group Member: Haozhe Gu  999200555     Zhiyi Xu 999324428

We wants to claim HW4 and HW6's points

HW4: a) we support create table , insert row and select command
     b) We will add iterator in rewriter.c
     e) There are in total 7 rewrite rules in rewriter.c(And it's loadable)
     d) We support opearators in evalexpr in expression.c
     e) We respect the output column specification

HW6: a) Implement on-disk B-tree, will create .idx file for column marked KEY or Primary Key use -d to see detail of index
     b) We use getnextIscan for index selection
     c) The optimizer will try to optimize the tree when selectrow is present. It will shift the tree and also move column with index to 
	the first.Then add the range for getnextIscan.

Final Project:
     a) We keep statistics for each table and each .idx file and stored in data directory. Use -d option for HW6, the program will show these sta tistics.(you
	can open the program again after insertion to see the difference)
     b) We implement the join on format.(from T1, T2  OR  from T1 join T2 on cond)
     c) We support Group By with AVG and Count (projection line consist of group by columnname and arbitary number of aggregate functions)
     d) We support In operator
     e) We DID NOT finish this
     
     EXTRA CREDIT
     a) We implement Order By clauses
     b) We implement Distinct Modifier
     c) We allow different tables to reuse column names and use dot format for colname.
     d) End of the Readme.txt attached the error list

Tables: biz: 20,000 rows table
	movies: 500 rows 250 distinct rows  column: id, title, year 
	movies_ratings: 250 distinct rows  column: id, score 

Sample QUeries:

	Test scan selection:	select bizid, latitude,category,state as CA, city as CAcity from biz where state = 'CA';
	

	Test index selection:	select id, 2016-year as yearpast,title from movies where ( id<100) and (2016-year <10);
	

	Test Distinct:	select distinct id, 2016-year as yearpast,title from movies where ( id<100) and (2016-year <10);
			
			select distinct state, city from biz;

	
	Test Orderby:	select title,year from movies where (year>1900) and(year < 1950) order by title;
			
			select name, phone, state, city from biz where (state = 'CA') or (state = 'AK') order by city;
 
			
	Test Distinct & Orderby:	select distinct title,id, year from movies where (id<100) and (year >2000) order by title;		 
						
					select distinct state, city from biz where (state ='CA') or (state = 'AK') order by state;								
					
					
	Test Group by:	select state, count(city) as numcity from biz group by state;
						
			select year, count(title) as nummovies, avg(year) as avgyear from movies group by year;

	
	Test Group by & Orderby:	select year, count(title) as nummovies, avg(year) as avgyear from movies group by year order by nummovies;
				
					select state, count(city) as numcity from biz group by state order by numcity;	

	Test Join:	select movies.id, movies.title, movies.year, movies_ratings.score from movies join movies_ratings on movies.id = movies_ratings.id where(movies_ratings.score> 85) and (movies_ratings.score <91);
			
			select movies.id, movies.title, movies.year, movies_ratings.score from movies, movies_ratings where movies_ratings.score>90;

			
	Test Join & Distinct & Orderby:	select distinct movies.id, movies.title, movies.year, movies_ratings.score from movies join movies_ratings on movies.id = movies_ratings.id where(movies_ratings.score> 85) and (movies_ratings.score <91) order by movies.title;

					select distinct movies.id, movies.title, movies.year, movies_ratings.score from movies, movies_ratings where movies.year > 2000 order by movies.title;
					
	Test in:	select id,title,year from movies where (year >2000) and( id in ( select id from movies_ratings where score>85 ) ) ;
			
	Test in & Distinct & Orderby:	select distinct id,title,year from movies where (year >2000) and( id in ( select id from movies_ratings where score>85 ) ) order by title;


Error Table:
ERROR: Table or index does not exist
ERROR: Too many files
::btree_insert: Error on insert
::init_btree: dont know how to do OP_%s
ERROR: null column invalid
ERROR: not a valid index column
::btree_insert: Read error on header block, should not happen
::btree_lookup: Cant read block, should not happen
B-Tree Index with one entry index block pointing at index block
::btree_alloc: Cant read header block
::btree_alloc: Insane free block number
::btree_insertr: Should never be asked to read block 0!
::btree_insertr: Cant read index block
::btree_insertr: Cant allocate space for split
::btree_insert: Error on insert
ERROR: not a valid index column
::readcsvhdr: Out of memory, should never happen
Cannot create database directory
ERROR: Table already exists
ERROR: Cannot create table
::define_table: Out of memory, should never happen
ERROR: Unknown system error
ERROR: Table does not exist
ERROR: Unknown server error
ERROR: Too few values
ERROR: Too many values
ERROR: Invalid command
ERROR: Invalid column name
ERROR: Output column does not exist
ERROR: Invalid column list
ERROR: Too many output columns
ERROR: Column used in WHERE clause does not exist
ERROR: Invalid WHERE clause
::csv_randomread: Cannot open table file
ERROR: Out of rows\n
ERROR: Cannot allocate a row element
ERROR: Not yet implemented (func)
ERROR: Column outside row context
ERROR: Column not found
invalid data is: %s
ERROR: Invalid data in pipeline
Invalid argument count
Invalid argument after IN
ERROR: Not yet implemented
Invalid argument count
Not yet implemented (string overload)
ERROR: Invalid table name in CREATE TABLE
ERROR: Invalid column def
ERROR: Invalid table name in INSERT command
ERROR: Not yet implemented (select)
ERROR: Not yet implemented (project)
ERROR: Cant find space for pipeline table column names
ERROR: Cant find space for output row
Bad projection spec
ERROR: It's not GROUP BY the: %s , PLEASE USE WITH AVG OR COUNT
ERROR: Not yet implemented (project data)
ERROR: Please select the GROUPBY COLNAME as the first selection
ERROR: Cant find space for pipeline table column names
ERROR: Cant find space for output row
::Bad list structure
ERROR: null table invalid
Invalid order by structure
ERROR: Invalid data in orderby
::insert_into_andchain: Normally, we should not get here
ERROR: Out of nodes
::opnum: unrecognized OP %s
Badly formed rule segment %s
Too many arguments in rule %s
::init_rules: Out of memory, should never happen here
failed OP_NULL

