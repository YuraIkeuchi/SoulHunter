//#pragma once
//#include "Input.h"
//#include "UI.h"
//#include "Pause.h"
//#include "SkillPause.h"
//#include "MiniMap.h"
//#include "Option.h"
//#include "TutorialText.h"
//#include "DirectXCommon.h"
//#include "Player.h"
//#include "PlayerSkill.h"
//#include "VolumManager.h"
//#include "InterBoss.h"
////UIやポーズなどをまとめた変数
//class PlayerHelp {
//public:
//	void SetPlayerSkill(PlayerSkill* playerskill) { this->playerskill.reset(playerskill); }
//	void SetPlayer(Player* player) { this->player.reset(player); }
//	void SetInterBoss(InterBoss* interboss) { this->firstboss.reset(interboss); }
//	PlayerHelp();
//public:
//	//初期化
//	void Initialize();
//	//更新
//	void Update();
//	//uiのアップデート
//	void BossAliveUpdate(InterBoss* boss = nullptr);
//	void NotAliveUpdate();
//	//描画
//	void ObjDraw();
//	void SpriteDraw();
//	//初期配置
//	void InitPos(std::vector<std::vector<int>>& map, const int& StageNumber);
//	//ロード時
//	void LoadInit(std::vector<std::vector<int>>& map, const int& StageNumber);
//	//マップ読み込み
//	void InitMap(std::vector<std::vector<int>>& map, const int& StageNumber);
//	//ミニマップリセット
//	void ResetMiniMap();
//	//スキルリセット
//	void ResetSkill();
//	void EndSave();
//	//セーブとチューtリアルテキストの初期化
//	void HelpObjInit(const int& StageNumber);
//public:
//	//getter
//	const bool& GetIsPause() { return m_IsPause; }
//	const bool& GetGameSave() { return  m_GameSave; }
//	//setter
//	void SetIsPause(const bool& IsPause) { this->m_IsPause = IsPause; }
//	void SetGameSave(const bool& m_GameSave) { this->m_GameSave = m_GameSave; }
//
//private:
//	//クラス
//	unique_ptr<PlayerSkill> playerskill = nullptr;
//	unique_ptr<Player> player = nullptr;
//	//ボス
//	unique_ptr<InterBoss> firstboss = nullptr;
//	//ポーズメニュー関連
//	Pause* pause;
//	SkillPause* skillpause = nullptr;
//	MiniMap* minimap = nullptr;
//	Option* option = nullptr;
//	//UI関係
//	UI* ui = nullptr;
//	//チュートリアルのテキスト
//	array<TutorialText*, Tutorial_Max> tutorialtext;
//	//共通変数(クリアしたかどうか)
//	Save* save = nullptr;
//	//セーブポイントに近づいたときの変数
//	bool m_GameSave = false;
//	bool m_IsPause = false;
//};