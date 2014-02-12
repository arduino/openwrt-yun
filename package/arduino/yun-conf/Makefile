#
# Copyright (c) 2013 Arduino LLC. All right reserved.
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=yun-conf
PKG_VERSION:=1.1.0
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/yun-conf
  SECTION:=utils
  CATEGORY:=Base system
  TITLE:=Custom Yún configurations
  DEPENDS:=+avahi-daemon +base-files +triggerhappy
endef

define Package/yun-conf/conffiles
/etc/avahi/services/arduino.service
/etc/config/arduino
/etc/httpd.conf
endef

define Build/Compile
	# NOOP
endef

define Package/yun-conf/install
	$(INSTALL_DIR) $(1)/etc/avahi/services
	$(INSTALL_DIR) $(1)/etc/arduino
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_DIR) $(1)/etc/triggerhappy/triggers.d

	$(INSTALL_CONF) ./files/etc/avahi/services/arduino.service $(1)/etc/avahi/services/
	$(INSTALL_CONF) ./files/etc/triggerhappy/triggers.d/reset.conf $(1)/etc/triggerhappy/triggers.d

	$(INSTALL_CONF) ./files/etc/httpd.conf $(1)/etc/
	$(INSTALL_CONF) ./files/etc/config/arduino $(1)/etc/config/
	#$(INSTALL_CONF) ./files/etc/config/dhcp $(1)/etc/config/dhcp.1

	$(INSTALL_DATA) ./files/etc/arduino/Caterina-Yun.hex $(1)/etc/arduino/
	$(INSTALL_CONF) ./files/etc/arduino/openwrt-yun-release $(1)/etc/arduino/
	sed -i "s/DATE/`date`/g" $(1)/etc/arduino/openwrt-yun-release
	$(INSTALL_CONF) ./files/etc/arduino/gpg_gen_key_batch $(1)/etc/arduino/
	$(INSTALL_DATA) ./files/etc/arduino/wifi_timezones.csv.gz $(1)/etc/arduino
	$(INSTALL_DATA) ./files/etc/arduino/wifi_error_statuses.csv.gz $(1)/etc/arduino
	$(INSTALL_DATA) ./files/etc/arduino/wifi_error_reasons.csv.gz $(1)/etc/arduino

	$(INSTALL_DATA) ./files/etc/LININO_CONTRIBUTORS.TXT $(1)/etc/
endef

$(eval $(call BuildPackage,yun-conf))
