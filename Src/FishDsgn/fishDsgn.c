/*********************************************************************
 * @file        fishDsgn.c
 * @brief       Manage the fish design in the game.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      AUDMBA
 * @date        20/11/2023
 * @version     1.0
 */
// ********************************************************************
// *                      Includes
// ********************************************************************
#include <math.h>
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
int g_last_frame_time_ui; /*< deal with the frame */
t_sFishMvmt_FishPosition g_fihes_position_s[NBR_FISH];

// ********************************************************************
// *                      Constants
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
 *	@brief Get the other fish point
*	@details We have the sommet of the triangle, we need to determine where are
*            the other point due to  t_sFishMvmt_FishPoint *f_positions_fishes_s
*            annd put it in f_fish_point_left_ps, f_fish_point_right_ps
*
*
*	@params[in]   f_design_ball_ps : pointor to the t_sDesignBall structure to save fish data
*	@params[out]
*
*  @retval RC_OK			                   @copydoc RC_OK
*  @retval RC_ERROR_MODULE_NOT_INITIALIZED    @copydoc RC_ERROR_MODULE_NOT_INITIALIZED
*/

static t_eReturnCode s_GetFishPoint(t_sFishMvmt_FishPosition  f_positions_fishes_s,    /*the sommet of the triangle*/
                                    t_sFishMvmt_FishPoint *f_fish_point_left_ps,        /*the left point*/
                                    t_sFishMvmt_FishPoint *f_fish_point_right_ps,      /*the right point*/
                                    float f_angle_f64                            );    /*Angle in radian between axeX and AxeY for the direction*/
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
static t_eReturnCode s_GetFishPoint(t_sFishMvmt_FishPosition  f_positions_fishes_s,    /*the sommet of the triangle*/
                                    t_sFishMvmt_FishPoint *f_fish_point_left_ps,       /*the left point*/
                                    t_sFishMvmt_FishPoint *f_fish_point_right_ps,      /*the right point*/
                                    float f_angle_f64                            )     /*Angle in radian between axeX and AxeY for the direction*/
{
    t_eReturnCode Ret_e = RC_OK;
    float projection_b_64;
    float projection_c_64;
    float projection_bb_64;
    float projection_cc_64;
    float x_base_64;
    float y_base_64;
    if(f_fish_point_left_ps == NULL || f_fish_point_right_ps == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ModLog_WriteInfoInFile("In FishDsgn param invalid");
    }
    if(Ret_e == RC_OK)
    {
        /*determine some stuff only in function of f_angle_f64, FISH_WIDTH, FISH_HEIGHT*/
        projection_c_64 = FISH_HEIGHT * cos(f_angle_f64);
        projection_b_64 = FISH_HEIGHT * sin(f_angle_f64);
        x_base_64 = f_positions_fishes_s.positionX_f64 + projection_c_64;
        y_base_64 = f_positions_fishes_s.positionY_f64 + projection_b_64;
        projection_bb_64 = (FISH_WIDTH / 2) * sin(M_PI/2 - f_angle_f64);
        projection_cc_64 = (FISH_WIDTH / 2) * cos(M_PI/2 - f_angle_f64);
        /*now we talking */
        /*left side*/
        f_fish_point_left_ps->axeX_f64 = x_base_64 - projection_cc_64;
        f_fish_point_left_ps->axeY_f64 = y_base_64 + projection_bb_64;
        /*right side*/
        f_fish_point_right_ps->axeX_f64 = x_base_64 + projection_cc_64;
        f_fish_point_right_ps->axeY_f64 = y_base_64 - projection_bb_64;
    }
    return Ret_e;
}
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/******************
* Fish_Render
******************/
t_eReturnCode Fish_Render(t_sFishMvmt_FishPosition f_positions_fishes_s, SDL_Renderer *f_renderer_ps)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sFishMvmt_FishPoint left_side_fish_s;
    t_sFishMvmt_FishPoint right_side_fish_s;
    if(f_renderer_ps == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        s_GetFishPoint(f_positions_fishes_s, &left_side_fish_s, &right_side_fish_s, f_positions_fishes_s.angle_f64);
        //erase the last window
        SDL_SetRenderDrawColor(f_renderer_ps, 0, 0, 0, 255);
        SDL_RenderClear(f_renderer_ps);
        //Here is where we can start drawing our game obkect
        //draw rectangle
        /*SDL_Rect ball_rect_s = {f_setup_ball_s.axeX_f,
                                f_setup_ball_s.axeY_f,
                                f_setup_ball_s.height_f,
                                f_setup_ball_s.width_f};
        SDL_SetRenderDrawColor(f_renderer_ps, 255, 255, 255, 255);
        SDL_RenderFillRect(f_renderer_ps, &ball_rect_s);*/
        //Swap buffer

        /*draw birds in window*/
        SDL_SetRenderDrawColor(f_renderer_ps, 255, 0, 0, 255);
        SDL_RenderDrawLineF(f_renderer_ps, f_positions_fishes_s.positionX_f64 , f_positions_fishes_s.positionY_f64,
                                           left_side_fish_s.axeX_f64          ,left_side_fish_s.axeY_f64);
        SDL_RenderDrawLineF(f_renderer_ps, f_positions_fishes_s.positionX_f64 , f_positions_fishes_s.positionY_f64,
                                           right_side_fish_s.axeX_f64         ,right_side_fish_s.axeY_f64);
        SDL_RenderDrawLineF(f_renderer_ps, right_side_fish_s.axeX_f64          , right_side_fish_s.axeY_f64,
                                           left_side_fish_s.axeX_f64          ,left_side_fish_s.axeY_f64);
        //use for rectangle
        //SDL_SetRenderDrawColor(f_renderer_ps, 255, 255, 255, 255);
        SDL_RenderPresent(f_renderer_ps);
    }
    return Ret_e;

}
/*******************
* Main_Setup
*******************/
t_eReturnCode Fish_Setup(t_sFishMvmt_FishPosition *f_positions_fishes_s)
{
    t_eReturnCode Ret_e = RC_OK;
    if(f_positions_fishes_s == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ModLog_WriteErrorInFile("In Main_Setup, param invalid");
    }
    else if(Ret_e == RC_OK)
    {
        f_positions_fishes_s->positionX_f64 = (int)400;
        f_positions_fishes_s->positionY_f64 = (int)300;
        f_positions_fishes_s->angle_f64 = (float)  M_PI / 8;

        //ModLog_WriteInfoInFile("THe ball is initialize");
    }
    return Ret_e;
}
/*****************
* Main_Update
******************/
t_eReturnCode Fish_Update(t_sFishMvmt_FishPosition *f_positions_fishes_s)
{
    t_eReturnCode Ret_e = RC_OK;
    float delta_time_f;
    int actual_frame_f;
    if(f_positions_fishes_s == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
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
        f_positions_fishes_s->positionX_f64 -= (float)70 * cos(f_positions_fishes_s->angle_f64) * delta_time_f; /*max 70 pixels each second */
        f_positions_fishes_s->positionY_f64 -= (float)50 * sin(f_positions_fishes_s->angle_f64) * delta_time_f; /*max 50 pixels each second */
    }
    return Ret_e;

}

//************************************************************************************
// End of File
//************************************************************************************

