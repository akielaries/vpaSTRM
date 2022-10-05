#! /bin/sh
# script to compile and run our program. using just makefiles is a pain :(

# rebuild our program 
make compile 

# run but with arguments passed in and 
# write errors and normal output to log file


# run bin, display to console AND write to .txt file
#./bin/run/convert-001 "$@" | tee logs/STDOUT-001.txt
./bin/run/vpaSTRM-001 "$@" 

# run bin, display stderr and stdout to seperate files


