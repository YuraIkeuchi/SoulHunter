#pragma once
#include "BackObjCommon.h"
#include "BackRock.h"
#include "BackBox.h"
#include "BackTorch.h"
#include "Player.h"
//背景OBJのエディタクラス
class ObjEdit {
protected:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	//各OBJの生成(引数が多いので後々修正する)
	void RockArgment(std::vector<BackObjCommon*>& objs,Player* player, const XMFLOAT3& pos, const XMFLOAT3& rot);
	void BoxArgment(std::vector<BackObjCommon*>& objs, Player* player, const XMFLOAT3& pos, const XMFLOAT3& rot);
	void TorchArgment(std::vector<BackObjCommon*>& objs, Player* player, const XMFLOAT3& pos, const XMFLOAT3& rot);
private:
};