#!/bin/bash

function CreateRecord(){ 
	read -p "Enter Employee ID : " id
	read -p "Enter Employee Name : " name
	read -p "Enter Employee Location : " location
	echo " "
	
	#"-c" in grep command is used to return the count of number of matching lines
	record=$(grep -c $id "employee_records.txt")
	if [ $record -eq 0 ]
	then 
		echo "$id         $name          $location" >> employee_records.txt
		echo "Recorded created successfully !!"
	else "Employee already exists."
	fi
}

function DeleteRecord(){
	echo " "
	read -p "Enter the Employee Id that needs to be deleted : "  Id
	record=$(grep -c $Id "employee_records.txt")
	echo " "
	if [ $record -eq 0 ]
	then 
		echo "Record with $Id doesn't exists."
	else	
	#"-v" in grep command is used to print all lines that do not match a specific pattern of characters.
		grep -v "$Id" employee_records.txt>temp.txt && mv temp.txt employee_records.txt 
		echo "Record deleted successfully!!"
	fi
}

function SearchRecord(){
	echo " "
	read -p "Enter the Employee Id/Name/Location that needs to be searched : " search
	record=$(grep -c $search "employee_records.txt")
	if [ $record -eq 0 ]
	then 
		echo "Record with Id/Name/Location $search doesn't exists."
	else
	#"-w" in grep command is used to find and print the results for whole words only.
	#"-i" in grep command is used to ignore case in grep searches.
	echo " "
	echo "ID        NAME          LOCATION"
	echo "________________________________"
	grep -wi $search "employee_records.txt"
	echo "________________________________"
	fi
}

function DisplayRecord(){
	echo " "
	echo "ID        NAME          LOCATION"
	echo "________________________________"
	cat employee_records.txt
	echo "________________________________"
}

function SortRecord(){
	sort employee_records.txt > temp.txt 
    mv temp.txt employee_records.txt
    echo "All records have been sorted."
}

while true;
do
echo " "
echo "***********MENU***********"
echo "Enter Your Choice : "
echo "1. Create Employee Record"
echo "2. Delete Employee Record"
echo "3. Search Employee Record"
echo "4. Display Employee Record"
echo "5. Sort Employee Record"
echo "6. Exit"
echo "**************************"
read -p "Enter your choice :  " choice 
echo " "

case $choice in

1)  CreateRecord
;;

2)  DeleteRecord
;;

3)	SearchRecord
;;

4)	DisplayRecord
;;

5)	SortRecord
;;

6)	exit
;;

*)
echo "You have entered a wrong choice"
;;

esac
done
