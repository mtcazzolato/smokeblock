/**
* @file
*
* This file contains the definition of the YUVColorSystem class.
*
* @version 1.0
* @author 009
* @author 006
* @date 01-10-2014
*/
#ifndef SRGBCOLORSYSTEM_H
#define SRGBCOLORSYSTEM_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <Pixel.h>

/**
* @author 009
* @author 006
* @version 1.0.
*/
class SRGBColorSystem {

    public:
        SRGBColorSystem();
        ~SRGBColorSystem();

        double getROfSRGB(Pixel p);
        double getGOfSRGB(Pixel p);
        double getBOfSRGB(Pixel p);
};

#endif
