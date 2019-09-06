/**
* Copyright (C) 2015 Mirela Teixeira Cazzolato <mirelac@usp.br>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*
* RESCUER Project
* Reliable and Smart Crowdsourcing Solution for Emergency and Crisis Management
* Smoke Block Classifier
*/

#ifndef SMOKEBLOCKRESULT_HPP
#define SMOKEBLOCKRESULT_HPP

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <math.h>
#include <vector> 	/// std:vector
#include <utility> 	/// std::pair
#include <float.h>

class SmokeBlockResult
{
public:
    /// Constructor
    SmokeBlockResult();
    /// Constructor
    SmokeBlockResult(std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > >, int what);
    /// Destructor
    virtual ~SmokeBlockResult();
    /// Set resulting Minimum Bounding Rectangles, concerning the smoke regions
    void setResultingMBR(std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > mbrs);
    /// Get resulting Minimum Bounding Rectangles, concerning the smoke regions
    std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > getResultingMBR();
    /// Set resulting what tag
    void setResultingWhatTag(int what);
    /// Get resulting what tag
    int getResultingWhatTag();
    /// Set resulting (segmented) image
    void setResultingImage(cv::Mat *segmentedImage);
    /// Get resulting (segmented) image
    cv::Mat* getResultingImage();
    /// Set resulting colors
    void setResultingMeanColors(std::vector<CvScalar> colors);
    /// Get resulting RGB mean colors
    //vector<CvScalar> getResultingBGRMeanColors();
    std::vector<CvScalar> getResultingBGRMeanColors();
    /// Get and Set resulting H, S and V color
    void setResultingHColor(std::vector< float > h);
    std::vector< float > getResultingHColor();
    void setResultingSColor(std::vector< float > s);
    std::vector< float > getResultingSColor();
    void setResultingVColor(std::vector< float > v);     
    std::vector< float > getResultingVColor();

private:
    /// MBRs coordinates of the identified smoke regions
    std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > mbrs;	
    /// "what" tag
    int what;
    /// Convert RGB to HSV color space values
    void RGB2HSV(CvScalar BGRcolor);

    /// H, S and V values. Each position of the vector corresponds to a MBR
    std::vector< float > hColors;
    std::vector< float > sColors;
    std::vector< float > vColors;
    /// Resulting Mean colors of RGB color space
    std::vector<CvScalar> resultingMeanColors;
    /// Resulting segmented image
    cv::Mat *segmentedImage;
};

#endif /* SMOKEBLOCKRESULT_HPP */
