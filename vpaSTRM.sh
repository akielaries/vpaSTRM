#! /bin/sh
# script to compile and run our program. using just makefiles is a pain :(

# rebuild our program 
make compile 

# run but with arguments passed in and 
# write errors and normal output to log file

#./bin/run/convert-001"$@" #2>logs/ERROR-001.txt 1>logs/TEST_LOG-001.txt
./bin/run/convert-001 2>logs/ERROR-001.txt 1>logs/TEST_LOG-001.txt

