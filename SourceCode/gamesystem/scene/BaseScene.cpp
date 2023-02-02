#include "BaseScene.h"
#include "ImageManager.h"
#include "PlayerSkill.h"
#include "VariableCommon.h"
#include "ParticleEmitter.h"
Block* BaseScene::block = nullptr;
MiniMap* BaseScene::minimap = nullptr;
//Pause* BaseScene::pause = nullptr;
bool BaseScene::m_GameLoad = false;
bool BaseScene::m_GameLoop = false;
bool BaseScene::s_New = false;
//Newするを一回にしたい
void BaseScene::NewFinish() {
	s_New = true;
}
//共通の初期化
void BaseScene::BaseInitialize(DirectXCommon* dxCommon) {
	// デバイスをセット
	IKEFBXObject3d::SetDevice(dxCommon->GetDev());
	// グラフィックスパイプライン生成
	IKEFBXObject3d::CreateGraphicsPipeline();
	// カメラ生成
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height);
	IKETexture::SetCamera(camera);
	// 3Dオブジェクトにカメラをセット
	IKEObject3d::SetCamera(camera);
	//particleMan->SetCamera(camera);
	IKEFBXObject3d::SetCamera(camera);
	//ポストエフェクトの初期化
	//(普通)
	postEffect = new PostEffect();
	postEffect->Initialize();
	postEffect->CreateGraphicsPipeline(L"Resources/Shaders/PostEffectTestVS.hlsl", L"Resources/Shaders/SepiaPS.hlsl");

	// ライト生成
	lightGroup = LightGroup::Create();
	// 3Dオブエクトにライトをセット
	IKEObject3d::SetLightGroup(lightGroup);
	ParticleManager::SetCamera(camera);
	ParticleEmitter::GetInstance()->AllDelete();
	//丸影のためのやつ
	lightGroup->SetDirLightActive(0, false);
	lightGroup->SetDirLightActive(1, false);
	lightGroup->SetDirLightActive(2, false);
	lightGroup->SetPointLightActive(0, true);
	lightGroup->SetPointLightActive(1, true);
	lightGroup->SetCircleShadowActive(0, true);
}
//プレイヤー関係の初期化
void BaseScene::PlayerInitialize() {
	//プレイヤー
	player->Initialize();
	player->StateInitialize();
	player->SetBlock(block);
}
//カメラの初期化
void BaseScene::CameraInitialize() {
	//カメラの動き
	camerawork->SetPlayer(player);
	camerawork->SetInterBoss(firstboss);
}
//エネミーの初期化
void BaseScene::EnemyInitialize() {
	//ボス
	firstboss->SetPlayer(player);
	firstboss->Initialize();

	//リスポーン関係(敵)
	respornenemy->Initialize();

}
//ポーズの初期化
void BaseScene::PauseInitialize() {
	//ポーズメニュー
	//スキルセット
	skillpause->SetPlayer(player);
	skillpause->Initialize();
	//ミニマップ
	minimap->Initialize();
	minimap->SetPlayer(player);
	minimap->SetSave(save);
	//オプション
	option->Initialize();
	pause->SetSkillPause(skillpause);
	pause->SetMiniMap(minimap);
	pause->SetOption(option);
	pause->SetPlayer(player);
	pause->Initialize();
}
//プレイヤーの手助けになるものの初期化
void BaseScene::HelperInitialize() {
	//UI
	ui = new UI(player, firstboss);
	//チュートリアル
	tutorialtext = new TutorialText();
	tutorialtext->SetPlayer(player);
	//セーブ関係
	save->Initialize();
	save->SetPlayer(player);
}
//背景OBJの初期化
void BaseScene::BackObjInitialize() {
	//宝箱
	chest->SetPlayer(player);
}
//ゲームの始まり
void BaseScene::StartGame() {
	//最初からにした場合
	if (!m_GameLoad) {
		skillpause->InitPos();
		StageNumber = TutoRial;
		block->Initialize(tutorialmap, 0, StageNumber);
		minimap->InitMap(tutorialmap, StageNumber);
		PlayerSkill::GetInstance()->ResetSkill();
		skillpause->ResetSkillPause();
		enemymanager->LoadEnemyParam(TutoRial,player,block, lightGroup);
		backmanager->LoadObjParam(TutoRial,player, lightGroup);
	}
	//ロードした場合
	else {
		LoadGame();
		StageNumber = StartStage;
		player->LoadPlayer(m_PlayerStartPos);
		save->InitSave(StageNumber);
		chest->InitChest(StageNumber);
		if (StageNumber == TutoRial) {
			block->Initialize(tutorialmap, 0, StageNumber);
			minimap->InitMap(tutorialmap, StageNumber);
		}
		else if (StageNumber == Map1) {
			block->Initialize(map1, 0, StageNumber);
			minimap->InitMap(map1, StageNumber);
		}
		else if (StageNumber == Map3) {
			block->Initialize(map3, 0, StageNumber);
			minimap->InitMap(map3, StageNumber);
		}
		else if (StageNumber == Map5) {
			block->Initialize(map5, 0, StageNumber);
			minimap->InitMap(map5, StageNumber);
		}
	}
}
//ゲームデータのセーブ(位置とマップ番号)
void BaseScene::SaveGame() {
	std::ofstream playerofs("Resources/game_param/gamedata.csv");  // ファイルパスを指定する

	playerofs << "StageNumber" << "," << StartStage << std::endl;
	playerofs << "POP" << "," << player->GetPosition().x
		<< "," << player->GetPosition().y
		<< "," << player->GetPosition().z << std::endl;
	playerofs << "DushSkill" << "," << PlayerSkill::GetInstance()->GetDushSkill() << std::endl;
	playerofs << "LibraSkill" << "," << PlayerSkill::GetInstance()->GetLibraSkill() << std::endl;
	playerofs << "CompassSkill" << "," << PlayerSkill::GetInstance()->GetCompassSkill() << std::endl;
	playerofs << "HealSkill" << "," << PlayerSkill::GetInstance()->GetHealSkill() << std::endl;
	playerofs << "HP" << "," << player->GetHP() << std::endl;
	playerofs << "Soul" << "," << player->GetSoulCount() << std::endl;
}
//ゲームデータのロード
void BaseScene::LoadGame() {
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
		else if (word.find("HealSkill") == 0) {

			std::getline(line_stream, word, ',');
			bool l_starthealskill = (int)std::atof(word.c_str());

			PlayerSkill::GetInstance()->SetHealSkill(l_starthealskill);
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