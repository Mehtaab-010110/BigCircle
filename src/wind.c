#include <math.h>
#include "../include/wind.h"

#define PI 3.14159265358979323846

// Source: FAA Pilot's Handbook of Aeronautical Knowledge, Chapter 16
// Source: Claude AI for wind component calculations
// https://www.faa.gov/regulations_policies/handbooks_manuals/aviation/phak
void calculateWindComponents(double windSpeed, double windDirection, 
                             double courseDirection,
                             double *headwind, double *crosswind) {
    
    // Convert directions to radians for trig functions
    double windRad = windDirection * PI / 180.0;
    double courseRad = courseDirection * PI / 180.0;
    
    // Calculate the angle between wind direction and course
    double angleDiff = windRad - courseRad;

    // Headwind component (positiv e = headwind, negative = tailwind)
    *headwind = windSpeed * cos(angleDiff);
    
    // Crosswind component (positive = from right, negative = from left)
    *crosswind = windSpeed * sin(angleDiff);
}

double calculateGroundSpeed(double trueAirspeed, double headwind) {
    // Ground speed = airspeed + wind effect
    // Positive headwind slows you down, negative (tailwind) speeds you up
    return trueAirspeed - headwind;
}

double calculateWindCorrectionAngle(double trueAirspeed, double crosswind) {
    // Calculate the angle to "crab" into the wind
    double angleRad = asin(crosswind / trueAirspeed);
    
    // Convert back to degrees
    return angleRad * 180.0 / PI;
}
