#pragma once

#include <cmath>
#include <iostream>

/**
 * @class CPoint
 * @brief Represents a point or vector in 3D space.
 */
class CPoint {
public:
    /**
     * @brief Default constructor.
     */
    CPoint();

    /**
     * @brief Constructor with position.
     * @param posX X coordinate.
     * @param posY Y coordinate.
     * @param posZ Z coordinate.
     */
    CPoint(double posX, double posY, double posZ);

    /**
     * @brief Destructor.
     */
    ~CPoint() = default;

    CPoint operator+(const CPoint& arg) const;
    CPoint operator-(const CPoint& arg) const;
    CPoint operator*(const double scalar) const;
    CPoint operator/(const double scalar) const;

    /**
     * @brief Output stream operator for debugging.
     */
    friend std::ostream& operator<<(std::ostream& os, const CPoint& point);

    /**
     * @brief Calculates Euclidean distance to another point.
     * @param arg Another point.
     * @return Distance value.
     */
    double distance(const CPoint& arg) const;

    double posX;
    double posY;
    double posZ;
};
