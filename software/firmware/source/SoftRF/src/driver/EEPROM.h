/*
 * EEPROMHelper.h
 * Copyright (C) 2016-2022 Linar Yusupov
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef EEPROMHELPER_H
#define EEPROMHELPER_H

#ifdef __cplusplus
#include "../system/SoC.h"
#endif /* __cplusplus */

#if !defined(EXCLUDE_EEPROM)
#if defined(ENERGIA_ARCH_CC13XX) || defined(ENERGIA_ARCH_CC13X2)
#include <EEPROM_CC13XX.h>
#elif defined(ARDUINO_ARCH_SAMD)
#include <FlashAsEEPROM.h>
#else
#ifdef __cplusplus
#include <EEPROM.h>
#endif /* __cplusplus */
#endif /* CC13XX or CC13X2 */
#endif /* EXCLUDE_EEPROM */

#define SOFTRF_EEPROM_MAGIC   0xBABADEDA
#define SOFTRF_EEPROM_VERSION 0x00000060

enum
{
	EEPROM_EXT_LOAD,
	EEPROM_EXT_DEFAULTS,
	EEPROM_EXT_STORE
};

typedef struct Settings {
    uint8_t  mode;          //Normal; Bridge; UAV
    uint8_t  rf_protocol;   //Legacy; OGNTP; P3I; FANET; UAT; 1090ES
    uint8_t  band;          //AUTO; EU; RU; CN; US/CA; NZ; UK; AU; IN; KR; IL (AUTO not recommended as of 28/06/2022)
    uint8_t  aircraft_type; //Glider; Towplane; Powered; Helicopter; UAV; Hangglider; Paraglider; Balloon; Static
    uint8_t  txpower;       //Full; Low; Off
    uint8_t  volume;        //Loud; Low; Off
    uint8_t  led_num;
    uint8_t  pointer;

    bool     nmea_g:1;      //GNSS
    bool     nmea_p:1;      //Private - SoftRF-specific sentences
    bool     nmea_l:1;      //Legacy - FLARM-specific sentences
    bool     nmea_s:1;      //Sensors
    bool     resvd1:1;
    uint8_t  nmea_out:3;    //Off; Serial; UDP; TCP; Bluetooth (Bluetooth only available for ESP32- and nRF52-platforms)

    uint8_t  bluetooth:3;   //Off; SPP; LE /* Only for ESP32-platform with built-in Bluetooth with SPP-Serial Port Profile and LE-Low Energy*/
    uint8_t  alarm:3;       //None; Distance; Vector
    bool     stealth:1;     //Stealth Mode for Legacy- and OGNTP-protocol
    bool     no_track:1;    //No Track Mode for Legacy- and FANET-protocol

    uint8_t  gdl90:3;       //Off; Serial; UDP; Bluetooth
    uint8_t  d1090:3;       //Off; Serial; Bluetooth
    uint8_t  json:2;

    uint8_t  power_save;    //Disabled; WiFi OFF; GNSS; No Receive

    int8_t   freq_corr;     //Frequency Correction /* +/-, kHz */
    uint8_t  resvd2;
    uint8_t  resvd3;
    uint8_t  resvd4;

    /* Use a key provided by (local) gliding contest organizer */
    uint32_t igc_key[4];

} __attribute__((packed)) settings_t;

typedef struct EEPROM_S {
    uint32_t  magic;
    uint32_t  version;
    settings_t settings;
} eeprom_struct_t;

typedef union EEPROM_U {
   eeprom_struct_t field;
   uint8_t raw[sizeof(eeprom_struct_t)];
} eeprom_t;

void EEPROM_setup(void);
void EEPROM_defaults(void);
void EEPROM_store(void);
extern settings_t *settings;

#endif /* EEPROMHELPER_H */
