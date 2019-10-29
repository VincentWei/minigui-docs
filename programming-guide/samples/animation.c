#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
#include "../include/mgncs.h"
#include "../include/mrdr.h"
#define IDC_ANI 100
#define IDC_BTN1 101
#define IDC_BTN2 102
#define IDC_BTN3 103
#define IDC_ANIM 104

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

//START_OF_PIC
static NCS_PROP_ENTRY animate_props [] = {
	{ NCSP_ANMT_GIFFILE, (DWORD)"tuzi1.gif" },
	{ NCSP_ANMT_INTERVAL, 6 },
	{0, 0}
};

static NCS_PROP_ENTRY animate_props_ex [] = {
	{ NCSP_ANMT_DIR, (DWORD)"." },
	{ NCSP_ANMT_INTERVAL, 100 },
	{0, 0}
};
//END_OF_PIC

NCS_RDR_ELEMENT btn_rdr_elements[] = 
{
	{ NCS_MODE_USEFLAT, 1},
	{ -1, 0 }
};

static NCS_RDR_INFO btn_rdr_info[] =
{
	{"flat","flat", NULL}
};

NCS_RDR_ELEMENT animate_rdr_elements[] = 
{
	{ NCS_MODE_USEFLAT, 1},
	{ -1, 0 }
};

static NCS_RDR_INFO animate_rdr_info[] = 
{
	{"flat", "flat", NULL}
};

//START_OF_KEY_EVENT
static void btn_notify(mWidget *button, int id, int nc, DWORD add_data)
{
    mAnimate *anim = (mAnimate *)ncsGetChildObj(GetParent(button->hwnd), IDC_ANI);

    switch (id)
    {
        case IDC_BTN1 :
			ncsAnimateStart(anim);    
            break;
        case IDC_BTN2 :
			ncsAnimatePauseResume(anim);
            break;
        case IDC_BTN3 :
            ncsAnimateStop(anim);
            break;
    }

}

static NCS_EVENT_HANDLER btn_handlers [] = {
    NCS_MAP_NOTIFY(NCSN_BUTTON_PUSHED, btn_notify),
	{0, NULL}	
};
//END_OF_KEY_EVENT

//START_OF_TMPL
static NCS_WND_TEMPLATE _ctrl_templ[] = {
	{
		NCSCTRL_ANIMATE, 
		IDC_ANI,
		50, 50, 300, 300,
		WS_BORDER | WS_VISIBLE |NCSS_ANMT_AUTOFIT | NCSS_ANMT_AUTOLOOP | \		NCSS_ANMT_AUTOPLAY,
		WS_EX_NONE,
		"test",
		animate_props, //props,
		animate_rdr_info,
		NULL, //handlers,
		NULL, //controls
		0,
		0 //add data
	},
	{
		NCSCTRL_ANIMATE, 
		IDC_ANIM,
		0, 230, 300, 300,
		WS_BORDER | WS_VISIBLE | NCSS_ANMT_AUTOLOOP | NCSS_ANMT_AUTOFIT | \		NCSS_ANMT_AUTOPLAY,,
		WS_EX_NONE,
		"test2",
		animate_props_ex, //props,
		animate_rdr_info,
		NULL, //handlers,
		NULL, //controls
		0,
		0 //add data
	},
	{
		NCSCTRL_BUTTON, 
		IDC_BTN1,
		450, 100, 70, 30,
		WS_VISIBLE | NCSS_NOTIFY,
		WS_EX_NONE,
        "Start",
		NULL,
		btn_rdr_info,
		btn_handlers,
		NULL,
		0,
		0
	},	
	{
		NCSCTRL_BUTTON, 
		IDC_BTN2,
		450, 200, 70, 30,
		WS_VISIBLE | NCSS_NOTIFY,
		WS_EX_NONE,
        "Pause",
		NULL,
		btn_rdr_info,
		btn_handlers,
		NULL,
		0,
		0
	},	
	{
		NCSCTRL_BUTTON, 
		IDC_BTN3,
		450, 300, 70, 30,
		WS_VISIBLE | NCSS_NOTIFY,
		WS_EX_NONE,
        "Stop",
		NULL,
		btn_rdr_info,
		btn_handlers,
		NULL,
		0,
		0
	},	
};
//END_OF_TMPL

static NCS_EVENT_HANDLER mymain_handlers[] = {
	{MSG_CREATE, mymain_onCreate},
	{MSG_CLOSE, mymain_onClose},
	{0, NULL}
};

//define the main window template
static NCS_MNWND_TEMPLATE mymain_templ = {
	NCSCTRL_DIALOGBOX, 
	1,
	0, 0, 600, 600,
	WS_CAPTION | WS_BORDER | WS_VISIBLE,
	WS_EX_NONE,
    "animate Test ....",
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
	mDialogBox* mydlg = (mDialogBox *)ncsCreateMainWindowIndirect(&mymain_templ, HWND_DESKTOP);

	_c(mydlg)->doModal(mydlg, TRUE);


	MainWindowThreadCleanup(mydlg->hwnd);
	return 0;
}

#ifdef _MGRM_THREADS
#include <minigui/dti.c>
#endif

