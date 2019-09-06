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

#ifndef NBCLASSIFIER_HPP
#define NBCLASSIFIER_HPP

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <float.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <map>

class NBClassifier
{
public:
    /// Constructor
    NBClassifier();
    /// Destructor
    virtual ~NBClassifier();
    /// Classify a given image feature vector
    int trainClassifier(std::vector< std::vector<double> > dataset, std::vector<int> classes);
    /// Classify an image as smoke or not_identified, given the feature vector
    int classify(std::vector<double> fvector);        
private:
    void processInputData(std::vector< std::vector<double> > dataset, std::vector<int> classes);
    /// Default number of attributes
    static int defaultNumberOfAttributes;
    /// Default number of class values
    static int defaultNumberOfClasses;
    /// Total number of data
    unsigned int n_total;
    std::map<int, int> n;
    /// 
    std::map<int, double> priors;
    /// Dataset
    std::map<int, std::vector< std::vector<double> > > data;
    /// Sum for each class of each feature
    std::map<int, std::vector<double> > sum_x;
    /// Mean for each class of each feature
    std::map<int, std::vector<double> > means;
    /// Variance for each class of each feature
    std::map<int, std::vector<double> > variances;
};

#endif // NBCLASSIFIER_HPP
