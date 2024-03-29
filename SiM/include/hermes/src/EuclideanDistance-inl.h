/**
* Constructor.
*/
template <class ObjectType>
EuclideanDistance<ObjectType>::EuclideanDistance(){
}

/**
* Destructor.
*/
template <class ObjectType>
EuclideanDistance<ObjectType>::~EuclideanDistance(){
}

/**
* @deprecated Use getDistance(ObjectType &obj1, ObjectType &obj2) instead.
*
* @copydoc getDistance(ObjectType &obj1, ObjectType &obj2) .
*/
template <class ObjectType>
double EuclideanDistance<ObjectType>::GetDistance(ObjectType &obj1, ObjectType &obj2) throw (std::length_error){

    return getDistance(obj1, obj2);
}

/**
* Calculates the Euclidean distance between two feature vectors.
* This calculus is based on the math form sqrt((feature_1[i] - feature_2[i])^2).
* To make this computations both feature vectors should have the same size().
*
* @param obj1: The first feature vector.
* @param obj2: The second feature vector.
* @throw Exception If the computation is not possible.
* @return The Euclidean distance between feature vector 1 and feature vector 2.
*/
template <class ObjectType>
double EuclideanDistance<ObjectType>::getDistance(ObjectType &obj1, ObjectType &obj2) throw (std::length_error){

    if (obj1.size() != obj2.size()){
        throw std::length_error("The feature vectors do not have the same size.");
    }

    double d = 0;
    double tmp;

    for (size_t i = 0; i < obj1.size(); i++){
        tmp = obj1[i] - obj2[i];
        d = d + (tmp * tmp);
    }

    // Statistic support
    this->updateDistanceCount();

    return sqrt(d);
}
