#include <stdio.h>
#include <math.h>
#include "../include/wind.h"
#include "../include/performance.h"
#include "../include/drag.h"

#define EARTH_RADIUS 3440.065
#define PI 3.14159265358979323846

double toRadians(double degrees) {
    return degrees * PI / 180.0;
}

double calculateBearing(double lat1, double lon1, double lat2, double lon2) {
    lat1 = toRadians(lat1);
    lon1 = toRadians(lon1);
    lat2 = toRadians(lat2);
    lon2 = toRadians(lon2);
    
    double dlon = lon2 - lon1;
    double y = sin(dlon) * cos(lat2);
    double x = cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos(dlon);
    
    double bearing = atan2(y, x);
    bearing = bearing * 180.0 / PI;
    bearing = fmod(bearing + 360.0, 360.0);
    
    return bearing;
}

double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    lat1 = toRadians(lat1);
    lon1 = toRadians(lon1);
    lat2 = toRadians(lat2);
    lon2 = toRadians(lon2);
    
    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;
    
    double a = sin(dlat/2) * sin(dlat/2) + 
               cos(lat1) * cos(lat2) * sin(dlon/2) * sin(dlon/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    
    return EARTH_RADIUS * c;
}

int main() {
    double lat1 = 51.1215;
    double lon1 = -114.0130;
    double lat2 = 49.1967;
    double lon2 = -123.1815;
    
    printf("=== Advanced Flight Calculator ===\n");
    printf("=== Calgary (YYC) to Vancouver (YVR) ===\n\n");
    
    double distance = calculateDistance(lat1, lon1, lat2, lon2);
    double courseDirection = calculateBearing(lat1, lon1, lat2, lon2);
    
    printf("Total Distance: %.2f NM\n", distance);
    printf("Course: %.1f°\n\n", courseDirection);
    
    // Create flight phases
    FlightPhase phases[3];
    calculateFlightPhases(distance, phases);
    
    // Variable wind conditions (changes each phase)
    double windSpeeds[3] = {25.0, 35.0, 20.0};
    double windDirs[3] = {270.0, 290.0, 310.0};
    
    printf("=== Flight Profile ===\n");
    
    double totalTime = 0.0;
    double totalFuel = 0.0;
    
    for (int i = 0; i < 3; i++) {
        // Calculate wind for this phase
        double headwind, crosswind;
        calculateWindComponents(windSpeeds[i], windDirs[i], courseDirection,
                               &headwind, &crosswind);
        
        // Apply drag penalty to fuel rate
        double dragPenalty = calculateDragPenalty(phases[i].airspeed_kts, 450.0);
        phases[i].fuel_rate_lbs *= dragPenalty;
        
        // Calculate performance
        computePhasePerformance(&phases[i], headwind);
        
        printf("\n%s Phase:\n", phases[i].name);
        printf("  Wind: %.0f kts from %.0f° (headwind: %.1f kts)\n", 
               windSpeeds[i], windDirs[i], headwind);
        printf("  Distance: %.1f NM @ %.0f kts\n", 
               phases[i].distance_nm, phases[i].airspeed_kts);
        printf("  Time: %.2f hours\n", phases[i].time_hours);
        printf("  Fuel: %.0f lbs\n", phases[i].fuel_used_lbs);
        
        totalTime += phases[i].time_hours;
        totalFuel += phases[i].fuel_used_lbs;
    }
    
    printf("\n=== TOTAL ===\n");
    printf("Flight Time: %.2f hours (%.0f min)\n", totalTime, totalTime * 60);
    printf("Fuel Burn: %.0f pounds (%.0f gallons)\n", totalFuel, totalFuel / 6.7);
    printf("\n");
    
    return 0;
}
