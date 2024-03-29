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

#include "Slic.hpp"

/**
 * Constructor
 */
Slic::Slic()
{

}

/**
 * Destructor
 */
Slic::~Slic()
{
    clearData();
}

/**
 * Clear all data saved by the algorithm
 */
void Slic::clearData()
{
    clusters.clear();
    distances.clear();
    centers.clear();
    centerCounts.clear();
}

/**
 * Initialize the cluster centers and initial values of the pixel-wise cluster
 * assignment and distance values
 *
 * @param *image The image (Mat*).
 */
void Slic::initializeData(cv::Mat *image)
{
    /// Initialize the cluster and distance matrices
    for (int i = 0; i < image->cols; i++)
    {
        std::vector<int> cr; /// cluster
        std::vector<double> dr; /// distance

        for (int j = 0; j < image->rows; j++)
        {
            cr.push_back(-1);
            dr.push_back(FLT_MAX);
        }

        clusters.push_back(cr);
        distances.push_back(dr);
    }

    /// Initialize the centers and counters
    for (int i = step; i < image->cols - step/2; i += step)
    {
        for (int j = step; j < image->rows - step/2; j += step)
        {
            std::vector<double> center;
            /// Find the local minimum (gradient-wise)
            CvPoint nc = findLocalMinimum(image, cvPoint(i,j));
            
            CvScalar color = image->at<cv::Vec3b>(nc.y, nc.x);
           
            /// Generate the center vector
            center.push_back(color.val[0]);
            center.push_back(color.val[1]);
            center.push_back(color.val[2]);
            center.push_back(nc.x);
            center.push_back(nc.y);

            /// Append to vector of centers
            centers.push_back(center);
            centerCounts.push_back(0);
        }
    }
}

/**
 * Compute the distance between a cluster center and an given pixel
 *
 * @param ci The cluster index
 * @param pixel The pixel
 * @param color The Lab values of the pixel
 * @return The distance between the cluster and the pixel
 */
double Slic::computeDistance(int ci, CvPoint pixel, CvScalar color)
{
    double dc = sqrt(pow(centers[ci][0] - color.val[0], 2) + pow(centers[ci][1]
            - color.val[1], 2) + pow(centers[ci][2] - color.val[2], 2));
    double ds = sqrt(pow(centers[ci][3] - pixel.x, 2) + pow(centers[ci][4] - pixel.y, 2));

    return sqrt(pow(dc / nc, 2) + pow(ds / ns, 2));
}

/**
 * Find a minimum local gradient point of a pixel in a 3x3 neighborhood. This
 * method is called in the initialization of the cluster centers
 *
 * @param *image The image been segmented
 * @param center The pixel center
 * @return The minimum local gradient point
 */
CvPoint Slic::findLocalMinimum(cv::Mat *image, CvPoint center)
{
    double min_grad = FLT_MAX;
    CvPoint loc_min = cvPoint(center.x, center.y);

    for (int i = center.x-1; i < center.x+2; i++)
    {
        for (int j = center.y-1; j < center.y+2; j++)
        {
            CvScalar c1 = image->at<cv::Vec3b>(j+1, i);
            CvScalar c2 = image->at<cv::Vec3b>(j, i+1);
            CvScalar c3 = image->at<cv::Vec3b>(j, i);

            /// Convert color values to grayscale values
            double i1 = c1.val[0];
            double i2 = c2.val[0];
            double i3 = c3.val[0];

            /// Compute horizontal and vertical gradients and keep track of the minimum
            if (sqrt(pow(i1 - i3, 2)) + sqrt(pow(i2 - i3,2)) < min_grad)
            {
                min_grad = fabs(i1 - i3) + fabs(i2 - i3);
                loc_min.x = i;
                loc_min.y = j;
            }            
        }
    }

    return loc_min;
}

/**
 * Generates the image superpixels by computing the over-segmentation based
 * on the step-size and relative weighting of the pixel and color values
 *
 * @param *image The Lab image to be segmented
 * @param step The step size
 * @param nc the weight
 */
void Slic::generateSuperpixels(cv::Mat *image, int step, int nc)
{
    this->step = step;
    this->nc = nc;
    this->ns = step;
        
    /// Clear previous data (if any), and re-initialize it
    clearData();
    initializeData(image);
    
    /// Run EM for 10 iterations (as prescribed by the algorithm)
    for (int i = 0; i < NR_ITERATIONS; i++)
    {
        /// Reset distance values
        for (int j = 0; j < image->cols; j++)
        {
            for (int k = 0;k < image->rows; k++)
            {
                distances[j][k] = FLT_MAX;
            }
        }

        for (int j = 0; j < (int) centers.size(); j++)
        {
            /// Only compare to pixels in a 2 x step by 2 x step region. (2S x 2S)
            for (int k = centers[j][3] - step; k < centers[j][3] + step; k++)
            {
                for (int l = centers[j][4] - step; l < centers[j][4] + step; l++)
                {
                    if (k >= 0 && k < image->cols && l >= 0 && l < image->rows)
                    {
                        CvScalar color = image->at<cv::Vec3b>(l, k);
                        double d = computeDistance(j, cvPoint(k,l), color);

                        /// Update cluster allocation if the cluster minimizes the distance
                        if (d < distances[k][l])
                        {
                            distances[k][l] = d;
                            clusters[k][l] = j;
                        }
                    }
                }
            }
        }
        
        /// Clear the center values
        for (int j = 0; j < (int) centers.size(); j++)
        {
            centers[j][0] = centers[j][1] = centers[j][2] = centers[j][3] = centers[j][4] = 0;
            centerCounts[j] = 0;
        }

        /// Compute the new cluster centers
        for (int j = 0; j < image->cols; j++)
        {
            for (int k = 0; k < image->rows; k++)
            {
                int c_id = clusters[j][k];

                if (c_id != -1)
                {
                    CvScalar color = image->at<cv::Vec3b>(k, j);

                    centers[c_id][0] += color.val[0];
                    centers[c_id][1] += color.val[1];
                    centers[c_id][2] += color.val[2];
                    centers[c_id][3] += j; /// x
                    centers[c_id][4] += k; /// y

                    centerCounts[c_id] += 1;
                }
            }
        }

        /// Normalize the clusters
        for (int j = 0; j < (int) centers.size(); j++)
        {
            centers[j][0] /= centerCounts[j];
            centers[j][1] /= centerCounts[j];
            centers[j][2] /= centerCounts[j];
            centers[j][3] /= centerCounts[j];
            centers[j][4] /= centerCounts[j];
        }
    }
}

/**
 * Enforce connectivity of the superpixels. This part is not actively discussed
 * in the paper, but forms an active part of the implementation of the authors
 * of the paper
 *
 * @param *image The input image
 */
void Slic::createConnectivity(cv::Mat *image)
{
    int label = 0, adjlabel = 0;
    const int lims = (image->cols * image->rows) / ((int)centers.size());

    const int dx4[4] = {-1,  0,  1,  0};
    const int dy4[4] = { 0, -1,  0,  1};

    /// Initialize the new cluster matrix
    vec2di newClusters;
    for (int i = 0; i < image->cols; i++)
    {
        std::vector<int> nc;
        for (int j = 0; j < image->rows; j++)
        {
            nc.push_back(-1);
        }
        newClusters.push_back(nc);
    }

    for (int i = 0; i < image->cols; i++)
    {
        for (int j = 0; j < image->rows; j++)
        {
            if (newClusters[i][j] == -1)
            {
                std::vector<CvPoint> elements;
                elements.push_back(cvPoint(i, j));

                /// Find an adjacent label, for possible further use
                for (int k = 0; k < 4; k++)
                {
                    int x = elements[0].x + dx4[k], y = elements[0].y + dy4[k];

                    if (x >= 0 && x < image->cols && y >= 0 && y < image->rows)
                    {
                        if (newClusters[x][y] >= 0)
                        {
                            adjlabel = newClusters[x][y];
                        }
                    }
                }

                int count = 1;
                for (int c = 0; c < count; c++)
                {
                    for (int k = 0; k < 4; k++)
                    {
                        int x = elements[c].x + dx4[k], y = elements[c].y + dy4[k];

                        if (x >= 0 && x < image->cols && y >= 0 && y < image->rows)
                        {
                            if (newClusters[x][y] == -1 && clusters[i][j] == clusters[x][y])
                            {
                                elements.push_back(cvPoint(x, y));
                                newClusters[x][y] = label;
                                count += 1;
                            }
                        }
                    }
                }

                /// Use the earlier found adjacent label if a segment size is
                /// smaller than a limit
                if (count <= lims >> 2)
                {
                    for (int c = 0; c < count; c++)
                    {
                        newClusters[elements[c].x][elements[c].y] = adjlabel;
                    }
                    label -= 1;
                }
                label += 1;
            }
        }
    }
}

/**
 * Display the cluster centers
 *
 * @input *image The input image
 * @input color The color to be used to draw the center grids
 */
void Slic::displayCenterGrid(cv::Mat *image, CvScalar color)
{
    for (int i = 0; i < (int) centers.size(); i++)
    {
        cvCircle(image, cvPoint(centers[i][3], centers[i][4]), 2, color, 2);        
    }
}

/**
 * Display the contour of the superpixels (a single pixel wide contour)
 *
 * @param *image The input image
 * @param color The color to be used to draw the contour of the superpixels
 */
void Slic::displayContours(cv::Mat *image, CvScalar color)
{
    const int dx8[8] = {-1, -1,  0,  1, 1, 1, 0, -1};
    const int dy8[8] = { 0, -1, -1, -1, 0, 1, 1,  1};

    /// Initialize the contour vector and the matrix detailing whether a pixel
    /// is already taken to be a contour.
    std::vector<CvPoint> contours;
    vec2db istaken;
    for (int i = 0; i < image->cols; i++) {
        std::vector<bool> nb;
        for (int j = 0; j < image->rows; j++) {
            nb.push_back(false);
        }
        istaken.push_back(nb);
    }

    /// Go through all the pixels
    for (int i = 0; i < image->cols; i++) {
        for (int j = 0; j < image->rows; j++) {
            int nr_p = 0;

            /// Compare the pixel to its 8 neighbours
            for (int k = 0; k < 8; k++) {
                int x = i + dx8[k], y = j + dy8[k];

                if (x >= 0 && x < image->cols && y >= 0 && y < image->rows) {
                    if (istaken[x][y] == false && clusters[i][j] != clusters[x][y]) {
                        nr_p += 1;
                    }
                }
            }

            /// Add the pixel to the contour list if desired
            if (nr_p >= 2) {
                contours.push_back(cvPoint(i,j));
                istaken[i][j] = true;
            }
        }
    }

    /// Draw the contour pixels
    for (int i = 0; i < (int)contours.size(); i++) {
        image->at<cv::Vec3b>(contours[i].y, contours[i].x)[0] = color.val[0];
        image->at<cv::Vec3b>(contours[i].y, contours[i].x)[1] = color.val[1];
        image->at<cv::Vec3b>(contours[i].y, contours[i].x)[2] = color.val[2];
    }    
}

/**
 * Paint the pixels of each cluster with the same color values.
 * The specified color is the mean RGB color per cluster
 *
 * @param *image The input image
 */
void Slic::colorWithClusterMeans(cv::Mat *image)
{
    std::vector<CvScalar> colors(centers.size());

    /// Gather the color values per cluster
    for (int i = 0; i < image->cols; i++)
    {
        for (int j = 0; j < image->rows; j++)
        {
            int index = clusters[i][j];

            colors[index].val[0] += image->at<cv::Vec3b>(j, i)[0];
            colors[index].val[1] += image->at<cv::Vec3b>(j, i)[1];
            colors[index].val[2] += image->at<cv::Vec3b>(j, i)[2];            
        }
    }

    /// Divide by the number of pixels per cluster to get the mean color
    for (int i = 0; i < (int)colors.size(); i++)
    {
        colors[i].val[0] /= centerCounts[i];
        colors[i].val[1] /= centerCounts[i];
        colors[i].val[2] /= centerCounts[i];
    }

    /// Fill in
    for (int i = 0; i < image->cols; i++)
    {
        for (int j = 0; j < image->rows; j++)
        {
            CvScalar ncolor = colors[clusters[i][j]];
            image->at<cv::Vec3b>(j, i)[0] = ncolor.val[0];
            image->at<cv::Vec3b>(j, i)[1] = ncolor.val[1];
            image->at<cv::Vec3b>(j, i)[2] = ncolor.val[2];
        }
    }
}

/**
 * Get the matrix of pixels, with the superpixel region assignment of each pixel 
 * @return The matrix of pixels
 */
vec2di Slic::getMatrixOfPiixels()
{
    return this->clusters;
}

/**
 * Get the number of generated superpixels
 * @return Number of generated superpixels
 */
int Slic::getNumberOfSuperpixels()
{
    return (this->centers.size());
}
