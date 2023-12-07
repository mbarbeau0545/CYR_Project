/*********************************************************************
 * @file        main.c
 * @brief
 * @details     TemplateDetailsDescription.\n
 *
 * @author      AUDMBA
 * @date        20/11/2023
 * @version     0.0
 */

// ********************************************************************
// *                      Includes
// ********************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Library/ModuleLog/ModuleLog.h"
#include "Config/TypeCommon.h"
//#include "SDL2/SDL.h"
#include "FishDsgn/fishDsgn.h"
#include "Config/Constant.h"

// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************
bool g_game_is_running = false; /*<manage the output if g_game_is_running = false*/

// ********************************************************************
// *                      Constants
// ********************************************************************

/**************************************
* Initaialize the log for this project
***************************************/

/**************************************
* Initaializewindow pointor
***************************************/
SDL_Window * g_window_ps = NULL;
SDL_Renderer * g_renderer_ps = NULL;
SDL_Window * g_screen_ps = NULL;


// ********************************************************************
// *                      Variables
// ********************************************************************

//****************************************************************************
//                      Local functions - Prototypes
//****************************************************************************
/**
 *
 *	@brief  Initialize Window for the game
 *	@details
 *
 *
 *	@params[in]   None
 *	@params[out]
 *
 *  @retval RC_OK			                   @copydoc RC_OK
 *  @retval RC_ERROR_MODULE_NOT_INITIALIZED    @copydoc RC_ERROR_MODULE_NOT_INITIALIZED
 */
static t_eReturnCode s_Main_InitializeWindow(void);
/****************************************************************************/
/**
 *
 *	@brief  Destroy Window for the game
 *	@details
 *
 *
 *	@params[in]   None
 *	@params[out]
 *
 *  @retval RC_OK			                   @copydoc RC_OK
 *  @retval RC_ERROR_MODULE_NOT_INITIALIZED    @copydoc RC_ERROR_MODULE_NOT_INITIALIZED
 */
static t_eReturnCode s_Main_DestroyWindow(void);
/****************************************************************************/
/**
 *
 *	@brief  Deal with exiting the game
*	@details
*
*
*	@params[in]   None
*	@params[out]
*
*  @retval RC_OK			                   @copydoc RC_OK
*  @retval RC_ERROR_MODULE_NOT_INITIALIZED    @copydoc RC_ERROR_MODULE_NOT_INITIALIZED
*/
static t_eReturnCode s_Main_ProcessInput(void);
/****************************************************************************/
//****************************************************************************
//                      Public functions - Implementation
//****************************************************************************

//****************************************************************************
//                      Local functions - Implementation
//****************************************************************************
/**************************************
* Main_InitializeWindow
***************************************/
static t_eReturnCode s_Main_InitializeWindow(void)
{
    t_eReturnCode Ret_e = RC_OK;
    ModLog_InitializeDataFile("../Docs/Log/LogMain.txt");
    ModLog_InitializeInfoFile("../Docs/Log/LogMain.txt");
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        ModLog_WriteInfoInFile("In main SLD couldn't initialize SDL module");
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(Ret_e == RC_OK)
    {

        g_window_ps = SDL_CreateWindow("MyWindow",                   //   Title
                                 SDL_WINDOWPOS_CENTERED,        //   Xposition in screen
                                 SDL_WINDOWPOS_CENTERED,        //   Yposition in screen
                                 WINDOW_WIDTH,                  //   Width window
                                 WINDOW_HEIGHT,                 //   Heigh wibdow
                                 SDL_WINDOW_SHOWN);
        if(!g_window_ps)
        {
            ModLog_WriteInfoInFile("In main, Error creating SDL Window, g_window_ps is null");
            Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
        }
        // = rendu
        g_renderer_ps = SDL_CreateRenderer(g_window_ps, -1, 0);
        if(!g_renderer_ps)
        {
            ModLog_WriteInfoInFile("In main, Error creating SDL WINdow, g_renderer_ps is null");
            Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
        }
    }
    //inittialize g_game_is_running to true
    if(Ret_e == RC_OK)
    {
        g_game_is_running = true;
    }
    return Ret_e;

}
/**************************************
* Main_DestroyWindow
***************************************/
static t_eReturnCode s_Main_DestroyWindow(void)
{
    t_eReturnCode Ret_e = RC_OK;
    SDL_DestroyRenderer(g_renderer_ps);
    SDL_DestroyWindow(g_window_ps);
    SDL_Quit();
    return Ret_e;
}
/**************************************
* Main_ProcessInput
***************************************/
static t_eReturnCode s_Main_ProcessInput(void)
{
    t_eReturnCode Ret_e = RC_OK;
    SDL_Event event_s;
    SDL_PollEvent(&event_s);
    switch(event_s.type)
    {
        case SDL_QUIT:      //event whever you click on the cross to close window
        {
            g_game_is_running = false;
            break;
        }
        case SDL_KEYDOWN:
        {
            if(event_s.key.keysym.sym == SDLK_ESCAPE)
            {
                g_game_is_running = false;
                break;
            }
        }
    }
    return Ret_e;
}

//****************************************************************************
// main
//****************************************************************************
int main(int argc, char *argv[])
{
    t_eReturnCode Ret_e = RC_OK;
    t_sFishMvmt_FishParameters fish_position_as[NBR_FISH];
    //initialize g_game_is_running
    Ret_e = s_Main_InitializeWindow();
    //ModLog_WriteDataInFile(ModLog_INT, "InitializeWindow report :",&Ret_e);
    //Ret_e = Main_Setup();
    if(Ret_e == RC_OK)
    {
        /*initialize setup for each fish and setup */
        Ret_e = FishDsgn_Setup(fish_position_as);
        if(Ret_e != RC_OK)
        {
            ModLog_WriteInfoInFile("In main,FishDsgn_Setup");
        }
        else
        {
            while(g_game_is_running == true)
            {
                Ret_e = s_Main_ProcessInput();
                if(Ret_e == RC_OK)
                {
                    Ret_e = FishDsgn_Render(fish_position_as, g_renderer_ps);
                    if(Ret_e == RC_OK)
                    {
                        Ret_e = FishDsgn_Update(fish_position_as);
                    }
                }
            }
            free(fish_position_as->bank_alignmt_fishes_ps);
            free(fish_position_as->bank_attract_fishes_ps);
            free(fish_position_as->bank_repulse_fishes_ps);
        }
    }
    s_Main_DestroyWindow();
    return EXIT_SUCCESS;
}
//****************************************************************************
// End of File
//****************************************************************************
