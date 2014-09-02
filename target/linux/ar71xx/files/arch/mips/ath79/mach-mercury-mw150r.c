/*
 *  Mercury MW150R board support
 *
 *  Copyright (C) 2012 Andrew 'Necromant' Andrianov <andrew@ncrmnt.org>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#include <asm/mach-ath79/ath79.h>
#include <asm/mach-ath79/ar71xx_regs.h>

#include "common.h"
#include "dev-wmac.h"
#include "dev-eth.h"
#include "dev-gpio-buttons.h"
#include "dev-leds-gpio.h"
#include "dev-m25p80.h"
#include "machtypes.h"

#define MW150R_GPIO_LED_GEAR	27
#define MW150R_GPIO_LED_WLAN	0
#define MW150R_GPIO_LED_LOCK	26
#define MW150R_GPIO_LED_LAN1	13
#define MW150R_GPIO_LED_LAN2	14
#define MW150R_GPIO_LED_LAN3	15
#define MW150R_GPIO_LED_LAN4	16
#define MW150R_GPIO_LED_WAN		17

#define MW150R_GPIO_BTN_RESET		11

#define MW150R_KEYS_POLL_INTERVAL	20	/* msecs */
#define MW150R_KEYS_DEBOUNCE_INTERVAL (3 * MW150R_KEYS_POLL_INTERVAL)

static const char *mw150r_part_probes[] = {
	"tp-link",
	NULL,
};

static struct flash_platform_data mw150r_flash_data = {
	.part_probes	= mw150r_part_probes,
};

static struct gpio_led mw150r_leds_gpio[] __initdata = {
	{
		.name		= "mercury:green:lan1",
		.gpio		= MW150R_GPIO_LED_LAN1,
	}, {
		.name		= "mercury:green:lan2",
		.gpio		= MW150R_GPIO_LED_LAN2,
	}, {
		.name		= "mercury:green:lan3",
		.gpio		= MW150R_GPIO_LED_LAN3,
	}, {
		.name		= "mercury:green:lan4",
		.gpio		= MW150R_GPIO_LED_LAN4,
	}, {
		.name		= "mercury:green:gear",
		.gpio		= MW150R_GPIO_LED_GEAR,
		.active_low	= 1,
	}, {
		.name		= "mercury:green:lock",
		.gpio		= MW150R_GPIO_LED_LOCK,
	}, {
		.name		= "mercury:green:wan",
		.gpio		= MW150R_GPIO_LED_WAN,
		.active_low	= 1,
	}, {
		.name		= "mercury:green:wlan",
		.gpio		= MW150R_GPIO_LED_WLAN,
	},
};

static struct gpio_keys_button mw150r_gpio_keys[] __initdata = {
	{
		.desc		= "reset",
		.type		= EV_KEY,
		.code		= KEY_RESTART,
		.debounce_interval = MW150R_KEYS_DEBOUNCE_INTERVAL,
		.gpio		= MW150R_GPIO_BTN_RESET,
	}
};

static void __init mw150r_setup(void)
{
	u8 *mac = (u8 *) KSEG1ADDR(0x1f01fc00);
	u8 *ee = (u8 *) KSEG1ADDR(0x1fff1000);

	ath79_register_m25p80(&mw150r_flash_data);

	ath79_gpio_function_disable(AR724X_GPIO_FUNC_ETH_SWITCH_LED0_EN |
				    AR724X_GPIO_FUNC_ETH_SWITCH_LED1_EN |
				    AR724X_GPIO_FUNC_ETH_SWITCH_LED2_EN |
				    AR724X_GPIO_FUNC_ETH_SWITCH_LED3_EN |
				    AR724X_GPIO_FUNC_ETH_SWITCH_LED4_EN);

	ath79_register_leds_gpio(-1, ARRAY_SIZE(mw150r_leds_gpio),
				 mw150r_leds_gpio);

	ath79_register_gpio_keys_polled(-1, MW150R_KEYS_POLL_INTERVAL,
					ARRAY_SIZE(mw150r_gpio_keys),
					mw150r_gpio_keys);

	ath79_init_mac(ath79_eth0_data.mac_addr, mac, 1);
	ath79_init_mac(ath79_eth1_data.mac_addr, mac, -1);

	ath79_register_mdio(0, 0x0);

	/* LAN ports */
	ath79_register_eth(1);

	/* WAN port */
	ath79_register_eth(0);

        ath79_register_wmac(ee, mac);

}
MIPS_MACHINE(ATH79_MACH_MERCURY_MW150R, "MW150R", "Mercury MW150R",
	     mw150r_setup);
