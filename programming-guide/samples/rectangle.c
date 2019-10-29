/*
 * ** rectangle.c: Sample program for mGNCS Programming Guide
 * **      A mGNCS application for mRect.
 * **
 * ** Copyright (C) 2009 FMSoft Technologies.
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
#include <mgncs/mgncs.h>

#define ID_RECT1  101
#define ID_RECT2  102
#define ID_RECT3  103
#define ID_RECT4  104

static BOOL mymain_onCreate(mWidget* self, DWORD add_data)
{
	//TODO : initialize
	return TRUE;
}

static void mymain_onClose(mWidget* self, int message)
{
	DestroyMainWindow(self->hwnd);
	PostQuitMessage(0);
}


//Propties for
static NCS_PROP_ENTRY rect1_props [] = {
    {NCSP_RECTANGLE_BORDERSIZE, 3},
    {NCSP_RECTANGLE_BORDERCOLOR, 0xFFFF0000},
    {NCSP_RECTANGLE_FILLCOLOR, 0x00000000},
	{0, 0}
};

static NCS_PROP_ENTRY rect2_props [] = {
    {NCSP_RECTANGLE_BORDERSIZE, 2},
    {NCSP_RECTANGLE_BORDERCOLOR, 0xFFFFFFF},
    {NCSP_RECTANGLE_FILLCOLOR, 0xFF0F0F0F},
	{0, 0}
};

static NCS_PROP_ENTRY rect3_props [] = {
    {NCSP_RECTANGLE_BORDERSIZE, 0},
    {NCSP_RECTANGLE_BORDERCOLOR, 0xFF0C0000},
    {NCSP_RECTANGLE_FILLCOLOR, 0xFF00FFFF},
	{0, 0}
};

static NCS_PROP_ENTRY rect4_props [] = {
    {NCSP_RECTANGLE_BORDERSIZE, 5},
    {NCSP_RECTANGLE_BORDERCOLOR, 0xFF0000FF},
    {NCSP_RECTANGLE_FILLCOLOR, 0xFF00FF00},
    {NCSP_RECTANGLE_XRADIUS, 4},
    {NCSP_RECTANGLE_YRADIUS, 4},
	{0, 0}
};

//Controls
static NCS_WND_TEMPLATE _ctrl_templ[] = {
	{
		NCSCTRL_STATIC, 
		0,
		10, 10, 80, 40,
		WS_VISIBLE, WS_EX_NONE,
        "Normal rectangle:",
		NULL, NULL, NULL, NULL, 
		0, 0 
	},
	{
		NCSCTRL_RECTANGLE, 
		ID_RECT1,
		110, 10, 80, 40,
		WS_VISIBLE,
		WS_EX_NONE,
		"",
		rect1_props, //props,
		NULL, //rdr_info
		NULL, //handlers,
		NULL, //controls
		0,
		0 //add data
	},
	{
		NCSCTRL_STATIC, 
		0,
		10, 60, 80, 40,
		WS_VISIBLE, WS_EX_NONE,
        "Filled rectangle:",
		NULL, NULL, NULL, NULL, 
		0, 0 
	},
	{
		NCSCTRL_RECTANGLE, 
		ID_RECT2,
		110, 60, 80, 40,
		WS_VISIBLE,
		WS_EX_NONE,
		"",
		rect2_props, //props,
		NULL, //rdr_info
		NULL, //handlers,
		NULL, //controls
		0,
		0 //add data
	},
	{
		NCSCTRL_STATIC, 
		0,
		10, 110, 80, 40,
		WS_VISIBLE, WS_EX_NONE,
        "no Border rectangle:",
		NULL, NULL, NULL, NULL, 
		0, 0 
	},
	{
		NCSCTRL_RECTANGLE, 
		ID_RECT3,
		110, 110, 80, 40,
		WS_VISIBLE,
		WS_EX_NONE,
		"",
		rect3_props, //props,
		NULL, //rdr_info
		NULL, //handlers,
		NULL, //controls
		0,
		0 //add data
	},
	{
		NCSCTRL_STATIC, 
		0,
		10, 160, 80, 40,
		WS_VISIBLE, WS_EX_NONE,
        "Round rectangle:",
		NULL, NULL, NULL, NULL, 
		0, 0 
	},
	{
		NCSCTRL_RECTANGLE, 
		ID_RECT4,
		110, 160, 80, 40,
		WS_VISIBLE,
		WS_EX_NONE,
		"",
		rect4_props, //props,
		NULL, //rdr_info
		NULL, //handlers,
		NULL, //controls
		0,
		0 //add data
	},
};


static NCS_EVENT_HANDLER mymain_handlers[] = {
	{MSG_CREATE, mymain_onCreate },
	{MSG_CLOSE, mymain_onClose },
	{0, NULL }
};

//define the main window template
static NCS_MNWND_TEMPLATE mymain_templ = {
	NCSCTRL_DIALOGBOX, 
	1,
	0, 0, 320, 320,
	WS_CAPTION | WS_BORDER | WS_VISIBLE,
	WS_EX_NONE,
    "Rectangle Test ....",
	NULL,
	NULL,
	mymain_handlers,
	_ctrl_templ,
	sizeof(_ctrl_templ)/sizeof(NCS_WND_TEMPLATE),
	0,
	0, 0,
};

int MiniGUIMain(int argc, const char* argv[])
{
	ncsInitialize();
	mDialogBox* mydlg = (mDialogBox *)ncsCreateMainWindowIndirect 
                                (&mymain_templ, HWND_DESKTOP);
	
	printf("NCSP_RECTANGLE_BORDERSIZE=%d\n",NCSP_RECTANGLE_BORDERSIZE);

	_c(mydlg)->doModal(mydlg, TRUE);


	MainWindowThreadCleanup(mydlg->hwnd);
	return 0;
}

#ifdef _MGRM_THREADS
#include <minigui/dti.c>
#endif

