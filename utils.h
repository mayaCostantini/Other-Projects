#ifndef UTILS_H
#define UTILS_H 1

#include <iostream>


/*!
 * \file utils.h
 * \brief Declaration of useful fonctions for other parts
 * \author Group D
 */

enum COEFFICIENT_TYPE: int{
    FUNCTION_1, /*!< 1/(1+x^k)*/
    FUNCTION_2, /*!< (1+x)^(-x)*/
    EXPONENTIAL_DECREASING /*!< Deacreasing exponential function e^(-x^(k)) */
};

/*!
    *  \brief We work with a lot of 2 dimensionnal arrays. This function free this kind of array of any type T

    *
    *  \param data : 2 dimensionnal array to be freed
    *  \param height: the length of the first dimension 
    */
template <class T>
void free_2Darray(T** data, int height){
    for (int i = 0; i < height; i++){
        delete[] data[i];
    }
    delete[] data;
}


/*!
    *  \brief We work with a lot of 2 dimensionnal arrays. This function deep copies this kind of array to a new one that is returned.

    *
    *  \param data : 2 dimensionnal array to be freed
    *  \param height: the length of the first dimension 
    *  \param width : the length of the second dimension
    */
template <class T>
T** copy_2Darray(T** data, int height, int width){
    T** copiedArray = new T*[height];

    for (int i = 0; i < height; i++){
        copiedArray[i] = new T[width];
        for (int j = 0; j < width; j++){
            copiedArray[i][j] = data[i][j];
        }
    }
    return copiedArray;
}



/*!
    *  \brief A bunch of functions with value 1 at 0 and decreasing as x grows.

    *
    *  \param functionType: a COEFFICIENT_TYPE to be chosen. It determines the function to be actually used
    *  \param x: the parameter such that the returned value is c(x)
    *  \param k: a parameter tuning the function.
    */
double Coefficients(COEFFICIENT_TYPE functionType, double x, float k);



/*!
    *  \brief Computes the barycenter of a fingerprint
    *   The barycenter of a fingerprint is computed as a weighted mean of its values. 
    *
    *  \param data: the double dimensionnal array on which to compute the barycenter
    *  \param width: the width of the image
    *  \param height: the height of the image
    *  \param retW: an integer that will be modified to become the coordinate of the barycenter along the x axis
    *  \param retH: an integer that will be modified to become the coordinate of the barycenter along the y axis
    */
void barycenter(double** data, int width, int height, int& retW, int& retH);

class Image; //forward declaration

/*!
    *  \brief Computes the barycenter of a fingerprint
    *   The barycenter of a fingerprint is computed as a weighted mean of its values. 
    *
    *  \param im: Image object on which to compute the barycenter
    *  \param retW: an integer that will be modified to become the coordinate of the barycenter along the x axis
    *  \param retH: an integer that will be modified to become the coordinate of the barycenter along the y axis
    */
void barycenter(const Image& im, int& retW, int& retH); 

/*!
    *  \brief generate coordinates to plotted, using translation and the loss_function
    *
    *  \param pathPicOriginal: path to the original picture
    *  \param pathDataOutput: path to the output file containing the coordinates 
    *  \param labelX: label to the x axis
    *  \param labelY: label to the y axis
    *  \param orderSubPix: order of the size matrix considered as a pixel, to compute the loss functions
    */
int loss_generator_translation(const std::string pathPicOriginal, 
                                std::string pathDataOutput, 
                                std::string labelX, 
                                std::string labelY, 
                                int orderSubPix);

/*!
    *  \brief generate coordinates to plotted, using rotation and the loss_function
    *
    *  \param pathPicOriginal: path to the original picture
    *  \param pathDataOutput: path to the output file containing the coordinates 
    *  \param labelX: label to the x axis
    *  \param labelY: label to the y axis
    *  \param orderSubPix: order of the size matrix considered as a pixel, to compute the loss functions
    */
int loss_generator_rot(const std::string pathPicOriginal, 
                                std::string pathDataOutput, 
                                std::string labelX, 
                                std::string labelY, 
                                int orderSubPix);

/*!
    *  \brief generate coordinates to plotted, using rotation and the loss_function
    *
    *  \param pathPicOriginal: path to the original picture
    *  \param pathDataOutput: path to the output file containing the coordinates 
    *  \param labelX: label to the x axis
    *  \param labelY: label to the y axis
    *  \param orderSubPix: order of the size matrix considered as a pixel, to compute the correlation rate
    */
int correlation_generator_rot(const std::string pathPicOriginal, 
                                std::string pathDataOutput, 
                                std::string labelX, 
                                std::string labelY, 
                                int orderSubPix);

/*!
    *  \brief greedy algorithm to find the local minimum:  
    *  \param myImage: image target and image original (both)  
    *  \param p0: 
    *  \param opti_rate: speed rate of convergence (a kind of learning rate) 
    *  \param is_loss: boolean : 1 means that the loss function is used 
    */
double opti_greedy(Image& myImage, double p0, double opti_rate, int is_loss);
/* naive optimization to finde p* (here p_x*)
 is_loss == 1 iff the function used is a loss function
 is_loss == 0 iff the function used is a correlation rate */ 


/* Not finished */
/*!
    *  \brief gradient descent algorithm to compute the global minimum of the objective function  
    *  \param p:
    *  \param imageTarget: image targeted by the initial image
    *  \param imageInitial: image targeting the target image 
    *  \param ethaTrans: learning rate for translation (along x and y)
    *  \param ethaRot: learning rate for rotation (theta)
    *  \param hTrans: step for x, y to compute the 1 order partial derivative
    *  \param hTheta: step for theta to compute the 1 order partial derivative
    */
double* gradient_descent(double* p, const Image &imageTarget, const Image &imageInitial, double ethaTrans, double ethaRot, double hTrans, double hTheta);

#endif