#include "point.h"

CPoint::CPoint( void ):
    posX(0),
    posY(0),
    posZ(0) {}

CPoint::CPoint( double posX, double posY, double posZ ):
    posX(posX),
    posY(posY),
    posZ(posZ) {}
    
CPoint CPoint::operator+ (const CPoint& arg) const {
    return CPoint(this->posX + arg.posX, 
                  this->posY + arg.posY, 
                  this->posZ + arg.posZ);
}
        
CPoint CPoint::operator- ( const CPoint& arg ) const {
    return CPoint (this->posX - arg.posX, this->posY - arg.posY, this->posZ - arg.posZ);
}

CPoint CPoint::operator* ( const double scalar ) const {
    return CPoint (this->posX * scalar, this->posY * scalar, this->posZ * scalar);
} 

CPoint CPoint::operator/ ( const double scalar ) const {
    return CPoint (this->posX / scalar, this->posY / scalar, this->posZ / scalar);
}

std::ostream& operator<< ( std::ostream& os, const CPoint& point ) {
    os << '(' << point.posX << ", " << point.posY << ", " << point.posZ << ')';
    return os;
}

double CPoint::distance ( const CPoint& arg ) const {
    return sqrt((this->posX - arg.posX) * (this->posX - arg.posX) + 
                (this->posY - arg.posY) * (this->posY - arg.posY) + 
                (this->posZ - arg.posZ) * (this->posZ - arg.posZ));
}