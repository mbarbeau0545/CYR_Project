/*******************************************************************/
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

// ********************************************************************
// *                      Includes
// ********************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ModuleLog.h"
// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************
const char *address_info_file_pc;
const char *address_data_file_pc;
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
char *FormatActualHour() {
    static char heure_formatee[80];
    time_t temps_actuel;
    struct tm *temps_info;

    time(&temps_actuel);
    temps_info = localtime(&temps_actuel);
    strftime(heure_formatee, sizeof(heure_formatee), "%Y-%m-%d %H:%M:%S", temps_info);

    return heure_formatee;
}
//*********************************************************************
t_eModLog_EtatFonction ModLog_InitializeInfoFile(const char* f_address_file_client_pc)
{

    //manage time
    char *format_hour_pc = FormatActualHour();
    address_info_file_pc = f_address_file_client_pc;
    t_eModLog_EtatFonction state_initializeInfoFile_e = ModLog_FUNCTION_UNDONE;
    FILE *fpData;
    if(f_address_file_client_pc == NULL)
    {
        state_initializeInfoFile_e = ModLog_ERREUR_PTR_NULL;
        printf("can't find the path\n");
    }
    else
    {
        fpData = fopen(f_address_file_client_pc, "w");
        if(fpData == NULL)
        {
            state_initializeInfoFile_e = ModLog_ERREUR_PTR_NULL;
            printf("In initializeFile, none pointer to %s\n", f_address_file_client_pc);
        }
        else
        {
            state_initializeInfoFile_e = ModLog_FUNCTION_DONE;
             fprintf(fpData," * ******************************************************************\n"
                    " * Copyright (C) 2023 - \n"
                    " *\n"
                    " * It should not be reproduced in any medium or used in any way\n * without prior written consent of AUDMBA\n"
                    " * ******************************************************************\n"
                    " * This document repertory every information and error\n"
                    " * Last update : %s\n"
                    " * *****************************************************************\n\n",format_hour_pc);
        }
        fclose(fpData);
    }

    return state_initializeInfoFile_e;
}

//*********************************************************************
t_eModLog_EtatFonction ModLog_InitializeDataFile(const char* f_address_file_client_pc)
{
    char *format_hour_pc = FormatActualHour();
    address_data_file_pc = f_address_file_client_pc;
    t_eModLog_EtatFonction state_initializeDataFile_e = ModLog_FUNCTION_UNDONE;
    FILE *fpData;
    if(f_address_file_client_pc == NULL)
    {
        state_initializeDataFile_e = ModLog_ERREUR_PTR_NULL;
        printf("can't find the path\n");
    }
    else
    {
        fpData = fopen(f_address_file_client_pc, "w");
        if(fpData == NULL)
        {
            state_initializeDataFile_e = ModLog_ERREUR_PTR_NULL;
            printf("In initializeFile, none pointer to %s\n", f_address_file_client_pc);
        }
        else
        {
            state_initializeDataFile_e = ModLog_FUNCTION_DONE;
             fprintf(fpData," * ******************************************************************\n"
                    " * Copyright (C) 2023 - \n"
                    " *\n"
                    " * It should not be reproduced in any medium or used in any way\n * without prior written consent of AUDMBA\n"
                    " * ******************************************************************\n"
                    " * This document repertory every information and error\n"
                    " * Last update : %s\n"
                    " * *****************************************************************\n\n",format_hour_pc);
        }
        fclose(fpData);
    }

    return state_initializeDataFile_e;
}

//*********************************************************************
t_eModLog_EtatFonction ModLog_WriteInfoInFile(const char *f_msg_pc)
{
    t_eModLog_EtatFonction state_WriteInfoInFile_e = ModLog_FUNCTION_UNDONE;
    FILE *fpData;
    fpData = fopen(address_info_file_pc, "a+");
    if(fpData == NULL || f_msg_pc == NULL)
    {
        state_WriteInfoInFile_e = ModLog_ERREUR_PTR_NULL;
        printf("In WriteInfoInFile, none pointer\n");
    }
    else
    {
        fprintf(fpData, "[Info] :%s\n", f_msg_pc);
        state_WriteInfoInFile_e = ModLog_FUNCTION_DONE;
        fclose(fpData);
    }
    return state_WriteInfoInFile_e;
}

//*********************************************************************
t_eModLog_EtatFonction ModLog_WriteErrorInFile(const char *f_msg_pc)
{
    t_eModLog_EtatFonction state_WriteErrorInFile_e = ModLog_FUNCTION_UNDONE;
    FILE *fpData;
    fpData = fopen(address_info_file_pc, "a");
    if(fpData == NULL || f_msg_pc == NULL)
    {
        state_WriteErrorInFile_e = ModLog_ERREUR_PTR_NULL;
        printf("In WriteErrorInFile, none pointer\n");
    }
    else
    {
        fprintf(fpData,"[Error] : %s\n", f_msg_pc);
        fclose(fpData);
        state_WriteErrorInFile_e = ModLog_FUNCTION_DONE;
    }
    return state_WriteErrorInFile_e;
}

//*********************************************************************
t_eModLog_EtatFonction ModLog_WriteDataInFile(t_eModLog_ReturnType f_type_e, const char *f_msg_pc, void *f_data_pv)
{
    t_eModLog_EtatFonction state_WriteInfoInFile = ModLog_FUNCTION_UNDONE;
    FILE *fpData;
    fpData = fopen(address_data_file_pc, "a+");
    if(fpData == NULL || f_msg_pc == NULL || f_data_pv == NULL || f_type_e < 0 )
    {
        state_WriteInfoInFile = ModLog_ERREUR_PTR_NULL;
        printf("In WriteInfoInFile, none pointer\n");
    }
    else
    {
        switch(f_type_e)
        {
            case ModLog_INT:
            {
                int *int_value_pi = (int *)f_data_pv;
                fprintf(fpData, "%s : %d\n", f_msg_pc, *int_value_pi);
                state_WriteInfoInFile = ModLog_FUNCTION_DONE;
                break;
            }
            case ModLog_CHAR:
            {
                char *char_value_pc = (char *)f_data_pv;
                fprintf(fpData, "%s : %c\n", f_msg_pc, *char_value_pc);
                state_WriteInfoInFile = ModLog_FUNCTION_DONE;
                break;
            }
            case ModLog_STRING:
            {   char *string_value[100];
                strcpy(string_value, (char *)f_data_pv);
                fprintf(fpData, "%s : %s\n", f_msg_pc, &string_value);
                state_WriteInfoInFile = ModLog_FUNCTION_DONE;
                break;
            }
            case ModLog_FLOAT:
            {
                float *float_value_pf = (float *)f_data_pv;
                fprintf(fpData, "%s : %f\n", f_msg_pc, *float_value_pf);
                state_WriteInfoInFile = ModLog_FUNCTION_DONE;
                break;
            }
            case ModLog_ADDRESS:
            {

                fprintf(fpData, "%s : %p\n", f_msg_pc, f_data_pv);
                state_WriteInfoInFile = ModLog_FUNCTION_DONE;
                break;
            }
            case ModLog_UNSIGNED_INT:
            {
                unsigned int *ui_value_pui = (unsigned int *)f_data_pv;
                fprintf(fpData, "%s :%u\n", f_msg_pc, *ui_value_pui);
                state_WriteInfoInFile = ModLog_FUNCTION_DONE;
                break;
            }
            default:
                printf("ModLogSearchKey : t_eModLog_ReturnType is not valid");
                break;

        }

        fclose(fpData);
    }
    return state_WriteInfoInFile;
}


t_eModLog_EtatFonction ModLog_SearchFor(const char *f_msg_to_search_pc, const char *f_file_to_read_pc, const char *f_file_to_write_pc)
{
    t_eModLog_EtatFonction state_WriteInfoInFile = ModLog_FUNCTION_UNDONE;
    FILE *fpData;
    FILE *fpWriteSearch;
    char line[MAX_BUFFER];
    fpWriteSearch = fopen(f_file_to_write_pc, "w");
    fpData = fopen(f_file_to_read_pc, "r");
        if(fpData == NULL || fpWriteSearch == NULL  || f_file_to_read_pc == NULL || f_file_to_write_pc == NULL)
    {
        state_WriteInfoInFile = ModLog_ERREUR_PTR_NULL;
        printf("In WriteInfoInFile, none pointer\n");
    }
    else
    {
        while(fgets(line,MAX_BUFFER,fpData) != NULL)
        {
                if(strstr(line, f_msg_to_search_pc)!= NULL)
                {
                    fprintf(fpWriteSearch,"%s",line);
                }
        }
        state_WriteInfoInFile = ModLog_FUNCTION_DONE;
    }
    return state_WriteInfoInFile;
}
