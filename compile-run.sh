#! /bin/sh
# script to compile and run our program. using just makefiles if a pain :(

# rebuild our program 
make compile 

# run but with arguments passed in
./bin/run/transforms-001 "$@"


