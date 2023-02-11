#include "ObjEdit.h"
#include "BackRock.h"
#include "BackBox.h"
#include "BackTorch.h"

//íåÇÃê∂ê¨
void ObjEdit::RockArgment(std::vector<BackObjCommon*>& objs,GamePlayer* player, const XMFLOAT3& pos, const XMFLOAT3& rot){
	BackObjCommon* newPiller;
	newPiller = new BackRock();
	newPiller->Initialize();
	newPiller->SetPosition(pos);
	newPiller->SetRotation(rot);
	newPiller->SetPlayer(player);
	objs.push_back(newPiller);
}

//ä‚ÇÃê∂ê¨
void ObjEdit::BoxArgment(std::vector<BackObjCommon*>& objs, GamePlayer* player, const XMFLOAT3& pos, const XMFLOAT3& rot) {
	BackObjCommon* newBox;
	newBox = new BackBox();
	newBox->Initialize();
	newBox->SetPosition(pos);
	newBox->SetRotation(rot);
	newBox->SetPlayer(player);
	objs.push_back(newBox);
}

//ä‚ÇÃê∂ê¨
void ObjEdit::TorchArgment(std::vector<BackObjCommon*>& objs, GamePlayer* player, const XMFLOAT3& pos, const XMFLOAT3& rot) {
	BackObjCommon* newTorch;
	newTorch = new BackTorch();
	newTorch->Initialize();
	newTorch->SetPosition(pos);
	newTorch->SetRotation(rot);
	newTorch->SetPlayer(player);
	objs.push_back(newTorch);
}
