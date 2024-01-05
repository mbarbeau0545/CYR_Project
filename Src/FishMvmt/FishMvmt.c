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
#include <pthread.h>

// ********************************************************************
// *                      Defines
// ********************************************************************
#define MAX_THREADS 5
#define FISH_BY_THREADS NBR_FISH / MAX_THREADS
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
*	@brief   In repulsion zone the fish is too close of fihes around and has to move in csq.\n
*	@details After calculating the distance between f_fish_position_ps and the f_group_fish_ps.\n
*            We calculate an angle to avoid percution
*
*
*	@params[in] f_fish_position_ps : a pointor to the fish we lookin' at
*	@params[in] f_size_array_u64 :fish whom is too close
*	@params[in] f_angle_repulsion_f64 :number of element in repulsion zone
*	@params[out]
*
*  @retval RC_OK			                     @copydoc RC_OK
*  @retval RC_ERROR_PARAM_INVALID                @copydoc RC_ERROR_PARAM_INVALID
*/
static t_eReturnCode s_FishMvmt_Repulsion(t_sFishMvmt_FishParameters   f_fish_position_s,
                                          float *f_angle_repulsion_f64,
                                          unsigned int f_size_array_u64 );
/*************************************************************************/
/**
*
*	@brief   In alignment zone, the fish has to have a colinear direction to the group
*	@details We calculate the average direction of the group due to f_group_fish_ps and
*            This is the new direction of f_fish_position_ps
*
*	@params[in] f_fish_s         : all fishes around
*	@params[in] f_angle_alignment_f64  : angle due to alignment zone
*	@params[in] f_nbr_elem_alignmt_u64       : number of element in algmnt zone
*	@params[out]
*
*  @retval RC_OK			                     @copydoc RC_OK
*  @retval RC_ERROR_PARAM_INVALID                @copydoc RC_ERROR_PARAM_INVALID
*/
static t_eReturnCode s_FishMvmt_Alignment(t_sFishMvmt_FishParameters f_fish_s,
                                          unsigned int f_nbr_elem_alignmt_u64,
                                          float *f_angle_alignment_f64);
/*************************************************************************/

/**
*
*  	@brief     In Attraction zone, the fish is attracted by the center of mass
*	@details   If a fish has no group he has to adopt a group
*
*
*	@params[in] f_fish_s        : a pointor to the fish we lookin' at
*	@params[in] f_angle_attract_f64     : return angle alignment
*	@params[in] f_count_fish_attract_u64  : number of fish in attract zone
*	@params[in] f_count_fish_alignmt_u64  : number of fish in alignment zone
*	@params[out]
*
*  @retval RC_OK			                     @copydoc RC_OK
*  @retval RC_ERROR_PARAM_INVALID                @copydoc RC_ERROR_PARAM_INVALID
*/
static t_eReturnCode s_FishMvmt_Attraction( t_sFishMvmt_FishParameters f_fish_s,
                                            unsigned int f_count_fish_attract_u64,
                                            unsigned int f_count_fish_alignmt_u64,
                                            float *f_angle_attract_f64);
/*************************************************************************/
/**
*
*	@brief  Calculate the value of the angle of each fishes
*	@details Due to f_fish_position_pas, we genarate different circles around each fish.\n
*           - zone repulsion : the fish is too close of fihes around and has to move in csq.\n
*           - zone alignment : the fish is going where the group around him is going.\n
*           - zone attraction : the fish is going to one the center of mass.\n
*
*
*	@params[in] f_fish_position_pas : array of fishes positions
*	@params[in] f_speed_fish_f64    : the speed for each pieces
*	@params[out]
*
*  @retval RC_OK			                     @copydoc RC_OK
*  @retval RC_ERROR_PARAM_INVALID                @copydoc RC_ERROR_PARAM_INVALID
*/
t_eReturnCode s_FishMvmt_MovingFishes(t_sFishMvmt_FishParameters f_positions_fishes_as[]);
/*************************************************************************/
/**
 *
 *	@brief   Know where are the center of position group
*	@details
*
*
*	@params[in]
*	@params[out]
*
*  @retval RC_OK			                     @copydoc RC_OK
*  @retval RC_ERROR_PARAM_INVALID                @copydoc RC_ERROR_PARAM_INVALID
*/
//static t_eReturnCode s_FishMvmt_GetBankFishPositions();
/*************************************************************************/
/**
 *
 *	@brief   Calculater distance betwwen two point
*	@details
*
*
*	@params[in] f_return_value_f64 : to put the result
*	@params[in] f_fish_positionA_ps: Point A
*	@params[in]f_fish_positionB_ps : Point B
*	@params[out]
*
*  @retval RC_OK			                     @copydoc RC_OK
*  @retval RC_ERROR_PARAM_INVALID                @copydoc RC_ERROR_PARAM_INVALID
*/
static t_eReturnCode s_FishMvmt_CalculateDistance(float *f_return_value_f64,
                                                  t_sFishMvmt_FishParameters f_fish_positionA_ps,
                                                  t_sFishMvmt_FishParameters f_fish_positionB_ps);

/*************************************************************************/
/**
 *
 *	@brief   Replace fish who are in the limits of the screen
*	@details Knowing the position of the fish due to f_fishes_position_s,
*            We check if the position of the fish is superior than limits.\n
*            If it's the case, we change the position.\n
*
*
*	@params[in] f_fishes_position_ps : position of the fish.
*	@params[in] f_is_border_touch_pb : return booleen if the fish touch a border.
*	@params[out]
*
*  @retval RC_OK			                     @copydoc RC_OK
*  @retval RC_ERROR_PARAM_INVALID                @copydoc RC_ERROR_PARAM_INVALID
*/
static t_eReturnCode s_FishMvmt_BorderFish(t_sFishMvmt_FishParameters *f_fishes_position_ps, bool *f_is_border_touch_pb);
/*************************************************************************/
/**
 *
 *	@brief   Calcul Distances between the considerer fish and other in the Grid
*	@details The considerer fish f_fish_position_s and it's collegue f_linkedlist_ps are on the grid,
*            this function determine the distance between them
*
*
*	@params[in] f_fish_position_s : the consider fish position
*	@params[in] f_group_fish_s    : group of fish in the grid
*	@params[in] f_count_zone_uai  : an array with the dimension of each zone
*	@params[out]
*
*  @retval RC_OK			                     @copydoc RC_OK
*  @retval RC_ERROR_PARAM_INVALID                @copydoc RC_ERROR_PARAM_INVALID
*/
static t_eReturnCode s_FishMvmt_GetInFoRadar(t_sFishMvmt_FishParameters f_fish_position_s,
                                             t_sFishMvmt_FishParameters f_group_fish_s,
                                             unsigned int f_count_zone_uai[]);
/*************************************************************************/
/**
 *
 *	@brief   Sort the Array in decroissant way
*	@details
*
*
*	@params[in] f_distance_af : the consider array
*	@params[in] f_size_array_u64 :size of array
*	@params[out]
*
*  @retval RC_OK			                     @copydoc RC_OK
*  @retval RC_ERROR_PARAM_INVALID                @copydoc RC_ERROR_PARAM_INVALID
*/
//static t_eReturnCode s_FishMvmt_SortDecroissantArray(float f_array_af[], unsigned int f_size_array_u64);
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
t_eReturnCode FishMvmt_FishMain(t_sFishMvmt_FishParameters f_fishes_positions_as[])
{
    t_eReturnCode Ret_e = RC_OK;
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
        if(Ret_e == RC_OK)
        {
            Ret_e = s_FishMvmt_MovingFishes(f_fishes_positions_as);
        }
        if(Ret_e != RC_OK)
        {
            ModLog_WriteErrorInFile("In FishMvmt_FishMain, s_FishMvmt_MovingFishes failed");
        }
    }
    return Ret_e;
}
t_eReturnCode s_FishMvmt_MovingFishes(t_sFishMvmt_FishParameters f_fish_position_pas[])
{

    ModLog_WriteInfoInFile("We enter in s_FishMvmt_MovingFishes");
    t_eReturnCode Ret_e = RC_OK;
   
    bool is_border_touch_b;
    int LI_u64;
    int LI2_u64;
    float angle_f64;
     float delta_time_f;
    float fish_velocity_f64;
    int actual_frame_f;
    float angle_zone_af[FISH_MVMT_NBR_ANGLE];
    unsigned int count_zone_af[FISH_MVMT_NBR_COUNT];
    int boundary_grid_aui[FISH_MVMT_NBR_BOUNDARY];
    if(f_fish_position_pas == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ModLog_WriteInfoInFile("In FishMvmnt_Separation param invalid");
    }
    if(Ret_e == RC_OK)
    {
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
        fish_velocity_f64 = (float) FISH_SPEED * delta_time_f;
        /*do for each fish*/
        for(LI_u64 = 0 ; LI_u64 < FISH_BY_THREADS ; LI_u64++)
        {
           
            Ret_e = s_FishMvmt_BorderFish(&f_fish_position_pas[LI_u64], &is_border_touch_b);
            /*if fish not touch a border*/
            if(is_border_touch_b != true && Ret_e == RC_OK)
            {
                //do allocation for the array
                if(Ret_e == RC_OK)
                {
                    /*initialize final angle to 0*/
                    angle_f64 = 0;
                    /*initialize all array to 0*/
                    memset(angle_zone_af, (float)0,   sizeof(angle_zone_af));
                    memset(count_zone_af, (float)0,   sizeof(count_zone_af));
                    memset(boundary_grid_aui, (float)0,sizeof(boundary_grid_aui));
                    memset(f_fish_position_pas->bank_alignmt_fishes_ps, (float)0,sizeof(t_sFishMvmt_BankFish));
                    memset(f_fish_position_pas->bank_attract_fishes_ps, (float)0, sizeof(t_sFishMvmt_BankFish));
                    memset(f_fish_position_pas->bank_repulse_fishes_ps, (float)0, sizeof(t_sFishMvmt_FishPosition));
                    boundary_grid_aui[FISH_MVMT_BOUNDARY_UP_X]    = f_fish_position_pas[LI_u64].positionX_f64 + (float)FISH_RADAR_SQUARE;
                    boundary_grid_aui[FISH_MVMT_BOUNDARY_DOWN_X]  = f_fish_position_pas[LI_u64].positionX_f64 - (float)FISH_RADAR_SQUARE;
                    boundary_grid_aui[FISH_MVMT_BOUNDARY_UP_Y]    = f_fish_position_pas[LI_u64].positionY_f64 + (float)FISH_RADAR_SQUARE;
                    boundary_grid_aui[FISH_MVMT_BOUNDARY_DOWN_Y]  = f_fish_position_pas[LI_u64].positionY_f64 +-  (float)FISH_RADAR_SQUARE;
                    /*find the other fishes in the grid we just determine and pull it in linkedlist*/
                    for(LI2_u64 = 0 ; LI2_u64 < NBR_FISH ; LI2_u64++)
                    {
                        /*see if the x-axes and y-axes  corresponding*/
                        if( LI2_u64 != LI_u64
                        &&f_fish_position_pas[LI2_u64].positionX_f64 <= boundary_grid_aui[FISH_MVMT_BOUNDARY_UP_X]
                        &&f_fish_position_pas[LI2_u64].positionX_f64 >= boundary_grid_aui[FISH_MVMT_BOUNDARY_DOWN_X]
                        &&f_fish_position_pas[LI2_u64].positionY_f64 <= boundary_grid_aui[FISH_MVMT_BOUNDARY_UP_Y]
                        &&f_fish_position_pas[LI2_u64].positionY_f64 >= boundary_grid_aui[FISH_MVMT_BOUNDARY_DOWN_Y])
                        {
                            /*put it in the right linklist add at the end */
                            Ret_e = s_FishMvmt_GetInFoRadar(f_fish_position_pas[LI_u64],
                                                            f_fish_position_pas[LI2_u64],
                                                            count_zone_af);

                            /*Write error msg if adding element in linked list doesn't work*/
                            if(Ret_e != RC_OK)
                            {
                                ModLog_WriteErrorInFile("In s_FishMvmt_GetInFoRadar, s_FishMvmt_GetInFoRadar failed");
                                break;
                            }
                        }
                    }
                    /*dertermine the distance between the fish and others*/
                    if(Ret_e == RC_OK)
                    {/*everything is full : array etc*/
                        if(count_zone_af[FISH_MVMT_COUNT_REPULSE] != (unsigned int)0)
                        {
                            s_FishMvmt_Repulsion(f_fish_position_pas[LI_u64],&angle_f64, count_zone_af[FISH_MVMT_COUNT_REPULSE]);
                        }
                        else
                        {
                            if(count_zone_af[FISH_MVMT_COUNT_ALGNMT] != (unsigned int)0)
                            {
                                s_FishMvmt_Alignment(f_fish_position_pas[LI_u64],
                                                    count_zone_af[FISH_MVMT_COUNT_ALGNMT],
                                                    &angle_zone_af[FISH_MVMT_ANGLE_ALGNMT] );

                                if(count_zone_af[FISH_MVMT_COUNT_ATTRACT] != (unsigned int)0)
                                {
                                    s_FishMvmt_Attraction(f_fish_position_pas[LI_u64],
                                                        count_zone_af[FISH_MVMT_COUNT_ATTRACT],
                                                        count_zone_af[FISH_MVMT_COUNT_ALGNMT],
                                                        &angle_zone_af[FISH_MVMT_ANGLE_ATTRACT]);

                                    angle_f64 =    (float)COEF_ALGNMT_ANGLE * angle_zone_af[FISH_MVMT_ANGLE_ALGNMT]
                                                    + (float)COEF_ATTRACT_ANGLE * angle_zone_af[FISH_MVMT_ANGLE_ATTRACT];
                                }
                                else
                                {//count_fish_attract = 0
                                    angle_f64 = angle_zone_af[FISH_MVMT_ANGLE_ALGNMT];
                                }
                            }
                            else
                            {//count_fish_alignmt = 0
                                if( count_zone_af[FISH_MVMT_COUNT_ATTRACT] != (unsigned int)0)
                                {
                                    s_FishMvmt_Attraction(f_fish_position_pas[LI_u64],
                                                        count_zone_af[FISH_MVMT_COUNT_ATTRACT],
                                                        count_zone_af[FISH_MVMT_COUNT_ALGNMT],
                                                        &angle_zone_af[FISH_MVMT_ANGLE_ATTRACT]);

                                    angle_f64 = (float)angle_zone_af[FISH_MVMT_ANGLE_ATTRACT];
                                }
                                else
                                {//count_fish_attract = 0
                                    angle_f64 = (float)f_fish_position_pas[LI_u64].angle_f64;
                                }
                            }
                        }
                        f_fish_position_pas[LI_u64].angle_f64 = angle_f64;
                        f_fish_position_pas[LI_u64].positionX_f64 -= fish_velocity_f64 * cos(angle_f64);
                        f_fish_position_pas[LI_u64].positionY_f64 -= fish_velocity_f64 * sin(angle_f64);
                        /*free the allocation and linked list*/
                    }
                }
            }
        }
    }
    ModLog_WriteInfoInFile("We exit from s_FishMvmt_MovingFishes");
    return Ret_e;
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************

/************************************
* s_FishMvmt_CalculateDistance
************************************/
static t_eReturnCode s_FishMvmt_CalculateDistance(float *f_return_value_f64, t_sFishMvmt_FishParameters f_fish_positionA_ps, t_sFishMvmt_FishParameters f_fish_positionB_ps)
{
    t_eReturnCode Ret_e = RC_OK;
    if(f_return_value_f64 == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ModLog_WriteInfoInFile("In s_FishMvmt_CalculateDistance param invalid");
    }
    if(Ret_e == RC_OK)
    {
        *f_return_value_f64 = sqrt(pow(f_fish_positionB_ps.positionX_f64 - f_fish_positionA_ps.positionX_f64, 2) + pow(f_fish_positionB_ps.positionY_f64 - f_fish_positionA_ps.positionY_f64, 2));
    }
    return Ret_e;

}
/***************************
* s_FishMvmt_GetBorderFish
***************************/
static t_eReturnCode s_FishMvmt_BorderFish(t_sFishMvmt_FishParameters *f_fishes_position_ps, bool *f_is_border_touch_pb)
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
* s_FishMvmt_GetInFoRadar
************************************/
static t_eReturnCode s_FishMvmt_GetInFoRadar(t_sFishMvmt_FishParameters f_fish_position_s,
                                             t_sFishMvmt_FishParameters f_group_fish_s,
                                             unsigned int f_count_zone_uai[])
{
    ModLog_WriteInfoInFile("We enter in s_FishMvmt_GetInFoRadar");
    t_eReturnCode Ret_e = RC_OK;
    float distance_f64;
    bool complete_task_b = false;
    if(f_count_zone_uai == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ModLog_WriteInfoInFile("In s_FishMvmt_GetInFoRadar param invalid");
    }
    if(Ret_e == RC_OK)
    {
        /*POSSIBLE ERROR*/
        Ret_e = s_FishMvmt_CalculateDistance(&distance_f64, f_fish_position_s, f_group_fish_s);
        if(Ret_e == RC_OK)
        {
            if(distance_f64 <= ZONE_REPULSION)
            {
                f_fish_position_s.bank_repulse_fishes_ps[f_count_zone_uai[FISH_MVMT_COUNT_REPULSE]].angle_f64      = (float)f_group_fish_s.angle_f64;
                f_fish_position_s.bank_repulse_fishes_ps[f_count_zone_uai[FISH_MVMT_COUNT_REPULSE]].positionX_f64  = (float)f_group_fish_s.positionX_f64;
                f_fish_position_s.bank_repulse_fishes_ps[f_count_zone_uai[FISH_MVMT_COUNT_REPULSE]].positionY_f64  = (float)f_group_fish_s.positionY_f64;
                f_count_zone_uai[FISH_MVMT_COUNT_REPULSE] += 1;
                complete_task_b = true;
                ModLog_WriteInfoInFile("distance put in repulse zone");
            }
            if(distance_f64 <= ZONE_ALIGNMENT
            && distance_f64 > ZONE_REPULSION)
            {
                f_fish_position_s.bank_alignmt_fishes_ps[f_count_zone_uai[FISH_MVMT_COUNT_ALGNMT]].angle_f64    =  (float)f_group_fish_s.angle_f64;
                f_fish_position_s.bank_alignmt_fishes_ps[f_count_zone_uai[FISH_MVMT_COUNT_ALGNMT]].distance_f64 =  (float)distance_f64;
                f_count_zone_uai[FISH_MVMT_COUNT_ALGNMT] += 1;
                complete_task_b = true;
                ModLog_WriteInfoInFile("distance put in alignmt zone");
            }
            if(distance_f64 <= ZONE_ATTRACTION
            && distance_f64 > ZONE_ALIGNMENT)
            {
                f_fish_position_s.bank_attract_fishes_ps[ f_count_zone_uai[FISH_MVMT_COUNT_ATTRACT]].angle_f64    =  (float)f_group_fish_s.angle_f64;
                f_fish_position_s.bank_attract_fishes_ps[ f_count_zone_uai[FISH_MVMT_COUNT_ATTRACT]].distance_f64 =  (float)distance_f64;
                 f_count_zone_uai[FISH_MVMT_COUNT_ATTRACT] += 1 ;
                complete_task_b = true;
                ModLog_WriteInfoInFile("distance put in attract zone");

            }
            if(complete_task_b != true)
            {
                ModLog_WriteErrorInFile("In s_FishMvmt_GetInFoRadar not enter in a single condition");
            }
        }
    }
    ModLog_WriteInfoInFile("We exit in s_FishMvmt_GetInFoRadar");
    return Ret_e;
}

/************************************
* s_FishMvmt_Repulsion
************************************/
static t_eReturnCode s_FishMvmt_Repulsion(t_sFishMvmt_FishParameters   f_fish_position_s,
                                          float *f_angle_repulsion_f64,
                                          unsigned int f_size_array_u64 )
{
    ModLog_WriteInfoInFile("We enter in s_FishMvmt_Repulsion");
    t_eReturnCode Ret_e = RC_OK;
    bool do_nothing_b = false;
    int LI_u64;
    if(f_angle_repulsion_f64 == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ModLog_WriteInfoInFile("In s_FishMvmt_SetNewDirection param invalid");
    }
    if(Ret_e == RC_OK)
    {
        for(LI_u64 = 0 ; LI_u64 < f_size_array_u64 ; LI_u64++)
        {
            //see if the case is not empty
            /*if the 2 fishes have almost the same direction do nothing*/
            if(f_fish_position_s.bank_repulse_fishes_ps[LI_u64].angle_f64 > DELTA_ANGLE_ACCEPTATION)
            {
                if(f_fish_position_s.angle_f64 <= DELTA_ANGLE_ACCEPTATION + f_fish_position_s.bank_repulse_fishes_ps[LI_u64].angle_f64
                &&f_fish_position_s.angle_f64 >=f_fish_position_s.bank_repulse_fishes_ps[LI_u64].angle_f64 - DELTA_ANGLE_ACCEPTATION
                    )
                {
                    *f_angle_repulsion_f64 = (float)0;
                    do_nothing_b = true;
                }
            }
            if(do_nothing_b != true)
            {/*which means the direction are not the same*/
                if(f_fish_position_s.bank_repulse_fishes_ps[LI_u64].positionX_f64 >= f_fish_position_s.positionX_f64)
                {
                    if((f_fish_position_s.bank_repulse_fishes_ps[LI_u64].angle_f64 <     M_PI / 2
                      &&f_fish_position_s.bank_repulse_fishes_ps[LI_u64].angle_f64  >=    0)
                     ||(f_fish_position_s.bank_repulse_fishes_ps[LI_u64].angle_f64 >=     3 * M_PI / 2
                     && f_fish_position_s.bank_repulse_fishes_ps[LI_u64].angle_f64 <     2 * M_PI ))
                    {
                        if(f_fish_position_s.angle_f64 >= 0
                        &&f_fish_position_s.angle_f64 < M_PI)
                        {
                            *f_angle_repulsion_f64 =- (float)(REPULSION_ANGLE);
                        }
                        else
                        {
                            *f_angle_repulsion_f64 = + (float) REPULSION_ANGLE;
                        }
                    }
                    else
                    /*f_group_fish_ps->angle_f64 >     M_PI / 2
                    &&f_group_fish_ps->angle_f64  <    3 * M_PI / 2*/
                    {
                        *f_angle_repulsion_f64 = (float)f_fish_position_s.angle_f64;
                    }
                }
                else
                {/*f_repulse_grp_fish_as[LI_u64].positionX_f64 <= f_fish_position_s->positionX_f64*/
                    if(f_fish_position_s.bank_repulse_fishes_ps[LI_u64].angle_f64 >= M_PI / 2
                    && f_fish_position_s.bank_repulse_fishes_ps[LI_u64].angle_f64 < 3 * M_PI / 2)
                    {
                        *f_angle_repulsion_f64 = (float)f_fish_position_s.angle_f64;
                    }
                    else
                    {/*the inverse */
                        if(f_fish_position_s.angle_f64 >= 0
                        && f_fish_position_s.angle_f64 <= M_PI)
                        {
                            *f_angle_repulsion_f64 = +(float)REPULSION_ANGLE;
                        }
                        else
                        {/*PI to 2 * PI*/
                            *f_angle_repulsion_f64 =  -(float)REPULSION_ANGLE;
                        }
                    }
                }
            }
        }
    }
    ModLog_WriteInfoInFile("We enter in s_FishMvmt_Repulsion");
    return Ret_e;
}
/************************
* s_FishMvmt_Alignment
************************/
static t_eReturnCode s_FishMvmt_Alignment(t_sFishMvmt_FishParameters f_fish_s,
                                          unsigned int f_nbr_elem_alignmt_u64,
                                          float *f_angle_alignment_f64)
{
    ModLog_WriteInfoInFile("We enter in s_FishMvmt_Alignment");
    t_eReturnCode Ret_e = RC_OK;
    float sum_angle_f64;
    int LI_u64;
    if(f_angle_alignment_f64 == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ModLog_WriteErrorInFile("In s_FishMvmt_Alignment param invalid");
    }
    if(Ret_e == RC_OK)
    {
        if(f_nbr_elem_alignmt_u64 < NBR_INTERACTION_MAX)
        {
            for(LI_u64 = 0 ; LI_u64 < f_nbr_elem_alignmt_u64 ; LI_u64++)
            {/*calculte the direction of the group*/

                sum_angle_f64 += (float)f_fish_s.bank_alignmt_fishes_ps[LI_u64].angle_f64;
            }
            /*calculate the average angle*/
            *f_angle_alignment_f64 = sum_angle_f64 / (float)f_nbr_elem_alignmt_u64;
        }
        else
        {/*(f_nbr_elem_alignmt_u64 > NBR_INTERACTION_MAX*/
            *f_angle_alignment_f64 = f_fish_s.angle_f64;

        }


    }
    ModLog_WriteInfoInFile("We exit in s_FishMvmt_Alignment");
    return Ret_e;
}
/************************
* s_FishMvmt_Attraction
************************/
static t_eReturnCode s_FishMvmt_Attraction( t_sFishMvmt_FishParameters f_fish_s,
                                            unsigned int f_count_fish_attract_u64,
                                            unsigned int f_count_fish_alignmt_u64,
                                            float *f_angle_attract_f64)
{
    ModLog_WriteInfoInFile("We enter in s_FishMvmt_Attraction");
    t_eReturnCode Ret_e = RC_OK;
    float average_angle_f64;
    unsigned int LI_u64;

    if(f_angle_attract_f64 == NULL )
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ModLog_WriteErrorInFile("In s_FishMvmt_Attraction param invalid");
    }
    if(Ret_e == RC_OK)
    {
        /*initialize data needed*/
        average_angle_f64 = (float)0.0;
        /*if there is only one fish around the angle of my fish equals the fish one*/
        if(f_count_fish_attract_u64 == (unsigned int)1)
        {
            ModLog_WriteInfoInFile("nbr_fish_attract_u64");
            *f_angle_attract_f64 = f_fish_s.bank_attract_fishes_ps[0].angle_f64;
        }
        if(f_count_fish_alignmt_u64 == (unsigned int)1)
        {
            ModLog_WriteInfoInFile("nbr_fish_algnmt_u64");
            *f_angle_attract_f64 = f_fish_s.bank_attract_fishes_ps[0].angle_f64;
        }
        else
        {
            if(f_count_fish_attract_u64 >= f_count_fish_alignmt_u64)
            {
                for(LI_u64 = 0 ; LI_u64 < f_count_fish_attract_u64 ; LI_u64++)
                {
                    ModLog_WriteInfoInFile("nbr_fish_attract_u64 > nbr_fish_algnmt_u64");
                    average_angle_f64 = average_angle_f64 + (float)f_fish_s.bank_attract_fishes_ps[LI_u64].angle_f64;
                }    
                *f_angle_attract_f64 = (float)average_angle_f64 / f_count_fish_attract_u64;
            }
            else if(f_count_fish_attract_u64 < f_count_fish_alignmt_u64)
            {
                {/*group fish is a center of mass*/
                    ModLog_WriteInfoInFile("nbr_fish_attract_u64 < nbr_fish_algnmt_u64");
                    *f_angle_attract_f64 = (float)0;
                }
            }
            ModLog_WriteInfoInFile("We exit from s_FishMvmt_Attraction");
        }
    }
    return Ret_e;
}

//************************************************************************************
// End of File
//************************************************************************************

