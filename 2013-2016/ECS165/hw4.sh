#! /bin/bash

echo "Start shell script for ECS165 HW4"
start_postgres 
echo "Start compile files"

g++ -o query -Wall -lpqxx -lpq Query.cpp
g++ -o table -Wall -lpqxx -lpq Settable.cpp

echo "Setting Tables"

table

echo "running query"
query

echo "About to remove programs"
rm  query table
