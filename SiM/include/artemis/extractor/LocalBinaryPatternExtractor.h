#ifndef LOCALBINARYPATTERNEXTRACTOR_H
#define LOCALBINARYPATTERNEXTRACTOR_H

#include <ImageBase.h>
#include <Extractor.h>

/**
 * This is a Template-Class. 
 *
 * <P> A Local Binary Pattern is a the frequency of all textures codes 
 * for the 8-neighbors pixel region in the Image of each color band. This
 * implementation creates a feature vector with 59 textures code, 58 uniforms
 * and 1 non-uniform.
 *
 * NOTE:
 * <ul>
 * <li>SignatureType must be an array object satisfying interface stObject
 * (e.g. stBasicArrayObject <double>);</li>
 * <li>normalizationRange is the maximum value of a bin in the normalization,
 * i.e., every bin is in the range [0, normalizationRange]. It defaults to 1.<br/>
 * The normalization in the range [0, 1] means that the sum of all bin values
 * is equal to 1. The normalization in the range [0, normalizationRange] first
 * normalize the bin values in the range [0, 1] and, thereafter, divides every
 * value is divided by the maximum value found, making the maximum equals to
 * normalizationRange.</li>
 * </ul>
 *
 * @brief Extractor of Local Binary Pattern (8-neighbors)
 * @author 014
 * @see BasicArrayObject
 * @version 1.0
 */
template< class SignatureType, class DataObjectType = Image >
class LocalBinaryPatternExtractor : public Extractor<SignatureType, DataObjectType> {
    private:
        u_int16_t numFeatures;

    protected:
        u_int16_t lookUp[256];

    private:
        void createLookUp();

    public:
        LocalBinaryPatternExtractor(u_int16_t value = 59);
        virtual ~LocalBinaryPatternExtractor();
        u_int16_t getNumFeatures();
        void setNumFeatures(u_int16_t value);
        void generateSignature(const DataObjectType & image, SignatureType & sign);

};

#include "LocalBinaryPatternExtractor-inl.h"

#endif
