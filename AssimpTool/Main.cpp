#include "pch.h"
#include "Main.h"
#include "Engine/Game.h"
#include "AssimpTool.h"
#include "ImGuiDemo.h"



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
	desc.app = make_shared<AssimpTool>();

	GAME->Run(desc);

	return 0;
}