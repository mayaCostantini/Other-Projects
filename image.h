#ifndef IMAGE_H
#define IMAGE_H 1

/*! \mainpage Digital Analysis of Fingerprints - Group D - MSIAM 2019/2020
 *   This project was realized by the MSIAM 2019/2020 - Group D composed of Grégoire Lambert, Maya Costantini, Roman Edward Zacharek, Matthias Lotta and Diana Farhat
 * during the January modelling project.
 * 
 *  The main goal of the project was to reproduce artifacts that would appear on data corresponding to fingerprints. These modifications 
 *  can be of various sorts. For instance we implemented rotations, symmetries, translations, approximations of dry and moist
 *  , of an effect of weak pressure and more ! We used openCV 4.2 for image manipulation.
 *  
 * This project was also a lot about managing a group of 5 during a month in C++.
 * 
 * You will find on this repository : 
 * 
 * README.md : It contains a lot of informations on how to setup your computer for the project.
 * 
 * test: contains the test files (which are more like demo files) of each subpart that we implemented. 
 * 
 * src: source code, definition of our functions.
 * 
 * include: headers
 * 
 * documentation: config files for building the documentation
 * 
 * data: is separated in two subfolders (mainly). 'original' contains the original data on which we worked. You need to import it from somewhere else. 'result' will contain the output data.
 * 
 * msiam_m1_project.pdf : contains the original subject for this project.
 * 
 *
 */


/*!
 * \file image.h
 * \brief Declaration of the main class for managing pictures
 * \author Group D
 */

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

#include "morpho_filter.h"
#include "warp.h"
#include "utils.h"

enum SYM_TYPE : int{
    SYM_NONE, /*!< No symmetry applied */
    SYM_X, /*!< Symmetry along the x-axis */
    SYM_Y,  /*!< Symmetry along the y-axis */
    SYM_DIAG1, /*!< Symmetry along the top-left bottom-right diagonal*/
    SYM_DIAG2 /*!< Symmtry along the top-right bottom-left diagonal */
};

enum MF_TYPE : int{
    MF_NONE,      /*!< No morphological operation applied */
    MF_EROSION,    /*!< Applies erosion */
    MF_DILATION,    /*!< Applies dilation */
    MF_OPENING,    /*!< Applies opening */
    MF_CLOSING    /*!< Applies closing */
};

enum FUNCTION_MODE: int {
    HORIZONTAL,  /*!< Applies the rain effect horizontally */
    VERTICAL, /*!< Applies the rain effect vertically  */
    DIAGONAL /*!< Applies the rain effect diagonnally */
};



class Image
{
      /*! \class Image
   * \brief Class storing a picture. The methods correspond to the operations that can be applied on Image instances. The data is stored in a 2D-array as doubles in the [0, 1] range. OpenCV Mat object is used for loading, displaying and saving. 
   *
   */
    private:
    int imageWidth, imageHeight;        /*!< Picture dimensions */
    double **imageData;     /*!< pixel data of dimension [height][width] : gray scale between 0 and 1 (1 = white) */
    std::string pathToImage;

    public:
    /*!
     *  \brief Constructor from path
     *
     *  Constructor of the class Image
     *
     *  \param fullPath : path to the file '.png' to be loaded
     */
    Image(std::string fullPath); 

    /*!
     *  \brief Constructor from array of double
     *
     *  Constructor of the class Image
     *  Initialize the object from  2D array of double describing the image
     *  No copy is made of the 2D array. Modifying it results in modifying the Image object
     *
     *  \param data : 2D array to store the pixel data
     *  \param width : width of the picture
     *  \param height : height of the picture
     */
    Image(double** data, int width, int height);  

    /*!
     *  \brief Constructor from array of boolean
     *
     *  Constructor of the class Image
     *  Initialize the object from  2D array of boolean describing the image
     *  The input array is deleted
     *
     *  \param data : pointer of pointer to store pixels white/black (bools). Deleted by the constructor
     *  \param width : width of the picture
     *  \param height : height of the picture
     */
    Image(bool** data, int width, int height);

    /*!
     *  \brief Copy constructor
     *
     *  (deep) Copy constructor of the class Image
     *  \param other : image to be copied
     */
    Image(const Image& other);

    /*!
     *  \brief Destructor
     * 
     *  Destructor of the class Image
     */
    ~Image();
    
    /* *************************
                Getters
       ************************* */
    /*!
     *  \brief width getter
     */
    int getWidth() const; // Returns the image's width
    /*!
     *  \brief height getter
     */
    int getHeight() const; // Returns the image's height
    /*!
     *  \brief empty ?
     * Returns whether the image is empty or not
     */
    bool empty() const; 

    /*!
     *  \brief return the path to the image
     * 
     */
    std::string getPath() const;
    /* *************************
              Overloading
       ************************* */
    /*!
     *  \brief copy assignement
     *
     *  \param other : the Image assigned 
     */
    Image& operator=(const Image& other);

    
     /*!
     *  \brief () overloading for accessing pixel values.
     * 
     * Returns the pixel at coordinate x, y
     *
     *  \param height : coordinate y
     *  \param width : coordinate x  
     */
    double operator()(int height,int width) const; // Returns the pixel at coordinate x, y

    /*!
     *  \brief add pixels
     * 
     * Add two images termwise, returned values cannot exceed one
     * 
     *  \param other : 2nd Image to compute the addition with  
     */
    Image operator+(const Image& other) const;

        /*!
     *  \brief subsctract pixels
     * 
     * Subsctract two images termwise, returned values cannot be lower than 0
     * 
     *  \param other : 2nd Image to compute the susctract with  
     */
    Image operator-(const Image& other) const; 


    /* *************************
        Input/Ouput operations
       ************************* */
        /*!
     *  \brief Convert Image to Mat openCV object
     * 
     * Create a Mat object which corresponds to the image
     */
    cv::Mat toMat() const;

    /*!
     *  \brief show on shell
     * 
     * Displays the original image and waits for any key to be pressed
     * 
     * \param windowName : name of the window used to display  
     */
    void display(cv::String windowName = " ") const;

    /*!
     *  \brief prints raw data
     * 
     * Print the matrix of the image as it is stored in memory
     * 
     * \param o : ostream where to print   
     */
    void displayData(std::ostream& o) const;

    
    /*!
     *  \brief saves the Image at the given path
     * 
     * Saves the Image.
     * 
     * \param fullPath : path where to save the picture   
     */
    void save(std::string fullPath) const;


     /*!
     *  \brief reverts the image to the original picture, thus erases all of the modifcations 
     *  To be used only if the image was created from a path 
     */
    void revert();


    /* *************************
        Pixel manipulation
       ************************* */
    /*!
     *  \brief Creating rectangles in Picture
     * 
     * Fills a rectangle at given coordinates (top left, bottom right)
     * 
     * \param xA : absc top left 
     * \param yA : ordo top left 
     * \param xB : absc bottom right  
     * \param yB : ordo bottom right 
     * \param intensity : intensity in [0, 1] filling the rectangle
     */
    void rectangleFill(int xA, int yA, int xB, int yB, double intensity = 1.); 


    /* Symmetry functions */
        /*!
     *  \brief Symmetry regarding axis
     * 
     * Compute the symmetrical of the image with respect to the given axis
     * 
     * \param axis : SYM_TYPE which defines on which axis the symmetry is to be applied
     */
    Image symmetry(SYM_TYPE axis = SYM_NONE) const; 

    
    /* *************************
        Morphological filters
       ************************* */
    /*!
     *  \brief morphological Filters
     * 
     * Binarizes the Image and returns a filtered version of the it
     * 
     * \param type : MF_TYPE which defines the type of morphological operation to use 
     * \param selem : StructuringElement to be used for the operations 
     */
    Image morphologicalFilterBin(MF_TYPE type, StructuringElement& selem);


    /*!
     *  \brief morphological Filter
     * 
     * Returns a filtered version of the Image
     * 
     * \param type : MF_TYPE which defines the type of morphological operation to use 
     * \param selem : StructuringElement to be used for the operations 
     */
    Image morphologicalFilterGrayscale(MF_TYPE type, StructuringElement& selem);


    /*!
     *  \brief morphological Filter centered. Support erosion and dilation.
     * 
     * Determines the barycenter of the grayscale image, typically a fingerprint, and applies erosion
     * or dilation differently as the pixels are farther from the barycenter.
     * Erosion is stronger the farther away you get from the barycenter.
     * Dilation is stronger close to the middle.
     * 
     * \param type : MF_TYPE which defines the type of morphological operation to use. Support erosion and dilation only.
     * \param selemType : Shape of structuring element to use. 
     * \param flat : Whether or not to use flat structuring elements
     */
    Image morphologicalFilterGrayscaleCentered(MF_TYPE type, SELEM_SHAPE selemType, bool flat = true);


    /* Interpolation functions defined in src/warp.cpp */
    /*!
     *  \brief Interpolate the coordinates of the input (floating) pixel with a nearest neighbour interpolation
     * 
     * \param x : x-axis coordinate of the pixel to interpolate
     * \param y : y-axis coordinate of the pixel to interpolate
     * \param default_intensity : default intensity to fill the created gaps with. Default to -1. Negative values are ignored in later computations, for instance MSE.
     * 
     */
    double pix_interpol0(double x, double y, double default_intensity = -1) const;// given the reals (x, y), return the intensity of the pixel in [0, 1] using interpolation of order 0. By default white

    /*!
     *  \brief Interpolate the coordinates of the input (floating) pixel with a bilinear interpolation
     * 
     * \param x : x-axis coordinate of the pixel to interpolate
     * \param y : y-axis coordinate of the pixel to interpolate
     * \param default_intensity : default intensity to fill the created gaps with. Default to -1. Negative values are ignored in later computations, for instance MSE.
     * 
     */
    double pix_interpol1(double x, double y, double default_intensity = -1) const; // given the reals (x, y), return the intensity of the pixel in [0, 1] using interpolation of order 1. By default white

    /*!
     *  \brief Interpolate the coordinates of the input (floating) pixel with a bicubic interpolation
     * 
     * \param x : x-axis coordinate of the pixel to interpolate
     * \param y : y-axis coordinate of the pixel to interpolate
     * \param default_intensity : default intensity to fill the created gaps with. Default to -1. Negative values are ignored in later computations, for instance MSE.
     * 
     */
    double pix_interpol3(double x, double y, double default_intensity = -1) const; // given the reals (x, y), return the intensity of the pixel in [0, 1] using interpolation of order 3. By default white


    /* Rotation functions */
    /*!
     *  \brief Rotate the Image by a given angle.
     * Inverse mapping method
     * 
     * \param theta : angle of rotation
     * \param i_c : x-axis' coordinate around which to perform rotation
     * \param j_c : y-axis' coordinate around which to perform rotation
     * \param method : interpolation method to use. Default to INTERP_BILINEAR
     * \param default_intensity : default intensity to fill the created gaps with. Default to -1. Negative values are ignored in later computations, for instance MSE.
     * 
     */
    Image rotation_interpol(double theta, int i_c, int j_c, INTERP_METHOD method = INTERP_BILINEAR, double default_intensity = -1) const; 


    /* Translation function */
    /*!
     *  \brief Translates the Image by a given angle.
     * 
     * \param delta_X : translation along the x-axis in pixels
     * \param delta_Y : translation along the y-axis in pixels
     * \param method : interpolation method to use. Default to INTERP_BILINEAR. 
     * \param default_intensity : default intensity to fill the created gaps with. Default to -1. Negative values are ignored in later computations, for instance MSE.
     * 
     */
    Image translation_interpol(double delta_X, double delta_Y, INTERP_METHOD method = INTERP_BILINEAR, double default_intensity = -1) const;

    /* cost fonctions & correlations */
    /*!
     *  \brief Computes the mean squared error between two images.
     * Are only counted the pixels for which the two Images have positive values at a given location, i.e. if one of 
     * the two pixel values is negative, the two pixels are ignored.
     * 
     * \param other: other image with which the distance is computed.
     * \param order_sub_pix: Gap between pixels, if one wants to gain in efficiency, but loose in precision. Default to 1, i.e. all pixels are considered.
     * 
     */
    double meanSquaredError(const Image& other, int order_sub_pix) const;

    /*!
     *  \brief Computes the correlation rate between two images
     * 
     * Are only counted the pixels for which the two Images have positive values at a given location, i.e. if one of 
     * the two pixel values is negative, the two pixels are ignored.
     * 
     * \param other: other image with which the rate is computed.
     * \param order_sub_pix: Gap between pixels, if one wants to gain in efficiency, but loose in precision. Default to 1, i.e. all pixels are considered.
     * 
     */
    double correlationRate(const Image& other, int order_sub_pix) const;

    
    /*!
     *  \brief Keeps a chosen surface on the image intact and the outside of it lowers the intensity of pixels.
     *
     *  The surface can be a circle of an ellipse of any size, it can be rotated by any angle, and the borders can be randomized.
     *
     *  \param xCenter : the x coordinate of the center of the surface
     *  \param yCenter : the y coordinate of the center of the surface
     *  \param xRadius : the horizontal radius of the surface
     *  \param yRadius : the vertival radius of the surface
     *  \param coeffType: one of the functions
     *  \param angle: the angle of rotation in degrees
     *  \param k : paramater for some of the functions
     *  \param randomized: boolean, if true then the borders of the surface are randomized, otherwise they borders stay intact.
     */
    void imageFilling(int xCenter, int yCenter, int xRadius, int yRadius, COEFFICIENT_TYPE coeffType, float angle, float k, bool randomized = false);
    

    /*!
    *   \brief Simulates a small deformation of the fingerprint that ressembles a swirl
    * 
    * \param swirlCenterX: the x coordinate of the center of the swirl
    * \param swirlCenterY: the y coordinate of the center of the swirl
    * \param swirlRadius: the length of the radius 
    * \param swirlTwists: the strength of the swirl
    */
    void swirlImage(float swirlCenterX, float swirlCenterY, float swirlRadius, float swirlTwists);



    /*!
    *   \brief Simulates small deformations on a fingerprint, inside of a given square.
    * 
    * \param mode: can be either HORIZONTAL, VERTICAL or DIAGONAL
    * \param topLeftPixelX: coordinate of the top left x coordinate of the square in which to apply the effect
    * \param topLeftPixelY: coordinate of the top left y coordinate of the square in which to apply the effect
    * \param squareLength: the size of the square in which to apply the effect
    */
    void rainEffect(FUNCTION_MODE mode, int topLeftPixelX, int topLeftPixelY, int squareLength);

};

#endif
