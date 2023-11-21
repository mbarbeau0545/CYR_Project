 /* ******************************************************************
 * Copyright (C) 2023 - AUDMBA
 *
 * This document is AUDMBA property.
 * It should not be reproduced in any medium or used in any way
 * without prior written consent of AUDMBA
 * ******************************************************************/
/**
* @file        LinkedList.c
* @brief       Manage LinkedList.
* @details     
* @author      AUDMBA
* @date        28/10/2023
* @version     0.0
*
*/
// ********************************************************************
// *                      Includes
// ********************************************************************
#include "LinkedList.h"

// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************
static t_bool g_init_linked_list = (t_bool)false;
// ********************************************************************
// *                      Constants
// ********************************************************************

// ********************************************************************
// *                      Variables
// ********************************************************************

//****************************************************************************
//                      Local functions - Prototypes
//****************************************************************************

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
//****************************************************************************
//                      Public functions - Implementation
//****************************************************************************
//*******************************
// LinkList_CreatLinkedList
//*******************************
t_sLinkedList *LinkList_CreatLinkedList(t_uint16 f_size_struct_u16)
{
    t_sLinkedList *LinkedList_s = (t_sLinkedList *)malloc(sizeof(t_sLinkedList));
    t_eReturnCode Ret_e = RC_OK;
    if(f_size_struct_u16 < 0)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else if(LinkedList_s == NULL)
    {
        Ret_e = RC_ERROR_ALLOC_FAILED;
    }
    else if(Ret_e == RC_OK)
    {
    LinkedList_s->first_elment_pv = (void *)NULL;
    LinkedList_s->last_element_pv = (void *)NULL;
    LinkedList_s->size_struct_u16 = f_size_struct_u16;
    LinkedList_s->nbr_element_u16 = 0;
    }
    g_init_linked_list = true;
    return LinkedList_s;
}
//*******************************
// LinkList_AddElement
//*******************************
t_eReturnCode LinkList_AddElement(t_sLinkedList *f_linkedlist_ps, void * f_data_pv, t_uint8 f_place_u8)
{
    t_sElement *current_ps;
    t_sElement *element_add_ps;
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 index_loop_u8;
    if(g_init_linked_list == false)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    else if(f_linkedlist_ps == NULL || f_data_pv == NULL || f_place_u8 < 0)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else if(Ret_e == RC_OK)
    {
        current_ps = f_linkedlist_ps->first_elment_pv;
        element_add_ps = (t_sElement *)malloc(sizeof(f_linkedlist_ps->size_struct_u16));
        element_add_ps->data_pv = (void *)f_data_pv;
        if(current_ps == NULL && f_linkedlist_ps->nbr_element_u16 != 0)
        {
            Ret_e = RC_ERROR_POINTOR_NULL;
        }
        else
        {
            //add when there's no element yet
            if(f_linkedlist_ps->nbr_element_u16 == 0)
            {
                element_add_ps->next_struct_pv = (void *)NULL;
                f_linkedlist_ps->first_elment_pv = (t_sElement *)element_add_ps;
                f_linkedlist_ps->last_element_pv = (t_sElement *)element_add_ps;
                Ret_e = RC_OK;
            }
            //add at the end
            else if(f_place_u8 == 0)
            {
                element_add_ps->next_struct_pv = (t_sElement *)f_linkedlist_ps->first_elment_pv;
                f_linkedlist_ps->first_elment_pv = (t_sElement *)element_add_ps;
            }
            else if(f_place_u8 == -1)
            {
                element_add_ps->next_struct_pv = (void *)NULL;
                f_linkedlist_ps->last_element_pv->next_struct_pv = (t_sElement *)element_add_ps;
                f_linkedlist_ps->last_element_pv = (t_sElement *)element_add_ps;
                Ret_e = RC_OK;
            }
            else
            {
                for(index_loop_u8 = 0 ; index_loop_u8 < f_place_u8 -1; index_loop_u8 ++)
                {
                    current_ps = (t_sElement *)current_ps->next_struct_pv;
                }
                if(current_ps == NULL)
                {
                    Ret_e = RC_ERROR_POINTOR_NULL;
                }
                else
                {
                    element_add_ps->next_struct_pv = current_ps ->next_struct_pv;
                    current_ps->next_struct_pv = (t_sElement *)element_add_ps;
                    Ret_e = RC_OK;
                }
            }
            f_linkedlist_ps->nbr_element_u16 += (t_uint8)1;
        }
    }
    return Ret_e;
}
//*******************************
// LinkList_GetElement
//*******************************
/*t_eReturnCode LinkListGetElement(t_sLinkedList *f_list_ps, void *f_return_element_ps, unsigned int f_position_ui)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sElement *current_ps;
    unsigned int LI_ui;
    //verify arg
    if(f_list_ps == NULL || f_return_element_ps != NULL)
    {
        Ret_e = RC_ERROR_POINTOR_NULL;
    }
    else if(f_position_ui < 0 || f_position_ui > f_list_ps->nbr_element_u16)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else
    {
        if(f_position_ui == 0)
        {
            memcpy(f_return_element_ps,f_list_ps->first_elment_pv->data_pv, sizeof(f_list_ps->size_struct_u16));
            //f_return_element_ps = (void *)f_list_ps->first_element_ps->data_pv;
                Ret_e = RC_OK;
        }
        else if(f_position_ui == -1)
        {
            memcpy(f_return_element_ps,f_list_ps->last_element_pv->data_pv, sizeof(f_list_ps->size_struct_u16));
            //f_return_element_ps = (void *)f_list_ps->first_element_ps->data_pv;
                Ret_e = RC_OK;
        }
        else
        {
            current_ps = (t_sElement *)f_list_ps->first_elment_pv;
            for(LI_ui  = 0 ; LI_ui < f_position_ui ; LI_ui ++)
            {
                current_ps = (t_sElement *)current_ps->next_struct_pv;
            }
            memcpy(f_return_element_ps,current_ps->data_pv, sizeof(f_list_ps->size_struct_u16));
            //f_return_element_ps = (void *)current_ps->data_pv;
            Ret_e = RC_OK;
        }
}
return Ret_e;
}*/
//*******************************
// LinkList_ReplaceElement
//*******************************
t_eReturnCode LinkList_ReplaceElement(t_sLinkedList *f_linkedlist_ps, void *f_data_pv, t_uint8 f_place_u8)
{
    t_sElement *current_ps;
    t_uint8 loop_index_u8;
    t_eReturnCode Ret_e = RC_OK;
    if(g_init_linked_list == false)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    else if(f_linkedlist_ps == NULL || f_data_pv == NULL || f_place_u8 < 0)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else if(Ret_e == RC_OK)
    {
        current_ps = (t_sElement *)f_linkedlist_ps->first_elment_pv;
        if(current_ps == NULL)
        {
            Ret_e = RC_ERROR_POINTOR_NULL;
        }
        else
        {
            if(f_place_u8 == (t_uint8)0)
            {
                f_linkedlist_ps->first_elment_pv->data_pv = f_data_pv;
            }
            else if (f_place_u8 == (t_uint8)-1)
            {
                f_linkedlist_ps->last_element_pv = (t_sElement *)f_data_pv;
            }
            else
            {
                for(loop_index_u8 = 1 ; loop_index_u8 < f_place_u8 ; loop_index_u8++)
                {
                    current_ps = (t_sElement *)current_ps->next_struct_pv;
                }
                if(current_ps != NULL)
                {
                    current_ps->data_pv = (void *)f_data_pv;
                    Ret_e = RC_OK;
                }
                else
                {
                    Ret_e = RC_ERROR_POINTOR_NULL;
                }
            }
        }
    }
    return Ret_e;
}
//*******************************
// LinkList_EraseElement
//*******************************
t_eReturnCode LinkList_EraseElement(t_sLinkedList *f_linkedlist_ps, t_uint8 f_place_u8)
{
    t_sElement *current_ps;
    t_sElement *precedent_ps;
    t_uint8 loop_index_u8;
    t_eReturnCode Ret_e = RC_OK;
    if(g_init_linked_list == false)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    else if(f_linkedlist_ps == NULL  || f_place_u8 < 0 || f_place_u8 > f_linkedlist_ps->nbr_element_u16)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else if(Ret_e == RC_OK)
    {
        current_ps = f_linkedlist_ps->first_elment_pv;
        if(current_ps == NULL)
        {
            Ret_e = RC_ERROR_POINTOR_NULL;
        }
        else
        {
            //erase the first element
            if(f_place_u8 == 0)
            {
                f_linkedlist_ps->first_elment_pv = (t_sElement *)current_ps->next_struct_pv;
            }
            //erase the last element
            else if (f_place_u8 == -1)
            {
                for(loop_index_u8 = 0 ; loop_index_u8 < f_linkedlist_ps->nbr_element_u16 - 1  ; loop_index_u8++)
                {
                    current_ps = (t_sElement *)current_ps->next_struct_pv;
                }
                //check the pointor
                if(current_ps == NULL)
                {
                    Ret_e = RC_ERROR_POINTOR_NULL;
                }
                else
                {
                    f_linkedlist_ps->last_element_pv = (t_sElement *)current_ps;
                    Ret_e = RC_OK;
                }

            }
            //erase the element betwween the first and the last
            else
            {
                for(loop_index_u8 = 0 ; loop_index_u8 < f_place_u8 ; loop_index_u8++)
                {
                    precedent_ps = current_ps;
                    current_ps = (t_sElement *)current_ps->next_struct_pv;
                }
                if(current_ps == NULL)
                {
                    Ret_e = RC_ERROR_POINTOR_NULL;
                }
                else
                {
                    precedent_ps->next_struct_pv = current_ps->next_struct_pv;
                    current_ps->data_pv = (void *)NULL;
                    current_ps->next_struct_pv = (void *)NULL;
                    Ret_e = RC_OK;
                }
            }
        }
    }
    return Ret_e;
}
//*******************************
// LinkList_FreeList
//*******************************
t_eReturnCode LinkList_FreeList(t_sLinkedList *f_linkedlist_ps)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sElement *current_ps;
    t_sElement *next_ps;
    t_uint8 loop_index_u8;
    if(g_init_linked_list == false)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    else if (f_linkedlist_ps == NULL)
    {
        Ret_e = RC_ERROR_POINTOR_NULL;
    }
    else
    {
        current_ps = f_linkedlist_ps->first_elment_pv;
        if(current_ps == NULL)
        {
            Ret_e = RC_ERROR_POINTOR_NULL;
        }
        else
        {
            for(loop_index_u8 = (t_uint8)0 ; loop_index_u8 < f_linkedlist_ps->nbr_element_u16 ; loop_index_u8++)
            {
                next_ps = (t_sElement *)current_ps->next_struct_pv;
                current_ps->data_pv = NULL;
                current_ps->next_struct_pv = NULL;
                current_ps = next_ps;
            }
            //free the struct t_sLinkedList himself
            free(f_linkedlist_ps);
        }
    }
    return Ret_e;
}
//****************************************************************************
//                      Local functions - Implementation
//****************************************************************************

//****************************************************************************
// End of File
//****************************************************************************/
