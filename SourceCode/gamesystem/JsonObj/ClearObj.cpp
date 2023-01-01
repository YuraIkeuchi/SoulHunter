#include "ClearObj.h"
#include "ModelManager.h"
#include "JsonLoader.h"
#include "imgui.h"
using namespace DirectX;
ClearObj::ClearObj() {
	modeltorch = ModelManager::GetInstance()->GetModel(ModelManager::BackTorch);
}
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

			newObject->SetTiling(50.0f);
			newObject->SetFog(true);
			// ”z—ñ‚É“o˜^
			objects.push_back(newObject);
		}
	}

	IKEObject3d* objtorch_ = new IKEObject3d();
	objtorch_ = IKEObject3d::Create();
	objtorch_->SetModel(modeltorch);
	objtorch_->SetScale({ 3.5f,3.5f,3.5f });
	objtorch.reset(objtorch_);
}
//XV
void ClearObj::Update(int Timer) {

	//Json—p
	for (auto& object : objects) {
		object->Update();
	}

	objtorch->SetPosition(m_TorchPos);
	objtorch->Update();
}
//‘O–Ê•`‰æ
const void ClearObj::FrontDraw() {
	ImGui::Begin("torch");
	ImGui::Text("torchX:%f", m_TorchPos.x);
	ImGui::Text("torchY:%f", m_TorchPos.y);
	ImGui::Text("torchZ:%f", m_TorchPos.z);
	ImGui::End();
}
//”wŒi•`‰æ
const void ClearObj::BackDraw() {	//Json—p
	for (auto& object : objects) {
		object->Draw();
	}

	objtorch->Draw();
}
//‰ð•ú
void ClearObj::Finalize() {

}