wbt202-config
=============

[![Build Status](https://travis-ci.org/enpe/wbt202-config.svg?branch=master)](https://travis-ci.org/enpe/wbt202-config)

Command-line configuration tool for the [Wintec WBT-202 GPS Data Logger][1].

The device comes with the `WBT_Tool.exe` for changing the configuration. Unfortunately, this program only works on Windows and leaves non-Windows users with no simple way to configure their data logger since the configuration is stored in 3 undocumented binary files.

This project aims at documenting these configuration files and supplying a command-line tool for easily reading and writing them.


Building the project
--------------------

1. Clone the repository

        git clone git://github.com/enpe/wbt202-config.git
        cd wbt202-config
        git submodule init
        git submodule update

2. Build the project

        mkdir build
        cd build
        cmake ..
        make

    For building with debug information call cmake with the `-DDEBUG=1` option.


[1]: http://www.wintec-gps.de/wintec_wbt-202.php

