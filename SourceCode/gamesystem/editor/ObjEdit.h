#pragma once
#include "BackObjCommon.h"
#include "BackRock.h"
#include "BackBox.h"
#include "BackTorch.h"
#include "Player.h"
//�w�iOBJ�̃G�f�B�^�N���X
class ObjEdit {
protected:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	//�eOBJ�̐���(�����������̂Ō�X�C������)
	void RockArgment(std::vector<BackObjCommon*>& objs,Player* player, const XMFLOAT3& pos, const XMFLOAT3& rot);
	void BoxArgment(std::vector<BackObjCommon*>& objs, Player* player, const XMFLOAT3& pos, const XMFLOAT3& rot);
	void TorchArgment(std::vector<BackObjCommon*>& objs, Player* player, const XMFLOAT3& pos, const XMFLOAT3& rot);
private:
};