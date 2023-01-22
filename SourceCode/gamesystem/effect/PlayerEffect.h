#pragma once
#include <DirectXMath.h>
#include <memory> 
#include "AttackEffect.h"
#include "WallAttackEffect.h"
#include "PlayerDamageEffect.h"
#include "PlayerDushEffect.h"
#include <list> // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��
//�U���G�t�F�N�g
class PlayerEffect {
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	PlayerEffect();
	//�G�t�F�N�g�̐���
	void CreateEffect(const std::string& newname, XMFLOAT3 pos, int dir);
	void Initialize();//������
	void Update();//�X�V
	void Draw();//�`��
	
public:
private:
	vector<AttackEffect*> attackeffects;
	vector<WallAttackEffect*>walleffects;
	vector<PlayerDushEffect*> dusheffects;
	vector<PlayerDamageEffect*> damageeffects;
};