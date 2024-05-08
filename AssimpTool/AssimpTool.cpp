#include "pch.h"
#include "AssimpTool.h"
#include "Converter.h"

void AssimpTool::Init()
{
	{
		shared_ptr<Converter> converter = make_shared<Converter>();

		converter->ReadAssetFile(L"Wolf/WolfAnim.fbx");
		converter->ExportMaterialData(L"Wolf/WolfAnim");
		converter->ExportModelData(L"Wolf/WolfAnim");
	}
}

void AssimpTool::Update()
{

}

void AssimpTool::Render()
{

}
