# gr-bad

DAB (Digital Audio Broadcasting (ETSI EN 300 401)) channel decoder.
Actually set of gnuradio blocks aiming to build DAB channel decoder.
Currently only mode I is supported and only RX part.

## How to build this module

First of all you will need all the required dependencies.
Most likely you have them already installed.
I am assuming that you already have gnuradio installed. If not, please do so first.

You can go to [Installing GR from Binaries](https://wiki.gnuradio.org/index.php/InstallingGR#From_Binaries)
or [Installing GR from Source](https://wiki.gnuradio.org/index.php/InstallingGR#From_Source)
depending on your needs.

By the way, I am using gnuradio 3.8.

Then, as with every gnuradio module we use cmake.

```
  $ mkdir build
  $ cd build
  $ cmake ..
  $ make
  $ sudo make install
  $ sudo ldconfig
```

## How can I listen to my favourite radio station

This is only channel decoder.
To listen to radio stations or to list available radio stations you will need additional packages. But more about that later.
As of now, you can pass fic or selected subchannel for further processing via posix fifo files (fifo sink block - gr::bad::fifo_sink)
or just save them to the file (file sink block - gr::blocks::file_sink).
Creating a fifo file is as easy as typing for example
```
  $ mkfifo fic.fifo
```
or
```
  $ mkfifo msc.fifo
```
The idea now is to use GStreamer to play for us our selected radio station.
When we have subchannel coded by mpeg1 layer 2 we can use following pipeline:
```
gst-launch-1.0 filesrc location=msc.fifo ! mpegaudioparse ! mpg123audiodec ! autoaudiosink
```
But what about DAB+ subchannels (these are HE AAC coded with additional DAB Plus Audio Super Frames wrapping).
I would give a try one of the following pipelines:
```
gst-launch-1.0 filesrc location=msc.fifo ! dabplusparse ! avdec_aac ! autoaudiosink
```
or
```
gst-launch-1.0 filesrc location=msc.fifo ! dabplusparse ! faad ! autoaudiosink
```
or even
```
gst-launch-1.0 filesrc location=msc.fifo ! dabplusparse ! fdkaacdec ! autoaudiosink
```
depending which aac decoder is present on your system (or depending on your flavours).
