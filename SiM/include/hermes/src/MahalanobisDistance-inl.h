/**
* Constructor.
*/
template <class ObjectType>
MahalanobisDistance<ObjectType>::MahalanobisDistance(size_t dim){

    if (dim != 0){
        this->dim = dim;
        inverted_matrix2 = new matrix<double>(dim, dim);
        mean_vector.resize(dim, 0.0);
    }
}

/**
* Destructor.
*/
template <class ObjectType>
MahalanobisDistance<ObjectType>::~MahalanobisDistance(){

    if (inverted_matrix2 != NULL){
        delete (inverted_matrix2);
    }
    mean_vector.clear();
}

template <class ObjectType>
void MahalanobisDistance<ObjectType>::init(std::vector<ObjectType> &FVs) throw (std::length_error){

    double covariance_tmp, zscore_derivation;

    size_t num_FV = FVs.size();

    if (num_FV == 0) {
        return;
    }

    matrix<double> covariance_matrix(dim,dim);
    /* =====================================================================================
     * Z-score normalization
     ===================================================================================== */
    zscore norm;
    for (size_t i = 0; i < dim; i++) { // loop trought dimensions
        norm = zscore();
        for (size_t j = 0; j < num_FV; j++) { // loop trought FVs
            norm(FVs[j][i]);
        }
        /* variance with N-1 (sample variance) */
        zscore_derivation = sqrt(variance(norm) * (double)dim/((double)dim-1));
        for (size_t j = 0; j < num_FV; j++) {
            FVs[j][i] = (FVs[j][i] - mean(norm)) / zscore_derivation;
        }
    }
    /* =====================================================================================
     * Calculate covariance matrix
    ===================================================================================== */
    for (size_t l = 0; l < dim; l++) { //lines
        for (size_t c = 0; c < dim && c <= l; c++) { //columns
            covariance_XY cov;
            for (size_t j = 0; j < num_FV; j++)
                cov(FVs[j][l], covariate1 = FVs[j][c]); // loop through feature vectors
            covariance_tmp = covariance(cov) * ( ((double)num_FV + 1) / ((double)num_FV) ); // sample variance (matrix + F1 => num_FV + 1)
            covariance_matrix(l,c) = covariance_tmp; covariance_matrix(c,l) = covariance_tmp; // symmetric covariance matrix
            cout << l << " - " << c << endl;
        }
    }
    /* =====================================================================================
     * Invert covariance matrix - LU decomposition algorithm
    ===================================================================================== */
    bool inv = InvertMatrix(covariance_matrix, (*inverted_matrix2));
    if(inv == false) {
        throw  std::length_error("Cannot invert the matrix");
    }

    for (size_t i = 0; i < dim; i++) {
        localMean M;
        for (size_t j = 0; j < num_FV; j++) {
            M(FVs[j][i]);
        }
        mean_vector[i] = mean(M);
    }
}

template <class ObjectType>
double MahalanobisDistance<ObjectType>::getDistance(ObjectType &obj1)throw (std::length_error){

    /* =====================================================================================
     * Variable declarations
    ===================================================================================== */
    double result;
    std::vector<double> dif_mean(dim), tmp_vector(dim);
    /* =====================================================================================
     * Calculate differences vector
     ===================================================================================== */
    for (size_t i = 0; i < dim; i++) {
        dif_mean[i] = obj1[i] - mean_vector[i];
    }
    /* =====================================================================================
     * Mahalanobis distance
    ===================================================================================== */
    for (size_t i = 0; i < dim; i++) {
        tmp_vector[i] = 0;
        for (size_t j = 0; j < dim; j++) {
            tmp_vector[i] += dif_mean[j] * (*inverted_matrix2)(j,i);
        }
    }
    result = 0;
    for (size_t i = 0; i < dim; i++) {
        result += tmp_vector[i] * dif_mean[i];
    }
    /* =====================================================================================
     * Result
    ===================================================================================== */
    //return result;
    return sqrt(result);
}

/**
* @deprecated Use getDistance(ObjectType *obj1, ObjectType *obj2) instead.
*
* @copydoc getDistance(ObjectType *obj1, ObjectType *obj2) .
*/
template <class ObjectType>
double  MahalanobisDistance<ObjectType>::GetDistance(ObjectType &obj1, ObjectType &obj2) throw (std::length_error){

    return getDistance(obj1, obj2);
}

/**
* The implementation is based on the following papers:
* Feature Vector Selection method using mahalanobis distance for diagnostics of analog circuits based on ls-svm - Link: http://www.researchgate.net/publication/257579922_Feature_Vector_Selection_Method_Using_Mahalanobis_Distance_for_Diagnostics_of_Analog_Circuits_Based_on_LS-SVM
* Approach to fault identification for eltronic products using md - Link: http://ieeexplore.ieee.org/stamp/stamp.jsp?arnumber=5299092
*
* To make this computations both feature vectors should have the same size.
* Notice that, values of the feature vector must be non-negative.
*
* @param obj1: The first feature vector.
* @param obj2: The second feature vector.
* @throw Exception If the computation is not possible.
* @return The distance between feature vector 1 and feature vector 2.
*/
template <class ObjectType>
double  MahalanobisDistance<ObjectType>::getDistance(ObjectType &obj1, ObjectType &obj2) throw (std::length_error){

    int dimension = obj1.size(), num_FV = 2;
    double result, covariance_tmp;
    std::vector<double> dif_mean, tmp_vector(dimension);
    matrix<double> covariance_matrix(dimension,dimension), inverted_matrix(dimension,dimension);

    // Z-score normalization
    double zscore_derivation;
    zscore norm;
    for(size_t i = 0; i < dimension; i++) {
	norm = zscore();
    norm(obj1[i]);
        norm(obj2[i]);

	/* variance with N-1 (sample variance) */
	zscore_derivation = sqrt(variance(norm) * (double)dimension/((double)dimension-1));

    obj1[i] = (obj1[i] - mean(norm)) / zscore_derivation;
    obj2[i] = (obj2[i] - mean(norm)) / zscore_derivation;
    }

    // Calculate differences vector
    for (size_t i = 0; i < dimension; i++) {
        localMean M;
        M(obj1[i]);
        M(obj2[i]);
        dif_mean.push_back(obj1[i] - mean(M));
    }

    //Calculate Covariance matrix
    for (size_t l = 0; l < dimension; l++) {               //lines
        for (size_t c = 0; c < dimension && c <= l; c++) { //columns
            covariance_XY cov;
            cov(obj1[l], covariate1 = obj1[c]);
            cov(obj2[l], covariate1 = obj2[c]); // loop through feature vectors
            covariance_tmp = covariance(cov) * ( ((double) num_FV) / ((double) num_FV - 1) );     // sample variance
            covariance_matrix(l, c) = covariance_tmp; covariance_matrix(c, l) = covariance_tmp;   // symmetric covariance matrix
        }
    }

    // Invert covariance matrix - LU decomposition algorithm
    bool inv = InvertMatrix(covariance_matrix, inverted_matrix);
    if (inv == false) {
        throw std::length_error("Not invertible matrix.");
    }

    // Mahalanobis distance

    for (size_t i = 0; i < dimension; i++) {
        tmp_vector[i] = 0;
        for(size_t j = 0; j < dimension; j++) {
            tmp_vector[i] += dif_mean[j] * inverted_matrix(j,i);
        }
    }
    result = 0;
    for(size_t i = 0; i < dimension; i++) {
        result += tmp_vector[i] * dif_mean[i];
    }

    //Clears
    dif_mean.clear();
    tmp_vector.clear();
    covariance_matrix.clear();

    // Statistic support
    this->updateDistanceCount();

    //Result
    return sqrt(result);
}


/**
* The implementation is based on the following papers:
* Feature Vector Selection method using mahalanobis distance for diagnostics of analog circuits based on ls-svm - Link: http://www.researchgate.net/publication/257579922_Feature_Vector_Selection_Method_Using_Mahalanobis_Distance_for_Diagnostics_of_Analog_Circuits_Based_on_LS-SVM
* Approach to fault identification for eltronic products using md - Link: http://ieeexplore.ieee.org/stamp/stamp.jsp?arnumber=5299092
*
* @param obj1: The first feature vector.
* @param obj2: A set of feature vectors.
* @throw Exception If the computation is not possible.
* @return The distance between feature vector 1 and feature vector 2.
*/
template <class ObjectType>
double  MahalanobisDistance<ObjectType>::getDistance(ObjectType &obj1, std::vector<ObjectType> obj2) throw (std::length_error){

    // Variable declarations
    int dimension = obj1.size(), num_FV = obj2.size();
    double result, zscore_derivation, covariance_tmp;
    std::vector<double> dif_mean(dimension), tmp_vector(dimension);
    matrix<double> covariance_matrix(dimension,dimension), inverted_matrix(dimension,dimension);

    std::cout << "normalizacao" << std::endl;
    // Z-score normalization
    zscore norm;
    for(size_t i = 0; i < dimension; i++) { // loop trought dimensions
	norm = zscore();
    norm(obj1[i]);
	for(size_t j = 0; j < num_FV; j++) { // loop trought FVs
        norm(obj2[j][i]);
	}
	/* variance with N-1 (sample variance) */
	zscore_derivation = sqrt(variance(norm) * (double)dimension/((double)dimension-1));
    obj1[i] = ( (obj1[i] - mean(norm)) / zscore_derivation);
	for(size_t j = 0; j < num_FV; j++) {
        obj2[j][i] = ((obj2[j][i] - mean(norm))/ zscore_derivation);
	}
    }

    std::cout << "dif vector" << std::endl;
    // Calculate differences vector
    for (size_t i = 0; i < dimension; i++) {
        localMean M;
        M(obj1[i]);
        for (size_t j = 0; j < num_FV; j++) {
            M(obj2[j][i]);
        }
        dif_mean[i] = (obj1[i] - mean(M));
    }

    std::cout << "cov matrix" << std::endl;
    //Calculate covariance matrix
    for (size_t l = 0; l < dimension; l++) { //lines
        for (size_t c = 0; c < dimension && c <= l; c++) { //columns
            covariance_XY cov;
            cov((obj1[l]), covariate1 = obj1[c]);
            for (size_t j = 0; j < num_FV; j++)
                cov(obj2[j][l], covariate1 = (obj2[j][c])); // loop through feature vectors
            covariance_tmp = covariance(cov) * ( ((double)num_FV + 1) / ((double)num_FV) ); // sample variance (matrix + F1 => num_FV + 1)
            covariance_matrix(l,c) = covariance_tmp;
            covariance_matrix(c,l) = covariance_tmp; // symmetric covariance matrix
        }
    }

    std::cout << "inv" << std::endl;
    //Invert covariance matrix - LU decomposition algorithm
    bool inv = InvertMatrix(covariance_matrix, inverted_matrix);
    if (inv == false) {
        throw std::length_error("Not invertible matrix.");
    }

    std::cout << "distance maha" << std::endl;
    //Mahalanobis distance
    for (size_t i = 0; i < dimension; i++) {
        tmp_vector[i] = 0;
        for(int j = 0; j < dimension; j++) {
            tmp_vector[i] += dif_mean[j] * inverted_matrix(j,i);
        }
    }
    result = 0;

    for (size_t i = 0; i < dimension; i++) {
        result += tmp_vector[i] * dif_mean[i];
    }

    //Clears
    dif_mean.clear();
    tmp_vector.clear();
    covariance_matrix.clear();

    // Statistic support
    this->updateDistanceCount();

    // Result
    return sqrt(result);
}
