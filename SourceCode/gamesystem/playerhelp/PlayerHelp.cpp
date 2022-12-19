//#include "PlayerHelp.h"
//#include "imgui.h"
//PlayerHelp::PlayerHelp() {
//	skillpause = new SkillPause();
//	minimap = new MiniMap();
//	option = new Option();
//	pause = new Pause();
//	save = new Save();
//}
//
//void PlayerHelp::Initialize() {
//	//UI
//	ui = new UI(player.get(), firstboss.get());
//	ui->SetPlayerSkill(playerskill.get());
//	//チュートリアル
//	for (int i = 0; i < tutorialtext.size(); i++) {
//		tutorialtext[i] = new TutorialText();
//		tutorialtext[i]->SetPlayer(player.get());
//	}
//	//セーブ関係
//	save->Initialize();
//	save->SetPlayer(player.get());
//
//	//ポーズメニュー
//	//スキルセット
//	skillpause->SetPlayer(player.get());
//	skillpause->SetPlayerSkill(playerskill.get());
//	skillpause->Initialize();
//	//skillpause->InitPos();
//	//ミニマップ
//	minimap->Initialize();
//	minimap->SetPlayer(player.get());
//	minimap->SetSave(save);
//	//オプション
//	option->Initialize();
//	pause->SetSkillPause(skillpause);
//	pause->SetMiniMap(minimap);
//	pause->SetOption(option);
//	pause->SetPlayer(player.get());
//	pause->Initialize();
//}
//
//void PlayerHelp::Update() {
//	Input* input = Input::GetInstance();
//
//	if (input->TriggerButton(input->Select)) {
//		pause->SetChangePause(true);
//	}
//	m_GameSave = save->GetGameSave();
//	//m_IsPause = pause->GetIsPause();
//	//pause->SetIsPause(m_IsPause);
//
//
//	pause->Update();
//	for (int i = 0; i < tutorialtext.size(); i++) {
//		tutorialtext[i]->Update(i);
//	}
//	minimap->UseCompass(playerskill.get());
//	save->Update();
//	//minimap->SetMiniPlayerPos(StageNumber);
//}
//
//void PlayerHelp::BossAliveUpdate(InterBoss* boss) {
//	ui->Update(boss);
//}
//
//void PlayerHelp::NotAliveUpdate() {
//	ui->Update();
//}
//
//void PlayerHelp::ObjDraw() {
//	ImGui::Begin("Game");
//	ImGui::Text("m_IsPause::%d", m_IsPause);
//	ImGui::End();
//	save->Draw();
//	//チュートリアル
//	for (int i = 0; i < tutorialtext.size(); i++) {
//		tutorialtext[i]->Draw();
//	}
//	
//}
//
//void PlayerHelp::SpriteDraw() {
//	ui->Draw();
//	pause->Draw();
//}
//
//void PlayerHelp::InitPos(std::vector<std::vector<int>>& map, const int& StageNumber) {
//	skillpause->InitPos();
//	minimap->InitMap(map, StageNumber);
//	skillpause->ResetSkillPause();
//}
//
//void PlayerHelp::LoadInit(std::vector<std::vector<int>>& map, const int& StageNumber) {
//	playerskill->InitSave(StageNumber);
//	minimap->InitMap(map, StageNumber);
//}
//
//void PlayerHelp::InitMap(std::vector<std::vector<int>>& map, const int& StageNumber) {
//	minimap->InitMap(map, StageNumber);
//}
//
//void PlayerHelp::HelpObjInit(const int& StageNumber) {
//	save->InitSave(StageNumber);
//	for (int i = 0; i < tutorialtext.size(); i++) {
//		tutorialtext[i]->InitBoard(StageNumber, i);
//	}
//}
//
//void PlayerHelp::ResetMiniMap() {
//	minimap->ResetBlock();
//}
//
//void PlayerHelp::ResetSkill() {
//	skillpause->ResetSkillPause();
//}
//
//void PlayerHelp::EndSave() {
//	save->SetGameSave(m_GameSave);
//}