/**********************************************************************
* @file        LinkedList.h
* @brief       Manage LinkedList.
* @details
* @author      AUDMBA
* @date        28/10/2023
* @version     0.0
*
***********************************************************************/
#ifndef __LinkedList_H
#define __LinkedList_H
    // ********************************************************************
    // *                      Exemple
    // ********************************************************************
/*typedef struct
{
    int positionX;
    int positionY;
}t_sPosition;

typedef struct
{
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    //be careful the client has to put the pointor structure first and after the pointor to the next element
    //cause if he/she doesn't that doesn't work
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    t_sPosition * data_ps;
    void * next_element_pv;

}t_ssnake_Position;
int main()
{
    t_eReturnCode Ret_e;
    t_sPosition position1 = {1,2};
    t_sPosition position2 = {5,6};
    t_ssnake_Position *SnakePo;
    t_sLinkedList *snakelist;
    snakelist = LinkList_CreatLinkedList(sizeof(t_sPosition));
    LinkList_AddElement(snakelist, &position1,0);
    LinkList_AddElement(snakelist, &position2,0);
    SnakePo = snakelist->first_elment_pv;
    printf("%d", SnakePo->data_ps->positionX);


    return 0;
}*/
    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    // ********************************************************************
    // *                      Defines
    // ********************************************************************

    // ********************************************************************
    // *                      Types
    // ********************************************************************
    typedef struct
    {
        void *data_pv;
        void *next_struct_pv;
    } t_sElement;
    typedef struct
    {
        t_sElement * first_elment_pv;
        t_sElement * last_element_pv;
        t_uint16 size_struct_u16;
        t_uint16 nbr_element_u16;

    } t_sLinkedList;
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
    /**
     * @brief       Create a linked list
     * @details     allocate a t_sPile_ps pointor for the first element of f_list_ps and the last one.\n
     *              We can know the size of the linkedlist thanks to size_ts
     *              We can know the place in memory for t_sPile
     *              and fill in with f_data_vp.
     *
     * @param[in]   f_data_size : place in memory for a typedef struct
     * @param[out]  LinkedList : to mangage the linked list, find the head or the tail
     *
     * @retval      LINKLIST_FUNCTION_DONE          @copydoc LINKLIST_FUNCTION_DONE
     * @retval      FUNCTION_NOT_FINISH             @copydoc FUNCTION_NOT_FINISH
     * @retval      FUNCTION_UNDONE                 @copydoc FUNCTION_UNDONE
     * @retval      ERREUR_PTR_NULL                 @copydoc ERREUR_PTR_NULL
     * @retval      ERREUR_ALLOC                    @copydoc ERREUR_ALLOC
     */
    t_sLinkedList *LinkList_CreatLinkedList(t_uint16 f_size_struct_u16);
    /**
     * @brief       Add an element of the list
     * @details     Can add an element to the list whatever it is, unless f_position_ui is bigger or lower than the lenth list.\n
     *              At the end of the list\n
     *              If f_position_si = 0 we add at the beginning of linked list, the first element becoming the second
     *              If f_position_si = -1 we add at the end of linked list, the  last element becoming the "second last"
                    Else the client wants to add inside in the array if 2 it's the third element etc
     *
     * @param[in]   f_list_ps : Linked list.\n
     * @param[in]   f_element_ps : Data to add in the linked list, it's t_sPile type.\n
     * @param[out]  none
     *
     * @retval      LINKLIST_FUNCTION_DONE                   @copydoc LINKLIST_FUNCTION_DONE
     * @retval      FUNCTION_NOT_FINISH             @copydoc FUNCTION_NOT_FINISH
     * @retval      FUNCTION_UNDONE                 @copydoc FUNCTION_UNDONE
     * @retval      ERREUR_PTR_NULL                 @copydoc ERREUR_PTR_NULL
     * @retval      ERREUR_ALLOC                    @copydoc ERREUR_ALLOC
    */
     t_eReturnCode LinkList_AddElement(t_sLinkedList *f_linkedlist_ps, void * f_data_pv, t_uint8 f_place_u8);
    /**
     * @brief       Remplace a specific element of the list
     * @details     Can remplace an element to the list whatever it is, unless f_position_ui is bigger or lower than the lenth list.\n
     *              If f_position_si = 0 we replace at the beginning of linked list, the first element becoming the second
     *              If f_position_si = -1 we replace at the end of linked list, the  last element becoming the "second last"
                    Else the client wants to replace inside in the array if 2 it's the third element etc
     *
     * @param[in]   f_list_ps : Linked list.\n
     * @param[in]   f_data_vp : Data to add in the linked list.\n
     * @param[in]   f_position_ui : where to insert the new element
     *
     * @param[out]  none
     *
     * @retval      LINKLIST_FUNCTION_DONE                   @copydoc LINKLIST_FUNCTION_DONE
     * @retval      FUNCTION_NOT_FINISH             @copydoc FUNCTION_NOT_FINISH
     * @retval      FUNCTION_UNDONE                 @copydoc FUNCTION_UNDONE
     * @retval      ERREUR_PTR_NULL                 @copydoc ERREUR_PTR_NULL
     * @retval      ERREUR_ALLOC                    @copydoc ERREUR_ALLOC
    */
   t_eReturnCode LinkList_ReplaceElement(t_sLinkedList *f_linkedlist_ps, void *f_data_pv, t_uint8 f_place_u8);
      /***********************************************************/
    /**
     * @brief       Return an element from linked list .\n NOT WORKING
     * @details     Throughout a pointer f_return_element_ps we point to the dedicate zone
     *              The client has to say which element he wants with f_place_ui.\n
     *              If f_position_si = 0 we return  the first element becoming the second
     *              If f_position_si = -1 we return the  last element becoming the "second last"
     *              Else the client wants to return an element inside the array if 2 it's the third element etc
     *
     * @param[in]   f_list_ps : Linked list.\
     * @param[in]   f_return_element_ps : pointor the the right struct.\n
     * @param[in]   f_position_ui : where to insert the new element
     *
     * @param[out]  none
     *
     * @retval      LINKLIST_FUNCTION_DONE          @copydoc LINKLIST_FUNCTION_DONE
     * @retval      FUNCTION_NOT_FINISH             @copydoc FUNCTION_NOT_FINISH
     * @retval      FUNCTION_UNDONE                 @copydoc FUNCTION_UNDONE
     * @retval      ERREUR_PTR_NULL                 @copydoc ERREUR_PTR_NULL
     * @retval      ERREUR_ALLOC                    @copydoc ERREUR_ALLOC
    */
    //t_eReturnCode LinkListGetElement(t_sLinkedList *f_list_ps, void *f_return_element_ps, unsigned int f_position_ui);

    /**
     * @brief       Erase a specific element of the list
     * @details     Can erase an element to the list whatever it is, unless f_position_ui is bigger or lower than the lenth list.\n
     *              If f_position_si = 0 we erase at the beginning of linked list, the first element becoming the second
     *              If f_position_si = -1 we erase at the end of linked list, the  last element becoming the "second last"
                    Else the client wants to erase inside in the array if 2 it's the third element etc
     *
     * @param[in]   f_list_ps : Linked list.\n
     * @param[in]   f_data_vp : Data to add in the linked list.\n
     * @param[in]   f_position_ui : where to insert the new element
     *
     * @param[out]  none
     *
     * @retval      LINKLIST_FUNCTION_DONE                   @copydoc LINKLIST_FUNCTION_DONE
     * @retval      FUNCTION_NOT_FINISH             @copydoc FUNCTION_NOT_FINISH
     * @retval      FUNCTION_UNDONE                 @copydoc FUNCTION_UNDONE
     * @retval      ERREUR_PTR_NULL                 @copydoc ERREUR_PTR_NULL
     * @retval      ERREUR_ALLOC                    @copydoc ERREUR_ALLOC
    */
     t_eReturnCode LinkList_EraseElement(t_sLinkedList *f_linkedlist_ps, t_uint8 f_place_u8);
    /**
     * @brief       Free linked list and desallocate memory
     * @details     We search every element of f_list_ps and free it.\n
     *
     * @param[in]   f_list_ps : Linked list.\n
     *
     * @param[out]  none
     *
     * @retval      LINKLIST_FUNCTION_DONE          @copydoc LINKLIST_FUNCTION_DONE
     * @retval      FUNCTION_NOT_FINISH             @copydoc FUNCTION_NOT_FINISH
     * @retval      FUNCTION_UNDONE                 @copydoc FUNCTION_UNDONE
     * @retval      ERREUR_PTR_NULL                 @copydoc ERREUR_PTR_NULL
     * @retval      ERREUR_ALLOC                    @copydoc ERREUR_ALLOC
    */
     t_eReturnCode LinkList_FreeList(t_sLinkedList *f_linkedlist_ps);
#endif                   /* LinkedList_H */
//****************************************************************************
// End of File
//****************************************************************************

