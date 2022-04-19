/*
 *  Part of USB HID IR adapter. Detects IR codes from two codings.
 *
 * Copyright 2022 Mikhail Belkin <dltech174@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "ir_decoder.h"

uint8_t  necDecode(uint8_t data, uint8_t  addr);
uint16_t samsungDecode(uint8_t data, uint16_t addr);

uint16_t detect(uint8_t data, uint16_t addr)
{
    uint16_t ret = 0;
//    ret = necDecode(data, (uint8_t)addr);
    ret = samsungDecode(data, addr);
    return ret;
}

uint8_t necDecode(uint8_t data, uint8_t inAddr)
{
    static int bitCnt = 0;
    static uint8_t prev = 1;
    static uint8_t isStart = 0;
    static int oneCnt = 0;
    static int nullCnt = 0;
    static uint32_t word = 0;
//    uint8_t addr;
    uint8_t command;
    // detect start bit
    if((prev == 0) && (data == 1) && (nullCnt > 20)) {
        isStart = 1;
        bitCnt = 0;
        word = 0;
    }
    // detect one
    if((prev == 1) && (data == 0) && (isStart > 0) && (oneCnt > 7) && (oneCnt < 11)) {
        word += (uint32_t)(1<<bitCnt);
        ++bitCnt;
    }
    // detect null
    if((prev == 1) && (data == 0) && (isStart > 0) && (oneCnt < 7)) {
        ++bitCnt;
    }
    // decode command
    if((bitCnt >= 32) && ((word & 0xff) == (~(word >> 8) & 0xff)) && \
      ((word >> 16 & 0xff) == (~(word >> 24) & 0xff)) && ((inAddr == 0xff) || (inAddr == (uint8_t)word))) {
//        addr = (uint8_t)word;
        command = (uint8_t)(word >> 16);
        isStart = 0;
        bitCnt = 0;
        word = 0;
        return command;
    }
    // null counters in case of error
    if(bitCnt >= 32) {
        bitCnt = 0;
        isStart = 0;
        word = 0;
    }
    // edge detector
    if(data == 1) ++oneCnt;
    else oneCnt = 0;
    if(data == 0) ++nullCnt;
    else nullCnt = 0;
    prev = data;
    return 0xff;
}

uint16_t samsungDecode(uint8_t data, uint16_t inAddr)
{
    static uint8_t prev = 1;
    static uint8_t isStart = 0;
    static int oneCnt = 0;
    static int nullCnt = 0;
    static int bitCnt = 0;
    static uint32_t word = 0;
//    uint16_t addr;
    uint16_t command;
    // detect start bit
    if((prev == 0) && (data == 1) && (nullCnt > 20) && (nullCnt < 25)) {
        isStart = 1;
        word = 0;
        bitCnt = 0;
    }
    // detect one
    if((prev == 1) && (data == 0) && (isStart > 0) && (oneCnt > 7) && (oneCnt < 11)) {
        word += (uint32_t)1<<bitCnt;
        ++bitCnt;
    }
    // detect null
    if((prev == 1) && (data == 0) && (isStart > 0) && (oneCnt < 7)) {
        ++bitCnt;
    }
    // decode command
    if( (bitCnt >= 32) && (isStart > 0) && ((inAddr == 0xffff) || (inAddr == (uint16_t)word))) {
//        addr = (uint16_t)word;
        command = (uint16_t)(word >> 16);
        bitCnt = 0;
        isStart = 0;
        word = 0;
        return command;
    }
    if((bitCnt >= 32) || (oneCnt > 30)) {
        bitCnt = 0;
        isStart = 0;
        word = 0;
    }
    // edge detector
    if(data == 1) ++oneCnt;
    else oneCnt = 0;
    if(data == 0) ++nullCnt;
    else nullCnt = 0;
    prev = data;
    return 0xffff;
}
