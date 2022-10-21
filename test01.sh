#! /bin/sh
# script to compile and run our program. using just makefiles is a pain :(

# rebuild our program 
#../make compile 

# run but with arguments passed in and 
# write errors and normal output to log file


# run bin, display to console AND write to .txt file
# test 1

FLAGS1="-d ../cv-data/input/small_bunny_1080p_60fps-TRIM.mp4"
#./bin/run/vpaSTRM-110 $-d $cv-data/input/small_bunny_1080p_60fps-TRIM.mp4
./bin/run/vpaSTRM-110 >> echo "$FLAGS1"


# run bin, display stderr and stdout to seperate files

