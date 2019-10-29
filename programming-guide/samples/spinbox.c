#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include <mgncs/mgncs.h>

//START_SPINBOX
#define ID_SPINBOX1      101
#define ID_SPINBOX2      102
#define ID_SPINBOX3      103
#define ID_SPINBOX4      104

static char * item [] =
{
    "SpinBox item-1st",
    "SpinBox item-2nd",
    "SpinBox item-3rd",
    "SpinBox item-4th"
};

static BOOL mymain_onCreate(mWidget* self, DWORD add_data)
{ 
    int i;
    mSpinBox *spinner3, *spinner4;

    spinner3 = (mSpinBox *)_c(self)->getChild(self, ID_SPINBOX3);
    spinner4 = (mSpinBox *)_c(self)->getChild(self, ID_SPINBOX4);

    for (i = 0; i < sizeof(item)/sizeof(char*); i++)
	{

        _c(spinner3)->addItem (spinner3, item[i]);

        _c(spinner4)->addItem (spinner4, item[i]);

    }
        
	return TRUE;
}


//Propties for
static NCS_PROP_ENTRY spinner_props [] = {

	{NCSP_SPNBOX_MAXPOS, 12},
	{NCSP_SPNBOX_MINPOS, 0},
	{NCSP_SPNBOX_CURPOS, 0},
	{NCSP_SPNBOX_LINESTEP, 1},
	{0, 0}
};

//END_SPINBOX

static void mymain_onClose(mWidget* self, int message)
{
	DestroyMainWindow(self->hwnd);
	PostQuitMessage(0);
}



static NCS_RDR_INFO spin_rdr_info[] =
{
	{"fashion", "fashion", NULL}
};

//Controls
static NCS_WND_TEMPLATE _ctrl_templ[] = {
	{
		NCSCTRL_SPINBOX , 
		ID_SPINBOX1,
		20, 10, 100, 20,
		WS_VISIBLE | NCSS_SPNBOX_HORIZONTAL | NCSS_SPNBOX_NUMBER | NCSS_SPNBOX_READONLY,
		WS_EX_NONE,
		"spinbox",
		spinner_props, //props,
		spin_rdr_info, //NULL, //rdr_info
		NULL, //handlers,
		NULL, //controls
		0,
		0 //add data
	},
    {
		NCSCTRL_SPINBOX , 
		ID_SPINBOX2,
		20, 40, 100, 20,
		WS_VISIBLE | NCSS_SPNBOX_VERTICAL | NCSS_SPNBOX_NUMBER | NCSS_SPNBOX_AUTOLOOP,
		WS_EX_NONE,
		"spinbox",
		spinner_props, //props,
		spin_rdr_info, //NULL, //rdr_info
		NULL, //handlers,
		NULL, //controls
		0,
		0 //add data
	},
	{
		NCSCTRL_SPINBOX , 
		ID_SPINBOX3,
		150, 10, 150, 20,
		WS_VISIBLE | NCSS_SPNBOX_HORIZONTAL | NCSS_SPNBOX_STRING,
		WS_EX_NONE,
		"spinbox",
		NULL, //props,
		spin_rdr_info, //NULL, //rdr_info
		NULL, //handlers,
		NULL, //controls
		0,
		0 //add data
	},
    {
		NCSCTRL_SPINBOX , 
		ID_SPINBOX4,
		150, 40, 150, 20,
		WS_VISIBLE | NCSS_SPNBOX_VERTICAL | NCSS_SPNBOX_STRING,
		WS_EX_NONE,
		"spinbox",
		NULL, //props,
		spin_rdr_info, //NULL, //rdr_info
		NULL, //handlers,
		NULL, //controls
		0,
		0 //add data
	}
};


static NCS_EVENT_HANDLER mymain_handlers[] = {
	{MSG_CREATE,mymain_onCreate},
	{MSG_CLOSE,mymain_onClose},
	{0, NULL}
};

//define the main window template
static NCS_MNWND_TEMPLATE mymain_templ = {
	NCSCTRL_DIALOGBOX, 
	1,
	0, 0, 340, 150,
	WS_CAPTION | WS_BORDER | WS_VISIBLE,
	WS_EX_NONE,
    "SpinBox Test ....",
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
	if(argc>1)
	{
		spin_rdr_info[0].glb_rdr = argv[1];
		spin_rdr_info[0].ctl_rdr = argv[1];
	}


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

