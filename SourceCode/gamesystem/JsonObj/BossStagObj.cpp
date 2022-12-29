#include "BossStagObj.h"
#include "ModelManager.h"
#include "imgui.h"
#include "JsonLoader.h"
#include "ImageManager.h"
using namespace DirectX;
//初期化
void BossStagObj::Initialize() {

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
	//パーティクル
	ParticleTex* particletex_;
	particletex_ = new ParticleTex();
	particletex_->Initialize();
	particletex.reset(particletex_);

}
//更新
void BossStagObj::AppUpdate() {
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
void BossStagObj::EndUpdate() {
	m_EndTimer++;
	//Json用
	for (auto& object : objects) {
		object->Update();
	}
	m_ParticleCount++;
	if (m_ParticleCount > 2) {
		m_ParticleCount = 0;
	}
	//パーティクル
	particletex->SetStartColor({ 1.0f,0.5f,0.0f,1.0f });
	particletex->SetStartScale(0.5f);
	particletex->SetParticleBreak(true);
	particletex->SetParticleBillboard(true);
	particletex->Update({ 0.0f,8.0f,20.0f }, m_ParticleCount, 2, 2);
}
//前面描画
const void BossStagObj::FrontDraw() {
	//パーティクルの描画
	IKEObject3d::PreDraw();
	particletex->Draw();
	IKEObject3d::PostDraw();
	IKESprite::PreDraw();
	for (int i = 0; i < CurtainSprite.size(); i++) {
		CurtainSprite[i]->Draw();
	}
	SkipSprite->Draw();
	IKESprite::PostDraw();

}
//背景描画
const void BossStagObj::BackDraw() {
	ImGui::Begin("BossApp");
	ImGui::Text("m_EndTimer:%d", m_EndTimer);
	ImGui::End();

	IKEObject3d::PreDraw();
	//Json用
	for (auto& object : objects) {
		object->Draw();
	}
	IKEObject3d::PostDraw();
}
//解放
void BossStagObj::Finalize() {

}