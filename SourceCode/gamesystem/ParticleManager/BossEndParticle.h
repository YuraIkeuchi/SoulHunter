#pragma once
#include "IKETexture.h"
#include "IKEModel.h"
#include "IkeObject3d.h"
#include <array>   
#include <memory>
using namespace std;         //  ���O��Ԏw��
//����OBJ�̃p�[�e�B�N��
class BossEndParticle {
protected:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	BossEndParticle();
public:

	/// <summary>
	/// ������
	/// </summary>
	/// <returns>����</returns>
	void Initialize();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void ObjUpdate(const XMFLOAT3& StartPos, int Timer, int TargetTimer);
	void DownRockParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer);
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	void ImGuiDraw();
public:
	//gettersetter
private:
	//�萔
	static const int BossEndParticle_Max = 40;//�p�[�e�B�N���̐�
private:
	array<unique_ptr <IKEObject3d>, BossEndParticle_Max> particleobj;
	IKEModel* model = nullptr;
	//��̕�
	array<XMFLOAT3, BossEndParticle_Max> m_RockPos;
	array<XMFLOAT3, BossEndParticle_Max> m_Rockscale;
	array<XMFLOAT3, BossEndParticle_Max> m_RockRandPos;
	array<XMFLOAT3, BossEndParticle_Max> m_RockAddPower;
	array<float, BossEndParticle_Max> m_Gravity;
	array<bool, BossEndParticle_Max> m_RockAlive;
	enum Dir {
		Up,
		Down,
		Right,
		Left
	};


};