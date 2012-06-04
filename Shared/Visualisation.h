#ifndef VISUALISATION_H
#define VISUALISATION_H

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
	
public:
	WindowInfoPtr getWindowInfo() const { return info; }
	virtual ~Visualisation();

protected:
	WindowInfoPtr info;
};

#endif
