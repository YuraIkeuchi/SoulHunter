#include "LoadSceneActor.h"
#include "Audio.h"
#include "input.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include "imgui.h"
#include "VariableCommon.h"
//初期化
void LoadSceneActor::Initialize(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup) {

	BaseInitialize(dxCommon);
	//スプライト生成
	const int ExplainLoadCount = Load_Max;
	IKESprite* loadsprite_[Load_Max];
	for (int i = 0; i < Load_Max; i++) {
		loadsprite_[i] = IKESprite::Create(ImageManager::LoadText1, { 0.0f,0.0f });
		loadsprite_[i]->SetAnchorPoint({ 0.5f,0.5f });
		loadsprite_[i]->SetPosition(m_Position);
		int number_index_y = i / ExplainLoadCount;
		int number_index_x = i % ExplainLoadCount;
		loadsprite_[i]->SetTextureRect(
			{ static_cast<float>(number_index_x) * ExplainWidth_Cut, static_cast<float>(number_index_y) * ExplainHeight_Cut },
			{ static_cast<float>(ExplainWidth_Cut), static_cast<float>(ExplainHeight_Cut) });
		loadsprite_[i]->SetSize({ ExplainWidth_Cut,ExplainHeight_Cut });
		loadsprite[i].reset(loadsprite_[i]);
	}

	const int NowLoadCount = Now_Max;
	IKESprite* nowsprite_[Now_Max];
	for (int i = 0; i < Now_Max; i++) {
		nowsprite_[i] = IKESprite::Create(ImageManager::NowLoad1, { 0.0f,0.0f });
		nowsprite_[i]->SetAnchorPoint({ 0.5f,0.5f });
		nowsprite_[i]->SetPosition({ 1000.0f,680.0f });
		int number_index_y = i / NowLoadCount;
		int number_index_x = i % NowLoadCount;
		nowsprite_[i]->SetTextureRect(
			{ static_cast<float>(number_index_x) * LoadWidth_Cut, static_cast<float>(number_index_y) * LoadHeight_Cut },
			{ static_cast<float>(LoadWidth_Cut), static_cast<float>(LoadHeight_Cut) });
		nowsprite_[i]->SetSize({ LoadWidth_Cut,LoadHeight_Cut });
		nowsprite[i].reset(nowsprite_[i]);
	}

	//カメラ関係
	camerawork = new CameraWork();
	// カメラ注視点をセット
	camerawork->SetPlayer(player);
	//スプライト生成
	scenechange = new SceneChange();
	scenechange->SetSubStartChange(true);
	m_LoadNumber = rand() % 5;
	//ポストエフェクトをリセットする
	PlayPostEffect = false;
	if (!s_New) {
		SceneManager::GetInstance()->SetLoad(true);
	}
}
//更新
void LoadSceneActor::Update(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup) {

	Input* input = Input::GetInstance();

	m_LoadTimer++;
	m_LoadAnimeTimer++;

	if (m_LoadAnimeTimer == 30) {
		m_LoadAnimeCount++;
		m_LoadAnimeTimer = 0;
	}

	if (m_LoadAnimeCount == 4) {
		m_LoadAnimeCount = 0;
	}

	if (!s_New) {
		if (m_LoadAnimeTimer == 15 && m_LoadAnimeCount == 2) {
			m_LoadChackCount++;
		}
		else if (m_LoadAnimeTimer == 15 && m_LoadAnimeCount == 3) {
			m_LoadChackCount++;
		}

		if (m_LoadChackCount == 2) {
			NewFinish();
		}
	}

	//一定時間でシーンが変わる
	if (m_LoadTimer >= 200 && !SceneManager::GetInstance()->GetLoad()) {
		scenechange->SetAddStartChange(true);
	}

	//そのままシーンチェンジ
	if (scenechange->AddBlack(0.05f)) {
		SceneManager::GetInstance()->ChangeScene("FIRSTSTAGE");
	}

	loadsprite[m_LoadNumber]->SetColor(m_color);
	loadsprite[m_LoadNumber]->SetPosition(m_Position);
	loadsprite[m_LoadNumber]->SetSize(m_Size);
	nowsprite[m_LoadAnimeCount]->SetColor(m_color);

	lightgroup->Update();
	MoveLoad();
	scenechange->Update();
	scenechange->SubBlack(0.05f);
}
//描画
void LoadSceneActor::Draw(DirectXCommon* dxCommon) {

	//ポストエフェクトをかけるか
	if (PlayPostEffect) {
		postEffect->PreDrawScene(dxCommon->GetCmdList());
		GameDraw(dxCommon);
		postEffect->PostDrawScene(dxCommon->GetCmdList());
		dxCommon->PreDraw();
		postEffect->Draw(dxCommon->GetCmdList());
		SpriteDraw();
		dxCommon->PostDraw();
	}
	else {
		postEffect->PreDrawScene(dxCommon->GetCmdList());
		postEffect->Draw(dxCommon->GetCmdList());
		postEffect->PostDrawScene(dxCommon->GetCmdList());
		dxCommon->PreDraw();
		GameDraw(dxCommon);
		SpriteDraw();
		dxCommon->PostDraw();
	}
}
//背景描画
void LoadSceneActor::ModelDraw(DirectXCommon* dxCommon) {
	IKEObject3d::PreDraw();
	IKEObject3d::PostDraw();
}
//前面描画
void LoadSceneActor::SpriteDraw() {
	IKESprite::PreDraw();
	loadsprite[m_LoadNumber]->Draw();
	nowsprite[m_LoadAnimeCount]->Draw();
	scenechange->Draw();
	IKESprite::PostDraw();
}
//上の描画にスプライトなども混ぜた
void LoadSceneActor::GameDraw(DirectXCommon* dxCommon)
{
	//スプライトの描画
	ModelDraw(dxCommon);
}
//ImGuiの描画
void LoadSceneActor::ImGuiDraw(DirectXCommon* dxCommon) {
}
//解放
void LoadSceneActor::Finalize() {
	//delete save;
}
//
void LoadSceneActor::MoveLoad() {
	m_Angle += 2.0f;
	m_Angle2 = m_Angle * (3.14f / 180.0f);

	m_Size = { (sin(m_Angle2) * 32.0f) + (1028.0f),
	(sin(m_Angle2) * 16.0f) + (128.0f), };
}