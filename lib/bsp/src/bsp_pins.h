#pragma once
// Sole board: MagicBox HW v2.1.0, verified device identity and product pin configuration.
constexpr int BSP_MIC_BCLK = 42, BSP_MIC_DATA = 2, BSP_MIC_WS = 1;
constexpr int BSP_SPEAKER_BCLK = 40, BSP_SPEAKER_DATA = 41, BSP_SPEAKER_WS = 39;
constexpr int BSP_VOLUME = 8, BSP_RGB = 46;
constexpr int BSP_KEYS[] = {4, 3};
constexpr const char *BSP_BOARD_NAME = "MagicBox HW v2.1.0 / ESP32-S3";
constexpr unsigned BSP_KEY_COUNT = sizeof(BSP_KEYS) / sizeof(BSP_KEYS[0]);
constexpr unsigned BSP_SAMPLE_RATE = 16000;
