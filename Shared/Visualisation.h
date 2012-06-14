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

class D3DRenderer
{
public:
    D3DRenderer();
    D3DRenderer(const WindowInfoPtr infoCopy);
    ~D3DRenderer();
        
    bool Init(HWND wnd, const int width, const int height);
    void Begin();
    void End();
    void DrawAll();
    void DrawText();
    void Shutdown();

    ID3D11Device * GetDevice() const { return d3d_device; }
    WindowInfoPtr GetWindowInfo() const { return info; }

private:
    WindowInfoPtr info;
    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    IDXGISwapChain * swapChain;
    ID3D11Device* d3d_device;
    ID3D11DeviceContext * deviceContext;
    ID3D11RenderTargetView* renderTargetView;
    ID3D11Texture2D* depthStencilBuffer;
    ID3D11DepthStencilState* depthStencilState;
    ID3D11DepthStencilView * depthStencilView;
    ID3D11RasterizerState* rasterState;
};

typedef std::shared_ptr<D3DRenderer> RendererPtr;

#endif
