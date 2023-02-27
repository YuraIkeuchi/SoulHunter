#include "PlaySceneActor.h"
#include "Audio.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include "imgui.h"
#include "VariableCommon.h"
#include "PlayerSkill.h"
#include "ParticleEmitter.h"
#include "OpenBrowser.h"
//�v���C�V�[���̏�����(���݂͍�����)
void PlaySceneActor::PlaySceneInitialize() {
	enemymanager->SoulSet(player, block);
}
//������
void PlaySceneActor::Initialize(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup)
{
	//�ŏ���new����
	player = new GamePlayer();
	skillpause = new SkillPause();
	option = new Option();
	pause = new Pause();
	mapchange = new MapChange();
	save = new Save();
	chest = new Chest();
	respornenemy = new ResPornEnemy();
	firstboss = new FirstBoss();
	camerawork = new CameraWork();
	enemymanager = new EnemyManager();
	backmanager = new BackObjManager();
	camerawork->SetCameraType(2);
	dxCommon->SetFullScreen(true);
	//���ʂ̏�����
	BaseInitialize(dxCommon);
	//�v���C���[������
	PlayerInitialize();
	//�I�[�f�B�I
	Audio::GetInstance()->LoadSound(1, "Resources/Sound/BGM/Boss.wav");
	//�J�����̏�����
	CameraInitialize();
	//�|�[�Y�̏�����
	PauseInitialize();
	//�G�̏�����
	EnemyInitialize();
	//�w�iOBJ�̏�����
	BackObjInitialize();
	//�v���C���[�̎菕���ɂȂ���̂̏�����
	HelperInitialize();
	//�v���C�V�[���̏�����
	PlaySceneInitialize();
	//�V�[���J��
	scenechange = new SceneChange();
	scenechange->SetSubStartChange(true);
	//���񂾂Ƃ��ɈÂ��Ȃ�悤�̂��
	BlackFilter = IKESprite::Create(ImageManager::BlackFilter, { 0.0f,0.0f });
	BlackFilter->SetColor(BlackColor);
	BlackFilter->SetSize({ 1280.0f,720.0f });
	//���[�h������
	StartGame(lightgroup);
	enemymanager->SetPause(pause);
	enemymanager->SetChest(chest);
	backmanager->LoadObjParam(StageNumber, player, lightgroup);
	backmanager->LoadBackObjAlways(StageNumber);
	BGMStart = true;
	//�{�X�V�[���̂��߂̂���
	BossStagObj* bossstagobj_;
	bossstagobj_ = new BossStagObj();
	bossstagobj_->Initialize();
	bossstagobj.reset(bossstagobj_);

	BossSceneChange* bossscenechange_;
	bossscenechange_ = new BossSceneChange();
	bossscenechange.reset(bossscenechange_);

	//�v���C���[�h�͓G�𓮂���
	m_MoveEnemy = true;

	//�|�X�g�G�t�F�N�g�̃t�@�C���w��
	postEffect->CreateGraphicsPipeline(L"Resources/Shaders/PostEffectTestVS.hlsl", L"Resources/Shaders/NewToneMapPS.hlsl");

	ParticleEmitter::GetInstance()->AllDelete();

	PlayPostEffect = true;
}
//�X�V
void PlaySceneActor::Update(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup)
{
	//�{�X�o��V�[���̍X�V
	if (m_BossNumber == BossApp) {
		BossAppUpdate();
	}
	else if (m_BossNumber == BossEnd) {
		//�{�X��|������̍X�V
		BossEndUpdate();
	}
	else {
		//���ʂ̏����̍X�V
		NormalUpdate();
	}
	//�e�N���X�X�V
	AllUpdate(camera);
	//���̔z�u
	LightSet(lightgroup);
	//�{�X�̕����̏���
	BossRoomUpdate();
	//�S�[������
	GoalHit();
	//�V�[����}�b�v�̕ύX�̏���
	ChangeUpdate();
	//BGM�X�^�[�g
	if (BGMStart == true) {
		Audio::GetInstance()->LoopWave(0, VolumManager::GetInstance()->GetBGMVolum());
		BGMStart = false;
	}
	//���y�̉��ʂ��ς��
	Audio::GetInstance()->VolumChange(0, VolumManager::GetInstance()->GetBGMVolum());

	//�}�b�v�̓ǂݍ���
	MapInitialize(lightgroup);

	//�Q�[���̃Z�[�u
	if (save->GetGameSave()) {
		StartStage = StageNumber;
		SaveGame();
		save->SetGameSave(false);
	}

	m_PlayerPos = camera->GetEye();
}
//���ʂ̍X�V
void PlaySceneActor::NormalUpdate() {
	block->Update(m_PlayerPos);

	//�v���C���[�̍X�V
	if (!pause->GetIsPause() && !chest->GetExplain()) {
		player->Update();
	}
	else {
		player->Pause();
	}
	//�ݒu�����G�̍X�V
	enemymanager->Update(m_MoveEnemy);
	enemymanager->SoulUpdate();
	backmanager->Update();

	tutorialtext->Update();

	//���̑��̍X�V
	if (!pause->GetIsPause() && m_BossNumber == BossBattle) {
		respornenemy->Update(firstboss);
	}

	//�p�[�e�B�N���`��
	ParticleEmitter::GetInstance()->Update();
	minimap->SetMiniPlayerPos(StageNumber);
	pause->Update();
	chest->Update();
	VolumManager::GetInstance()->Update();
	save->Update();
	BlackFilter->SetColor(BlackColor);
	if (StageNumber == BossMap) {
		ui->Update(firstboss);
	}
	else {
		ui->Update();
	}
}
//�{�X�o��̍X�V
void PlaySceneActor::BossAppUpdate() {
	player->BossAppUpdate(1);
	bossstagobj->AppUpdate();
	firstboss->AppUpdate();
}
//�{�X�I���̍X�V
void PlaySceneActor::BossEndUpdate() {
	player->BossEndUpdate(1);
	firstboss->EndUpdate();
	bossstagobj->EndUpdate();
	//�p�[�e�B�N���`��
	ParticleEmitter::GetInstance()->Update();
}
//�`��
void PlaySceneActor::Draw(DirectXCommon* dxCommon)
{
	//�`����@
	//�|�X�g�G�t�F�N�g�������邩
	if (PlayPostEffect) {
		postEffect->PreDrawScene(dxCommon->GetCmdList());
		BackDraw(dxCommon);
		postEffect->PostDrawScene(dxCommon->GetCmdList());

		dxCommon->PreDraw();
		postEffect->Draw(dxCommon->GetCmdList());
		FrontDraw(dxCommon);
		ImGuiDraw(dxCommon);
		postEffect->ImGuiDraw();
		dxCommon->PostDraw();
	}
	else {
		postEffect->PreDrawScene(dxCommon->GetCmdList());
		postEffect->Draw(dxCommon->GetCmdList());
		postEffect->PostDrawScene(dxCommon->GetCmdList());
		dxCommon->PreDraw();
		if (StageNumber != BossMap) {
			ImGuiDraw(dxCommon);
		}
		camerawork->ImGuiDraw();
		BackDraw(dxCommon);
		FrontDraw(dxCommon);
		dxCommon->PostDraw();
	}
}
//���
void PlaySceneActor::Finalize()
{
	delete postEffect;
}
//���f���̕`��
void PlaySceneActor::ModelDraw(DirectXCommon* dxCommon) {
	if (m_BossNumber == BossApp || m_BossNumber == BossEnd) {
		bossstagobj->BackDraw();
	}

	//�{�X�o��V�[�����ǂ����ŕ`������߂�
	if (m_BossNumber == BossApp) {
		BossAppDraw(dxCommon);
	}
	else if (m_BossNumber == BossEnd) {
		BossEndDraw(dxCommon);
	}
	else {
		NormalDraw(dxCommon);
	}

}
//���̕`��
void PlaySceneActor::BackDraw(DirectXCommon* dxCommon)
{
#pragma endregion
	ModelDraw(dxCommon);
}
//�|�X�g�G�t�F�N�g��������Ȃ�
void PlaySceneActor::FrontDraw(DirectXCommon* dxCommon) {
	//���S�ɑO�ɏ����X�v���C�g
	IKESprite::PreDraw();
	if (player->GetHP() != 0) {
		chest->SpriteDraw();
		tutorialtext->SpriteDraw();
		pause->Draw();
		BlackFilter->Draw();
		chest->MapDraw(minimap->GetMapType(), minimap->GetMapColor(), pause->GetIsPause(), pause->GetPauseNumber());
		enemymanager->MapDraw(minimap->GetMapType(), minimap->GetMapColor());
	}
	mapchange->Draw();
	scenechange->Draw();
	bossscenechange->Draw();
	IKESprite::PostDraw();
}
//IMGui�̕`��
void PlaySceneActor::ImGuiDraw(DirectXCommon* dxCommon) {
	{
		ImGui::Begin("Scene");
		ImGui::SetWindowPos(ImVec2(1000, 150));
		ImGui::SetWindowSize(ImVec2(280, 150));
		if (ImGui::RadioButton("m_EditorScene", &m_SceneChange)) {
			scenechange->SetAddStartChange(true);
			m_SceneChange = true;
			m_SceneMigration = Editor;
		}
		if (ImGui::RadioButton("m_TitleScene", &m_SceneChange)) {
			scenechange->SetAddStartChange(true);
			m_SceneChange = true;
			m_SceneMigration = Title;
		}
		ImGui::End();
	}
}
//���ʂ̕`��
void PlaySceneActor::NormalDraw(DirectXCommon* dxCommon) {
	//��ʂ������Ԃ͕`�悳��Ȃ�
	if (BlackColor.w <= 1.0f) {
		//�X�e�[�W�̕`��
		backmanager->AlwaysDraw(dxCommon);
		block->Draw(m_PlayerPos);
		if (StageNumber != BossMap) {
			backmanager->Draw(dxCommon);
		}
		save->Draw();
		//�`���[�g���A��
		tutorialtext->Draw();
		//������΂�
		chest->Draw();
		//�G�̕`��
		enemymanager->Draw(dxCommon);
		enemymanager->SoulDraw();
		//�{�X�̕`��
		if (StageNumber == BossMap) {
			firstboss->Draw(dxCommon);
			respornenemy->Draw();
		}
		ParticleEmitter::GetInstance()->SmokeDrawAll();
		ParticleEmitter::GetInstance()->FireDrawAll();
	}
	IKESprite::PreDraw();
	ui->Draw();
	if (player->GetHP() == 0) {
		BlackFilter->Draw();
	}
	IKESprite::PostDraw();
	//�p�[�e�B�N���`��
	ParticleEmitter::GetInstance()->FlontDrawAll();
	//�v���C���[�̕`��
	player->Draw(dxCommon);
	// 3D�I�u�W�F�N�g�`��㏈��
	IKEObject3d::PostDraw();

}
//�{�X�o��V�[���̕`��
void PlaySceneActor::BossAppDraw(DirectXCommon* dxCommon) {
	firstboss->AppDraw(dxCommon);
	player->BossAppDraw(dxCommon);
	bossstagobj->FrontDraw();
}
//�{�X�I���V�[���̕`��
void PlaySceneActor::BossEndDraw(DirectXCommon* dxCommon) {
	firstboss->EndDraw(dxCommon);
	player->BossEndDraw(dxCommon);
	camerawork->EndDraw();
	bossstagobj->FrontDraw();
	ParticleEmitter::GetInstance()->FlontDrawAll();
}
//�}�b�v�������Ƃ���ɍ��킹��������
void PlaySceneActor::MapInitialize(LightGroup* lightgroup) {
	//�}�b�v�̓ǂݍ���
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
		AllDelete();
		player->InitPlayer(StageNumber);
		save->InitSave(StageNumber);
		tutorialtext->InitBoard(StageNumber);
		chest->InitChest(StageNumber);
		enemymanager->LoadEnemyParam(StageNumber, player, block, lightgroup);
		backmanager->LoadObjParam(StageNumber, player, lightgroup);
		backmanager->LoadBackObjAlways(StageNumber);
		StageChange = false;
		player->SetGoalDir(0);
	}
}
//�S�폜
void PlaySceneActor::AllDelete() {
	enemymanager->DeleteEnemy();
	backmanager->ObjDelete();
	//�v�f�S�폜
	player->Finalize();
	ParticleEmitter::GetInstance()->AllDelete();
}
//�e�N���X�̍X�V
void PlaySceneActor::AllUpdate(DebugCamera* camera) {
	scenechange->Update();
	scenechange->SubBlack(0.05f);
	mapchange->Update();
	mapchange->SubBlack();
	bossscenechange->Update();
	bossscenechange->SubBlack(0.08f);
	camerawork->Update(camera);
}
//���C�g�̈ʒu
void PlaySceneActor::LightSet(LightGroup* lightgroup) {
	lightgroup->Update();
	///�|�C���g���C�g
	lightgroup->SetPointLightPos(0, XMFLOAT3(player->GetPosition().x, player->GetPosition().y + 2.0f, player->GetPosition().z - 5.0f));
	lightgroup->SetPointLightColor(0, XMFLOAT3(pointLightColor));
	lightgroup->SetPointLightAtten(0, XMFLOAT3({ 6.0f,6.0f,6.0f }));

	lightgroup->SetPointLightPos(1, XMFLOAT3(save->GetPosition().x, save->GetPosition().y + 5.0f, save->GetPosition().z + 2.0f));
	lightgroup->SetPointLightColor(1, XMFLOAT3(pointLightColor));
	lightgroup->SetPointLightAtten(1, XMFLOAT3(pointLightAtten));


	if (StageNumber != BossMap) {
		lightgroup->SetPointLightActive(1, true);
	}
	else {
		lightgroup->SetPointLightActive(1, false);
	}
	//�ۉe
	lightgroup->SetCircleShadowDir(0, XMVECTOR({ circleShadowDir[0], circleShadowDir[1], circleShadowDir[2], 0 }));
	if (m_BossNumber == BossApp || m_BossNumber == BossEnd) {
		lightgroup->SetCircleShadowCasterPos(0, XMFLOAT3({ 0.0f, 8.0f, 0.0f }));
	}
	else {
		lightgroup->SetCircleShadowCasterPos(0, XMFLOAT3({ player->GetPosition().x, player->GetPosition().y, player->GetPosition().z }));
	}
	lightgroup->SetCircleShadowAtten(0, XMFLOAT3(circleShadowAtten));
	lightgroup->SetCircleShadowFactorAngle(0, XMFLOAT2(circleShadowFactorAngle));

	enemymanager->LightSet(StageNumber, lightgroup);
	backmanager->LightSet(StageNumber, lightgroup);
}
//�{�X�����̏���
void PlaySceneActor::BossRoomUpdate() {
	Input* input = Input::GetInstance();
	//�{�X�����̏���
	if (StageNumber == BossMap) {
		Audio::GetInstance()->StopWave(0);
		firstboss->SetAlive(true);
		//�{�X�o��
		if (m_BossNumber == BossApp) {
			//�J�������[�N��v���C���[�̋���
			camerawork->SetCameraType(3);
			firstboss->SetMovie(true);
			player->SetMovie(true);

			//���t���[���Ń{�X��ɓ���
			if (bossstagobj->GetAppTimer() == 800) {
				bossscenechange->SetAddStartChange(true);
			}
			//�{�^���ł��s����
			if (input->TriggerButton(input->Button_A) && !bossscenechange->GetSubStartChange()) {
				bossscenechange->SetAddStartChange(true);
				bossstagobj->SetEndApp(true);
			}

			//��������{�X��
			if (bossscenechange->AddBlack(0.04f)) {
				ParticleEmitter::GetInstance()->AllDelete();
				bossscenechange->SetSubStartChange(true);
				bossstagobj->SetApp(false);
				Audio::GetInstance()->LoopWave(1, VolumManager::GetInstance()->GetBGMVolum());
				firstboss->SetMovie(false);
				m_BossNumber = BossBattle;
				player->SetMovie(false);
				firstboss->BattleInitialize();
			}

		}
		else if (m_BossNumber == BossBattle) {
			//�{�X�o�g��
			////�����_���œG���o������
			//if (respornenemy->GetEnemyArgment()) {
			//	InterEnemy* newEnemy;
			//	newEnemy = new Enemy();
			//	newEnemy->Initialize();
			//	newEnemy->SetPlayer(player);
			//	newEnemy->SetBlock(block);
			//	newEnemy->SetPosition(respornenemy->GetResPornPosition());
			//	m_Enemys.push_back(newEnemy);
			//	m_NormalEnemyCount++;
			//	respornenemy->SetEnemyArgment(false);
			//}
			camerawork->SetCameraType(2);

			if (StageNumber == BossMap) {
				if (!pause->GetIsPause()) {
					firstboss->Update();
				}
				else {
					firstboss->Pause();
				}
			}

			//�{�X��|�������Ƃ̏���
			if (firstboss->GetDeathTimer() > 100) {
				bossscenechange->SetAddStartChange(true);
				Audio::GetInstance()->StopWave(1);
			}
			if (bossscenechange->AddBlack(0.04f)) {
				m_BossNumber = BossEnd;
				bossscenechange->SetSubStartChange(true);
			}
		}
		else if (m_BossNumber == BossEnd) {
			camerawork->SetCameraType(4);
			//���t���[���Ń^�C�g���ɖ߂�
			if (bossstagobj->GetEndTimer() == 670) {
				scenechange->SetAddStartChange(true);
			}
			//�{�^���ł��s����
			if (input->TriggerButton(input->Button_A) && !bossscenechange->GetSubStartChange()) {
				scenechange->SetAddStartChange(true);
			}
		}
	}
	else {
		camerawork->SetCameraType(2);
		firstboss->SetAlive(false);
	}
}
//�V�[���ύX�Ȃ�
void PlaySceneActor::ChangeUpdate() {
	//���񂾂Ƃ����߂����
	if (player->DeathMove()) {
		scenechange->SetAddStartChange(true);
	}
	//�V�[���ύX
	if (scenechange->AddBlack(0.05f)) {
		//ImGui�ŃV�[����؂�ւ������ǂ���
		if (m_SceneChange) {
			m_GameLoad = true;
			StartStage = StageNumber;
			block->ResetBlock();
			minimap->ResetBlock();
			//�V�[��������߂�
			if (m_SceneMigration == Editor) {
				SceneManager::GetInstance()->ChangeScene("EDITORSCENE");
			}
			else if (m_SceneMigration == Title) {
				m_GameLoop = true;
				Audio::GetInstance()->StopWave(0);
				SceneManager::GetInstance()->ChangeScene("TITLE");
			}
			m_SceneChange = false;
		}
		else {
			block->ResetBlock();
			minimap->ResetBlock();
			Audio::GetInstance()->StopWave(0);
			Audio::GetInstance()->StopWave(1);
			if (player->GetHP() < 1) {
				SceneManager::GetInstance()->ChangeScene("TITLE");
				m_GameLoop = true;
			}
			else {
				SceneManager::GetInstance()->ChangeScene("GAMECLEAR");
				m_GameLoop = true;
			}
		}
	}

	//�w�i���Â��Ȃ邩�ǂ���
	if (!player->GetAlive() && BlackColor.w < 1.0f) {
		BlackColor.w += 0.1f;
	}
	else if (player->GetAlive() && BlackColor.w > 0.0f) {
		BlackColor.w -= 0.1f;
	}
}
//�S�[������
void PlaySceneActor::GoalHit() {
	//�S�[������
	if (!player->GetChangeInterVal()) {
		if (block->GetLeftGoal()) {
			player->SetChangeInterVal(true);
			player->SetGoalDir(1);
			if (StageNumber == Map1) {
				StageNumber = TutoRial;
			}
			else if (StageNumber == Map2) {
				StageNumber = Map1;
			}
			else if (StageNumber == Map3) {
				StageNumber = Map2;
			}
			else if (StageNumber == Map4) {
				StageNumber = Map5;
			}
			else if (StageNumber == Map5) {
				StageNumber = Map6;
			}
			mapchange->SetAddStartChange(true);
			block->SetLeftGoal(false);
		}

		if (block->GetRightGoal()) {
			player->SetChangeInterVal(true);
			player->SetGoalDir(2);
			if (StageNumber == TutoRial) {
				StageNumber = Map1;
			}
			else if (StageNumber == Map1) {
				StageNumber = Map2;
			}
			else if (StageNumber == Map2) {
				StageNumber = Map3;
			}
			else if (StageNumber == Map5) {
				StageNumber = Map4;
			}
			else if (StageNumber == Map6) {
				StageNumber = Map5;
			}
			mapchange->SetAddStartChange(true);
			block->SetRightGoal(false);
		}

		if (block->GetDownGoal()) {
			player->SetChangeInterVal(true);
			player->SetGoalDir(4);
			if (StageNumber == Map1) {
				StageNumber = Map6;
			}
			else if (StageNumber == Map3) {
				StageNumber = Map4;
			}
			else if (StageNumber == Map5) {
				StageNumber = BossMap;
				firstboss->SetMovie(true);
			}
			mapchange->SetAddStartChange(true);
			block->SetDownGoal(false);
		}

		if (block->GetUpGoal()) {
			player->SetGoalDir(3);
			player->SetChangeInterVal(true);
			if (StageNumber == Map4) {
				StageNumber = Map3;
			}
			else if (StageNumber == Map6) {
				StageNumber = Map1;
			}
			mapchange->SetAddStartChange(true);
			block->SetUpGoal(false);
		}
	}

	//�}�b�v�ύX
	if (mapchange->AddBlack()) {
		StageChange = true;
		block->ResetBlock();
		minimap->ResetBlock();
		mapchange->SetSubStartChange(true);
		if (StageNumber == BossMap) {
			m_BossNumber = BossApp;
			bossstagobj->SetAppStart(true);
		}
	}
}