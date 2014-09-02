#
# Copyright (C) 2009 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

define Profile/MW150R-16M
        NAME:=Mercury MW150R 16Mb
        PACKAGES:=kmod-usb-core kmod-usb2
endef
define Profile/MW150R-16M/Description
        Package set optimized for the Mercury MW150R with 16Mb Flash.
endef
$(eval $(call Profile,MW150R-16M))

define Profile/MW150R-8M
        NAME:=Mercury MW150R 8Mb
        PACKAGES:=kmod-usb-core kmod-usb2
endef
define Profile/MW150R-8M/Description
        Package set optimized for the Mercury MW150R with 8Mb Flash.
endef
$(eval $(call Profile,MW150R-8M))

define Profile/MW150R-4M
        NAME:=Mercury MW150R 4Mb
        PACKAGES:=kmod-usb-core kmod-usb2
endef
define Profile/MW150R-4M/Description
        Package set optimized for the Mercury MW150R with 4Mb Flash.
endef
$(eval $(call Profile,MW150R-4M))
