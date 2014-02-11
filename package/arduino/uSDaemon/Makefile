#
# Copyright (c) 2013 Arduino LLC. All right reserved.
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=uSDaemon
PKG_VERSION:=1.0.0
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/uSDaemon
  SECTION:=utils
  CATEGORY:=Base system
  TITLE:=uSD auto (un)mount
  DEPENDS:=+block-mount
endef

define Build/Compile
	# NOOP
endef

define Package/uSDaemon/install
	$(INSTALL_DIR) $(1)/sbin/
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_DIR) $(1)/lib/functions

	$(INSTALL_BIN) ./files/sbin/uSDaemon $(1)/sbin/
	$(INSTALL_BIN) ./files/etc/init.d/usd $(1)/etc/init.d
	$(INSTALL_DATA) ./files/lib/functions/post_mount.sh $(1)/lib/functions
endef

$(eval $(call BuildPackage,uSDaemon))

