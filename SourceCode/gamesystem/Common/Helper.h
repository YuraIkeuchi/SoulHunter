#pragma once

#include <Windows.h>
#include <d3d12.h>
#include <DirectXMath.h>

class Helper
{
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	//Clampを返す関数
	void IntClamp(int& Num, const int Min, const int Max);
	void FloatClamp(float& Num, const float Min, const float Max);
};

