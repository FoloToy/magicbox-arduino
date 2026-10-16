#pragma once
// MagicBox HW0.2.0 / ESP32 hardware facts; the only supported board.
constexpr int BSP_MIC_BCLK = 23, BSP_MIC_DATA = 22, BSP_MIC_WS = 21;
constexpr int BSP_SPEAKER_BCLK = 2, BSP_SPEAKER_DATA = 15, BSP_SPEAKER_WS = 4;
constexpr int BSP_VOLUME = 34, BSP_RGB = 27, BSP_INDICATOR = 13;
constexpr int BSP_KEYS[] = {36, 14, 26}; // GPIO36 requires the PCB's external pull-up.
constexpr const char *BSP_BOARD_NAME = "MagicBox HW 0.2.0 / ESP32";
constexpr unsigned BSP_KEY_COUNT = sizeof(BSP_KEYS) / sizeof(BSP_KEYS[0]);
constexpr unsigned BSP_SAMPLE_RATE = 16000;
