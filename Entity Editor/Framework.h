#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <Windows.h>
#include <memory>
#include <cassert>

struct Entity;
class EntityManager;
class D3DRenderer;

typedef std::shared_ptr<EntityManager> EntityManagerPtr;
typedef std::shared_ptr<D3DRenderer> RendererPtr;

enum IOFileType
{
    TEXT = 1,
    JSON,
    XML,
    IMAGE
};

class ApplicationFramework
{
public:
    ApplicationFramework(HINSTANCE instance_) : 
      wnd_(0), 
      instance(instance_), 
      selection(0),
      running(false)
    {
    }
	
    ~ApplicationFramework() 
    {
	    assert("Shutdown not performed." && wnd_ == 0);
        ::DestroyWindow(wnd_);
    }

public:
	bool Init();
	void Run();
	void Shutdown();

private:
    void  OnDraw();
    bool  OnEvent(UINT msg, WPARAM wParam, LPARAM lParam);
    void  OpenFileDialog(const IOFileType ft);
    void  OpenSaveDialog(const IOFileType ft);
    void  OnInit(HWND wnd, CREATESTRUCT * cs);
    void  SetControlFont(HWND font_control, int points, const char * font_name, 
	    bool is_bold = false);
    void  OnUpdate(float time);
    void  CreateEntity();
    void  RemoveEntity(const int index);
    int   GetCurrentListSelection() const { return selection; }
    void  UpdateAll();

private:
	static LRESULT WINAPI WndProc(HWND wnd, UINT msg, WPARAM wParam, 
        LPARAM lParam);

private:
	HWND wnd_;
	HINSTANCE instance;
	bool running;
    int selection;

    EntityManagerPtr entity_manager;
    RendererPtr renderer;

private:
    enum
    {
        IDC_TEXT_LABEL = 200,
        ID_SINGLELINE,
        IDBC_ADDBUTTON,
        IDBC_REMOVEBUTTON,
        IDBC_CLEARBUTTON,
        IDBC_AUTOCHECKBOX,
        IDC_PANEL,
        IDCL_LISTBOX,
        IDC_GROUP_BOX,
        IDCC_SIMPLE,
        IDCC_DROPDOWN,
        IDCC_DROPDOWNLIST
    };
    HWND list_box;
};

#endif
