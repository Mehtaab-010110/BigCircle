#ifndef WIND_H
#define WIND_H

// Calculate headwind and crosswind components from wind vector
void calculateWindComponents(double windSpeed, double windDirection, 
                             double courseDirection,
                             double *headwind, double *crosswind);

// Calculate ground speed (speed over ground, affected by wind)
double calculateGroundSpeed(double trueAirspeed, double headwind);

// Calculate wind correction angle (how much to adjust heading)
double calculateWindCorrectionAngle(double trueAirspeed, double crosswind);

#endif
