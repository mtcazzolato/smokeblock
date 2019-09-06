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

#ifndef SMOKEBLOCKCLASSIFIER_HPP
#define SMOKEBLOCKCLASSIFIER_HPP

#include <opencv2/core/types_c.h>
#include <opencv2/core/core_c.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <stdio.h>
#include <math.h>
#include <vector> 	/// std:vector
#include <utility> 	/// std::pair
#include <float.h>
#include <fstream>
#include <sstream>
#include <iterator>

#include "Artemis.h"
#include "Hermes.h"
#include "BasicArrayObject.h"

#include "Slic.hpp"
#include "NBClassifier.hpp"
#include "SmokeBlockResult.hpp"

typedef BasicArrayObject<double> Signature;

class SmokeBlockClassifier
{
public:
    /// Constructor
    SmokeBlockClassifier();
    /// Destructor
    virtual ~SmokeBlockClassifier();
    /// Process input image, extract superpixels, classify and segment smoke areas
    SmokeBlockResult* processImage(cv::Mat *image);
    /// Process input image and return the predicted class
    int classify(cv::Mat *image);
    /// Draw MBRs in the input image
    void drawMBRs(cv::Mat *image);
private:
    int initializeClassifier();
    /// Train classifier
    int trainClassifier(std::vector< std::vector<double> > dataset, std::vector<int> classValues);
    /// Train global classifier
    int trainGlobalClassifier(std::vector< std::vector<double> > dataset, std::vector<int> classValues);
    /// Train classifier from CSV train file
    int trainClassifierFromCSV();
    /// Classify and segment a given image
    void classifyImage(cv::Mat *image);
    /// Segment a given image, based on the classification of each superpixel
    void segmentImage(cv::Mat *image, vec2di clusters);
    /// Generate superpixels from an image, using Slic algorithm
    vec2di generateSuperpixels(cv::Mat *image);
    /// Read train data from CSV
    std::vector< std::vector<double> > readTrainData(std::string filepath);
    /// Read train class data from CSV
    vector<int> readTrainClasses(std::string filepath);
    /// Get the MBR coordinates, considering the superpixel regions classified as smoke
    std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > getMBRs(cv::Mat *th_image, cv::Mat *src_image);
    /// Extract features from superpixels
    vector<double> extractFeatures(Image *image);
    /// Extract Color Layout features from the given image
    Signature getColorLayoutFeatures(Image *image);
    /// Extract Haralick reafures from the given image
    Signature getHaralickFeatures(Image *image);
    /// Concatenate two feature vectors
    std::vector<double> concatenateFeatureVectors(Signature fv1, Signature fv2);
    /// Convert IplImage to Image (from Artemis library)
    Image* Mat2Image(cv::Mat *image);
    
    /// step size
    int step;
    /// weight
    int nc;
    /// Number of superpixels
    int numberOfSuperpixels;    
    /// Naive Bayes classifier
    NBClassifier *classifier;
    /// Global Naive Bayes classifier
    NBClassifier *globalClassifier;
    /// Obtained results
    SmokeBlockResult *sbResults;
    
    std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > smokeSuperpixelPoints;
};

#endif /* SMOKEBLOCKCLASSIFIER_HPP*/