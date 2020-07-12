# gr-bad

DAB (Digital Audio Broadcasting (ETSI EN 300 401)) channel decoder.
Actually set of gnuradio blocks aiming to build DAB channel decoder. 
Currently only mode I is supported and only RX part.

## How to build this module

As with every gnuradio module we use cmake.

$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
$ sudo ldconfig

## How can I listen to my favourite radio station

This is only channel decoder. 
To listen to radio stations or to list available radio stations you will need additional packages. But more about that later.


