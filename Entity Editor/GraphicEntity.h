#ifndef GRAPHIC_ENTITY_H
#define GRAPHIC_ENTITY_H

#include <d3d11.h>
#include <D3DX11.h>
#include <xnamath.h>

struct SimpleVertex {
	XMFLOAT3 position;
};

class BaseGraphicEntity 
{
public:
    ~BaseGraphicEntity() {}

    virtual void Initialise(const char * filename, DxImpl * impl) = 0;
    virtual void Render(ID3D11Device * device) = 0;

    ID3D11VertexShader * vshader;
    ID3D11PixelShader * pshader;
	ID3D11Buffer * vertexBuffer;
	SimpleVertex vertices[3];

protected:
    BaseGraphicEntity() {}
};

class TexturedQuad2D : public BaseGraphicEntity
{
public:
    TexturedQuad2D() {}
	void Initialise(const char * filename, DxImpl * impl) {
		vertices[0].position = XMFLOAT3(0.0f, 0.5f, 0.5f);
		vertices[1].position = XMFLOAT3(0.5f, -0.5f, 0.5f);
		vertices[2].position = XMFLOAT3(-0.5f, -0.5f, 0.5f);
		
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(SimpleVertex) * 3;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = vertices;
		impl->d3d_device->CreateBuffer(&bd, &InitData, &vertexBuffer);

		UINT stride = sizeof(SimpleVertex);
		UINT offset = 0;
		impl->deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		impl->deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    }

    void Render(ID3D11Device * device) {
		//device->
	}

};

#endif