#!/bin/sh -ex
rm -f dl
rm -fr staging_dir build_dir bin broken_packages
make distclean

ln -s $DL_FOLDER dl

./scripts/feeds uninstall -a
rm -rf feeds
./scripts/feeds update -a
./scripts/feeds install -a
./scripts/feeds uninstall erlang freeswitch remotefs libzstream shflags opensips pulseaudio xmlrpc-c rtorrent sox umurmur-polarssl freecwmp-zstream osirisd logtrigger libplist libimobiledevice cmus mxml boost wt
rm -f .config
git checkout .config
make oldconfig

if [ -z "$MAKE_JOBS" ]; then
	MAKE_JOBS="2"
fi

nice -n 10 make -j $MAKE_JOBS V=s
