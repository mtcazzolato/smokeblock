/**
* @file
*
* This file include all files needed by artemis.
*
* @version 1.0
* @author Marcelo Ponciano da Silva (ponciano@icmc.usp.br)
* @author Marcos Vinicius Naves Bedo (marcosivni@grad.icmc.usp.br)
* @date 11-03-2010
*/

#ifndef ARTEMIS_H
#define ARTEMIS_H

#include <math.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>

//#include <util/stException.h>

#include <extractor/Extractor.h>
#include <extractor/HaralickExtractor.h>
#include <extractor/HaralickFeature.h>
#include <extractor/MetricHistogram.h>
#include <extractor/TotalColorHistogram.h>
#include <extractor/NormalizedHistogram.h>
#include <extractor/Wavelets.h>
#include <extractor/ZernikeExtractor.h>
#include <extractor/TextureSpectrum.h>
#include <extractor/DiscreteCosineTransformation.h>
#include <extractor/YCrCbColorSystem.h>
#include <extractor/ColorLayout.h>
#include <extractor/ColorStructure.h>
#include <extractor/ScalableColor.h>
#include <extractor/EdgeHistogram.h>
#include <extractor/EdgeHistogramExtractor.h>
#include <extractor/SRGBColorSystem.h>
#include <extractor/XYZColorSystem.h>
#include <extractor/ColorTemperature.h>
#include <extractor/DaubechiesExtractor.h>
#include <extractor/HaarExtractor.h>
#include <extractor/TextureBrowsing.h>
#include <extractor/LocalBinaryPatternExtractor.h>
#include <extractor/BICHistogramExtractor.h>

#include <image/Pixel.h>
#include <image/ImageBase.h>
#include <image/bmp/BmpLib.h>
//#include <artemis/image/dicom/DcmLib.h>
#include <image/jpg/JpgLib.h>
//#include <artemis/image/krl/FileHandler.h>
//#include <artemis/image/krl/KrlLib.h>
#include <image/png/PngLib.h>

#endif
