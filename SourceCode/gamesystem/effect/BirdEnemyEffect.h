#pragma once
#include <DirectXMath.h>
#include "IKETexture.h"
#include <array>   
#include <memory> 
#include "Helper.h"
using namespace std;         //  ���O��Ԏw��
//�W�����v�����Ƃ��̃G�t�F�N�g
class BirdEnemyEffect {
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	BirdEnemyEffect();

	void Initialize();
	void Finalize();
	//������ɂ��G���ƂɕK�v�ɂȂ��Ă��܂���
	void Update(const XMFLOAT3& pos);
	void Draw();
	void SetEffect(const XMFLOAT3& pos);
private:
	//�萔
	static const int JumpEffect_Max = 5;//�G�t�F�N�g�̐�

public:
	//getter setter
private:
	unique_ptr<Helper> helper;
	//�e�N�X�`��
	array<unique_ptr<IKETexture>, JumpEffect_Max> JumpDamageEffect;

	//���̑��ϐ�
	array<XMFLOAT3, JumpEffect_Max> m_Position;//���W
	array<XMFLOAT3, JumpEffect_Max> m_Rotation;//��]
	array<XMFLOAT3, JumpEffect_Max> m_Scale;//�傫��
	array<float, JumpEffect_Max> m_Gravity;//�d��
	array<float, JumpEffect_Max> m_AddRot;//������]��
	array<XMFLOAT3, JumpEffect_Max> m_AddPower;//�������x
	array<bool, JumpEffect_Max> m_Effect;//�����t���O
	array<bool, JumpEffect_Max> m_Birth;//�n�܂����u��
	array<int, JumpEffect_Max> m_Timer;//����
	array<int, JumpEffect_Max> m_EffectNumber;//�G�t�F�N�g�ɉ����͂̎��

	//�G�t�F�N�g�ɗ͂���������
	enum EffectNumber {
		No,
		Birth,
		Fall
	};
};