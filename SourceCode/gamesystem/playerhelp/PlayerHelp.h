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
////UI��|�[�Y�Ȃǂ��܂Ƃ߂��ϐ�
//class PlayerHelp {
//public:
//	void SetPlayerSkill(PlayerSkill* playerskill) { this->playerskill.reset(playerskill); }
//	void SetPlayer(Player* player) { this->player.reset(player); }
//	void SetInterBoss(InterBoss* interboss) { this->firstboss.reset(interboss); }
//	PlayerHelp();
//public:
//	//������
//	void Initialize();
//	//�X�V
//	void Update();
//	//ui�̃A�b�v�f�[�g
//	void BossAliveUpdate(InterBoss* boss = nullptr);
//	void NotAliveUpdate();
//	//�`��
//	void ObjDraw();
//	void SpriteDraw();
//	//�����z�u
//	void InitPos(std::vector<std::vector<int>>& map, const int& StageNumber);
//	//���[�h��
//	void LoadInit(std::vector<std::vector<int>>& map, const int& StageNumber);
//	//�}�b�v�ǂݍ���
//	void InitMap(std::vector<std::vector<int>>& map, const int& StageNumber);
//	//�~�j�}�b�v���Z�b�g
//	void ResetMiniMap();
//	//�X�L�����Z�b�g
//	void ResetSkill();
//	void EndSave();
//	//�Z�[�u�ƃ`���[t���A���e�L�X�g�̏�����
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
//	//�N���X
//	unique_ptr<PlayerSkill> playerskill = nullptr;
//	unique_ptr<Player> player = nullptr;
//	//�{�X
//	unique_ptr<InterBoss> firstboss = nullptr;
//	//�|�[�Y���j���[�֘A
//	Pause* pause;
//	SkillPause* skillpause = nullptr;
//	MiniMap* minimap = nullptr;
//	Option* option = nullptr;
//	//UI�֌W
//	UI* ui = nullptr;
//	//�`���[�g���A���̃e�L�X�g
//	array<TutorialText*, Tutorial_Max> tutorialtext;
//	//���ʕϐ�(�N���A�������ǂ���)
//	Save* save = nullptr;
//	//�Z�[�u�|�C���g�ɋ߂Â����Ƃ��̕ϐ�
//	bool m_GameSave = false;
//	bool m_IsPause = false;
//};