#	Author		:	Varad Girish Mashalkar
#	Roll Number	:	33337
#	Batch		:	M11
#	Date		:	19/08/2021
#	Version	:	1
#	Assignment	:	1B
#	Course		:	Operating Systems Laboratory

address_book_name="addr.txt"
echo "\nThe default name of the address book has been set to $address_book_name by default"
echo "The name of the address book can be altered using the 6th Menu option."
while true; do

	echo "\n*****************Menu*****************"
	echo "1. Create address Book"
	echo "2. View Address Book"
	echo "3. Insert a Record"
	echo "4. Modify a Record"
	echo "5. Delete a Record"
	echo "6. Set address book target"
	echo "7. Exit"
	echo "**************************************"
	echo "\n Enter choice : "
	read choice_code
	case "$choice_code" in 
	
		# Create Address book if it does not exist, else display appropriate message.
		1)echo "Enter name of address book"
		read address_book_name
		while true; do
			if [ -z "$address_book_name" ]; 
			then
				echo "File name cannot be empty"
				echo "Please enter file name : "
				read address_book_name
			else
				break;
			fi
		done
		if test -f "$address_book_name"; 
		then
			echo "$address_book_name already exists !"
		else
			touch "$address_book_name"		
			echo "\nAddress book created !"	
		fi
		echo "The following list shows the contents of your current working directory : \n"
		ls ;;
		
		# View contents of address book if it exists, else create file.
		2)if test -f "$address_book_name";
		then 
			echo "\nContents of address book : $address_book_name"
			cat $address_book_name
		else
			echo "Creating address book with name $address_book_name"
			echo "The following list shows the contents of your current working directory : \n"
			ls 
		fi;;
		
		# Enter new record into the address book with input validation. (Primary key : Name)	
		3)echo "Enter name :" 
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
		search=`grep $name $address_book_name`
		len=`echo $search | wc -w`
		if test $len -gt 0;
		then
			echo "Record Already exists"
			echo "Consider modifying the record if the roll number is correct."
		else
			echo "Enter address : "
			read address
			while true; do
				if [ -z "$address" ];
				then
					echo "\nPlease Enter name !"
					read address
				else
					break
				fi
			done
			echo "Enter phone number"
			read phone_number
			while true; do
				if [ -z "$phone_number" ];
				then
					echo "\nPlease Enter name !"
					read phone_number
				else
					break
				fi
			done
			echo $name $address $phone_number | cat >> $address_book_name
			echo "New record inserted into address book"
		fi;;
		
		# Modify record if it exists, else display error message.
		4)echo "Enter name of person whose record is to be modified"
		read person_name
		original_record=`grep "$person_name" "$address_book_name"`
		len=`echo $original_record | wc -w`
		if test $len -gt 0;
		then
			echo "Enter updated record"
			echo "Enter name :" 
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
			echo "Enter address : "
			read address
			while true; do
				if [ -z "$address" ];
				then
					echo "\nPlease Enter name !"
					read address
				else
					break
				fi
			done
			echo "Enter phone number"
			read phone_number
			while true; do
				if [ -z "$phone_number" ];
				then
					echo "\nPlease Enter name !"
					read phone_number
				else
					break
				fi
			done
			echo "Original Record \t: $original_record"
			sed -i "s/$original_record/$name $address $phone_number/g" "$address_book_name"
			echo "Record found and modified !"
		else
			echo "No record found" 
		fi;;
		
		# Delete record.
		5)echo "Enter name of Person whose record is to be deleted"
		read person_name
		grep -v "$person_name" "$address_book_name" >> temp.txt
		mv temp.txt "$address_book_name"
		echo "\nContents of file are : \n"
		cat $address_book_name;;
		
		# Change working address books.
		6)echo "Enter name of address book to be accessed :"
		read address_book_name
		echo "Working address book set to $address_book_name";;
		
		# Exit loop.
		7)echo "\nThank You!"
		exit;;
		
		# Invalid input stage.
		*)echo "\nInvalid choice 1";;
		
	esac
done
