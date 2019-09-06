/**
 * @file
 *
 * This file contains the implementation of the DCMImage class.
 */

#include "DcmLib.h"


/**
* Default class constructor.
*/
DCMImage::DCMImage() {

}

/**
* Class constructor that opens the DICOM image in the provided file.
*
* @param filename: The name of the file.
* @exception dicom_error If the image file could not be opened.
* @see openImage(string filename)
*/
DCMImage::DCMImage(std::string filename) {

    openImage(filename);
}

/**
* Class destructor.
*/
DCMImage::~DCMImage() {
}

/**
* Opens the DICOM image in the provided file.
*
* @param filename: The name of the file.
*/
void DCMImage::openImage(std::string filename) {

    dicom::Read(filename, data);
    setFilename(filename);

    if (data.empty()){
       throw std::runtime_error("The DICOM image file cannot be opened or the file does not exists");
    }

    setImageID(0);
    unsigned short w, h, bpp, cha;
    data(dicom::TAG_ROWS) >> h;
    data(dicom::TAG_COLUMNS) >> w;
    data(dicom::TAG_SAMPLES_PER_PX) >> cha;
    data(dicom::TAG_BITS_ALLOC) >> bpp;

    setWidth(w);
    setHeight(h);
    setBitsPerPixel(bpp);
    setChannels(cha);
    setImageID(0);

    deletePixelMatrix();
    try{
        createPixelMatrix(getWidth(), getHeight());
    } catch (...) {
        throw std::runtime_error("Cannot create pixel matrix on DCM image");
    }


    std::vector<unsigned short> pixelData;
    data(dicom::TAG_PIXEL_DATA) >> pixelData;

    //Converts the dicomlib to Pixel Matrix
    for(size_t x = 0; x < getWidth(); x++){
        for(size_t y = 0; y < getHeight(); y++){
            Pixel aux (pixelData[(x*getWidth())+y], pow (2, getBitsPerPixel()));
            setPixel(x, y, aux);
        }
    }
    pixelData.clear();

    /*int wWidth, wCenter;
    wWidth = (int) atof (getStringTag(dicom::TAG_WINDOW_WIDTH).c_str());
    wCenter = (int) atof (getStringTag(dicom::TAG_WINDOW_CENTER).c_str());

    cout << wWidth << " " << wCenter << endl;

    windowing(2000, 1500);*/
}

void DCMImage::windowing(size_t width, size_t center){

    Image *aux = clone();

    u_int16_t numBins = pow(2, aux->getBitsPerPixel());
    double grayScale[numBins];

    for (size_t i = 0; i < numBins; i++){
        if (i < (center-(width/2))){
            grayScale[i] = 0;
        } else {
            if (i < (center + (width/2))){
                grayScale[i] = (numBins/width)*(i - (center - (width/2)));
                if (grayScale[i] < 0){
                    grayScale[i] = 0;
                } else {
                    if (grayScale[i] > numBins-1){
                        grayScale[i] = numBins - 1;
                    }
                }
            } else {
                grayScale[i] = numBins - 1;
            }
        }
    }

    //AVOID MEMORY LEAK --- EXTREMELY IMPORTANT!!!!!!!!!!!!
    aux->deletePixelMatrix();
    aux->createPixelMatrix(getWidth(), getHeight());

    for (size_t x = 0; x < aux->getWidth(); x++){
        for (size_t y = 0; y < aux->getHeight(); y++){
            Pixel *p = new Pixel(grayScale[(u_int16_t) getPixel(x, y).getGrayPixelValue()], numBins);
            setPixel(x, y, *p);
        }
    }

    delete (aux);
}
/**
* Saves the current DICOM image into a file.
*
* @param filename The name of the file.
*/
void DCMImage::saveToFile(std::string filename) throw (std::runtime_error){

    CvScalar s;
    IplImage *image = cvCreateImage(cvSize(getWidth(), getHeight()), IPL_DEPTH_8U, 0);

    u_int8_t div;
    if ((getBitsPerPixel() > 8) && (getBitsPerPixel() <= 16))
        div = 16;
    else
        div = 1;

    for(size_t x = 0; x < getWidth(); x++){
        for(size_t y = 0; y < getHeight(); y++){
            s.val[0] = (getPixel(x, y).getGrayPixelValue()/div);
            cvSet2D(image, x, y, s);
        }
    }

    filename.append(".bmp");

    if (!cvSaveImage(filename.c_str(), image)){
        throw std::runtime_error("This jpg file cannot been created!");
    }
}

/**
* Clones the current DICOM image.
*
* @return An DICOM image clone.
* @warning The caller of this method is responsible to dispose the returned object.
*/
DCMImage * DCMImage::clone() {
    return new DCMImage(*this);
}

/**
* Sets a string DICOM TAG value
*
* @param tagId The tag identification.
* @param tagValue The new tag value.
*
* @exception dicom_error If the DCMTK operation is not successful.
*/
//void DCMImage::setStringTag(DCMImage::TagID tagId, string & tagValue) {
//}

/**
* Gets a DICOM TAG string value
*
* @param tagId The tag identification.
* @return The tag value as string.
*
*/
std::string DCMImage::getStringTag(dicom::Tag tagId) const {

    //Not always will be a string
    dicom::Value vr(data(tagId));
    return dicom::GetValueDataInString(vr);
}

