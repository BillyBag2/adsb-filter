# adsb-filter

A geographical filter for a "basestation" ADS-B stream. Pipe the stream through the filter and only messages for planes in the region of interest will get through.

Use net cat (`nc`) commands to manage the streams.

For entertainment only. Not to be used for anything important.

# Prerequisites

 ```
 apt-get install build-essential
 ```

# Building

Build...
```
make
```
Clean build...
```
make clean
make
```
## Know build issues

* No include file dependency checking. Use `make clean` until fixed.

# Known SW issues

* At time of writing the region of ineterst was the "U.K".  Would be nice to add more regions. Perhaps as command line parameters.

* At time of writing the region of interest was a simple single "rectangle" is angular coordinate space. The code could be changed so a more complex region could be made up of a number of "rectangles".

* Error handling may need some improvement.

* Only tested on a decompressed VirtualRadar stream. Streams from other sources may not be compatable.

# tools

## Net cat

Read a tcpip stream to stdout.

```
nc <host1> <port1> | adsb-filter | nc <host2> <port2>
```

Setup a push reciever in VirtualRadar.

# Under the hood

Regions are a "rectangle" in a angualar coordinate space. They cannot cross the date line.
