# OpenWrt Yún

This is a custom version of OpenWrt, targeted to the Arduino Yún. Some of its core packages, including the kernel and uboot, are derived from [Linino](http://linino.org/doku.php).

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

To clone the repository using git SSH, make sure you [have your public SSH key in your github profile](https://help.github.com/articles/generating-ssh-keys) and execute:

```bash
git clone git@github.com:arduino/OpenWrt-yun.git
```

However if you can't use git SSH you can instead clone the repository over HTTPS by executing:

```bash
git clone https://github.com/arduino/openwrt-yun.git
````

If you clone the repository using HTTPS you _must_ edit the feeds.conf.default file and change the package repository from git SSH to HTTPS by changing the first line from:

```
src-git packages git@github.com:arduino/openwrt-packages-yun.git
```

to:

```
src-git packages https://github.com/arduino/openwrt-packages-yun.git
```

### Building

Now start the build process

```bash
cd OpenWrt-yun
DL_FOLDER=~/DOWNLOAD ./build.sh
```

If you have more than one CPU, you can speed the build process up by specifying a number of concurrent jobs equal to the number of CPUs plus 1. For example, if you have 4 CPUs, use command `DL_FOLDER=~/DOWNLOAD MAKE_JOBS=5 ./build.sh`. If left unspecified, the default value of 2 is used.

### Continuing an interrupted build

For some reasons, you may need to interrupt the build. Maybe it was an error, maybe you run out of time. To resume compiling, DO NOT use the `build.sh` script as it will wipe out all the previously done work. Instead use

```bash
MAKE_JOBS=5 nice -n 10 make -j $MAKE_JOBS V=s
```

Change the value of `MAKE_JOBS` to the number of your cores + 1. My pc has 4 cores, so I set it to 5.

### Troubleshooting

There is a variety of reasons for the build process to fail. If you're unable to understand why it failed, resume compiling with the following command:

```bash
nice -n 10 nohup make -j 1 V=s &
```

This will create a `nohup.out` file with the whole output of the compilation, errors included. Please paste the content of that file on http://pastebin.com/ or zip and attach that file on a new topic on the 
[arduino forum](http://forum.arduino.cc/index.php?board=93.0).
