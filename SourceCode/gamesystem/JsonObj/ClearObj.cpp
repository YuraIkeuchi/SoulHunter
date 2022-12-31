#include "ClearObj.h"
#include "ModelManager.h"
#include "JsonLoader.h"
using namespace DirectX;
//‰Šú‰»
void ClearObj::Initialize() {
	
	//Json
	jsonData = JsonLoader::LoadFile("Clear");

	//Json“Ç‚Ýž‚Ý‚ÌOBJ
	for (auto& objectData : jsonData->objects) {
		//•’Ê‚ÌOBJ
		if (objectData.GimmickName == "NoGimmick") {
			// ƒtƒ@ƒCƒ‹–¼‚©‚ç“o˜^Ï‚Ýƒ‚ƒfƒ‹‚ðŒŸõ
			IKEModel* model = IKEModel::LoadFromOBJ(objectData.fileName, true);
			decltype(models)::iterator it = models.find(objectData.fileName);
			if (it != models.end()) {
				model = it->second;
			}

			// ƒ‚ƒfƒ‹‚ðŽw’è‚µ‚Ä3DƒIƒuƒWƒFƒNƒg‚ð¶¬
			IKEObject3d* newObject = IKEObject3d::Create();
			newObject->SetModel(model);
			XMFLOAT3 Startpos;

			// À•W
			DirectX::XMStoreFloat3(&Startpos, objectData.translation);

			newObject->SetPosition(Startpos);

			// ‰ñ“]Šp
			DirectX::XMFLOAT3 rot;
			DirectX::XMStoreFloat3(&rot, objectData.rotation);
			newObject->SetRotation(rot);

			// À•W
			DirectX::XMFLOAT3 scale;
			DirectX::XMStoreFloat3(&scale, objectData.scaling);
			newObject->SetScale(scale);

			newObject->SetTiling(20.0f);
			newObject->SetFog(true);
			// ”z—ñ‚É“o˜^
			objects.push_back(newObject);
		}
	}
}
//XV
void ClearObj::Update(int Timer) {

	//Json—p
	for (auto& object : objects) {
		object->Update();
	}
}
//‘O–Ê•`‰æ
const void ClearObj::FrontDraw() {

}
//”wŒi•`‰æ
const void ClearObj::BackDraw() {	//Json—p
	for (auto& object : objects) {
		object->Draw();
	}
}
//‰ð•ú
void ClearObj::Finalize() {

}