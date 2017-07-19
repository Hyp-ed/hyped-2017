#! /bin/bash


# enter the desired brakes extension in mm
read -p 'Enter distance to be achieved: ' TARGET_DIST

# runs the python script to do a single distance measurement
# distance recorded in details.txt
python proxisensorSTtest.py
# waits for 1 second, can be commented out
sleep 1
# assign the distance in the text file to a variable
CURR_DIST=$(cat distance.txt)
echo "Current distance is: $CURR_DIST"

# extend and retract brakes until desired distance is reached
while [ $CURR_DIST != $TARGET_DIST ]
do
# if distance is less - retract the brakes
	if [[ $CURR_DIST -lt $TARGET_DIST ]]
	then
		# run the c-file calling retract_one function
		./hyd_control retract
		# keep retracting for 0.1 second, change delay if necessary
		# don't know how fast the physical system works
		sleep 0.1
		# hold the brakes in current state to take another measurement
		./hyd_control hold
		# can be reduced to less tha a second, sensor is fast
		sleep 1
		# take measurement
		python proxisensorSTtest.py
		#sleep 5
		CURR_DIST=$(cat distance.txt)
		echo $CURR_DIST
		# can be commented out, for testing purposes
		#sleep 5

# if greater than desired - extend
	elif [[ $CURR_DIST -gt $TARGET_DIST ]]
	then
		# run the c file. COMPLETE the extend function first
		./hyd_control extend
		# keep extending for 0.1 sec
		# change if necessary
                sleep 0.1
                ./hyd_control hold
		sleep 1
		# take another measuremnt
                python proxisensorSTtest.py
		#sleep 5
                CURR_DIST=$(cat distance.txt)
		echo $CURR_DIST
		#sleep 5
	else
		echo "\nTarget distance achieved"
	fi
	echo "\nTarget distance achieved"
done

