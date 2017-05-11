# SE
So Easy C++ libarary

This library depends on libcurl and jsoncpp
So before you're going to use it, you should install the both third-part library

Note: 
    1. install libcurl
$: git clone https://github.com/curl/curl.git
$: cd curl
$: ./configure --prefix=/usr/local
$: make
$: make install

    2. install jsoncpp
$: git clone https://github.com/open-source-parsers/jsoncpp.git
$: cd jsoncpp
$: mkdir build
$: cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local  ..
$: make
$: make install

Then you can compile this library for your own applications

Before using this library, you need compile this library first by executing the following commands:

    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Release \
          -DCMAKE_INSTALL_PREFIX=/usr/local \
          ..
    make -j4 
    [sudo] make install
