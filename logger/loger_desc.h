#ifndef H_LOGER_DESC
#define H_LOGER_DESC
/*
 * Part of USB HID vcp STM32 based solution.
 * All descriptors for simplest USB 2.0 HID vcp with D-pad and two buttons
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
#include "usb_core.h"

// descriptor size
#define vcpDeviseDescSize 18
#define vcpConfigurationDescSize 9
#define vcpInterfaceDescSize 9
#define vcpInEndpDescSize 7
#define vcpHidDescSize  9
#define vcpConfTotalSize    vcpConfigurationDescSize + \
 vcpInterfaceDescSize + vcpInEndpDescSize + vcpHidDescSize
#define vcpReportDescSize   63//54
#define vcpDeviceQualifierSize   10
#define stringLangIdSize 4
#define vcpStringVendorSize 14
#define vcpStringProductSize 12


// descriptors
const uint8_t vcpDeviseDesc[vcpDeviseDescSize] =
{
    vcpDeviseDescSize,       // bLenght
    0x01,       // bDescriptorType, Device descriptor
    0x00,0x02,  // bcdUSB, usb 2.0
    0x02,       // bDeviceClass, CDC
    0x02,       // bDeviceSubclass, abstract control model
    0x02,       // bDeviceProtocol, not used
    0x40,       // bMaxPacketSize0, maximum size 64 byte
    0x04,0x83,  // idVendor, SiLabs 0xc4 0x10 st 0x83 0x04
    0x57,0x40,  // idProduct st 0x2c 0x57
    0x00,0x02,  // bcdDevice
    0x01,       // iManufacter
    0x02,       // iProduct
    0x00,       // iSerialNumber
    0x01        // bNumConfigurations
};

const uint8_t vcpConfigurationDesc[vcpConfigurationDescSize] =
{
    vcpConfigurationDescSize,       // bLenght
    0x02,       // bDescriptorType, Configuration descriptor
    vcpConfTotalSize, 0x00, // TotalLenght
    0x02,       // bNumInterfaces
    0x01,       // bConfigurationValue
    0x00,       // iConfiguration
    0xa0,       // bmAttributes, self-powered
    0x32        // maxPower, 100mA
};

// configuration interface (CDC standard obliges)
const uint8_t vcpInterface0Desc[vcpInterfaceDescSize] =
{
    vcpInterfaceDescSize,       // bLenght
    0x04,       // bDescriptorType, Interface descriptor
    0x00,       // bInterfaceNumber
    0x00,       // bAlternateSetting
    0x01,       // bNumEndpoints
    0x02,       // bInterfaceClass, Communication interface class
    0x02,       // bInterfaceSubClass, Abstract control Model
    0x01,       // bInterfaceProtocol, AT commands
    0x00        // bInterface
};

// input/output interface
const uint8_t vcpInterface1Desc[vcpInterfaceDescSize] =
{
    vcpInterfaceDescSize,       // bLenght
    0x04,       // bDescriptorType, Interface descriptor
    0x01,       // bInterfaceNumber
    0x00,       // bAlternateSetting
    0x02,       // bNumEndpoints
    0x02,       // bInterfaceClass, Communication interface class
    0x00,       // bInterfaceSubClass, not used
    0x00,       // bInterfaceProtocol, not used
    0x00        // bInterface
};

const uint8_t vcpInEndpDesc[vcpEndpDescSize] =
{
    vcpEndpDescSize,       // bLenght
    0x05,       // bDescriptorType, endpoint descriptor
    0x81,       // bEndpointAddress, IN endpoint 1
    0x02,       // bMattributes, bulk
    0x40,0x00,  // MaxPacketSize, 64 bytes
    0x00        // bInterval ignore
};

const uint8_t vcpOutEndpDesc[vcpEndpDescSize] =
{
    vcpEndpDescSize,       // bLenght
    0x05,       // bDescriptorType, endpoint descriptor
    0x02,       // bEndpointAddress, IN endpoint 1
    0x02,       // bMattributes, bulk
    0x40,0x00,  // MaxPacketSize, 64 bytes
    0x00        // bInterval ignore
};

const uint8_t vcpConfEndpDesc[vcpEndpDescSize] =
{
    vcpEndpDescSize,       // bLenght
    0x05,       // bDescriptorType, endpoint descriptor
    0x83,       // bEndpointAddress, IN endpoint 3
    0x03,       // bMattributes, Interrupt
    0x40,0x00,  // MaxPacketSize, 64 bytes
    0xff        // bInterval ignore
};

const uint8_t vcpHidDesc[vcpHidDescSize] =
{
    vcpHidDescSize,       // bLenght
    0x21,       // bDescriptorType, HID descriptor
    0x10,0x01,  // bcdHID, HID spec 1.01
    0x00,       // country code SU 0x21
    0x01,       // bNumDescriptors
    0x22,       // bDescriptorType, report descriptor
    vcpReportDescSize,0x00  // wDescriptorLenght
};

// 63 byte variant from standard
const uint8_t vcpReportDesc[vcpReportDescSize] =
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
    0x81, 0x01,         //   input(Cnst,Var,Abs)
    // no leds
    0x95, 0x01, //   REPORT_COUNT (5)
	0x75, 0x01, //   REPORT_SIZE (1)
	0x05, 0x08, //   USAGE_PAGE (LEDs)
	0x19, 0x01, //   USAGE_MINIMUM (Num Lock)
	0x29, 0x01, //   USAGE_MAXIMUM (Num Lock)
	0x91, 0x02, //   OUTPUT (Data,Var,Abs) ; LED report
	0x95, 0x01, //   REPORT_COUNT (1)
	0x75, 0x07, //   REPORT_SIZE (3)
	0x91, 0x01, //   OUTPUT (Cnst,Var,Abs) ; LED report padding
    // buttons array (6 buttons pressed simulateously)
    0x95, 0x06,         //   report_count(6)
    0x75, 0x08,         //   report_size(8)
    0x15, 0x00,         //   logical minimum(0)
    0x25, 0x65,         //   logical maximum(101)
    0x05, 0x07,         //  usage_page(Keyboard)
    0x19, 0x00,         //   usage_minimum(0)
    0x29, 0x81,         //   usage_maximum(Keyboard Application)65
    0x81, 0x00,         //   input(Data,Ary,Abs)
    0xc0                // end_collection (application)
};

const uint8_t vcpDeviceQualifier[vcpDeviceQualifierSize] =
{
    vcpDeviceQualifierSize,  // bLenght
    0x06,       // device qualifier type
    0x00,0x02,  // bcdUSB, usb 2.0
    0x00,       // bDeviceClass,
    0x00,       // bDeviceSubclass, not used
    0x00,       // bDeviceProtocol
    0x40,       // bMaxPacketSize0, maximum pack size for the other conf
    0x00,       // bNumConfigurations, number of the other speed conf
    0x00,       // bReserved
};

const uint8_t stringLangId[stringLangIdSize] =
{
    stringLangIdSize,
    0x03,
    0x09,
    0x04
};

const uint8_t vcpStringVendor[remoteStringVendorSize] =
{
    remoteStringVendorSize,
    0x03,
    'd',0,'l',0,'t',0,'e',0,'c',0,'h',0
};

const uint8_t vcpKbdStringProduct[remoteStringProductSize] =
{
    remoteStringProductSize,
    0x03,
    'l',0,'o',0,'g',0,'e',0,'r',0
};

const descriptorsTyp remoteDesc = {
    vcpDeviseDescSize,
    vcpConfigurationDescSize,
    vcpInterfaceDescSize,
    vcpInEndpDescSize,
    vcpHidDescSize,
    vcpConfTotalSize,
    vcpReportDescSize,
    stringLangIdSize,
    remoteStringVendorSize,
    remoteStringProductSize,
    remoteDeviceQualifierSize,
    vcpDeviseDesc,
    vcpConfigurationDesc,
    vcpInterfaceDesc,
    vcpInEndpDesc,
    vcpHidDesc,
    vcpReportDesc,
    stringLangId,
    remoteStringVendor,
    remoteKbdStringProduct,
    remoteDeviceQualifier
};

#endif
