#pragma once
// Only hardware facts extracted from the matching product pin configuration.
#if (defined(BSP_MAGICBOX_020) + defined(BSP_MAGICBOX_PRO) + defined(BSP_MAGICBOX_PRO2)) != 1
#error "Select exactly one MagicBox hardware profile"
#endif
#if defined(BSP_MAGICBOX_020)
constexpr int BSP_MIC_BCLK = 23, BSP_MIC_DATA = 22, BSP_MIC_WS = 21;
constexpr int BSP_SPEAKER_BCLK = 2, BSP_SPEAKER_DATA = 15, BSP_SPEAKER_WS = 4;
constexpr int BSP_VOLUME = 34, BSP_RGB = 27, BSP_INDICATOR = 13;
constexpr int BSP_KEYS[] = {36, 14, 26}; // GPIO36 requires the PCB's external pull-up.
constexpr int BSP_I2C_SDA = -1, BSP_I2C_SCL = -1, BSP_ACCEL_IRQ = -1;
constexpr const char *BSP_BOARD_NAME = "MagicBox HW 0.2.0 / ESP32";
#else
constexpr int BSP_MIC_BCLK = 42, BSP_MIC_DATA = 2, BSP_MIC_WS = 1;
constexpr int BSP_SPEAKER_BCLK = 40;
#if defined(BSP_MAGICBOX_PRO)
constexpr int BSP_SPEAKER_DATA = 39, BSP_SPEAKER_WS = 41;
constexpr const char *BSP_BOARD_NAME = "MagicBox Pro HW 1.0.0 / ESP32-S3";
#else
constexpr int BSP_SPEAKER_DATA = 41, BSP_SPEAKER_WS = 39;
constexpr const char *BSP_BOARD_NAME = "MagicBox Pro2 HW 2.1.0 / ESP32-S3";
#endif
constexpr int BSP_VOLUME = 8, BSP_RGB = 46, BSP_INDICATOR = -1;
constexpr int BSP_KEYS[] = {4, 3, 6};
constexpr int BSP_I2C_SDA = 12, BSP_I2C_SCL = 13, BSP_ACCEL_IRQ = 14;
#endif
constexpr unsigned BSP_KEY_COUNT = sizeof(BSP_KEYS) / sizeof(BSP_KEYS[0]);
constexpr unsigned BSP_SAMPLE_RATE = 16000;
