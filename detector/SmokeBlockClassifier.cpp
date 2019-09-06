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

#include "SmokeBlockClassifier.hpp"

/**
 * Constructor
 */
SmokeBlockClassifier::SmokeBlockClassifier()
{
    this->classifier = new NBClassifier();
    this->globalClassifier = new NBClassifier();
    this->sbResults = new SmokeBlockResult();
    this->step = 45;
    this->nc = 150;
}

/**
 * Destructor
 */
SmokeBlockClassifier::~SmokeBlockClassifier()
{

}

/**
 * Train classifier, extract superpixel, classify each region, segment image
 * and generate results
 * @param image Input image
 * @return SmokeBlockResult object, containing the outputs from SmokeBlockClassifier
 */
SmokeBlockResult* SmokeBlockClassifier::processImage(cv::Mat *image)
{
    trainClassifierFromCSV();
    classifyImage(image);
    return this->sbResults;
}

/**
 * Train classifier, extract superpixel, classify each region, segment image
 * and generate results
 * @param image Input image
 * @return predicted class
 */
int SmokeBlockClassifier::classify(cv::Mat *image)
{
    trainClassifierFromCSV();
    classifyImage(image);
    return this->sbResults->getResultingWhatTag();
}

/**
 * Train classifier using training data from CSV, and save built model.
 * @return 0 if model was built and saved successfully
 */
int SmokeBlockClassifier::trainClassifierFromCSV()
{
    /// Read global training data
    std::vector< std::vector<double> > globalDataset = readTrainData("use/train/features/training_global_cl_hr.csv");
    /// Read global class data
    std::vector<int> globalClassValues = readTrainClasses("use/train/features/training_global_classes.csv");
    
    /// Read superpixel training data
    std::vector< std::vector<double> > dataset = readTrainData("use/train/features/training_cl_hr.csv");
    /// Read superpixel class data
    std::vector<int> classValues = readTrainClasses("use/train/features/training_classes.csv");
    
    //printf("Dataset loaded.\n");
    
    /// Train global classifier
    trainGlobalClassifier(globalDataset, globalClassValues);
    
    /// Train superpixel classifier
    trainClassifier(dataset, classValues);
    
    return 0;
}

/**
 * Train global classifier and save built model.
 * @param dataset All data to be used in the training phase
 * @param classValues All classifications of the dataset been used in the training phase
 * @return 0 if model was built and saved successfully
 */
int SmokeBlockClassifier::trainGlobalClassifier(std::vector< std::vector<double> > dataset, std::vector<int> classValues)
{
    this->globalClassifier->trainClassifier(dataset, classValues);
    return 0;
}

/**
 * Train classifier and save built model.
 * @param dataset All data to be used in the training phase
 * @param classValues All classifications of the dataset been used in the training phase
 * @return 0 if model was built and saved successfully
 */
int SmokeBlockClassifier::trainClassifier(std::vector< std::vector<double> > dataset, std::vector<int> classValues)
{
    this->classifier->trainClassifier(dataset, classValues);
    return 0;
}

/**
 * Classify the superpixels of the given image, and segment the image
 * @param image Pointer to the image to be segmented
 */
void SmokeBlockClassifier::classifyImage(cv::Mat *image)
{   
    vec2di clusters = generateSuperpixels(image);
    segmentImage(image, clusters);
        
    /// Classify global image
    Image *newimage = Mat2Image(image);
    std::vector<double> features = extractFeatures(newimage);
    int predictedClass = this->globalClassifier->classify(features);
    //printf("Predicted class = %d.\n", predictedClass);
    /// Set tag with the global classifier result
    this->sbResults->setResultingWhatTag(predictedClass);
    
    delete newimage;
}

/**
 * Generate superpixel regions of a given image
 * @param image The image to generate the superpixels
 * @return matrix of pixels and its corresponding superpixel
 */
vec2di SmokeBlockClassifier::generateSuperpixels(cv::Mat *image)
{
    Slic slic;
    /// Generate superpixels
    slic.generateSuperpixels(image, step, nc); /// step = 45 and adherence = 150 (color weight)
    /// Create connectivity
    slic.createConnectivity(image);
    vec2di pixels = slic.getMatrixOfPiixels();
    this->numberOfSuperpixels = slic.getNumberOfSuperpixels();
    
    return pixels;
}

/**
 * Get each superpixel, extracts the features and classify it as smoke or not.
 * Non-smoke regions are painted as yellow.
 * @param image Input image
 * @param clusters the matrix of pixels and its corresponding superpixel
 */
void SmokeBlockClassifier::segmentImage(cv::Mat *image, vec2di clusters)
{
    cv::Mat th_image = image->clone();
    vec2dd featureVectors;
    
    /// Superpixel boundaries
    std::vector<int> x1, x2, y1, y2;
    
    /// initialization
    for (int i = 0; i < this->numberOfSuperpixels; i++)
    {
        /// initializes ROI's bound
        x1.push_back(INT_MAX);
        x2.push_back(-1);
        y1.push_back(INT_MAX);
        y2.push_back(-1);
    }
    
    /// Determine the ROI of each superpixel
    for (int i = 0; i < clusters.size(); i++)
    {
        for (int j = 0; j < clusters.at(0).size(); j++)
        {
            /// Checks if pixel is included in a superpixel
            if (!(clusters[i][j] == -1))
            {                
                if ( i < x1.at(clusters[i][j]) ){
                    x1[ clusters[i][j] ] = i; /// Minor value of x
                }                
                if ( j < y1.at(clusters[i][j]) ){
                    y1[ clusters[i][j] ] = j; /// Minor value of y
                }                
                if ( i > x2.at(clusters[i][j]) ){
                    x2[ clusters[i][j] ] = i; /// Higher value of x
                }                
                if ( j > y2.at(clusters[i][j]) ){
                    y2[ clusters[i][j] ] = j; /// Higher value of y                 
                }
            }
        }
    }
    
    for (int imageIndex = 0; imageIndex < this->numberOfSuperpixels; imageIndex++)
    {   
        /// if the superpixel number is invalid
        if ((imageIndex < 0) || (imageIndex >= this->numberOfSuperpixels))
        {
            cerr << "Invalid superpixel number. Using default number (superpixel number -> 1)" << endl;
            imageIndex = 0;
        }
        
        int xmin = x1.at(imageIndex);
        int xmax = x2.at(imageIndex);
        int ymin = y1.at(imageIndex);
        int ymax = y2.at(imageIndex);
        
        cv::Mat changingImage = image->clone();
        cv::Rect region(xmin, ymin, xmax-xmin, ymax-ymin);
        changingImage = changingImage(region);
        
        CvSize size;
        size.width = region.width;
        size.height = region.height;
        cv::Mat currentROI = cv::Mat(size, CV_8UC1, changingImage.channels());

        currentROI = changingImage.clone();
        
        /// x coordinate
        for (int x = xmin; x < xmax; x++)
        {
            /// y coordinate
            for (int y = ymin; y < ymax; y++)
            {
                if (clusters[x][y] != imageIndex) /// Paint pixels of the region that are not part of the superpixel
                {
                    CvScalar s = currentROI.at<cv::Vec3b>(y-ymin, x-xmin);

                    //CvScalar s;
                    //s = cvGet2D(&currentROI, y-ymin, x-xmin); /// Get the (x,y) pixel value
                    s.val[0] = 255; /// R
                    s.val[1] = 255; /// G
                    s.val[2] = 255; /// B
                    //cvSet2D(&currentROI, y-ymin, x-xmin, s); /// Set the (x,y) pixel value
                    currentROI.at<cv::Vec3b>(y-ymin, x-xmin)[0] = s.val[0];
                    currentROI.at<cv::Vec3b>(y-ymin, x-xmin)[1] = s.val[1];
                    currentROI.at<cv::Vec3b>(y-ymin, x-xmin)[2] = s.val[2];
                }
            }
        }
        
        /// Extract features from the current ROI
        Image *image2 = Mat2Image(&currentROI);
        std::vector<double> features = extractFeatures(image2);
        int predictedClass = this->classifier->classify(features);
        
        /// Paint superpixels
        if (predictedClass == 0) // superpixel classified as non smoke
        {
            for (int x = xmin; x <= xmax; x++) /// x coordinate
            {
                for (int y = ymin; y <= ymax; y++) /// y coordinate
                {
                    if (clusters[x][y] == imageIndex)
                    {
                        /// Segment original image
                        //CvScalar s;
                        //s = cvGet2D(image, y, x); /// Get the (x,y) pixel value
                        CvScalar s = image->at<cv::Vec3b>(y, x);
                        s.val[0] = 0; /// B
                        s.val[1] = 0; /// G
                        s.val[2] = 0; /// R
                        //cvSet2D(image, y, x, s); /// Set the (x,y) pixel value
                        image->at<cv::Vec3b>(y, x)[0] = s.val[0];
                        image->at<cv::Vec3b>(y, x)[1] = s.val[1];
                        image->at<cv::Vec3b>(y, x)[2] = s.val[2];
                        
                        /// Paint threshold image
                        //s = cvGet2D(&th_image, y, x); /// Get the (x,y) pixel value
                        s = th_image.at<cv::Vec3b>(y, x);
                        s.val[0] = 255; /// B
                        s.val[1] = 0; /// G
                        s.val[2] = 0; /// R
                        //cvSet2D(&th_image, y, x, s); /// Set the (x,y) pixel value
                        th_image.at<cv::Vec3b>(y, x)[0] = s.val[0];
                        th_image.at<cv::Vec3b>(y, x)[1] = s.val[1];
                        th_image.at<cv::Vec3b>(y, x)[2] = s.val[2];
                    }
                }
            }
        }
        else /// superpixel classified as smoke
        {
            for (int x = xmin; x <= xmax; x++) /// x coordinate
            {
                for (int y = ymin; y <= ymax; y++) /// y coordinate
                {
                    if (clusters[x][y] == imageIndex)
                    {
                        /// Paint threshold image
                        //CvScalar s;
                        //s = cvGet2D(&th_image, y, x); /// Get the (x,y) pixel value
                        CvScalar s = th_image.at<cv::Vec3b>(y, x);
                        s.val[0] = 255; /// B
                        s.val[1] = 255; /// G
                        s.val[2] = 255; /// R
                        //cvSet2D(&th_image, y, x, s); /// Set the (x,y) pixel value
                        th_image.at<cv::Vec3b>(y, x)[0] = s.val[0];
                        th_image.at<cv::Vec3b>(y, x)[1] = s.val[1];
                        th_image.at<cv::Vec3b>(y, x)[2] = s.val[2];
                    }
                }
            }
            
            /// Add smoke area coordinates
            std::pair <int, int> P1(xmin, ymin);
            std::pair <int, int> P2(xmax, ymax);
            std::pair< std::pair<int, int>, std::pair<int, int> > points(P1, P2);
            this->smokeSuperpixelPoints.push_back(points);
        }
        
        delete image2;        
    }
    
    getMBRs(&th_image, image);
    sbResults->setResultingImage(image);
}

/**
 * Get the MBR coordinates, and computes each MBR mean color
 * @param th_image the Threshold image, with smoke and non smoke pixels painted
 * @param source_image Segmented source image, with non-smoke regions painted
 * @return resulting MBR coordinates, for each region containing smoke
 */
std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > SmokeBlockClassifier::getMBRs(cv::Mat *th_image, cv::Mat *source_image)
{
    std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > mbrs;
    std::vector<CvScalar> regionColors;
    
    int thresh = 100;
    
    cv::Mat src_image = th_image->clone();
    cv::cvtColor(src_image, src_image, CV_BGR2GRAY);
    cv::blur(src_image, src_image, cv::Size(3,3));
    
    std::vector< std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    
    cv::threshold(src_image, src_image, thresh, 255, cv::THRESH_BINARY); /// Detect edges using threshold
    cv::findContours(src_image, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0,0)); /// Find contours
    
    std::vector< std::vector<cv::Point> > contours_poly(contours.size()); /// Approximate contours to polygons
    std::vector<cv::Rect> boundRect(contours.size()); /// Get bound rects
    
    for(int i = 0; i < contours.size(); i++)
    {
        cv::approxPolyDP(cv::Mat(contours[i]), contours_poly[i], 3, true);
        boundRect[i] = cv::boundingRect(cv::Mat(contours_poly[i]));
    }
        
    /// Add contours to results
    for (int i = 0; i < contours.size(); i++)
    {
        /// if region is not too small
        if(!((boundRect[i].br().x - boundRect[i].tl().x) < 20 || 
                (boundRect[i].br().y - boundRect[i].tl().y) < 20))
        {
            /// if region is inside another, inside = 1
            int inside = 0;
            
            for (int j = 0; j < boundRect.size(); j++)
            {
                if (    (boundRect[j].tl().x < boundRect[i].tl().x) &&
                        (boundRect[j].tl().y < boundRect[i].tl().y) &&
                        (boundRect[j].br().x > boundRect[i].br().x) &&
                        (boundRect[j].br().y > boundRect[i].br().y)     )
                {
                    /// Rectangle is inside another one. Do not add it to results.
                    inside = 1;
                }
            }

            if (inside == 0)
            {
                /// Compute mean color of the MBR region
                CvScalar meanColor;
                meanColor.val[0] = 0;
                meanColor.val[1] = 0;
                meanColor.val[2] = 0;                
                int superpixelcount = 0;
                
                std::pair <int, int> P1(boundRect[i].tl().x, boundRect[i].tl().y);
                std::pair <int, int> P2(boundRect[i].br().x, boundRect[i].br().y);
                std::pair< std::pair<int, int>, std::pair<int, int> > points(P1, P2);
                
                for (int x = boundRect[i].tl().x; x < boundRect[i].br().x; x++)
                {
                    for (int y = boundRect[i].tl().y; y < boundRect[i].br().y; y++)    
                    {
                        CvScalar s = th_image->at<cv::Vec3b>(y, x);

                        if (s.val[0] == 255 && s.val[1] == 255 && s.val[2] == 255) /// If pixel was classified as smoke
                        {
                            CvScalar s2 = source_image->at<cv::Vec3b>(y, x);
                            meanColor.val[0] += s2.val[0];
                            meanColor.val[1] += s2.val[1];
                            meanColor.val[2] += s2.val[2];
                            superpixelcount++;
                        }
                    }
                }
                
                /// Get the mean values of each region
                meanColor.val[0] /= superpixelcount;
                meanColor.val[1] /= superpixelcount;
                meanColor.val[2] /= superpixelcount;
                
                /// Add region coordinates to result
                mbrs.push_back(points);
                regionColors.push_back(meanColor);
            }
        }
    }
    
    /// Add resulting MBRs to result
    sbResults->setResultingMBR(mbrs);
    /// Set mean colors from each MBR
    sbResults->setResultingMeanColors(regionColors);
    
    /// Return computed MBR coordinates
    return mbrs;
}

/**
 * Draw MBR in the segmented image
 * @param image Input segmented image
 */
void SmokeBlockClassifier::drawMBRs(cv::Mat *image)
{
    std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > mbrs = this->sbResults->getResultingMBR();
    std::vector<CvScalar> colors = sbResults->getResultingBGRMeanColors();
    
    for (int i = 0; i < mbrs.size(); i++)
    {
        /// Paint MBR with main region color
        CvScalar color = colors[i];

        cv::rectangle
        (
            *image,
            cv::Point(mbrs[i].first.first, mbrs[i].first.second),
            cv::Point(mbrs[i].second.first, mbrs[i].second.second),
            color,
            4,
            8,
            0
        );
    }
}

/**
 * Convert Mat to Image, from Artemis library
 * @param image Input Mat to be converted
 * @return Image object, from Artemis library
 */
Image* SmokeBlockClassifier::Mat2Image(cv::Mat *image)
{
    Image *image2 = new JPGImage();
    image2->setChannels(image->channels());
    
    try
    {
        image2->createPixelMatrix((u_int32_t) image->cols, (u_int32_t) image->rows);
    }
    catch(...)
    {
        throw std::runtime_error("Cannot create the pixel matrix on jpg image");
    }
    
    //Converts the Mat OpenCVStructure to Pixel Matrix
    for (u_int32_t x = 0; x < image2->getWidth(); x++){
      for (u_int32_t y = 0; y < image2->getHeight(); y++){
          Pixel aux;
          
          aux.setRedPixelValue      (((uchar *)(image->data + y * image->step))[x * image->channels() +2]);
          aux.setGreenPixelValue    (((uchar *)(image->data + y * image->step))[x * image->channels() +1]);
          aux.setBluePixelValue     (((uchar *)(image->data + y * image->step))[x * image->channels() +0]);

          image2->setPixel(x, y, aux);
      }
    }
            
    return image2;
}

/**
 * Read feature vectors from CVS training dataset file
 * @return vector of feature vectors of the training dataset
 */
std::vector< std::vector<double> > SmokeBlockClassifier::readTrainData(std::string filepath)
{
    //std::string filepath = "use/train/features/training_cl_hr.csv";
        
    std::ifstream ifs(filepath.c_str());
    std::vector< std::vector<double> > vec;

    for (string line; getline(ifs, line); )
    {
        replace(line.begin(), line.end(), ',', ' ');
        std::istringstream in(line);
        vec.push_back(std::vector<double>(std::istream_iterator<double>(in), std::istream_iterator<double>()));
    }

    ifs.close();

    return vec;
}

/**
 * Read feature vectors from CVS training classes file
 * @return vector with the classes of the training dataset
 */
std::vector<int> SmokeBlockClassifier::readTrainClasses(std::string filepath)
{
    //std::string filepath = "use/train/features/training_classes.csv";
    
    ifstream ifs(filepath.c_str());
    std::vector< std::vector<int> > vec;

    for (string line; getline(ifs, line); )
    {
        replace(line.begin(), line.end(), ',', ' ');
        std::istringstream in(line);
        vec.push_back(std::vector<int>(std::istream_iterator<int>(in), std::istream_iterator<int>()));
    }

    ifs.close();
    
    std::vector<int> vec_final;
    
    for (int i = 0; i < vec.size(); i++)
    {
        vec_final.push_back(vec.at(i).at(0));
    }

    return vec_final;
}

/**
 * Extract features from input image
 * @param image Input image
 * @return feature vector extracted of the image
 */
std::vector<double> SmokeBlockClassifier::extractFeatures(Image *image)
{
    Signature signature;
    Signature signature2;
    signature = getColorLayoutFeatures(image);
    signature2 = getHaralickFeatures(image);
    
    std::vector<double> result = concatenateFeatureVectors(signature, signature2);
    /// return the resulting feature_vector, with 40 features (har + cl))
    return result;
}

/**
 * Extract Haralick features from the input image
 * @param image Input image
 * @return feature vector extracted of the image
 */
Signature SmokeBlockClassifier::getHaralickFeatures(Image *image)
{
    Signature hfv; /// Haralick feature vector
    HaralickExtractor<Signature, Image> hDescriptor;
    hDescriptor.generateSignature(*image, hfv);
    return hfv;
}

/**
 * Extract Color Layout features from the input image
 * @param image Input image
 * @return feature vector extracted of the image
 */
Signature SmokeBlockClassifier::getColorLayoutFeatures(Image *image)
{
    Signature clfv; /// Color Layout feature vector
    ColorLayoutExtractor<Signature, Image> clDescriptor;
    clDescriptor.generateSignature(*image, clfv);
    return clfv;
}

/**
 * Concatenate the two given feature vectors
 * @param fv1 First feature vector
 * @param fv2 Second feature vector
 * @return the concatenated feature vector
 */
std::vector<double> SmokeBlockClassifier::concatenateFeatureVectors(Signature fv1, Signature fv2)
{
    /// concatenate feature vectors    
    vector<double> result = fv1.getData();
    vector<double> resultcs = fv2.getData();
    result.insert(result.end(), resultcs.begin(), resultcs.end());
    
    return result;    
}
