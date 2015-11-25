#include "AcqParams.hpp"

AcqParams::AcqParams(const float aduGain,  const float cameraGain,
                     const int cameraType, const UInt hotStartFrame,
                     const UInt laserOnFrame)
    : aduGain_(aduGain)
    , cameraGain_(cameraGain)
    , cameraType_(cameraType)
    , hotStartFrame_(hotStartFrame)
    , laserOnFrame_(laserOnFrame)
{ }
