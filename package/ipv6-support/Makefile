#
# Copyright (C) 2010-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=ipv6-support
PKG_VERSION:=2013-05-27.1
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/ipv6-support
  SECTION:=ipv6
  CATEGORY:=IPv6
  DEPENDS:=+kmod-ipv6 +ip6tables +6relayd +odhcp6c +6in4 +6rd +6to4 +ds-lite
  TITLE:=Extended IPv6-support for home routers (meta package)
  MAINTAINER:=Steven Barth <steven@midlink.org>
  PKGARCH:=all
endef

define Package/ipv6-support/description
This package provides basic IPv6 support including Router Discovery,
DHCPv6 (client & server), prefix delegation and distribution.
endef

define Build/Compile
endef

define Build/Configure
endef

define Package/ipv6-support/postinst
#!/bin/sh
[ -n "$${IPKG_INSTROOT}" ] || /etc/uci-defaults/10_network-enable-ipv6 || true
[ -n "$${IPKG_INSTROOT}" ] || rm -f /etc/uci-defaults/10_network-enable-ipv6 || true
endef

define Package/ipv6-support/install
	$(INSTALL_DIR) $(1)/etc/uci-defaults
	$(INSTALL_BIN) ./files/network-enable-ipv6.defaults $(1)/etc/uci-defaults/10_network-enable-ipv6
endef

$(eval $(call BuildPackage,ipv6-support))
