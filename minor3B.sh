#Jared Westmoreland
#3600 Systems Programming
#10/1/2017
#Gives information of the files in current folder

#!/bin/bash

#variables
count=0
fake=0
exe=0
cool=0
hello=0;
world=0;
plus=0;

#if user input does not exist
if [ -z $1 ]
then
	#count the directory files
	for (( i = 1; i <= `find . -mindepth 1 -maxdepth 1 -type d | wc -l` ; i++ ))
	do
		count=$[$count + 1]
	done
	#Give total amount of Executables
	exe=`find . -type f -perm +111 | wc -l`
	#Give total amount of readable files by subtracting other files from the total amount
	cool=$[ `ls -l | wc -l` - $count - $exe - 1]
	#This does not work, but this was me trying to find the amount of bytes
	for (( j = 1; j <= `ls -l | wc -l`; j++))
	do
		if [ -z $file ]
		then
			: #basically kills the if statement so it can go on to the next one
		elif [ -d $file ]
		then
			:
		elif (( `find $file -type f -perm +111 | wc -l` != 0 ))
		then
			:
		elif (( `find $file -not -executable | wc -l` != 0 ))
		then
			plus=`stat -c%s *`
			world=$[$world + $plus]
		fi
	done
#this the user input exists
else
	#go to a for loop
	for (( j = 1; j <= `ls -l | wc -l`; j++ ))
	do
		#store the user input to the nth in file
		file=("${@:j:1}")
		#if file does not exist break the loop
		if [ -z $file ]
		then
			break
		#if it finds a directory file add 1
		elif [ -d $file ]
		then
			count=$[$count + 1]
		#if it finds an executable file add 1
		elif (( `find $file -type f -perm +111 | wc -l` != 0 ))
		then
			exe=$[$exe + 1 ]
		#if it finds and ordinary file add 1
		elif (( `find $file -not -executable | wc -l` != 0))
		then
			cool=$[$cool + 1]
			#adds the total amount of bytes in a readable file
			world=$[$world + `stat --printf="%s" $file`]
		else
			#counts the non-existent file if the user inputs one
                        fake=$[$fake + 1 ]
		fi
	done
fi


#display
echo '================= file data ================='
echo 'ordinary, readable, executable files : '$exe
echo 'non-existent or other types of files : '$fake
echo 'directory files                      : '$count
echo 'ordinary and readable files          : '$cool
echo 'total bytes in ordinary files        : '$world
