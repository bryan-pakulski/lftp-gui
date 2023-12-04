# lftp-gui
ImGui front end for the lftp project https://lftp.yar.ru/

# Building

The GUI (and optionally LFTP) can be built from the root project directory by running `/scripts/build.sh`

Release mode can be enabled by passing the `-r` flag: `/scripts/build.sh -r`

The packaged release can be found in the `build/lftp-ui-bin` directory. Alternatively there is a github pipeline that will build from master.

## Requirements

Using the default CMake build system should automatically retrieve the required libraries for this project:
- imgui
- glm
- glad
- glfw
- yaml-cpp

To save time while building a precompiled version of lftp can also be used in the root project directory, otherwise if you wish to build from source
see the requirements below, lftp will be automatically built if it can't be found as part of the `/scripts/build.sh` script.

## Requirements (Building LFTP locally)

The default configuration flags used when building locally are:
```
    ./configure --prefix=/usr \
                --with-openssl
```

Packages:
- autoconf
- libtool
- gettext-devel
- automake
- gnulib (see: https://www.gnu.org/software/gnulib/)
  You will also need the gnulib-tool script in your path and accessible during build time, i.e.
  `ln -s $HOME/lftp-gui/build/lftp/gnulib/gnulib-tool $HOME/bin/gnulib-tool`

Libraries:
- readline-devel
- zlib-devel
- gnutls-devel or openssl-devel (optional)
- expat-devel (optional)
