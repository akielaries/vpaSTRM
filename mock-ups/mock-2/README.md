# mock-up v2

### To run
> :warning: This assumes are connected to the NAU VPN and
have necessary dependencies installed (openCV-python, Flask)


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

