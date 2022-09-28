#! /bin/sh
# script to compile and run our program. using just makefiles if a pain :(

# rebuild our program 
make compile 

# run but with arguments passed in and 
# write errors and normal output to log file
./bin/run/transforms-001 "$@" 2>logs/ERROR-001.txt 1>logs/TEST_LOG-001.txt


