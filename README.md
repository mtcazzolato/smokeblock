# The SmokeBlock Approach

Implementation of the work published in AMC SAC 2016:  

## Method, Input and Output
The SmokeBlock approach works in the following way. Given an input image:  
- Extract superpixel regions;  
- Classify each region using a trained Naive Bayes classifier;  
- Segment image with all regions classified as smoke;  
- Classify the segmented image using a trained global Naive Bayes classifier.  

As result, the algorithm provides:  
- A set of coordinate points, representing MBRs;  
- The mean color of all pixels classified as smoke in a MBR;  
- The "what" tag, informing 1 if image was classified as smoke, and 0 if the image was classified as non-smoke;  
- The segmented image, containing only regions classifies as smoke.  

Naive Bayes training (for superpixels):  
- The Naive Bayes classifier is trained using a dataset of feature vectors, extracted from smoke and non-smoke regions;  
- All regions are superpixels, manually classified as smoke and non-smoke.  

Naive Bayes training (for the global segmented image):  
- The Naive Bayes classifier is trained using a dataset of feature vectors, extracted from smoke and non-smoke segmented images;  

## How to use
In order to successfully work, there must be a directory "use" in the same directory of the executable file, with:  
- "use/train/features/" directory, containing the training files "training_classes.csv", "training_cl_hr.csv", "training_global_cl_hr.csv" and "training_global_classes.csv".  

There is a sample of how to use in "main.cpp" source file.  

There is also a Makefile in the main directory.  

## Last Update
Updated version: 27.05.2016  
- Added global classification using Naive Bayes;  
- Improved training features from global images (segmented);  
- Improved training features from superpixels;  
- Cleaning unused files.  

## Contact Information

In case of any interest on collaborations or for further information, please contact us through the following emails:  
- Mirela Cazzolato: mtcazzolato@gmail.com  
- Agma Juci Machado Traina: agma@icmc.usp.br    

## License and Citation Request

SmokeBlock is available for researches and data scientists under the GNU General Public License. In case of publication and/or public use of the available sources, as well as any resource derived from it, one should acknowledge its creators by citing the following paper.  

> CAZZOLATO, M. T.; BEDO, M. V. N. ; COSTA, A. F. ; SOUZA, J. A. ; TRAINA JR, C. ; RODRIGUES JR, J. F. ; TRAINA, A. J. M.  . **Unveiling smoke in social images with the SmokeBlock approach**. In: 31st ACM Symposium on Applied Computing, Pisa, Itália. Proceedings of the 31st ACM Symposium on Applied Computing, 2016. DOI: 10.1145/2851613.2851634. p. 49-54.  

Bibtex entry:  
```
@inproceedings{CazzolatoEtAl2016,
    author    = {Mirela T. Cazzolato and
                Marcos Vinicius Naves Bedo and
                Alceu Ferraz Costa and
                J{\'{e}}ssica Andressa de Souza and
                Caetano Traina Jr. and
                Jos{\'{e}} Fernando Rodrigues Jr. and
                Agma J. M. Traina},
    title     = {Unveiling smoke in social images with the SmokeBlock approach},
    booktitle = {Proceedings of the 31st Annual {ACM} Symposium on Applied Computing,
                Pisa, Italy, April 4-8, 2016},
    pages     = {49--54},
    year      = {2016},
    url       = {https://doi.org/10.1145/2851613.2851634},
    doi       = {10.1145/2851613.2851634},
}
```

## FiSmo Dataset

The dataset reported in [Cazzolato et al., 2016] is available online, in this [link](https://github.com/mtcazzolato/dsw2017).  
