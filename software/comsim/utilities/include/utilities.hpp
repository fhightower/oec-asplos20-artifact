// utilities.hpp
// utilities header file
//
// Copyright 2019 Bradley Denby
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not
// use this file except in compliance with the License. You may obtain a copy of
// the License at <http://www.apache.org/licenses/LICENSE-2.0>.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations under
// the License.

// Standard library
#include <array>           // array
#include <cstdint>         // int16_t, uint8_t, uint32_t
#include <tuple>           // tuple

// comsim
#include <ChannelType.hpp> // ChannelType

namespace comsim { namespace util {
  // Return true if the provided year is a leap year; return false otherwise
  // Parameters:
  //  year: The Gregorian calendar year of interest
  // Returns:
  //  True if the provided year is a leap year; otherwise false
  // Reference: common knowledge
  double isLeapYear(const int16_t& year);

  // Return the TLE epoch year, month, day, hour, minute, second, nanosecond
  // Parameters:
  //  tleFile: A string indicating the path to the TLE file
  // Returns:
  //  TLE epoch year, month, day, hour, minute, second, nanosecond as a tuple
  // Reference: Three line element set format, e.g. in Space Track Report No. 3
  std::tuple<int16_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint32_t>
   getTleEpoch(const std::string& tleFile);

  // Calculate the Julian day at 0h (midnight) of the given (year, month, day).
  // The Julian day at 12h (noon) is an integer, so Julian days at 0h are
  // therefore given by the Julian day at 12h (noon) - 0.5
  // Parameters:
  //  year: The Gregorian (standard) calendar year of interest
  //  month: The Gregorian calendar month of interest
  //  day: The Gregorian calendar day of interest
  // Returns:
  //  The Julian day at 0h (midnight) of the Gregorian date of interest. This
  //  function is valid only for Gregorian dates that correspond to positive
  //  Julian days.
  // Reference: comsim/documentation/fliegel1968letters.pdf
  double calcJulianDayFromYMD(
   const int16_t& year, const uint8_t& month, const uint8_t& day
  );

  // Calculate the number of seconds since midnight given (hour, minute, second)
  // Parameters:
  //  hour: UT1 hours since midnight
  //  minute: UT1 minutes since midnight
  //  second: UT1 seconds since midnight
  // Returns:
  //  The number of seconds since midnight
  // Reference: Standard calculation
  uint32_t calcSecSinceMidnight(
   const uint8_t& hour, const uint8_t& minute, const uint8_t& second
  );

  // Calculate time interval in minutes between the event of interest and epoch
  // Parameters:
  //  yearEvent: Year of event of interest
  //  monthEvent: Month of event of interest
  //  dayEvent: Day of event of interest
  //  hourEvent: Hour of event of interest
  //  minuteEvent: Minute of event of interest
  //  secondEvent: Second of event of interest
  //  nanosecondEvent: Nanosecond of event of interest
  //  yearEpoch: Year of epoch of interest
  //  monthEpoch: Month of epoch of interest
  //  dayEpoch: Day of epoch of interest
  //  hourEpoch: Hour of epoch of interest
  //  minuteEpoch: Minute of epoch of interest
  //  secondEpoch: Second of epoch of interest
  //  nanosecondEpoch: Nanosecond of epoch of interest
  // Returns:
  //  Event of interest - epoch in minutes (negative values OK)
  // Reference: Uses calcJulianDayFromYMD
  double calcTdiffMin(
   const int16_t& yearEvent, const uint8_t& monthEvent, const uint8_t& dayEvent,
   const uint8_t& hourEvent, const uint8_t& minuteEvent,
   const uint8_t& secondEvent, const uint32_t& nanosecondEvent,
   const int16_t& yearEpoch, const uint8_t& monthEpoch, const uint8_t& dayEpoch,
   const uint8_t& hourEpoch, const uint8_t& minuteEpoch,
   const uint8_t& secondEpoch, const uint32_t& nanosecondEpoch
  );

  // Calculate ECI position given necessary TLE parameters and time since epoch
  // Parameters:
  //  bstar: Pseudo drag term (inverse Earth radii)
  //  i0: Inclination (radians) at TLE epoch
  //  o0: Right ascension of node (RAAN) (radians) at TLE epoch
  //  e0: Eccentricity (unitless) at TLE epoch
  //  w0: Argument of perigee (radians) at TLE epoch
  //  m0: Mean anomaly (radians) at TLE epoch
  //  n0: Mean motion (radians per minute) at TLE epoch
  //  tsince: Minutes since TLE epoch (can be negative or positive)
  // Returns:
  //  The ECI x, y, and z coordinates of the satellite at the given solar time
  // Reference: comsim/documentation/hoots1980models.pdf
  std::array<float,3> sgp4(
   const float& bstar, const float& i0, const float& o0, const float& e0,
   const float& w0, const float& m0, const float& n0, const float& tsince
  );

  // Calculate GMST in radians given UT1 time in Julian days + seconds + ns
  // Parameters:
  //  julianDay: Julian days up to midnight of the Gregorian date of interest
  //  second: seconds since midnight of the Gregorian date of interest
  //  nanosecond: nanoseconds since Julian day + second
  // Returns:
  //  The Greenwich mean sidereal time (GMST) angle in radians, i.e. the angle
  //  of rotation between vernal equinox and zero longitude at the given time
  // Reference: comsim/documentation/aoki1982new.pdf
  //  Precisely stated, this function converts a UT1 time to GMST radians.
  //  UTC is always within 0.9 seconds of UT1 (via leap second adjustments).
  //  If accuracy better than one second is required, then formally convert the
  //  UTC time to UT1 using DUT1: UT1 = UTC+DUT1 (DUT1 available in tables).
  double calcGMSTRadFromUT1(
   const double& julianDay, const uint32_t& second, const uint32_t& nanosecond
  );

  // Calculate ERA in radians given UT1 time in Julian days + seconds + ns
  // Parameters:
  //  julianDay: Julian days up to midnight of the Gregorian date of interest
  //  second: seconds since midnight of the Gregorian date of interest
  //  nanosecond: nanoseconds since Julian day + second
  // Returns:
  //  The Earth rotation angle (ERA) in radians, i.e. the angle of rotation
  //  between the terrestrial intermediate origin and the celestial intermediate
  //  origin at the given time
  // Reference: comsim/documentation/capitaine2000definition.pdf
  //  Precisely stated, this function converts a UT1 time to ERA radians.
  //  UTC is always within 0.9 seconds of UT1 (via leap second adjustments).
  //  If accuracy better than one second is required, then formally convert the
  //  UTC time to UT1 using DUT1: UT1 = UTC+DUT1 (DUT1 available in tables).
  double calcERARadFromUT1(
   const double& julianDay, const uint32_t& second, const uint32_t& nanosecond
  );

  // Calculate ECI coordinates given date, time, latitude, longitude, and
  // altitude (height above the ellipsoid)
  // Parameters:
  //  julianDay: Julian days up to midnight of the UT1 Gregorian day of interest
  //  second: UT1 seconds since midnight of the Gregorian date of interest
  //  nanosecond: UT1 nanoseconds since Julian day + second
  //  lat: latitude in radians
  //  lon: longitude in radians
  //  alt: height above the ellipsoid in kilometers
  // Returns:
  //  The equivalent (x,y,z) ECI coordinates in kilometers
  // Reference: Fundamentals of astrodynamics and applications, 4th ed., pg. 138
  std::array<double,3> dtlla2eci(
   const double& julianDay, const uint32_t& second, const uint32_t& nanosecond,
   const double& lat, const double& lon, const double& alt
  );

  // Calculate SEZ coordinates given date, time, and ECI coordinates
  // Parameters:
  //  julianDay: Julian days up to midnight of the UT1 Gregorian day of interest
  //  second: UT1 seconds since midnight of the Gregorian date of interest
  //  nanosecond: UT1 nanoseconds since Julian day + second
  //  lat: latitude in radians
  //  lon: longitude in radians
  //  eciVector: a vector in the ECI coordinate frame
  // Returns:
  //  The equivalent (x,y,z) SEZ coordinates in kilometers
  // Reference: Fundamentals of astrodynamics and applications, 4th ed., pg. 168
  std::array<double,3> dteci2sez(
   const double& julianDay, const uint32_t& second, const uint32_t& nanosecond,
   const double& lat, const double& lon, const std::array<double,3>& eciVector
  );

  // Calculate look angle azimuth in degrees clockwise from North to satellite
  // from a ground station
  // Parameters:
  //  julianDay: Julian days up to midnight of the UT1 Gregorian day of interest
  //  second: UT1 seconds since midnight of the Gregorian date of interest
  //  nanosecond: UT1 nanoseconds since Julian day + second
  //  lat: latitude of ground station in radians
  //  lon: longitude of ground station in radians
  //  alt: height above the ellipsoid of ground station in kilometers
  //  eciPosnSat: satellite ECI position in kilometers
  // Returns:
  //  Look angle azimuth in degrees clockwise from North to satellite in degrees
  // Reference: The Astronomical Almanac
  double calcAzimuthDeg(
   const double& julianDay, const uint32_t& second, const uint32_t& nanosecond,
   const double& lat, const double& lon, const double& alt,
   const std::array<double,3>& eciPosnSat
  );

  // Calculate look angle elevation in degrees from ground station to satellite
  // Parameters:
  //  julianDay: Julian days up to midnight of the UT1 Gregorian day of interest
  //  second: UT1 seconds since midnight of the Gregorian date of interest
  //  nanosecond: UT1 nanoseconds since Julian day + second
  //  lat: latitude of ground station in radians
  //  lon: longitude of ground station in radians
  //  alt: height above the ellipsoid of ground station in kilometers
  //  eciPosnSat: satellite ECI position in kilometers
  // Returns:
  //  Look angle elevation from the ground station to the satellite in radians
  // Reference: The Astronomical Almanac
  double calcElevationDeg(
   const double& julianDay, const uint32_t& second, const uint32_t& nanosecond,
   const double& lat, const double& lon, const double& alt,
   const std::array<double,3>& eciPosnSat
  );

  // Calculate the height above the ellipsoid given the ECI position
  // Parameters:
  //  eciPosnSat: satellite ECI position in kilometers
  // Returns:
  //  Height above ellipsoid in kilometers
  // Reference: comsim/documentation/borkowski1989accurate.pdf
  double calcAltitudeKm(const std::array<double,3>& eciPosnSat);

  // Calculate the satellite subpoint latitude in degrees given the ECI position
  // Parameters:
  //  eciPosnSat: satellite ECI position in kilometers
  // Returns:
  //  Subpoint latitude in degrees
  // Reference: comsim/documentation/borkowski1989accurate.pdf
  double calcSubpointLatitude(const std::array<double,3>& eciPosnSat);

  // Calculate the satellite subpoint longitude (degrees) given the ECI position
  // Parameters:
  //  julianDay: Julian days up to midnight of the UT1 Gregorian day of interest
  //  second: UT1 seconds since midnight of the Gregorian date of interest
  //  nanosecond: UT1 nanoseconds since Julian day + second
  //  eciPosnSat: satellite ECI position in kilometers
  // Returns:
  //  Subpoint longitude in degrees
  // Reference: comsim/documentation/borkowski1989accurate.pdf
  double calcSubpointLongitude(
   const double& julianDay, const uint32_t& second, const uint32_t& nanosecond,
   const std::array<double,3>& eciPosnSat
  );

  // Calculate the great circle arc in radians between two (Az,El) coordinates
  // Parameters:
  //  az1: azimuth 1 in degrees
  //  el1: elevation 1 in degrees
  //  az2: azimuth 2 in degrees
  //  el2: elevation 2 in degrees
  // Returns:
  //  Great circle arc in radians between two (Az,El) coordinates
  //  NOTE: The implementation is of a special case assuming an ellipsoid with
  //        equal major and minor axes.
  // Reference: comsim/documentation/vincenty1975direct
  double calcGreatCircleArc(
   const double& az1Deg, const double& el1Deg,
   const double& az2Deg, const double& el2Deg
  );

  // Calculate the magnitude of a Cartesian 3D vector
  // Parameters:
  //  cartesian: a Cartesian 3D vector
  // Returns:
  //  The magnitude of the input
  // Reference: Standard calculation
  double magnitude(const std::array<double,3>& cartesian);

  // Convert a decibel value to decimal
  // Parameters:
  //  db: a decibel value
  // Returns:
  //  The equivalent decimal value
  // Reference: Standard calculation
  double dB2Dec(const double& db);

  // Calculate the maximum possible bits per second
  // Parameters:
  //  txPowerW: Transmit power in Watts
  //  txLineLossFactor: Transmit line loss factor (not dB)
  //  txGainFactor: Transmit gain factor (not dB)
  //  atmoLossFactor: Atmospheric loss factor (not dB)
  //  rxGainFactor: Receive gain factor (not dB)
  //  centerFreqHz: Channel center frequency (Hz)
  //  rangeKm: Magnitude of vector between transmit and receive in km
  //  systemNoiseTempK: System noise temperature in Kelvin
  //  bandwidthHz: Channel bandwidth in Hz
  // Returns:
  //  The maximum possible channel bits per second under Shannon-Hartley theorem
  // Reference: comsim/documentation/wertz1999space.pdf
  uint64_t calcMaxBitsPerSec(
   const double& txPowerW, const double& txLineLossFactor,
   const double& txGainFactor, const double& atmoLossFactor,
   const double& rxGainFactor, const double& centerFreqHz,
   const double& rangeKm, const double& systemNoiseTempK,
   const double& bandwidthHz
  );

  // Calculate the separation vector from start to end
  // Parameters:
  //  end: The end vector
  //  start: The start vector
  // Returns:
  //  End vector minus start vector
  // Reference: Standard calculation
  std::array<double,3> calcSeparationVector(
   const std::array<double,3>& end, const std::array<double,3>& start
  );

  double calcAtmosphericLoss();

  double calcSystemNoiseTemp(
   const ChannelType& channelType, const double& centerFrequencyHz
  );
}}
