#!/bin/bash -ex

if [ -h dl ]; then
	rm -f dl
fi

rm -fr staging_dir build_dir bin broken_packages
make distclean

if [ -n "$DL_FOLDER" ] && [ ! -a dl ]; then
	ln -s $DL_FOLDER dl
fi

./scripts/feeds uninstall -a
rm -rf feeds
./scripts/feeds update -a
./scripts/feeds install -a
./scripts/feeds uninstall erlang freeswitch remotefs libzstream shflags opensips pulseaudio xmlrpc-c rtorrent sox umurmur-polarssl freecwmp-zstream osirisd logtrigger libplist libimobiledevice cmus mxml boost wt etherpuppet php4
rm -f .config
git checkout .config
if [ "Yes" = "$BUILD_BASE_ONLY" ]; then
	sed 's/=m$/=n/' <.config >.baseonlyconfig
	mv .config .origconfig; mv .baseonlyconfig .config;
fi
make oldconfig

if [ -z "$MAKE_JOBS" ]; then
	MAKE_JOBS="2"
fi

nice -n 10 make -j $MAKE_JOBS V=s
