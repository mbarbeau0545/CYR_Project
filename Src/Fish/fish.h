/*********************************************************************
 * @file        fish.h
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
    // ********************************************************************
    // *                      Defines
    // ********************************************************************

    // ********************************************************************
    // *                      Types
    // ********************************************************************
    /*draw rectangle*/
    typedef struct
    {
        float axeX_f;
        float axeY_f;
        float width_f;
        float height_f;
    }t_sDesignBall;

    /*draw triangle*/
    typedef struct 
    {
        unsigned int position_x1_ui;
        unsigned int position_y1_ui;
        unsigned int position_x2_ui;
        unsigned int position_y2_ui;
        unsigned int position_x3_ui;
        unsigned int position_y3_ui;
    }t_sDesignTriangle;
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
     *	@brief  Deal with exit window for now
    *	@details
    *
    *
    *	@params[in]   None
    *	@params[out]
    *
    *  @retval RC_OK			                   @copydoc RC_OK
    *  @retval RC_ERROR_MODULE_NOT_INITIALIZED    @copydoc RC_ERROR_MODULE_NOT_INITIALIZED
    *  @retval RC_ERROR_PARAM_INVALID    @copydoc RC_ERROR_PARAM_INVALID
    */
    t_eReturnCode Fish_ProcessInput(void);
    /****************************************************************************/
    
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
    t_eReturnCode Fish_Setup(t_sDesignTriangle *f_setup_triangle_s)
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

    t_eReturnCode Fish_Update(t_sDesignBall *f_design_ball_ps);
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
   t_eReturnCode Fish_Render(t_sDesignTriangle f_setup_ball_s, SDL_Renderer *f_renderer_ps);
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
