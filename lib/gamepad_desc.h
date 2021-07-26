#ifndef H_GAMEPAD_DESC
#define H_GAMEPAD_DESC
/*
 * Part of USB HID gamepad STM32 based solution.
 * All descriptors for simplest USB 2.0 HID gamepad with D-pad and two buttons
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
 #include <inttypes.h>

// descriptor size
#define gamepadDeviseDescSize 18
#define gamepadConfigurationDescSize 9
#define gamepadInterfaceDescSize 9
#define gamepadInEndpDescSize 7
#define gamepadHidDescSize  9
#define gamepadConfTotalSize    gamepadConfigurationDescSize + \
    gamepadInterfaceDescSize + gamepadInEndpDescSize + gamepadHidDescSize
#define gamepadReportDescSize   55
#define stringLangIdSize 4
#define gamepadStringVendorSize 6
#define gamepadStringProductSize 8

// descriptors
const uint8_t gamepadDeviseDesc[gamepadDeviseDescSize] =
{
    gamepadDeviseDescSize,       // bLenght
    0x01,       // bDescriptorType, Device descriptor
    0x00,0x02,  // bcdUSB, usb 2.0
    0x03,       // bDeviceClass, HID
    0x00,       // bDeviceSubclass, not used
    0x00,       // bDeviceProtocol, not used
    0x40,       // bMaxPacketSize0, maximum size 64 byte
    0x83,0x04,  // idVendor, SiLabs 0xc4 0x10
    0x75,0x40,  // idProduct
    0x00,0x01,  // bcdDevice
    0x01,       // iManufacter
    0x02,       // iProduct
    0x00,       // iSerialNumber
    0x01        // bNumConfigurations
};

const uint8_t gamepadConfigurationDesc[gamepadConfigurationDescSize] =
{
    gamepadConfigurationDescSize,       // bLenght
    0x02,       // bDescriptorType, Configuration descriptor
    gamepadConfTotalSize, 0x00, // TotalLenght
    0x01,       // bNumInterfaces
    0x01,       // bConfigurationValue
    0x00,       // iConfiguration
    0xe0,       // bmAttributes, self-powered
    0x32        // maxPower, 100mA
};

const uint8_t gamepadInterfaceDesc[gamepadInterfaceDescSize] =
{
    gamepadInterfaceDescSize,       // bLenght
    0x04,       // bDescriptorType, Interface descriptor
    0x00,       // bInterfaceNumber
    0x00,       // bAlternateSetting
    0x01,       // bNumEndpoints
    0x03,       // bInterfaceClass, HID
    0x00,       // bInterfaceSubClass,
    0x00,       // bInterfaceProtocol
    0x00        // bInterface
};

const uint8_t gamepadInEndpDesc[gamepadInEndpDescSize] =
{
    gamepadInEndpDescSize,       // bLenght
    0x05,       // bDescriptorType, endpoint descriptor
    0x81,       // bEndpointAddress, IN endpoint 1
    0x03,       // bMattributes, interrupt endpoint
    0x04,0x00,  // MaxPacketSize, 4 bytes
    0x20        // bInterval 32 ms
};

const uint8_t gamepadHidDesc[gamepadHidDescSize] =
{
    0x09,       // bLenght
    0x21,       // bDescriptorType, HID descriptor
    0x00,0x01,  // bcdHID, HID spec 1.01
    0x33,       // country code SU
    0x01,       // bNumDescriptors
    0x22,       // bDescriptorType, report descriptor
    gamepadReportDescSize,0x00  // wDescriptorLenght
};

// report descriptor for gamepad w d-pad and two buttons
const uint8_t gamepadReportDesc[gamepadReportDescSize] =
{
    0x05, 0x01,         // usage_page(Generic Desctop)
    0x09, 0x05,         // usage(Game pad)
    0xa1, 0x01,         // collection(Application)
    0x05, 0x01,         //  usage_page(Generic Desctop)
    0x09, 0x01,         //  usage(Pointer)
    0xa1, 0x00,         //   collection(Physical)
    0x09, 0x39,         //   usage(Hat switch)
    0x15, 0x00,         //   logical minimum(0)
    0x25, 0x07,         //   logical maximum(7)
    0x35, 0x00,         //   physical minimum(0)
    0x46, 0x3b, 0x01,   //   physical maximum(315)
    0x65, 0x14,         //   unit(Eng Rot:Angular Pos)
    0x95, 0x01,         //   report_count(1)
    0x75, 0x04,         //   report_size(4)
    0x81, 0x42,         //   input(Data,Var,Abs,Null)
    0xc0,               //  end_collection
    0x05, 0x09,         //  usage_page(Button)
    0x15, 0x00,         //  logical minimum(0)
    0x25, 0x01,         //  logical maximum(1)
    0x95, 0x02,         //  report_count(2)
    0x75, 0x01,         //  report_size(1)
    0x81, 0x02,         //  input(Data,Var,Abs)
// byte alingment
    0x95, 0x01,         //  report_count(1)
    0x75, 0x02,         //  report_size(2)
    0x81, 0x01,         //  input(Const)
    0xc0                // end_collection
};

const uint8_t stringLangId[stringLangIdSize] =
{
    stringLangIdSize,
    0x03,
    0x09,
    0x04
};

const uint8_t gamepadStringVendor[gamepadStringVendorSize] =
{
    gamepadStringVendorSize,
    0x03,
    'z',0,'x',0
};

const uint8_t gamepadStringProduct[gamepadStringProductSize] =
{
    gamepadStringProductSize,
    0x03,
    'j',0,'o',0,'y',0
};

#endif
