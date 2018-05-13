#
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=u_netlink
PKG_VERSION:=0.1
PKG_RELEASE:=1
PKG_MAINTAINER:=liujie<liujie@bdcom.com.cn>
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)
include $(INCLUDE_DIR)/package.mk

define Package/u_netlink
  SECTION:=libs
  CATEGORY:=Libraries
  DEPENDS:=
  TITLE:=u_netlink just for sth
  URL:=http://www.bdcom.com.cn
  MAINTAINER:=liujie <liujie@bdcom.com.cn>
endef


define Package/u_netlink/description
	u_netlink just for test
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef



define Package/u_netlink/install
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/u_netlink $(1)/bin
endef


$(eval $(call BuildPackage,u_netlink))
