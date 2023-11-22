/*********************************************************************
 * @file        Constant.h
 * @brief       This file repertory all constant needed.\n
 * @details
 *
 * @author      AUDMBA
 * @date        20/11/2023
 * @version     0.0
 */

#ifndef CONSTANT_H_INCLUDED
#define CONSTANT_H_INCLUDED




    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "Config/TypeCommon.h"

    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    /*setup  windows*/
    #define WINDOW_WIDTH 800
    #define WINDOW_HEIGHT 600

    /*boolean*/
    #define false 0
    #define true 1

    /*speed and fps stuff frame*/
    #define FPS 30 /*< 30 images per second */
    #define FRAME_TARGET_TIME (1000 / FPS) /*< number of frame per second */

    /*Width and Height of triangle representing the fish*/
    #define FISH_WIDTH 10
    #define FISH_HEIGHT 10
    #define NBR_FISH 100

    /*radar fish grid*/
    #define FISH_RADAR_HEIGHT = 50;     /**< Height of the radar */
    #define FISH_RADAR_WIDTH = 50;      /**< Height of the radar */

    /*vision field for fish radar to know where are the other fish*/
    #define GRID_X WINDOW_WIDTH / ((WINDOW_WIDTH / 100) * 2 ) /**<equals 50 no matter what*/
    #define GRID_Y WINDOW_HEIGHT / ((WINDOW_HEIGHT / 100) * 2 ) /**<equals 50 no matter what*/
    // ********************************************************************
    // *                      Types
    // ********************************************************************

    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************

    // ********************************************************************
    // *                      Variables
    // ********************************************************************

    //********************************************************************************
    //                      Local functions - Prototypes
    //********************************************************************************

        //****************************************************************************
    //                      Public functions - Implementation
    //********************************************************************************

    //********************************************************************************
    //                      Local functions - Implementation
    //********************************************************************************


#endif // CONSTANT_H_INCLUDED
//************************************************************************************
// End of File
//************************************************************************************







