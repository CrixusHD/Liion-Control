#include "../include/display.h"
#include <lgfx/v1/platforms/esp32s3/Bus_RGB.hpp>
#include <lgfx/v1/platforms/esp32s3/Panel_RGB.hpp>

LGFX::LGFX(void) {
    {
        auto cfg = _bus_instance.config();
        cfg.panel = &_panel_instance;
        cfg.pin_d0  = TFT_B0;
        cfg.pin_d1  = TFT_B1;
        cfg.pin_d2  = TFT_B2;
        cfg.pin_d3  = TFT_B3;
        cfg.pin_d4  = TFT_B4;
        cfg.pin_d5  = TFT_G0;
        cfg.pin_d6  = TFT_G1;
        cfg.pin_d7  = TFT_G2;
        cfg.pin_d8  = TFT_G3;
        cfg.pin_d9  = TFT_G4;
        cfg.pin_d10 = TFT_G5;
        cfg.pin_d11 = TFT_R0;
        cfg.pin_d12 = TFT_R1;
        cfg.pin_d13 = TFT_R2;
        cfg.pin_d14 = TFT_R3;
        cfg.pin_d15 = TFT_R4;
        cfg.pin_henable = TFT_DE;
        cfg.pin_vsync   = TFT_VSYNC;
        cfg.pin_hsync   = TFT_HSYNC;
        cfg.pin_pclk    = TFT_PCLK;
        cfg.freq_write  = 16000000;
        cfg.hsync_polarity    = 0;
        cfg.hsync_front_porch = 8;
        cfg.hsync_pulse_width = 4;
        cfg.hsync_back_porch  = 8;
        cfg.vsync_polarity    = 0;
        cfg.vsync_front_porch = 8;
        cfg.vsync_pulse_width = 4;
        cfg.vsync_back_porch  = 8;
        cfg.pclk_active_neg   = 1;
        cfg.de_idle_high      = 0;
        cfg.pclk_idle_high    = 0;
        _bus_instance.config(cfg);
        _panel_instance.setBus(&_bus_instance);
    }
    {
        auto cfg = _panel_instance.config();
        cfg.memory_width  = TFT_WIDTH;
        cfg.memory_height = TFT_HEIGHT;
        cfg.panel_width   = TFT_WIDTH;
        cfg.panel_height  = TFT_HEIGHT;
        cfg.offset_x = 0;
        cfg.offset_y = 0;
        _panel_instance.config(cfg);
    }
    {
        auto cfg = _light_instance.config();
        cfg.pin_bl = TFT_BL;
        cfg.invert = false;
        cfg.freq   = 44100;
        cfg.pwm_channel = 1;
        _light_instance.config(cfg);
        _panel_instance.setLight(&_light_instance);
    }
    setPanel(&_panel_instance);
}
