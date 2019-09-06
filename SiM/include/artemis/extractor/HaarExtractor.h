/**
* @file
*
* This file defines the basis for for Daubechies and Haar Wavelets Extractor.
*
* @version 1.0
* @author 005
* @author 006
* @date 18-08-2010
*/
#ifndef HAAREXTRACTOR_H
#define HAAREXTRACTOR_H

#include <vector>
#include <cmath>
#include <cfloat>


#include <Extractor.h>
#include <Wavelets.h>
#include <ImageBase.h>

/**
* This is a Template-Class. A template-parameter levels defines the levels
* utilized on the Wavelet. The template parameter vectorComposition defines
* a type of signature what will be utilized.
*
* @brief Implementation of Haar Wavelet Extractor
* @author 005
* @author 006
* @see ImageBase
* @see ImageException
* @version 1.0
*/
template< class SignatureType, class DataObjectType = Image >
class HaarExtractor : public Extractor<SignatureType, DataObjectType> , public Wavelets <SignatureType, DataObjectType>{
    public:
        HaarExtractor();
        virtual ~HaarExtractor();

        virtual void generateSignature(const DataObjectType & img, SignatureType & sign) throw (std::runtime_error);
};

#include "HaarExtractor-inl.h"
#endif
