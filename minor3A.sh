#Jared Westmoreland
#Making A Box
#9/30/2017
#CSCE3600 Minor3A

#!/bin/bash

#If the input is wrong
if [ -z $2 ]
then
echo 'usage: ./minor3A.sh height width'

#If both inputs are less than or equal to 1
elif (( $1 <= 1 || $2 <= 1))
then
echo 'error: height ('$1') and width ('$2') must be > 1'

#This is the display using loops
else
printf '+' #I learned using printf does not use new line like echo
for (( j = 2; j < $2; j++ ))
do
printf '-'
done
echo '+'

#This is the height
for (( i = 2; i < $1 ; i++ ))
do
printf '|'
	#This is the space between the edges
	for (( j = 2; j < $2; j++ ))
	do
	printf ' '
	done
echo '|'
done

#Lastly this is the bottom
printf '+'
for (( j = 2; j < $2; j++ ))
do
printf '-'
done
echo '+'

fi
