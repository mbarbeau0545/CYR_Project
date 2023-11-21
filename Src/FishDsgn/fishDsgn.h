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
    #include "Config/TypeCommon.h"
    #include "SDL2/SDL.h"
    #include "Config/Constant.h"
    #include "../FishMvmt/FishMvmt.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************

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
    t_eReturnCode Fish_Setup(t_sFishMvmt_FishPosition *f_setup_triangle_s);
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

    t_eReturnCode Fish_Update(t_sFishMvmt_FishPosition f_positions_fishes_ps[]);
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
   t_eReturnCode Fish_Render(t_sFishMvmt_FishPosition f_setup_ball_s, SDL_Renderer *f_renderer_ps);
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