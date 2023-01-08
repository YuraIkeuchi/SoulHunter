#include "LoadScene.h"
#include "Audio.h"
#include "input.h"
#include "DebugText.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include "imgui.h"
//初期化
void LoadScene::Initialize(DirectXCommon* dxCommon) {

	BaseInitialize(dxCommon);
	//スプライト生成
	const int ExplainLoadCount = 2;
	IKESprite* loadsprite_[2];
	//gaussian = new PostEffect();
	for (int i = 0; i < 2; i++) {
		loadsprite_[i] = IKESprite::Create(ImageManager::LoadText1, { 0.0f,0.0f });
		loadsprite_[i]->SetAnchorPoint({ 0.5f,0.5f });
		loadsprite_[i]->SetPosition({ 640.0f,320.0f });
		int number_index_y = i / ExplainLoadCount;
		int number_index_x = i % ExplainLoadCount;
		loadsprite_[i]->SetTextureRect(
			{ static_cast<float>(number_index_x) * ExplainWidth_Cut, static_cast<float>(number_index_y) * ExplainHeight_Cut },
			{ static_cast<float>(ExplainWidth_Cut), static_cast<float>(ExplainHeight_Cut) });
		loadsprite_[i]->SetSize({ ExplainWidth_Cut,ExplainHeight_Cut });
		loadsprite[i].reset(loadsprite_[i]);
	}

	const int NowLoadCount = 4;
	IKESprite* nowsprite_[4];
	for (int i = 0; i < 4; i++) {
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
	spotLightDir[0] = 0;
	spotLightDir[1] = 0;
	spotLightDir[2] = 1;

	//スプライト生成
	scenechange = new SceneChange();
	scenechange->SetSubStartChange(true);
	m_LoadNumber = rand() % 2;

	//ポストエフェクトをリセットする
	PlayPostEffect = false;
}
//更新
void LoadScene::Update(DirectXCommon* dxCommon) {
	ParticleManager::GetInstance()->Update();
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
			block = new Block();
		}
		else if (m_LoadAnimeTimer == 15 && m_LoadAnimeCount == 3) {
			m_LoadChackCount++;
			minimap = new MiniMap();
		}

		if (m_LoadChackCount == 2) {
			NewFinish();
		}
	}

	//一定時間でシーンが変わる
	if (m_LoadTimer == 200) {
		scenechange->SetAddStartChange(true);
	}

	//そのままシーンチェンジ
	if (scenechange->AddBlack(0.05f)) {
		SceneManager::GetInstance()->ChangeScene("FIRSTSTAGE");
	}

	loadsprite[m_LoadNumber]->SetColor(m_color);
	nowsprite[m_LoadAnimeCount]->SetColor(m_color);

	lightGroup->Update();

	//camera->SetEye(m_EyePos);
	//camera->SetTarget(m_TargetPos);
	//camera->Update();
	//expandchange->Update();
	scenechange->Update();
	scenechange->SubBlack(0.05f);
	ChangePostEffect(PostType);
}
//描画
void LoadScene::Draw(DirectXCommon* dxCommon) {

	//ポストエフェクトをかけるか
	if (PlayPostEffect) {
		postEffect->PreDrawScene(dxCommon->GetCmdList());
		GameDraw(dxCommon);
		postEffect->PostDrawScene(dxCommon->GetCmdList());
		dxCommon->PreDraw();

		postEffect->Draw(dxCommon->GetCmdList());
		SpriteDraw();

		//ImGuiDraw(dxCommon);
		//PostImGuiDraw(dxCommon);

		//player->ImGuiDraw();
		//particleobj->ImGuiDraw();
		dxCommon->PostDraw();
	}
	else {
		postEffect->PreDrawScene(dxCommon->GetCmdList());
		postEffect->Draw(dxCommon->GetCmdList());
		postEffect->PostDrawScene(dxCommon->GetCmdList());

		dxCommon->PreDraw();
		//ImGuiDraw(dxCommon);
		//PostImGuiDraw(dxCommon);
		GameDraw(dxCommon);
		SpriteDraw();
		/*player->ImGuiDraw();
		for (int i = 0; i < 2; i++) {
			enemy[i]->ImGuiDraw();
		}*/
		//particleobj->ImGuiDraw();
		dxCommon->PostDraw();
	}
}
//背景描画
void LoadScene::ModelDraw(DirectXCommon* dxCommon) {
	IKEObject3d::PreDraw();
	IKEObject3d::PostDraw();
}
//前面描画
void LoadScene::SpriteDraw() {
	IKESprite::PreDraw();
	loadsprite[m_LoadNumber]->Draw();
	nowsprite[m_LoadAnimeCount]->Draw();
	scenechange->Draw();
	IKESprite::PostDraw();
}
//上の描画にスプライトなども混ぜた
void LoadScene::GameDraw(DirectXCommon* dxCommon)
{
	//ImGuiDraw();
#pragma region 背景スプライト描画
	// 背景スプライト描画前処理

#pragma endregion
	//スプライトの描画
	ModelDraw(dxCommon);
	//FBXの描画
	//object1->Draw(dxCommon->GetCmdList());
}
//ImGuiの描画
void LoadScene::ImGuiDraw(DirectXCommon* dxCommon) {
}
//解放
void LoadScene::Finalize() {
	//３ｄのモデルのデリート
	//delete sprite;
	delete save;
}
//ポストエフェクトのImGui
void LoadScene::PostImGuiDraw(DirectXCommon* dxCommon) {
	{
		if (PlayPostEffect) {
			ImGui::Begin("PostType");
			ImGui::SetWindowPos(ImVec2(600, 450));
			ImGui::SetWindowSize(ImVec2(280, 150));
			ImGui::Text("m_ChangePostEffect:%d", m_ChangePostEffect);
			if (ImGui::RadioButton("Stripe", &PostType)) {

				PostType = Stripe;
				m_ChangePostEffect = true;
				//ChangePostEffect(PostType);
			}
			if (ImGui::RadioButton("Gaussian", &PostType)) {
				PostType = Blur;
				m_ChangePostEffect = true;

			}
			ImGui::End();
		}
	}
	{
		ImGui::Begin("postEffect");
		ImGui::SetWindowPos(ImVec2(700, 150));
		ImGui::SetWindowSize(ImVec2(280, 150));
		if (ImGui::RadioButton("PostEffect", &PlayPostEffect)) {
			PlayPostEffect = true;
		}
		if (ImGui::RadioButton("Default", &PlayPostEffect)) {
			PlayPostEffect = false;
		}
		ImGui::End();
	}
}
//ポストエフェクト変更
void LoadScene::ChangePostEffect(int PostType) {
	if (m_ChangePostEffect) {

		if (PostType == Stripe) {

			postEffect->CreateGraphicsPipeline(L"Resources/Shaders/PostEffectTestVS.hlsl", L"Resources/Shaders/PostEffectTestPS.hlsl");
		}
		else if (PostType == Blur) {

			postEffect->CreateGraphicsPipeline(L"Resources/Shaders/GaussianVS.hlsl", L"Resources/Shaders/GaussianPS.hlsl");
		}

		m_ChangePostEffect = false;
	}
}
