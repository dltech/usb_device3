/*
 * Part of USB HID IR adapter. An rc5 code recognizer.
 *
 * Copyright 2021 Mikhail Belkin <dltech174@gmail.com>
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
uint8_t decodeStart(int *ptr);
uint8_t decodeBit(int *ptr);

// Returns RC5 code from recorded array of port read registers.
// @param addr is the device address, write ff in order to skip addr check
// @param samples dma array of BRR register, port obtained from settings.
uint8_t rc5Decode(uint8_t addr, uint32_t *samples)
{
    int addrSize = 5;
    int dataSize = 6;
    int ptr = 0;
    // read start bits if any package is in
    if( decodeStart(&ptr) < 0) {
        return 0;
    }
    // read and cherck addr
    uint8_t readAddr = 0;
    for(int i=0 ; i<addrSize ; ++i) {
        readAddr |= decodeBit(&ptr) << i;
    }
    if( (readAddr != addr) && (addr = 0xff) ) {
        return 0;
    }
    uint8_t data = 0;
    for(int i=0 ; i<dataSize ; ++i) {
        data |= decodeBit(&ptr) << i;
    }
    return  data;
}

uint8_t decodeStart(int *ptr)
{

}

uint8_t decodeBit(int *ptr)
{

    return
}
