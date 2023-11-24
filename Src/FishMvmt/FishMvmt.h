/*********************************************************************
 * @file        FishMvmt.h
 * @brief       Template_BriefDescription.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      AUDMBA
 * @date        21/11/2023
 * @version     1.0
 */

#ifndef FISH_MOVEMENT_C_INCLUDED
#define FISH_MOVEMENT_C_INCLUDED
    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include <string.h>
    #include <math.h>
    #include <stdbool.h>
    #include "Library/ModuleLog/ModuleLog.h"
    #include "SDL2/SDL.h"
    #include "Config/TypeCommon.h"
    #include "Config/Constant.h"
    #include "FishMvmt/FishMvmt.h"
    #include "Library/LinkedList/Src/LinkedList.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************

    // ********************************************************************
    // *                      Types
    // ********************************************************************
    /*general properties of a fish */
    typedef struct
    {
        float positionX_f64;    /*<position in x axes*/
        float positionY_f64;    /*<position in y axes*/
        float angle_f64;        /*<angle of the fish direction*/
    } t_sFishMvmt_FishPosition;
    /*deal with link list */

    typedef struct
    {
        t_sFishMvmt_FishPosition *fish_position_ps;    /**< A pointor to the t_sFishMvmt_FishPosition structure*/
        void *next_elem_ps;                             /**< A pointor to the next element*/
    } t_sFishMvmt_LLfishPosRadar;
    /*to get the trhree point of the triangle aka the fish*/
    typedef struct
    {
        float axeX_f64;
        float axeY_f64;
    } t_sFishMvmt_FishPoint;

    /*argument neeeded for changing angle of a certain fish*/
    typedef struct
    {
        float distance_f64;
        float angle_f64;
    } t_sFishMvmt_BankFish;

    typedef struct
    {
        t_sFishMvmt_FishPoint *fish_position_s;
        float angle_f64;
    } t_sFishMvmt_FishRepulsion;

    typedef enum
    {
        FISH_MVMT_COUNT_ATTRACT,
        FISH_MVMT_COUNT_ALGNMT,
        FISH_MVMT_COUNT_REPULSE,

        FISH_MVMT_NBR_COUNT,
    } t_eFishMvmt_ZoneCount;
    typedef enum
    {
        FISH_MVMT_ANGLE_ALGNMT,
        FISH_MVMT_ANGLE_ATTRACT,

        FISH_MVMT_NBR_ANGLE,
    } t_eFishMvmt_ZoneAngle;

    typedef enum
    {
        FISH_MVMT_BOUNDARY_UP_X,
        FISH_MVMT_BOUNDARY_DOWN_X,
        FISH_MVMT_BOUNDARY_UP_Y,
        FISH_MVMT_BOUNDARY_DOWN_Y,

        FISH_MVMT_NBR_BOUNDARY,
    } t_eFishMvmt_Boundary;
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************

    // ********************************************************************
    // *                      Variables
    // ********************************************************************

    //****************************************************************************
    //                      Local functions - Prototypes
    //****************************************************************************

    //****************************************************************************
    //                      Public functions - Implementation
    //*****************************************************************************

     /**
     *
     *	@brief Allow all fishes to move in their envirenment
    *	@details
    *
    *
    *	@params[in] f_fishes_positions_as : positions and directions of all fishes
    *	@params[out]
    *
    *
    *
    */
    t_eReturnCode FishMvmt_FishMain(t_sFishMvmt_FishPosition f_fishes_positions_as[]);

    //********************************************************************************
    //                      Local functions - Implementation
    //********************************************************************************

#endif // FISH_MOVEMENT_C_INCLUDED
//************************************************************************************
// End of File
//************************************************************************************
