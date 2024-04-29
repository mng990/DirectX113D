#include "pch.h"
#include "Main.h"
#include "Engine/Game.h"
#include "01. TriangleDemo.h"
#include "02. QuadDemo.h"
#include "03. ConstantBufferDemo.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int hShowCmd)
{
	GameDesc desc;

	desc.appName = L"DirectX113D";
	desc.hInstance = hInstance;
	desc.vsync = false;
	desc.hWnd = NULL;
	desc.width = 800;
	desc.height = 600;
	desc.clearColor = Color(0.5f, 0.5f, 0.5f, 0.5f);
	desc.app = make_shared<ConstantBufferDemo>();

	GAME->Run(desc);

	return 0;
}