#pragma once
#include "ObjCommon.h"
#include <memory>
//�w�i�̊�Ȃǋ��ʔw�i�̃N���X
class BackObjAlways :
	public ObjCommon {
protected:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	BackObjAlways();

	bool Initialize() override;//������
	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(DirectXCommon* dxCommon) override;
private:
	//�萔
	static const int BackRock_Max = 11;//OBJ�̐�
private:
	
};