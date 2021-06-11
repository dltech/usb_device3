
// desc ex from freejoy project
uint8_t JoystickHID_ReportDescriptor[JoystickHID_SIZ_REPORT_DESC] =
  {
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x04,                    // USAGE (Joystick)
    0xa1, 0x01,                    // COLLECTION (Application)

		0x85, REPORT_ID_JOY,				 	 //		REPORT_ID	(JOY_REPORT_ID)

		// buttons data
		0x05, 0x09,                    //   USAGE_PAGE (Button)
    0x19, 0x01,                    //   USAGE_MINIMUM (Button 1)
    0x29, MAX_BUTTONS_NUM,         //   USAGE_MAXIMUM (Button MAX_BUTTONS_NUM)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x95, MAX_BUTTONS_NUM,         //   REPORT_COUNT (MAX_BUTTONS_NUM)
    0x81, 0x00,                    //   INPUT (Data,Ary,Abs)

		// axis data
		0x05, 0x01,                    // 	USAGE_PAGE (Generic Desktop)
		0x09, 0x30,                    //   USAGE (X)
    0x09, 0x31,                    //   USAGE (Y)
    0x09, 0x32,                    //   USAGE (Z)
    0x09, 0x33,                    //   USAGE (Rx)
    0x09, 0x34,                    //   USAGE (Ry)
    0x09, 0x35,                    //   USAGE (Rz)
		0x09, 0x36,                    //   USAGE (Slider)
		0x09, 0x36,                    //  	USAGE (Slider)
    0x16, 0x01, 0x80,              //  	LOGICAL_MINIMUM (-32767)
    0x26, 0xFF, 0x7F,						   //   LOGICAL_MAXIMUM (32767)
    0x75, 0x10,                    //   REPORT_SIZE (16)
    0x95, MAX_AXIS_NUM,       		 //   REPORT_COUNT (MAX_AXIS_NUM)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)

		// POV data
		0x09, 0x39, 									 //   USAGE (Hat switch)
		0x15, 0x00, 									 //   LOGICAL_MINIMUM (0)
		0x25, 0x07, 									 //   LOGICAL_MAXIMUM (7)
		0x35, 0x00, 									 //   PHYSICAL_MINIMUM (0)
		0x46, 0x3B, 0x01,							 //   PHYSICAL_MAXIMUM (315)
		0x65, 0x12, 									 //   UNIT (SI Rot:Angular Pos)
		0x75, 0x08, 									 //   REPORT_SIZE (8)
		0x95, 0x01, 								   //   REPORT_COUNT (1)
		0x81, 0x02, 									 //   INPUT (Data,Var,Abs)
		0x09, 0x39, 									 //   USAGE (Hat switch)
		0x81, 0x02, 									 //   INPUT (Data,Var,Abs)
		0x09, 0x39, 									 //   USAGE (Hat switch)
		0x81, 0x02, 									 //   INPUT (Data,Var,Abs)
		0x09, 0x39, 									 //   USAGE (Hat switch)
		0x81, 0x02, 									 //   INPUT (Data,Var,Abs)

		0xc0,                           // END_COLLECTION
  }; /* CustomHID_ReportDescriptor */




Usage Page (Generic Desktop),
Usage (Joystick),
Collection (Application),
Usage Page (Generic Desktop),
Usage (Pointer),
Collection (Physical),
Logical Minimum (-127),
Logical Maximum (127),
Report Size (8),
Report Count (2),
Push,
Usage (X),
Usage (Y),
Input (Data, Variable, Absolute),
Usage (Hat switch),
Logical Minimum (0),
Logical Maximum (3),
Physical Minimum 0),
Physical Maximum (270),
Unit (Degrees),
Report Count (1),
Report Size (4),
Input (Data, Variable, Absolute, Null State),
Logical Minimum (0),
Logical Maximum (1),
Report Count (2),
Report Size (1),
Usage Page (Buttons),
Usage Minimum (Button 1),
Usage Maximum (Button 2),
Unit (None),
Input (Data, Variable, Absolute)
End Collection,

Usage Minimum (Button 3),
Usage Minimum (Button 4),
Input (Data, Variable, Absolute),
Pop,
Usage (Throttle),
Report Count (1),
Input (Data, Variable, Absolute),
End Collection
