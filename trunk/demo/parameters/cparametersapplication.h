#ifndef __CPARAMETERSAPPLICATION_H__
#define __CPARAMETERSAPPLICATION_H__

#include "system/crtcapplication.h"

class CParametersFrameListener;

class CParametersApplication : public CRtcApplication
{
public:
    CParametersApplication();

    virtual ~CParametersApplication();

protected:

    virtual void createScene();

private:

    void createFrameListener();

    CParametersFrameListener * mpFrameListener;
};

#endif // __CPARAMETERSAPPLICATION_H__