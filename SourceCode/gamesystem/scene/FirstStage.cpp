#include "FirstStage.h"
#include "Audio.h"
#include "Input.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include "imgui.h"
#include <Easing.h>
//初期化
void FirstStage::Initialize(DirectXCommon* dxCommon)
{
	//最初にnewする
	player = new Player();
	playerbullet = new PlayerBullet();
	playereffect = new PlayerEffect();
	playerskill = new PlayerSkill();
	skillpause = new SkillPause();
	option = new Option();
	pause = new Pause();
	mapchange = new MapChange();
	message = new Message();
	save = new Save();
	backobjalways = new BackObjAlways();
	backlight = new BackLight();
	chest = new Chest();
	respornenemy = new ResPornEnemy();
	firstboss = new FirstBoss();
	camerawork = new CameraWork();
	hitstop = new HitStop();
	bossappobj = new BossAppObj();
	camerawork->SetCameraType(2);
	dxCommon->SetFullScreen(true);
	//共通の初期化
	BaseInitialize(dxCommon);
	//プレイヤー初期化
	PlayerInitialize();
	// テクスチャ1番に読み込み
	Audio::GetInstance()->LoadSound(0, "Resources/Sound/BGM/ruinsBGM.wav");
	Audio::GetInstance()->LoadSound(1, "Resources/Sound/BGM/Boss.wav");
	//カメラの初期化
	CameraInitialize();
	//ポーズの初期化
	PauseInitialize();
	//敵の初期化
	EnemyInitialize();
	//背景OBJの初期化
	BackObjInitialize();
	//プレイヤーの手助けになるものの初期化
	HelperInitialize();
	//シーン遷移
	scenechange = new SceneChange();
	scenechange->SetSubStartChange(true);
	//ライト
	spotLightDir[0] = 0;
	spotLightDir[1] = 0;
	spotLightDir[2] = 1;
	//死んだときに暗くなるようのやつ
	BlackFilter = IKESprite::Create(ImageManager::BlackFilter, { 0.0f,0.0f });
	BlackFilter->SetColor(BlackColor);
	//ロード初期化
	StartGame();
	LoadEnemyParam(StageNumber);
	LoadObjParam(StageNumber);
	BGMStart = true;

	bossappobj->Initialize();
	bossappchange = new BossAppChange();
}
//更新
void FirstStage::Update(DirectXCommon* dxCommon)
{
	Input* input = Input::GetInstance();
	if (!bossappobj->GetApp()) {
		NormalUpdate();
	}
	
	BossAppUpdate();
	//各クラス更新
	AllUpdate();
	//光の配置
	LightSet();
	//ボスの部屋の処理
	BossRoomUpdate();
	//ゴール判定
	GoalHit();
	//シーンやマップの変更の処理
	ChangeUpdate();
	//BGMスタート
	if (BGMStart == true) {
		Audio::GetInstance()->LoopWave(0, VolumManager::GetInstance()->GetBGMVolum());
		BGMStart = false;
	}
	//音楽の音量が変わる
	Audio::GetInstance()->VolumChange(0, VolumManager::GetInstance()->GetBGMVolum());

	//マップの読み込み
	MapInitialize();
	
	//ゲームのセーブ
	if (save->GetGameSave()) {
		StartStage = StageNumber;
		SaveGame();
		save->SetGameSave(false);
	}
}
//普通の更新
void FirstStage::NormalUpdate() {
	message->Update();
	block->Update(m_PlayerPos);

	//プレイヤーの更新
	if (!pause->GetIsPause() && !chest->GetExplain() && !hitstop->GetHitStop() && !message->GetExplain()) {
		player->Update();
	}
	else {
		player->Pause();
	}
	//プレイヤーの弾の更新
	if (!pause->GetIsPause() && !chest->GetExplain() && !hitstop->GetHitStop() && !message->GetExplain()) {
		playerbullet->Update();
	}
	else {
		playerbullet->Pause();
	}

	//設置した敵の更新
	//普通の敵
	EnemyUpdate(m_Enemys);
	//棘の敵
	EnemyUpdate(m_ThornEnemys);
	//羽の敵
	EnemyUpdate(m_WingEnemys);
	//鳥の敵
	EnemyUpdate(m_BirdEnemys);
	//棘のOBJ
	for (ThornObj* thornobj : m_ThornObjs) {
		if (thornobj != nullptr) {
			if (!pause->GetIsPause() && !chest->GetExplain() && !hitstop->GetHitStop() && !message->GetExplain()) {
				thornobj->Update();
			}
			else {
				thornobj->Pause();
			}
		}
	}
	//柱
	BackObjUpdate(m_BackRocks);
	//岩
	BackObjUpdate(m_BackBoxs);
	//松明
	BackObjUpdate(m_BackTorchs);

	//魂関係
	for (int i = 0; i < Soul_Max; i++) {
		for (int j = 0; j < m_NormalEnemyCount; j++) {
			normalplayersoul[i][j]->Update(m_Enemys[j]);
		}
	}
	for (int i = 0; i < Soul_Max; i++) {
		for (int j = 0; j < m_WingEnemyCount; j++) {
			wingplayersoul[i][j]->Update(m_WingEnemys[j]);
		}
	}

	for (int i = 0; i < Soul_Max; i++) {
		for (int j = 0; j < m_BirdEnemyCount; j++) {
			birdplayersoul[i][j]->Update(m_BirdEnemys[j]);
		}
	}

	for (int i = 0; i < tutorialtext.size(); i++) {
		tutorialtext[i]->Update(i);

	}
	//エフェクトの更新
	if (!pause->GetIsPause() && !chest->GetExplain() && !hitstop->GetHitStop() && !message->GetExplain()) {
		playereffect->Update();
	}
	//その他の更新
	hitstop->Update();
	if (!pause->GetIsPause() && m_BossNumber == BossBattle) {
		respornenemy->Update(firstboss);
	}
	ParticleManager::GetInstance()->Update();
	backobjalways->Update();
	backlight->Update();
	minimap->UseCompass(playerskill);
	minimap->SetMiniPlayerPos(StageNumber);
	pause->Update();
	playerskill->Update();
	chest->Update();
	VolumManager::GetInstance()->Update();
	save->Update();
	BlackFilter->SetColor(BlackColor);
	if (StageNumber == BossMap && !pause->GetIsPause() && !hitstop->GetHitStop()) {
		firstboss->Update();
		ui->Update(firstboss);
	}
	else {
		ui->Update();
	}
}
//ボス部屋の更新
void FirstStage::BossAppUpdate() {
	bossappobj->Update();
}
//描画
void FirstStage::Draw(DirectXCommon* dxCommon)
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
		//FPSManager::GetInstance()->ImGuiDraw();
		//ImGuiDraw(dxCommon);
		camerawork->ImGuiDraw();
		//PostImGuiDraw(dxCommon);
		dxCommon->PostDraw();
	}
	else {
		postEffect->PreDrawScene(dxCommon->GetCmdList());
		postEffect->Draw(dxCommon->GetCmdList());
		postEffect->PostDrawScene(dxCommon->GetCmdList());
		dxCommon->PreDraw();
		//FPSManager::GetInstance()->ImGuiDraw();
		ImGuiDraw(dxCommon);
		camerawork->ImGuiDraw();
		//PostImGuiDraw(dxCommon);
		BackDraw(dxCommon);
		FrontDraw(dxCommon);
		dxCommon->PostDraw();
	}
}
//解放
void FirstStage::Finalize()
{
	delete postEffect;
}
//モデルの描画
void FirstStage::ModelDraw(DirectXCommon* dxCommon) {
}
//後ろの描画
void FirstStage::BackDraw(DirectXCommon* dxCommon)
{
#pragma endregion
	ModelDraw(dxCommon);
}
//ポストエフェクトがかからない
void FirstStage::FrontDraw(DirectXCommon* dxCommon) {
	//ボス登場シーンかどうかで描画を決める
	if (!bossappobj->GetApp()) {
		NormalDraw(dxCommon);
	}
	else {
		BossAppDraw(dxCommon);
	}
	//
	IKESprite::PreDraw();
	mapchange->Draw();
	scenechange->Draw();
	bossappchange->Draw();
	BlackFilter->Draw();
	IKESprite::PostDraw();
}
//IMGuiの描画
void FirstStage::ImGuiDraw(DirectXCommon* dxCommon) {
	{
		int App = camerawork->GetCameraNumber();
		float frame = camerawork->GetFrame();
		ImGui::Begin("GamePlay");
		ImGui::SetWindowPos(ImVec2(1000, 150));
		ImGui::SetWindowSize(ImVec2(280, 150));
		if (ImGui::RadioButton("m_SceneChange", &m_SceneChange)) {
			scenechange->SetAddStartChange(true);
			m_SceneChange = true;
		}
		ImGui::End();
	}
	/*{
		ImGui::Begin("Load");
		ImGui::Text("m_RockNum:%d", m_BackRock_Num);
		ImGui::Text("m_TorchNum:%d", m_BackTorch_Num);
		ImGui::End();
	}*/
}
//普通の描画
void FirstStage::NormalDraw(DirectXCommon* dxCommon) {
	//ステージの描画
	backobjalways->Draw();
	block->Draw(m_PlayerPos);
	if (StageNumber != BossMap) {
		BackObjDraw(m_BackRocks, dxCommon);
		BackObjDraw(m_BackBoxs, dxCommon);
		BackObjDraw(m_BackTorchs, dxCommon);
	}
	backlight->Draw();
	save->Draw();
	//パーティクルの描画
	particleMan->Draw(dxCommon->GetCmdList());
	//チュートリアル
	for (int i = 0; i < tutorialtext.size(); i++) {
		tutorialtext[i]->Draw();
	}
	//たからばこ
	chest->Draw();
	message->Draw();
	//敵の描画
	EnemyDraw(m_Enemys, dxCommon);
	EnemyDraw(m_ThornEnemys, dxCommon);
	EnemyDraw(m_WingEnemys, dxCommon);
	EnemyDraw(m_BirdEnemys, dxCommon);
	//棘のOBJ
	for (ThornObj* thornobj : m_ThornObjs) {
		if (thornobj != nullptr) {
			thornobj->Draw(dxCommon);
		}
	}

	//プレイヤーの描画
	player->Draw(dxCommon);
	playerbullet->Draw(dxCommon);
	playereffect->Draw();

	//ボスの描画
	if (StageNumber == BossMap) {
		firstboss->Draw();
		respornenemy->Draw();
	}

	//魂関係
	for (int i = 0; i < Soul_Max; i++) {
		for (int j = 0; j < m_NormalEnemyCount; j++) {
			normalplayersoul[i][j]->Draw();
		}
	}

	for (int i = 0; i < Soul_Max; i++) {
		for (int j = 0; j < m_WingEnemyCount; j++) {
			wingplayersoul[i][j]->Draw();
		}
	}

	for (int i = 0; i < Soul_Max; i++) {
		for (int j = 0; j < m_BirdEnemyCount; j++) {
			birdplayersoul[i][j]->Draw();
		}
	}

	playerskill->Draw();
	// 3Dオブジェクト描画後処理
	IKEObject3d::PostDraw();

	//完全に前に書くスプライト
	IKESprite::PreDraw();
	ui->Draw();
	pause->Draw();
	chest->ExplainDraw();
	message->ExplainDraw();
	IKESprite::PostDraw();
}
//ボスシーンの描画
void FirstStage::BossAppDraw(DirectXCommon* dxCommon) {
	bossappobj->BackDraw();
}
//マップ初期化とそれに合わせた初期化
void FirstStage::MapInitialize() {
	//マップの読み込み
	if (StageChange) {
		AllDelete();
		switch (StageNumber)
		{
		case Map1:
			block->Initialize(map1,0, StageNumber);
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
			block->Initialize(bossmap,0, StageNumber);
			minimap->InitMap(bossmap, StageNumber);
		case TutoRial:
			block->Initialize(tutorialmap, 0, StageNumber);
			minimap->InitMap(tutorialmap, StageNumber);
		default:
			break;
		}
		player->InitPlayer(StageNumber);
		save->InitSave(StageNumber);
		backobjalways->InitRock(StageNumber);
		LoadEnemyParam(StageNumber);
		for (int i = 0; i < tutorialtext.size(); i++) {
			tutorialtext[i]->InitBoard(StageNumber, i);
		}
		message->InitMessage(StageNumber);
		chest->InitChest(StageNumber);
		LoadObjParam(StageNumber);
		StageChange = false;
		player->SetGoalDir(0);
	}
}
//全削除
void FirstStage::AllDelete() {
	//要素全削除
	EnemyFinalize(m_Enemys);
	EnemyFinalize(m_ThornEnemys);
	EnemyFinalize(m_WingEnemys);
	EnemyFinalize(m_BirdEnemys);
	player->Finalize();
	m_Enemys.clear();
	m_ThornEnemys.clear();
	m_WingEnemys.clear();
	m_BirdEnemys.clear();
	m_ThornObjs.clear();
	m_BackRocks.clear();
	m_BackBoxs.clear();
	m_NormalEnemyCount = 0;
	m_ThornObjCount = 0;
	m_WingEnemyCount = 0;
	m_EnemyCount = 0;
	m_BackObjCount = 0;
}
//各クラスの更新
void FirstStage::AllUpdate() {
	lightGroup->Update();
	scenechange->Update();
	scenechange->SubBlack(0.05f);
	mapchange->Update();
	mapchange->SubBlack();
	bossappchange->Update();
	bossappchange->SubBlack(0.005f);
	camerawork->Update(camera);
}
//ライトの位置
void FirstStage::LightSet() {
	m_PlayerPos = camera->GetEye();
	///ポイントライト
	lightGroup->SetPointLightPos(0, XMFLOAT3(player->GetPosition().x, player->GetPosition().y, player->GetPosition().z - 5.0f));
	lightGroup->SetPointLightColor(0, XMFLOAT3(pointLightColor));
	lightGroup->SetPointLightAtten(0, XMFLOAT3(pointLightAtten));

	lightGroup->SetPointLightPos(1, XMFLOAT3(save->GetPosition().x, save->GetPosition().y + 2.0f, save->GetPosition().z + 2.0f));
	lightGroup->SetPointLightColor(1, XMFLOAT3(pointLightColor));
	lightGroup->SetPointLightAtten(1, XMFLOAT3(pointLightAtten));

	for (BackObjCommon* torch : m_BackTorchs) {
		for (int i = 0; i < m_BackTorch_Num; i++) {
			if (torch != nullptr) {
				lightGroup->SetPointLightPos(i + 2, XMFLOAT3({ m_BackTorchs[i]->GetPosition().x, m_BackTorchs[i]->GetPosition().y + 3.0f, m_BackTorchs[i]->GetPosition().z + 3.0f }));
				lightGroup->SetPointLightColor(i + 2, XMFLOAT3(pointLightColor));
				lightGroup->SetPointLightAtten(i + 2, XMFLOAT3(pointLightAtten));
			}
		}
	}

	//丸影
	lightGroup->SetCircleShadowDir(0, XMVECTOR({ circleShadowDir[0], circleShadowDir[1], circleShadowDir[2], 0 }));
	lightGroup->SetCircleShadowCasterPos(0, XMFLOAT3({ player->GetPosition().x, player->GetPosition().y, player->GetPosition().z }));
	lightGroup->SetCircleShadowAtten(0, XMFLOAT3(circleShadowAtten));
	lightGroup->SetCircleShadowFactorAngle(0, XMFLOAT2(circleShadowFactorAngle));

	for (InterEnemy* enemy : m_Enemys) {
		for (int i = 0; i < m_Enemy_Num; i++) {
			if (enemy != nullptr) {
				lightGroup->SetCircleShadowDir(i + 2, XMVECTOR({ circleShadowDir[0], circleShadowDir[1], circleShadowDir[2], 0 }));
				lightGroup->SetCircleShadowCasterPos(i + 2, XMFLOAT3({ m_Enemys[i]->GetPosition().x, m_Enemys[i]->GetPosition().y, m_Enemys[i]->GetPosition().z }));
				lightGroup->SetCircleShadowAtten(i + 2, XMFLOAT3(circleShadowAtten));
				lightGroup->SetCircleShadowFactorAngle(i + 2, XMFLOAT2(circleShadowFactorAngle));
			}
		}
	}

	for (InterEnemy* enemy : m_ThornEnemys) {
		for (int i = 0; i < m_ThornEnemy_Num; i++) {
			if (enemy != nullptr) {
				lightGroup->SetCircleShadowDir(i + m_Enemy_Num, XMVECTOR({ circleShadowDir[0], circleShadowDir[1], circleShadowDir[2], 0 }));
				lightGroup->SetCircleShadowCasterPos(i + m_Enemy_Num, XMFLOAT3({ m_ThornEnemys[i]->GetPosition().x,  m_ThornEnemys[i]->GetPosition().y,  m_ThornEnemys[i]->GetPosition().z }));
				lightGroup->SetCircleShadowAtten(i + m_Enemy_Num, XMFLOAT3(circleShadowAtten));
				lightGroup->SetCircleShadowFactorAngle(i + m_Enemy_Num, XMFLOAT2(circleShadowFactorAngle));
			}
		}
	}

	for (InterEnemy* enemy : m_WingEnemys) {
		for (int i = 0; i < m_WingEnemy_Num; i++) {
			if (enemy != nullptr) {
				lightGroup->SetCircleShadowDir(i + (m_Enemy_Num + m_ThornEnemy_Num), XMVECTOR({ circleShadowDir[0], circleShadowDir[1], circleShadowDir[2], 0 }));
				lightGroup->SetCircleShadowCasterPos(i + (m_Enemy_Num + m_ThornEnemy_Num), XMFLOAT3({ m_WingEnemys[i]->GetPosition().x,  m_WingEnemys[i]->GetPosition().y,  m_WingEnemys[i]->GetPosition().z }));
				lightGroup->SetCircleShadowAtten(i + (m_Enemy_Num + m_ThornEnemy_Num), XMFLOAT3(circleShadowAtten));
				lightGroup->SetCircleShadowFactorAngle(i + (m_Enemy_Num + m_ThornEnemy_Num), XMFLOAT2(circleShadowFactorAngle));
			}
		}
	}

	for (InterEnemy* enemy : m_BirdEnemys) {
		for (int i = 0; i < m_BirdEnemy_Num; i++) {
			if (enemy != nullptr) {
				lightGroup->SetCircleShadowDir(i + (m_Enemy_Num + m_ThornEnemy_Num + m_WingEnemy_Num), XMVECTOR({ circleShadowDir[0], circleShadowDir[1], circleShadowDir[2], 0 }));
				lightGroup->SetCircleShadowCasterPos(i + (m_Enemy_Num + m_ThornEnemy_Num + m_WingEnemy_Num), XMFLOAT3({ m_BirdEnemys[i]->GetPosition().x, m_BirdEnemys[i]->GetPosition().y,  m_BirdEnemys[i]->GetPosition().z }));
				lightGroup->SetCircleShadowAtten(i + (m_Enemy_Num + m_ThornEnemy_Num + m_WingEnemy_Num), XMFLOAT3(circleShadowAtten));
				lightGroup->SetCircleShadowFactorAngle(i + (m_Enemy_Num + m_ThornEnemy_Num + m_WingEnemy_Num), XMFLOAT2(circleShadowFactorAngle));
			}
		}
	}

	if (StageNumber == BossMap) {
		lightGroup->SetCircleShadowDir((m_Enemy_Num + m_ThornEnemy_Num + m_WingEnemy_Num + m_BirdEnemy_Num) + 1, XMVECTOR({ circleShadowDir[0], circleShadowDir[1], circleShadowDir[2], 0 }));
		lightGroup->SetCircleShadowCasterPos((m_Enemy_Num + m_ThornEnemy_Num + m_WingEnemy_Num + m_BirdEnemy_Num) + 1, XMFLOAT3({ firstboss->GetPosition().x, firstboss->GetPosition().y, firstboss->GetPosition().z }));
		lightGroup->SetCircleShadowAtten((m_Enemy_Num + m_ThornEnemy_Num + m_WingEnemy_Num + m_BirdEnemy_Num) + 1,XMFLOAT3(circleShadowAtten));
		lightGroup->SetCircleShadowFactorAngle((m_Enemy_Num + m_ThornEnemy_Num + m_WingEnemy_Num + m_BirdEnemy_Num) + 1,XMFLOAT2(circleShadowFactorAngle));
	}
}
//ボス部屋の処理
void FirstStage::BossRoomUpdate() {
	//ボス部屋の処理
	if (StageNumber == BossMap) {

		firstboss->SetAlive(true);
		//ボス登場
		if (bossappobj->GetApp()) {
			if (bossappobj->GetAppTimer() == 400) {
				bossappchange->SetAddStartChange(true);
			}
			if (bossappchange->AddBlack(0.005f)) {
				bossappchange->SetSubStartChange(true);
				bossappobj->SetApp(false);
			}
			camerawork->SetCameraType(3);
			firstboss->SetMovie(true);
			player->SetMovie(true);
			if (camerawork->GetEndApp()) {
				Audio::GetInstance()->LoopWave(1, VolumManager::GetInstance()->GetBGMVolum());
				firstboss->SetMovie(false);
				m_BossNumber = BossBattle;
				player->SetMovie(false);
			}
		}
		else {
			//ボスバトル
			if (firstboss->GetDeathTimer() > 200) {
				scenechange->SetAddStartChange(true);
			}
			if (respornenemy->GetEnemyArgment()) {
				InterEnemy* newEnemy;
				newEnemy = new Enemy();
				newEnemy->Initialize();
				newEnemy->SetPlayer(player);
				newEnemy->SetBlock(block);
				newEnemy->SetPlayerBullet(playerbullet);
				newEnemy->SetPlayerEffect(playereffect);
				newEnemy->SetPosition(respornenemy->GetResPornPosition());
				m_Enemys.push_back(newEnemy);
				m_NormalEnemyCount++;
				respornenemy->SetEnemyArgment(false);
			}
			camerawork->SetCameraType(2);
		}
	}
	else {
		camerawork->SetCameraType(2);
		firstboss->SetAlive(false);
	}
}
//シーン変更など
void FirstStage::ChangeUpdate() {

	//死んだときも戻される
	if (player->GetHP() < 1) {
		scenechange->SetAddStartChange(true);
	}

	//シーン変更
	if (scenechange->AddBlack(0.05f)) {
		//エディタシーンへ変更
		if (m_SceneChange) {
			m_GameLoad = true;
			StartStage = StageNumber;
			block->ResetBlock();
			minimap->ResetBlock();
			SaveGame();
			SceneManager::GetInstance()->ChangeScene("EDITORSCENE");
			m_SceneChange = false;
		}
		else {
			block->ResetBlock();
			minimap->ResetBlock();
			Audio::GetInstance()->StopWave(0);
			Audio::GetInstance()->StopWave(1);
			if (player->GetHP() < 1) {
				SceneManager::GetInstance()->ChangeScene("GAMEOVER");
				m_GameLoop = true;
			}
			else {
				SceneManager::GetInstance()->ChangeScene("TITLE");
				m_GameLoop = true;
			}
		}
	}

	//背景が暗くなるかどうか
	if (!player->GetAlive() && BlackColor.w < 1.0f) {
		BlackColor.w += 0.1f;
	}
	else if (player->GetAlive() && BlackColor.w > 0.0f) {
		BlackColor.w -= 0.1f;
	}
}
//ゴール判定
void FirstStage::GoalHit() {
	//ゴール判定
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
				Audio::GetInstance()->StopWave(0);
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

	//マップ変更
	if (mapchange->AddBlack()) {
		StageChange = true;
		block->ResetBlock();
		minimap->ResetBlock();
		mapchange->SetSubStartChange(true);
		if (StageNumber == BossMap) {
			bossappobj->SetAppStart(true);
		}
	}
}