#ifndef __CSAMPLE0APPLICATION_H__
#define __CSAMPLE0APPLICATION_H__

#include "system/crtcapplication.h"

class CSample0FrameListener;

class CSample0Application : public CRtcApplication
{
public:
    CSample0Application();

    virtual ~CSample0Application();

protected:

    virtual void createScene();

private:

    void createFrameListener();

    CSample0FrameListener * mpFrameListener;
};

#endif // __CSAMPLE0APPLICATION_H__