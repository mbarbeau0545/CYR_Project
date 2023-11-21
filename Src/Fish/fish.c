/*********************************************************************
 * @file        fish.c
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
#include "Library/ModuleLog/ModuleLog.h"
#include "Config/TypeCommon.h"
#include "fish.h"
// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************
int g_last_frame_time_ui; /*< deal with the frame */

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

//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/******************
* Fish_Render
******************/
t_eReturnCode Fish_Render(t_sDesignBall f_setup_ball_s, SDL_Renderer *f_renderer_ps)
{
    t_eReturnCode Ret_e = RC_OK;
    if(f_renderer_ps == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        SDL_SetRenderDrawColor(f_renderer_ps, 0, 0, 0, 255);
        SDL_RenderClear(f_renderer_ps);
        //Here is where we can start drawing our game obkect
        //draw rectangle
        SDL_Rect ball_rect_s = {f_setup_ball_s.axeX_f,
                                f_setup_ball_s.axeY_f,
                                f_setup_ball_s.height_f,
                                f_setup_ball_s.width_f};
        SDL_SetRenderDrawColor(f_renderer_ps, 255, 255, 255, 255);
        SDL_RenderFillRect(f_renderer_ps, &ball_rect_s);
        //Swap buffer
        SDL_RenderPresent(f_renderer_ps);
    }
    return Ret_e;

}
/*******************
* Main_Setup
*******************/
t_eReturnCode Fish_Setup(t_sDesignBall *f_setup_ball_s)
{
    t_eReturnCode Ret_e = RC_OK;
    if(f_setup_ball_s == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ModLog_WriteErrorInFile("In Main_Setup, param invalid");
    }
    else if(Ret_e == RC_OK)
    {
        f_setup_ball_s->axeX_f = 20;
        f_setup_ball_s->axeY_f = 20;
        f_setup_ball_s->height_f = 15;
        f_setup_ball_s->width_f = 15;
        //ModLog_WriteInfoInFile("THe ball is initialize");
    }
    return Ret_e;
}
/*****************
* Main_Update
******************/
t_eReturnCode Fish_Update(t_sDesignBall *f_design_ball_ps)
{
    t_eReturnCode Ret_e = RC_OK;
    float delta_time_f;
    int actual_frame_f;
    if(f_design_ball_ps == NULL)
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
        f_design_ball_ps->axeX_f += (float)70 * delta_time_f; /*70 pixels each second */
        f_design_ball_ps->axeY_f += (float)50 * delta_time_f; /*50 pixels each second */
    }
    return Ret_e;

}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************

//************************************************************************************
// End of File
//************************************************************************************

