#include "AppImpl.h"
#include <iostream>

bool WinImpl::Init()
{
	assert("WinImpl::Init already performed." && wnd_ == 0);

	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = 0;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = 0;
	wc.hInstance = 0;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = "entity_editor";
	wc.lpszMenuName = 0;
	wc.style = CS_OWNDC;

	if (0 == RegisterClass(&wc))
	{
		std::cerr << "WinImpl::Init Failed; RegisterClass failed." << std::endl;
		return false;
	}

	wnd_ = CreateWindow("entity_editor", "Entity Editor - Steven Gleed", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, 0, 0);
	if (wnd_ == 0)
	{
		std::cerr << "WinImpl::Init Failed; CreateWindow failed." << std::endl;
		return false;
	}

	SetWindowLongPtr(wnd_, GWL_USERDATA, (LONG_PTR)this);

	OnInit();

	return true;
}

void WinImpl::Run()
{
	assert( "WinImpl::Init not performed" && wnd_ != 0 );

	// Make the window appear
	ShowWindow(wnd_, SW_SHOW);

	// Establish a "message loop", continuously listening for and processing window events, updating and drawing the "scene"
	MSG msg;
	running = true;
	long start_time = timeGetTime();
	while (running)
	{
		// Handle all pending events
		while ( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) != 0 )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}

		OnUpdate( 0.001f * ( timeGetTime() - start_time ) );
		OnDraw();
	}
}

void WinImpl::Shutdown()
{
	DestroyWindow(wnd_);
	wnd_ = 0;
}

void WinImpl::OnDraw() 
{
}

bool WinImpl::OnEvent(UINT msg, WPARAM wParam, LPARAM lParam) 
{ 
	return true; 
}

void WinImpl::OnInit() 
{
}

void WinImpl::OnUpdate(float time) 
{
}

LRESULT CALLBACK WinImpl::WndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
    {
        case WM_CLOSE:
            DestroyWindow(wnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(wnd, msg, wParam, lParam);
    }
    return 0;
}
