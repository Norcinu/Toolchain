#ifndef ABOUT_DIALOG_H
#define ABOUT_DIALOG_H

#include <Windows.h>

class AboutDialog
{
public:
	AboutDialog(void);
	~AboutDialog(void);

	static BOOL CALLBACK AboutDialogProc(HWND wnd, UINT msg, WPARAM wp, LPARAM lp);
};

#endif
