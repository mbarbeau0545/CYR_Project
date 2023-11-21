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
#include "Config/TypeCommon.h"
#include "Config/Constant.h"
#include "FishMvmt/FishMvmt.h"
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
static t_eReturnCode s_FishMovement_GetMinimalDistanceFish();
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
static t_eReturnCode s_FishMovement_GetCloserFishBankPosition();
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
static t_eReturnCode s_FishMovement_ObstacleAvoidance();
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
static t_eReturnCode s_FishMovement_GetBorderFish();

/*************************************************************************/
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************

//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
static t_eReturnCode s_FishMovement_GetBorderFish(t_sFishMvmt_FishPosition *f_fishes_position_s[])
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

