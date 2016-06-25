#!/bin/bash

#
# Copyright (c) 2014 Arduino LLC. All right reserved.
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

if [ "$(id -u)" != "0" ]; then
	echo "This script must be run as root" 1>&2
	exit 1
fi

echo >> /etc/apt/sources.list
echo "deb http://mirror.switch.ch/ftp/mirror/debian/ wheezy-backports main" >> /etc/apt/sources.list

apt-get update

apt-get install -y git subversion build-essential asciidoc \
	fastjar flex gawk libgtk2.0-dev intltool zlib1g-dev \
	genisoimage libncurses5-dev libssl-dev ruby sdcc unzip \
	bison libboost-dev libxml-parser-perl libusb-dev bin86 \
	bcc sharutils openjdk-7-jdk mercurial cvs bzr \
	nodejs-legacy curl

curl -L https://www.npmjs.org/install.sh | sh

echo "ALL DONE! YEAH!!"

