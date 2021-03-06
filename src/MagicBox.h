/*==========================================================
 Copyright (c) avp::ptr, 2010
 ==========================================================*/

#ifndef _MAGICBOX_H_
#define _MAGICBOX_H_

#include "GpsData.h"

class MagicBox : public boost::enable_shared_from_this<MagicBox>
{
public:

    enum Direction
    {
        UP, DOWN, RIGHT, LEFT
    };

    enum Zoom
    {
        ZOOM_IN, ZOOM_OUT
    };

    MagicBox(const AppSettings& settings, double size, double padding);
    ~MagicBox();

    bool isInBox(const ofxPoint<double>& utmPoint) const;

    void setupBox(const ofxPoint<double>& currUtm);

    void setSize(double newSize);

    void updateBoxIfNeeded(const ofxPoint<double>& utmPoint);

    void addToBoxSize(double sizeToAdd);

    const ofxRectangle<double>& getTheBox() const { return m_theBox; }
    const ofxRectangle<double> getNormalizedBox() const;
    const ofxRectangle<double>& getPaddedBox() const { return m_theBox; }
    const ofxRectangle<double> getNormalizedPaddedBox() const;
    const ofxPoint<double>& getCenter() const {return m_centerUtm; }
    const GpsPoint getCenterGps() const;
    const double getSize() const { return m_currentSize; }

    const ofxPoint<double> getDrawablePoint(const UtmPoint& utmPoint) const;

    void toggleZoomLevel(size_t zoomLevel);

    void zoom(Zoom z);
    void move(Direction d);
    void move(Direction d, double val);

private:

    bool isInPaddedBox(const ofxPoint<double>& utmPoint) const;

    void addX(double val);
    void addY(double val);

    void setBoxes();
    double getSizeWithPadding() const;

    ofxPoint<double> m_centerUtm;

    ofxRectangle<double> m_theBox;
    ofxRectangle<double> m_paddedBox;

    const AppSettings& m_settings;
    double m_currentSize;

    double m_padding;

    static double m_zoomLevels[4];

    double m_defaultSize;

    static int m_boxNum;

    int m_boxId;
};

#endif // _MAGICBOX_H_
