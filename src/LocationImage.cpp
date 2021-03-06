#include "LocationImage.h"
#include "GeoUtils.h"

//------------------------------------------------------------------------------

LocationImage::LocationImage(ofImageWeak image, const MagicBoxWeak magicBox,
                             LocationImageData lid)
:
DrawingLifeDrawable(),
m_magicBox(magicBox),
m_lid(lid),
m_image(image)
{
    m_utm.x = 0.0;
    m_utm.y = 0.0;

    m_utm = GeoUtils::LonLat2Utm(lid.gps.lon, lid.gps.lat);
}

//------------------------------------------------------------------------------

LocationImage::~LocationImage()
{
}

//------------------------------------------------------------------------------

void LocationImage::draw()
{
    const ofImagePtr image = m_image.lock();
    const MagicBoxPtr magicBox = m_magicBox.lock();
    if (image && magicBox)
    {
//        ofSetColor(0xffffff);
        ofSetColor(255,255,255,m_lid.alpha);
        const ofxPoint<double>& tmp = magicBox->getDrawablePoint(m_utm);
        image->draw(getScaledUtmX(tmp.x), getScaledUtmY(tmp.y));

        if (m_lid.anchorShow)
        {
            ofSetHexColor(0xff0000);
            ofCircle(getScaledUtmX(tmp.x), getScaledUtmY(tmp.y), 5);
        }

    }

}

//------------------------------------------------------------------------------
