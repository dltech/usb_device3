

#define gamepadHidDescSize  7
uint8_t gamepadHidDesc[gamepadHidDescSize] =
{
    0x07,       // bLenght
    0x00,       // bDescriptorType
    0x00, 0x00, // bcdHID
    0x33,       // country code SU
    0x01,       // bNumDescriptors
    0x00,       // bDescriptorType
    0x00, 0x37  // wDescriptorLenght
}

// report descriptor for gamepad w d-pad and two buttons
#define gamepadreportDescSize   55
uint8_t gamepadReportDesc[gamepadreportDescSize] =
{
    0x05, 0x01,         // usage_page(Generic Desctop)
    0x09, 0x05,         // usage(Game pad)
    0xa1, 0x01,         // collection(Application)
    0x05, 0x01,         //  usage_page(Generic Desctop)
    0x09, 0x01,         //  usage(Pointer)
    0xa1, 0x00,         //   collection(Physical)
    0x09, 0x39,         //   usage(Hat switch)
    0x15, 0x00,         //   logical minimum(0)
    0x25, 0x03,         //   logical maximum(3)
    0x35, 0x00,         //   physical minimum(0)
    0x46, 0x0e, 0x01    //   physical maximum(270)
    0x65, 0x12,         //   unit(Sl Rot:Angular Pos)
    0x95, 0x01,         //   report_count(1)
    0x75, 0x04,         //   report_size(4)
    0x81, 0x42,         //   input(Data,Var,Abs,Null)
    0xc0                //  end_collection
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
