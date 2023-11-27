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
    #define NBR_FISH 30

    /*radar fish grid*/
    #define RADAR_SCALE 2.5
    #define FISH_RADAR_SQUARE FISH_HEIGHT * RADAR_SCALE     /**<Length of the radar */
    #define NBR_ELEM_ZONE 20                                /**<nbr max of elem for one fish*/
    /*define the different radar zone*/
    #define ZONE_ATTRACTION FISH_RADAR_SQUARE                /*100*/                            /**< the fish try to get closer of another fish respecting distance*/
    #define ZONE_ALIGNMENT  FISH_RADAR_SQUARE / (2)          /*50*/                          /**< the fish adapt his direction to be colinear*/
    #define ZONE_REPULSION  FISH_RADAR_SQUARE / RADAR_SCALE  /*10*/          /**< the fish has to change his direction cause another fish is to close*/
    #define DELTA_ANGLE_ACCEPTATION 0.1                                     /*acceptation of none change dir in s_FishMvmt_Repulsion*/
    #define COEF_ALGNMT_ANGLE 0.8
    #define COEF_ATTRACT_ANGLE 0.2
    #define REPULSION_ANGLE M_PI / 4
    #define NBR_INTERACTION_MAX 6
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







