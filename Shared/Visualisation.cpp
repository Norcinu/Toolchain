#include "Visualisation.h"
#include "WindowInfo.h"
#include "DxImpl.h"
#include "Utils.h"

D3D_DRIVER_TYPE g_driverType = D3D_DRIVER_TYPE_NULL;
D3D_FEATURE_LEVEL g_featureLevel = D3D_FEATURE_LEVEL_11_0;

D3DRenderer::D3DRenderer() :
    info(new RendererInfo),
    dximpl(new DxImpl) {}

D3DRenderer::D3DRenderer(const RendererInfoPtr infoCopy) :
    info(infoCopy),
    dximpl(new DxImpl) {}

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

    ZeroMemory(&dximpl->swapChainDesc, sizeof(dximpl->swapChainDesc));
    dximpl->swapChainDesc.BufferCount = 1;
    dximpl->swapChainDesc.BufferDesc.Width = info->windowWidth;
    dximpl->swapChainDesc.BufferDesc.Height = info->windowHeight;
    dximpl->swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    dximpl->swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    dximpl->swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    dximpl->swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    dximpl->swapChainDesc.OutputWindow = wnd;
    dximpl->swapChainDesc.SampleDesc.Count = 1;
    dximpl->swapChainDesc.SampleDesc.Quality = 0;
    dximpl->swapChainDesc.Windowed = TRUE;

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
            &dximpl->swapChainDesc,
            &dximpl->swapChain,
            &dximpl->d3d_device,
            &g_featureLevel,
            &dximpl->deviceContext);

        if (SUCCEEDED(result))
            break;
    }

    if (FAILED(result))
        return false;

    ID3D11Texture2D* backBuffer = nullptr;
    result = dximpl->swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), 
        (LPVOID*)&backBuffer);
    
    if (FAILED(result))
        return false;

    result = dximpl->d3d_device->CreateRenderTargetView(backBuffer, 
        NULL, &dximpl->renderTargetView);

    backBuffer->Release();
    if (FAILED(result))
        return false;

    dximpl->deviceContext->OMSetRenderTargets(1, &dximpl->renderTargetView, NULL);

    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)info->windowWidth;
    vp.Height = (FLOAT)info->windowHeight;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    dximpl->deviceContext->RSSetViewports(1, &vp);

    return true;
}

ID3D11Device* D3DRenderer::GetDevice() const 
{
    return dximpl->d3d_device;
}

void D3DRenderer::Begin()
{
#ifdef _DEBUG
    //CalculateFPS();
#endif

    float clearColour[4] = {0.0f, 0.125f, 0.3f, 1.0f};
    dximpl->deviceContext->ClearRenderTargetView(
        dximpl->renderTargetView, clearColour);
}

void D3DRenderer::End()
{
    dximpl->swapChain->Present(0, 0);
}

void D3DRenderer::Shutdown()
{
    if (dximpl->deviceContext)
    {
        dximpl->deviceContext->ClearState();
        dximpl->deviceContext->Release();
    }

    if (dximpl->renderTargetView)
        dximpl->renderTargetView->Release();
    if (dximpl->swapChain)
        dximpl->swapChain->Release();
    if (dximpl->d3d_device)
        dximpl->d3d_device->Release();
}

void D3DRenderer::CalculateFPS() 
{  
    static auto lastTime = timeGetTime();
    static auto frames = 0;
    static auto fps = 0;

    auto newTime = timeGetTime();

    if (newTime - lastTime > 1000)
    {
        auto newFPS = (frames * 1000 / (newTime - lastTime));
        std::string str = utils::str::ToString<unsigned long>(newFPS) + "\n";
        OutputDebugString(str.c_str());
        lastTime = newTime;
        frames = 0;
    }
    frames++;
}
