#include "Visualisation.h"

D3D_DRIVER_TYPE g_driverType = D3D_DRIVER_TYPE_NULL;
D3D_FEATURE_LEVEL g_featureLevel = D3D_FEATURE_LEVEL_11_0;

D3DRenderer::D3DRenderer() :
    info(new WindowInfo),
    swapChain(nullptr),
    d3d_device(nullptr),
    deviceContext(nullptr),
    renderTargetView(nullptr),
    depthStencilBuffer(nullptr),
    depthStencilState(nullptr),
    depthStencilView(nullptr),
    rasterState(nullptr) {}

D3DRenderer::D3DRenderer(const WindowInfoPtr infoCopy) :
    info(infoCopy),
    swapChain(nullptr),
    d3d_device(nullptr),
    deviceContext(nullptr),
    renderTargetView(nullptr),
    depthStencilBuffer(nullptr),
    depthStencilState(nullptr),
    depthStencilView(nullptr),
    rasterState(nullptr) {}

D3DRenderer::~D3DRenderer()
{
    Shutdown();
}

bool D3DRenderer::Init(HWND wnd, const int width, const int height)
{
    info->windowWidth = width;
    info->windowHeight = height;
    info->aspect = info->windowWidth / info->windowHeight;

    UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_DRIVER_TYPE driverTypes[] = 
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE
    };

    UINT numDriverTypes = ARRAYSIZE(driverTypes);

    D3D_FEATURE_LEVEL featureLevels[] = 
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0
    };

    UINT numFeatureLevels = ARRAYSIZE(featureLevels);

    ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc.Width = info->windowWidth;
    swapChainDesc.BufferDesc.Height = info->windowHeight;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = wnd;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.Windowed = TRUE;

    HRESULT result = S_OK;
    for (auto index = 0; index < numDriverTypes; index++)
    {
        g_driverType = driverTypes[index];
        result = D3D11CreateDeviceAndSwapChain(NULL,
            g_driverType,
            NULL, 
            createDeviceFlags,
            featureLevels,
            numFeatureLevels,
            D3D11_SDK_VERSION,
            &swapChainDesc,
            &swapChain,
            &d3d_device,
            &g_featureLevel,
            &deviceContext);

        if (SUCCEEDED(result))
            break;
    }

    if (FAILED(result))
        return false;

    ID3D11Texture2D* backBuffer = nullptr;
    result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
    if (FAILED(result))
        return false;

    result = d3d_device->CreateRenderTargetView(backBuffer, NULL, &renderTargetView);
    backBuffer->Release();
    if (FAILED(result))
        return false;

    deviceContext->OMSetRenderTargets(1, &renderTargetView, NULL);

    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)info->windowWidth;
    vp.Height = (FLOAT)info->windowHeight;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    deviceContext->RSSetViewports(1, &vp);

    return true;
}

void D3DRenderer::Begin()
{
    float clearColour[4] = {0.0f, 0.125f, 0.3f, 1.0f};
    deviceContext->ClearRenderTargetView(renderTargetView, clearColour);
    OutputDebugString("begin");
}

void D3DRenderer::End()
{
    swapChain->Present(0, 0);
}

void D3DRenderer::Shutdown()
{
}
