/**
* @file
*
* This file contains the definition of the YUVColorSystem class.
*
* @version 1.0
* @author 009
* @author 006
* @date 15-08-2014
*/
#ifndef HSVCOLORSYSTEM_HPP
#define HSVCOLORSYSTEM_HPP

#include <Pixel.h>
#include <stdexcept>

/**
* @author 009
* @author 006
* @version 1.0.
*/
class HSVColorSystem {

    public:
        HSVColorSystem();
        ~HSVColorSystem();

        void toHSV(Pixel p, u_int16_t *hue, u_int16_t *saturation, u_int16_t *value) throw (std::runtime_error);
};

#endif
