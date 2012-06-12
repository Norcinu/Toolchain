#ifndef VISUALISATION_H
#define VISUALISATION_H

#include <Windows.h>
#include <d3d11.h>
#include <memory>

struct WindowInfo
{
	WindowInfo() :
		windowHeight(0), 
		windowWidth(0), 
		aspect(0.0f) 
	{}
	
	WindowInfo(int h, int w, float fov) : 
		windowHeight(h),
		windowWidth(w),
		aspect(fov) {}
	
	~WindowInfo() {}
	
	int windowHeight;
	int windowWidth;
	float aspect;
};

typedef std::shared_ptr<WindowInfo> WindowInfoPtr;

class Visualisation
{
protected:
	Visualisation();
	Visualisation(const WindowInfoPtr infoCopy);
	virtual bool Init(HWND wnd, const int width, const int height) = 0;
public:
	WindowInfoPtr getWindowInfo() const { return info; }
	virtual ~Visualisation();

protected:
	WindowInfoPtr info;
};

class D3DRenderer : public Visualisation
{
public:
    D3DRenderer() {}
    ~D3DRenderer() {}

    bool Init(HWND wnd, const int width, const int height);

};

#endif
