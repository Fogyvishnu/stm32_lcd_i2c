
#ifndef INC_STM32_LCD_I2C_H_
#define INC_STM32_LCD_I2C_H_

#include "stm32l4xx_hal.h"    //  <---- HAL for STM32L4   <=====> Replace this for other series

typedef struct {
	I2C_HandleTypeDef *hi2c;
	uint8_t i2c_addr;
	uint8_t backlight;
} LCD_I2C_HandleTypeDef;

void LCD_I2C_Init(LCD_I2C_HandleTypeDef *lcd);
void LCD_I2C_Command(LCD_I2C_HandleTypeDef *lcd, uint8_t cmd);
void LCD_I2C_WriteChar(LCD_I2C_HandleTypeDef *lcd, char data);
void LCD_I2C_Print(LCD_I2C_HandleTypeDef *lcd, const char *str);
void LCD_I2C_Clear(LCD_I2C_HandleTypeDef *lcd);
void LCD_I2C_SetCursor(LCD_I2C_HandleTypeDef *lcd, uint8_t row, uint8_t col);


#endif /* INC_STM32_LCD_I2C_H_ */
