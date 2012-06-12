#include "Framework.h"
#include "../Entity Editor/AppUtilities.h"
#include "../Entity Editor/resource.h"
#include <iostream>
#include <ShObjIdl.h>

#include "../Entity Editor/AboutDialog.h"
//#define _WIN32_WINNT 0x0700

static std::string current_open_file = "";
static COMDLG_FILTERSPEC extensions[] = 
{
	{L"Json Files (*.json)", L"*.json"},
	{L"Text Files (*.txt)", L"*.txt"},
	{L"XML Files (*.xml)", L"*.xml"}
};

bool ApplicationFramework::Init()
{
    assert("ApplicationFramework::Init already performed." && wnd_ == 0);


    WNDCLASS wc;
    ZeroMemory(&wc, sizeof(WNDCLASS));

    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BTNFACE+1); 
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hIcon = 0;
    wc.hInstance = instance;
    wc.lpfnWndProc = ApplicationFramework::WndProc;
    wc.lpszClassName = "entity_editor";
    wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); 
    wc.style = CS_OWNDC;

    if (0 == ::RegisterClass(&wc))
    {
        std::cerr << "ApplicationFramework::Init Failed; RegisterClass failed." << std::endl;
        return false;
    }

    int desktop_width = GetSystemMetrics(SM_CXSCREEN);
    int desktop_height = GetSystemMetrics(SM_CYSCREEN);

    wnd_ = ::CreateWindow(
	    "entity_editor", 
	    "Entity Editor - Steven Gleed",
		WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX/* WS_OVERLAPPEDWINDOW*/, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		0, 0, 0, 0);

    if (wnd_ == 0)
    {
        std::cerr << "ApplicationFramework::Init Failed; CreateWindow failed." 
	        << std::endl;
		
        return false;
    }

    ::SetWindowLongPtr(wnd_, GWL_USERDATA, (LONG_PTR)this);

    // I do not like this!
    OnInit(wnd_, (CREATESTRUCT*)this);

    return true;
}

void ApplicationFramework::Run()
{
	assert( "ApplicationFramework::Init not performed" && wnd_ != 0 );

	// Make the window appear
	::ShowWindow(wnd_, SW_SHOW);
	//UpdateWindow(wnd_);

	// Establish a "message loop", continuously listening for and processing 
    // window events, updating and drawing the "scene"
	MSG msg;
	running = true;
	long start_time = ::timeGetTime();
	while (running)
	{
		while (::GetMessage(&msg,0,0,0))
		{
			::TranslateMessage( &msg );
			::DispatchMessage( &msg );
		}

		OnUpdate( 0.001f * ( timeGetTime() - start_time ) );
		OnDraw();
	}
}

void ApplicationFramework::Shutdown()
{
    ::DestroyWindow(wnd_);
    wnd_ = 0;
}

void ApplicationFramework::OnDraw() 
{
}

bool ApplicationFramework::OnEvent(UINT msg, WPARAM wParam, LPARAM lParam) 
{ 
    switch(LOWORD(wParam))
    {
    case ID_FILE_OPEN40007:
        OpenFileDialog();
        break;
    case ID_FILE_SAVEAS:
        OpenSaveDialog();
        break;
    case ID_HELP_ABOUT:
        DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), this->wnd_,
	        AboutDialog::AboutDialogProc);
    }

    return true; 
}

void ApplicationFramework::OnInit(HWND wnd, CREATESTRUCT * cs) 
{
    RECT d3d_static_pos = { 10, 15, 640, 480 };
    RECT grp_box_pos = { 660, 10, 395, 485 };
    RECT ent_list_pos = {675, 35, 125, 200 };
    RECT phs_radio_pos;
    RECT ai_radio_pos;
    RECT new_btn_pos = {675, 300, 125, 35};
    RECT remove_btn_pos = {675, 340, 125, 35};
    RECT clear_btn_pos = {675, 380, 125, 35};

    HWND group_box = app_helper::CreateButton(
	    wnd, 
	    cs->hInstance, 
	    BS_GROUPBOX|BS_CENTER, 
        grp_box_pos, 
	    IDC_GROUP_BOX, 
	    ("Entity Controls"));
    
    HWND list_box = app_helper::CreateListbox(
	    wnd, 
	    cs->hInstance, 
	    0, 
	    ent_list_pos, 
	    IDCL_LISTBOX, 
	    (""));
    
    app_helper::AddString(list_box, ("Test 1"));
    app_helper::AddString(list_box, ("Test 2"));
    app_helper::AddString(list_box, ("Test 3"));
    app_helper::AddString(list_box, ("Test 4"));

    HWND new_btn = app_helper::CreateButton(
        wnd, 
        cs->hInstance,
        BS_DEFPUSHBUTTON,
        new_btn_pos,
        IDBC_PUSHBUTTON,
        ("Create New Entity"));
    
    HWND remove_btn = app_helper::CreateButton(
        wnd, 
        cs->hInstance,
        BS_DEFPUSHBUTTON,
        remove_btn_pos,
        IDBC_PUSHBUTTON,
        ("Remove Entity"));
        
    HWND clear_btn = app_helper::CreateButton(
        wnd, 
        cs->hInstance,
        BS_DEFPUSHBUTTON,
        clear_btn_pos,
        IDBC_PUSHBUTTON,
        ("Remove All"));

    app_helper::CreateStatic(wnd, cs->hInstance, 0, d3d_static_pos, 
	    IDC_TEXT_LABEL, ("Direct3D Window goes here."));

    SetControlFont(group_box, 17, "Consolas", true);
    SetControlFont(list_box, 17, "Consolas");
    SetControlFont(new_btn, 14, "Consolas", true);
    SetControlFont(remove_btn, 14, "Consolas", true);
    SetControlFont(clear_btn, 14, "Consolas", true);
}

void ApplicationFramework::OnUpdate(float time) 
{
}

LRESULT CALLBACK ApplicationFramework::WndProc(HWND wnd, UINT msg, WPARAM wParam,
	LPARAM lParam)
{
	ApplicationFramework* app = (ApplicationFramework *)GetWindowLongPtr(wnd, 
		GWL_USERDATA);

	if (app == nullptr)
		return DefWindowProc(wnd, msg, wParam, lParam);

	switch ( msg )
	{
    case WM_COMMAND:
        if (!app->OnEvent(msg, wParam, lParam))
            return ::DefWindowProc(wnd, msg, wParam, lParam);
        break;
	case WM_CLOSE:
		::ShowWindow( app->wnd_, SW_HIDE );
		app->running = false;
		break;
	case WM_CREATE:
		app->OnInit(wnd,reinterpret_cast<CREATESTRUCT*>(lParam));
		return 0;
	case WM_DESTROY:
		::PostQuitMessage(0);    //signal end of application
		return 0; 
	}

	return ::DefWindowProc(wnd,msg,wParam,lParam);	
}

// move this and OpenSaveDialog() into one method, maybe determine which
// to open by add a function pointer.
// perhaps a function to configure the appropriate dialog too.
void ApplicationFramework::OpenFileDialog()
{
    IFileDialog *file_dialog = nullptr;
    HRESULT hr = CoCreateInstance(
		CLSID_FileOpenDialog, 
		NULL, 
		CLSCTX_INPROC_SERVER, 
		IID_PPV_ARGS(&file_dialog));

    if (SUCCEEDED(hr))
    {
        IFileDialogEvents *dialog_event = nullptr;
        file_dialog->SetFileTypes(ARRAYSIZE(extensions), extensions);
        file_dialog->SetTitle(L"Open Entity");
        file_dialog->Show(this->wnd_);
    }
}

void ApplicationFramework::OpenSaveDialog()
{
	IFileSaveDialog * save_dialog = nullptr;
	HRESULT hr = CoCreateInstance(
		CLSID_FileSaveDialog, 
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&save_dialog));
	
	if (SUCCEEDED(hr))
	{
        hr = save_dialog->SetFileTypes(ARRAYSIZE(extensions), extensions);
        if (SUCCEEDED(hr))
        {
		    save_dialog->SetTitle(L"Save Entity");
		    save_dialog->Show(this->wnd_);
        }
        else if (FAILED(hr))
            OutputDebugString("FAILED");
	}
}

void ApplicationFramework::SetControlFont( HWND font_control, int points, 
	const char * font_name, bool is_bold )
{
    HFONT hFont = NULL;
   
    if (is_bold) 
    {
         hFont = CreateFont(points, 0, 0, 0, 700,
            FALSE, 
			FALSE, 
			FALSE,
            ANSI_CHARSET, 
			OUT_DEVICE_PRECIS, 
			CLIP_MASK,
            ANTIALIASED_QUALITY, 
			DEFAULT_PITCH, 
			font_name);
    }
    else
    {
        // Use normal font for other controls
        hFont = CreateFont(points, 0, 0, 0, 550,
            FALSE, 
			FALSE, 
			FALSE,
            ANSI_CHARSET, 
			OUT_DEVICE_PRECIS, 
			CLIP_MASK,
            ANTIALIASED_QUALITY, 
			DEFAULT_PITCH, 
			font_name);
    }
   
    SendMessage(font_control, WM_SETFONT, WPARAM (hFont), TRUE);
}
