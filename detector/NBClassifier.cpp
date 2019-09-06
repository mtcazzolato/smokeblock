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

#include "NBClassifier.hpp"

/// haralick + color layout
int NBClassifier::defaultNumberOfAttributes = 40;

/// 2 values: smoke or not_identified
int NBClassifier::defaultNumberOfClasses = 2;

/**
 * Constructor
 */
NBClassifier::NBClassifier()
{
    this->n_total = 0;
}

/**
 * Destructor
 */
NBClassifier::~NBClassifier()
{
    
}

/**
 * Train Naive Bayes classifier from the given dataset and class values
 * @param dataset Train dataset
 * @param classes Train class data
 * @return 0 if classifier was built successfully
 */
int NBClassifier::trainClassifier(std::vector< std::vector<double> > dataset, std::vector<int> classes)
{
    /// Process input data
    processInputData(dataset, classes);
    
    /// For each class, apply the iterator in the sums (one for class)
    for (std::map<int, std::vector<double> >::iterator it = sum_x.begin(); it != sum_x.end(); it++)
    {
        priors[(*it).first] = (double) n[(*it).first] / n_total;
        
        /// Compute mean for each attribute
        std::vector<double> feature_means;
        /// For each attribute
        for (int i = 0; i < (*it).second.size(); i++)
        {
            /// Adds the mean of each attribute to feature_means
            feature_means.push_back(sum_x[(*it).first][i] / n[(*it).first]);
        }
        
        /// Compute variance for each attribute
        std::vector<double> feature_variances(feature_means.size());
        /// For each feature vector of the current class
        for (int i = 0; i < data[(*it).first].size(); i++)
        {
            /// For each attribute
            for (int j = 0; j < data[(*it).first][i].size(); j++)
            {
                /// Increments the variance of each attribute
                feature_variances[j] += (data[(*it).first][i][j] - feature_means[j]) * (data[(*it).first][i][j] - feature_means[j]);
            }
        }
        
        /// After increment, finish variance computation
        for (int i = 0; i < feature_variances.size(); i++)
        {
            /// Attribute variance divided by the number of data in the class
            feature_variances[i] /= data[(*it).first].size();
        }
        
        /// Adds the computed mean for the vector of means of the current class
        means[(*it).first] = feature_means;
        /// Adds the computed variance for the vector of variances of the current class
        variances[(*it).first] = feature_variances;
    }
 
    //printf("Classifier trained.\n");
    
    return 0;
}

/**
 * Classify the given feature vector using the trained Naive Bayes classifier
 * @param fvector Feature vector of the image to be classified
 * @return Predicted class
 */
int NBClassifier::classify(std::vector<double> fvector)
{
    double probability = 0.0;
    /// Class to be predicted
    int predlabel = 0;
    double maxlikelihood = 0.0;
    double denom = 0.0;
    /// Vector of probabilities
    std::vector<double> probs;
    
    /// For each class
    for (std::map<int, double>::iterator it = priors.begin(); it != priors.end(); it++)
    {
        /// numer receives the number of data of the current class divided by the total number of data
        double numer = priors[(*it).first];
        /// For each attribute
        for (int i = 0; i < fvector.size(); i++)
        {
            numer *= (1 / sqrt(2 * M_PI * variances[(*it).first][i]) *
                    exp((-1 * (fvector[i] - means[(*it).first][i]) *
                    (fvector[i] - means[(*it).first][i])) / (2 * variances[(*it).first][i])));

        }
        
        /// If the probability of this class is bigger than the previous (if any)
        if(numer > maxlikelihood)
        {
            /// This is the maximum likelihood so far
            maxlikelihood = numer;
            /// Predicted class
            predlabel = (*it).first;            
        }
        
        /// Increments denominator
        denom += numer;
        /// Adds the probability to the vector
        probs.push_back(numer);
    }
    
    probability = maxlikelihood / denom;
    
    return predlabel; //probs.at(predlabel);
}

/**
 * Process input dataset and class values
 * @param dataset Input dataset
 * @param classes Input class values
 */
void NBClassifier::processInputData(std::vector< std::vector<double> > dataset, std::vector<int> classes)
{
    int dataset_size = dataset.size();
    
    for (int i = 0; i < dataset_size; i++)
    {
        /// Get the class value
        int label = classes.at(i);
        
        /// For each attribute
        for (int j = 0; j < dataset.at(i).size(); j++)
        {
            /// If it's the first time reading the class value, initialize it
            if (sum_x.find(label) == sum_x.end())
            {
                /// Initializes the vector with 0.0 for all attributes
                std::vector<double> empty;
                for (int k = 0; k < dataset.at(i).size(); k++)
                {
                    empty.push_back(0.0);
                }
                sum_x[label] = empty;
            }
            
            /// Increments the sum of each attribute with the corresponding values
            sum_x[label][j] += dataset.at(i).at(j);
        } /// Finished processing current line
       
        if (dataset.at(i).size() != sum_x[label].size())
        {
            printf("# inconsistent feature count! sparse data not supported yet.\n");
            exit(1);
        }
        
        /// Adds feature vector in the dataset, for the current class
        data[label].push_back(dataset.at(i));
        /// Increment counter for the current class
        n[label]++;
        /// Increments the number of feature vectors read
        n_total++;
    }/// Closes the loop of lines
    
    /// Finished processing input data
    //printf("Input data processed.\n");
}
