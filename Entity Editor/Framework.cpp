#include "Framework.h"
#include "AppUtilities.h"
#include "resource.h"
#include <iostream>
#include <ShObjIdl.h>
#include <string>
#include <functional>

#include "Entity.h"
#include "AboutDialog.h"
#include "Visualisation.h"
#include "Utils.h"

namespace
{
    int window_height = 600;
    int window_width = 1024;

    static std::string current_open_file = "";
    static COMDLG_FILTERSPEC extensions[] = 
    {
	    {L"Json Files (*.json)", L"*.json"},
	    {L"Text Files (*.txt)", L"*.txt"},
	    {L"XML Files (*.xml)", L"*.xml"}
    };

    static COMDLG_FILTERSPEC gfx_extensions[] = 
    {
        {L"Bitmap Files (*.bmp)", L"*.bmp"},
        {L"PNG Files (*.png)", L"*.png"},
        {L"Targa Files (*.tga)", L"*.tga"},
        {L"3D Object Files (*.obj)", L"*.obj"}
    };
}

struct GetSizeFunctor {
    void operator()(std::string& msg, size_t size) {      
        std::string conversion = utils::str::ToString<size_t>(size);
        msg.append(conversion.begin(), conversion.end());
        msg += "\n";
        OutputDebugString(msg.c_str());   
    }
};

typedef struct GetSelectionFunctor {
    int operator()() {
        return 1;
    }
} GetSelection;

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
		WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX /*| WS_OVERLAPPEDWINDOW*/, 
		desktop_width / 8, 
		10/*desktop_height / 4*/, 
		window_width,//CW_USEDEFAULT, 
		window_height, 
		0, 0, 0, 0);

    if (wnd_ == 0)
    {
        std::cerr << "ApplicationFramework::Init Failed; CreateWindow failed." 
	        << std::endl;
		
        return false;
    }

    ::SetWindowLongPtr(wnd_, GWL_USERDATA, (LONG_PTR)this);

    entity_manager = std::make_shared<EntityManager>();
    renderer = std::make_shared<D3DRenderer>();
    

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
        while (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE) != 0)
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
    //if (renderer->GetDevice() != nullptr)
    {
        renderer->Begin();
        renderer->End();
    }
}

bool ApplicationFramework::OnEvent(UINT msg, WPARAM wParam, LPARAM lParam) 
{ 
    switch(LOWORD(wParam))
    {
    case ID_FILE_OPEN40007:
        OpenFileDialog(TEXT);
        break;
    case ID_FILE_SAVEAS:
        OpenSaveDialog(TEXT);
        break;
    case ID_HELP_ABOUT:
        DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), this->wnd_,
	        AboutDialog::AboutDialogProc);
        break;
    case IDBC_ADDBUTTON:
        OutputDebugString("PUSHED BUTTON\n");
        if (!renderer->LoadTexture("Em1.jpg"))
            return false;
        CreateEntity();
        break;
    case IDBC_REMOVEBUTTON:
        OutputDebugString("REMOVE BUTTON\n");
        RemoveEntity(selection);
        break;
    case IDBC_CLEARBUTTON:
        OutputDebugString("CLEAR BUTTON\n");
        break;
    case IDCL_LISTBOX:
        switch (HIWORD(wParam))
        {
        case LBN_SELCHANGE:
            selection = (int)SendMessage(list_box, LB_GETCURSEL, 0, 0);
            OutputDebugString("SELECTION CHANGED\n");
            break;
        }
        break;
    }
    
    return true; 
}

void ApplicationFramework::OnInit(HWND wnd, CREATESTRUCT * cs) 
{   
    // positions were 675 // group right -> 395 bottom 485
    RECT d3d_static_pos = {10, 15, 640, 480};
    RECT grp_box_pos = {660, 10, 285, 350}; // 285
    RECT ent_list_pos = {675, 35, 125, 200};
    RECT phs_radio_pos = {800, 155, 125, 35};
    RECT ai_radio_pos = {800, 185, 125, 35};
    RECT new_btn_pos = {800, 35, 125, 35};
    RECT remove_btn_pos = {800, 75, 125, 35};
    RECT clear_btn_pos = {800, 115, 125, 35};
    RECT ent_txt_name = {800, 235, 125, 25};
    RECT ent_txt_pos = {800, 265, 125, 25}; 
    RECT ent_txt_side = {800, 295, 125, 25};
    RECT ent_lbl_name = {675, 235, 125, 25};
    RECT ent_lbl_pos = {675, 265, 125, 25};
    RECT ent_lbl_side = {675, 295, 125, 25};

    HWND group_box = app_helper::CreateButton(
	    wnd, 
	    cs->hInstance, 
	    BS_GROUPBOX|BS_CENTER, 
        grp_box_pos, 
	    IDC_GROUP_BOX, 
	    ("Entity Controls"));
    
    list_box = app_helper::CreateListbox(
	    wnd, 
	    cs->hInstance, 
        LBS_NOTIFY|LBS_WANTKEYBOARDINPUT, 
	    ent_list_pos, 
	    IDCL_LISTBOX, 
	    (""));
    
    HWND new_btn = app_helper::CreateButton(
        wnd, 
        cs->hInstance,
        BS_DEFPUSHBUTTON,
        new_btn_pos,
        IDBC_ADDBUTTON,
        ("Create New Entity"));
    
    HWND remove_btn = app_helper::CreateButton(
        wnd, 
        cs->hInstance,
        BS_DEFPUSHBUTTON,
        remove_btn_pos,
        IDBC_REMOVEBUTTON,
        ("Remove Entity"));
        
    HWND clear_btn = app_helper::CreateButton(
        wnd, 
        cs->hInstance,
        BS_DEFPUSHBUTTON,
        clear_btn_pos,
        IDBC_CLEARBUTTON,//IDBC_ADDBUTTON,
        ("Remove All"));

    HWND d3d_label = app_helper::CreateStatic(wnd, cs->hInstance, 0, d3d_static_pos, 
	    IDC_TEXT_LABEL, ("D3D Window goes here."));

    if (!renderer->Init(d3d_label, 320, 240))
        OutputDebugString("ERROR LOADING DX11\n");

    app_helper::CreateButton(wnd, cs->hInstance, BS_RADIOBUTTON, 
        ai_radio_pos, IDBC_AUTOCHECKBOX, ("Has AI?"));

    app_helper::CreateButton(wnd, cs->hInstance, BS_RADIOBUTTON, 
        phs_radio_pos, IDBC_AUTOCHECKBOX, ("Has Physics?"));

    HWND en = app_helper::CreateEditBox(wnd, cs->hInstance, 0, ent_txt_name, 
        ID_SINGLELINE, (""));
    txtEntityName = std::make_pair(en, ent_txt_name);

    HWND ep = app_helper::CreateEditBox(wnd, cs->hInstance, 0, ent_txt_pos, 
        ID_SINGLELINE, (""));
    txtEntityPos = std::make_pair(ep, ent_txt_pos);

    HWND es = app_helper::CreateEditBox(wnd, cs->hInstance, 0, ent_txt_side, 
        ID_SINGLELINE, (""));
    txtEntitySide = std::make_pair(es, ent_txt_side);

    app_helper::CreateStatic(wnd, cs->hInstance, 0, ent_lbl_name,
        IDC_TEXT_LABEL, ("Entity name:"));

    app_helper::CreateStatic(wnd, cs->hInstance, 0, ent_lbl_pos,
        IDC_TEXT_LABEL, ("Entity position:"));

    app_helper::CreateStatic(wnd, cs->hInstance, 0, ent_lbl_side,
        IDC_TEXT_LABEL, ("Entity side:"));

    // add static to display information of current entity.

    //SetControlFont(group_box, 17, "Consolas", true);
    //SetControlFont(list_box, 17, "Consolas");
    //SetControlFont(new_btn, 10.5, "Microsoft Sans Serif", true);
    //SetControlFont(remove_btn, 16, "Consolas", true);
    //SetControlFont(clear_btn, 14, "Consolas", true);
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
void ApplicationFramework::OpenFileDialog(const IOFileType ft)
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
        switch (ft)
        {
        case TEXT:
            file_dialog->SetFileTypes(ARRAYSIZE(extensions), extensions);
            break;
        case IMAGE:
            file_dialog->SetFileTypes(ARRAYSIZE(gfx_extensions), gfx_extensions);
        }
            
        file_dialog->SetTitle(L"Open Entity");
        file_dialog->Show(this->wnd_);
    }
}

void ApplicationFramework::OpenSaveDialog(const IOFileType ft)
{
	IFileSaveDialog * save_dialog = nullptr;
	HRESULT hr = CoCreateInstance(
		CLSID_FileSaveDialog, 
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&save_dialog));
	
	if (SUCCEEDED(hr))
	{
        switch (ft)
        {
        case TEXT:
            hr = save_dialog->SetFileTypes(ARRAYSIZE(extensions), extensions);
            break;
        case IMAGE:
            hr = save_dialog->SetFileTypes(ARRAYSIZE(gfx_extensions), gfx_extensions);
            break;
        }
       
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

void ApplicationFramework::UpdateAll() {
    //SendMessage(wnd, 
    //LPSTR buffer;
    //Edit_GetText(txtEntityName.first, buffer, 1024);
}

void ApplicationFramework::SetEditText(HWND hwnd, std::string& msg) {
    Edit_SetText(hwnd, (LPSTR)msg.c_str());
}

std::string ApplicationFramework::GetEditText(HWND hwnd) const {
    int length = Edit_GetTextLength(hwnd);
    LPSTR buffer = "";
    Edit_GetText(hwnd, buffer, length);
#ifdef _DEBUG 
    // check this!!!!
    OutputDebugString(*buffer + "\n");
#endif
    return std::move(std::string(buffer));
}

void ApplicationFramework::CreateEntity() {
    Entity::entity_ptr ent = std::make_shared<Entity>();
    ent->name = "Entity " + utils::str::ToString<size_t>(entity_manager->GetSize());
   
    app_helper::AddString(list_box, ent->name);
    entity_manager->Add(ent);
    SetEditText(txtEntityName.first, std::string(ent->name));
    std::string x = utils::str::ToString<float>(ent->x);
    std::string y = utils::str::ToString<float>(ent->y);
    std::string position = x + ", " + y;
    SetEditText(txtEntityPos.first, position);
    //SetEditText(txtEntitySide.first, ent->side);
#ifdef _DEBUG
    OutputDebugString(ent->name.c_str()); 
    OutputDebugString("\n");
#endif
}

void ApplicationFramework::RemoveEntity(const int index) {
#ifdef _DEBUG
    size_t size = entity_manager->GetSize();
    GetSizeFunctor gsf;
    std::function<void (std::string&, size_t)> func(gsf);
    func(std::string("Size before deletion "), size);
#endif

  entity_manager->Remove(index);
  //auto F = [selection]() {
  //};
  SendMessage(list_box, LB_DELETESTRING, 0, (LPARAM)selection+1);
  
#ifdef _DEBUG
    size = entity_manager->GetSize(); 
    std::string msg = "Size after deletion ";
    
    auto funcPrint = [&size, &msg]() {
        std::string conversion = utils::str::ToString<size_t>(size);
        msg.append(conversion.begin(), conversion.end());
        msg += "\n";
        OutputDebugString(msg.c_str());
    };

    funcPrint();
    //func(std::string("Size after deletion "), size);
#endif
}
