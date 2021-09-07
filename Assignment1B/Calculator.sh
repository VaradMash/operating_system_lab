#	Author		:	Varad Girish Mashalkar
#	Roll Number	:	33337
#	Batch		:	L11
#	Date		:	19/08/2021
#	Version		:	1
#	Assignment	:	1B (Additional)
#	Course		:	Operating Systems Laboratory


while true; do
	echo "\n***************Menu***************"
	echo "\n1. Use bc\n2.Use expr\n3.exit"
	echo "\n**********************************"
	echo "Enter choice : "
	read eval_choice
	case "$eval_choice" in
		# Evalute operation using bc calculator.
		1)echo "Enter 1st number"
		read num1
		echo "Enter 2nd number"
		read num2
		while true; do
			echo "\nChoice of operands :"
			echo "1. +\n2. -\n3. \*\n4 \ \n5. %\n6Exit"
			echo "Enter choice of operand : "
			read operand_choice	
			case "$operand_choice" in 
		
				1)addition=`echo "$num1+$num2" | bc`
				echo "\n$num1 + $num2 = $addition";;
			
				2)difference=`echo "$num1-$num2" | bc`
				echo "\n$num1 - $num2 = $difference";;
			
				3)product=`echo "$num1*$num2" | bc`
				echo "$num1 X $num2 = $product";;
			
				4)division=`echo "$num1/$num2" | bc`
				echo "$num1 / $num2 = $division";;
			
				5)modulo=`echo "$num1%$num2" | bc`
				echo "$num1 % $num2 = $modulo";;
			
				6)break;;
				
				*) echo "\nInvalid choice !";;
			
			esac
		done;;
		# Evaluate expression using expr command.
		2)echo "Enter 1st number"
		read num1
		echo "Enter 2nd number"
		read num2
		while true; do
			echo "\nChoice of operands :"
			echo "1. +\n2. -\n3. \*\n4 \ \n5. %\n6. Exit"
			echo "Enter choice of operand : "
			read operand_choice
			echo "\nResult : "
			case "$operand_choice" in 
		
				1)addition=`expr $num1 + $num2`
				echo "\n$num1 + $num2 = $addition";;
			
				2)difference=`expr $num1 - $num2`
				echo "\n$num1 - $num2 = $difference";;
			
				3)product=`expr $num1 "*" $num2`
				echo "$num1 X $num2 = $product";;
			
				4)division=`expr $num1 / $num2`
				echo "$num1 / $num2 = $division";;
			
				5)modulo=`expr $num1 % $num2`
				echo "$num1 % $num2 = $addition";;

				6)break;;

				*) echo "\nInvalid choice !";;
			
			esac
		done;;
		
		3)echo "Thank you !"
		exit;;
		
		*) echo "Invalid choice !";;
		
	esac
done