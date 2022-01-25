#ifndef H_DMA_REGS
#define H_DMA_REGS
/*
 * Part of Belkin STM32 HAL, DMA register definitions of STM32F1xx MCUs.
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

#include "memorymap.h"

/* DMA interrupt status register */
#define DMA1_ISR    MMIO32(DMA1_BASE + 0x000)
#define DMA2_ISR    MMIO32(DMA2_BASE + 0x000)
// Channel x transfer error clear
#define TEIF1      0x0000008
#define TEIF2      0x0000080
#define TEIF3      0x0000800
#define TEIF4      0x0008000
#define TEIF5      0x0080000
#define TEIF6      0x0800000
#define TEIF7      0x8000000
// Channel x half transfer clear
#define HTIF1      0x0000004
#define HTIF2      0x0000040
#define HTIF3      0x0000400
#define HTIF4      0x0004000
#define HTIF5      0x0040000
#define HTIF6      0x0400000
#define HTIF7      0x4000000
// Channel x transfer complete clear
#define TCIF1      0x0000002
#define TCIF2      0x0000020
#define TCIF3      0x0000200
#define TCIF4      0x0002000
#define TCIF5      0x0020000
#define TCIF6      0x0200000
#define TCIF7      0x2000000
// Channel x global interrupt clear
#define GIF1      0x0000001
#define GIF2      0x0000010
#define GIF3      0x0000100
#define GIF4      0x0001000
#define GIF5      0x0010000
#define GIF6      0x0100000
#define GIF7      0x1000000

/* DMA interrupt flag clear register */
#define DMA1_IFCR   MMIO32(DMA1_BASE + 0x004)
#define DMA2_IFCR   MMIO32(DMA2_BASE + 0x004)
// Channel x transfer error clear
#define CTEIF1      0x0000008
#define CTEIF2      0x0000080
#define CTEIF3      0x0000800
#define CTEIF4      0x0008000
#define CTEIF5      0x0080000
#define CTEIF6      0x0800000
#define CTEIF7      0x8000000
// Channel x half transfer clear
#define CHTIF1      0x0000004
#define CHTIF2      0x0000040
#define CHTIF3      0x0000400
#define CHTIF4      0x0004000
#define CHTIF5      0x0040000
#define CHTIF6      0x0400000
#define CHTIF7      0x4000000
// Channel x transfer complete clear
#define CTCIF1      0x0000002
#define CTCIF2      0x0000020
#define CTCIF3      0x0000200
#define CTCIF4      0x0002000
#define CTCIF5      0x0020000
#define CTCIF6      0x0200000
#define CTCIF7      0x2000000
// Channel x global interrupt clear
#define CGIF1      0x0000001
#define CGIF2      0x0000010
#define CGIF3      0x0000100
#define CGIF4      0x0001000
#define CGIF5      0x0010000
#define CGIF6      0x0100000
#define CGIF7      0x1000000

/* DMA channel x configuration registers */
#define DMA1_CCR1   MMIO32(DMA1_BASE + 0x008)
#define DMA2_CCR1   MMIO32(DMA2_BASE + 0x008)
#define DMA1_CCR2   MMIO32(DMA1_BASE + 0x01c)
#define DMA2_CCR2   MMIO32(DMA2_BASE + 0x01c)
#define DMA1_CCR3   MMIO32(DMA1_BASE + 0x030)
#define DMA2_CCR3   MMIO32(DMA2_BASE + 0x030)
#define DMA1_CCR4   MMIO32(DMA1_BASE + 0x044)
#define DMA2_CCR4   MMIO32(DMA2_BASE + 0x044)
#define DMA1_CCR5   MMIO32(DMA1_BASE + 0x058)
#define DMA2_CCR5   MMIO32(DMA2_BASE + 0x058)
#define DMA1_CCR6   MMIO32(DMA1_BASE + 0x06c)
#define DMA2_CCR6   MMIO32(DMA2_BASE + 0x06c)
#define DMA1_CCR7   MMIO32(DMA1_BASE + 0x080)
#define DMA2_CCR7   MMIO32(DMA2_BASE + 0x080)
// Memory to memory mode
#define MEM2MEM         0x4000
// Channel priority level
#define PL_LOW          0x0000
#define PL_MEDIUM       0x1000
#define PL_HIGH         0x2000
#define PL_VERY_HIGH    0x3000
// Memory size
#define MSIZE_8BIT      0x0000
#define MSIZE_16BIT     0x0400
#define MSIZE_32BIT     0x0800
// Peripheral size
#define PSIZE_8BIT      0x0000
#define PSIZE_16BIT     0x0100
#define PSIZE_32BIT     0x0200
// Memory increment mode
#define MINC            0x0080
// Peripheral increment mode
#define PINC            0x0040
// Circular mode
#define CIRC            0x0020
// Data transfer direction
#define DIR             0x0010
// Transfer error interrupt enable
#define TEIE            0x0008
// Half transfer interrupt enable
#define HTIE            0x0004
// Transfer complete interrupt enable
#define TCIE            0x0002
// Channel enable
#define DMA_EN          0x0001

/* DMA channel x number of data registers */
#define DMA1_CNDTR1 MMIO32(DMA1_BASE + 0x00c)
#define DMA2_CNDTR1 MMIO32(DMA2_BASE + 0x00c)
#define DMA1_CNDTR2 MMIO32(DMA1_BASE + 0x020)
#define DMA2_CNDTR2 MMIO32(DMA2_BASE + 0x020)
#define DMA1_CNDTR3 MMIO32(DMA1_BASE + 0x034)
#define DMA2_CNDTR3 MMIO32(DMA2_BASE + 0x034)
#define DMA1_CNDTR4 MMIO32(DMA1_BASE + 0x048)
#define DMA2_CNDTR4 MMIO32(DMA2_BASE + 0x048)
#define DMA1_CNDTR5 MMIO32(DMA1_BASE + 0x05c)
#define DMA2_CNDTR5 MMIO32(DMA2_BASE + 0x05c)
#define DMA1_CNDTR6 MMIO32(DMA1_BASE + 0x070)
#define DMA2_CNDTR6 MMIO32(DMA2_BASE + 0x070)
#define DMA1_CNDTR7 MMIO32(DMA1_BASE + 0x084)
#define DMA2_CNDTR7 MMIO32(DMA2_BASE + 0x084)
// NDT[15:0]: Number of data to transfer

/* DMA channel x peripheral address register */
#define DMA1_CPAR1  MMIO32(DMA1_BASE + 0x010)
#define DMA2_CPAR1  MMIO32(DMA2_BASE + 0x010)
#define DMA1_CPAR2  MMIO32(DMA1_BASE + 0x024)
#define DMA2_CPAR2  MMIO32(DMA2_BASE + 0x024)
#define DMA1_CPAR3  MMIO32(DMA1_BASE + 0x038)
#define DMA2_CPAR3  MMIO32(DMA2_BASE + 0x038)
#define DMA1_CPAR4  MMIO32(DMA1_BASE + 0x04c)
#define DMA2_CPAR4  MMIO32(DMA2_BASE + 0x04c)
#define DMA1_CPAR5  MMIO32(DMA1_BASE + 0x060)
#define DMA2_CPAR5  MMIO32(DMA2_BASE + 0x060)
#define DMA1_CPAR6  MMIO32(DMA1_BASE + 0x074)
#define DMA2_CPAR6  MMIO32(DMA2_BASE + 0x074)
#define DMA1_CPAR7  MMIO32(DMA1_BASE + 0x088)
#define DMA2_CPAR7  MMIO32(DMA2_BASE + 0x088)
// PA[31:0]: Peripheral address

/* DMA channel x memory address register */
#define DMA1_CMAR1  MMIO32(DMA1_BASE + 0x014)
#define DMA2_CMAR1  MMIO32(DMA2_BASE + 0x014)
#define DMA1_CMAR2  MMIO32(DMA1_BASE + 0x028)
#define DMA2_CMAR2  MMIO32(DMA2_BASE + 0x028)
#define DMA1_CMAR3  MMIO32(DMA1_BASE + 0x03c)
#define DMA2_CMAR3  MMIO32(DMA2_BASE + 0x03c)
#define DMA1_CMAR4  MMIO32(DMA1_BASE + 0x050)
#define DMA2_CMAR4  MMIO32(DMA2_BASE + 0x050)
#define DMA1_CMAR5  MMIO32(DMA1_BASE + 0x064)
#define DMA2_CMAR5  MMIO32(DMA2_BASE + 0x064)
#define DMA1_CMAR6  MMIO32(DMA1_BASE + 0x078)
#define DMA2_CMAR6  MMIO32(DMA2_BASE + 0x078)
#define DMA1_CMAR7  MMIO32(DMA1_BASE + 0x08c)
#define DMA2_CMAR7  MMIO32(DMA2_BASE + 0x08c)
// MA[31:0]: Memory address

#endif
