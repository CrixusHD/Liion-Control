
#ifndef DISPLAY_CONFIG_H
#define DISPLAY_CONFIG_H

// Display-Größe
#define TFT_WIDTH  800
#define TFT_HEIGHT 480

// Backlight Pin
#define TFT_BL 2

// ESP32-8048S043C RGB Display Pins
#define TFT_DE      40
#define TFT_VSYNC   41
#define TFT_HSYNC   39
#define TFT_PCLK    42

// RGB Data Pins (5-6-5 Format)
#define TFT_R0      45
#define TFT_R1      48
#define TFT_R2      47
#define TFT_R3      21
#define TFT_R4      14

#define TFT_G0      5
#define TFT_G1      6
#define TFT_G2      7
#define TFT_G3      15
#define TFT_G4      16
#define TFT_G5      4

#define TFT_B0      8
#define TFT_B1      3
#define TFT_B2      46
#define TFT_B3      9
#define TFT_B4      1

// Touch GT911 I2C Pins - KORRIGIERT!
#define TOUCH_SDA   19
#define TOUCH_SCL   20
#define TOUCH_INT   0     // <- WAR 18, MUSS 0 SEIN!
#define TOUCH_RST   38

#endif