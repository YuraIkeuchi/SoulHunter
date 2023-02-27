#include "EditorSceneActor.h"
#include "Audio.h"
#include "SceneManager.h"
#include "imgui.h"
#include "VariableCommon.h"
#include "PlayerSkill.h"
#include "ParticleEmitter.h"
//初期化
void EditorSceneActor::Initialize(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup)
{
	//各クラスのnew
	player = new GamePlayer();
	skillpause = new SkillPause();
	option = new Option();
	pause = new Pause();
	mapchange = new MapChange();
	save = new Save();
	chest = new Chest();
	camerawork = new CameraWork();
	enemymanager = new EnemyManager();
	backmanager = new BackObjManager();
	camerawork->SetCameraType(2);
	OpenBrowser* openbrowser_;
	openbrowser_ = new OpenBrowser();
	openbrowser.reset(openbrowser_);
	dxCommon->SetFullScreen(false);
	//共通の初期化
	BaseInitialize(dxCommon);
	//プレイヤー初期化
	PlayerInitialize();
	//カメラの初期化
	CameraInitialize();
	//背景OBJの初期化
	BackObjInitialize();
	//ポーズの初期化
	PauseInitialize();
	//プレイヤーの手助けになるものの初期化
	HelperInitialize();
	//シーン遷移
	scenechange = new SceneChange();
	scenechange->SetSubStartChange(true);
	//エディタ
	ImGuiEditor* imguieditor_;
	imguieditor_ = new ImGuiEditor();
	imguieditor.reset(imguieditor_);
	enemymanager->SetPause(pause);
	enemymanager->SetChest(chest);
	enemymanager->LoadEnemyParam(StageNumber, player, block, lightgroup);
	backmanager->LoadObjParam(StageNumber, player, lightgroup);
	BGMStart = true;

	//エディタモードは最初は敵を止める
	m_MoveEnemy = false;

	//ポストエフェクトのファイル指定
	postEffect->CreateGraphicsPipeline(L"Resources/Shaders/PostEffectTestVS.hlsl", L"Resources/Shaders/NewToneMapPS.hlsl");

	ParticleEmitter::GetInstance()->AllDelete();

	PlayPostEffect = true;
}
//更新
void EditorSceneActor::Update(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup)
{
	//各クラス更新
	AllUpdate(camera);
	//光の配置
	LightSet(lightgroup);
	//シーンやマップの変更の処理
	ChangeUpdate();
	//音楽の音量が変わる
	Audio::GetInstance()->VolumChange(0, VolumManager::GetInstance()->GetBGMVolum());
	//エディタ時はHPが減らない
	player->SetHP(5);
	//マップの読み込み
	MapInitialize();
	//敵の位置セーブ
	if (m_EditorSave) {
		enemymanager->OpenEnemyParam(StageNumber);
		enemymanager->SaveEnemyParam(StageNumber);
		m_EditorSave = false;
	}

	//敵の位置ロード
	if (m_EditorLoad) {
		enemymanager->LoadEnemyParam(StageNumber, player, block, lightgroup);
		m_EditorLoad = false;
	}

	//背景OBJの位置セーブ
	if (m_ObjSave) {
		backmanager->OpenObjParam(StageNumber);
		backmanager->SaveObjParam(StageNumber);
		m_ObjSave = false;
	}

	//背景OBJの位置ロード
	if (m_ObjLoad) {
		backmanager->LoadObjParam(StageNumber, player, lightgroup);
		m_ObjLoad = false;
	}

	//ゲームのセーブ
	if (save->GetGameSave()) {
		StartStage = StageNumber;
		SaveGame();
		save->SetGameSave(false);
	}

	//エディタ関係
	EditorUpdate();

	//要素全削除(敵)
	if (m_EnemyDelete) {
		enemymanager->DeleteEnemy();
		m_EnemyDelete = false;
	}
	//要素全削除(OBJ)
	if (m_ObjDelete) {
		backmanager->ObjDelete();
		m_ObjDelete = false;
	}

	//マップチェンジ
	if (m_MapChange) {
		StageMapChange(StageNumber,lightgroup);
		m_MapChange = false;
	}

	m_PlayerPos = camera->GetEye();
}
//描画
void EditorSceneActor::Draw(DirectXCommon* dxCommon)
{
	//描画方法
	//ポストエフェクトをかけるか
	if (PlayPostEffect) {
		postEffect->PreDrawScene(dxCommon->GetCmdList());
		BackDraw(dxCommon);
		postEffect->PostDrawScene(dxCommon->GetCmdList());
		dxCommon->PreDraw();
		postEffect->Draw(dxCommon->GetCmdList());
		FrontDraw(dxCommon);
		ImGuiDraw(dxCommon);
		//player->ImGuiDraw();
		//enemymanager->ImGuiDraw();
		camerawork->ImGuiDraw();
		postEffect->ImGuiDraw();
		dxCommon->PostDraw();
	}
	else {
		postEffect->PreDrawScene(dxCommon->GetCmdList());
		postEffect->Draw(dxCommon->GetCmdList());
		postEffect->PostDrawScene(dxCommon->GetCmdList());
		dxCommon->PreDraw();
		ImGuiDraw(dxCommon);
		camerawork->ImGuiDraw();
		BackDraw(dxCommon);
		FrontDraw(dxCommon);
		dxCommon->PostDraw();
	}
}
//解放
void EditorSceneActor::Finalize()
{
	delete postEffect;
}
//モデルの描画
void EditorSceneActor::ModelDraw(DirectXCommon* dxCommon) {
#pragma region 3Dオブジェクト描画
	//背景は先に描画する

}
//後ろの描画
void EditorSceneActor::BackDraw(DirectXCommon* dxCommon)
{
	IKEObject3d::PreDraw();
	backmanager->AlwaysDraw(dxCommon);
	block->Draw(m_PlayerPos);
	if (StageNumber != BossMap) {
		backmanager->Draw(dxCommon);
	}
	save->Draw();
	//敵の描画
	enemymanager->Draw(dxCommon);
	tutorialtext->Draw();
	ParticleEmitter::GetInstance()->SmokeDrawAll();
	ParticleEmitter::GetInstance()->FireDrawAll();
	//たからばこ
	chest->Draw();
	//パーティクル描画
	ParticleEmitter::GetInstance()->FlontDrawAll();
	//ImGuiのOBJの描画
	imguieditor->ObjDraw();
	// 3Dオブジェクト描画後処理
	IKEObject3d::PostDraw();
}
//ポストエフェクトがかからない
void EditorSceneActor::FrontDraw(DirectXCommon* dxCommon) {
	IKEObject3d::PreDraw();
	IKESprite::PreDraw();
	ui->Draw();
	mapchange->Draw();
	pause->Draw();
	chest->SpriteDraw();
	scenechange->Draw();
	chest->MapDraw(minimap->GetMapType(), minimap->GetMapColor(), pause->GetIsPause(), pause->GetPauseNumber());
	enemymanager->MapDraw(minimap->GetMapType(), minimap->GetMapColor());
	IKESprite::PostDraw();
#pragma endregion
}
//IMGuiの描画
void EditorSceneActor::ImGuiDraw(DirectXCommon* dxCommon) {
	ImGui::Begin("Editor");
	ImGui::SetWindowPos(ImVec2(1000, 150));
	ImGui::SetWindowSize(ImVec2(280, 150));
	if (ImGui::RadioButton("m_GameScene", &m_SceneChange)) {
		scenechange->SetAddStartChange(true);
		m_SceneChange = true;
		m_SceneMigration = GamePlay;
	}
	if (ImGui::RadioButton("m_TitleScene", &m_SceneChange)) {
		scenechange->SetAddStartChange(true);
		m_SceneChange = true;
		m_SceneMigration = Title;
	}
	if (ImGui::RadioButton("m_EnemyDelete", &m_EnemyDelete)) {
		m_EnemyDelete = true;
	}
	if (ImGui::RadioButton("m_ObjDelete", &m_ObjDelete)) {
		m_ObjDelete = true;
	}
	if (ImGui::RadioButton("Move", &m_MoveEnemy)) {
		m_MoveEnemy = true;
	}
	ImGui::End();
	//WEBページオープン
	{
		ImGui::Begin("Open");
		ImGui::SetWindowPos(ImVec2(1000, 450));
		ImGui::SetWindowSize(ImVec2(280, 300));
		if (ImGui::Button("OPENWEB")) {
			openbrowser->OpenWebPage();
		}
		ImGui::End();
	}
	//敵生成
	imguieditor->EditorImGuiDraw();
	{
		//マップ切り替え
		ImGui::Begin("MapNumber");
		ImGui::SetWindowPos(ImVec2(560, 500));
		ImGui::SetWindowSize(ImVec2(280, 230));
		if (ImGui::Button("Map1", ImVec2(90, 50))) {
			StageNumber = Map1;
			m_MapChange = true;
		}
		if (ImGui::Button("Map2", ImVec2(90, 50))) {
			StageNumber = Map2;
			m_MapChange = true;
		}
		if (ImGui::Button("Map3", ImVec2(90, 50))) {
			StageNumber = Map3;
			m_MapChange = true;
		}
		if (ImGui::Button("Map4", ImVec2(90, 50))) {
			StageNumber = Map4;
			m_MapChange = true;
		}
		if (ImGui::Button("Map5", ImVec2(90, 50))) {
			StageNumber = Map5;
			m_MapChange = true;
		}
		if (ImGui::Button("Map6", ImVec2(90, 50))) {
			StageNumber = Map6;
			m_MapChange = true;
		}
		if (ImGui::Button("TutorialMap", ImVec2(90, 50))) {
			StageNumber = TutoRial;
			m_MapChange = true;
		}
		ImGui::End();
	}
	//セーブとロード
	{
		ImGui::Begin("Save & Load");
		ImGui::SetWindowPos(ImVec2(1000, 0));
		ImGui::SetWindowSize(ImVec2(280, 150));
		if (ImGui::Button("EnemySave", ImVec2(90, 50))) {
			m_EditorSave = true;
			enemymanager->SaveNum();
		}
		if (ImGui::Button("EnemyLoad", ImVec2(90, 50))) {
			m_EditorLoad = true;
		}

		if (ImGui::Button("OBJSave", ImVec2(90, 50))) {
			m_ObjSave = true;
			backmanager->SaveNum();
		}
		if (ImGui::Button("OBJLoad", ImVec2(90, 50))) {
			m_ObjLoad = true;
		}

		ImGui::Unindent();
		ImGui::End();
	}
}
//マップの読み込みとそれに合わせた初期化
void EditorSceneActor::MapInitialize() {
	if (StageChange) {
		switch (StageNumber)
		{
		case Map1:
			block->Initialize(map1, 0, StageNumber);
			minimap->InitMap(map1, StageNumber);
		case Map2:
			block->Initialize(map2, 0, StageNumber);
			minimap->InitMap(map2, StageNumber);
		case Map3:
			block->Initialize(map3, 0, StageNumber);
			minimap->InitMap(map3, StageNumber);
		case Map4:
			block->Initialize(map4, 0, StageNumber);
			minimap->InitMap(map4, StageNumber);
		case Map5:
			block->Initialize(map5, 0, StageNumber);
			minimap->InitMap(map5, StageNumber);
		case Map6:
			block->Initialize(map6, 0, StageNumber);
			minimap->InitMap(map6, StageNumber);
		case BossMap:
			block->Initialize(bossmap, 0, StageNumber);
			minimap->InitMap(bossmap, StageNumber);
		case TutoRial:
			block->Initialize(tutorialmap, 0, StageNumber);
			minimap->InitMap(tutorialmap, StageNumber);
		default:
			break;
		}
		StageChange = false;
		player->SetGoalDir(0);
	}
}
//マップ切り替えの関数
void EditorSceneActor::StageMapChange(int StageNumber,LightGroup* lightgroup) {
	enemymanager->DeleteEnemy();
	backmanager->ObjDelete();
	m_MoveEnemy = false;
	mapchange->SetAddStartChange(true);
	save->InitSave(StageNumber);
	tutorialtext->InitBoard(StageNumber);
	chest->InitChest(StageNumber);
	enemymanager->LoadEnemyParam(StageNumber, player, block, lightgroup);
	backmanager->LoadObjParam(StageNumber, player, lightgroup);
	backmanager->LoadBackObjAlways(StageNumber);
}
//各クラスの更新
void EditorSceneActor::AllUpdate(DebugCamera* camera) {

	scenechange->Update();
	scenechange->SubBlack(0.05f);
	mapchange->Update();
	mapchange->SubBlack();
	block->Update(m_PlayerPos);

	//ぷれいやーの更新
	if (!pause->GetIsPause() && !chest->GetExplain()) {
		player->Editor();
	}
	else {
		player->Pause();
	}

	//設置した敵の更新
	enemymanager->Update(m_MoveEnemy);
	backmanager->Update();

	tutorialtext->Update();

	//その他の更新
	ParticleEmitter::GetInstance()->Update();
	minimap->SetMiniPlayerPos(StageNumber);
	pause->Update();
	chest->Update();
	VolumManager::GetInstance()->Update();
	save->Update();
	ui->Update();
	camerawork->Update(camera);
}
//ライトの位置
void EditorSceneActor::LightSet(LightGroup* lightgroup) {
	lightgroup->Update();
	///ポイントライト
	lightgroup->SetPointLightPos(0, XMFLOAT3(player->GetPosition().x, player->GetPosition().y, player->GetPosition().z - 5.0f));
	lightgroup->SetPointLightColor(0, XMFLOAT3(pointLightColor));
	lightgroup->SetPointLightAtten(0, XMFLOAT3({ 10.0f,10.0f,10.0f }));

	lightgroup->SetPointLightPos(1, XMFLOAT3(save->GetPosition().x, save->GetPosition().y + 2.0f, save->GetPosition().z + 2.0f));
	lightgroup->SetPointLightColor(1, XMFLOAT3(pointLightColor));
	lightgroup->SetPointLightAtten(1, XMFLOAT3(pointLightAtten));

	//丸影
	lightgroup->SetCircleShadowDir(0, XMVECTOR({ circleShadowDir[0], circleShadowDir[1], circleShadowDir[2], 0 }));
	lightgroup->SetCircleShadowCasterPos(0, XMFLOAT3({ player->GetPosition().x, player->GetPosition().y, player->GetPosition().z }));
	lightgroup->SetCircleShadowAtten(0, XMFLOAT3(circleShadowAtten));
	lightgroup->SetCircleShadowFactorAngle(0, XMFLOAT2(circleShadowFactorAngle));

	enemymanager->LightSet(StageNumber, lightgroup);
	backmanager->LightSet(StageNumber, lightgroup);
}
//シーン変更など
void EditorSceneActor::ChangeUpdate() {

	//死んだときも戻される
	if (player->GetHP() < 1) {
		scenechange->SetAddStartChange(true);
	}

	//ImGuiでシーンを切り替えたかどうか
	if (scenechange->AddBlack(0.05f)) {
		//ゲームシーンへ変更
		if (m_SceneChange) {
			m_GameLoad = true;
			StartStage = StageNumber;
			block->ResetBlock();
			minimap->ResetBlock();
			SaveGame();
			//シーン先を決める
			if (m_SceneMigration == GamePlay) {
				SceneManager::GetInstance()->ChangeScene("FIRSTSTAGE");
			}
			else if (m_SceneMigration == Title) {
				m_GameLoop = true;
				Audio::GetInstance()->StopWave(0);
				SceneManager::GetInstance()->ChangeScene("TITLE");
			}
			m_SceneChange = false;
		}
	}
	//マップ切り替え
	if (mapchange->AddBlack()) {
		block->ResetBlock();
		minimap->ResetBlock();
		mapchange->SetSubStartChange(true);
		StageChange = true;
	}

	//背景が暗くなるかどうか
	if (!player->GetAlive() && BlackColor.w < 1.0f) {
		BlackColor.w += 0.02f;
	}
	else if (player->GetAlive() && BlackColor.w > 0.0f) {
		BlackColor.w -= 0.02f;
	}
}
//エディタ関係の更新
void EditorSceneActor::EditorUpdate() {

	imguieditor->Update(player->GetPosition());
	//エネミーの生成
	if (imguieditor->GetEnemyArgment()) {
		//普通
		if (imguieditor->GetEnemyType() == Normal) {
			enemymanager->EnemyBirth(Normal, player, block);
		}
		//棘のやつ
		else if (imguieditor->GetEnemyType() == Thorn) {
			enemymanager->EnemyBirth(Thorn, player, block);
		}
		//羽の敵
		else if (imguieditor->GetEnemyType() == Bound) {
			enemymanager->EnemyBirth(Bound, player, block);
		}
		//鳥の敵
		else if (imguieditor->GetEnemyType() == Bird) {
			enemymanager->EnemyBirth(Bird, player, block);
		}
		else if (imguieditor->GetEnemyType() == Follow) {
			enemymanager->EnemyBirth(Follow, player, block);
		}
		else {
			enemymanager->EnemyBirth(FakeChest, player, block);
		}
		imguieditor->SetEnemyArgment(false);
	}
	//棘のやつ(OBJ)
	if (imguieditor->GetThornObjArgment()) {
		enemymanager->ThornBirth(imguieditor->GetThornObjArgment(), player, imguieditor->GetThornDir());

		imguieditor->SetThornObjArgment(false);
	}
	//背景objの生成
	if (imguieditor->GetBackObjArgment()) {
		//柱
		if (imguieditor->GetBackObjType() == BackOBJRock) {
			backmanager->ObjBirth(BackOBJRock, player, imguieditor->GetPosition(), imguieditor->GetRotation());
		}
		//岩
		else if (imguieditor->GetBackObjType() == BackOBJBox) {
			backmanager->ObjBirth(BackOBJBox, player, imguieditor->GetPosition(), imguieditor->GetRotation());
		}
		//松明
		else {
			backmanager->ObjBirth(BackOBJTorch, player, imguieditor->GetPosition(), imguieditor->GetRotation());
		}
		imguieditor->SetBackObjArgment(false);
	}
	//エネミーの削除
	//普通
	if (imguieditor->GetEnemyDelete()) {
		if (imguieditor->GetEnemyType() == Normal) {
			enemymanager->DeleteEnemyPop(imguieditor->GetEnemyType());
		}
		//とげ
		else if (imguieditor->GetEnemyType() == Thorn) {
			enemymanager->DeleteEnemyPop(imguieditor->GetEnemyType());
		}
		//羽
		else if (imguieditor->GetEnemyType() == Bound) {
			enemymanager->DeleteEnemyPop(imguieditor->GetEnemyType());
		}
		//鳥
		else if (imguieditor->GetEnemyType() == Bird) {
			enemymanager->DeleteEnemyPop(imguieditor->GetEnemyType());
		}
		//追従
		else if (imguieditor->GetEnemyType() == Follow) {
			enemymanager->DeleteEnemyPop(imguieditor->GetEnemyType());
		}
		//宝箱
		else if (imguieditor->GetEnemyType() == FakeChest) {
			enemymanager->DeleteEnemyPop(imguieditor->GetEnemyType());
		}
		imguieditor->SetEnemyDelete(false);
	}
	//とげ(OBJ)
	if (imguieditor->GetDeleteThornObj()) {
		enemymanager->DeleteThornPop();
		imguieditor->SetDeleteThornObj(false);
	}
	//objの削除
	if (imguieditor->GetBackObjDelete()) {
		//柱
		if (imguieditor->GetBackObjType() == BackOBJRock) {
			backmanager->DeleteObjPop(imguieditor->GetBackObjType());
		}
		//岩
		if (imguieditor->GetBackObjType() == BackOBJBox) {
			backmanager->DeleteObjPop(imguieditor->GetBackObjType());
		}
		//松明
		if (imguieditor->GetBackObjType() == BackOBJTorch) {
			backmanager->DeleteObjPop(imguieditor->GetBackObjType());
		}
		imguieditor->SetBackObjDelete(false);
	}
}