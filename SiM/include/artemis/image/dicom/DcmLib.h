/**
 * @file
 *
 * This file contains a class to manipulate DCM Images. Dicom Images
 * are images what respect the pattern of ACR/NEMA for nuclear medical
 * images.
 *
 * @version 1.0
 * @author 004
 * @author 005
 * @author 006
 * @date 09-03-2010
 */

#ifndef DCMLIB_HPP
#define DCMLIB_HPP

#include <cstdlib>
#include <sstream>
#include <ImageBase.h>
#include <dicomlib/dicomlib.hpp>

#include <cv.h>
#include <highgui.h>


/**
 * This class has the references to manipulate
 * and extract information from DICOM medical
 * files. All information are powered, at this
 * implementation, using dicomlib under GPL
 * License.
 *
 * @brief Class to manipulate DICOM Images
 * @author 004
 * @author 005
 * @author 006
 *
 * @todo Implement DICOM tag getters and setters for other datatypes than string.
 *
 * @version 1.0
 * @date 15/02/2010
 * @see ImageBase.hpp
 */
class DCMImage : public Image {

    public:
        dicom::DataSet data;

    public:

        DCMImage();
        DCMImage(std::string filename);
        virtual ~DCMImage();

        void openImage(std::string filename);
        void windowing(size_t width, size_t center);

        void saveToFile(std::string filename) throw (std::runtime_error);

        DCMImage* clone();

        std::string getStringTag(dicom::Tag tagId) const;
};

#endif

