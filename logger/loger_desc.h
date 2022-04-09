#ifndef H_LOGER_DESC
#define H_LOGER_DESC
/*
 * Part of USB VCP on STM32.
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
#define vcpOutEndpDescSize 7
#define vcpFunctionalSize 14
#define vcpConfTotalSize    vcpConfigurationDescSize + \
 vcpInterfaceDescSize + vcpInEndpDescSize + vcpOutEndpDescSize + vcpFunctionalSize
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
    0x00,       // bDeviceProtocol, not used
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
    0x01,       // bNumInterfaces
    0x01,       // bConfigurationValue
    0x00,       // iConfiguration
    0xa0,       // bmAttributes, self-powered
    0x32        // maxPower, 100mA
};

// configuration interface (CDC standard obliges)
const uint8_t vcpInterfaceDesc[vcpInterfaceDescSize] =
{
    vcpInterfaceDescSize,       // bLenght
    0x04,       // bDescriptorType, Interface descriptor
    0x00,       // bInterfaceNumber
    0x00,       // bAlternateSetting
    0x02,       // bNumEndpoints
    0x02,       // bInterfaceClass, Communication interface class
    0x02,       // bInterfaceSubClass, Abstract control Model
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

const uint8_t vcpFunctional[vcpFunctionalSize] =
{
    // header functional descriptor
    5,          // bFunctionLength
    0x24,       // bDescriptorType, CS_INTERFACE constant is functional descr type
    0x00,       // bDescriptorSubtype, header functional
    0x01,       // bcdCDC, USB CDC standard version (1.01)
    0x10,
    // Abstract Control Management Functional Descriptor
    4,          // bFunctionLength
    0x24,       // bDescriptorType, CS_INTERFACE constant is functional descr type
    0x02,       // bDescriptorSubtype, Abstract control model functional
    0x02,       // bmCapabilities, support set/get lineCoding
    // Call Management Functional Descriptor
    5,          // bFunctionLength
    0x24,       // bDescriptorType, CS_INTERFACE constant is functional descr type
    0x01,       // bDescriptorSubtype, Call management functional
    0x00,       // bmCapabilities, do not support call maqnagement
    0x00,       // bDataInterface, optional interface for call management (none)
};

const uint8_t vcpDeviceQualifier[vcpDeviceQualifierSize] =
{
    vcpDeviceQualifierSize,  // bLenght
    0x06,       // device qualifier type
    0x00,0x02,  // bcdUSB, usb 2.0
    0x02,       // bDeviceClass,
    0x02,       // bDeviceSubclass,
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

const descriptorsTyp usbComDesc = {
    vcpDeviseDescSize,
    vcpConfigurationDescSize,
    vcpInterfaceDescSize,
    vcpInEndpDescSize,
    vcpOutEndpDescSize,
    vcpFunctionalDescSize,
    vcpConfTotalSize,
    stringLangIdSize,
    vcpStringVendorSize,
    vcpStringProductSize,
    vcpDeviceQualifierSize,
    vcpDeviseDesc,
    vcpConfigurationDesc,
    vcpInterfaceDesc,
    vcpInEndpDesc,
    vcpOutEndpDesc,
    vcpFunctionalDesc,
    stringLangId,
    vcpStringVendor,
    vcpStringProduct,
    vcpDeviceQualifier
};

#endif
