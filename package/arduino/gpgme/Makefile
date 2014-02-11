#
# Copyright (C) 2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=gpgme
PKG_VERSION:=1.3.1
PKG_RELEASE:=1.dh1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=ftp://ftp.gnupg.org/gcrypt/gpgme/
PKG_MD5SUM:=90afa8436ce2b2683c001c824bd22601

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/libgpgme
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=GnuPG Made Easy library
  URL:=http://www.gnupg.org/
  DEPENDS:=+gnupg +libassuan +libpthread
endef

define Package/libgpgme/description
 GPGME (GnuPG Made Easy) is a C language library that allows to add
 support for cryptography to a program. It is designed to make access to
 public key crypto engines like GnuPG or GpgSM easier for applications.
 GPGME provides a high-level crypto API for encryption, decryption,
 signing, signature verification and key management.
endef

CONFIGURE_ARGS += \
	--enable-shared \
	--enable-static \
	--with-gpg=/"usr/bin/gpg" \
	--with-gpg-error-prefix="$(STAGING_DIR)/usr" \
	--with-libassuan-prefix="$(STAGING_DIR)/usr" \
	--without-g13 \
	--without-gpgconf \
	--without-gpgsm \
	--without-pth \

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/gpgme.h $(1)/usr/include/

	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libgpgme{,-pthread}.{a,so*} $(1)/usr/lib/

	$(INSTALL_DIR) $(2)/bin $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/gpgme-config \
		$(2)/bin/
	ln -sf $(STAGING_DIR)/host/bin/gpgme-config $(1)/usr/bin/gpgme-config
endef

define Package/libgpgme/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libgpgme{,-pthread}.so.* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,libgpgme))
