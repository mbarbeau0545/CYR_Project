/*********************************************************************
 * @file        fishDsgn.h
 * @brief       Manage the fish design in the game.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */

#ifndef FISH_C_INCLUDED
#define FISH_C_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include <math.h>
    #include <time.h>
    #include "Library/ModuleLog/ModuleLog.h"
    #include "Config/TypeCommon.h"
    #include "fishDsgn.h"
    #include "../FishMvmt/FishMvmt.h"
    #include "Config/Constant.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************

    // ********************************************************************
    // *                      Types
    // ********************************************************************
    typedef enum
    {
        pt_sommet,  /**<sommet of triangle*/
        pt_left,    /**<left side triangle*/
        pt_right,   /**<right side triangle*/
        /*number of point*/
        nbr_point,
    }t_eFishDsgn_triangle;
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************

    // ********************************************************************
    // *                      Variables
    // ********************************************************************

    //********************************************************************************
    //                      Local functions - Prototypes
    //********************************************************************************


    /**
     *
     *	@brief  Initialize the fish dimension and position
    *	@details
    *
    *
    *	@params[in]   f_design_ball_ps : pointor to the t_sDesignBall structure to save fish data
    *	@params[out]
    *
    *  @retval RC_OK			                   @copydoc RC_OK
    *  @retval RC_ERROR_MODULE_NOT_INITIALIZED    @copydoc RC_ERROR_MODULE_NOT_INITIALIZED
    */
    t_eReturnCode FishDsgn_Setup(t_sFishMvmt_FishPosition f_positions_fishes_as[]);
    /****************************************************************************/
    /**
     *
     *	@brief  Initialize Window for the game
    *	@details
    *
    *
    *	@params[in]   f_design_ball_ps : pointor to the t_sDesignBall structure to save fish data
    *	@params[out]
    *
    *  @retval RC_OK			                   @copydoc RC_OK
    *  @retval RC_ERROR_MODULE_NOT_INITIALIZED    @copydoc RC_ERROR_MODULE_NOT_INITIALIZED
    */

    t_eReturnCode FishDsgn_Update(t_sFishMvmt_FishPosition f_positions_fishes_ps[]);
    /****************************************************************************/
    /**
     *
     *	@brief  upload the fish on the window
    *	@details
    *
    *
    *	@params[in]   f_design_ball_s :  t_sDesignBall structure to save fish data
    *	@params[out]
    *
    *  @retval RC_OK			                   @copydoc RC_OK
    *  @retval RC_ERROR_MODULE_NOT_INITIALIZED    @copydoc RC_ERROR_MODULE_NOT_INITIALIZED
    */
    t_eReturnCode FishDsgn_Render(t_sFishMvmt_FishPosition f_positions_fishes_as[], SDL_Renderer *f_renderer_ps);
    //****************************************************************************
    //                      Public functions - Implementation
    //********************************************************************************

    //********************************************************************************
    //                      Local functions - Implementation
    //********************************************************************************
#endif // ITEM_C_INCLUDED
//************************************************************************************
// End of File
//************************************************************************************

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
