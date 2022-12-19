#pragma once
#include "IKETexture.h"
#include "AllArray.h"
#include <array>   
#include <memory>
#include <list> // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��
//�񕜂̃p�[�e�B�N��
class ParticleHeal {
protected:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	ParticleHeal();
public:

	/// <summary>
	/// ������
	/// </summary>
	/// <returns>����</returns>
	void Initialize();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update(const XMFLOAT3& StartPos, int Timer, int TargetTimer);
	void ParticleMove(const XMFLOAT3& StartPos, int Timer, int TargetTimer);//�p�[�e�B�N���̓���
	void HealEffect(const XMFLOAT3& StartPos);//�񕜂����u�Ԃ̃G�t�F�N�g
	void Draw();//�`��
	void ImGuiDraw();//ImGui
public:
	//gettersetter
	bool GetHeal() { return  m_Heal; }

	void SetStartColor(const XMFLOAT4& m_color) { this->m_StartColor = m_color; }
	void SetHeal(bool m_Heal) { this->m_Heal = m_Heal; }
private:
	//�e�N�X�`��
	unique_ptr<IKETexture> healeffecttex;
	array<unique_ptr <IKETexture>, ParticleHeal_Max> particletex;
	//�ϐ�
	array<XMFLOAT3, ParticleHeal_Max> m_pos;//���W
	array<float, ParticleHeal_Max> m_Angle;//�p�x
	array<XMFLOAT4, ParticleHeal_Max> m_color;//�F
	array<XMFLOAT2, ParticleHeal_Max> m_speed;//�ړ����x
	array<XMFLOAT3, ParticleHeal_Max> m_scale;//�傫��
	array<XMFLOAT3, ParticleHeal_Max> m_AddPower;//������
	XMFLOAT4 m_StartColor = { 1.0f,1.0f,1.0f,1.0f };//�n�܂�̐F
	
	
	array<bool, ParticleHeal_Max> m_Alive;//�������Ă��邩
	array<bool, ParticleHeal_Max> m_ScaleChange;//�傫���̕ύX
	array<int, ParticleHeal_Max> m_Number;
	array<int, ParticleHeal_Max> m_Timer;
	XMFLOAT3 m_StartPos = { 0.0f,0.0f,0.0f };
	//�L����G�t�F�N�g
	bool m_Heal = false;
	bool m_HealStart = false;
	XMFLOAT3 m_HealPos = { 0.0f,0.0f,0.0f };
	XMFLOAT3 m_HealRot = { 0.0f,0.0f,0.0f };
	XMFLOAT3 m_HealScale = { 0.0f,0.0f,0.0f };
	XMFLOAT4 m_HealColor = { 1.0f,1.0f,1.0f,0.0f };
	enum HealEffectNumber {
		Appear,
		Disappear
	};
	HealEffectNumber m_HealEffectNumber;
};