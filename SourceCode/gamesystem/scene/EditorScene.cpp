#include "EditorScene.h"
#include "Audio.h"
#include "SceneManager.h"
#include "imgui.h"
#include "VariableCommon.h"
#include "PlayerSkill.h"
#include "ParticleEmitter.h"
//初期化
void EditorScene::Initialize(DirectXCommon* dxCommon)
{
	//各クラスのnew
	player = new Player();
	skillpause = new SkillPause();
	option = new Option();
	pause = new Pause();
	mapchange = new MapChange();
	save = new Save();
	backlight = new BackLight();
	chest = new Chest();
	camerawork = new CameraWork();
	enemymanager = new EnemyManager();
	backmanager = new BackObjManager();
	camerawork->SetCameraType(2);
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
	//ライト
	spotLightDir[0] = 0;
	spotLightDir[1] = 0;
	spotLightDir[2] = 1;
	StartGame();
	enemymanager->SetPause(pause);
	enemymanager->SetChest(chest);
	enemymanager->LoadEnemyParam(StageNumber,player,block);
	backmanager->LoadObjParam(StageNumber,player);
	BGMStart = true;

	//エディタモードは最初は敵を止める
	m_MoveEnemy = false;

	//ポストエフェクトのファイル指定
	postEffect->CreateGraphicsPipeline(L"Resources/Shaders/PostEffectTestVS.hlsl", L"Resources/Shaders/NewToneMapPS.hlsl");

	ParticleEmitter::GetInstance()->AllDelete();

	PlayPostEffect = true;
}
//更新
void EditorScene::Update(DirectXCommon* dxCommon)
{
	//各クラス更新
	AllUpdate();
	//光の配置
	LightSet();
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
		enemymanager->LoadEnemyParam(StageNumber,player,block);
		m_EditorLoad = false;
	}

	//背景OBJの位置セーブ
	if (m_ObjSave) {
		backmanager->OpenObjParam(StageNumber);
		backmanager->SaveObjParam(StageNumber);
	/*	OpenObjParam(StageNumber);
		SaveObjParam(StageNumber);*/
		m_ObjSave = false;
	}

	//背景OBJの位置ロード
	if (m_ObjLoad) {
		backmanager->LoadObjParam(StageNumber, player);
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
}
//描画
void EditorScene::Draw(DirectXCommon* dxCommon)
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
		//FPSManager::GetInstance()->ImGuiDraw();
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
		//FPSManager::GetInstance()->ImGuiDraw();
		PostImGuiDraw(dxCommon);
		camerawork->ImGuiDraw();
		BackDraw(dxCommon);
		FrontDraw(dxCommon);
		dxCommon->PostDraw();
	}
}
//解放
void EditorScene::Finalize()
{
	delete postEffect;
}
//モデルの描画
void EditorScene::ModelDraw(DirectXCommon* dxCommon) {
#pragma region 3Dオブジェクト描画
	//背景は先に描画する
	
}
//後ろの描画
void EditorScene::BackDraw(DirectXCommon* dxCommon)
{
	IKEObject3d::PreDraw();
	backmanager->AlwaysDraw(dxCommon);
	block->Draw(m_PlayerPos);
	if (StageNumber != BossMap) {
		backmanager->Draw(dxCommon);
	}
	backlight->Draw();
	save->Draw();
	//敵の描画
	enemymanager->Draw(dxCommon);

	for (int i = 0; i < tutorialtext.size(); i++) {
		tutorialtext[i]->Draw();
	}
	ParticleEmitter::GetInstance()->SmokeDrawAll();
	ParticleEmitter::GetInstance()->FireDrawAll();
	//たからばこ
	chest->Draw();
	//プレイヤーの描画
	player->Draw(dxCommon);
	//パーティクル描画
	ParticleEmitter::GetInstance()->FlontDrawAll();
	//ImGuiのOBJの描画
	imguieditor->ObjDraw();
	// 3Dオブジェクト描画後処理
	IKEObject3d::PostDraw();
}
//ポストエフェクトがかからない
void EditorScene::FrontDraw(DirectXCommon* dxCommon) {
	IKEObject3d::PreDraw();
	IKESprite::PreDraw();
	ui->Draw();
	mapchange->Draw();
	pause->Draw();
	chest->ExplainDraw();
	scenechange->Draw();
	enemymanager->MapDraw(minimap->GetMapType(), minimap->GetMapColor());
	IKESprite::PostDraw();
#pragma endregion
}
//ポストエフェクトのImGui
void EditorScene::PostImGuiDraw(DirectXCommon* dxCommon) {
}
//IMGuiの描画
void EditorScene::ImGuiDraw(DirectXCommon* dxCommon) {
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
	if (ImGui::RadioButton("NoMove", &m_MoveEnemy)) {
		m_MoveEnemy = false;
	}
	ImGui::Text("m_MoveEnemy:%d", m_MoveEnemy);
	ImGui::End();
	//ポストエフェクト
	{
		ImGui::Begin("postEffect");
		ImGui::SetWindowPos(ImVec2(1000, 450));
		ImGui::SetWindowSize(ImVec2(280, 300));
		if (ImGui::RadioButton("PostEffect", &PlayPostEffect)) {
			PlayPostEffect = true;
		}
		if (ImGui::RadioButton("Default", &PlayPostEffect)) {
			PlayPostEffect = false;
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
			StageMapChange(StageNumber);
		}
		if (ImGui::Button("Map2", ImVec2(90, 50))) {
			StageNumber = Map2;
			StageMapChange(StageNumber);
		}
		if (ImGui::Button("Map3", ImVec2(90, 50))) {
			StageNumber = Map3;
			StageMapChange(StageNumber);
		}
		if (ImGui::Button("Map4", ImVec2(90, 50))) {
			StageNumber = Map4;
			StageMapChange(StageNumber);
		}
		if (ImGui::Button("Map5", ImVec2(90, 50))) {
			StageNumber = Map5;
			StageMapChange(StageNumber);
		}
		if (ImGui::Button("Map6", ImVec2(90, 50))) {
			StageNumber = Map6;
			StageMapChange(StageNumber);
		}
		if (ImGui::Button("TutorialMap", ImVec2(90, 50))) {
			StageNumber = TutoRial;
			StageMapChange(StageNumber);
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
void EditorScene::MapInitialize() {
	if (StageChange) {
		enemymanager->DeleteEnemy();
		backmanager->ObjDelete();
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
		save->InitSave(StageNumber);
		for (int i = 0; i < tutorialtext.size(); i++) {
			tutorialtext[i]->InitBoard(StageNumber, i);
		}
		enemymanager->LoadEnemyParam(StageNumber,player,block);
		backmanager->LoadObjParam(StageNumber, player);
		backmanager->LoadBackObjAlways(StageNumber);
		chest->InitChest(StageNumber);
		StageChange = false;
		player->SetGoalDir(0);
	}
}
//マップ切り替えの関数
void EditorScene::StageMapChange(int StageNumber) {
	m_MoveEnemy = false;
	mapchange->SetAddStartChange(true);
	save->InitSave(StageNumber);
	for (int i = 0; i < tutorialtext.size(); i++) {
		tutorialtext[i]->InitBoard(StageNumber, i);
	}
}

//ゲームデータのセーブ(位置とマップ番号)
void EditorScene::SaveGame() {
	std::ofstream playerofs("Resources/game_param/gamedata.csv");  // ファイルパスを指定する
	//normalofs << "Enemy_Quantity" << "," << m_Enemys.size() << std::endl;

	playerofs << "Wait" << "," << 120 << std::endl;
	playerofs << "StageNumber" << "," << StartStage << std::endl;
	playerofs << "POP" << "," << player->GetPosition().x
		<< "," << player->GetPosition().y
		<< "," << player->GetPosition().z << std::endl;
	playerofs << "DushSkill" << "," << PlayerSkill::GetInstance()->GetDushSkill() << std::endl;
	playerofs << "LibraSkill" << "," << PlayerSkill::GetInstance()->GetLibraSkill() << std::endl;
	playerofs << "CompassSkill" << "," << PlayerSkill::GetInstance()->GetCompassSkill() << std::endl;
	playerofs << "HP" << "," << player->GetHP() << std::endl;
	playerofs << "Soul" << "," << player->GetSoulCount() << std::endl;
}
//ゲームデータのロード
void EditorScene::LoadGame() {
	m_GameFile.open("Resources/game_param/gamedata.csv");
	m_GamePopcom << m_GameFile.rdbuf();
	m_GameFile.close();

	while (std::getline(m_GamePopcom, m_GameLine)) {
		std::istringstream line_stream(m_GameLine);
		std::string word;
		std::getline(line_stream, word, ',');

		if (word.find("//") == 0) {
			continue;
		}
		if (word.find("StageNumber") == 0) {

			std::getline(line_stream, word, ',');
			int number = (int)std::atof(word.c_str());

			StartStage = number;
		}
		else if (word.find("POP") == 0) {
			std::getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			std::getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			std::getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			m_PlayerStartPos = { x,y,z };

		}
		else if (word.find("DushSkill") == 0) {

			std::getline(line_stream, word, ',');
			bool l_startdushskill = (int)std::atof(word.c_str());

			PlayerSkill::GetInstance()->SetDushSkill(l_startdushskill);
		}
		else if (word.find("LibraSkill") == 0) {

			std::getline(line_stream, word, ',');
			bool l_startlibraskill = (int)std::atof(word.c_str());

			PlayerSkill::GetInstance()->SetLibraSkill(l_startlibraskill);
		}
		else if (word.find("CompassSkill") == 0) {

			std::getline(line_stream, word, ',');
			bool l_startcompassskill = (int)std::atof(word.c_str());

			PlayerSkill::GetInstance()->SetCompassSkill(l_startcompassskill);
		}
		else if (word.find("HP") == 0) {

			std::getline(line_stream, word, ',');
			int l_startHP = (int)std::atof(word.c_str());

			player->SetHP(l_startHP);
		}
		else if (word.find("Soul") == 0) {

			std::getline(line_stream, word, ',');
			float l_startSoulCount = (float)std::atof(word.c_str());

			player->SetSoulCount(l_startSoulCount);
			break;
		}
	}

}
//各クラスの更新
void EditorScene::AllUpdate() {
	lightGroup->Update();
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
	
	for (int i = 0; i < tutorialtext.size(); i++) {
		tutorialtext[i]->Update(i);
	}

	//その他の更新
	ParticleEmitter::GetInstance()->Update();
	backlight->Update();
	minimap->SetMiniPlayerPos(StageNumber);
	pause->Update();
	chest->Update();
	VolumManager::GetInstance()->Update();
	save->Update();
	ui->Update();
	camerawork->Update(camera);
}
//ライトの位置
void EditorScene::LightSet() {
	m_PlayerPos = camera->GetEye();
	///ポイントライト
	lightGroup->SetPointLightPos(0, XMFLOAT3(player->GetPosition().x, player->GetPosition().y, player->GetPosition().z - 5.0f));
	lightGroup->SetPointLightColor(0, XMFLOAT3(pointLightColor));
	lightGroup->SetPointLightAtten(0, XMFLOAT3({10.0f,10.0f,10.0f}));

	lightGroup->SetPointLightPos(1, XMFLOAT3(save->GetPosition().x, save->GetPosition().y + 2.0f, save->GetPosition().z + 2.0f));
	lightGroup->SetPointLightColor(1, XMFLOAT3(pointLightColor));
	lightGroup->SetPointLightAtten(1, XMFLOAT3(pointLightAtten));

	//for (BackObjCommon* torch : m_BackTorchs) {
	//	for (int i = 0; i < m_BackTorch_Num; i++) {
	//		if (torch != nullptr) {
	//			lightGroup->SetPointLightPos(i + 2, XMFLOAT3({ m_BackTorchs[i]->GetPosition().x, m_BackTorchs[i]->GetPosition().y + 3.0f, m_BackTorchs[i]->GetPosition().z + 3.0f }));
	//			lightGroup->SetPointLightColor(i + 2, XMFLOAT3(pointLightColor));
	//			lightGroup->SetPointLightAtten(i + 2, XMFLOAT3(pointLightAtten));
	//		}
	//	}
	//}

	//丸影
	lightGroup->SetCircleShadowDir(0, XMVECTOR({ circleShadowDir[0], circleShadowDir[1], circleShadowDir[2], 0 }));
	lightGroup->SetCircleShadowCasterPos(0, XMFLOAT3({ player->GetPosition().x, player->GetPosition().y, player->GetPosition().z }));
	lightGroup->SetCircleShadowAtten(0, XMFLOAT3(circleShadowAtten));
	lightGroup->SetCircleShadowFactorAngle(0, XMFLOAT2(circleShadowFactorAngle));

	//for (InterEnemy* enemy : m_Enemys) {
	//	for (int i = 0; i < m_Enemy_Num; i++) {
	//		if (enemy != nullptr) {
	//			lightGroup->SetCircleShadowDir(i + 2, XMVECTOR({ circleShadowDir[0], circleShadowDir[1], circleShadowDir[2], 0 }));
	//			lightGroup->SetCircleShadowCasterPos(i + 2, XMFLOAT3({ m_Enemys[i]->GetPosition().x, m_Enemys[i]->GetPosition().y, m_Enemys[i]->GetPosition().z }));
	//			lightGroup->SetCircleShadowAtten(i + 2, XMFLOAT3(circleShadowAtten));
	//			lightGroup->SetCircleShadowFactorAngle(i + 2, XMFLOAT2(circleShadowFactorAngle));
	//		}
	//	}
	//}

	//for (InterEnemy* enemy : m_ThornEnemys) {
	//	for (int i = 0; i < m_ThornEnemy_Num; i++) {
	//		if (enemy != nullptr) {
	//			lightGroup->SetCircleShadowDir(i + m_Enemy_Num, XMVECTOR({ circleShadowDir[0], circleShadowDir[1], circleShadowDir[2], 0 }));
	//			lightGroup->SetCircleShadowCasterPos(i + m_Enemy_Num, XMFLOAT3({ m_ThornEnemys[i]->GetPosition().x,  m_ThornEnemys[i]->GetPosition().y,  m_ThornEnemys[i]->GetPosition().z }));
	//			lightGroup->SetCircleShadowAtten(i + m_Enemy_Num, XMFLOAT3(circleShadowAtten));
	//			lightGroup->SetCircleShadowFactorAngle(i + m_Enemy_Num, XMFLOAT2(circleShadowFactorAngle));
	//		}
	//	}
	//}

	//for (InterEnemy* enemy : m_BoundEnemys) {
	//	for (int i = 0; i < m_BoundEnemy_Num; i++) {
	//		if (enemy != nullptr) {
	//			lightGroup->SetCircleShadowDir(i + (m_Enemy_Num + m_ThornEnemy_Num), XMVECTOR({ circleShadowDir[0], circleShadowDir[1], circleShadowDir[2], 0 }));
	//			lightGroup->SetCircleShadowCasterPos(i + (m_Enemy_Num + m_ThornEnemy_Num), XMFLOAT3({ m_BoundEnemys[i]->GetPosition().x,  m_BoundEnemys[i]->GetPosition().y,  m_BoundEnemys[i]->GetPosition().z }));
	//			lightGroup->SetCircleShadowAtten(i + (m_Enemy_Num + m_ThornEnemy_Num), XMFLOAT3(circleShadowAtten));
	//			lightGroup->SetCircleShadowFactorAngle(i + (m_Enemy_Num + m_ThornEnemy_Num), XMFLOAT2(circleShadowFactorAngle));
	//		}
	//	}
	//}

	//for (InterEnemy* enemy : m_BirdEnemys) {
	//	for (int i = 0; i < m_BirdEnemy_Num; i++) {
	//		if (enemy != nullptr) {
	//			lightGroup->SetCircleShadowDir(i + (m_Enemy_Num + m_ThornEnemy_Num + m_BoundEnemy_Num), XMVECTOR({ circleShadowDir[0], circleShadowDir[1], circleShadowDir[2], 0 }));
	//			lightGroup->SetCircleShadowCasterPos(i + (m_Enemy_Num + m_ThornEnemy_Num + m_BoundEnemy_Num), XMFLOAT3({ m_BirdEnemys[i]->GetPosition().x, m_BirdEnemys[i]->GetPosition().y,  m_BirdEnemys[i]->GetPosition().z }));
	//			lightGroup->SetCircleShadowAtten(i + (m_Enemy_Num + m_ThornEnemy_Num + m_BoundEnemy_Num), XMFLOAT3(circleShadowAtten));
	//			lightGroup->SetCircleShadowFactorAngle(i + (m_Enemy_Num + m_ThornEnemy_Num + m_BoundEnemy_Num), XMFLOAT2(circleShadowFactorAngle));
	//		}
	//	}
	//}
}
//シーン変更など
void EditorScene::ChangeUpdate() {

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
void EditorScene::EditorUpdate() {

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
		else {
			enemymanager->EnemyBirth(Bird, player, block);
		}
		imguieditor->SetEnemyArgment(false);
	}
	//棘のやつ(OBJ)
	if (imguieditor->GetThornObjArgment()) {
		enemymanager->ThornBirth(imguieditor->GetThornObjArgment(),player,imguieditor->GetThornDir());
	
		imguieditor->SetThornObjArgment(false);
	}
	//背景objの生成
	if (imguieditor->GetBackObjArgment()) {
		//柱
		if (imguieditor->GetBackObjType() == Rock) {
			backmanager->ObjBirth(Rock, player, imguieditor->GetPosition(), imguieditor->GetRotation());
		}
		//岩
		else if (imguieditor->GetBackObjType() == Box) {
			backmanager->ObjBirth(Box, player, imguieditor->GetPosition(), imguieditor->GetRotation());
		}
		//松明
		else {
			backmanager->ObjBirth(Torch, player, imguieditor->GetPosition(), imguieditor->GetRotation());
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
		if (imguieditor->GetBackObjType() == Rock) {
			backmanager->DeleteObjPop(imguieditor->GetBackObjType());
		}
		//岩
		if (imguieditor->GetBackObjType() == Box) {
			backmanager->DeleteObjPop(imguieditor->GetBackObjType());
		}
		//松明
		if (imguieditor->GetBackObjType() == Torch) {
			backmanager->DeleteObjPop(imguieditor->GetBackObjType());
		}
		imguieditor->SetBackObjDelete(false);
	}
}