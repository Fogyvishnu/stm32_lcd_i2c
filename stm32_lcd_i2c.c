#include "stm32_lcd_i2c.h"
#include "string.h"

// LCD control bits
#define LCD_BACKLIGHT 0x08
#define LCD_ENABLE    0x04
#define LCD_RW        0x02
#define LCD_RS        0x01

// === Low-level I2C write function ===
static void LCD_I2C_Write(LCD_I2C_HandleTypeDef *lcd, uint8_t data) {
    HAL_I2C_Master_Transmit(lcd->hi2c, lcd->i2c_addr, &data, 1, HAL_MAX_DELAY);
}

// === Toggle the EN (Enable) pin to latch data ===
static void LCD_PulseEnable(LCD_I2C_HandleTypeDef *lcd, uint8_t data) {
    LCD_I2C_Write(lcd, data | LCD_ENABLE);  // EN = 1
    HAL_Delay(1);
    LCD_I2C_Write(lcd, data & ~LCD_ENABLE); // EN = 0
    HAL_Delay(1);
}

// === Send upper/lower 4 bits of byte ===
static void LCD_WriteNibble(LCD_I2C_HandleTypeDef *lcd, uint8_t nibble, uint8_t mode) {
    uint8_t data = (nibble & 0xF0) |
                   (mode ? LCD_RS : 0x00) |
                   (lcd->backlight ? LCD_BACKLIGHT : 0);
    LCD_I2C_Write(lcd, data);       // Send nibble
    LCD_PulseEnable(lcd, data);     // Latch with enable pulse
}

// === Send a full 8-bit byte in two 4-bit parts ===
static void LCD_SendByte(LCD_I2C_HandleTypeDef *lcd, uint8_t byte, uint8_t mode) {
    LCD_WriteNibble(lcd, byte & 0xF0, mode);          // Upper nibble
    LCD_WriteNibble(lcd, (byte << 4) & 0xF0, mode);   // Lower nibble
}

// === Send a command byte to the LCD ===
void LCD_I2C_Command(LCD_I2C_HandleTypeDef *lcd, uint8_t cmd) {
    LCD_SendByte(lcd, cmd, 0);  // mode = 0 (command)
}

// === Send a single character to the LCD ===
void LCD_I2C_WriteChar(LCD_I2C_HandleTypeDef *lcd, char data) {
    LCD_SendByte(lcd, data, 1);  // mode = 1 (data)
}

// === Print a null-terminated string on the LCD ===
void LCD_I2C_Print(LCD_I2C_HandleTypeDef *lcd, const char *str) {
    while (*str) {
        LCD_I2C_WriteChar(lcd, *str++);
    }
}

// === Clear the LCD display ===
void LCD_I2C_Clear(LCD_I2C_HandleTypeDef *lcd) {
    LCD_I2C_Command(lcd, 0x01);   // Clear display
    HAL_Delay(2);                 // Delay for clear operation
}

// === Set cursor to specific row and column ===
void LCD_I2C_SetCursor(LCD_I2C_HandleTypeDef *lcd, uint8_t row, uint8_t col) {
    static const uint8_t row_offsets[] = {0x00, 0x40, 0x14, 0x54};
    LCD_I2C_Command(lcd, 0x80 | (col + row_offsets[row]));
}

// === Initialize the LCD in 4-bit I2C mode ===
void LCD_I2C_Init(LCD_I2C_HandleTypeDef *lcd) {
    HAL_Delay(50);  // LCD power-on delay

    // Initialization sequence (3x 0x30 + 0x20 to enter 4-bit mode)
    LCD_WriteNibble(lcd, 0x30, 0); HAL_Delay(5);
    LCD_WriteNibble(lcd, 0x30, 0); HAL_Delay(1);
    LCD_WriteNibble(lcd, 0x30, 0); HAL_Delay(1);
    LCD_WriteNibble(lcd, 0x20, 0); HAL_Delay(1);  // 4-bit mode

    // LCD setup
    LCD_I2C_Command(lcd, 0x28); // Function Set: 4-bit, 2-line, 5x8 font
    LCD_I2C_Command(lcd, 0x0C); // Display ON, Cursor OFF
    LCD_I2C_Command(lcd, 0x06); // Entry mode: increment, no shift
    LCD_I2C_Clear(lcd);         // Clear screen
}
