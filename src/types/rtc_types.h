#ifndef __RTC_TYPES_H__
#define __RTC_TYPES_H__

namespace rtc {

#define RTC_DISABLE_COPY_AND_ASSIGNMENT( class_name ) \
class_name           (const class_name &);            \
class_name &operator=(const class_name &);            \

typedef unsigned int TViewportHandle;
typedef unsigned int TCameraId;

TViewportHandle const kInvalidViewportHandle = 0;
TCameraId       const kInvalidCameraId       = 0;

#define RTC_SET_BIT( bit_position ) ( 1 << bit_position )

struct SViewportInfo
{
    explicit SViewportInfo( float const _left, float const _top, float const _width, float const _height )
        :left(_left)
        ,top(_top)
        ,width(_width)
        ,height(_height)
    {
    }

    float left;
    float top;
    float width;
    float height;
};

} // namespace

#endif // __RTC_TYPES_H__