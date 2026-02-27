#ifndef DRAG_H
#define DRAG_H

// Calculate fuel penalty due to speed deviation from optimal
// Source: Simple quadratic drag approximation
double calculateDragPenalty(double speed, double optimalSpeed);

#endif
