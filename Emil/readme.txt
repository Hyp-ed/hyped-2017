This set of programs is able to retract, extend and hold the brakes 
until the desired separation is achieved.
User is prompted to enter the separation when main_script.sh is run.

To run the the script:

cd /hyped/hydr_test
./main_script.sh

Main script runs different files (proxiTtest.py and hyd_control.c)

If you want to modify the solenoids being activated uring retraction,
extension or hold, modify hyd_control.c

To edit:
sudo nano hyd_control.c
Ctrl + o to save
Ctrl + x to exit

If hyd_control.c is modified, it needs to be compiled afterwards.
To compile:
gcc -Wall -o hyd_control hyd_control.c -lwiringPi 

Python file is the sensor driver, DO NOT MODIFY

If issues with file permissions:
sudo chmod 777 filename