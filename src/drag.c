#include "../include/drag.h"

// Simple drag model: fuel increases when flying faster/slower than optimal
double calculateDragPenalty(double speed, double optimalSpeed) {
    // Calculate how far from optimal speed
    double speedRatio = speed / optimalSpeed;
    
    // Penalty increases with square of deviation
    // At optimal speed: penalty = 1.0 (no change)
    // 10% faster/slower: ~1% more fuel
    // Source - Claude AI
    double penalty = 1.0 + 0.1 * (speedRatio - 1.0) * (speedRatio - 1.0);
    
    return penalty;
}
