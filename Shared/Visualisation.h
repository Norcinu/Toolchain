#ifndef VISUALISATION_H
#define VISUALISATION_H

#include <Windows.h>
#include <d3d11.h>
#include <memory>

struct RendererInfo;
struct DxImpl;

typedef std::shared_ptr<RendererInfo> RendererInfoPtr;
typedef std::shared_ptr<DxImpl> DxImplPtr;

class D3DRenderer
{
public:
    D3DRenderer();
    D3DRenderer(const RendererInfoPtr infoCopy);
    ~D3DRenderer();
        
    bool Init(HWND wnd, const int width, const int height);
    void Begin();
    void End();
    void DrawAll();
    void DrawText();
    void Shutdown();
    void CalculateFPS();

    ID3D11Device * GetDevice() const; // { return dximpl->d3d_device; }
    RendererInfoPtr GetWindowInfo() const { return info; }

private:
    RendererInfoPtr info;
    DxImplPtr dximpl;
};

typedef std::shared_ptr<D3DRenderer> RendererPtr;

#endif
