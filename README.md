STM32 I2C LCD Library
<div align="center">
https://img.shields.io/badge/STM32-HAL-blue?logo=stmicroelectronics&logoColor=white
https://img.shields.io/badge/Interface-I2C-green
https://img.shields.io/badge/Display-HD44780-yellow
https://img.shields.io/badge/License-MIT-success
https://img.shields.io/badge/Platform-STM32_CubeIDE-orange

Lightweight HAL-based library for HD44780 LCD with I2C PCF8574 backpack

</div>
📋 Overview
A portable, efficient library for interfacing HD44780-compatible LCD displays (16x2, 20x4, etc.) via I2C backpack (PCF8574) with STM32 microcontrollers. Built on STM32 HAL for maximum compatibility across STM32 series (L4, F4, F1, etc.).

✨ Features
Feature	Description
🚀 4-Bit Mode	Efficient I2C communication using 4-bit mode, minimizing pin usage
🖥️ Multi-Display Support	Compatible with 16x2, 20x4, and other HD44780 LCD modules
🔧 Simple API	Intuitive functions for text display, cursor control, and display management
🔄 HAL Abstraction	Clean abstraction layer using STM32 HAL I2C
📱 Cross-Platform	Easily portable across STM32 series (L4, F4, F1, etc.)
⚡ Lightweight	Minimal resource consumption, perfect for constrained environments
🚀 Quick Start
Prerequisites
STM32CubeIDE / STM32CubeMX

Configured I2C peripheral (e.g., I2C1, I2C2)

I2C LCD backpack (PCF8574 typically at 0x27 or 0x3F)

Installation Steps
Add Library Files to your STM32 project:

c
// Copy these files to your project source folder:
lcd_i2c_hal.c
lcd_i2c_hal.h
Include Header in your main application:

c
#include "lcd_i2c_hal.h"
Configure I2C using CubeMX:

Enable I2C peripheral

Configure appropriate pins

Set clock speed (typically 100kHz)

Initialize and Use:

c
// External I2C handle (defined by CubeMX)
extern I2C_HandleTypeDef hi2c1;

// LCD handle
LCD_HandleTypeDef lcd;

// Initialize LCD (address 0x27, 16 columns, 2 rows)
LCD_I2C_Init(&lcd, &hi2c1, 0x27, 16, 2);

// Display text
LCD_I2C_Print(&lcd, "Hello, STM32!");
LCD_I2C_SetCursor(&lcd, 0, 1);
LCD_I2C_Print(&lcd, "I2C LCD Demo");
