/*
 * Part of USB HID gamepad STM32 based solution.
 * Contains descriptor concatenation function.
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

#include "gamepad_desc.h"

// Concatenation to make descriptors in request readable form
int descCat(uint8_t *in, uint8_t *out, int prev, uint16_t size, uint16_t mainLen) {
    for( int index = prev ; (index<mainLen) && (index<size) ; ++index) {
        out[index] = in[index - prev];
    }
    return index;
}
