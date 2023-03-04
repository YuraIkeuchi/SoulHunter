#include "BaseActor.h"
#include "VariableCommon.h"
#include "PlayerSkill.h"
#include "Block.h"
#include "MiniMap.h"
bool BaseActor::m_GameLoad = false;
bool BaseActor::m_NormalMode = false;
bool BaseActor::m_GameLoop = false;
bool BaseActor::s_New = false;

//���ʏ�����
void BaseActor::BaseInitialize(DirectXCommon* dxCommon) {
	//�|�X�g�G�t�F�N�g�̏�����
	//(����)
	postEffect = new PostEffect();
	postEffect->Initialize();
	postEffect->CreateGraphicsPipeline(L"Resources/Shaders/PostEffectTestVS.hlsl", L"Resources/Shaders/SepiaPS.hlsl");
}
//New��������ɂ�����
void BaseActor::NewFinish() {
	s_New = true;
}
//�v���C���[�֌W�̏�����
void BaseActor::PlayerInitialize() {
	//�v���C���[
	player->Initialize();
	player->StateInitialize();
}
//�J�����̏�����
void BaseActor::CameraInitialize() {
	//�J�����̓���
	camerawork->SetPlayer(player);
	camerawork->SetInterBoss(firstboss);
}
//�G�l�~�[�̏�����
void BaseActor::EnemyInitialize() {
	//�{�X
	firstboss->SetPlayer(player);
	firstboss->Initialize();

	//���X�|�[���֌W(�G)
	respornenemy->Initialize();
}
//�|�[�Y�̏�����
void BaseActor::PauseInitialize() {
	//�|�[�Y���j���[
	//�X�L���Z�b�g
	skillpause->SetPlayer(player);
	skillpause->Initialize();
	//�~�j�}�b�v
	MiniMap::GetInstance()->Initialize();
	MiniMap::GetInstance()->SetPlayer(player);
	MiniMap::GetInstance()->SetSave(save);
	//�I�v�V����
	option->Initialize();
	pause->SetSkillPause(skillpause);
	pause->SetOption(option);
	pause->SetPlayer(player);
	pause->Initialize();
}
//�v���C���[�̎菕���ɂȂ���̂̏�����
void BaseActor::HelperInitialize() {
	//UI
	ui = new UI(player, firstboss);
	//�`���[�g���A��
	tutorialtext = new TutorialText();
	tutorialtext->SetPlayer(player);
	//�Z�[�u�֌W
	save->Initialize();
	save->SetPlayer(player);
}
//�w�iOBJ�̏�����
void BaseActor::BackObjInitialize() {
	//��
	chest->SetPlayer(player);
}
//�Q�[���̎n�܂�
void BaseActor::StartGame(LightGroup* lightgroup) {
	//�ŏ�����ɂ����ꍇ
	if (!m_GameLoad) {
		skillpause->InitPos();
		StageNumber = TutoRial;
		Block::GetInstance()->Initialize(tutorialmap, 0, StageNumber);
		MiniMap::GetInstance()->InitMap(tutorialmap, StageNumber);
		skillpause->ResetSkillPause();
		enemymanager->LoadEnemyParam(TutoRial, player, lightgroup);
		backmanager->LoadObjParam(TutoRial, player, lightgroup);
		//�Q�[�����[�h�ɂ���ăX�L���l���󋵂��ς��
		if (m_NormalMode) {
			PlayerSkill::GetInstance()->ResetSkill();
		}
		else {
			PlayerSkill::GetInstance()->AllGetSkill();
		}
	}
	//���[�h�����ꍇ
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
//�Q�[���f�[�^�̃Z�[�u(�ʒu�ƃ}�b�v�ԍ�)
void BaseActor::SaveGame() {
	std::ofstream playerofs("Resources/game_param/gamedata.csv");  // �t�@�C���p�X���w�肷��

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
//�Q�[���f�[�^�̃��[�h
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