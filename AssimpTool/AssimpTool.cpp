#include "pch.h"
#include "AssimpTool.h"
#include "Converter.h"

void AssimpTool::Init()
{
	{
		shared_ptr<Converter> converter = make_shared<Converter>();
		
		converter->ReadAssetFile(L"Hulkbuster/Hulkbuster.fbx");
		converter->ExportMaterialData(L"Hulkbuster/Hulkbuster");
		converter->ExportModelData(L"Hulkbuster/Hulkbuster");
	}
}

void AssimpTool::Update()
{

}

void AssimpTool::Render()
{

}
