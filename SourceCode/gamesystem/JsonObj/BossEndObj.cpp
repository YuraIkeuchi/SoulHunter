#include "BossEndObj.h"
#include "ModelManager.h"
#include "imgui.h"
#include "JsonLoader.h"
#include "ImageManager.h"
using namespace DirectX;
//初期化
void BossEndObj::Initialize() {

	jsonData = JsonLoader::LoadFile("BossApp");

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

	//スプライト生成
	IKESprite* CurtainSprite_[2];
	//gaussian = new PostEffect();
	for (int i = 0; i < CurtainSprite.size(); i++) {
		CurtainSprite_[i] = IKESprite::Create(ImageManager::Curtain, { 0.0f,0.0f });
		CurtainSprite_[i]->SetAnchorPoint({ 0.5f,0.0f });
		CurtainSprite[i].reset(CurtainSprite_[i]);
	}

	CurtainSprite[0]->SetPosition({ 640.0f,0.0f });
	CurtainSprite[1]->SetPosition({ 640.0f,620.0f });

	IKESprite* SkipSprite_;
	SkipSprite_ = IKESprite::Create(ImageManager::SkipText, { 0.0f,0.0f });
	SkipSprite_->SetAnchorPoint({ 0.5f,0.0f });
	SkipSprite_->SetPosition({ 1000.0f,620.0f });
	SkipSprite.reset(SkipSprite_);

}
//更新
void BossEndObj::Update() {
	//pos = player->GetPosition();
	//ボス登場フラグが立ったらタイマーが動く
	if (m_AppStart && !m_EndApp) {
		//登場の間はtrue
		m_App = true;
		m_AppTimer++;
		//一定フレームでフラグ終了
		if (m_AppTimer == 800) {
			//m_App = false;
			m_AppStart = false;
			m_EndApp = true;
		}
	}

	//Json用
	for (auto& object : objects) {
		object->Update();
	}

}
//前面描画
const void BossEndObj::FrontDraw() {
}
//背景描画
const void BossEndObj::BackDraw() {
	/*ImGui::Begin("BossApp");
	ImGui::Text("m_App:%d", m_App);
	ImGui::Text("m_AppTimer:%d", m_AppTimer);
	ImGui::Text("m_End:%d", m_EndApp);
	ImGui::Text("m_AppStart:%d", m_AppStart);
	ImGui::End();*/
	//Json用
	for (auto& object : objects) {
		object->Draw();
	}

	IKESprite::PreDraw();
	for (int i = 0; i < CurtainSprite.size(); i++) {
		CurtainSprite[i]->Draw();
	}
	SkipSprite->Draw();
	IKESprite::PostDraw();
}
//解放
void BossEndObj::Finalize() {

}