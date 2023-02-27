#include "EditorSceneActor.h"
#include "Audio.h"
#include "SceneManager.h"
#include "imgui.h"
#include "VariableCommon.h"
#include "PlayerSkill.h"
#include "ParticleEmitter.h"
//������
void EditorSceneActor::Initialize(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup)
{
	//�e�N���X��new
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
	//���ʂ̏�����
	BaseInitialize(dxCommon);
	//�v���C���[������
	PlayerInitialize();
	//�J�����̏�����
	CameraInitialize();
	//�w�iOBJ�̏�����
	BackObjInitialize();
	//�|�[�Y�̏�����
	PauseInitialize();
	//�v���C���[�̎菕���ɂȂ���̂̏�����
	HelperInitialize();
	//�V�[���J��
	scenechange = new SceneChange();
	scenechange->SetSubStartChange(true);
	//�G�f�B�^
	ImGuiEditor* imguieditor_;
	imguieditor_ = new ImGuiEditor();
	imguieditor.reset(imguieditor_);
	enemymanager->SetPause(pause);
	enemymanager->SetChest(chest);
	enemymanager->LoadEnemyParam(StageNumber, player, block, lightgroup);
	backmanager->LoadObjParam(StageNumber, player, lightgroup);
	BGMStart = true;

	//�G�f�B�^���[�h�͍ŏ��͓G���~�߂�
	m_MoveEnemy = false;

	//�|�X�g�G�t�F�N�g�̃t�@�C���w��
	postEffect->CreateGraphicsPipeline(L"Resources/Shaders/PostEffectTestVS.hlsl", L"Resources/Shaders/NewToneMapPS.hlsl");

	ParticleEmitter::GetInstance()->AllDelete();

	PlayPostEffect = true;
}
//�X�V
void EditorSceneActor::Update(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup)
{
	//�e�N���X�X�V
	AllUpdate(camera);
	//���̔z�u
	LightSet(lightgroup);
	//�V�[����}�b�v�̕ύX�̏���
	ChangeUpdate();
	//���y�̉��ʂ��ς��
	Audio::GetInstance()->VolumChange(0, VolumManager::GetInstance()->GetBGMVolum());
	//�G�f�B�^����HP������Ȃ�
	player->SetHP(5);
	//�}�b�v�̓ǂݍ���
	MapInitialize();
	//�G�̈ʒu�Z�[�u
	if (m_EditorSave) {
		enemymanager->OpenEnemyParam(StageNumber);
		enemymanager->SaveEnemyParam(StageNumber);
		m_EditorSave = false;
	}

	//�G�̈ʒu���[�h
	if (m_EditorLoad) {
		enemymanager->LoadEnemyParam(StageNumber, player, block, lightgroup);
		m_EditorLoad = false;
	}

	//�w�iOBJ�̈ʒu�Z�[�u
	if (m_ObjSave) {
		backmanager->OpenObjParam(StageNumber);
		backmanager->SaveObjParam(StageNumber);
		m_ObjSave = false;
	}

	//�w�iOBJ�̈ʒu���[�h
	if (m_ObjLoad) {
		backmanager->LoadObjParam(StageNumber, player, lightgroup);
		m_ObjLoad = false;
	}

	//�Q�[���̃Z�[�u
	if (save->GetGameSave()) {
		StartStage = StageNumber;
		SaveGame();
		save->SetGameSave(false);
	}

	//�G�f�B�^�֌W
	EditorUpdate();

	//�v�f�S�폜(�G)
	if (m_EnemyDelete) {
		enemymanager->DeleteEnemy();
		m_EnemyDelete = false;
	}
	//�v�f�S�폜(OBJ)
	if (m_ObjDelete) {
		backmanager->ObjDelete();
		m_ObjDelete = false;
	}

	//�}�b�v�`�F���W
	if (m_MapChange) {
		StageMapChange(StageNumber,lightgroup);
		m_MapChange = false;
	}

	m_PlayerPos = camera->GetEye();
}
//�`��
void EditorSceneActor::Draw(DirectXCommon* dxCommon)
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
//���
void EditorSceneActor::Finalize()
{
	delete postEffect;
}
//���f���̕`��
void EditorSceneActor::ModelDraw(DirectXCommon* dxCommon) {
#pragma region 3D�I�u�W�F�N�g�`��
	//�w�i�͐�ɕ`�悷��

}
//���̕`��
void EditorSceneActor::BackDraw(DirectXCommon* dxCommon)
{
	IKEObject3d::PreDraw();
	backmanager->AlwaysDraw(dxCommon);
	block->Draw(m_PlayerPos);
	if (StageNumber != BossMap) {
		backmanager->Draw(dxCommon);
	}
	save->Draw();
	//�G�̕`��
	enemymanager->Draw(dxCommon);
	tutorialtext->Draw();
	ParticleEmitter::GetInstance()->SmokeDrawAll();
	ParticleEmitter::GetInstance()->FireDrawAll();
	//������΂�
	chest->Draw();
	//�p�[�e�B�N���`��
	ParticleEmitter::GetInstance()->FlontDrawAll();
	//ImGui��OBJ�̕`��
	imguieditor->ObjDraw();
	// 3D�I�u�W�F�N�g�`��㏈��
	IKEObject3d::PostDraw();
}
//�|�X�g�G�t�F�N�g��������Ȃ�
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
//IMGui�̕`��
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
	//WEB�y�[�W�I�[�v��
	{
		ImGui::Begin("Open");
		ImGui::SetWindowPos(ImVec2(1000, 450));
		ImGui::SetWindowSize(ImVec2(280, 300));
		if (ImGui::Button("OPENWEB")) {
			openbrowser->OpenWebPage();
		}
		ImGui::End();
	}
	//�G����
	imguieditor->EditorImGuiDraw();
	{
		//�}�b�v�؂�ւ�
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
	//�Z�[�u�ƃ��[�h
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
//�}�b�v�̓ǂݍ��݂Ƃ���ɍ��킹��������
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
//�}�b�v�؂�ւ��̊֐�
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
//�e�N���X�̍X�V
void EditorSceneActor::AllUpdate(DebugCamera* camera) {

	scenechange->Update();
	scenechange->SubBlack(0.05f);
	mapchange->Update();
	mapchange->SubBlack();
	block->Update(m_PlayerPos);

	//�Ղꂢ��[�̍X�V
	if (!pause->GetIsPause() && !chest->GetExplain()) {
		player->Editor();
	}
	else {
		player->Pause();
	}

	//�ݒu�����G�̍X�V
	enemymanager->Update(m_MoveEnemy);
	backmanager->Update();

	tutorialtext->Update();

	//���̑��̍X�V
	ParticleEmitter::GetInstance()->Update();
	minimap->SetMiniPlayerPos(StageNumber);
	pause->Update();
	chest->Update();
	VolumManager::GetInstance()->Update();
	save->Update();
	ui->Update();
	camerawork->Update(camera);
}
//���C�g�̈ʒu
void EditorSceneActor::LightSet(LightGroup* lightgroup) {
	lightgroup->Update();
	///�|�C���g���C�g
	lightgroup->SetPointLightPos(0, XMFLOAT3(player->GetPosition().x, player->GetPosition().y, player->GetPosition().z - 5.0f));
	lightgroup->SetPointLightColor(0, XMFLOAT3(pointLightColor));
	lightgroup->SetPointLightAtten(0, XMFLOAT3({ 10.0f,10.0f,10.0f }));

	lightgroup->SetPointLightPos(1, XMFLOAT3(save->GetPosition().x, save->GetPosition().y + 2.0f, save->GetPosition().z + 2.0f));
	lightgroup->SetPointLightColor(1, XMFLOAT3(pointLightColor));
	lightgroup->SetPointLightAtten(1, XMFLOAT3(pointLightAtten));

	//�ۉe
	lightgroup->SetCircleShadowDir(0, XMVECTOR({ circleShadowDir[0], circleShadowDir[1], circleShadowDir[2], 0 }));
	lightgroup->SetCircleShadowCasterPos(0, XMFLOAT3({ player->GetPosition().x, player->GetPosition().y, player->GetPosition().z }));
	lightgroup->SetCircleShadowAtten(0, XMFLOAT3(circleShadowAtten));
	lightgroup->SetCircleShadowFactorAngle(0, XMFLOAT2(circleShadowFactorAngle));

	enemymanager->LightSet(StageNumber, lightgroup);
	backmanager->LightSet(StageNumber, lightgroup);
}
//�V�[���ύX�Ȃ�
void EditorSceneActor::ChangeUpdate() {

	//���񂾂Ƃ����߂����
	if (player->GetHP() < 1) {
		scenechange->SetAddStartChange(true);
	}

	//ImGui�ŃV�[����؂�ւ������ǂ���
	if (scenechange->AddBlack(0.05f)) {
		//�Q�[���V�[���֕ύX
		if (m_SceneChange) {
			m_GameLoad = true;
			StartStage = StageNumber;
			block->ResetBlock();
			minimap->ResetBlock();
			SaveGame();
			//�V�[��������߂�
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
	//�}�b�v�؂�ւ�
	if (mapchange->AddBlack()) {
		block->ResetBlock();
		minimap->ResetBlock();
		mapchange->SetSubStartChange(true);
		StageChange = true;
	}

	//�w�i���Â��Ȃ邩�ǂ���
	if (!player->GetAlive() && BlackColor.w < 1.0f) {
		BlackColor.w += 0.02f;
	}
	else if (player->GetAlive() && BlackColor.w > 0.0f) {
		BlackColor.w -= 0.02f;
	}
}
//�G�f�B�^�֌W�̍X�V
void EditorSceneActor::EditorUpdate() {

	imguieditor->Update(player->GetPosition());
	//�G�l�~�[�̐���
	if (imguieditor->GetEnemyArgment()) {
		//����
		if (imguieditor->GetEnemyType() == Normal) {
			enemymanager->EnemyBirth(Normal, player, block);
		}
		//���̂��
		else if (imguieditor->GetEnemyType() == Thorn) {
			enemymanager->EnemyBirth(Thorn, player, block);
		}
		//�H�̓G
		else if (imguieditor->GetEnemyType() == Bound) {
			enemymanager->EnemyBirth(Bound, player, block);
		}
		//���̓G
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
	//���̂��(OBJ)
	if (imguieditor->GetThornObjArgment()) {
		enemymanager->ThornBirth(imguieditor->GetThornObjArgment(), player, imguieditor->GetThornDir());

		imguieditor->SetThornObjArgment(false);
	}
	//�w�iobj�̐���
	if (imguieditor->GetBackObjArgment()) {
		//��
		if (imguieditor->GetBackObjType() == BackOBJRock) {
			backmanager->ObjBirth(BackOBJRock, player, imguieditor->GetPosition(), imguieditor->GetRotation());
		}
		//��
		else if (imguieditor->GetBackObjType() == BackOBJBox) {
			backmanager->ObjBirth(BackOBJBox, player, imguieditor->GetPosition(), imguieditor->GetRotation());
		}
		//����
		else {
			backmanager->ObjBirth(BackOBJTorch, player, imguieditor->GetPosition(), imguieditor->GetRotation());
		}
		imguieditor->SetBackObjArgment(false);
	}
	//�G�l�~�[�̍폜
	//����
	if (imguieditor->GetEnemyDelete()) {
		if (imguieditor->GetEnemyType() == Normal) {
			enemymanager->DeleteEnemyPop(imguieditor->GetEnemyType());
		}
		//�Ƃ�
		else if (imguieditor->GetEnemyType() == Thorn) {
			enemymanager->DeleteEnemyPop(imguieditor->GetEnemyType());
		}
		//�H
		else if (imguieditor->GetEnemyType() == Bound) {
			enemymanager->DeleteEnemyPop(imguieditor->GetEnemyType());
		}
		//��
		else if (imguieditor->GetEnemyType() == Bird) {
			enemymanager->DeleteEnemyPop(imguieditor->GetEnemyType());
		}
		//�Ǐ]
		else if (imguieditor->GetEnemyType() == Follow) {
			enemymanager->DeleteEnemyPop(imguieditor->GetEnemyType());
		}
		//��
		else if (imguieditor->GetEnemyType() == FakeChest) {
			enemymanager->DeleteEnemyPop(imguieditor->GetEnemyType());
		}
		imguieditor->SetEnemyDelete(false);
	}
	//�Ƃ�(OBJ)
	if (imguieditor->GetDeleteThornObj()) {
		enemymanager->DeleteThornPop();
		imguieditor->SetDeleteThornObj(false);
	}
	//obj�̍폜
	if (imguieditor->GetBackObjDelete()) {
		//��
		if (imguieditor->GetBackObjType() == BackOBJRock) {
			backmanager->DeleteObjPop(imguieditor->GetBackObjType());
		}
		//��
		if (imguieditor->GetBackObjType() == BackOBJBox) {
			backmanager->DeleteObjPop(imguieditor->GetBackObjType());
		}
		//����
		if (imguieditor->GetBackObjType() == BackOBJTorch) {
			backmanager->DeleteObjPop(imguieditor->GetBackObjType());
		}
		imguieditor->SetBackObjDelete(false);
	}
}