#!/usr/bin/env python
# this stuff is in the
# gps.py -- Python interface to GPSD.
# script here /usr/share/python-support/python-gps
#
#
# EarthDistance code swiped from Kismet and corrected
# (As yet, this stuff is not in the libgps C library.)

import time
import calendar
import math


def Deg2Rad(x):
    """Degrees to radians."""
    return x * (math.pi / 180)


def CalcRad(lat):
    """Radius of curvature in meters at specified latitude."""
    a = 6378.137
    e2 = 0.081082 * 0.081082
    # the radius of curvature of an ellipsoidal Earth in the plane of a
    # meridian of latitude is given by
    #
    # R' = a * (1 - e^2) / (1 - e^2 * (sin(lat))^2)^(3/2)
    #
    # where a is the equatorial radius,
    # b is the polar radius, and
    # e is the eccentricity of the ellipsoid = sqrt(1 - b^2/a^2)
    #
    # a = 6378 km (3963 mi) Equatorial radius (surface to center distance)
    # b = 6356.752 km (3950 mi) Polar radius (surface to center distance)
    # e = 0.081082 Eccentricity
    sc = math.sin(Deg2Rad(lat))
    x = a * (1.0 - e2)
    z = 1.0 - e2 * sc * sc
    y = pow(z, 1.5)
    r = x / y

    r = r * 1000.0  # Convert to meters
    return r


def EarthDistance(lat1, lon1, lat2, lon2):
    """Distance in meters between two points specified in degrees."""
    x1 = CalcRad(lat1) * math.cos(Deg2Rad(lon1)) * math.sin(Deg2Rad(90 - lat1))
    x2 = CalcRad(lat2) * math.cos(Deg2Rad(lon2)) * math.sin(Deg2Rad(90 - lat2))
    y1 = CalcRad(lat1) * math.sin(Deg2Rad(lon1)) * math.sin(Deg2Rad(90 - lat1))
    y2 = CalcRad(lat2) * math.sin(Deg2Rad(lon2)) * math.sin(Deg2Rad(90 - lat2))
    z1 = CalcRad(lat1) * math.cos(Deg2Rad(90 - lat1))
    z2 = CalcRad(lat2) * math.cos(Deg2Rad(90 - lat2))
    a = (x1 * x2 + y1 * y2 + z1 * z2) / pow(CalcRad((lat1 + lat2) / 2), 2)
    # a should be in [1, -1] but can sometimes fall outside it by
    # a very small amount due to rounding errors in the preceding
    # calculations (this is prone to happen when the argument points
    # are very close together).  Thus we constrain it here.
    if abs(a) > 1: a = 1
    elif a < -1: a = -1
    return CalcRad((lat1 + lat2) / 2) * math.acos(a)


def MeterOffset(lat1, lon1, lat2, lon2):
    """Return offset in meters of second arg from first."""
    dx = EarthDistance((lat1, lon1), (lat1, lon2))
    dy = EarthDistance((lat1, lon1), (lat2, lon1))
    if lat1 < lat2: dy *= -1
    if lon1 < lon2: dx *= -1
    return (dx, dy)


def isotime(s):
    """Convert timestamps in ISO8661 format to and from Unix time."""
    if type(s) == type(1):
        return time.strftime("%Y-%m-%dT%H:%M:%S", time.gmtime(s))
    elif type(s) == type(1.0):
        date = int(s)
        msec = s - date
        date = time.strftime("%Y-%m-%dT%H:%M:%S", time.gmtime(s))
        return date + "." + repr(msec)[2:]
    elif type(s) == type(""):
        if s[-1] == "Z":
            s = s[:-1]
        if "." in s:
            (date, msec) = s.split(".")
        else:
            date = s
            msec = "0"
        # Note: no leap-second correction!
        tf = "%Y-%m-%dT%H:%M:%S"
        return calendar.timegm(time.strptime(date, tf)) + float("0." + msec)
    else:
        raise TypeError
