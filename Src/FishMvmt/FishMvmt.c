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
#include "FishMvmt.h"
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
static t_eReturnCode s_FishMvmt_GetCloserFishPosition();
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
static t_eReturnCode s_FishMvmt_GetBankFishPositions();
/*************************************************************************/
/**
 *
 *	@brief   Avoid fish to touch another fish
*	@details Knowing the exzct position of the different fish around the fish
*            we lookin' at due to ---------------.\n
*            We adjust the position of the fish
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
 *	@brief Replace fish who are in the limits of the screen
*	@details Knowing the position of the fish due to f_fishes_position_s,
*            We check if the position of the fish is superior than limits.\n
*            If it's the case, we change the position.\n
*
*
*	@params[in] f_fishes_position_ps : position of the fish.
*	@params[in] f_is_border_touch_pb : say if the fish touch a border.
*	@params[out]
*
*  @retval RC_OK			                   @copydoc RC_OK
*  @retval RC_ERROR_MODULE_NOT_INITIALIZED    @copydoc RC_ERROR_MODULE_NOT_INITIALIZED
*/
static t_eReturnCode s_FishMvmt_BorderFish(t_sFishMvmt_FishPosition *f_fishes_position_ps, bool *f_is_border_touch_pb);
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
t_eReturnCode FishMvmt_FishMove(t_sFishMvmt_FishPosition f_fishes_positions_as[])
{
    t_eReturnCode Ret_e = RC_OK;
    bool is_border_touch_b;
    int LI_u64;
    float delta_time_f;
    int actual_frame_f;
    if(f_fishes_positions_as == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ModLog_WriteInfoInFile("In FishMvmt_FishMove param invalid");

    }
    if(Ret_e == RC_OK)
    {
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
        for(LI_u64 = 0 ; LI_u64 < NBR_FISH ; LI_u64++)
        {
            Ret_e = s_FishMvmt_BorderFish(&f_fishes_positions_as[LI_u64], &is_border_touch_b);
            if(Ret_e == RC_OK)
            {
                if(is_border_touch_b != true)
                {
                    //vitesse d'avancement et direction
                    f_fishes_positions_as[LI_u64].positionX_f64 -= (float)70 * cos(f_fishes_positions_as[LI_u64].angle_f64) * delta_time_f; /*max 70 pixels each second */
                    f_fishes_positions_as[LI_u64].positionY_f64 -= (float)70 * sin(f_fishes_positions_as[LI_u64].angle_f64) * delta_time_f; /*max 70 pixels each second */
                }
            }

        }
    }
    return Ret_e;
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
/***************************
* s_FishMvmt_GetBorderFish
***************************/
static t_eReturnCode s_FishMvmt_BorderFish(t_sFishMvmt_FishPosition *f_fishes_position_ps, bool *f_is_border_touch_pb)
{
    t_eReturnCode Ret_e = RC_OK;
    if(f_fishes_position_ps == NULL || f_is_border_touch_pb == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ModLog_WriteInfoInFile("In s_FishMvmt_BorderFish param invalid");
    }
    //put f_is_border_touch_b to false if it's not equal true
    *f_is_border_touch_pb = false;
    if(f_fishes_position_ps->positionX_f64 < (float)0)
    {
        f_fishes_position_ps->positionX_f64 = (float)WINDOW_WIDTH;
        *f_is_border_touch_pb = true;
    }
    else if(f_fishes_position_ps->positionX_f64 > (float)WINDOW_WIDTH)
    {
        f_fishes_position_ps->positionX_f64 = (float)0;
        *f_is_border_touch_pb = true;
    }
    else if(f_fishes_position_ps->positionY_f64 < (float)0)
    {
        f_fishes_position_ps->positionY_f64 = (float)WINDOW_HEIGHT;
        *f_is_border_touch_pb = true;
    }
    else if (f_fishes_position_ps->positionY_f64 > (float)WINDOW_HEIGHT)
    {
        f_fishes_position_ps->positionY_f64 = (float)0;
        *f_is_border_touch_pb = true;
    }
    return Ret_e;
}
/************************************
* s_FishMvmt_GetCloserFishPosition
************************************/
t_eReturnCode FishMvmt_Separation(t_sFishMvmt_FishPosition *f_fishes_position_ps, t_sLinkedList *f_linkedlist_ps)
{
    t_eReturnCode Ret_e = RC_OK;
    int boundary_up_x = 0;
    int boundary_down_x = 0;
    int boundary_up_y = 0;
    int boundary_down_x = 0;
    if(f_fishes_position_ps == NULL || f_linkedlist_ps == NULL )
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ModLog_WriteInfoInFile("In FishMvmnt_Separation param invalid");
    }
    if(Ret_e == RC_OK)
    {
        /*determine the radar fish*/

    }
}
//************************************************************************************
// End of File
//************************************************************************************

