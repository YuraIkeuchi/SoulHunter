#include "BaseActor.h"
#include "VariableCommon.h"
#include "PlayerSkill.h"
#include "Block.h"
#include "MiniMap.h"
bool BaseActor::m_GameLoad = false;
bool BaseActor::m_NormalMode = false;
bool BaseActor::m_GameLoop = false;
bool BaseActor::s_New = false;

//共通初期化
void BaseActor::BaseInitialize(DirectXCommon* dxCommon) {
	//ポストエフェクトの初期化
	//(普通)
	postEffect = new PostEffect();
	postEffect->Initialize();
	postEffect->CreateGraphicsPipeline(L"Resources/Shaders/PostEffectTestVS.hlsl", L"Resources/Shaders/SepiaPS.hlsl");
}
//Newするを一回にしたい
void BaseActor::NewFinish() {
	s_New = true;
}
//プレイヤー関係の初期化
void BaseActor::PlayerInitialize() {
	//プレイヤー
	player->Initialize();
	player->StateInitialize();
}
//カメラの初期化
void BaseActor::CameraInitialize() {
	//カメラの動き
	camerawork->SetPlayer(player);
	camerawork->SetInterBoss(firstboss);
}
//エネミーの初期化
void BaseActor::EnemyInitialize() {
	//ボス
	firstboss->SetPlayer(player);
	firstboss->Initialize();

	//リスポーン関係(敵)
	respornenemy->Initialize();
}
//ポーズの初期化
void BaseActor::PauseInitialize() {
	//ポーズメニュー
	//スキルセット
	skillpause->SetPlayer(player);
	skillpause->Initialize();
	//ミニマップ
	MiniMap::GetInstance()->Initialize();
	MiniMap::GetInstance()->SetPlayer(player);
	MiniMap::GetInstance()->SetSave(save);
	//オプション
	option->Initialize();
	pause->SetSkillPause(skillpause);
	pause->SetOption(option);
	pause->SetPlayer(player);
	pause->Initialize();
}
//プレイヤーの手助けになるものの初期化
void BaseActor::HelperInitialize() {
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
void BaseActor::BackObjInitialize() {
	//宝箱
	chest->SetPlayer(player);
}
//ゲームの始まり
void BaseActor::StartGame(LightGroup* lightgroup) {
	//最初からにした場合
	if (!m_GameLoad) {
		skillpause->InitPos();
		StageNumber = TutoRial;
		Block::GetInstance()->Initialize(tutorialmap, 0, StageNumber);
		MiniMap::GetInstance()->InitMap(tutorialmap, StageNumber);
		skillpause->ResetSkillPause();
		enemymanager->LoadEnemyParam(TutoRial, player, lightgroup);
		backmanager->LoadObjParam(TutoRial, player, lightgroup);
		//ゲームモードによってスキル獲得状況が変わる
		if (m_NormalMode) {
			PlayerSkill::GetInstance()->ResetSkill();
		}
		else {
			PlayerSkill::GetInstance()->AllGetSkill();
		}
	}
	//ロードした場合
	else {
		LoadGame();
		StageNumber = StartStage;
		player->LoadPlayer(m_PlayerStartPos);
		tutorialtext->LoadGame();
		save->InitSave(StageNumber);
		chest->InitChest(StageNumber);
		if (StageNumber == TutoRial) {
			Block::GetInstance()->Initialize(tutorialmap, 0, StageNumber);
			MiniMap::GetInstance()->InitMap(tutorialmap, StageNumber);
		}
		else if (StageNumber == Map1) {
			Block::GetInstance()->Initialize(map1, 0, StageNumber);
			MiniMap::GetInstance()->InitMap(map1, StageNumber);
		}
		else if (StageNumber == Map3) {
			Block::GetInstance()->Initialize(map3, 0, StageNumber);
			MiniMap::GetInstance()->InitMap(map3, StageNumber);
		}
		else if (StageNumber == Map5) {
			Block::GetInstance()->Initialize(map5, 0, StageNumber);
			MiniMap::GetInstance()->InitMap(map5, StageNumber);
		}
	}
}
//ゲームデータのセーブ(位置とマップ番号)
void BaseActor::SaveGame() {
	std::ofstream playerofs("Resources/game_param/gamedata.csv");  // ファイルパスを指定する

	playerofs << "StageNumber" << "," << StartStage << std::endl;
	playerofs << "POP" << "," << player->GetPosition().x
		<< "," << player->GetPosition().y
		<< "," << player->GetPosition().z << std::endl;
	playerofs << "DushSkill" << "," << PlayerSkill::GetInstance()->GetDushSkill() << std::endl;
	playerofs << "LibraSkill" << "," << PlayerSkill::GetInstance()->GetLibraSkill() << std::endl;
	playerofs << "CompassSkill" << "," << PlayerSkill::GetInstance()->GetCompassSkill() << std::endl;
	playerofs << "HealSkill" << "," << PlayerSkill::GetInstance()->GetHealSkill() << std::endl;
	playerofs << "JumpSkill" << "," << PlayerSkill::GetInstance()->GetJumpSkill() << std::endl;
	playerofs << "HP" << "," << player->GetHP() << std::endl;
	playerofs << "Soul" << "," << player->GetSoulCount() << std::endl;
}
//ゲームデータのロード
void BaseActor::LoadGame() {
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
		else if (word.find("JumpSkill") == 0) {

			std::getline(line_stream, word, ',');
			bool l_startjumpskill = (int)std::atof(word.c_str());

			PlayerSkill::GetInstance()->SetJumpSkill(l_startjumpskill);
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