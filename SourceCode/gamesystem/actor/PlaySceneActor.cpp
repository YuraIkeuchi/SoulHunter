#include "PlaySceneActor.h"
#include "Audio.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include "imgui.h"
#include "VariableCommon.h"
#include "PlayerSkill.h"
#include "ParticleEmitter.h"
#include "OpenBrowser.h"
//プレイシーンの初期化(現在は魂だけ)
void PlaySceneActor::PlaySceneInitialize() {
	enemymanager->SoulSet(player, block);
}
//初期化
void PlaySceneActor::Initialize(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup)
{
	//最初にnewする
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
	//共通の初期化
	BaseInitialize(dxCommon);
	//プレイヤー初期化
	PlayerInitialize();
	//オーディオ
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
	//プレイシーンの初期化
	PlaySceneInitialize();
	//シーン遷移
	scenechange = new SceneChange();
	scenechange->SetSubStartChange(true);
	//死んだときに暗くなるようのやつ
	BlackFilter = IKESprite::Create(ImageManager::BlackFilter, { 0.0f,0.0f });
	BlackFilter->SetColor(BlackColor);
	BlackFilter->SetSize({ 1280.0f,720.0f });
	//ロード初期化
	StartGame(lightgroup);
	enemymanager->SetPause(pause);
	enemymanager->SetChest(chest);
	backmanager->LoadObjParam(StageNumber, player, lightgroup);
	backmanager->LoadBackObjAlways(StageNumber);
	BGMStart = true;
	//ボスシーンのためのもの
	BossStagObj* bossstagobj_;
	bossstagobj_ = new BossStagObj();
	bossstagobj_->Initialize();
	bossstagobj.reset(bossstagobj_);

	BossSceneChange* bossscenechange_;
	bossscenechange_ = new BossSceneChange();
	bossscenechange.reset(bossscenechange_);

	//プレイモードは敵を動かす
	m_MoveEnemy = true;

	//ポストエフェクトのファイル指定
	postEffect->CreateGraphicsPipeline(L"Resources/Shaders/PostEffectTestVS.hlsl", L"Resources/Shaders/NewToneMapPS.hlsl");

	ParticleEmitter::GetInstance()->AllDelete();

	PlayPostEffect = true;
}
//更新
void PlaySceneActor::Update(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup)
{
	//ボス登場シーンの更新
	if (m_BossNumber == BossApp) {
		BossAppUpdate();
	}
	else if (m_BossNumber == BossEnd) {
		//ボスを倒した後の更新
		BossEndUpdate();
	}
	else {
		//普通の処理の更新
		NormalUpdate();
	}
	//各クラス更新
	AllUpdate(camera);
	//光の配置
	LightSet(lightgroup);
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
	MapInitialize(lightgroup);

	//ゲームのセーブ
	if (save->GetGameSave()) {
		StartStage = StageNumber;
		SaveGame();
		save->SetGameSave(false);
	}

	m_PlayerPos = camera->GetEye();
}
//普通の更新
void PlaySceneActor::NormalUpdate() {
	block->Update(m_PlayerPos);

	//プレイヤーの更新
	if (!pause->GetIsPause() && !chest->GetExplain()) {
		player->Update();
	}
	else {
		player->Pause();
	}
	//設置した敵の更新
	enemymanager->Update(m_MoveEnemy);
	enemymanager->SoulUpdate();
	backmanager->Update();

	tutorialtext->Update();

	//その他の更新
	if (!pause->GetIsPause() && m_BossNumber == BossBattle) {
		respornenemy->Update(firstboss);
	}

	//パーティクル描画
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
//ボス登場の更新
void PlaySceneActor::BossAppUpdate() {
	player->BossAppUpdate(1);
	bossstagobj->AppUpdate();
	firstboss->AppUpdate();
}
//ボス終了の更新
void PlaySceneActor::BossEndUpdate() {
	player->BossEndUpdate(1);
	firstboss->EndUpdate();
	bossstagobj->EndUpdate();
	//パーティクル描画
	ParticleEmitter::GetInstance()->Update();
}
//描画
void PlaySceneActor::Draw(DirectXCommon* dxCommon)
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
//解放
void PlaySceneActor::Finalize()
{
	delete postEffect;
}
//モデルの描画
void PlaySceneActor::ModelDraw(DirectXCommon* dxCommon) {
	if (m_BossNumber == BossApp || m_BossNumber == BossEnd) {
		bossstagobj->BackDraw();
	}

	//ボス登場シーンかどうかで描画を決める
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
//後ろの描画
void PlaySceneActor::BackDraw(DirectXCommon* dxCommon)
{
#pragma endregion
	ModelDraw(dxCommon);
}
//ポストエフェクトがかからない
void PlaySceneActor::FrontDraw(DirectXCommon* dxCommon) {
	//完全に前に書くスプライト
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
//IMGuiの描画
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
//普通の描画
void PlaySceneActor::NormalDraw(DirectXCommon* dxCommon) {
	//画面が黒い間は描画されない
	if (BlackColor.w <= 1.0f) {
		//ステージの描画
		backmanager->AlwaysDraw(dxCommon);
		block->Draw(m_PlayerPos);
		if (StageNumber != BossMap) {
			backmanager->Draw(dxCommon);
		}
		save->Draw();
		//チュートリアル
		tutorialtext->Draw();
		//たからばこ
		chest->Draw();
		//敵の描画
		enemymanager->Draw(dxCommon);
		enemymanager->SoulDraw();
		//ボスの描画
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
	//パーティクル描画
	ParticleEmitter::GetInstance()->FlontDrawAll();
	//プレイヤーの描画
	player->Draw(dxCommon);
	// 3Dオブジェクト描画後処理
	IKEObject3d::PostDraw();

}
//ボス登場シーンの描画
void PlaySceneActor::BossAppDraw(DirectXCommon* dxCommon) {
	firstboss->AppDraw(dxCommon);
	player->BossAppDraw(dxCommon);
	bossstagobj->FrontDraw();
}
//ボス終了シーンの描画
void PlaySceneActor::BossEndDraw(DirectXCommon* dxCommon) {
	firstboss->EndDraw(dxCommon);
	player->BossEndDraw(dxCommon);
	camerawork->EndDraw();
	bossstagobj->FrontDraw();
	ParticleEmitter::GetInstance()->FlontDrawAll();
}
//マップ初期化とそれに合わせた初期化
void PlaySceneActor::MapInitialize(LightGroup* lightgroup) {
	//マップの読み込み
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
//全削除
void PlaySceneActor::AllDelete() {
	enemymanager->DeleteEnemy();
	backmanager->ObjDelete();
	//要素全削除
	player->Finalize();
	ParticleEmitter::GetInstance()->AllDelete();
}
//各クラスの更新
void PlaySceneActor::AllUpdate(DebugCamera* camera) {
	scenechange->Update();
	scenechange->SubBlack(0.05f);
	mapchange->Update();
	mapchange->SubBlack();
	bossscenechange->Update();
	bossscenechange->SubBlack(0.08f);
	camerawork->Update(camera);
}
//ライトの位置
void PlaySceneActor::LightSet(LightGroup* lightgroup) {
	lightgroup->Update();
	///ポイントライト
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
	//丸影
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
//ボス部屋の処理
void PlaySceneActor::BossRoomUpdate() {
	Input* input = Input::GetInstance();
	//ボス部屋の処理
	if (StageNumber == BossMap) {
		Audio::GetInstance()->StopWave(0);
		firstboss->SetAlive(true);
		//ボス登場
		if (m_BossNumber == BossApp) {
			//カメラワークやプレイヤーの挙動
			camerawork->SetCameraType(3);
			firstboss->SetMovie(true);
			player->SetMovie(true);

			//一定フレームでボス戦に入る
			if (bossstagobj->GetAppTimer() == 800) {
				bossscenechange->SetAddStartChange(true);
			}
			//ボタンでも行ける
			if (input->TriggerButton(input->Button_A) && !bossscenechange->GetSubStartChange()) {
				bossscenechange->SetAddStartChange(true);
				bossstagobj->SetEndApp(true);
			}

			//こっからボス戦
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
			//ボスバトル
			////ランダムで敵が出現する
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

			//ボスを倒したあとの処理
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
			//一定フレームでタイトルに戻る
			if (bossstagobj->GetEndTimer() == 670) {
				scenechange->SetAddStartChange(true);
			}
			//ボタンでも行ける
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
//シーン変更など
void PlaySceneActor::ChangeUpdate() {
	//死んだときも戻される
	if (player->DeathMove()) {
		scenechange->SetAddStartChange(true);
	}
	//シーン変更
	if (scenechange->AddBlack(0.05f)) {
		//ImGuiでシーンを切り替えたかどうか
		if (m_SceneChange) {
			m_GameLoad = true;
			StartStage = StageNumber;
			block->ResetBlock();
			minimap->ResetBlock();
			//シーン先を決める
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

	//背景が暗くなるかどうか
	if (!player->GetAlive() && BlackColor.w < 1.0f) {
		BlackColor.w += 0.1f;
	}
	else if (player->GetAlive() && BlackColor.w > 0.0f) {
		BlackColor.w -= 0.1f;
	}
}
//ゴール判定
void PlaySceneActor::GoalHit() {
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
			m_BossNumber = BossApp;
			bossstagobj->SetAppStart(true);
		}
	}
}