#ifndef __SCONTROLLERDATA_H__
#define __SCONTROLLERDATA_H__

#include "types/rtc_types.h"

namespace rtc {

inline unsigned int BUTTONS_DOWN( unsigned int lastButtons, unsigned int buttons )
{
    return (lastButtons^buttons) & buttons;
}

inline unsigned int BUTTONS_UP( unsigned int lastButtons, unsigned int buttons )
{
    return (lastButtons^buttons) & lastButtons;
}

enum EButton
{
     kButton_Up    = RTC_SET_BIT( 0 )
    ,kButton_Down  = RTC_SET_BIT( 1 )
    ,kButton_Left  = RTC_SET_BIT( 2 )
    ,kButton_Right = RTC_SET_BIT( 3 )
    ,kButton_Start = RTC_SET_BIT( 4 )
    ,kButton_Back  = RTC_SET_BIT( 5 )

    ,kButton_ApplicationQuit = RTC_SET_BIT( 31 ) 
};

struct SPointerAxis
{
    SPointerAxis()
        :absolute(0)
        ,relative(0)
    {
    }

    int absolute;
    int relative;
};

struct SControllerData
{
    SControllerData()
        :pointerX()
        ,pointerY()
        ,buttons(0)
        ,buttonsUp(0)
        ,buttonsDown(0)
    {
    }

    SPointerAxis pointerX;
    SPointerAxis pointerY;

    unsigned int buttons;
    unsigned int buttonsUp;
    unsigned int buttonsDown;
};

} // namespace

#endif // __SCONTROLLERDATA_H__