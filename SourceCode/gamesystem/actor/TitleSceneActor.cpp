#include "TitleSceneActor.h"
#include "Audio.h"
#include "input.h"
#include "SceneManager.h"
#include <Easing.h>
#include "ImageManager.h"
#include "imgui.h"
#include "VariableCommon.h"
#include "ParticleEmitter.h"
TitleObj* TitleSceneActor::titleobj = nullptr;
bool TitleSceneActor::m_TitleNew = false;
//初期化
void TitleSceneActor::Initialize(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup) {
	//共通の初期化
	BaseInitialize(dxCommon);
	//スプライト生成
	IKESprite* TitlePartsSprite_[TITLE_MAX];
	const int TitleCount = TITLE_MAX;
	for (int i = 0; i < TitlePartsSprite.size(); i++) {
		TitlePartsSprite_[i] = IKESprite::Create(ImageManager::TitleParts, { 0.0f,0.0f });
		int number_index_y = i / TitleCount;
		int number_index_x = i % TitleCount;
		TitlePartsSprite_[i]->SetTextureRect(
			{ static_cast<float>(number_index_x) * PartsWidth_Cut, static_cast<float>(number_index_y) * PartsHeight_Cut },
			{ static_cast<float>(PartsWidth_Cut), static_cast<float>(PartsHeight_Cut) });
		TitlePartsSprite_[i]->SetAnchorPoint({ 0.5f,0.5f });
		TitlePartsSprite[i].reset(TitlePartsSprite_[i]);
		m_PartsSize[i] = { PartsWidth_Cut,PartsHeight_Cut };
	}

	m_PartsPos[NewGame] = { 640.0f,480.0f };
	m_PartsPos[LoadGame] = { 640.0f,640.0f };
	m_PartsPos[SelectGame] = { 640.0f,480.0f };

	IKESprite* ModePartsSprite_[MODE_MAX];
	const int ModeCount = MODE_MAX;
	for (int i = 0; i < ModePartsSprite.size(); i++) {
		ModePartsSprite_[i] = IKESprite::Create(ImageManager::ModeParts, { 0.0f,0.0f });
		int number_index_y = i / ModeCount;
		int number_index_x = i % ModeCount;
		ModePartsSprite_[i]->SetTextureRect(
			{ static_cast<float>(number_index_x) * PartsWidth_Cut, static_cast<float>(number_index_y) * PartsHeight_Cut },
			{ static_cast<float>(PartsWidth_Cut), static_cast<float>(PartsHeight_Cut) });
		ModePartsSprite_[i]->SetAnchorPoint({ 0.5f,0.5f });
		ModePartsSprite[i].reset(ModePartsSprite_[i]);
		m_ModePartsSize[i] = { PartsWidth_Cut,PartsHeight_Cut };
	}

	m_ModePartsPos[NewGame] = { 300.0f,640.0f };
	m_ModePartsPos[LoadGame] = { 800.0f,640.0f };
	m_ModePartsPos[SelectGame] = { 300.0f,640.0f };
	//タイトル
	IKESprite* TitleSprite_;
	TitleSprite_ = IKESprite::Create(ImageManager::Title, { 0.0f,0.0f });
	TitleSprite.reset(TitleSprite_);
	//モード
	IKESprite* ModeSprite_;
	ModeSprite_ = IKESprite::Create(ImageManager::ModeBack, { 0.0f,0.0f });
	ModeSprite.reset(ModeSprite_);

	const int ExplainHeight_Cut = 400;
	IKESprite* ModeEplainSprite_[EXPLAIN_MAX];
	const int EXPLAINCount = EXPLAIN_MAX;
	for (int i = 0; i < ModePartsSprite.size(); i++) {
		ModeEplainSprite_[i] = IKESprite::Create(ImageManager::ModeExplain, { 0.0f,0.0f });
		int number_index_y = i / EXPLAINCount;
		int number_index_x = i % EXPLAINCount;
		ModeEplainSprite_[i]->SetTextureRect(
			{ static_cast<float>(number_index_x) * FullWidth_Cut, static_cast<float>(number_index_y) * ExplainHeight_Cut },
			{ static_cast<float>(FullWidth_Cut), static_cast<float>(ExplainHeight_Cut) });
		ModeEplainSprite_[i]->SetAnchorPoint({ 0.5f,0.5f });
		ModeEplainSprite_[i]->SetPosition({ 640.0f,250.0f });
		ModeEplainSprite[i].reset(ModeEplainSprite_[i]);
		m_ExplainSize[i] = { FullWidth_Cut,ExplainHeight_Cut };
	}

	//カメラワーク
	camerawork = new CameraWork();
	camerawork->SetCameraType(0);

	//Json
	if (!m_TitleNew) {
		titleobj = new TitleObj();
		titleobj->Initialize();
		m_TitleNew = true;
	}
	//ライト
	m_LightPos = { 0.0f,0.0f,0.0f };

	//シーンチェンジ
	scenechange = new SceneChange();
	if (m_GameLoop) {
		scenechange->SetSubStartChange(true);
	}

	//セーブ
	save = new Save();
	m_TitleSelect = NewGame;
	m_ModeSelect = EasyMode;
	dxCommon->SetFullScreen(true);

	//オーディオ
	Audio::GetInstance()->LoadSound(0, "Resources/Sound/BGM/ruinsBGM.wav");
	Audio::GetInstance()->LoopWave(0, VolumManager::GetInstance()->GetBGMVolum());
}
//更新
void TitleSceneActor::Update(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup) {
	lightgroup->Update();
	titleobj->Update();
	//カメラの位置調整
	camerawork->Update(camera);
	///ポイントライト
	lightgroup->SetPointLightPos(0, m_LightPos);
	lightgroup->SetPointLightColor(0, XMFLOAT3(pointLightColor));
	lightgroup->SetPointLightAtten(0, XMFLOAT3(pointLightAtten));

	//ライトを徐々に小さくする
	if (scenechange->GetAddStartChange()) {
		pointLightAtten[0] = Ease(In, Cubic, 0.1f, pointLightAtten[0], 0.0f);
		pointLightAtten[1] = Ease(In, Cubic, 0.1f, pointLightAtten[1], 0.0f);
		pointLightAtten[2] = Ease(In, Cubic, 0.1f, pointLightAtten[2], 0.0f);
	}

	if (scenechange->AddBlack(0.01f)) {
		Audio::GetInstance()->StopWave(0);
		if (!m_GameLoad) {
			SceneManager::GetInstance()->ChangeScene("INTRODUCTION");
		}
		else {
			SceneManager::GetInstance()->ChangeScene("LOAD");
		}
	}
	for (int i = 0; i < TitlePartsSprite.size(); i++) {
		TitlePartsSprite[i]->SetPosition(m_PartsPos[i]);
		TitlePartsSprite[i]->SetSize(m_PartsSize[i]);
		TitlePartsSprite[i]->SetColor(m_TitleColor);
	}

	for (int i = 0; i < ModePartsSprite.size(); i++) {
		ModePartsSprite[i]->SetPosition(m_ModePartsPos[i]);
		ModePartsSprite[i]->SetSize(m_ModePartsSize[i]);
		ModePartsSprite[i]->SetColor(m_ModeColor);
	}

	for (int i = 0; i < ModeEplainSprite.size(); i++) {
		ModeEplainSprite[i]->SetSize(m_ExplainSize[i]);
		ModeEplainSprite[i]->SetColor(m_ModeColor);
	}
	TitleSprite->SetColor(m_TitleColor);
	ModeSprite->SetColor(m_ModeColor);
	ParticleEmitter::GetInstance()->FireEffect(100, { 0.0f,23.0f,0.0f }, 5.0f, 0.0f, { 1.0f,0.5f,0.0f,0.5f }, { 1.0f,0.5f,0.0f,0.5f });
	//パーティクル更新
	ParticleEmitter::GetInstance()->Update();
	//ゲーム選択
	SelectGameMode();
	//色の変更
	ColorChange();
	scenechange->Update();
	scenechange->SubBlack(0.05f);
}
//描画
void TitleSceneActor::Draw(DirectXCommon* dxCommon) {
	//ポストエフェクトをかけるか
	if (PlayPostEffect) {
		postEffect->PreDrawScene(dxCommon->GetCmdList());
		GameDraw(dxCommon);
		postEffect->PostDrawScene(dxCommon->GetCmdList());
		dxCommon->PreDraw();
		postEffect->Draw(dxCommon->GetCmdList());
		FrontDraw();
		//ImGuiDraw(dxCommon);
		//PostImGuiDraw(dxCommon);
		camerawork->ImGuiDraw();
		dxCommon->PostDraw();
	}
	else {
		postEffect->PreDrawScene(dxCommon->GetCmdList());
		postEffect->Draw(dxCommon->GetCmdList());
		postEffect->PostDrawScene(dxCommon->GetCmdList());
		dxCommon->PreDraw();
		//ImGuiDraw(dxCommon);
		//PostImGuiDraw(dxCommon);
		camerawork->ImGuiDraw();
		GameDraw(dxCommon);
		FrontDraw();
		dxCommon->PostDraw();
	}
}
//背景
void TitleSceneActor::ModelDraw(DirectXCommon* dxCommon) {
	IKEObject3d::PreDraw();
	titleobj->BackDraw();
	IKEObject3d::PostDraw();
}
//前面描画
void TitleSceneActor::FrontDraw() {
	IKEObject3d::PreDraw();
	//パーティクル描画
	ParticleEmitter::GetInstance()->FireDrawAll();
	IKEObject3d::PostDraw();
	IKESprite::PreDraw();
	TitleSprite->Draw();
	TitlePartsSprite[2]->Draw();
	for (int i = 0; i < 2; i++) {
		TitlePartsSprite[i]->Draw();
	}
	ModeSprite->Draw();
	ModePartsSprite[2]->Draw();
	for (int i = 0; i < 2; i++) {
		ModePartsSprite[i]->Draw();
	}
	ModeEplainSprite[m_ModeSelect]->Draw();
	scenechange->Draw();
	IKESprite::PostDraw();
}
//上の描画にスプライトなども混ぜた
void TitleSceneActor::GameDraw(DirectXCommon* dxCommon)
{
	//ImGuiDraw();
#pragma region 背景スプライト描画
	// 背景スプライト描画前処理

#pragma endregion
	//スプライトの描画
	ModelDraw(dxCommon);
}
//ImGui描画
void TitleSceneActor::ImGuiDraw(DirectXCommon* dxCommon) {
}
//解放
void TitleSceneActor::Finalize() {
	//３ｄのモデルのデリート
	//delete sprite;
	delete postEffect;
	delete save;
}
//ポストエフェクトのImgui
void TitleSceneActor::PostImGuiDraw(DirectXCommon* dxCommon) {
}
//ポストエフェクトの種類
void TitleSceneActor::ChangePostEffect(int PostType) {
}
void TitleSceneActor::SelectGameMode() {
	Input* input = Input::GetInstance();
	//ゲームを始めるかモードを選択するか
	//ゲームの場合
	if (m_SelectType == Game) {
		if (m_TitleSelect == NewGame && input->LeftTriggerStick(input->Down)) {
			Audio::GetInstance()->PlayWave("Resources/Sound/SE/Select.wav", VolumManager::GetInstance()->GetSEVolum());
			m_TitleSelect = LoadGame;
		}

		else if (m_TitleSelect == LoadGame && input->LeftTriggerStick(input->Up)) {
			Audio::GetInstance()->PlayWave("Resources/Sound/SE/Select.wav", VolumManager::GetInstance()->GetSEVolum());
			m_TitleSelect = NewGame;
		}
		//NewGameかLoadGameか
		if (input->PushKey(DIK_RETURN) || input->TriggerButton(input->Button_B) && !scenechange->GetSubStartChange() && !scenechange->GetAddStartChange()) {
			Audio::GetInstance()->PlayWave("Resources/Sound/SE/Buttun.wav", VolumManager::GetInstance()->GetSEVolum());
			if (m_TitleSelect == LoadGame) {
				scenechange->SetAddStartChange(true);
				m_GameLoad = true;
			}
			else {
				m_SelectType = Mode;
				m_ModeChange = true;
				m_Frame = m_FrameMin;
				m_AfterTitleAlpha = m_ColorMin;
				m_AfterModeAlpha = m_ColorMax;
			}
		}
		//タイトルの文字が動く
		TitleMove();
	}
	else {
		//モード選択
		if (m_ModeSelect == EasyMode && input->LeftTriggerStick(input->Right)) {
			Audio::GetInstance()->PlayWave("Resources/Sound/SE/Select.wav", VolumManager::GetInstance()->GetSEVolum());
			m_ModeSelect = NormalMode;
		}

		else if (m_ModeSelect == NormalMode && input->LeftTriggerStick(input->Left)) {
			Audio::GetInstance()->PlayWave("Resources/Sound/SE/Select.wav", VolumManager::GetInstance()->GetSEVolum());
			m_ModeSelect = EasyMode;
		}
		//EasyGameかNormalGameか
		if (input->PushKey(DIK_RETURN) || input->TriggerButton(input->Button_B) && !scenechange->GetSubStartChange() && !scenechange->GetAddStartChange()) {
			Audio::GetInstance()->PlayWave("Resources/Sound/SE/Buttun.wav", VolumManager::GetInstance()->GetSEVolum());
			scenechange->SetAddStartChange(true);
			m_GameLoad = false;
			if (m_ModeSelect == EasyMode) {
				m_NormalMode = false;
			}
			else {
				m_NormalMode = true;
			}
		}
		//前の画面に戻る
		if (input->TriggerButton(input->Select)) {
			m_SelectType = Game;
			m_ModeChange = true;
			m_Frame = m_FrameMin;
			m_AfterTitleAlpha = m_ColorMax;
			m_AfterModeAlpha = m_ColorMin;
		}
		//モードの文字が動く
		ModeMove();
	}
}
//パーツの動き(タイトル)
void TitleSceneActor::TitleMove() {
	if (m_TitleSelect == NewGame) {
		m_Angle[NewGame] += 2.0f;
		m_Angle2[NewGame] = m_Angle[NewGame] * (3.14f / 180.0f);
		//選択時座標が上下に動く
		m_PartsPos[SelectGame] = m_PartsPos[NewGame];
		m_Angle[LoadGame] = 0.0f;
		//選択時サイズも少し変わる
		m_PartsSize[NewGame] = { (sin(m_Angle2[NewGame]) * 32.0f) + (640.0f),
			(sin(m_Angle2[NewGame]) * 16.0f) + (128.0f) };
		m_PartsSize[SelectGame] = m_PartsSize[NewGame];
		m_PartsSize[LoadGame] = { 640.0f,128.0f };
	}
	else {
		m_Angle[LoadGame] += 2.0f;
		m_Angle2[LoadGame] = m_Angle[LoadGame] * (3.14f / 180.0f);
		//選択時座標が上下に動く
		m_PartsPos[SelectGame] = m_PartsPos[LoadGame];
		m_Angle[NewGame] = 0.0f;
		//選択時サイズも少し変わる
		m_PartsSize[LoadGame] = { (sin(m_Angle2[LoadGame]) * 32.0f) + (640.0f),
			(sin(m_Angle2[LoadGame]) * 16.0f - 16.0f) + (128.0f) };
		m_PartsSize[SelectGame] = m_PartsSize[LoadGame];
		m_PartsSize[NewGame] = { 640.0f,128.0f };
	}
}
//パーツの動き(モード)
void TitleSceneActor::ModeMove() {
	if (m_ModeSelect == EasyMode) {
		m_Angle[EasyMode] += 2.0f;
		m_Angle2[EasyMode] = m_Angle[EasyMode] * (3.14f / 180.0f);
		//選択時座標が上下に動く
		m_ModePartsPos[SelectMode] = m_ModePartsPos[EasyMode];
		//選択時サイズも少し変わる
		m_ModePartsSize[EasyMode] = { (sin(m_Angle2[EasyMode]) * 32.0f) + (640.0f),
			(sin(m_Angle2[EasyMode]) * 16.0f) + (128.0f) };
		m_ModePartsSize[SelectMode] = m_ModePartsSize[EasyMode];
		m_ModePartsSize[NormalMode] = { 640.0f,128.0f };
		m_Angle[NormalMode] = 0.0f;
	}
	else {
		m_Angle[NormalMode] += 2.0f;
		m_Angle2[NormalMode] = m_Angle[NormalMode] * (3.14f / 180.0f);
		//選択時座標が上下に動く
		m_ModePartsPos[SelectMode] = m_ModePartsPos[NormalMode];
		//選択時サイズも少し変わる
		m_ModePartsSize[NormalMode] = { (sin(m_Angle2[NormalMode]) * 32.0f) + (640.0f),
			(sin(m_Angle2[NormalMode]) * 16.0f - 16.0f) + (128.0f) };
		m_ModePartsSize[SelectMode] = m_ModePartsSize[NormalMode];
		m_ModePartsSize[EasyMode] = { 640.0f,128.0f };
		m_Angle[EasyMode] = 0.0f;
	}
}
//色の変更
void TitleSceneActor::ColorChange() {
	if (m_ModeChange) {
		if (m_Frame < m_FrameMax) {
			m_Frame += 0.1f;
		}
		else {
			m_Frame = m_FrameMax;
			m_ModeChange = false;
		}

		m_TitleColor.w = Ease(In, Cubic, m_Frame, m_TitleColor.w, m_AfterTitleAlpha);
		m_ModeColor.w = Ease(In, Cubic, m_Frame, m_ModeColor.w, m_AfterModeAlpha);
	}
}