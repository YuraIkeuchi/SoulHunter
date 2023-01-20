#pragma once
#include "IKETexture.h"
#include <array>   
#include <memory>
#include <list> // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��
//�p�[�e�B�N���^�C�v
enum Type {
	NormalPart,
	UpPart,
	EndPart,
	ChestPart,
	SavePart,
	BossEndPart,
};
//�e�N�X�`���̃p�[�e�B�N��
class ParticleTex {
protected:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	ParticleTex();
public:

	/// <summary>
	/// ������
	/// </summary>
	/// <returns>����</returns>
	void Initialize();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update(const XMFLOAT3& StartPos, int Timer, int TargetTimer, int ParticleType);

	//�e�p�[�e�B�N���̎��
	void NormalParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer);

	void UpParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer);

	void EndParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer);

	void ChestParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer);

	void SaveParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer);

	void BossEndParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer);
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	void ImGuiDraw();
public:
	void SetStartColor(const XMFLOAT4& m_color) { this->m_StartColor = m_color; }
	void SetParticleType(int m_ParticleType) { this->m_ParticleType = m_ParticleType; }
	void SetParticleBreak(bool m_ParticleBreak) { this->m_ParticleBreak = m_ParticleBreak; }
	void SetParticleBillboard(bool m_ParticleBillboard) { this->m_ParticleBillboard = m_ParticleBillboard; }
	void SetStartScale(float m_StartScale) { this->m_StartScale = m_StartScale; }
	void SetAddScale(float m_AddScale) { this->m_AddScale = m_AddScale; }
private:
	//�萔
	static const int ParticleTex_Max = 40;//�p�[�e�B�N���̐�
private:
	//�e�N�X�`��
	array<unique_ptr <IKETexture>, ParticleTex_Max> particletex;

	//�ϐ�
	array<XMFLOAT3, ParticleTex_Max> m_pos;//���W
	array<float, ParticleTex_Max> m_Angle;//�p�x
	array<XMFLOAT4, ParticleTex_Max> m_color;//�F
	array<XMFLOAT2, ParticleTex_Max> m_speed;//�ړ����x
	array<XMFLOAT3, ParticleTex_Max> m_scale;//�傫��
	array<XMFLOAT3, ParticleTex_Max> m_AddPower;//������
	XMFLOAT4 m_StartColor = { 1.0f,1.0f,1.0f,1.0f };//�n�܂�̐F

	array<bool, ParticleTex_Max> m_Alive;//�������Ă��邩
	array<bool, ParticleTex_Max> m_End;//�������Ă��邩
	array<bool, ParticleTex_Max> m_ScaleChange;//�傫���̕ύX
	array<int, ParticleTex_Max> m_Number;//�p�[�e�B�N���̓�������
	array<int, ParticleTex_Max> m_Timer;//�p�[�e�B�N���̎���
	XMFLOAT3 m_StartPos = { 0.0f,0.0f,0.0f };

	bool m_ParticleBreak = false;//�p�[�e�B�N�����X�ɂ�����
	float m_StartScale = 0.1f;//�n�܂�̑傫��
	float m_AddScale = 0.02f;//�傫���ɉ��Z�����
	int m_ParticleType = 0;//�p�[�e�B�N���̃^�C�v
	bool m_ParticleBillboard = false;//�r���{�[�h
	
};