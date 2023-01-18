#include "TitleObj.h"
#include "JsonLoader.h"
#include "ImageManager.h"
using namespace DirectX;	
//初期化
void TitleObj::Initialize() {

	ParticleManager* fire_ = new ParticleManager();
	fire_->Initialize(ImageManager::ParticleEffect);
	fire.reset(fire_);
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
	BirthParticle();
}
//前面描画
const void TitleObj::FrontDraw() {
	fire->Draw(addBle);
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

void TitleObj::BirthParticle() {
	XMFLOAT3 pos = { 0.0f,23.0f,0.0f };

	const float rnd_vel = 0.05f;
	XMFLOAT3 vel{};
	vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
	vel.y = (float)rand() / RAND_MAX * rnd_vel * 2.0f;// -rnd_vel / 2.0f;
	vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

	fire->Add(20, { pos.x,pos.y + 3.0f,pos.z }, vel, {}, 1.0f, 0.0f, { 1.0f,0.5f,0.0f,0.5f }, { 1.0f,0.5f,0.0f,0.5f });

	fire->Update();
}