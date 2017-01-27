#include "BaseCamera.h"

//------------------------------------------------------------------------------

namespace core
{

//------------------------------------------------------------------------------

BaseCamera::BaseCamera()
    : QObject()
    , _exposure(-1)
{}

void BaseCamera::setExposure(int exposure)
{

    qDebug("Camera: exposure time set to %d ms", exposure);
    _exposure = exposure;
}

//------------------------------------------------------------------------------

}
