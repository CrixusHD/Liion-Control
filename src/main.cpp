#include <Arduino.h>
#include <lvgl.h>
#include "display.h"
#include "gt911_touch.h"
#include "akku_data.h"
#include "i2c_comm.h"
#include "ui_manager.h"

static LGFX tft;
static GT911Touch touch;
static I2CComm i2cComm;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf, *disp_draw_buf2;
static lv_disp_drv_t disp_drv;

unsigned long lastI2CRequest = 0;
const unsigned long I2C_INTERVAL = 5000; // 5 Sekunden

void display_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.writePixels((lgfx::rgb565_t *)&color_p->full, w * h);
    tft.endWrite();
    lv_disp_flush_ready(disp);
}

void touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
    // Statische Variablen für den Jitter-Filter
    static uint16_t lastRawX = 0;
    static uint16_t lastRawY = 0;

    // Jitter-Filter-Schwelle (kannst du anpassen, z.B. auf 3 oder 5)
    const int JITTER_THRESHOLD = 5;

    uint16_t touchX, touchY;

    // --- PERFORMANCE-FIX (kein Stottern) ---
    // Serial.println("Touch pad read"); // <-- MUSS AUSKOMMENTIERT SEIN!

    if (touch.read(&touchX, &touchY)) {

        // --- JITTER-FILTER (kein "Wackeln") ---
        // Wir wenden den Filter auf die ROHDATEN (0-480 / 0-270) an.

        if (data->state == LV_INDEV_STATE_REL) {
            // Dies ist ein neuer Druck, Rohdaten speichern
            lastRawX = touchX;
            lastRawY = touchY;
        } else {
            // Dies ist ein gehaltener Druck
            // Wenn die Bewegung kleiner als die Schwelle ist...
            if (abs(touchX - lastRawX) < JITTER_THRESHOLD && abs(touchY - lastRawY) < JITTER_THRESHOLD) {
                // ...verwende die *alten* Rohdaten, um das Wackeln zu ignorieren.
                touchX = lastRawX;
                touchY = lastRawY;
            } else {
                // Bewegung ist groß genug, neue Rohdaten speichern
                lastRawX = touchX;
                lastRawY = touchY;
            }
        }

        // --- DEINE KORREKTE MAP-LOGIK ---
        // Jetzt werden die gefilterten Rohdaten auf das Display gemappt.
        data->point.x = map(touchX, 0, 480, 0, TFT_WIDTH - 1);
        data->point.y = map(touchY, 0, 270, 0, TFT_HEIGHT - 1);

        data->state = LV_INDEV_STATE_PR;

        // --- PERFORMANCE-FIX (kein Stottern) ---
        // Alle anderen Serial.print-Ausgaben müssen auch entfernt bleiben.

    } else {
        // Finger wurde losgelassen
        data->state = LV_INDEV_STATE_REL;
    }
}

void setup() {
    Serial.begin(115200);

    // Display initialisieren
    tft.begin();
    tft.setRotation(0);
    tft.setBrightness(255);

    // Touch initialisieren
    if (!touch.begin()) {
        Serial.println("Touch controller initialization failed!");
        // Fehlerbehandlung - z.B. weitermachen ohne Touch oder Fehlermeldung
    } else {
        Serial.println("Touch controller initialized successfully");
    }

    // I2C initialisieren
    i2cComm.begin();

    // LVGL initialisieren
    lv_init();

    // Buffer allokieren
    disp_draw_buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * TFT_WIDTH * 50, MALLOC_CAP_SPIRAM);
    disp_draw_buf2 = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * TFT_WIDTH * 50, MALLOC_CAP_SPIRAM);

    if (!disp_draw_buf || !disp_draw_buf2) {
        disp_draw_buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * TFT_WIDTH * 10, MALLOC_CAP_INTERNAL | MALLOC_CAP_DMA);
        lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, TFT_WIDTH * 10);
    } else {
        lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, disp_draw_buf2, TFT_WIDTH * 50);
    }

    // Display-Treiber
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = TFT_WIDTH;
    disp_drv.ver_res = TFT_HEIGHT;
    disp_drv.flush_cb = display_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    // Touch-Treiber
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = touchpad_read;
    lv_indev_drv_register(&indev_drv);

    // UI Manager starten
    uiManager.begin();

    Serial.println("Setup complete!");
}

void loop() {
    lv_timer_handler();

    // I2C Akku-Daten alle 5 Sekunden abrufen
    if (millis() - lastI2CRequest >= I2C_INTERVAL) {
        if (i2cComm.requestAkkuData()) {
            uiManager.updateAkkuData();
        }
        lastI2CRequest = millis();
    }

    delay(5);
}