#ifndef H_USART
#define H_USART
/*
 * Part of Belkin STM32 HAL, basic usart functions.
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
#include <inttypes.h>
#include "../lib/STM32F103_CMSIS/stm32f103.h"

// linecoding parameters
#define LINECODING_SIZE 7
typedef struct {
  uint32_t dwDTERate;
  uint8_t bCharFormat;
  uint8_t bParityType;
  uint8_t bDataBits;
} lineCodingTyp;
enum {
  LINE_STOP_BIT_1 = 0,
  LINE_STOP_BIT_1P5,
  LINE_STOP_BIT_2
};
enum {
  LINE_PARITY_NONE = 0,
  LINE_PARITY_ODD,
  LINE_PARITY_EVEN,
  LINE_PARITY_MARK,
  LINE_PARITY_SPACE
};

// port setup
#define UART_TX 8
#define UART_RX 9
// timeout setup
#define PSC_400BAUD     SYSTEM_CLOCK/4000
#define TOUT_CALC(baud) baud/100
// count of bytes
#define RX_SIZE 16
#define TX_SIZE 64

void uartInit(void);
void uartSetLine(lineCodingTyp *line);
void uartTx(uint8_t *data, int size);

#endif
