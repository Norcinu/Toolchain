#ifndef RENDERER_INFO_H
#define RENDERER_INFO_H

#include <memory>

struct RendererInfo
{
	RendererInfo() :
		windowHeight(0), 
		windowWidth(0), 
		aspect(0.0f) 
	{}
	
	RendererInfo(int h, int w, float fov) : 
		windowHeight(h),
		windowWidth(w),
		aspect(fov) {}
	
	~RendererInfo() {}
	
	int windowHeight;
	int windowWidth;
	float aspect;
};

typedef std::shared_ptr<RendererInfo> RendererInfoPtr;

#endif

