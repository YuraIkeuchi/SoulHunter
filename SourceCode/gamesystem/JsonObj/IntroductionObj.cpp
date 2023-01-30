#include "IntroductionObj.h"
#include "ModelManager.h"
#include "JsonLoader.h"
using namespace DirectX;
//初期化
void IntroductionObj::Initialize() {
	//ステージ背景
	modelskydome = ModelManager::GetInstance()->GetModel(ModelManager::Skydome);
	IKEObject3d* objskydome_ = new IKEObject3d();
	objskydome_ = IKEObject3d::Create();
	objskydome_->SetModel(modelskydome);
	objskydome_->SetPosition({ 0.0f, 0.0f, 0.0f });
	objskydome_->SetRotation({ 0.0f, 90.0f, 0.0f });
	objskydome_->SetScale({ 8.0f,8.0f,8.0f });
	objskydome.reset(objskydome_);

	//Json
	jsonData = JsonLoader::LoadFile("Introduction");

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

			newObject->SetTiling(20.0f);
			// 配列に登録
			objects.push_back(newObject);
		}
		//フォグ
		if (objectData.GimmickName == "FogGimmick") {
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

			newObject->SetTiling(20.0f);
			newObject->SetFog(true);
			// 配列に登録
			fogobjects.push_back(newObject);
		}
		//地面
		if (objectData.GimmickName == "Ground") {
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

			newObject->SetTiling(20.0f);
			// 配列に登録
			groundobjects.push_back(newObject);
		}
	}
}
//更新
void IntroductionObj::Update(int Timer) {

	if (Timer >= 120) {
		m_OffSet = 0.0f;
	}
	else {
		m_OffSet = -0.01f;
	}
	objskydome->Update();
	objskydome->SetAddOffset(0.0005f);
	//Json用
	for (auto& object : objects) {
		object->Update();
	}

	for (auto& object : fogobjects) {
		object->Update();
	}

	for (auto& object : groundobjects) {
		object->Update();
		object->SetAddOffset(m_OffSet);
	}
}
//前面描画
const void IntroductionObj::FrontDraw() {
	
}
//背景描画
const void IntroductionObj::BackDraw() {
	objskydome->Draw();
	//objskydome->Draw();
	//Json用
	for (auto& object : objects) {
		object->Draw();
	}
	for (auto& object : fogobjects) {
		object->Draw();
	}
	for (auto& object : groundobjects) {
		object->Draw();
	}
}
//解放
void IntroductionObj::Finalize() {

}