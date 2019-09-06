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

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include "opencv2/core/types_c.h"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "detector/Slic.hpp"
#include "detector/SmokeBlockClassifier.hpp"
#include "detector/SmokeBlockResult.hpp"
#include "detector/NBClassifier.hpp"

int main(int argc, char const *argv[])
{
    printf ("*** SmokeBlock classifier ***");

    /// Input: a Mat image
    cv::Mat image = cv::imread("/home/mirela/Desktop/imgs/2603685851.jpg");

    cv::namedWindow("original", cv::WINDOW_AUTOSIZE);
    cv::imshow("original", image);
    
    SmokeBlockClassifier *sbClassifier = new SmokeBlockClassifier();
    std::cout << "Process" << endl;
    SmokeBlockResult *result = sbClassifier->processImage(&image);
    std::cout << "Processing done" << std::endl;
    
    /// BEGIN-RESULTS ==========================================================
    std::cout << std::endl << "what = " << result->getResultingWhatTag() << std::endl;
    std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > mbrs = result->getResultingMBR();
    
    for (int i = 0; i < mbrs.size(); i++)
    {
        std::cout << "P1 (" << mbrs[i].first.first << ", " << mbrs[i].first.second
                << ") - P2 (" << mbrs[i].second.first << ", " << mbrs[i].second.second << ")" << std::endl;
        
        std::cout << "H = " << result->getResultingHColor().at(i)
                << ", S = " << result->getResultingSColor().at(i)
                << ", V = " << result->getResultingVColor().at(i) << std::endl;
        
        std::cout << "R = " << result->getResultingBGRMeanColors().at(i).val[2]
                << ", G = " << result->getResultingBGRMeanColors().at(i).val[1]
                << ", B = " << result->getResultingBGRMeanColors().at(i).val[0] << std::endl << std::endl;
    }
    
    sbClassifier->drawMBRs(&image);
    /// END-RESULTS ============================================================
    
    cv::Mat resultingImage = result->getResultingImage()->clone();
    
    cv::namedWindow("Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Image", resultingImage);
    cv::waitKey(0);
    //cvReleaseImage(&image);

//    return 0;
}
