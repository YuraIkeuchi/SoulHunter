#pragma once
#include "IKETexture.h"
#include <array>   
#include <memory>
using namespace std;         //  ���O��Ԏw��
class ParticleSoul {
protected:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	ParticleSoul();
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

	void NormalParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	void ImGuiDraw();
private://�萔
	static const int ParticleSoul_Max = 25;//�p�[�e�B�N���̐�
public:
	void SetStartColor(const XMFLOAT4& m_color) { this->m_StartColor = m_color; }
	void SetParticleType(int m_ParticleType) { this->m_ParticleType = m_ParticleType; }
	void SetParticleBreak(bool m_ParticleBreak) { this->m_ParticleBreak = m_ParticleBreak; }
	void SetStartScale(float m_StartScale) { this->m_StartScale = m_StartScale; }
	void SetAddScale(float m_AddScale) { this->m_AddScale = m_AddScale; }
private:
	//�e�N�X�`��
	array<unique_ptr <IKETexture>, ParticleSoul_Max> particlesoul;
	//�ϐ�
	array<XMFLOAT3, ParticleSoul_Max> m_pos;//���W
	array<float, ParticleSoul_Max> m_Angle;//�p�x
	array<XMFLOAT4, ParticleSoul_Max> m_color;//�F
	array<XMFLOAT2, ParticleSoul_Max> m_speed;//�ړ����x
	array<XMFLOAT3, ParticleSoul_Max> m_scale;//�傫��
	array<XMFLOAT3, ParticleSoul_Max> m_AddPower;//������
	XMFLOAT4 m_StartColor = { 1.0f,1.0f,1.0f,1.0f };//�n�܂�̐F


	array<bool, ParticleSoul_Max> m_Alive;//�������Ă��邩
	array<bool, ParticleSoul_Max> m_ScaleChange;//�傫���̕ύX
	array<int, ParticleSoul_Max> m_Number;
	array<int, ParticleSoul_Max> m_Timer;
	XMFLOAT3 m_StartPos = { 0.0f,0.0f,0.0f };
	//unique_ptr<Player> player;
	int m_ParticleType = 0;
	bool m_ParticleBreak = false;
	float m_StartScale = 0.1f;
	float m_AddScale = 0.02f;
	enum Type {
		Normal,
	};
};