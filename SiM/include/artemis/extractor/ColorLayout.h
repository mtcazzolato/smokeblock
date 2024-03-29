/**
 * @file
 *
 * This file defines a Class to extract a Color Layout of the image. This extractor is defined by MPEG7 pattern.
 *
 * @version 1.0
 * @author 009
 * @author 006
 * @see Image stBasicArrayObject
 * @date 23-07-2014
 */

#ifndef COLORLAYOUT_H
#define COLORLAYOUT_H

#include <DiscreteCosineTransformation.h>
#include <YCrCbColorSystem.h>
#include <Extractor.h>
#include <ImageBase.h>


template< class SignatureType, class DataObjectType = Image >
class ColorLayoutExtractor : public Extractor<SignatureType, DataObjectType> {

    private:
        u_int16_t numFeatures;
        u_int16_t numBlocks;

    private:
        std::vector<vector<int32_t> > imageSplitter(const u_int16_t channels, const u_int16_t dimension, const DataObjectType &image,
                                                std::vector<std::vector<int32_t> > blocks) throw (std::runtime_error);
        std::vector<std::vector<int32_t> > averageRepresentativeColorDefault(const u_int16_t channels, const u_int16_t dimension, int32_t *count, int32_t **sum, std::vector<std::vector<int32_t> > blocks);
        void quantifyYChannel(const int32_t block_value, int32_t &new_value);
        void quantifyCChannel(const int32_t block_value, int32_t &new_value);
        void quantify(const int32_t block_value, int32_t &new_value);
        void calculateZigZagPattern(const u_int16_t dimension, int32_t *zigzag);
        void sumQuantify(const u_int16_t dimension, std::vector<std::vector<int32_t> > blocks, int32_t **descriptor) throw (std::runtime_error);

    public:
        ColorLayoutExtractor(u_int16_t value1 = 256, u_int16_t value2 = 64);
        virtual ~ColorLayoutExtractor();

        void setNumFeatures(u_int16_t value);
        void setNumBlocks(u_int16_t value);

        u_int16_t getNumFeatures();
        u_int16_t getNumBlocks();

        u_int16_t getDimension() throw (std::bad_alloc*) ;

        virtual void generateSignature(const DataObjectType &image, SignatureType &sign) throw (std::runtime_error);
};


#include "ColorLayout-inl.h"
#endif
