#pragma once
#include <DirectXMath.h>
#include"CollisionPrimitive.h"
#include "IKEObject3d.h"
#include"IKEModel.h"
#include "Player.h"
#define DIRECTINPUT_VERSION 0x0800

//�w�i�ɒu��
//��ՃN���X
class BackObjCommon {
protected:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void SetPlayer(Player* player) { this->player.reset(player); }
	/// ���W�̎擾
	const XMFLOAT3& GetPosition() { return  m_pos; }

	const XMFLOAT3& GetRotation() { return m_rot; }

	/// ���W�̐ݒ�
	void SetPosition(const XMFLOAT3& m_pos) { this->m_pos = m_pos; }

	void SetRotation(const XMFLOAT3& m_rot) { this->m_rot = m_rot; }

	void SetScale(const XMFLOAT3& m_scale) { this->m_scale = m_scale; }
protected:
	//�N���X
	unique_ptr<Player> player = nullptr;
	//OBJ�ƃ��f��
	unique_ptr<IKEObject3d> object3d = nullptr;
	IKEModel* model = nullptr;
	//���W
	XMFLOAT3 m_pos = { 0,0,0 };
	XMFLOAT3 m_rot = { 0,0,0 };
	XMFLOAT3 m_scale = { 0.4f,0.4f,0.4f };
	enum ObjType {
		Piller,
		Rock,
		Wall
	};
public:
	virtual ~BackObjCommon() = default;
	//������
	virtual void Initialize() = 0;
	//�X�V
	void Update();
	//�`��
	void Draw();

	virtual void SetObj() = 0;//�z�u
	virtual void specialDraw() = 0;//���̑��̕`��

	bool UpdateCollide();//�X�V�͈�

	bool DrawCollide();//�`��͈�
};