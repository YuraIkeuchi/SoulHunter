#include "ClearObj.h"
#include "ModelManager.h"
#include "JsonLoader.h"
#include "imgui.h"
using namespace DirectX;
ClearObj::ClearObj() {
	modeltorch = ModelManager::GetInstance()->GetModel(ModelManager::BackTorch);
}
//初期化
void ClearObj::Initialize() {
	//Json
	jsonData = JsonLoader::LoadFile("Clear");
	//Json読み込みのOBJ
	for (auto& objectData : jsonData->objects) {
		//普通のOBJ
		if (objectData.GimmickName == "NoGimmick") {
			// ファイル名から登録済みモデルを検索
			IKEModel* model = IKEModel::LoadFromOBJ(objectData.fileName, true);
			decltype(models)::iterator it = models.find(objectData.fileName);
			if (it != models.end()) {
				model = it->second;
			}

			// モデルを指定して3Dオブジェクトを生成
			IKEObject3d* newObject = IKEObject3d::Create();
			newObject->SetModel(model);
			XMFLOAT3 Startpos;

			// 座標
			DirectX::XMStoreFloat3(&Startpos, objectData.translation);

			newObject->SetPosition(Startpos);

			// 回転角
			DirectX::XMFLOAT3 rot;
			DirectX::XMStoreFloat3(&rot, objectData.rotation);
			newObject->SetRotation(rot);

			// 座標
			DirectX::XMFLOAT3 scale;
			DirectX::XMStoreFloat3(&scale, objectData.scaling);
			newObject->SetScale(scale);

			newObject->SetTiling(50.0f);
			// 配列に登録
			objects.push_back(newObject);
		}
	}
}
//更新
void ClearObj::Update(int Timer) {
	//Json用
	for (auto& object : objects) {
		object->Update();
	}
}
//前面描画
const void ClearObj::FrontDraw() {
	
}
//背景描画
const void ClearObj::BackDraw() {	//Json用
	for (auto& object : objects) {
		object->Draw();
	}
}
//解放
void ClearObj::Finalize() {

}