# OpenWrt Yún

This is a custom version of OpenWrt, targeted to the Arduino Yún. Some of its core packages, including the kernel and uboot, are derived from Linino.

## How to build

### Prerequites

In order to successfully build it, you need to setup a [Debian](https://www.debian.org/) computer with at least 30G of free disk space: we use Debian Wheezy. Using a virtual machine is suggested: you can make one with either [VirtualBox](https://www.virtualbox.org/) or [KVM](http://www.linux-kvm.org/page/Main_Pag).

Once the Debian computer is ready, run the following command

```bash
apt-get install git subversion build-essential asciidoc \
	fastjar flex gawk libgtk2.0-dev intltool zlib1g-dev \
	genisoimage libncurses5-dev libssl-dev ruby sdcc unzip \
	bison libboost-dev libxml-parser-perl libusb-dev bin86 \
	bcc sharutils openjdk-7-jdk mercurial cvs bzr
```

### Cloning the repo and setting up a download folder

While building, a lot of software will be downloaded. In order to avoid downloading it each time you run a build, store it to a separate folder

```bash
mkdir -p ~/DOWNLOAD
```

Now clone the repo with

```bash
git clone git@github.com:arduino/OpenWrt-yun.git
```

### Building

Now start the build process

```bash
cd OpenWrt-yun
DL_FOLDER=~/DOWNLOAD ./build.sh
```

If you have more than one CPU, you can speed the build process up by specifying a number of concurrent jobs equal to the number of CPUs plus 1. For example, if you have 4 CPUs, use command `DL_FOLDER=~/DOWNLOAD MAKE_JOBS=5 ./build.sh`. If left unspecified, the default value of 2 is used.

### Recovering

There is a variety of reasons for the build process to fail. If you run into an error you can recover, DO NOT use the `build.sh` script as it will wipe out all the previously done work. Instead use

```bash
MAKE_JOBS=5 nice -n 10 make -j $MAKE_JOBS V=s
```

