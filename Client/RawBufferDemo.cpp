#include "pch.h"
#include "RawBufferDemo.h"
#include "RawBuffer.h"

void RawBufferDemo::Init() 
{
	_shader = make_shared<Shader>(L"25. RawBufferDemo.fx");

	// �ϳ��� ������ �׷� ������ ��� ������ ����
	uint32 count = 10 * 8 * 3;

	shared_ptr<RawBuffer> rawBuffer = make_shared<RawBuffer>(nullptr, 0, count * sizeof(Output));

	_shader->GetUAV("Output")->SetUnorderedAccessView(rawBuffer->GetUAV().Get());

	// x, y, z ������ �׷�
	_shader->Dispatch(0, 0, 1, 1, 1);

	vector<Output> output(count);
	rawBuffer->CopyFromOutput(output.data());


	FILE* file;
	::fopen_s(&file, "../RawBuffer.csv", "w");

	assert(file != nullptr);

	::fprintf(file, "GroupID(X),GroupID(Y),GroupID(Z),GroupThreadID(X),GroupThreadID(Y),GroupThreadID(Z),DispatchThreadID(X),DispatchThreadID(Y),DispatchThreadID(Z),GroupIndex\n");

	for (uint32 i=0; i<count; i++)
	{
		const Output& temp = output[i];

		::fprintf(file, 
			"%d,%d,%d,	%d,%d,%d,	%d,%d,%d,	%d\n", 
			temp.groupID[0], temp.groupID[1], temp.groupID[2],
			temp.groupThreadID[0], temp.groupThreadID[1], temp.groupThreadID[2],
			temp.dispatchThreadID[0], temp.dispatchThreadID[1], temp.dispatchThreadID[2],
			temp.groupIndex
		);
	}


	::fclose(file);
}

void RawBufferDemo::Update()
{
}

void RawBufferDemo::Render()
{

}
