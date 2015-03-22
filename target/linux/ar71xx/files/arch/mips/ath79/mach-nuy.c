/*
 *  8devices NUY support
 *
 *  Copyright (C) 2011-2012 Gabor Juhos <juhosg@openwrt.org>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#include "dev-eth.h"
#include "dev-gpio-buttons.h"
#include "dev-leds-gpio.h"
#include "dev-m25p80.h"
#include "dev-spi.h"
#include "dev-usb.h"
#include "dev-wmac.h"
#include "machtypes.h"
#include <asm/mach-ath79/ar71xx_regs.h>
#include <asm/mach-ath79/ath79.h>
#include "common.h"
#include "gpio.h"
#include "linux/gpio.h"

#define DS_GPIO_LED_WLAN		13
#define DS_GPIO_LED_WAN			1
#define DS_GPIO_LED_USB			0

#define DS_GPIO_OE			22 /*SPI*/
#define DS_GPIO_AVR_RESET		12
#define DS_GPIO_OE2                     16 /*HANDSHAKE */
#define DS_GPIO_UART_ENA		17
#define DS_GPIO_CONF_BTN		11

#define DS_KEYS_POLL_INTERVAL		20	/* msecs */
#define DS_KEYS_DEBOUNCE_INTERVAL	(3 * DS_KEYS_POLL_INTERVAL)

#define DS_MAC0_OFFSET			0x0000
#define DS_MAC1_OFFSET			0x0006
#define DS_CALDATA_OFFSET		0x1000
#define DS_WMAC_MAC_OFFSET		0x1002

static struct gpio_led ds_leds_gpio[] __initdata = {
	{
		.name		= "ds:green:usb",
		.gpio		= DS_GPIO_LED_USB,
		.active_low	= 1,
	},
	{
		.name		= "ds:green:wlan",
		.gpio		= DS_GPIO_LED_WLAN,
		.active_low	= 1,
	},
	{
		.name		= "ds:green:wan",
		.gpio		= DS_GPIO_LED_WAN,
		.active_low	= 1,
	},
};

static struct gpio_keys_button ds_gpio_keys[] __initdata = {
	{
		.desc		= "configuration button",
		.type		= EV_KEY,
		.code		= KEY_WPS_BUTTON,
		.debounce_interval = DS_KEYS_DEBOUNCE_INTERVAL,
		.gpio		= DS_GPIO_CONF_BTN,
		.active_low	= 1,
	},
};

static void __init ds_common_setup(void)
{
	u8 *art = (u8 *) KSEG1ADDR(0x1fff0000);
	ath79_register_m25p80(NULL);

	ath79_register_wmac(art + DS_CALDATA_OFFSET,
			    art + DS_WMAC_MAC_OFFSET);
	ath79_init_mac(ath79_eth0_data.mac_addr, art + DS_MAC0_OFFSET, 0);
	ath79_init_mac(ath79_eth1_data.mac_addr, art + DS_MAC1_OFFSET, 0);

	ath79_register_mdio(0, 0x0);

	/* LAN ports */
	ath79_register_eth(0);

	/* WAN port */
	ath79_register_eth(1);
}

static void __init ds_setup(void)
{
	u32 t;
	
	ds_common_setup();

	ath79_register_leds_gpio(-1, ARRAY_SIZE(ds_leds_gpio),
				 ds_leds_gpio);
	ath79_register_gpio_keys_polled(-1, DS_KEYS_POLL_INTERVAL,
					ARRAY_SIZE(ds_gpio_keys),
					ds_gpio_keys);
	ath79_register_usb();

	//Disable the Function for some pins to have GPIO functionality active
	// GPIO6-7-8 and GPIO11
	ath79_gpio_function_setup(AR933X_GPIO_FUNC_JTAG_DISABLE | AR933X_GPIO_FUNC_I2S_MCK_EN, 0);
	ath79_gpio_function2_setup(AR933X_GPIO_FUNC2_JUMPSTART_DISABLE|
					AR933X_GPIO_FUNC2_WPS_DISABLE, 0);

	printk("Setting NUY GPIO\n");

	t = ath79_reset_rr(AR933X_RESET_REG_BOOTSTRAP);
	t |= AR933X_BOOTSTRAP_MDIO_GPIO_EN;
	ath79_reset_wr(AR933X_RESET_REG_BOOTSTRAP, t);

	// enable OE of level shifter
	if (gpio_request_one(DS_GPIO_OE,
		 GPIOF_OUT_INIT_LOW | GPIOF_EXPORT_DIR_FIXED,
		 "OE-1") != 0)
		printk("Error setting GPIO OE\n");

        if (gpio_request_one(DS_GPIO_UART_ENA,
                 GPIOF_OUT_INIT_HIGH | GPIOF_EXPORT_DIR_FIXED,
                 "UART-ENA") != 0)
                printk("Error setting GPIO Uart Enable\n");

	// enable OE of level shifter
        if (gpio_request_one(DS_GPIO_OE2,
		GPIOF_OUT_INIT_LOW | GPIOF_EXPORT_DIR_FIXED,
		"OE-2") != 0)
		printk("Error setting GPIO OE2\n");
}

MIPS_MACHINE(ATH79_MACH_NUY, "NUY", "8devices NUY",
	     ds_setup);
