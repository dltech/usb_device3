#ifndef H_REMOTE_DESC
#define H_REMOTE_DESC
/*
 * Part of USB HID ledlessKbd STM32 based solution.
 * All descriptors for simplest USB 2.0 HID ledlessKbd with D-pad and two buttons
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
#define ledlessKbdDeviseDescSize 18
#define ledlessKbdConfigurationDescSize 9
#define ledlessKbdInterfaceDescSize 9
#define ledlessKbdInEndpDescSize 7
#define ledlessKbdHidDescSize  9
#define ledlessKbdConfTotalSize    ledlessKbdConfigurationDescSize + \
 ledlessKbdInterfaceDescSize + ledlessKbdInEndpDescSize + ledlessKbdHidDescSize
#define ledlessKbdReportDescSize   45
#define stringLangIdSize 4
#define ledlessKbdStringVendorSize 14
#define ledlessKbdStringProductSize 18

// descriptors
const uint8_t ledlessKbdDeviseDesc[ledlessKbdDeviseDescSize] =
{
    ledlessKbdDeviseDescSize,       // bLenght
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

const uint8_t ledlessKbdConfigurationDesc[ledlessKbdConfigurationDescSize] =
{
    ledlessKbdConfigurationDescSize,       // bLenght
    0x02,       // bDescriptorType, Configuration descriptor
    ledlessKbdConfTotalSize, 0x00, // TotalLenght
    0x01,       // bNumInterfaces
    0x01,       // bConfigurationValue
    0x00,       // iConfiguration
    0xe0,       // bmAttributes, self-powered
    0x32        // maxPower, 100mA
};

const uint8_t ledlessKbdInterfaceDesc[ledlessKbdInterfaceDescSize] =
{
    ledlessKbdInterfaceDescSize,       // bLenght
    0x04,       // bDescriptorType, Interface descriptor
    0x00,       // bInterfaceNumber
    0x00,       // bAlternateSetting
    0x01,       // bNumEndpoints
    0x03,       // bInterfaceClass, HID
    0x01,       // bInterfaceSubClass, bootable (you can use it in bios)
    0x01,       // bInterfaceProtocol, keyboard
    0x00        // bInterface
};

const uint8_t ledlessKbdInEndpDesc[ledlessKbdInEndpDescSize] =
{
    ledlessKbdInEndpDescSize,       // bLenght
    0x05,       // bDescriptorType, endpoint descriptor
    0x81,       // bEndpointAddress, IN endpoint 1
    0x03,       // bMattributes, interrupt endpoint
    0x08,0x00,  // MaxPacketSize, 8 bytes
    0x20        // bInterval 32 ms
};

const uint8_t ledlessKbdHidDesc[ledlessKbdHidDescSize] =
{
    ledlessKbdHidDescSize,       // bLenght
    0x21,       // bDescriptorType, HID descriptor
    0x01,0x01,  // bcdHID, HID spec 1.01
    0x00,       // country code SU 0x33
    0x01,       // bNumDescriptors
    0x22,       // bDescriptorType, report descriptor
    ledlessKbdReportDescSize,0x00  // wDescriptorLenght
};

// standard keyboard descriptor (even boot compatible)
const uint8_t ledlessKbdReportDesc[ledlessKbdReportDescSize] =
{
    0x05, 0x01,         // usage_page(Generic Desctop)
    0x09, 0x06,         // usage(Keyboard)
    0xa1, 0x01,         // collection(Application)
    0x05, 0x07,         //  usage_page(Keyboard)
    0x19, 0xe0,         //   usage_minimum(Keyboard LeftControl)
    0x29, 0xe7,         //   usage_maximum(Keyboard Right GUI)
    0x15, 0x00,         //   logical minimum(0)
    0x25, 0x01,         //   logical maximum(1)
    // modifier byte (ctrl, alt, win)
    0x75, 0x01,         //   report_size(1);  (standard obliges)
    0x95, 0x08,         //   report_count(8)
    0x81, 0x02,         //   input(Data,Var,Abs)
    // reserved byte
    0x95, 0x01,         //   report_count(1)
    0x75, 0x08,         //   report_size(8)
    0x81, 0x03,         //   input(Cnst,Var,Abs)
    // no leds
    // buttons array (6 buttons pressed simulateously)
    0x95, 0x06,         //   report_count(6)
    0x75, 0x08,         //   report_size(8)
    0x15, 0x00,         //   logical minimum(0)
    0x25, 0x65,         //   logical maximum(101)
    0x05, 0x07,         //  usage_page(Keyboard)
    0x19, 0x00,         //  usage_minimum(0)
    0x29, 0x65,         //  usage_maximum(Keyboard Application)
    0x81, 0x00,         //  input(Data,Ary,Abs)
    0xc0                // end_collection (application)
};

const uint8_t stringLangId[stringLangIdSize] =
{
    stringLangIdSize,
    0x03,
    0x09,
    0x04
};

const uint8_t remoteStringVendor[remoteStringVendorSize] =
{
    ledlessKbdStringVendorSize,
    0x03,
    'd',0,'l',0,'t',0,'e',0,'c',0,'h',0
};

const uint8_t remoteKbdStringProduct[remoteStringProductSize] =
{
    ledlessKbdStringProductSize,
    0x03,
    't',0,'v',0,' ',0,
    'r',0,'e',0,'m',0,'o',0,'t',0,'e',0
};

#endif
