#include "AboutDialog.h"

AboutDialog::AboutDialog(void)
{
}


AboutDialog::~AboutDialog(void)
{
}

BOOL CALLBACK AboutDialog::AboutDialogProc(HWND wnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wp))
		{
		case IDOK:
			EndDialog(wnd, IDOK);
			break;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}