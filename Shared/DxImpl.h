#ifndef DX_IMPL_H
#define DX_IMPL_H

#include <memory>
#include <D3D11.h>

struct DxImpl
{
    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    IDXGISwapChain * swapChain;
    ID3D11Device* d3d_device;
    ID3D11DeviceContext * deviceContext;
    ID3D11RenderTargetView* renderTargetView;
    ID3D11Texture2D* depthStencilBuffer;
    ID3D11DepthStencilState* depthStencilState;
    ID3D11DepthStencilView * depthStencilView;
    ID3D11RasterizerState* rasterState;

    DxImpl() :
        swapChain(nullptr),
        d3d_device(nullptr),
        deviceContext(nullptr),
        renderTargetView(nullptr),
        depthStencilBuffer(nullptr),
        depthStencilState(nullptr),
        depthStencilView(nullptr),
        rasterState(nullptr) {}
};

typedef std::shared_ptr<DxImpl> DxImplPtr;

#endif
