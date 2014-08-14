wbt202-config
=============

Command-line configuration tool for the Wintec WBT 202.


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

