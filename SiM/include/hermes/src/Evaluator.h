#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP

//include dfs
#include "EuclideanDistance.h"
#include "ManhattanDistance.h"
#include "ChebyshevDistance.h"
#include "MetricHistogramDistance.h"
#include "JeffreyDivergenceDistance.h"
#include "CanberraDistance.h"
#include "KullbackLeiblerDivergenceDistance.h"
//#include "MahalanobisDistance.h"
#include "ColorLayoutDistance.h"
#include "SquaredChordDistance.h"
#include "BrayCurtisDistance.h"
#include "WarpDistance.h"
#include "QuiSquareDistance.h"
#include "SpearmanDistance.h"
#include "DTWDistance.h"
#include "MorositaDistance.h"
#include "SumProductDistance.h"


template <class FeatureVector>
class Evaluator{

private:
    int types; //qual df?

public:
    enum Distances{
        Euclidean = 1,
        CityBlock = 2,
        Chebyshev = 3,
        MHD = 4,
        Jeffrey = 5,
        Canberra = 6,
        KullbackLeibler = 7,
        Mahalanobis = 8,
        LayoutDistance = 9,
        SquaredChord = 10,
        BrayCurtis = 11,
        Warp = 12,
        QuiSquare = 13,
        Spearman = 14,
        DTW = 15,
        Morosita = 16,
        SumProduct = 17
    };


public:

    Evaluator(enum Distances distance){
        types = distance;
        // types = qual distancia
    }


    void setType(int distanceFunction){

        this->types = distanceFunction;
    }

    int getType(){

        return types;
    }

    double GetDistance(FeatureVector *obj1, FeatureVector *obj2){

        double answer;

        if (types == Euclidean){
            EuclideanDistance<FeatureVector> *d = new EuclideanDistance<FeatureVector>();
            answer = d->getDistance(*obj1, *obj2);
            delete(d);
        }
        if (types == CityBlock){
            ManhattanDistance<FeatureVector>  *d = new ManhattanDistance<FeatureVector> ();
            answer = d->getDistance(*obj1, *obj2);
            delete(d);
        }
        if (types == Chebyshev){
            ChebyshevDistance<FeatureVector>  *d = new ChebyshevDistance<FeatureVector> ();
            answer = d->getDistance(*obj1, *obj2);
            delete(d);
        }
        if (types == MHD){
            MetricHistogramDistance<FeatureVector>  *d = new MetricHistogramDistance<FeatureVector> ();
            answer = d->getDistance(*obj1, *obj2);
            delete(d);
        }
        if (types == Jeffrey){
            JeffreyDivergenceDistance<FeatureVector>  *d = new JeffreyDivergenceDistance<FeatureVector> ();
            answer = d->getDistance(*obj1, *obj2);
            delete(d);
        }
        if (types == Canberra){
            CanberraDistance<FeatureVector>  *d = new CanberraDistance<FeatureVector> ();
            answer = d->getDistance(*obj1, *obj2);
            delete(d);
        }
        if (types == KullbackLeibler){
            KullbackLeiblerDivergenceDistance<FeatureVector>  *d = new KullbackLeiblerDivergenceDistance<FeatureVector> ();
            answer = d->getDistance(*obj1, *obj2);
            delete(d);
        }
        if (types == Mahalanobis){
            //MahalanobisDistance<FeatureVector>  *d = new MahalanobisDistance<FeatureVector> ();
            //answer = d->getDistance(*obj1, *obj2);
            //delete(d);
        }
        if (types == LayoutDistance){
            ColorLayoutDistance<FeatureVector>  *d = new ColorLayoutDistance<FeatureVector> ();
            answer = d->getDistance(*obj1, *obj2);
            delete(d);
        }
        if (types == SquaredChord){
            SquaredChordDistance<FeatureVector>  *d = new SquaredChordDistance<FeatureVector> ();
            answer = d->getDistance(*obj1, *obj2);
            delete(d);
        }
        if (types == BrayCurtis){
            BrayCurtisDistance<FeatureVector>  *d = new BrayCurtisDistance<FeatureVector> ();
            answer = d->getDistance(*obj1, *obj2);
            delete(d);
        }
        if (types == Warp){
            WarpDistance<FeatureVector>  *d = new WarpDistance<FeatureVector> ();
            answer = d->getDistance(*obj1, *obj2);
            delete(d);
        }
        if (types == QuiSquare){
            QuiSquareDistance<FeatureVector>  *d = new QuiSquareDistance<FeatureVector> ();
            answer = d->getDistance(*obj1, *obj2);
            delete(d);
        }
        if (types == Spearman){
            SpearmanDistance<FeatureVector>  *d = new SpearmanDistance<FeatureVector> ();
            answer = d->getDistance(*obj1, *obj2);
            delete(d);
        }
        if (types == DTW){
            DTWDistance<FeatureVector>  *d = new DTWDistance<FeatureVector> ();
            answer = d->getDistance(*obj1, *obj2);
            delete(d);
        }
        if (types == Morosita){
            MorositaDistance<FeatureVector>  *d = new MorositaDistance<FeatureVector> ();
            answer = d->getDistance(*obj1, *obj2);
            delete(d);
        }
        if (types == SumProduct){
            SumProductDistance<FeatureVector>  *d = new SumProductDistance<FeatureVector>();
            answer = d->getDistance(*obj1, *obj2);
            delete(d);
        }


        return answer;
    }
};

#endif // EVALUATOR_HPP
