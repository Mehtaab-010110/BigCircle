#include <stdio.h>
#include <string.h>
#include "../include/performance.h"

// Source: ICAO Doc 8168 - Aircraft Operating Procedures
// Typical Boeing 737-800 performance values

void calculateFlightPhases(double totalDistance, FlightPhase phases[3]) {
    
    // Phase 1: CLIMB (0 to 35,000 ft)
    strcpy(phases[0].name, "Climb");
    phases[0].distance_nm = totalDistance * 0.15;  // 15% of total distance
    phases[0].altitude_ft = 17500.0;  // Average altitude
    phases[0].airspeed_kts = 280.0;   // Slower during climb
    phases[0].fuel_rate_lbs = 3500.0; // High fuel burn climbing
    
    // Phase 2: CRUISE (at 35,000 ft)
    strcpy(phases[1].name, "Cruise");
    phases[1].distance_nm = totalDistance * 0.70;  // 70% of distance
    phases[1].altitude_ft = 35000.0;
    phases[1].airspeed_kts = 450.0;   // Most efficient speed
    phases[1].fuel_rate_lbs = 2200.0; // Lower, efficient burn
    
    // Phase 3: DESCENT (35,000 ft to 0)
    strcpy(phases[2].name, "Descent");
    phases[2].distance_nm = totalDistance * 0.15;  // 15% of distance
    phases[2].altitude_ft = 17500.0;  // Average altitude
    phases[2].airspeed_kts = 300.0;   // Moderate descent speed
    phases[2].fuel_rate_lbs = 1800.0; // Low burn descending
}

void computePhasePerformance(FlightPhase *phase, double headwind) {
    // Calculate ground speed for this phase
    double groundSpeed = phase->airspeed_kts - headwind;
    
    // Time = Distance / Speed
    phase->time_hours = phase->distance_nm / groundSpeed;
    
    // Fuel = Time * Burn Rate
    phase->fuel_used_lbs = phase->time_hours * phase->fuel_rate_lbs;
}

void printPhase(FlightPhase *phase) {
    printf("  %-10s: %.1f NM, %.0f kts, %.2f hrs, %.0f lbs fuel\n",
           phase->name,
           phase->distance_nm,
           phase->airspeed_kts,
           phase->time_hours,
           phase->fuel_used_lbs);
}
