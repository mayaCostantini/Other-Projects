
#ifndef WARP_H
#define WARP_H 1

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>


/*!
 * \file warp.h
 * \brief Declaration of warping functions such as rotation and translation
 * \author Group D
 */

enum INTERP_METHOD{
    INTERP_NEAREST, /*!< Nearest neighbor interpolation, order 0 */
    INTERP_BILINEAR, /*!< Bilinear interpolation, order 1 */
    INTERP_BICUBIC /*!< Bicubic interpolation, order 3 */
};

/*!
    *  \brief Computes the inverse translation, that is, it returns the coordinates such that if we apply the translation on them we obtain the input coordinates
    * 
    * \param k: dest coordinate on the x axis
    * \param l: dest coordinate on the y axis
    * \param i_c: x-axis coordinates of the center of rotation
    * \param j_c: y-axis coordintaes of the center of rotation
    * \param theta: angle of rotation (going backwards)
    * \param destCoord: an array containing the original coordinates
    */
double* rotation(int k, int l, int i_c, int j_c, const double theta, double* destCoord); 


/*!
    *  \brief Computes the inverse translation, that is, it returns the coordinates such that if we apply the translation on them we obtain the input coordinates
    * 
    * \param k: dest coordinate on the x axis
    * \param l: dest coordinate on the y axis
    * \param delta_X: translation on the x axis (going backwards)
    * \param delta_Y: translation on the y axis (going backwards)
    * \param destCoord: an array containing the original coordinates
    */
double* translation(int k, int l, const double delta_X, const double delta_Y, double* destCoord);

/*!
    *  \brief Coefficient function for bicubic interpolation
    *
    * \param t : t such that c0(t) is returned
    */
double c0(double t);

/*!
    *  \brief Coefficient function for bicubic interpolation
    *
    * \param t : t such that c1(t) is returned
    */
double c1(double t);

/*!
    *  \brief Coefficient function for bicubic interpolation
    *
    * \param t : t such that c2(t) is returned
    */
double c2(double t);

/*!
    *  \brief Coefficient function for bicubic interpolation
    *
    * \param t : t such that c3(t) is returned
    */
double c3(double t);

#endif