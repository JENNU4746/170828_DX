#include "stdafx.h"

LPDIRECT3D9 g_pD3D; // hWnd
LPDIRECT3DDEVICE9 g_pd3dDevice; // HDC
BOOL g_bIsFullScreen = false;

LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL;
LPDIRECT3DTEXTURE9 g_pTexture = NULL;

HRESULT InitD3D(HWND hWnd) // DirectX객체 초기화
{
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	// 디바이스 설정
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = !g_bIsFullScreen;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferWidth = WIDTH;
	d3dpp.BackBufferHeight = HEIGHT;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice)))
		return E_FAIL;
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	return S_OK;
}

HRESULT PreRender(LPDIRECT3DDEVICE9 pd3dDevice)
{
	pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	return SUCCEEDED(pd3dDevice->BeginScene());
}

VOID Render(LPDIRECT3DDEVICE9 pd3dDevice)
{
	g_pd3dDevice->SetTexture(0, g_pTexture);
	g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
	g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 4);
}

VOID PostRender(LPDIRECT3DDEVICE9 pd3dDevice)
{
	pd3dDevice->EndScene();
	pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

VOID Run(LPDIRECT3DDEVICE9 pd3dDevice)
{
	PreRender(pd3dDevice);
	Render(pd3dDevice);
	PostRender(pd3dDevice);
}

VOID Cleanup()
{
	if (g_pd3dDevice != NULL) g_pd3dDevice->Release();
	if (g_pD3D != NULL) g_pD3D->Release();
}

HRESULT InitVB()
{
	char szFileName[256] = "./a.bmp";
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, szFileName, &g_pTexture)))
		return E_FAIL;

	if (FAILED(g_pd3dDevice->CreateVertexBuffer(6 * sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &g_pVB, NULL)))
		return E_FAIL;

	CUSTOMVERTEX* pVertices;
	if (FAILED(g_pVB->Lock(0, 0, (void**)&pVertices, 0)))
		return E_FAIL;

	pVertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	pVertices[0].tu = 1.0f; pVertices[0].tv = 1.0f;
	pVertices[1].position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	pVertices[1].tu = 1.0f; pVertices[1].tv = 0.0f;
	pVertices[2].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	pVertices[2].tu = 0.0f; pVertices[2].tv = 0.0f;
	pVertices[3].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	pVertices[3].tu = 0.0f; pVertices[3].tv = 1.0f;
	pVertices[4].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	pVertices[4].tu = 1.0f; pVertices[4].tv = 1.0f;
	pVertices[5].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	pVertices[5].tu = 0.0f; pVertices[5].tv = 0.0f;
	
	g_pVB->Unlock();
	return S_OK;
}