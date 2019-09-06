/**
 * @file
 *
 * This file defines a Class to DCT Transformation
 *
 * @version 1.0
 * @author 009
 * @author 006
 * @date 23-07-2014
 */
#ifndef DCTTRANSFORMATION_H
#define DCTTRANSFORMATION_H

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <stdexcept>
#include <cmath>

class DiscreteCosineTransformation {

    private:
        u_int8_t dimension;

	public:
        DiscreteCosineTransformation(u_int8_t dim = 8);
        virtual ~DiscreteCosineTransformation();

        void setDimension(u_int8_t value);
        u_int8_t getDimension();

        std::vector<int32_t> applyDCT(std::vector<int32_t> blocksValues) throw (std::range_error, std::runtime_error);
};

#endif
