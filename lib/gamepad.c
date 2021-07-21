/*
 * USB HID gamepad STM32 based solution. Call init, enjoy.
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

#include "../libopencm3/include/libopencm3/cm3/nvic.h"
#include "mysys.h"
#include "usb_core.h"
#include "gamepad_port.h"
#include "gamepad.h"

void gamepadInit()
{
    sysClk();
    portInit();
    usbCoreInit();
}

// all usb events handled in interrupt
void usb_lp_can_rx0_isr()
{
    usbCore();
}
