#include "TitleObj.h"
#include "ModelManager.h"
#include "ImageManager.h"
#include "JsonLoader.h"
using namespace DirectX;
//初期化
void TitleObj::Initialize() {
	//パーティクル
	m_ParticleCount = 0;

	jsonData = JsonLoader::LoadFile("Title");


	//リスポーン位置
	for (auto& objectData : jsonData->objects) {
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

			newObject->SetTiling(30.0f);
			// 配列に登録
			objects.push_back(newObject);
		}
	}
}
//更新
void TitleObj::Update() {
	//Json用
	for (auto& object : objects) {
		object->Update();
	}

	//炎のパーティクル
	if (!m_StopParticle) {
		m_ParticleCount++;
	}
	else {
		m_ParticleCount = 0;
	}


	if (m_ParticleCount > 6) {
		m_ParticleCount = 0;
	}
}
//前面描画
const void TitleObj::FrontDraw() {
	//particletex->Draw();
}
//背景描画
const void TitleObj::BackDraw() {
	//Json用
	for (auto& object : objects) {
		object->Draw();
	}
}
//解放
void TitleObj::Finalize() {

}