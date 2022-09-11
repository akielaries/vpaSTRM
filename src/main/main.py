"""
py script to run our stream feed + port to localhost + proxy to ngrok
"""
import subprocess
import os

# run the programs
def main():
    subprocess.run('python3 public_v1.py & python3 proxy.py', shell = True)

if __name__ == '__main__':
    # run main
    main()


