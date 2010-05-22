/*=======================================================
 Copyright (c) avp::ptr, 2010
 =======================================================*/

#include "Timeline.h"
#include <algorithm>


Timeline::Timeline()
:
m_counter(0)
{
    //ctor
}

Timeline::~Timeline()
{
    //dtor
}

void Timeline::setTimeline(vector<GpsData*> gpsDatas)
{
    m_counter = 0;
    m_timeline.clear();
    for(unsigned int i = 0; i < gpsDatas.size(); ++i)
    {
        for(unsigned int j = 0; j < gpsDatas[i]->getSegments().size(); ++j)
        {
            for(unsigned int k = 0; k < gpsDatas[i]->getSegments()[j].getPoints().size(); ++k)
            {
                string timeString = gpsDatas[i]->getSegments()[j].getPoints()[k].getTimestamp();
                TimelineObject tmObj;
                tmObj.timeString = timeString;
                tmObj.secs = makeTimeObject(timeString);
                tmObj.id = i;
                m_timeline.push_back(tmObj);
//                ofLog(OF_LOG_VERBOSE, "%s : %d : %li\n", tmObj.timeString.c_str(), tmObj.id, tmObj.secs);
            }
        }
    }
    sort();
}

int Timeline::getNext()
{
    if (m_timeline.size() > 0)
    {
        int id = m_timeline[m_counter].id;
        ++m_counter;
        m_counter %= m_timeline.size();
        return id;
    }
    else
    {
        return 0;
    }
}

time_t Timeline::makeTimeObject(std::string timeString)
{
    struct tm tm;
    time_t t;
    time(&t);
    int year, month, day, hour, min, sec;
    string str = timeString;
    str.replace(10, 1, " ");
    str.replace(19, 1, " ");
    sscanf(str.c_str(), "%d-%d-%d %d:%d:%d ", &year, &month, &day, &hour, &min, &sec);
    tm = *localtime(&t);
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = hour;
    tm.tm_min = min;
    tm.tm_sec = sec;
    tm.tm_isdst = -1;
    t = mktime(&tm);
    return t;
}

void Timeline::sort()
{
    TimelineObject compareObj;
	std::sort(m_timeline.begin(), m_timeline.end(), compareObj);
}
