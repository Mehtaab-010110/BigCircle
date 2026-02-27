#ifndef PERFORMANCE_H
#define PERFORMANCE_H

// Flight phase structure
typedef struct {
    char name[20];          // "Climb", "Cruise", "Descent"
    double distance_nm;     // Distance covered in this phase
    double altitude_ft;     // Average altitude for this phase
    double airspeed_kts;    // True airspeed
    double fuel_rate_lbs;   // Fuel burn rate (lbs/hour)
    double time_hours;      // Time for this phase (calculated)
    double fuel_used_lbs;   // Fuel used (calculated)
} FlightPhase;

// Calculate the three flight phases
void calculateFlightPhases(double totalDistance, FlightPhase phases[3]);

// Compute performance for a single phase (with wind)
void computePhasePerformance(FlightPhase *phase, double headwind);

// Display phase information
void printPhase(FlightPhase *phase);

#endif
