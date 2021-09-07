#	Author		:	Varad Girish Mashalkar
#	Roll Number	:	33337
#	Batch		:	L11
#	Date		:	19/08/2021
#	Version		:	1
#	Assignment	:	1B (Additional)
#	Course		:	Operating Systems Laboratory

studentDB_name="studentDB.txt"
echo "\nThe default name of the student database has been set to $studentDB_name by default"
echo "The name of the address book can be altered using the 6th Menu option."
while true; do

	echo "\n*****************Menu*****************"
	echo "1. Create new Student Database"
	echo "2. View Database"
	echo "3. Insert a Record"
	echo "4. Modify a Record"
	echo "5. Delete a Record"
	echo "6. Set Student Database targetr target"
	echo "7. Exit"
	echo "**************************************"
	echo "\n Enter choice : "
	read choice_code
	case "$choice_code" in 
	
		# Create Student Database if it does not exist, else display appropriate message.
		1)echo "Enter name of address book"
		read studentDB_name
		while true; do
			if [ -z "$studentDB_name" ]; 
			then
				echo "File name cannot be empty"
				echo "Please enter file name : "
				read studentDB_name
			else
				break;
			fi
		done
		if test -f "$studentDB_name"; 
		then
			echo "$studentDB_name already exists !"
		else
			touch "$studentDB_name"		
			echo "\nNew Student database created !"	
		fi
		echo "The following list shows the contents of your current working directory : \n"
		ls ;;
		
		# Display contents of Student database if it exists, else create database.
		2)if test -f "$studentDB_name";
		then 
			echo "\nContents of address book : $studentDB_name"
			cat $studentDB_name
		else
			echo "Creating address book with name $studentDB_name"
			touch $studentDB_name
			echo "The following list shows the contents of your current working directory : \n"
			ls 
		fi;;
			
		# Enter record into Database with input validations.
		# Check for primary key constraint on the file on roll number field.
		# Calculate Percentage and grade.
		3)echo "Enter Roll Number :" 
		read roll_number
		while true; do
			if test $roll_number -gt 0;
			then
				break			
			else
				echo "Please enter valid roll number : "
				read roll_number
			fi
		done
		search=`grep $roll_number $studentDB_name`
		len=`echo $search | wc -w`
		if test $len -gt 0;
		then
			echo "Record Already exists"
			echo "Consider modifying the record if the roll number is correct."
		else
			echo "Enter Name :" 
			read name
			while true; do
				if [ -z "$name" ];
				then
					echo "\nPlease Enter name !"
					read name
				else
					break
				fi
			done
			echo "Enter Marks in subject 1 : "
			read M1
			while true; do
				if [ $M1 -ge 0 ] && [ $M1 -le 100 ];
				then
					break
				else
					echo "Please enter valid marks (between 0 and 100 both inclusive)."
					read M1
				fi
			done
			echo "Enter Marks in subject 2 : "
			read M2
			while true; do
				if [ $M2 -ge 0 ] && [ $M2 -le 100 ];
				then
					break
				else
						echo "Please enter valid marks (between 0 and 100 both inclusive)."
					read M2
				fi
			done
			echo "Enter Marks in subject 3 : "
			read M3
			while true; do
				if [ $M3 -ge 0 ] && [ $M3 -le 100 ];
				then
					break
				else
					echo "Please enter valid marks (between 0 and 100 both inclusive)."
					read M3
				fi
			done
			total=`expr $M1 + $M2 + $M3`
			perc=`expr $total / 3`
			if [ $perc -le 100 ] && [ $perc -gt 90 ];
			then
				grade=O
			elif [ $perc -le 90 ] && [ $perc -gt 80 ];
			then
				grade=A
			elif [ $perc -le 80 ] && [ $perc -gt 70 ];
			then
				grade=B
			elif [ $perc -le 70 ] && [ $perc -gt 60 ];
			then
				grade=C
			elif [ $perc -le 60 ] && [ $perc -gt 50 ];
			then
				grade=D
			elif [ $perc -le 50 ] && [ $perc -ge 40 ];
			then
				grade=E
			else
				grade=Fail
			fi
			echo $roll_number $name $M1 $M2 $M3 $perc% $grade | cat >> $studentDB_name
			echo "New record inserted into address book"
		fi;;
		
		# Modify record if exists, else display error message
		4)echo "Enter Roll number of student whose record is to be modified"
		read roll_number
		original_record=`grep "$roll_number" "$address_book_name"`
		len=`echo $original_record | wc -w`
		if test $len -gt 0;
		then
			echo "Enter updated record"
			echo "Enter Roll Number :" 
			read roll_number
			while true; do
				if test $roll_number -gt 0;
				then
					break
				else
					echo "Please enter valid roll number : "
					read roll_number
				fi
			done
			echo "Enter Name :" 
			read name
			while true; do
				if [ -z "$name" ];
				then
					echo "\nPlease Enter name !"
					read name
				else
					break
				fi
			done
			echo "Enter Marks in subject 1 : "
			read M1
			while true; do
				if [ $M1 -ge 0 ] && [ $M1 -le 100 ];
				then
					break
				else
					echo "Please enter valid marks (between 0 and 100 both inclusive)."
					read M1
				fi
			done
			echo "Enter Marks in subject 2 : "
			read M2
			while true; do
				if [ $M2 -ge 0 ] && [ $M2 -le 100 ];
				then
					break
				else
					echo "Please enter valid marks (between 0 and 100 both inclusive)."
					read M2
				fi
			done
			echo "Enter Marks in subject 3 : "
			read M3
			while true; do
				if [ $M3 -ge 0 ] && [ $M3 -le 100 ];
				then
					break
				else
					echo "Please enter valid marks (between 0 and 100 both inclusive)."
					read M3
				fi
			done
			total=`expr $M1 + $M2 + $M3`
			perc=`expr $total / 3`
			if [ $perc -le 100 ] && [ $perc -gt 90 ];
			then
				grade=O
			elif [ $perc -le 90 ] && [ $perc -gt 80 ];
			then
				grade=A
			elif [ $perc -le 80 ] && [ $perc -gt 70 ];
			then
				grade=B
			elif [ $perc -le 70 ] && [ $perc -gt 60 ];
			then
				grade=C
			elif [ $perc -le 60 ] && [ $perc -gt 50 ];
			then
				grade=D
			elif [ $perc -le 50 ] && [ $perc -ge 40 ];
			then
				grade=E
			else
				grade=Fail
			fi
			echo "Original Record \t: $original_record"
			sed -i "s/$original_record/$roll_number $name $M1 $M2 $M3% $grade/g" "$address_book_name"
			echo "Record found and modified !"
		else
			echo "No record found" 
		fi;;
		
		# Delete record.
		5)echo "Enter Roll number of student whose record is to be deleted"
		read roll_number
		grep -v "$roll_number" "$studentDB_name" >> temp.txt
		mv temp.txt "$studentDB_name"
		echo "\nContents of file are : \n"
		cat $studentDB_name;;
		
		# Change current working StudentDB.
		6)echo "Enter name of Student DB to be accessed :"
		read studentDB_name
		echo "Working address book set to $studentDB_name";;
		
		# Exit loop
		7)echo "\nThank You!"
		exit;;
		
		# Invalid input stage.
		*)echo "\nInvalid choice 1";;
		
	esac
done
