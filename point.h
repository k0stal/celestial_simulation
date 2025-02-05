#pragma once

#include <cmath>
#include <iostream>

class CPoint {
    public:
        CPoint();
        CPoint( double posX, double posY, double posZ );
        ~CPoint() = default;

        CPoint operator+ ( const CPoint& arg ) const;
        CPoint operator- ( const CPoint& arg ) const;
        CPoint operator* ( const double scalar ) const; 
        CPoint operator/ ( const double scalar ) const;
        friend std::ostream& operator<< ( std::ostream& os, const CPoint& point );
        double distance ( const CPoint& arg ) const;

    //private:
        double posX;
        double posY;
        double posZ;
};

