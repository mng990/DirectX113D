#include "pch.h"
#include "GroupDemo.h"
#include "RawBuffer.h"

void GroupDemo::Init()
{
	_shader = make_shared<Shader>(L"26. GroupDemo.fx");

	// �ϳ��� ������ �׷� ������ ��� ������ ����
	uint32 threadCount = 10 * 8 * 3;
	uint32 groupCount = 2 * 1 * 1;

	uint32 count = groupCount * threadCount;

	vector<Input> inputs(count);

	for (int32 i = 0; i < count; i++)
		inputs[i].value = rand() % 10000;

	shared_ptr<RawBuffer> rawBuffer = make_shared<RawBuffer>(inputs.data(), sizeof(Input)* count, count * sizeof(Output));

	_shader->GetSRV("Input") ->SetResource(rawBuffer->GetSRV().Get());
	_shader->GetUAV("Output")->SetUnorderedAccessView(rawBuffer->GetUAV().Get());

	// x, y, z ������ �׷�
	_shader->Dispatch(0, 0, 2, 1, 1);

	vector<Output> output(count);
	rawBuffer->CopyFromOutput(output.data());


	FILE* file;
	::fopen_s(&file, "../RawBuffer.csv", "w");

	assert(file != nullptr);

	::fprintf(file, "GroupID(X),GroupID(Y),GroupID(Z),GroupThreadID(X),GroupThreadID(Y),GroupThreadID(Z),DispatchThreadID(X),DispatchThreadID(Y),DispatchThreadID(Z),GroupIndex,Value\n");

	for (uint32 i=0; i<count; i++)
	{
		const Output& temp = output[i];

		::fprintf(file, 
			"%d,%d,%d,	%d,%d,%d,	%d,%d,%d,	%d,%f\n", 
			temp.groupID[0], temp.groupID[1], temp.groupID[2],
			temp.groupThreadID[0], temp.groupThreadID[1], temp.groupThreadID[2],
			temp.dispatchThreadID[0], temp.dispatchThreadID[1], temp.dispatchThreadID[2],
			temp.groupIndex, temp.value
		);
	}


	::fclose(file);
}

void GroupDemo::Update()
{
}

void GroupDemo::Render()
{

}
