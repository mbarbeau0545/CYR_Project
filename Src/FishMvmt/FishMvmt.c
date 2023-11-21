/*********************************************************************
 * @file        FishMvmt.c
 * @brief       Template_BriefDescription.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      AUDMBA
 * @date        21/11/2023
 * @version     0.0
 */


// ********************************************************************
// *                      Includes
// ********************************************************************
#include "Library/ModuleLog/ModuleLog.h"
#include "Config/TypeCommon.h"
#include "Config/Constant.h"
#include "FishMvmt/FishMvmt.h"
// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************
int g_last_frame_time_ui; /*< deal with the frame */
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
static t_eReturnCode s_FishMvmt_GetMinimalDistanceFish();
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
static t_eReturnCode s_FishMvmt_GetCloserFishBankPosition();
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
static t_eReturnCode s_FishMmvt_ObstacleAvoidance();
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
static t_eReturnCode s_FishMvmt_GetBorderFish();
/*************************************************************************/
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
t_eReturnCode FishMvmt_FishMove(t_sFishMvmt_FishPosition *f_fishes_positions_ps )
{
    t_eReturnCode Ret_e = RC_OK;
    if(f_fishes_positions_ps == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        
    }
    if(Ret_e == RC_OK)
    {
        float delta_time_f;
        int actual_frame_f;
        /*Compare 32-bit SDL ticks values, and return true if `A` has passed `B`.*/
        while(SDL_TICKS_PASSED(SDL_GetTicks(), g_last_frame_time_ui + FRAME_TARGET_TIME) != true)
        {
        /*waste some time / sleep until we reach the frame target time */

        }
        /*Logic to keep a fixed timestep*/

        /******************************************************************
        *  Delta time is the amount of time elapsed since the last frame
        *  That is going to be how may pixels passed in a second
        *  it's about 0.002 s
        *******************************************************************/
        //               The current frame minus the last frame
        actual_frame_f = SDL_GetTicks();
        delta_time_f = (actual_frame_f - g_last_frame_time_ui) / (float)1000;
        g_last_frame_time_ui = SDL_GetTicks();
        f_fishes_positions_ps->positionX_f64 -= (float)70 * cos(f_fishes_positions_ps->angle_f64) * delta_time_f; /*max 70 pixels each second */
        f_fishes_positions_ps->positionY_f64 -= (float)50 * sin(f_fishes_positions_ps->angle_f64) * delta_time_f; /*max 50 pixels each second */
    }
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
static t_eReturnCode s_FishMvmt_GetBorderFish(t_sFishMvmt_FishPosition *f_fishes_position_s[])
{
    t_eReturnCode Ret_e = RC_OK;
    if(f_fishes_position_s == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }

    int LI_u64;
    for(LI_u64 = 0 ; LI_u64 < NBR_FISH ; LI_u64++)
    {
        if(    f_fishes_position_s[LI_u64]->positionX_f64 == (float)0)
        {
            f_fishes_position_s[LI_u64]->positionX_f64 = WINDOW_HEIGHT;   
        }
        else if(f_fishes_position_s[LI_u64]->positionX_f64 == (float)WINDOW_WIDTH)
        {
            f_fishes_position_s[LI_u64]->positionX_f64 == (float)0;
        }
        else if(f_fishes_position_s[LI_u64]->positionY_f64 == (float)0)
        {
            f_fishes_position_s[LI_u64]->positionY_f64 = (float)WINDOW_HEIGHT;
        }
        else if (f_fishes_position_s[LI_u64]->positionY_f64 == (float)WINDOW_HEIGHT)
        {
            f_fishes_position_s[LI_u64]->positionY_f64 = (float)0;
        }
    }

}
//************************************************************************************
// End of File
//************************************************************************************

