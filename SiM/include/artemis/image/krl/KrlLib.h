/**
* @file
*
* This file contains a class to manipulate KRL Images. KRL images are
* scanned medical images with a little header.
*
* This header is represented here by a struct, but your attributes are
* relationed only with the image.
*
* @version 1.0
* @author 005
* @author 006
* @date 11-01-2010
*/
#ifndef KRLLIB_HPP
#define KRLLIB_HPP

#include <ImageBase.h>
#include <krl/FileHandler.h>

/**
* This struct is a header for KRL images.
*
* @brief Header for KRL Images.
* @author 005
* @author 006
* @version 1.0
*/
struct KrlHeaderType {
       
    unsigned short headerType;
    char filename[32];
    unsigned short width;
    unsigned short height;
    char pixBytes;
    char pixBits;
    char OS;
    char compress;
    unsigned short compParas[5];
    char hdtime[32];
    char imgType;
    char black;
    unsigned short pixSize;
    unsigned short sampType;
    char optDensity;
    char dayNo[13];
    long medHistNo;
    char studyType[10];
    char patientName[50];
    char special[216];
    char comment[128];
};

/**
* @brief Handler Class to KRL Images
*
* @author 005
* @author 006
* @see ImageBase
* @see ImageException
* @see krlsample.cpp
* @version 1.0
*/
class KRLImage : public Image{

    private:            
        KrlHeaderType header;
        
    public:
        KRLImage();
        KRLImage(std::string filename);
        virtual ~KRLImage();
        
        void openImage(std::string filename) throw (std::runtime_error);
        
        KRLImage* clone();
};

#endif
