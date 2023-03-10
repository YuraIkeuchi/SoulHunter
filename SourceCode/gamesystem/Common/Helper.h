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
	bool CheckMax(float& Num, const float Max, const float Add);
	bool CheckMin(float& Num, const float Min, const float Add);
	//Clampを返す関数
	void IntClamp(int& Num, const int Min, const int Max);
	void FloatClamp(float& Num, const float Min, const float Max);
	//XMFLOAT3とfloatを加算する関数
	void Float3AddFloat(XMFLOAT3& Num, float Add);
	//XMFLOAT3とXMFLOAT3を加算する関数
	void Float3AddFloat3(XMFLOAT3& Num, XMFLOAT3 Add);
	//XMFLOAT3とfloatを減算する関数
	void Float3SubFloat(XMFLOAT3& Num, float Sub);
	//XMFLOAT3とXMFLOAT3を減算する関数
	void Float3SubFloat3(XMFLOAT3& Num, XMFLOAT3 Sub);
};

