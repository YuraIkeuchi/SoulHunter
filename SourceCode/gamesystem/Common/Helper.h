#pragma once

#include <Windows.h>
#include <d3d12.h>
#include <DirectXMath.h>

class Helper
{
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	bool CheckMax(float& Num, const float Max, const float Add);
	bool CheckMin(float& Num, const float Min, const float Add);
	//Clamp��Ԃ��֐�
	void IntClamp(int& Num, const int Min, const int Max);
	void FloatClamp(float& Num, const float Min, const float Max);
	//XMFLOAT3��float�����Z����֐�
	void Float3AddFloat(XMFLOAT3& Num, float Add);
	//XMFLOAT3��XMFLOAT3�����Z����֐�
	void Float3AddFloat3(XMFLOAT3& Num, XMFLOAT3 Add);
	//XMFLOAT3��float�����Z����֐�
	void Float3SubFloat(XMFLOAT3& Num, float Sub);
	//XMFLOAT3��XMFLOAT3�����Z����֐�
	void Float3SubFloat3(XMFLOAT3& Num, XMFLOAT3 Sub);
};

