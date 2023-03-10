#include "MiniMap.h"
#include "imgui.h"
#include <Easing.h>
#include "Input.h"
#include "Audio.h"
#include "VolumManager.h"
#include "VariableCommon.h"
#include "PlayerSkill.h"

MiniMap* MiniMap::GetInstance()
{
	static MiniMap instance;

	return &instance;
}
//初期化
void MiniMap::SpriteInit() {
	IKESprite::LoadTexture(12, L"Resources/2d/sceneback/PauseBack.png");
	IKESprite::LoadTexture(13, L"Resources/2d/sceneback/MiniMapPlayer.png");
	IKESprite::LoadTexture(14, L"Resources/2d/sceneback/MiniMapSave.png");
	IKESprite::LoadTexture(15, L"Resources/2d/Skill/Dush.png");
	IKESprite::LoadTexture(16, L"Resources/2d/sceneback/WholeMap.png");
	IKESprite::LoadTexture(17, L"Resources/2d/sceneback/MapState.png");
	IKESprite::LoadTexture(18, L"Resources/2d/sceneback/MiniBlock.png");
	IKESprite::LoadTexture(19, L"Resources/2d/sceneback/MiniBlockToge.png");
	IKESprite* MiniMapSprite_;
	MiniMapSprite_ = IKESprite::Create(12,{ 0.0f,0.0f });
	MiniMapSprite.reset(MiniMapSprite_);

	IKESprite* MiniPlayerSprite_;
	MiniPlayerSprite_ = IKESprite::Create(13, { 0.0f,0.0f });
	MiniPlayerSprite_->SetAnchorPoint({ 0.5f,0.5f });
	MiniPlayerSprite.reset(MiniPlayerSprite_);

	IKESprite* MiniSaveSprite_;
	MiniSaveSprite_ = IKESprite::Create(14, { 0.0f,0.0f });
	MiniSaveSprite_->SetAnchorPoint({ 0.5f,0.5f });
	MiniSaveSprite_->SetScale(0.7f);
	MiniSaveSprite.reset(MiniSaveSprite_);

	IKESprite* MiniDushSprite_;
	MiniDushSprite_ = IKESprite::Create(15, { 0.0f,0.0f });
	MiniDushSprite_->SetAnchorPoint({ 0.5f,0.5f });
	MiniDushSprite_->SetScale(0.3f);
	MiniDushSprite.reset(MiniDushSprite_);

	IKESprite* WholeMapSprite_;
	WholeMapSprite_ = IKESprite::Create(16, { 0.0f,0.0f });
	WholeMapSprite.reset(WholeMapSprite_);

	IKESprite* MapStateSprite_;
	MapStateSprite_ = IKESprite::Create(17, { 0.0f,0.0f });
	m_StatePos = { 1280.0f,640.0f };
	MapStateSprite.reset(MapStateSprite_);

	IKESprite* MiniBlockSprite_[map_max_y][map_max_x];
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			MiniBlockSprite_[y][x] = IKESprite::Create(18, { 0.0f,0.0f });
			MiniBlockSprite_[y][x]->SetPosition({ 2000.0f,0.0f });
			MiniBlockSprite_[y][x]->SetAnchorPoint({ 0.5f,0.5f });
			MiniBlockSprite_[y][x]->SetSize({ 22.0f,11.5f });
			MiniBlockSprite[y][x].reset(MiniBlockSprite_[y][x]);
		}
	}

	IKESprite* MiniBlockTogeSprite_[map_max_y][map_max_x];
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			MiniBlockTogeSprite_[y][x] = IKESprite::Create(19, { 0.0f,0.0f });
			MiniBlockTogeSprite_[y][x]->SetPosition({ 2000.0f,0.0f });
			MiniBlockTogeSprite_[y][x]->SetAnchorPoint({ 0.5f,0.5f });
			MiniBlockTogeSprite_[y][x]->SetSize({ 20.0f,20.0f });
			MiniBlockTogeSprite[y][x].reset(MiniBlockTogeSprite_[y][x]);
		}
	}
}
void MiniMap::Initialize() {
	helper = make_unique<Helper> ();
}
//更新
void MiniMap::Update()
{
	Input* input = Input::GetInstance();
	//元のポーズ画面に戻る
	if (input->TriggerButton(input->Start) && m_ColorChangeType == No) {
		Audio::GetInstance()->PlayWave("Resources/Sound/SE/Menu.wav", VolumManager::GetInstance()->GetSEVolum());
		m_ColorChangeType = Sub;
	}
	//マップタイプの変更
	SelectMapType();
	//マップタイプによっての更新
	if (m_MapType == Whole) {
		WholeUpdate();
	}
	else if (m_MapType == SelectMap) {
		SelectUpdate();
	}
	//色の変更
	ColorChange();
	//テキストの動き
	MoveStateTex();
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			MiniBlockSprite[y][x]->SetColor(m_MapColor);
			MiniBlockTogeSprite[y][x]->SetColor(m_MapColor);
		}
	}
	MiniMapSprite->SetColor(m_MapColor);
	MiniPlayerSprite->SetColor(m_PlayerColor);
	MiniPlayerSprite->SetPosition(m_PlayerPos);
	MiniSaveSprite->SetPosition(m_SavePos);
	MiniSaveSprite->SetColor(m_SaveColor);
	WholeMapSprite->SetColor(m_MapColor);
	MapStateSprite->SetColor(m_MapColor);
	MapStateSprite->SetPosition(m_StatePos);
}
//描画
const void MiniMap::Draw() {
	IKESprite::PreDraw();
	if (m_MapType == Whole) {
		WholeMapSprite->Draw();
	}
	else {
		for (int y = 0; y < map_max_y; y++)
		{
			for (int x = 0; x < map_max_x; x++)
			{
				if (MiniBlockSprite[y][x]->GetPosition().x != 2000.0f) {
					MiniBlockSprite[y][x]->Draw();
				}
				if (MiniBlockTogeSprite[y][x]->GetPosition().x != 2000.0f) {
					MiniBlockTogeSprite[y][x]->Draw();
				}
			}
		}
		if (PlayerSkill::GetInstance()->GetCompassSkill()) {
			if (save->GetAlive()) {
				MiniSaveSprite->Draw();
			}
		}
	}
	MiniPlayerSprite->Draw();
	MapStateSprite->Draw();
}
//Imgui
void MiniMap::ImguiDraw() {
	ImGui::Begin("Map");
	ImGui::Text("color.w:%f", m_MapColor.w);
	ImGui::Text("m_ColorChangeType:%d", m_ColorChangeType);
	ImGui::End();
}
//開放
void MiniMap::Finalize() {

}
//CSV読み込み
void MiniMap::InitMap(std::vector<std::vector<int>>& map, int StageNumber) {
	stagemap = map;
	//ステージによってマップの読み込みが変わる
	if (StageNumber == Map1) {
		m_StageNumber = Map1;
		MapChip::LoadCsvMap(stagemap, "Resources/csv/firststage.csv");
	}
	else if (StageNumber == Map2) {
		m_StageNumber = Map2;
		MapChip::LoadCsvMap(stagemap, "Resources/csv/firststage_second.csv");
	}
	else if (StageNumber == Map3) {
		m_StageNumber = Map3;
		MapChip::LoadCsvMap(stagemap, "Resources/csv/firststage_third.csv");
	}
	else if (StageNumber == Map4) {
		m_StageNumber = Map4;
		MapChip::LoadCsvMap(stagemap, "Resources/csv/firststage_fourth.csv");
	}
	else if (StageNumber == Map5) {
		m_StageNumber = Map5;
		MapChip::LoadCsvMap(stagemap, "Resources/csv/firststage_fifth.csv");
	}
	else if (StageNumber == Map6) {
		m_StageNumber = Map6;
		MapChip::LoadCsvMap(stagemap, "Resources/csv/firststage_sixth.csv");
	}
	else if (StageNumber == BossMap) {
		m_StageNumber = BossMap;
		MapChip::LoadCsvMap(stagemap, "Resources/csv/firstboss.csv");
	}
	else if (StageNumber == TutoRial) {
		m_StageNumber = TutoRial;
		MapChip::LoadCsvMap(stagemap, "Resources/csv/tutorial.csv");
	}
	MapCreate(0, StageNumber);
}
//ブロック配置
void MiniMap::MapCreate(int mapNumber, int StageNumber)
{
	for (int y = 0; y < map_max_y; y++) {//(yが15)
		for (int x = 0; x < map_max_x; x++) {//(xが59)

			if (MapChip::GetChipNum(x, y, stagemap[mapNumber]) == 1 || MapChip::GetChipNum(x, y, stagemap[mapNumber]) == 11)
			{
				//位置と大きさの変更
				MiniBlockSprite[y][x]->SetPosition({ x * m_LAND_SCALEX,  y * m_LAND_SCALEY });
			}

			if (MapChip::GetChipNum(x, y, stagemap[mapNumber]) == 7 || MapChip::GetChipNum(x, y, stagemap[mapNumber]) == 8 || MapChip::GetChipNum(x, y, stagemap[mapNumber]) == 9 || MapChip::GetChipNum(x, y, stagemap[mapNumber]) == 10)
			{
				//位置と大きさの変更
				MiniBlockTogeSprite[y][x]->SetPosition({ x * m_LAND_SCALEX,  y * m_LAND_SCALEY });
			}
		}
	}
}
//マップ位置によって描画する位置が変わる
void MiniMap::SetMiniPlayerPos(int StageNumber) {
	if (StageNumber == Map1) {
		MiniPlayerSprite->SetPosition({ 320.0f,120.0f });
	}
	else if (StageNumber == Map2) {
		MiniPlayerSprite->SetPosition({ 860.0f,95.0f });
	}
	else if (StageNumber == Map3) {
		MiniPlayerSprite->SetPosition({ 1050.0f,128.0f });
	}
	else if (StageNumber == Map4) {
		MiniPlayerSprite->SetPosition({ 1096.0f,295.0f });
	}
	else if (StageNumber == Map5) {
		MiniPlayerSprite->SetPosition({ 690.0f,390.0f });
	}
	else if (StageNumber == Map6) {
		MiniPlayerSprite->SetPosition({ 480.0f,290.0f });
	}
	else if (StageNumber == BossMap) {
		MiniPlayerSprite->SetPosition({ 800.0f,610.0f });
	}
	else if (StageNumber == TutoRial) {
		MiniPlayerSprite->SetPosition({ 90.0f,110.0f });
	}
}
//ブロックの初期
void MiniMap::ResetBlock() {
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			LookMap[y][x] = false;
			MiniBlockSprite[y][x]->SetPosition({ 2000.0f,0.0f });
			MiniBlockTogeSprite[y][x]->SetPosition({ 2000.0f,0.0f });
		}
	}
}
//マップの種類
void MiniMap::SelectMapType() {
	Input* input = Input::GetInstance();
	if (input->TriggerButton(input->Button_B)) {
		m_TextTimer = 0;
		m_MapTypeChange = true;
		if (m_MapType == Whole) {
			m_MapType = SelectMap;
		}
		else if (m_MapType == SelectMap) {
			m_MapType = Whole;
		}
	}
}
//全体マップ
void MiniMap::WholeUpdate() {
	float l_AddColor = 0.05f;//加わる色
	if (m_StageNumber == TutoRial) {
		m_PlayerPos = { 160.0f,120.0f };
	}
	else if (m_StageNumber == Map1) {
		m_PlayerPos = { 480.0f,120.0f };
	}
	else if (m_StageNumber == Map2) {
		m_PlayerPos = { 800.0f,120.0f };
	}
	else if (m_StageNumber == Map3) {
		m_PlayerPos = { 1120.0f,120.0f };
	}
	else if (m_StageNumber == Map4) {
		m_PlayerPos = { 1120.0f,360.0f };
	}
	else if (m_StageNumber == Map5) {
		m_PlayerPos = { 800.0f,360.0f };
	}
	else if (m_StageNumber == Map6) {
		m_PlayerPos = { 480.0f,360.0f };
	}
	else if (m_StageNumber == BossMap) {
		m_PlayerPos = { 800.0f,580.0f };
	}
}
//プレイヤーの位置
void MiniMap::SelectUpdate() {

	//プレイヤーの座標
	m_PlayerPos.x = player->GetPosition().x * 4.5f;
	m_PlayerPos.y = player->GetPosition().y * -2.4f;

	m_SavePos.x = save->GetPosition().x * 4.5f;
	m_SavePos.y = save->GetPosition().y * -2.4f;
}
//マップの色切り替え
void MiniMap::ColorChange() {
	float l_AddColor = 0.05f;//加わる色
	//色の変更
	if (m_ColorChangeType == Add) {
		m_MapColor.w += l_AddColor;
		m_PlayerColor.w += l_AddColor;
		m_SaveColor.w += l_AddColor;
		m_WholeColor.w += l_AddColor;
		if ((m_MapColor.w >= m_ColorMax)) {
			m_ColorChangeType = No;
		}
	}
	else if (m_ColorChangeType == Sub) {
		m_MapColor.w -= l_AddColor;
		m_PlayerColor.w -= l_AddColor;
		m_SaveColor.w -= l_AddColor;
		m_WholeColor.w -= l_AddColor;
		if ((m_MapColor.w <= m_ColorMin)) {
			m_ColorChangeType = No;
			m_ReturnMap = true;
			m_TextTimer = 0;
		}
	}
	//段々と色が変わる処理
	helper->FloatClamp(m_MapColor.w, m_ColorMin, m_ColorMax);
	helper->FloatClamp(m_PlayerColor.w, m_ColorMin, m_ColorMax);
	helper->FloatClamp(m_SaveColor.w, m_ColorMin, m_ColorMax);
	helper->FloatClamp(m_WholeColor.w, m_ColorMin, m_ColorMax);
}
//マップを切り替えるテキストが出てくる
void MiniMap::MoveStateTex() {
	Input* input = Input::GetInstance();
	if (m_StateTextNumber == NoText) {
		m_TextTimer++;
		if (m_TextTimer == 150) {
			m_Frame = 0.0f;
			m_AfterStatePos = { 700.0f,640.0f };
			m_TextTimer = 0;
			m_StateTextNumber = StartText;
		}
	}
	else if (m_StateTextNumber == StartText) {
		if (m_Frame < m_ColorMax) {
			m_Frame += 0.05f;
		}
		else {
			m_Frame = m_ColorMax;
		}
		if (input->TriggerButton(input->Button_B) || input->TriggerButton(input->Start)) {
			m_Frame = 0.0f;
			m_AfterStatePos = { 1280.0f,640.0f };
			m_StateTextNumber = BackText;
		}
	}
	else if (m_StateTextNumber == BackText) {
		if (m_Frame < m_ColorMax) {
			m_Frame += 0.05f;
		}
		else {
			m_StateTextNumber = NoText;
			m_Frame = 0.0f;
		}
	}

	m_StatePos = { Ease(In,Cubic,m_Frame,m_StatePos.x,m_AfterStatePos.x),
		Ease(In, Cubic, m_Frame, m_StatePos.y, m_AfterStatePos.y),
	};
}