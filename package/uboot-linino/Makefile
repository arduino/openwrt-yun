#
# Copyright (C) 2013 Linino.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=u-boot
PKG_VERSION:=linino
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(KERNEL_BUILD_DIR)/$(PKG_NAME)-$(BUILD_VARIANT)/$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=
PKG_MD5SUM:=
PKG_TARGETS:=bin

CAL_DATA:=art-linino.bin

include $(INCLUDE_DIR)/package.mk

define uboot/Default
  TITLE:=
  CONFIG:=
  IMAGE:=
endef

define uboot/linino
  TITLE:=U-boot for Linino project
endef

UBOOTS:=linino

define Package/uboot/template
define Package/uboot-ar71xx-$(1)
  SECTION:=boot
  CATEGORY:=Boot Loaders
  TITLE:=$(2)
  DEPENDS:=@TARGET_ar71xx
  URL:=http://www.linino.org
  DEFAULT:=y if (TARGET_ar71xx_generic_Linino)
  VARIANT:=$(1)
endef
endef

define Package/uboot-ar71xx-linino/config
	source $(SOURCE)/Config.in
endef

ifdef CONFIG_COMPRESSED_UBOOT
      export COMPRESSED_UBOOT=1
endif

ifdef CONFIG_HORNET_1_1_WAR
      export CONFIG_HORNET_1_1_WAR=1
endif

ifdef CONFIG_NEW_DDR_TAP_CAL
      export NEW_DDR_TAP_CAL=1
endif

ifdef CONFIG_LININO_DDR2
      export CONFIG_LININO_DDR2=1
endif

define BuildUbootPackage
	$(eval $(uboot/Default))
	$(eval $(uboot/$(1)))
	$(call Package/uboot/template,$(1),$(TITLE))
endef


ifdef BUILD_VARIANT
$(eval $(call uboot/$(BUILD_VARIANT)))
#UBOOT_CONFIG:=$(if $(CONFIG),$(CONFIG),$(BUILD_VARIANT))
UBOOT_CONFIG:=linino
UBOOT_IMAGE:=$(if $(IMAGE),$(IMAGE),openwrt-$(BOARD)-$(BUILD_VARIANT)-u-boot.bin)
endif

define Build/Prepare
	$(CP) ./$(PKG_SOURCE) $(DL_DIR)/
	$(call Build/Prepare/Default)
	$(CP) ./files/* $(PKG_BUILD_DIR)	
	find $(PKG_BUILD_DIR) -name .svn | $(XARGS) rm -rf
endef

define Build/Configure
	$(MAKE) -C $(PKG_BUILD_DIR) \
		mrproper
	$(MAKE) -C $(PKG_BUILD_DIR) \
		$(UBOOT_CONFIG)_config
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		CROSS_COMPILE=$(TARGET_CROSS)
endef

define Package/uboot/install/template
define Package/uboot-ar71xx-$(1)/install
	#$(INSTALL_DIR) $$(1)
	rm -rf $$(1)
	$(CP) $(PKG_BUILD_DIR)/tuboot.bin $(BIN_DIR)/$(2)
	$(CP) ./$(PKG_SOURCE) $(DL_DIR)/; $(CP) ./$(CAL_DATA) $(BIN_DIR)/openwrt-ar71xx-generic-linino-caldata.bin && touch $(BIN_DIR)/openwrt-ar71xx-generic-linino-caldata.bin
endef
endef

$(foreach u,$(UBOOTS), \
	$(eval $(call Package/uboot/install/template,$(u),openwrt-$(BOARD)-$(SUBTARGET)-$(u)-u-boot.bin)) \
)

$(foreach u,$(UBOOTS), \
	$(eval $(call BuildUbootPackage,$(u))) \
	$(eval $(call BuildPackage,uboot-ar71xx-$(u))) \
)
