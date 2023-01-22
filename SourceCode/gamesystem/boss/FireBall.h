#pragma once
#include "DirectXCommon.h"
#include "IKETexture.h"

using namespace std;         //  ���O��Ԏw��
//�v���C���[�̒e�̃N���X
class FireBall
{
protected:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

public:
	FireBall();
public:

	/// <summary>
	/// ������
	/// </summary>
	/// <returns>����</returns>
	bool Initialize();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();
	//�v���C���[�̋���
	void Draw(DirectXCommon* dxCommon);
	//�e�̈ړ�
	void Shot();

	//�|�[�Y�̂Ƃ�
	void Pause();

	bool Collide(XMFLOAT3 pos);

public:
	//gettersetter
	bool GetAlive() { return  m_Alive; }

	void SetAlive(bool Alive) { this->m_Alive = Alive; }

	void SetPosition(const XMFLOAT3& position) { m_Position = position; }
	void SetAddSpeed(float AddSpeed) { this->m_AddSpeed = AddSpeed; }
	void SetAddPowerY(float AddPowerY) { this->m_AddPowerY = AddPowerY; }

private:
	//�e�N�X�`��
	unique_ptr<IKETexture> firetex;
	XMFLOAT3 m_Position = {0.0f,0.0f,0.0f};
	XMFLOAT3 m_Rotation = { 0.0f,0.0f,0.0f };
	XMFLOAT3 m_Scale = { 0.0f,0.0f,0.0f };
	XMFLOAT4 m_Color = { 0.0f,0.0f,0.0f,0.0f };
	//�ϐ�
	XMFLOAT3 m_OldPos = { 0.0f,0.0f,0.0f };
	XMFLOAT2 m_Radius = { 0.5f,0.5f };
	float m_AddSpeed = 0.0f;
	float m_AddPowerY = 0.0f;
	bool m_Alive = false;
	int m_ParticleCount = 0;
};

