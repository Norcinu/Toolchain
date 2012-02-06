#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <Windows.h>
#include <cassert>

class ApplicationFramework
{
public:
	ApplicationFramework(HINSTANCE instance_) : wnd_(0), instance(instance_), running(false)
	{
	}
	
	~ApplicationFramework() 
	{
		assert("Shutdown not performed." && wnd_ == 0);
	}

public:
	bool Init();
	void Run();
	void Shutdown();

private:
	void  OnDraw();
	bool  OnEvent(UINT msg, WPARAM wParam, LPARAM lParam);
    void  OpenFileDialog();
    void  OnInit(HWND wnd, CREATESTRUCT * cs);
    void SetControlFont( HWND font_control, int points, const char * font_name, bool is_bold=false );
    void  OnUpdate(float time);

private:
	static LRESULT WINAPI WndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	HWND wnd_;
	HINSTANCE instance;
	bool running;

private:
	enum
	{
		IDC_TEXT_LABEL = 200,
		IDBC_PUSHBUTTON,
        IDBC_AUTOCHECKBOX,
		IDC_PANEL,
		IDCL_LISTBOX,
        IDC_GROUP_BOX,
        IDCC_SIMPLE,
        IDCC_DROPDOWN,
        IDCC_DROPDOWNLIST
	};
};

#endif
