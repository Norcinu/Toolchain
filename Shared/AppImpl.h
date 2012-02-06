#ifndef APP_IMPL_H
#define APP_IMPL_H

#ifdef _WIN32
#include <Windows.h>
#elif __linux__
 // change this to what it is really meant to be
#include <x11/x11.h>
#endif

#include <exception>
#include <cassert>

class AppImpl 
{
public:
	bool running;

	AppImpl() : running(true) {}
	
	virtual ~AppImpl() {}
	virtual bool Init() = 0; 
	virtual void Run() = 0;
	virtual void Shutdown() = 0;
};

class WinImpl : public AppImpl
{
public:
	WinImpl() : wnd_(0) 
	{
		if (!this->Init())
			throw std::exception("Failure to initialise WinImpl.");
	}
	
	~WinImpl() 
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
	void  OnInit();
	void  OnUpdate(float time);

private:
	static LRESULT WINAPI WndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	HWND wnd_;
};

#endif
