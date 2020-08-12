
#ifndef MORPHO_FILTER_H
#define MORPHO_FILTER_H 1


/*!
 * \file morpho_filter.h
 * \brief Tools for morphological filtering, such as StructuringElement or morphological methods.
 * \author Group D
 */


#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "image.h"

enum SELEM_SHAPE: int {
    SELEM_CROSS,  /*!< Cross structuring element */
    SELEM_CIRCLE, /*!< Circle structuring element */
    SELEM_DIAMOND, /*!< Diamond structuring element */
    SELEM_SQUARE /*!< Square structuring element */
};

class Pixel{
      /*! \class Pixel
   * \brief Pixel class for StructuringElement. It remembers the relative coordinates corresponding to one point of the neighbourhood of the associated StructuringElement
   *
   */
    private:
    int row, col; // coordinates of the pixel
    double value; // value of the pixel (used mostly with non flat structuring elements)
    public:
    /*!
     *  \brief Constructor
     *
     *
     *  \param y : y coordinate of the Pixel
     *  \param x : x coordinate of the Pixel
     *  \param val : value of the Pixel. Used for non flat StructuringElements. Default to 1.
     */
    Pixel(int y, int x, double val = 1);

    /*!
     *  \brief Getter for the y coordinate.
     */
    int getRow(); 

    /*!
     *  \brief Getter for the x coordinate.
     */
    int getCol(); 

    /*!
     *  \brief Getter for the value of the Pixel
     */
    double getVal(); 

    /*!
     *  \brief Set the y and x coordinates of the Pixel.
     * 
     *  \param y : y coordinate of the Pixel
     *  \param x : x coordinate of the Pixel
     * 
     */
    void setRowCol(int y, int x); 

};

class StructuringElement{
      /*! \class StructuringElement
   * \brief The StructuringElement defines the neighbourhood on which to apply morphological operations for each Pixels. 
   * It is basically a shape and can be conveniently set to be a square, circle, diamond or a cross. 
   * It can be flat (binary) or non-flat (non-binary). 
   * We store in a vector the relatives coordinates of the pixels on which to computes the operations. 
   *
   */
    private:
    std::vector<Pixel> shape; // useful to iterate over the relevant pixels of the shape
    int width, height; // width and height associated to the shape
    int anchorWidth, anchorHeight; // center of the shape


    public:
    /*!
     *  \brief Constructor from an array of boolean. Constructs a flat StructuringElement.
     * 
     * \param selem: array of booleans defining the StructuringElement.
     * \param w: width of the given array.
     * \param h: height of the given array.
     * \param aw: center of the shape with respect to the x-axis.
     * \param ah: center of the shape with respect to the y-axis.
     */
    StructuringElement(bool** selem, int w, int h, int aw, int ah); 

    /*!
     *  \brief Constructor from an array of doubles. Constructs a non-flat StructuringElement.
     * 
     * \param selem: array of doubles defining the StructuringElement.
     * \param w: width of the given array.
     * \param h: height of the given array.
     * \param aw: center of the shape with respect to the x-axis.
     * \param ah: center of the shape with respect to the y-axis.
     */
    StructuringElement(double** selem, int w, int h, int aw, int ah);

    /*!
     *  \brief Constructor from a general shape. The StructuringElement can either be flat or non-flat.
     * 
     *  \param generalShape: describe the shape of the StructuringElement, default to "cross". 
     *  \param size: The size should be rather seen as a category. The StructuringElement created will always be of odd width and height. Thus its final height = final width = 2 * size + 1. The center is the canonical one.
     *  \param flat: Whether or not the resulting StructuringElement is flat. For non-flat StructuringElement , the value is linearly descreasing from the center (1) to the sides (0).
     */
    StructuringElement(SELEM_SHAPE generalShape = SELEM_CROSS, int size = 1, bool flat = true); 

    /*!
     *  \brief Copy constructor.
     * 
     */
    StructuringElement(const StructuringElement& other); 

    /*!
     *  \brief returns false if the structuring element is included in the binarized data
     * The boolean values are inverted because a dilation of the black parts corresponds to an erosion of the white parts
     * 
     * \param data: 2 dimensionnal array describing an image
     * \param dataWidth: width of data
     * \param dataHeight: height of data
     * \param row: row of the pixel on which the operation needs to be applied
     * \param col: col of the pixel on which the operation needs to be applied
     * 
     */
    bool include(bool** data, int dataWidth, int dataHeight, int row, int col); 

    /*!
     *  \brief returns false if the structuring element is hits in the binarized data
     * The boolean values are inverted because a dilation of the black parts corresponds to an erosion of the white parts
     * 
     * 
     * \param data: 2 dimensionnal array describing an image
     * \param dataWidth: width of data
     * \param dataHeight: height of data
     * \param row: row of the pixel on which the operation needs to be applied
     * \param col: col of the pixel on which the operation needs to be applied
     * 
     */
    bool hit(bool** data, int dataWidth, int dataHeight, int row, int col); 

    /*!
     *  \brief returns the minimum value of the data withing the neighbourhood defined by the StructuringElement.
     * 
     * 
     * \param data: 2 dimensionnal array describing an image
     * \param dataWidth: width of data
     * \param dataHeight: height of data
     * \param row: row of the pixel on which the operation needs to be applied
     * \param col: col of the pixel on which the operation needs to be applied
     * 
     */
    double min(double** data, int dataWidth, int dataHeight, int row, int col); 

    /*!
     *  \brief returns the maximum value of the data withing the neighbourhood defined by the StructuringElement.
     * 
     * 
     * \param data: 2 dimensionnal array describing an image
     * \param dataWidth: width of data
     * \param dataHeight: height of data
     * \param row: row of the pixel on which the operation needs to be applied
     * \param col: col of the pixel on which the operation needs to be applied
     * 
     * 
     */
    double max(double** data, int dataWidth, int dataHeight, int row, int col); 

    /*!
     *  \brief Stores the StructuringElement as a PGM file at the given path for visualization. 
     * 
     * \param path: The path where to store the created PGM file.
     */
    void toPGM(std::string path);
};


/*!
    *  \brief determines an optimal threshold with Otsu's method for binarization of an grayscale image.
    * 
    * 
     * \param data: 2 dimensionnal array describing an image
     * \param width: width of data
     * \param height: height of data
    * 
    */
double determineThreshold(double** data, int width, int height); 


/*!
    *  \brief binarizes the data according to an optimal (Otsu's) threshold
    * 
    * 
     * \param data: 2 dimensionnal array describing an image
     * \param width: width of data
     * \param height: height of data
    * 
    */
bool** binarizeData(double** data, int width, int height); 


/*!
    *  \brief Erosion of a binarized data
    * 
    * 
     * \param data: 2 dimensionnal array describing an image
     * \param width: width of data
     * \param height: height of data
     * \param selem: A StructuringElement which defines the size of the neighbourhoods on which erosion is applied. Non-flat structuring elements are considered flat.
    * 
    */
bool** erosion(bool** data, int width, int height, StructuringElement& selem); 


/*!
    *  \brief Dilation of a binarized data
    * 
     * \param data: 2 dimensionnal array describing an image
     * \param width: width of data
     * \param height: height of data
     * \param selem: A StructuringElement which defines the size of the neighbourhoods on which dilation is applied. Non-flat structuring elements are considered flat.
    * 
    */
bool** dilation(bool** data, int width, int height, StructuringElement& selem); 


/*!
    *  \brief Grayscale erosion
    * 
     * \param data: 2 dimensionnal array describing an image
     * \param width: width of data
     * \param height: height of data
     * \param selem: A StructuringElement which defines the size of the neighbourhoods on which erosion is applied. Works with both flat and non-flat structuring elements
    * 
    */
double** erosion(double** data, int width, int height, StructuringElement& selem);



/*!
    *  \brief Grayscale dilation
    * 
     * \param data: 2 dimensionnal array describing an image
     * \param width: width of data
     * \param height: height of data
     * \param selem: A StructuringElement which defines the size of the neighbourhoods on which dilation is applied. Works with both flat and non-flat structuring elements
    * 
    */
double** dilation(double** data, int width, int height, StructuringElement& selem);



#endif