#include <stdio.h>
#include <math.h>

#define EARTH_RADIUS_NM 3440.065
#define PI 3.14159265358979323846

double toRadians(double degrees) {
    return degrees * PI / 180.0;
}

// Haversine formula from aviation reference
// Source: https://en.wikipedia.org/wiki/Haversine_formula
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
    
    return EARTH_RADIUS_NM * c;
}

int main() {
    // Test coordinates: Calgary to Vancouver
    double lat1 = 51.1215;
    double lon1 = -114.0130;
    double lat2 = 49.1967;
    double lon2 = -123.1815;
    
    printf("=== Flight Distance Calculator ===\n\n");
    printf("Route: Calgary (YYC) to Vancouver (YVR)\n\n");
    
    double distance = calculateDistance(lat1, lon1, lat2, lon2);
    
    // Using typical commercial aircraft values
    // TODO: Could make these user inputs later
    double cruiseSpeed = 450.0;  // knots (typical for 737)
    double fuelBurnRate = 2500.0;  // pounds per hour (approximate)
    
    double flightTime = distance / cruiseSpeed;
    double fuelBurn = flightTime * fuelBurnRate;
    
    printf("=== Results ===\n");
    printf("Distance: %.2f nautical miles\n", distance);
    printf("Estimated flight time: %.2f hours\n", flightTime);
    printf("Estimated fuel burn: %.2f pounds\n", fuelBurn);
    
    return 0;
}