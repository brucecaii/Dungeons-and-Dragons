## COMPILE + LINK + EXECUTE IN ONE COMMAND

```

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./thirdparty/ &&  export LD_LIBRARY_PATH && g++ -g *.cpp thirdparty/libcppunit.so -lsfml-graphics -lsfml-window -lsfml-system -I ./thirdparty -L ./thirdparty -o comp345build && ./comp345build


```
