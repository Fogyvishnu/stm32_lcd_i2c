# STM32 I2C LCD Library (HAL-Based)

This is a lightweight and portable library to interface HD44780-compatible LCD modules using an I2C backpack (PCF8574) with STM32 microcontrollers. It is written using the STM32 HAL library and is designed to work across STM32 L4, F4, F1, and other series by simply changing the included device header (e.g., stm32l4xx_hal.h, stm32f1xx_hal.h, etc.).


📟 Features

✅ 4-bit mode LCD communication via I2C (PCF8574)

✅ Compatible with 16x2, 20x4, etc.

✅ Simple API for printing text and setting cursor

✅ Clean abstraction using HAL I2C

✅ Easily portable to any STM32 series

✅ Lightweight, minimal dependencies


🚀 Getting Started

✅ Prerequisites

1. STM32CubeIDE / STM32CubeMX

2. Configured I2C peripheral (e.g., I2C1)

3. Compatible LCD I2C backpack (e.g., PCF8574 at address 0x27 or 0x3F)

🔧 Setup

1. Clone or copy the files lcd_i2c_hal.c and lcd_i2c_hal.h into your STM32 project.

2. Include lcd_i2c_hal.h in your main.c.

3. Add and configure an I2C peripheral using CubeMX (e.g., hi2c1).
