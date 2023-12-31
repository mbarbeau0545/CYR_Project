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
#include "fishDsgn.h"
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

static t_eReturnCode s_FishDsgn_GetFishPoint(t_sFishMvmt_FishPosition f_positions_fishes_s,    /*the sommet of the triangle*/
                                    t_sFishMvmt_FishPoint *f_fish_point_left_ps,       /*the left point*/
                                    t_sFishMvmt_FishPoint *f_fish_point_right_ps,      /*the right point*/
                                    float f_angle_f64                            );    /*Angle in radian between axeX and AxeY for the direction*/
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
static t_eReturnCode s_FishDsgn_GetFishPoint(t_sFishMvmt_FishPosition  f_positions_fishes_s,    /*the sommet of the triangle*/
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
* FishDsgn_Render
******************/
t_eReturnCode FishDsgn_Render(t_sFishMvmt_FishPosition f_positions_fishes_as[], SDL_Renderer *f_renderer_ps)
{
    t_eReturnCode Ret_e = RC_OK;
    unsigned int LI_u64;
    t_sFishMvmt_FishPoint left_side_fish_s;
    t_sFishMvmt_FishPoint right_side_fish_s;

    if (f_renderer_ps == NULL || f_positions_fishes_as == NULL)
    {
        return RC_ERROR_PARAM_INVALID;
    }

    // Effacement du rendu une seule fois avant la boucle
    SDL_SetRenderDrawColor(f_renderer_ps, 0, 0, 0, 255);
    SDL_RenderClear(f_renderer_ps);

    for (LI_u64 = 0; LI_u64 < NBR_FISH; LI_u64++)
    {
        s_FishDsgn_GetFishPoint(f_positions_fishes_as[LI_u64], &left_side_fish_s, &right_side_fish_s, f_positions_fishes_as[LI_u64].angle_f64);

        // Dessiner le poisson
        SDL_SetRenderDrawColor(f_renderer_ps, 255, 0, 0, 255);
        SDL_RenderDrawLineF(f_renderer_ps, f_positions_fishes_as[LI_u64].positionX_f64, f_positions_fishes_as[LI_u64].positionY_f64,
                            left_side_fish_s.axeX_f64, left_side_fish_s.axeY_f64);
        SDL_RenderDrawLineF(f_renderer_ps, f_positions_fishes_as[LI_u64].positionX_f64, f_positions_fishes_as[LI_u64].positionY_f64,
                            right_side_fish_s.axeX_f64, right_side_fish_s.axeY_f64);
        SDL_RenderDrawLineF(f_renderer_ps, right_side_fish_s.axeX_f64, right_side_fish_s.axeY_f64,
                            left_side_fish_s.axeX_f64, left_side_fish_s.axeY_f64);
    }
    // Mise à jour du rendu une seule fois après avoir dessiné tous les poissons
    SDL_RenderPresent(f_renderer_ps);

    return Ret_e;
}

/*******************
* FishDsgn_Setup
*******************/
t_eReturnCode FishDsgn_Setup(t_sFishMvmt_FishPosition f_positions_fishes_as[])
{
    t_eReturnCode Ret_e = RC_OK;
    unsigned int LI_u64;
    if(f_positions_fishes_as == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ModLog_WriteErrorInFile("In FishDsgn_Setup, param invalid");
    }
    else if(Ret_e == RC_OK)
    {
        for(LI_u64 =  0 ; LI_u64 < NBR_FISH ; LI_u64++)
        {
            f_positions_fishes_as[LI_u64].positionX_f64 = rand() % WINDOW_WIDTH;
            f_positions_fishes_as[LI_u64].positionY_f64 = rand() % WINDOW_HEIGHT;
            /* Nombre aléatoire entre 0 et 2 * PI */
            f_positions_fishes_as[LI_u64].angle_f64 = (float)rand() / (float)RAND_MAX * (2 * M_PI) + 0.1;

        }
    }
    return Ret_e;
}
/*****************
* FishDsgn_Update
******************/
t_eReturnCode FishDsgn_Update(t_sFishMvmt_FishPosition f_positions_fishes_as[])
{
    t_eReturnCode Ret_e = RC_OK;
    if(f_positions_fishes_as == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        FishMvmt_FishMain(f_positions_fishes_as);
    }
    return Ret_e;

}

//************************************************************************************
// End of File
//************************************************************************************

