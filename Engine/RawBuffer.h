#pragma once
class RawBuffer
{

public:
	RawBuffer(void* inputData, int32 inputByte, uint32 outputByte);
	~RawBuffer();

public:
	void CreateBuffer();
	void CopyToInput(void* data); // CPU -> InputBuffer(GPU)
	void CopyFromOutput(void* data); // ResultBuffer(GPU) -> CPU

	ComPtr<ID3D11UnorderedAccessView> GetUAV();
	ComPtr<ID3D11ShaderResourceView> GetSRV();

private:
	void CreateInput();
	void CreateSRV();
	void CreateOutput();
	void CreateUAV();
	void CreateResult();

private:
	ComPtr<ID3D11Buffer> _input;
	ComPtr<ID3D11ShaderResourceView> _srv;
	ComPtr<ID3D11Buffer> _output;
	ComPtr<ID3D11UnorderedAccessView> _uav;
	ComPtr<ID3D11Buffer> _result;

private:
	void* _inputData;
	uint32 _inputByte = 0;
	uint32 _outputByte = 0;
};

