#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include <mgncs/mgncs.h>
#include <time.h>

//START_UPDATE_TIME
static BOOL update_time(mStatic *listener,
		mTimer* sender,
		int id, 
		DWORD total_count)
{
	char szText[100];
	time_t tim;
	struct tm *ptm;
	static int old_count = 0;

	time(&tim);
	ptm = localtime(&tim);

	sprintf(szText, 
			"%02d:%02d:%d",
			ptm->tm_hour, 
			ptm->tm_min, 
            ptm->tm_sec);
	old_count = total_count;

	SetWindowText(listener->hwnd, szText);
    InvalidateRect(listener->hwnd, NULL, TRUE);

	return FALSE;
}
//END_UPDATE_TIME


//START_TIMER_CONNECT
static BOOL mymain_onCreate(mWidget* self, DWORD add_data)
{
	//TODO : initialize
	mTimer * timer = SAFE_CAST(mTimer, 
					_c(self)->getChild(self, 100));
	if(timer)
	{
		ncsAddEventListener((mObject*)timer, 
						(mObject*)ncsGetChildObj(self->hwnd, 101), 
						(NCS_CB_ONPIECEEVENT)update_time, 
						MSG_TIMER);
		_c(timer)->start(timer);
	}
	return TRUE;
}
//END_TIMER_CONNECT

static void mymain_onClose(mWidget* self, int message)
{
	DestroyMainWindow(self->hwnd);
	PostQuitMessage(0);
}

//Controls
//START_DECLARE_TIMER
static NCS_WND_TEMPLATE _ctrl_templ[] = {
	{
		NCSCTRL_TIMER, 
		100,
		10, 10, 0, 0,
		WS_BORDER | WS_VISIBLE,
		WS_EX_NONE,
		"",
		NULL, //props,
		NULL, //rdr_info
		NULL, //timer_props, //handlers,
		NULL, //controls
		0,
		0 //add data
	},
//END_DECLARE_TIMER
	{
		NCSCTRL_STATIC,
		101,
		10,10, 100, 30,
		WS_VISIBLE,
		0,
		"",
		NULL,
		NULL,
		NULL,
		NULL,
		0,
		0
	}
};


static NCS_EVENT_HANDLER mymain_handlers[] = {
	{MSG_CREATE, mymain_onCreate},
	{MSG_CLOSE, mymain_onClose},
	{0, NULL}
};

//define the main window template
static NCS_MNWND_TEMPLATE mymain_templ = {
	NCSCTRL_DIALOGBOX, 
	1,
	0, 0, 150, 80,
	WS_CAPTION | WS_BORDER | WS_VISIBLE,
	WS_EX_NONE,
    "Digital Clock",
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

	_c(mydlg)->doModal(mydlg, TRUE);

	MainWindowThreadCleanup(mydlg->hwnd);
	return 0;
}

#ifdef _MGRM_THREADS
#include <minigui/dti.c>
#endif

