#Jared Westmoreland
#System Programming
#10/6/2017

#!/bin/bash

bytes(){
	file=$1
	world=0

	if [ -z $file ]
	then
                echo 'The file is not readable'
	elif (( `find $file -readable | wc -l` != 0 ))
	then
		world=$[$world + `stat --printf="%s" "$file"`]
		printf $file
		printf " has "
		echo $world "bytes contained in the file"
	fi
}
stuff=0
here=0

if [ -z $1 ]
then
	echo 'Please put a an integer'
	read stuff
	for (( i=0; i<= $stuff; i++ ))
	do
		here=$[$stuff - $i]
		echo $here
	done
else
	bytes $1
fi

