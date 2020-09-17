/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Copyright (c) 2020 Martin Jäger / Libre Solar
 */

#include <kernel.h>
#include <device.h>
#include <init.h>
#include <drivers/pinmux.h>
#include <sys/sys_io.h>

#include <pinmux/stm32/pinmux_stm32.h>

/* this should normally go to drivers/pinmux/stm32/pinmux_stm32g4x.h */
#define STM32G4X_PINMUX_FUNC_PC6_PWM8_CH1 \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_PUSHPULL_NOPULL)

#define STM32G4X_PINMUX_FUNC_PA8_TIM1_CH1 \
	(STM32_PINMUX_ALT_FUNC_6 | STM32_PUSHPULL_NOPULL)
#define STM32G4X_PINMUX_FUNC_PB13_TIM1_CH1N \
	(STM32_PINMUX_ALT_FUNC_6 | STM32_PUSHPULL_NOPULL)

static const struct pin_config pinconf[] = {
	/* TIM1_CH1 and TIM1_CH1N */
	{STM32_PIN_PA8, STM32G4X_PINMUX_FUNC_PA8_TIM1_CH1},
	{STM32_PIN_PB13, STM32G4X_PINMUX_FUNC_PB13_TIM1_CH1N},
#if DT_NODE_HAS_STATUS(DT_NODELABEL(usart1), okay) && CONFIG_SERIAL
	{STM32_PIN_PA9, STM32G4X_PINMUX_FUNC_PA9_USART1_TX},
	{STM32_PIN_PA10, STM32G4X_PINMUX_FUNC_PA10_USART1_RX},
#endif /* CONFIG_SERIAL || UART_CONSOLE, usart1 */
	{STM32_PIN_PC6, STM32G4X_PINMUX_FUNC_PC6_PWM8_CH1},
	{STM32_PIN_PC7, STM32G4X_PINMUX_FUNC_PC7_PWM3_CH2},
#if DT_NODE_HAS_STATUS(DT_NODELABEL(usart3), okay) && CONFIG_SERIAL
	{STM32_PIN_PC10, STM32G4X_PINMUX_FUNC_PC10_USART3_TX},
	{STM32_PIN_PC11, STM32G4X_PINMUX_FUNC_PC11_USART3_RX},
#endif /* CONFIG_SERIAL, usart3 */
#if DT_NODE_HAS_STATUS(DT_NODELABEL(i2c1), okay) && CONFIG_I2C
	{STM32_PIN_PA15, STM32G4X_PINMUX_FUNC_PA15_I2C1_SCL},
	{STM32_PIN_PB7, STM32G4X_PINMUX_FUNC_PB7_I2C1_SDA},
#endif /* CONFIG_I2C, i2c1 */
#if DT_NODE_HAS_STATUS(DT_NODELABEL(i2c3), okay) && CONFIG_I2C
	{STM32_PIN_PC8, STM32G4X_PINMUX_FUNC_PC8_I2C3_SCL},
	{STM32_PIN_PC9, STM32G4X_PINMUX_FUNC_PC9_I2C3_SDA},
#endif /* CONFIG_I2C, i2c3 */
#if DT_NODE_HAS_STATUS(DT_NODELABEL(spi1), okay) && CONFIG_SPI
	{STM32_PIN_PB3, STM32G4X_PINMUX_FUNC_PB3_SPI1_SCK},
	{STM32_PIN_PB4, STM32G4X_PINMUX_FUNC_PB4_SPI1_MISO},
	{STM32_PIN_PB5, STM32G4X_PINMUX_FUNC_PB5_SPI1_MOSI},
#endif /* CONFIG_SPI, spi1 */
#if DT_NODE_HAS_STATUS(DT_NODELABEL(usb), okay) && CONFIG_USB_DC_STM32
	{STM32_PIN_PA11, STM32G4X_PINMUX_FUNC_PA11_USB_DM},
	{STM32_PIN_PA12, STM32G4X_PINMUX_FUNC_PA12_USB_DP},
#endif	/* CONFIG_USB_DC_STM32 */
};

static int pinmux_stm32_init(struct device *port)
{
	ARG_UNUSED(port);

	stm32_setup_pins(pinconf, ARRAY_SIZE(pinconf));

	return 0;
}

SYS_INIT(pinmux_stm32_init, PRE_KERNEL_1,
	 CONFIG_PINMUX_STM32_DEVICE_INITIALIZATION_PRIORITY);
