#pragma once
#include <DirectXMath.h>
#include "Player.h"
#include "ObjCommon.h"
#define DIRECTINPUT_VERSION 0x0800

//�w�i�ɒu��
//��ՃN���X
class BackObjCommon :
	public ObjCommon {
protected:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void SetPlayer(Player* player) { this->player.reset(player); }
protected:
	//�N���X
	unique_ptr<Player> player = nullptr;
	
	enum ObjType {
		Piller,
		Rock,
		Wall
	};
public:
	virtual ~BackObjCommon() = default;
	//������
	virtual bool Initialize()override;
	//�X�V
	void Update();
	//�`��
	virtual void Draw(DirectXCommon* dxCommon)override;

	virtual void SetObj() = 0;//�z�u
	virtual void specialDraw() = 0;//���̑��̕`��

	bool UpdateCollide();//�X�V�͈�

	bool DrawCollide();//�`��͈�
};