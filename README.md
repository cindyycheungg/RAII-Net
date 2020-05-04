# RAII-Net
Capture the flag like game written in C++ 

## Descripton 
This game can be run with XQuartz to enable graphics. 
To compile and run, you can use the option 
```
g++14 window.cc graphicsdemo.cc -o graphicsdemo -lX11 -L/usr/X11/lib -I/usr/X11/include

./graphicsdemo
```