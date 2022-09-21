# mock-up v2

### To run
> :warning: This assumes are connected to the NAU VPN and
have necessary dependencies installed (openCV-python, Flask)

This mock-up version has two programs, one for turret cam 0 and 1. They should both 
get executed at the same time via the user and will display our results on localhost
127.0.0.1:5000 and 127.0.0.1:5001 respectively. The idea is to have a new program for 
each camera and perhaps increment the port number by 1. All programs are able to utilize
the same index.html but since both programs are required to run simultaneously, we cannot
populate the same IP and PORT.

```
git clone git@github.com:DiscoverCCRI/ip_cam.git
cd /mock-2
python3 turret01.py
python3 turret02.py
```

our common errors persists:
```
[hevc @ 0x7f76ec02aec0] The cu_qp_delta -47 is outside the valid range [-26, 25].
[hevc @ 0x7f76f4044f40] Could not find ref with POC 5
```
but occur a bit less. This is tricky because both programs are trying to use 100% of the 
machines resources which results in lag itself. 


![example](https://github.com/DiscoverCCRI/ip_cam/blob/main/imgs/mockup-2.png)

