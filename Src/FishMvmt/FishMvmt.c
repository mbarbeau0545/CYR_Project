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
*	@brief   In repulsion zone the fish is too close of fihes around and has to move in csq.\n
*	@details After calculating the distance between f_fish_position_ps and the f_group_fish_ps.\n
*            We calculate an angle to avoid percution
*
*
*	@params[in] f_fish_position_ps : a pointor to the fish we lookin' at
*	@params[in] f_group_fish_ps :fish whom is too close
*	@params[in] f_angle_repulsion_f64 : angle due to repulsion fish
*	@params[out]
*
*  @retval RC_OK			                     @copydoc RC_OK
*  @retval RC_ERROR_PARAM_INVALID                @copydoc RC_ERROR_PARAM_INVALID
*/
static t_eReturnCode s_FishMvmt_Repulsion(t_sFishMvmt_FishPosition   f_fish_position_s,
                                          t_sFishMvmt_FishRepulsion  f_repulse_grp_fish_as[],
                                          float *f_angle_repulsion_f64,
                                          unsigned int f_size_array_u64 );
/*************************************************************************/
/**
*
*	@brief   In alignment zone, the fish has to have a colinear direction to the group
*	@details We calculate the average direction of the group due to f_group_fish_ps and
*            This is the new direction of f_fish_position_ps
*
*	@params[in] f_LL_fishes_ps         : all fishes around
*	@params[in] f_angle_alignment_f64  : angle due to alignment zone
*	@params[in] f_dis_attract_af       : angle and distance between fish and group fish in attract zone
*	@params[out]
*
*  @retval RC_OK			                     @copydoc RC_OK
*  @retval RC_ERROR_PARAM_INVALID                @copydoc RC_ERROR_PARAM_INVALID
*/
static t_eReturnCode s_FishMvmt_Alignment(t_sLinkedList  *f_LL_fishes_ps, float *f_angle_alignment_f64, t_sFishMvmt_BankFish f_dis_alignmt_af[]);
/*************************************************************************/

/**
*
*  	@brief     In Attraction zone, the fish is attracted by the center of mass
*	@details   If a fish has no group he has to adopt a group
*
*
*	@params[in] f_fish_position_ps        : a pointor to the fish we lookin' at
*	@params[in] f_angle_alignment_f64     : return angle alignment
*	@params[in] f_dis_repulse_af          : angle and distance between fish and group fish in repulse zone
*	@params[in] f_dis_attract_af          : angle and distance between fish and group fish in attract zone
*	@params[in] f_dis_algnmt_af           : angle and distance between fish and group fish in algnmt zone
*	@params[in] f_count_fish_attract_u64  : number of fish in attract zone
*	@params[in] f_count_fish_alignmt_u64  : number of fish in alignment zone
*	@params[out]
*
*  @retval RC_OK			                     @copydoc RC_OK
*  @retval RC_ERROR_PARAM_INVALID                @copydoc RC_ERROR_PARAM_INVALID
*/
static t_eReturnCode s_FishMvmt_Attraction(  float *f_angle_alignment_f64,
                                             t_sFishMvmt_BankFish f_dis_attract_af[],
                                             t_sFishMvmt_BankFish f_dis_algnmt_af[],
                                             unsigned int f_size_array_ui,
                                             unsigned int f_count_fish_attract_u64,
                                             unsigned int f_count_fish_alignmt_u64);
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
*	@params[out]
*
*  @retval RC_OK			                     @copydoc RC_OK
*  @retval RC_ERROR_PARAM_INVALID                @copydoc RC_ERROR_PARAM_INVALID
*/
static t_eReturnCode s_FishMvmt_MovingFishes(t_sFishMvmt_FishPosition f_fish_position_pas[]);
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
*	@params[in]f_fish_positionB_ps: Point B
*	@params[out]
*
*  @retval RC_OK			                     @copydoc RC_OK
*  @retval RC_ERROR_PARAM_INVALID                @copydoc RC_ERROR_PARAM_INVALID
*/
static t_eReturnCode s_FishMvmt_CalculateDistance(float *f_return_value_f64,
                                                  t_sFishMvmt_FishPosition f_fish_positionA_ps,
                                                  t_sFishMvmt_FishPosition f_fish_positionB_ps);
/************************************************************************************************/
/**
 *
 *	@brief   return a difference between two number for qsort
*	@details
*
*
*	@params[in] nbr1_pf64 :first number to compare
*	@params[in] nbr2_pf64: second number
*	@params[in]f_fish_positionB_ps: Point B
*	@params[out]
*
*  @retval RC_OK			                     @copydoc RC_OK
*  @retval RC_ERROR_PARAM_INVALID                @copydoc RC_ERROR_PARAM_INVALID
*/
//static float s_FishMvmt_ComparisonNumber(const void *nbr1_pf64, const void *nbr2_pf64 );
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
*  @retval RC_OK			                     @copydoc RC_OK
*  @retval RC_ERROR_PARAM_INVALID                @copydoc RC_ERROR_PARAM_INVALID
*/
static t_eReturnCode s_FishMvmt_BorderFish(t_sFishMvmt_FishPosition *f_fishes_position_ps, bool *f_is_border_touch_pb);
/*************************************************************************/
/**
 *
 *	@brief   Calcul Distances between the considerer fish and other in the Grid
*	@details The considerer fish f_fish_position_s and it's collegue f_linkedlist_ps are on the grid,
*            this function determine the distance between them
*
*
*	@params[in] f_fish_position_s : the consider fish position
*	@params[in] f_linkedlist_ps : group of fish in the grid
*	@params[in] f_dis_repulse_af: angle and distance between fish and group fish in repulse zone
*	@params[in] f_dis_attract_af: angle and distance between fish and group fish in attract zone
*	@params[in] f_dis_algnmt_af: angle and distance between fish and group fish in algnmt zone
*	@params[out]
*
*  @retval RC_OK			                     @copydoc RC_OK
*  @retval RC_ERROR_PARAM_INVALID                @copydoc RC_ERROR_PARAM_INVALID
*/
static t_eReturnCode s_FishMvmt_GetInFoRadar(t_sFishMvmt_FishPosition f_fish_position_s,
                                             t_sFishMvmt_FishPosition f_group_fish_s,
                                             t_sFishMvmt_FishPosition f_dis_repulse_af[],
                                             t_sFishMvmt_BankFish f_dis_attract_af[],
                                             t_sFishMvmt_BankFish f_dis_algnmt_af[]);
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
/*************************************************************************/
/**
 *
 *	@brief   Get the number of none 0 value i.I the fish number in each zone
*	@details put NULL to one and make the other one
*
*
*	@params[in] f_bank_array_af : the array of fishes alignment and attraction
*	@params[in] f_repulse_array_af : the array of fishes repulse
*	@params[in] f_bank_array_af : the array of fishes alignment and attraction
*	@params[in] f_bank_array_af : the array of fishes alignment and attraction
*	@params[in] f_bank_array_af : the array of fishes alignment and attraction
*	@params[out]
*
*  @retval RC_OK			                     @copydoc RC_OK
*  @retval RC_ERROR_PARAM_INVALID                @copydoc RC_ERROR_PARAM_INVALID
*/
static t_eReturnCode s_FishMvmt_GetNbrValue(t_sFishMvmt_BankFish f_bank_array_af[],
                                            t_sFishMvmt_FishRepulsion f_repulse_array_af[],
                                            unsigned int f_size_array_ui,
                                            unsigned int *f_countor_value);
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
t_eReturnCode FishMvmt_FishMain(t_sFishMvmt_FishPosition f_fishes_positions_as[])
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
        /*initialize Linklist for the radar*/
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
                    s_FishMvmt_MovingFishes(f_fishes_positions_as);
                    //vitesse d'avancement et direction
                    f_fishes_positions_as[LI_u64].positionX_f64 -= (float)70 * cos(f_fishes_positions_as[LI_u64].angle_f64) * delta_time_f; /*max 70 pixels each second */
                    f_fishes_positions_as[LI_u64].positionY_f64 -= (float)70 * sin(f_fishes_positions_as[LI_u64].angle_f64) * delta_time_f; /*max 70 pixels each second */
                }
            }

        }
    }
    return Ret_e;
}
static t_eReturnCode s_FishMvmt_MovingFishes(t_sFishMvmt_FishPosition f_fish_position_pas[])
{
    t_eReturnCode Ret_e = RC_OK;
    t_sLinkedList *LL_fish_position_ps;
    int LI_u64;
    int LI2_u64;
    float angle_f64;
    float angle_zone_af[FISH_MVMT_NBR_ANGLE];
    unsigned int count_zone_af[FISH_MVMT_NBR_COUNT];
    int boundary_grid_aui[FISH_MVMT_NBR_BOUNDARY];
    unsigned int nbr_element_u64 = 0;
    static t_sFishMvmt_BankFish *bank_attract_fishes;
    static t_sFishMvmt_BankFish *bank_alignmt_fishes;
    static t_sFishMvmt_FishRepulsion *bank_repulse_fishes;
    if(f_fish_position_pas == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ModLog_WriteInfoInFile("In FishMvmnt_Separation param invalid");
    }
    if(Ret_e == RC_OK)
    {
        //do allocation for the array
        bank_attract_fishes = malloc(NBR_ELEM_ZONE * sizeof(t_sFishMvmt_BankFish));
        bank_alignmt_fishes = malloc(NBR_ELEM_ZONE * sizeof(t_sFishMvmt_BankFish));
        bank_repulse_fishes = malloc(NBR_ELEM_ZONE * sizeof(t_sFishMvmt_FishPosition));
        /*do for each fish*/
        for(LI_u64 = 0 ; LI_u64 < NBR_FISH ; LI_u64++)
        {
            /*initialize final angle to 0*/
            angle_f64 = 0;
            /*initialize all array to 0*/
            memset(angle_zone_af, (float)0, sizeof(angle_zone_af));
            memset(count_zone_af, (float)0, sizeof(count_zone_af));
            memset(boundary_grid_aui, (float)0, sizeof(boundary_grid_aui));
            /*initialize linked list */
            LL_fish_position_ps = LinkList_CreatLinkedList(sizeof(t_sFishMvmt_FishPosition));
            boundary_grid_aui[FISH_MVMT_BOUNDARY_UP_X]    = f_fish_position_pas[LI_u64].positionX_f64 + (float)FISH_RADAR_SQUARE;
            boundary_grid_aui[FISH_MVMT_BOUNDARY_DOWN_X]  = f_fish_position_pas[LI_u64].positionX_f64 - (float)FISH_RADAR_SQUARE;
            boundary_grid_aui[FISH_MVMT_BOUNDARY_UP_Y]    = f_fish_position_pas[LI_u64].positionY_f64 + (float)FISH_RADAR_SQUARE;
            boundary_grid_aui[FISH_MVMT_BOUNDARY_DOWN_Y]  = f_fish_position_pas[LI_u64].positionY_f64 +-  (float)FISH_RADAR_SQUARE;
            /*find the other fishes in the grid we just determine and pull it in linkedlist*/
            for(LI2_u64 = 0 ; LI2_u64 < NBR_FISH ; LI2_u64++)
            {
                /*see if the x-axes and y-axes  corresponding*/
                if( LI2_u64 != LI_u64
                &&  f_fish_position_pas[LI2_u64].positionX_f64 <= boundary_grid_aui[FISH_MVMT_BOUNDARY_UP_X]
                &&f_fish_position_pas[LI2_u64].positionX_f64 >= boundary_grid_aui[FISH_MVMT_BOUNDARY_DOWN_X]
                &&f_fish_position_pas[LI2_u64].positionY_f64 <= boundary_grid_aui[FISH_MVMT_BOUNDARY_UP_Y]
                &&f_fish_position_pas[LI2_u64].positionY_f64 >= boundary_grid_aui[FISH_MVMT_BOUNDARY_DOWN_Y])
                {
                    /*put it in the right linklist add at the end */
                    Ret_e = s_FishMvmt_GetInFoRadar(f_fish_position_pas[LI_u64],
                                                    f_fish_position_pas[LI2_u64],
                                                    bank_repulse_fishes,
                                                    bank_attract_fishes,
                                                    bank_alignmt_fishes);

                    /*Write rror msg if adding element in linked list doesn't work*/
                    if(Ret_e != RC_OK)
                    {
                        ModLog_WriteErrorInFile("In s_FishMvmt_GetInFoRadar, s_FishMvmt_GetInFoRadar failed");
                        break;
                    }
                }
            }
            
            /*initialize all array to 0*/
            /*memset(bank_attract_fishes->distance_f64, (float)0, sizeof(bank_attract_fishes));
            memset(bank_alignmt_fishes->distance_f64, (float)0, sizeof(bank_alignmt_fishes));*/
            /*check if the alloc worked*/
            if(bank_attract_fishes == NULL || bank_alignmt_fishes == NULL || bank_repulse_fishes == NULL)
            {
                Ret_e = RC_ERROR_ALLOC_FAILED;
                ModLog_WriteInfoInFile("In s_FishMvmt_GetInFoRadar alloc failed");
            }
            /*dertermine the distance between the fish and others*/
            if(Ret_e == RC_OK)
            {/*everything is full : array etc*/
                /*sort the array decroissant way*/
                /*get the number of fish in each zone*/
                Ret_e = s_FishMvmt_GetNbrValue(bank_alignmt_fishes, NULL,nbr_element_u64, &count_zone_af[FISH_MVMT_COUNT_ALGNMT]);
                if(Ret_e == RC_OK)
                {
                    Ret_e = s_FishMvmt_GetNbrValue(NULL, bank_repulse_fishes,nbr_element_u64, &count_zone_af[FISH_MVMT_COUNT_REPULSE]);
                }
                if(Ret_e == RC_OK)
                {
                    Ret_e = s_FishMvmt_GetNbrValue(bank_attract_fishes, NULL,nbr_element_u64, &count_zone_af[FISH_MVMT_COUNT_ATTRACT]);
                }
                if(count_zone_af[FISH_MVMT_COUNT_REPULSE] != 0)
                {
                    s_FishMvmt_Repulsion(f_fish_position_pas[LI_u64], bank_repulse_fishes,&angle_f64, nbr_element_u64);
                }
                else
                {
                    if(count_zone_af[FISH_MVMT_COUNT_ALGNMT] != 0)
                    {
                        s_FishMvmt_Alignment(LL_fish_position_ps,
                                             &angle_zone_af[FISH_MVMT_ANGLE_ALGNMT],
                                             bank_alignmt_fishes);

                        if(count_zone_af[FISH_MVMT_COUNT_ATTRACT] != 0)
                        {
                            s_FishMvmt_Attraction(&angle_zone_af[FISH_MVMT_ANGLE_ATTRACT],
                                                  bank_attract_fishes,
                                                  bank_alignmt_fishes,
                                                   nbr_element_u64,
                                                   count_zone_af[FISH_MVMT_COUNT_ATTRACT],
                                                   count_zone_af[FISH_MVMT_COUNT_ALGNMT]);

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
                        if( count_zone_af[FISH_MVMT_COUNT_ATTRACT] != 0)
                        {
                            s_FishMvmt_Attraction(&angle_zone_af[FISH_MVMT_ANGLE_ATTRACT],
                                                  bank_attract_fishes,
                                                  bank_alignmt_fishes,
                                                  nbr_element_u64,
                                                  count_zone_af[FISH_MVMT_COUNT_ATTRACT],
                                                  count_zone_af[FISH_MVMT_COUNT_ALGNMT]);

                            angle_f64 = (float)angle_zone_af[FISH_MVMT_ANGLE_ATTRACT];
                        }
                        else
                        {//count_fish_attract = 0
                            angle_f64 = (float)0;
                        }
                    }
                }
            }
            /*change the dir to the fish*/
            f_fish_position_pas[LI_u64].angle_f64 = angle_f64;
        }

            /*free the allocation and linked list*/
            free(bank_alignmt_fishes);
            free(bank_attract_fishes);
            free(bank_repulse_fishes);
            LinkList_FreeList(LL_fish_position_ps);
    }
    return Ret_e;
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
/************************************
* s_FishMvmt_GetNbrValue
************************************/
static t_eReturnCode s_FishMvmt_GetNbrValue(t_sFishMvmt_BankFish f_bank_array_af[],t_sFishMvmt_FishRepulsion f_repulse_array_af[],unsigned int f_size_array_ui, unsigned int *f_countor_value)
{
    t_eReturnCode Ret_e = RC_OK;
    bool did_something_here_b = false;
    unsigned int LI_u64;
    if(f_bank_array_af != NULL && f_repulse_array_af == NULL)
    {
        if(Ret_e == RC_OK)
        {
            for(LI_u64 = 0 ; LI_u64 < f_size_array_ui ; LI_u64++)
            {
                if(f_bank_array_af[LI_u64].distance_f64 != (float)0)
                {
                    *f_countor_value += 1;
                }
            }
            did_something_here_b = true;
        }
        if(f_repulse_array_af != NULL && f_bank_array_af == NULL)
        {
            for(LI_u64 = 0 ; LI_u64 < f_size_array_ui ; LI_u64++)
                {
                    if(f_repulse_array_af[LI_u64].angle_f64 != (float)0)
                    {
                        *f_countor_value += 1;
                    }
                }
                did_something_here_b = true;
        }
        if(did_something_here_b != true)
        {
            Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
        }
    }
    return Ret_e;
}
/************************************
* s_FishMvmt_CalculateDistance
************************************/
static t_eReturnCode s_FishMvmt_CalculateDistance(float *f_return_value_f64, t_sFishMvmt_FishPosition f_fish_positionA_ps, t_sFishMvmt_FishPosition f_fish_positionB_ps)
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
* s_FishMvmt_GetInFoRadar
************************************/
static t_eReturnCode s_FishMvmt_GetInFoRadar(t_sFishMvmt_FishPosition f_fish_position_s,
                                             t_sFishMvmt_FishPosition f_group_fish_s,
                                             t_sFishMvmt_FishPosition f_dis_repulse_af[],
                                             t_sFishMvmt_BankFish f_dis_attract_af[],
                                             t_sFishMvmt_BankFish f_dis_algnmt_af[])
{
    t_eReturnCode Ret_e = RC_OK;
    int LI_64;
    unsigned int LI_repulse_u64 = 0;
    unsigned int LI_attract_u64 = 0;
    unsigned int LI_alignmt_u64 = 0;
    float distance_f64;
    t_sFishMvmt_LLfishPosRadar *current_ps;
    unsigned int nbr_element_u64 = f_linkedlist_ps->nbr_element_u16;
    if(f_linkedlist_ps == NULL || f_dis_algnmt_af == NULL || f_dis_repulse_af == NULL || f_dis_attract_af == NULL)
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
            bank_fish_s->distance_f64 = distance_f64;
            bank_fish_s->angle_f64 = f_group_fish_s.angle_f64;
            if(distance_f64 <= ZONE_REPULSION)
            {
                Ret_e = LinkList_AddElement(f_LL_fish_repulse_ps, &f_group_fish_s,0);
                complete_task_b = true;
                ModLog_WriteInfoInFile("distance put in repulse zone");
            }
            if(distance_f64 <= ZONE_ALIGNMENT
            && distance_f64 > ZONE_REPULSION)
            {
                Ret_e = LinkList_AddElement(f_LL_fish_alignmt_ps, bank_fish_s,0);
                complete_task_b = true;
                ModLog_WriteInfoInFile("distance put in alignmt zone");
            }
            if(distance_f64 <= ZONE_ATTRACTION
            && distance_f64 > ZONE_ALIGNMENT)
            {
                Ret_e = LinkList_AddElement(f_LL_fish_attract_ps, &bank_fish_s, 0);
                complete_task_b = true;
                ModLog_WriteInfoInFile("distance put in attract zone");

            }
            if(Ret_e != RC_OK)
            {
                ModLog_WriteErrorInFile("In s_FishMvmt_GetInFoRadar LinkList_AddElement failed");
            }
            if(complete_task_b != true)
            {
                ModLog_WriteErrorInFile("In s_FishMvmt_GetInFoRadar not enter in a single condition");
                ModLog_WriteDataInFile(ModLog_FLOAT, "distance", &distance_f64);
            }
        }
        
    }
    ModLog_WriteInfoInFile("We exit in s_FishMvmt_GetInFoRadar");
    return Ret_e;
}

/************************************
* s_FishMvmt_Repulsion
************************************/
static t_eReturnCode s_FishMvmt_Repulsion(t_sFishMvmt_FishPosition   f_fish_position_s,
                                          t_sFishMvmt_FishRepulsion  f_repulse_grp_fish_as[],
                                          float *f_angle_repulsion_f64,
                                          unsigned int f_size_array_u64 )
{
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
            if(f_repulse_grp_fish_as[LI_u64].angle_f64 != (float)0)
            {
                /*if the 2 fishes have almost the same direction do nothing*/
                if(f_repulse_grp_fish_as[LI_u64].angle_f64 > DELTA_ANGLE_ACCEPTATION)
                {
                    if(f_fish_position_s.angle_f64 <= DELTA_ANGLE_ACCEPTATION + f_repulse_grp_fish_as[LI_u64].angle_f64
                    &&f_fish_position_s.angle_f64 >= f_repulse_grp_fish_as[LI_u64].angle_f64 - DELTA_ANGLE_ACCEPTATION
                      )
                    {
                        *f_angle_repulsion_f64 = (float)0;
                        do_nothing_b = true;
                    }
                }
                if(do_nothing_b != true)
                {/*which means the direction are not the same*/
                    if(f_repulse_grp_fish_as[LI_u64].fish_position_s->axeX_f64 >= f_fish_position_s.positionX_f64)
                    {
                        if((f_repulse_grp_fish_as[LI_u64].angle_f64 <     M_PI / 2
                            && f_repulse_grp_fish_as[LI_u64].angle_f64  >=    0)
                        || (f_repulse_grp_fish_as[LI_u64].angle_f64 >=     3 * M_PI / 2
                        && f_repulse_grp_fish_as[LI_u64].angle_f64 <     2 * M_PI )
                          )
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
                            *f_angle_repulsion_f64 = (float)0;
                        }
                    }
                    else
                    {/*f_group_fish_ps->positionX_f64 >= f_fish_position_s->positionX_f64*/
                        if(f_repulse_grp_fish_as[LI_u64].angle_f64 >= M_PI / 2
                        && f_repulse_grp_fish_as[LI_u64].angle_f64 < 3 * M_PI / 2)
                        {
                            *f_angle_repulsion_f64 = (float)0;
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
    }
    return Ret_e;
}
/************************
* s_FishMvmt_Alignment
************************/
static t_eReturnCode s_FishMvmt_Alignment(t_sLinkedList  *f_LL_fishes_ps, float *f_angle_alignment_f64, t_sFishMvmt_BankFish f_dis_alignmt_af[])
{
    t_eReturnCode Ret_e = RC_OK;
    t_sFishMvmt_LLfishPosRadar *current_ps;
    unsigned int counter_angle_u64;
    float sum_angle_f64;
    int LI_u64;
    if(f_LL_fishes_ps == NULL || f_angle_alignment_f64 == NULL || f_dis_alignmt_af == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ModLog_WriteErrorInFile("In s_FishMvmt_Alignment param invalid");
    }
    if(Ret_e == RC_OK)
    {
        for(LI_u64 = 0 ; LI_u64 < f_LL_fishes_ps->nbr_element_u16 ; LI_u64++)
        {/*calculte the direction of the group*/
            if(f_dis_alignmt_af[LI_u64].distance_f64 != (float)0)
            {
                sum_angle_f64 += (float)f_dis_alignmt_af[LI_u64].angle_f64;
                counter_angle_u64 += (unsigned int)1;
            }
            current_ps = (t_sFishMvmt_LLfishPosRadar *)current_ps->next_elem_ps;
        }
        /*calculate the average angle*/
        *f_angle_alignment_f64 = sum_angle_f64 / (float)counter_angle_u64;
    }
    return Ret_e;
}
/************************
* s_FishMvmt_Attraction
************************/
static t_eReturnCode s_FishMvmt_Attraction(  float *f_angle_alignment_f64,
                                             t_sFishMvmt_BankFish f_dis_attract_af[],
                                             t_sFishMvmt_BankFish f_dis_algnmt_af[],
                                             unsigned int f_size_array_ui,
                                             unsigned int f_count_fish_attract_u64,
                                             unsigned int f_count_fish_alignmt_u64)
{
    t_eReturnCode Ret_e = RC_OK;
    float average_angle_f64;
    unsigned int LI_u64;

    if(f_angle_alignment_f64 == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ModLog_WriteErrorInFile("In s_FishMvmt_Attraction param invalid");
    }
    if(Ret_e == RC_OK)
    {
        if(Ret_e == RC_OK)
        {
            /*if there is only one fish around the angle of my fish equals the fish one*/
            if((f_count_fish_alignmt_u64 + f_count_fish_attract_u64 )== (unsigned int)1 )
            {
                for(LI_u64 = 0 ; LI_u64 < f_size_array_ui ; LI_u64++)
                {
                    if(f_dis_algnmt_af[LI_u64].angle_f64 != (float)0)
                    {
                        /*all tab are equals zero except one and tab are sort in decroissant way*/
                        *f_angle_alignment_f64 = (float)f_dis_algnmt_af[LI_u64].angle_f64;
                    }
                    if(f_dis_attract_af[LI_u64].angle_f64 != (float)0)
                    {
                        *f_angle_alignment_f64 = (float)f_dis_algnmt_af[LI_u64].angle_f64;
                    }
                }
                if(*f_angle_alignment_f64 == (float)0)
                {
                    ModLog_WriteErrorInFile("In s_FishMvmt_Attraction cannot find none 0 value");
                }
            }
            else
            {

                if(f_count_fish_alignmt_u64 < f_count_fish_attract_u64)
                {/*group attract is a centor of mass*/
                    for(LI_u64 = 0 ; LI_u64 < f_size_array_ui ; LI_u64++)
                    {
                        average_angle_f64 += f_dis_attract_af[LI_u64].angle_f64;
                    }
                    *f_angle_alignment_f64 = (float)average_angle_f64 / f_count_fish_attract_u64;
                }
                else
                {/*group fish is a center of mass*/
                    *f_angle_alignment_f64 = (float)0;
                }

            }
        }
    }
    return Ret_e;
}
/*static float s_FishMvmt_ComparisonNumber(const void *f_nbr1_pf64, const void *f_nbr2_pf64 )
{
    t_eReturnCode Ret_e = RC_OK;
    float return_nbr_f64 = 0;
    if(f_nbr1_pf64 == NULL || f_nbr2_pf64 == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ModLog_WriteErrorInFile("In s_FishMvmt_ComparisonNumber param invalid");
    }
    if(Ret_e == RC_OK)
    {
        return_nbr_f64 = (*(float*)f_nbr2_pf64 - *(float*)f_nbr1_pf64);
    }
    return return_nbr_f64;
}
static t_eReturnCode s_FishMvmt_SortDecroissantArray(t_sFishMvmt_BankFish , unsigned int f_size_array_u64)
{
    t_eReturnCode Ret_e = RC_OK;
    if(f_array_af == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ModLog_WriteErrorInFile("In s_FishMvmt_SortDecroissantArray param invalid");
    }
    if(Ret_e == RC_OK)
    {
        qsort(f_array_af, f_size_array_u64,f_array_af[0], s_FishMvmt_ComparisonNumber);
    }
    return Ret_e;
}*/
//************************************************************************************
// End of File
//************************************************************************************

