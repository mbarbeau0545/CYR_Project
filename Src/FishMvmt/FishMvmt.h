/*********************************************************************
 * @file        FishMvmt.h
 * @brief       Template_BriefDescription.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */

#ifndef FISH_MOVEMENT_C_INCLUDED
#define FISH_MOVEMENT_C_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
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
    typedef struct
    {
        float positionX_f64;    /*<position in x axes*/
        float positionY_f64;    /*<position in y axes*/
        float angle_f64;                /*<angle of the fish direction*/
    }t_sFishMvmt_FishPosition;
    typedef struct
    {
        float axeX_f64;
        float axeY_f64;
    }t_sFishMvmt_FishPoint;
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
    /**
     *
     *	@brief
    *	@details
    *
    *
    *	@params[in]
    *	@params[out]
    *
    *
    *
    */
    t_eReturnCode FishMvmt_Separation();
    /*************************************************************************/
    /**
     *
     *	@brief
    *	@details
    *
    *
    *	@params[in]
    *	@params[out]
    *
    *
    *
    */
    t_eReturnCode FishMvmt_Cohesion();
    /*************************************************************************/
    /**
     *
     *	@brief
    *	@details
    *
    *
    *	@params[in]
    *	@params[out]
    *
    *
    *
    */
    t_eReturnCode FishMvmt_Alignments();
     /**
     *
     *	@brief
    *	@details
    *
    *
    *	@params[in]
    *	@params[out]
    *
    *
    *
    */
    t_eReturnCode FishMvmt_FishMove(t_sFishMvmt_FishPosition f_fishes_positions_as[] );

    //********************************************************************************
    //                      Local functions - Implementation
    //********************************************************************************

#endif // FISH_MOVEMENT_C_INCLUDED
//************************************************************************************
// End of File
//************************************************************************************
