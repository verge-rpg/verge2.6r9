/*
Copyright (C) 1998 BJ Eirich (aka vecna)
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

// startup.c
// Copyright (C) 1998 BJ Eirich

#include <time.h>
#include <stdarg.h> // va_*
#include <stdlib.h>
#include "SDL.h"

//#define MAIN_H
#include "verge.h"

// in VERGE.CPP

extern int  VMain();

// Data

bool bActive;

static unsigned char vergepal[]=
{
    0x00,0x00,0x00,0x02,0x02,0x02,0x03,0x03,0x03,0x05,0x05,0x05,0x07,
        0x07,0x07,0x09,0x09,0x09,0x0a,0x0a,0x0a,0x0c,0x0c,0x0c,0x0e,0x0e,
        0x0e,0x0f,0x0f,0x0f,0x11,0x11,0x11,0x13,0x13,0x13,0x15,0x15,0x15,
        0x16,0x16,0x16,0x18,0x18,0x18,0x1a,0x1a,0x1a,0x1c,0x1c,0x1c,0x1d,
        0x1d,0x1d,0x1f,0x1f,0x1f,0x21,0x21,0x21,0x22,0x22,0x22,0x24,0x24,
        0x24,0x26,0x26,0x26,0x28,0x28,0x28,0x29,0x29,0x29,0x2b,0x2b,0x2b,
        0x2e,0x2e,0x2e,0x31,0x31,0x31,0x34,0x34,0x34,0x36,0x36,0x36,0x39,
        0x39,0x39,0x3c,0x3c,0x3c,0x3f,0x00,0x00,0x3b,0x00,0x00,0x38,0x00,
        0x00,0x35,0x00,0x00,0x32,0x00,0x00,0x2f,0x00,0x00,0x2c,0x00,0x00,
        0x29,0x00,0x00,0x26,0x00,0x00,0x22,0x00,0x00,0x1f,0x00,0x00,0x1c,
        0x00,0x00,0x19,0x00,0x00,0x16,0x00,0x00,0x13,0x00,0x00,0x10,0x00,
        0x00,0x3f,0x36,0x36,0x3f,0x2e,0x2e,0x3f,0x27,0x27,0x3f,0x1f,0x1f,
        0x3f,0x17,0x17,0x3f,0x10,0x10,0x3f,0x08,0x08,0x3f,0x00,0x00,0x11,
        0x0b,0x06,0x13,0x0d,0x07,0x15,0x0f,0x09,0x17,0x11,0x0a,0x18,0x13,
        0x0b,0x1a,0x15,0x0c,0x1c,0x17,0x0e,0x1e,0x19,0x0f,0x3f,0x3f,0x36,
        0x3f,0x3f,0x2e,0x3f,0x3f,0x27,0x3f,0x3f,0x1f,0x3f,0x3e,0x17,0x3f,
        0x3d,0x10,0x3f,0x3d,0x08,0x3f,0x3d,0x00,0x39,0x36,0x00,0x33,0x31,
        0x00,0x2d,0x2b,0x00,0x27,0x27,0x00,0x21,0x21,0x00,0x1c,0x1b,0x00,
        0x16,0x15,0x00,0x10,0x10,0x00,0x34,0x3f,0x17,0x31,0x3f,0x10,0x2d,
        0x3f,0x08,0x28,0x3f,0x00,0x24,0x39,0x00,0x20,0x33,0x00,0x1d,0x2d,
        0x00,0x18,0x27,0x00,0x36,0x3f,0x36,0x2e,0x3d,0x2e,0x27,0x3b,0x27,
        0x1f,0x39,0x1f,0x17,0x36,0x17,0x0f,0x34,0x0f,0x08,0x32,0x08,0x00,
        0x30,0x00,0x00,0x2d,0x00,0x00,0x2b,0x00,0x00,0x28,0x00,0x00,0x26,
        0x00,0x00,0x23,0x00,0x00,0x21,0x00,0x00,0x1e,0x00,0x00,0x1c,0x00,
        0x00,0x19,0x00,0x00,0x17,0x00,0x00,0x14,0x00,0x00,0x12,0x00,0x00,
        0x0f,0x00,0x02,0x0d,0x02,0x03,0x0a,0x03,0x05,0x08,0x05,0x36,0x3f,
        0x3f,0x2e,0x3f,0x3f,0x27,0x3f,0x3f,0x1f,0x3f,0x3f,0x17,0x3f,0x3f,
        0x0f,0x3f,0x3f,0x08,0x3f,0x3f,0x00,0x3f,0x3f,0x00,0x39,0x39,0x00,
        0x33,0x33,0x00,0x2d,0x2d,0x00,0x27,0x27,0x00,0x22,0x22,0x00,0x1c,
        0x1c,0x00,0x16,0x16,0x00,0x10,0x10,0x17,0x2f,0x3f,0x10,0x2c,0x3f,
        0x08,0x2a,0x3f,0x00,0x27,0x3f,0x00,0x23,0x39,0x00,0x1f,0x33,0x00,
        0x1b,0x2d,0x00,0x17,0x27,0x36,0x36,0x3f,0x2e,0x2f,0x3f,0x27,0x27,
        0x3f,0x1f,0x20,0x3f,0x17,0x18,0x3f,0x10,0x10,0x3f,0x08,0x09,0x3f,
        0x00,0x01,0x3f,0x00,0x00,0x3f,0x00,0x00,0x3b,0x00,0x00,0x38,0x00,
        0x00,0x35,0x00,0x00,0x32,0x00,0x00,0x2f,0x00,0x00,0x2c,0x00,0x00,
        0x29,0x00,0x00,0x26,0x00,0x00,0x22,0x00,0x00,0x1f,0x00,0x00,0x1c,
        0x00,0x00,0x19,0x00,0x00,0x16,0x00,0x00,0x13,0x00,0x00,0x10,0x0d,
        0x08,0x00,0x0f,0x09,0x00,0x12,0x0a,0x00,0x14,0x0b,0x00,0x16,0x0c,
        0x00,0x19,0x0d,0x00,0x1b,0x0e,0x00,0x1e,0x0f,0x00,0x20,0x10,0x00,
        0x22,0x11,0x00,0x25,0x12,0x00,0x28,0x15,0x03,0x2c,0x18,0x06,0x2f,
        0x1b,0x09,0x32,0x1e,0x0c,0x35,0x21,0x0e,0x39,0x24,0x11,0x3c,0x27,
        0x14,0x3f,0x2a,0x17,0x3f,0x2e,0x1c,0x3f,0x31,0x22,0x3f,0x35,0x27,
        0x3f,0x38,0x2c,0x22,0x1c,0x12,0x25,0x1f,0x14,0x29,0x22,0x17,0x2c,
        0x25,0x19,0x2f,0x28,0x1c,0x32,0x2a,0x1e,0x36,0x2d,0x20,0x39,0x30,
        0x23,0x3c,0x33,0x25,0x3f,0x3a,0x37,0x3f,0x38,0x34,0x3f,0x36,0x31,
        0x3f,0x35,0x2f,0x3f,0x33,0x2c,0x3f,0x31,0x29,0x3f,0x2f,0x27,0x3f,
        0x2e,0x24,0x3f,0x2c,0x20,0x3f,0x29,0x1c,0x3f,0x27,0x18,0x3c,0x25,
        0x17,0x3a,0x23,0x16,0x37,0x22,0x15,0x34,0x20,0x14,0x32,0x1f,0x13,
        0x2f,0x1e,0x12,0x2d,0x1c,0x11,0x2a,0x1a,0x10,0x28,0x19,0x0f,0x27,
        0x18,0x0e,0x24,0x17,0x0d,0x22,0x16,0x0c,0x20,0x14,0x0b,0x1d,0x13,
        0x0a,0x1b,0x12,0x09,0x17,0x10,0x08,0x15,0x0f,0x07,0x12,0x0e,0x06,
        0x10,0x0c,0x06,0x0e,0x0b,0x05,0x0a,0x08,0x03,0x3f,0x00,0x00,0x3f,
        0x04,0x00,0x3f,0x08,0x00,0x3f,0x0d,0x00,0x3f,0x11,0x00,0x3f,0x15,
        0x00,0x3f,0x19,0x00,0x3f,0x1d,0x00,0x3f,0x22,0x00,0x3f,0x26,0x00,
        0x3f,0x2a,0x00,0x3f,0x2e,0x00,0x3f,0x32,0x00,0x3f,0x37,0x00,0x3f,
        0x3b,0x00,0x3f,0x3f,0x00,0x3f,0x2f,0x00,0x36,0x28,0x00,0x2d,0x22,
        0x00,0x24,0x1b,0x00,0x1b,0x14,0x00,0x12,0x0d,0x00,0x09,0x07,0x00,
        0x00,0x00,0x00,0x29,0x00,0x28,0x23,0x00,0x2b,0x1d,0x00,0x2f,0x17,
        0x00,0x32,0x12,0x00,0x35,0x0c,0x00,0x38,0x06,0x00,0x3c,0x3f,0x3f,
        0x3f,0x3f
}; // gah!

int    hicolour     =0; // bleh --tSB
int  fullscreenmode =1; // ditto

char    joyflag     =0;

int     vidxres     =0;
int	    vidyres     =0;

string_k	startmap;   // start map

// ================================= Code ====================================

void Sys_Error(const char* format, ...)
{
    va_list argptr;
    static char string[1024];
    
    va_start(argptr, format);
    vsprintf(string, format, argptr);
    va_end(argptr);
    
    // <aen> why can't I nest another va() in here?
    Log::Writen("Sys: Exiting with message: ");
    Log::Write(string);
    
    ShutdownTimer();
    input.ShutDown();
    gfx.ShutDown();
    ShutdownSound();

    SDL_Quit();

    printf("%s",string);
    fflush(stdout);
    
    FreeAllMemory();
    
    Log::Write("Exit!");
    exit(-1);
}

void InitializeDefaults()
{
    vidxres=320;                         // default res is 320x240
    vidyres=240;
    
    memset(bindarray, 0, sizeof(bindarray)); // clear this here so we don't trigger random events on the first keypress
    
    startmap=""; //test.map";            // default startup map
    
    gfx.VSync(false);                    // no vsync by default
}

// <aen, apr 21>
// + added these few static routines and made ParseStartupFiles() use'em

static VFILE *user_cfg_file=0;
static char parse_str[256];

static char *parse_cfg_token()
{ vscanf(user_cfg_file, "%s", parse_str); return parse_str; }

// compares string against parse_str (grabbed by parse_cfg_token())
// 0=mismatch, 1=match
static int parse_match(char *str)
{ return !strcmp(parse_str, str); }

// zero error correcting or detection; fix <aen, apr 21>
void ParseStartupFiles()
{
    user_cfg_file = vopen("user.cfg");
    if (!user_cfg_file)
    {
        return;
    }
    
    while (1)
    {
        parse_cfg_token();
        
        // mounts a pack file; up to 3? (perhaps gaurd against more?)
        if (parse_match("mount"))
        {
            MountVFile(parse_cfg_token());
            continue;
        }
        // set video resolution
        else if (parse_match("vidmode"))
        {
            vidxres = atoi(parse_cfg_token());
            vidyres = atoi(parse_cfg_token());
            
            continue;
        }
        // log to VERGE.LOG
        else if (parse_match("log"))
        {
            Log::Enable();
            continue;
        }
        // map VERGE.EXE will run first when executed
        else if (parse_match("startmap"))      
        {
            startmap = parse_cfg_token();
            continue;
        } // --tSB why not?
        // 0=auto detect, 1=???, 2=???, 3=nosound
        else if (parse_match("sound_device"))
        {
            parse_cfg_token();
            //    	md_device = (UWORD)atoi(parse_cfg_token());
            continue;
        }
        // sound lib setting
        else if (parse_match("mixrate"))
        {
            //    	sfx_mixrate = (word)atoi(parse_cfg_token());
            continue;
        }
        // sound lib setting
        else if (parse_match("safemode"))
        {
            //        sfx_safemode=1;
            continue;
        }
        else if (parse_match("dmabufsize"))
        {
            parse_cfg_token();
            continue;
        }
        // sound lib setting
        else if (parse_match("force8bit"))
        { continue; }
        // sound lib setting
        else if (parse_match("forcemono"))
        { continue; }
        else if (parse_match("hicolor"))
        {
            hicolour=1;
            continue;
        }
        else if (parse_match("window"))
        {
            fullscreenmode=0;
            continue;
        }
        else if (parse_match("vsync"))
        {
            gfx.VSync(true);
            continue;
        }
        
        // unknown command, assume end
        break;
    }
    
    // done parsing config
    vclose(user_cfg_file);
}

void ParseAutoCFG()
{
    VFILE*	vf;
    int i;
    
    vf	=vopen("auto.cfg");
    if (!vf) return;
    
    while (1)
    {
        char temp[256+1]={0};
        vgets(temp, 256, vf);
        temp[256]='\0';
        
        for (i=0; i<strlen(temp); i++) {
            if (temp[i]==10 || temp[i]==13)
                temp[i]=0;
        }
        if (strlen(temp)<2) {
            break;
        }
        //cmd=temp;
//        Console_SendCommand(temp);
    }
    vclose(vf);
}

void LoadTransTable()
{ 
    VFILE*	vf;
    u8*   translucency_table;
    
    if (gfx.bpp!=1) return; // why bother?
       
    Log::Writen("Loading 8 bit translucency table");
    
    vf = vopen("TRANS.TBL");
    if (!vf)
    {
        Sys_Error("\ntrans.tbl not found");
    }
    
    translucency_table = (u8 *) valloc(256*256, "translucency_table", OID_TEMP);
    
    vread(translucency_table, 256*256, vf);
    gfx.InitLucentLUT(translucency_table); // weird, I know. ;)
    vfree(translucency_table);
    vclose(vf);

    Log::Write("...OK");
}

// --tSB moved Conlib_Ver() to conlib.h (that's the only place it's needed anyway :P

// Moved CheckMessages to verge.cpp --andy

void InitSystems()
{
    Log::Init();

    Log::Write("v2.6 startup. Logfile initialized.");
    
    Log::Writen("Initing SDL");
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_NOPARACHUTE);
    atexit(SDL_Quit);
    SDL_WM_SetCaption("Verge",0);
    Log::Write("...OK"); 

    LoadTransTable();

    srand(SDL_GetTicks());

    Log::Writen("Sys: Initializing keyboard handler.");
    if (!input.Init())
        Sys_Error("\nError initializing keyboard handler");
    memset(bindarray,0,256); // no keys bound yet
    input.ClipMouse(SRect(0,0,vidxres,vidyres));
    Log::Write("...OK");
        
    Log::Writen("Sys: Initializing music system.");
    InitSound();
    Log::Write("...OK");
    
    Log::Write("Sys: Initializing graphics.");
    if (!gfx.Init(vidxres, vidyres,hicolour!=0?16:8,fullscreenmode?true:false))
        Sys_Error("\nError initizlizing graphics");
    if (!gfx.SetPalette(vergepal))
        Sys_Error("\nError setting the palette");
    Log::Write("...OK");
    
    Log::Writen("Sys: Initializing timer. Set 100hz.");
    if (!InitTimer())
        Sys_Error("\nError initing timer");
    Log::Write("...OK");

    ParseAutoCFG();
}

int main(int argc,char* args[])
{
    if (1 == argc)
    {
        printf("VERGE v."VERSION" build "__DATE__" at "__TIME__". \n");
        printf("Copyright (C)1998 vecna \n");
    }
    
    // ---Directly from the DOS version -- used to be in verge.cpp but it fits here better. --tSB
    InitializeDefaults();
    ParseStartupFiles();
    
    InitSystems();
    
    return VMain();	
}