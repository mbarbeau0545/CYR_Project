 /* ******************************************************************
 * Copyright (C) 2023 - AUDMBA
 *
 * This document is AUDMBA property.
 * It should not be reproduced in any medium or used in any way
 * without prior written consent of AUDMBA
 * ******************************************************************/
/**
 * @file        ModuleLog.h
 * @brief       The purpose of this file is to add log at any Project\n
 * @details     This file can be used to manipulate Log.\n
 *              Write errror in a file
 *              Write info in a file
 *              Write Data in a file
 *              It the doclog doesn't exit, it will be create
 *
 * @author      AUDMBA
 * @date        23/10/2023
 * @version     0.0
 */
#ifndef MODULELOG_H
#define MODULELOG_H
    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <time.h>
    #include "ModuleLog.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define MAX_BUFFER 256
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    typedef enum
    {
        ModLog_FUNCTION_DONE = 0,
        ModLog_FUNCTION_UNDONE = -1,
        ModLog_FUNCTION_NOT_FINISH = 1,
        ModLog_ERREUR_ALLOC = -2,
        ModLog_ERREUR_PTR_NULL = -3,
    }t_eModLog_EtatFonction;
    typedef enum
    {
        ModLog_INT,
        ModLog_CHAR,
        ModLog_FLOAT,
        ModLog_STRING,
        ModLog_ADDRESS,
        ModLog_UNSIGNED_INT,
    }t_eModLog_ReturnType;
    // ********************************************************************
    // *                      Constants
    // ********************************************************************

    // ********************************************************************
    // *                      Variables
    // ********************************************************************

    //*********************************************************************
    //                      Local functions - Prototypes
    //*********************************************************************

    //*********************************************************************
    //                      Local functions - Implementation
    //*********************************************************************

    /**
     * @brief       Open a text file to write info and error in it
     * @details     The client has to put the path of the file.\n
     *              If the file does not exits but folders does, the file will be create.\n
     *
     * @param[in] f_address_file_client_pc : the file's path start from the current project
     * @param[out]
     *
     * @retval      ModLog_FUNCTION_DONE                   @copydoc ModLog_FUNCTION_DONE
     * @retval      ModLog_FUNCTION_NOT_FINISH             @copydoc ModLog_FUNCTION_NOT_FINISH
     * @retval      ModLog_FUNCTION_UNDONE                 @copydoc ModLog_FUNCTION_UNDONE
     * @retval      ModLog_ERREUR_PTR_NULL                 @copydoc ModLog_ERREUR_PTR_NULL
     * @retval      ModLog_ERREUR_ALLOC                    @copydoc ModLog_ERREUR_ALLOC
     */
    t_eModLog_EtatFonction ModLog_InitializeInfoFile(const char* f_address_file_client_pc);
    //********************************************************************************************/
    /**
     * @brief       Open a text file to write only data in it
     * @details     The client has to put the path of the file.\n
     *              If the file does not exits but folders exist, the file will be create.\n
     *
     * @param[in] f_address_file_client_pc : the file's path from the current project
     * @param[out]
     *
     * @retval      ModLog_FUNCTION_DONE                   @copydoc ModLog_FUNCTION_DONE
     * @retval      ModLog_FUNCTION_NOT_FINISH             @copydoc ModLog_FUNCTION_NOT_FINISH
     * @retval      ModLog_FUNCTION_UNDONE                 @copydoc ModLog_FUNCTION_UNDONE
     * @retval      ModLog_ERREUR_PTR_NULL                 @copydoc ModLog_ERREUR_PTR_NULL
     * @retval      ModLog_ERREUR_ALLOC                    @copydoc ModLog_ERREUR_ALLOC
     */
    t_eModLog_EtatFonction ModLog_InitializeDataFile(const char* f_address_file_client_pc);
    //********************************************************************************************/
    /**
     * @brief       Open a text file to write only Info in it
     * @details     The client only has to write whatever he wants thanks to msg.\n
     *              It will be better if the client precise which Function of which file is he writing.\n
     *
     * @param[in] f_msg_pc : msg's client he wants to write in his log
     * @param[out]
     *
     * @retval      ModLog_FUNCTION_DONE                   @copydoc ModLog_FUNCTION_DONE
     * @retval      ModLog_FUNCTION_NOT_FINISH             @copydoc ModLog_FUNCTION_NOT_FINISH
     * @retval      ModLog_FUNCTION_UNDONE                 @copydoc ModLog_FUNCTION_UNDONE
     * @retval      ModLog_ERREUR_PTR_NULL                 @copydoc ModLog_ERREUR_PTR_NULL
     * @retval      ModLog_ERREUR_ALLOC                    @copydoc ModLog_ERREUR_ALLOC
     */
    t_eModLog_EtatFonction ModLog_WriteInfoInFile(const char *f_msg_pc);
    //********************************************************************************************/
    /**
     * @brief       Open a text file to write only Erreur in it
     * @details     The client only has to write whatever he wants thanks to f_msg_pc.\n
     *              It will be better if the client precise which Function of which file is he writing.\n
     *
     * @param[in] f_msg_pc : msg's client he wants to write in his log
     * @param[out]
     *
     * @retval      ModLog_FUNCTION_DONE                   @copydoc ModLog_FUNCTION_DONE
     * @retval      ModLog_FUNCTION_NOT_FINISH             @copydoc ModLog_FUNCTION_NOT_FINISH
     * @retval      ModLog_FUNCTION_UNDONE                 @copydoc ModLog_FUNCTION_UNDONE
     * @retval      ModLog_ERREUR_PTR_NULL                 @copydoc ModLog_ERREUR_PTR_NULL
     * @retval      ModLog_ERREUR_ALLOC                    @copydoc ModLog_ERREUR_ALLOC
     */
    t_eModLog_EtatFonction ModLog_WriteErrorInFile(const char *f_msg_pc);
    //********************************************************************************************/
    /**
     * @brief       Open a text file to write only Data in it
     * @details     The client only has to write whatever he wants thanks to f_msg_pc.\n
     *              He can support his msg with f_data_pv, but his has to be a pointor
     *              It will be better if the client precise which Function of which file is he writing.\n
     *
     * @param[in] f_type_e : type of the data
     * @param[in] f_msg_pc : msg's client he wants to write in his log
     * @param[in] f_data_pv : data's client he wants to write in his log be careful to put the address !
     * @param[out]
     *
     * @retval      ModLog_FUNCTION_DONE                   @copydoc ModLog_FUNCTION_DONE
     * @retval      ModLog_FUNCTION_NOT_FINISH             @copydoc ModLog_FUNCTION_NOT_FINISH
     * @retval      ModLog_FUNCTION_UNDONE                 @copydoc ModLog_FUNCTION_UNDONE
     * @retval      ModLog_ERREUR_PTR_NULL                 @copydoc ModLog_ERREUR_PTR_NULL
     * @retval      ModLog_ERREUR_ALLOC                    @copydoc ModLog_ERREUR_ALLOC
     */
    t_eModLog_EtatFonction ModLog_WriteDataInFile(t_eModLog_ReturnType f_type_e, const char *f_msg_pc, void *f_data_pv);
        /**
     * @brief       Open a text file to write only the line where's keyword
     * @details     The client only has to search a specific line with a keyword : f_msg_to_search_pc\n
     *              In a file : f_file_to_read_pc and the program copied the line in a new file if it does not exist.\n

     *
     * @param[in] f_msg_to_search_pc : keyword to search\n
     * @param[in] f_file_to_read_pc : address to the file to search keyword\n
     * @param[in] f_file_to_write_pc : address to the file to write the line we've been searching\n
     * @param[out]
     *
     * @retval      ModLog_FUNCTION_DONE                   @copydoc ModLog_FUNCTION_DONE
     * @retval      ModLog_FUNCTION_NOT_FINISH             @copydoc ModLog_FUNCTION_NOT_FINISH
     * @retval      ModLog_FUNCTION_UNDONE                 @copydoc ModLog_FUNCTION_UNDONE
     * @retval      ModLog_ERREUR_PTR_NULL                 @copydoc ModLog_ERREUR_PTR_NULL
     * @retval      ModLog_ERREUR_ALLOC                    @copydoc ModLog_ERREUR_ALLOC
     */
    t_eModLog_EtatFonction ModLog_SearchFor(const char *f_msg_to_search_pc, const char *f_file_to_read_pc, const char *f_file_to_write_pc);
#endif // MODULELOG_H
