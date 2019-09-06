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
* This code was adapted from the code of Pascal Mettes, available
* in <https://github.com/PSMM/SLIC-Superpixels>
* Description: This file contains the class elements of the class Slic. This
* class is an implementation of the SLIC Superpixel algorithm by
* Achanta et al. 2012 [PAMI'12, vol. 34, num. 11, pp. 2274-2282].
*
* RESCUER Project
* Reliable and Smart Crowdsourcing Solution for Emergency and Crisis Management
* Smoke Block Classifier
*/

#ifndef SLIC_HPP
#define SLIC_HPP

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <float.h>

/// 2d matrices are handled by 2d vectors
#define vec2dd std::vector< std::vector<double> >
#define vec2di std::vector< std::vector<int> >
#define vec2db std::vector< std::vector<bool> >

/// The number of iterations run by the clustering algorithm
#define NR_ITERATIONS 10

class Slic {
    private:
        /// Cluster assignments for each pixel
        vec2di clusters;
        /// Distance values for each pixel
        vec2dd distances;
        /// LAB and xy values of the centers
        vec2dd centers;
        /// Number of occurences of each center
        std::vector<int> centerCounts;
        /// Step size per cluster, color (nc) and distance (ns) parameters
        int step, nc, ns;
        /// Compute the distance between a center and an individual pixel
        double computeDistance(int ci, CvPoint pixel, CvScalar colour);
        /// Find the pixel with the lowest gradient in a 3x3 surrounding
        CvPoint findLocalMinimum(cv::Mat *image, CvPoint center);
        /// Remove and initializes the 2d vectors
        void clearData();
        void initializeData(cv::Mat *image);
    public:
        /// Constructor
        Slic();
        /// Destructor
        virtual ~Slic();
        /// Generate superpixels for a given image
        void generateSuperpixels(cv::Mat *image, int step, int nc);
        /// Create connectivity between clusters for an image
        void createConnectivity(cv::Mat *image);
        /// Draw center point of each superpixel
        void displayCenterGrid(cv::Mat *image, CvScalar colour);
        /// Draw the contour of each superpixel
        void displayContours(cv::Mat *image, CvScalar colour);
        /// Paint each superpixel with the mean color of each region
        void colorWithClusterMeans(cv::Mat *image);
        /// Get matrix of pixels
        std::vector< std::vector<int> > getMatrixOfPiixels();
        /// Get total number of superpixels created
        int getNumberOfSuperpixels();
};

#endif // SLIC_HPP
