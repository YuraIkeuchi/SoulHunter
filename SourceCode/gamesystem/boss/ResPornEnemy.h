#pragma once
#include "InterBoss.h"
//�{�X�X�e�[�W�̂Ƃ��ɃU�R�G�����܂ɏo������
class ResPornEnemy
{
public:
	void Initialize();
	void Update(InterBoss* boss = nullptr);
	void Finalize();
	const void Draw();
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	//getter setter
	bool GetEnemyArgment() { return  m_EnemyArgment; }

	int GetResPornType() { return  m_ResPornType; }

	const XMFLOAT3& GetResPornPosition() { return  m_ResPornPos; }

	void SetEnemyArgment(bool m_EnemyArgment) { this->m_EnemyArgment = m_EnemyArgment; }
private:
	//�N���X
	//unique_ptr<ParticleTex> particletex = nullptr;
	//���̑��ϐ�
	XMFLOAT3 m_ResPornPos = { 0.0f,0.0f,0.0f };//���W
	int m_ResPornTimer = 0;//�����܂ł̎���
	bool m_EnemyArgment = false;//��������邩�ǂ���
	int m_ParticleCount = 0;//�p�[�e�B�N���̐����܂ł̃t���[��
	bool m_ResPornParticle = false;//�p�[�e�B�N�����o�邩�ǂ���
	int m_ResPornType = 0;//�G�̎��
	//���X�|�[���X���G�̎��
	enum ResPornEnemyType {
		Normal,
		Wing,
		Bird,
	};
};