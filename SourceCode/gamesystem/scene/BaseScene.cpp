#include "BaseScene.h"
#include "CollisionManager.h"
Block* BaseScene::block = nullptr;
MiniMap* BaseScene::minimap = nullptr;
//Pause* BaseScene::pause = nullptr;
bool BaseScene::m_GameLoad = false;
bool BaseScene::m_GameLoop = false;
bool BaseScene::s_New = false;
//Newするを一回にしたい
void BaseScene::NewFinish() {
	s_New = true;
}
//共通の初期化
void BaseScene::BaseInitialize(DirectXCommon* dxCommon) {
	// デバイスをセット
	IKEFBXObject3d::SetDevice(dxCommon->GetDev());

	// グラフィックスパイプライン生成
	IKEFBXObject3d::CreateGraphicsPipeline();
	//パ^ティクルマネージャー
	particleMan = ParticleManager::GetInstance();
	// カメラ生成
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height);
	IKETexture::SetCamera(camera);
	// 3Dオブジェクトにカメラをセット
	IKEObject3d::SetCamera(camera);
	particleMan->SetCamera(camera);
	IKEFBXObject3d::SetCamera(camera);
	//ポストエフェクトの初期化
	//(普通)
	postEffect = new PostEffect();
	postEffect->Initialize();
	postEffect->CreateGraphicsPipeline(L"Resources/Shaders/PostEffectTestVS.hlsl", L"Resources/Shaders/SepiaPS.hlsl");

	// ライト生成
	lightGroup = LightGroup::Create();
	// 3Dオブエクトにライトをセット
	IKEObject3d::SetLightGroup(lightGroup);
	// パーティクルマネージャ生成

	//BirthParticle();
	ParticleManager::GetInstance()->Update();

	//丸影のためのやつ
	lightGroup->SetDirLightActive(0, false);
	lightGroup->SetDirLightActive(1, false);
	lightGroup->SetDirLightActive(2, false);
	lightGroup->SetPointLightActive(0, true);
	lightGroup->SetPointLightActive(1, true);
	lightGroup->SetCircleShadowActive(0, true);
}
//プレイヤー関係の初期化
void BaseScene::PlayerInitialize() {
	//プレイヤー
	player->Initialize();
	player->StateInitialize();
	player->SetBlock(block);
	
	//スキル配置
	playerskill = new PlayerSkill();
	playerskill->Initialize();
	playerskill->SetPlayer(player);
}
//カメラの初期化
void BaseScene::CameraInitialize() {
	//カメラの動き
	camerawork->SetPlayer(player);
	camerawork->SetInterBoss(firstboss);
}
//エネミーの初期化
void BaseScene::EnemyInitialize() {
	//ボス
	firstboss->SetPlayer(player);
	firstboss->SetPause(pause);
	firstboss->Initialize();

	//リスポーン関係(敵)
	respornenemy->Initialize();

}
//ポーズの初期化
void BaseScene::PauseInitialize() {
	//ポーズメニュー
	//スキルセット
	skillpause->SetPlayer(player);
	skillpause->SetPlayerSkill(playerskill);
	skillpause->Initialize();
	//skillpause->InitPos();
	//ミニマップ
	minimap->Initialize();
	minimap->SetPlayer(player);
	minimap->SetSave(save);
	//オプション
	option->Initialize();
	pause->SetSkillPause(skillpause);
	pause->SetMiniMap(minimap);
	pause->SetOption(option);
	pause->SetPlayer(player);
	pause->Initialize();
}
//プレイヤーの手助けになるものの初期化
void BaseScene::HelperInitialize() {
	//UI
	ui = new UI(player, firstboss);
	ui->SetPlayerSkill(playerskill);
	//チュートリアル
	for (int i = 0; i < tutorialtext.size(); i++) {
		tutorialtext[i] = new TutorialText();
		tutorialtext[i]->SetPlayer(player);
	}
	//セーブ関係
	save->Initialize();
	save->SetPlayer(player);
}
//背景OBJの初期化
void BaseScene::BackObjInitialize() {
	//宝箱
	chest->SetPlayer(player);
	chest->SetPlayerSkill(playerskill);
	//背景obj
	backobjalways->Initialize();
	backlight->Initialize();
}
//ゲームの始まり
void BaseScene::StartGame() {
	//最初からにした場合
	if (!m_GameLoad) {
		skillpause->InitPos();
		StageNumber = TutoRial;
		block->Initialize(tutorialmap, 0, StageNumber);
		minimap->InitMap(tutorialmap, StageNumber);
		playerskill->ResetSkill();
		skillpause->ResetSkillPause();
		player->ResetSkill();
		LoadEnemyParam(TutoRial);
		LoadObjParam(TutoRial);
	}
	//ロードした場合
	else {
		LoadGame();
		StageNumber = StartStage;
		player->LoadPlayer(m_PlayerStartPos);
		save->InitSave(StageNumber);
		chest->InitChest(StageNumber);
		if (StageNumber == TutoRial) {
			block->Initialize(tutorialmap, 0, StageNumber);
			minimap->InitMap(tutorialmap, StageNumber);
		}
		else if (StageNumber == Map1) {
			block->Initialize(map1, 0, StageNumber);
			minimap->InitMap(map1, StageNumber);
		}
		else if (StageNumber == Map3) {
			block->Initialize(map3, 0, StageNumber);
			minimap->InitMap(map3, StageNumber);
		}
		else if (StageNumber == Map5) {
			block->Initialize(map5, 0, StageNumber);
			minimap->InitMap(map5, StageNumber);
		}
	}
}
//CSVを開いている
void BaseScene::OpenEnemyParam(const int& StageNumber) {
	switch (StageNumber)
	{
	case Map1:
		m_EnemyFile.open("Resources/enemy_param/NormalEnemy/FirstMapEnemy.csv");
		m_ThornEnemyFile.open("Resources/enemy_param/ThornEnemy/FirstMapThornEnemy.csv");
		m_BoundEnemyFile.open("Resources/enemy_param/BoundEnemy/FirstMapBoundEnemy.csv");
		m_BirdEnemyFile.open("Resources/enemy_param/BirdEnemy/FirstMapBirdEnemy.csv");
		m_ThornObjFile.open("Resources/enemy_param/ThornObj/FirstMapThornObj.csv");
	case Map2:
		m_EnemyFile.open("Resources/enemy_param/NormalEnemy/SecondMapEnemy.csv");
		m_ThornEnemyFile.open("Resources/enemy_param/ThornEnemy/SecondMapThornEnemy.csv");
		m_BoundEnemyFile.open("Resources/enemy_param/BoundEnemy/SecondMapBoundEnemy.csv");
		m_BirdEnemyFile.open("Resources/enemy_param/BirdEnemy/SecondMapBirdEnemy.csv");
		m_ThornObjFile.open("Resources/enemy_param/ThornObj/SecondMapThornObj.csv");
	case Map3:
		m_EnemyFile.open("Resources/enemy_param/NormalEnemy/ThirdMapEnemy.csv");
		m_ThornEnemyFile.open("Resources/enemy_param/ThornEnemy/ThirdMapThornEnemy.csv");
		m_BoundEnemyFile.open("Resources/enemy_param/BoundEnemy/ThirdMapBoundEnemy.csv");
		m_BirdEnemyFile.open("Resources/enemy_param/BirdEnemy/ThridMapBirdEnemy.csv");
		m_ThornObjFile.open("Resources/enemy_param/ThornObj/ThirdMapThornObj.csv");
	case Map4:
		m_EnemyFile.open("Resources/enemy_param/NormalEnemy/FourthMapEnemy.csv");
		m_ThornEnemyFile.open("Resources/enemy_param/ThornEnemy/FourthMapThornEnemy.csv");
		m_BoundEnemyFile.open("Resources/enemy_param/BoundEnemy/FourthMapBoundEnemy.csv");
		m_BirdEnemyFile.open("Resources/enemy_param/BirdEnemy/FourthMapBirdEnemy.csv");
		m_ThornObjFile.open("Resources/enemy_param/ThornObj/FourthMapThornObj.csv");
	case Map5:
		m_EnemyFile.open("Resources/enemy_param/NormalEnemy/FifthMapEnemy.csv");
		m_ThornEnemyFile.open("Resources/enemy_param/ThornEnemy/FifthMapThornEnemy.csv");
		m_BoundEnemyFile.open("Resources/enemy_param/BoundEnemy/FifthMapBoundEnemy.csv");
		m_BirdEnemyFile.open("Resources/enemy_param/BirdEnemy/FifthMapBirdEnemy.csv");
		m_ThornObjFile.open("Resources/enemy_param/ThornObj/FifthMapThornObj.csv");
	case Map6:
		m_EnemyFile.open("Resources/enemy_param/NormalEnemy/SixMapEnemy.csv");
		m_ThornEnemyFile.open("Resources/enemy_param/ThornEnemy/SixMapThornEnemy.csv");
		m_BoundEnemyFile.open("Resources/enemy_param/BoundEnemy/SixMapBoundEnemy.csv");
		m_BirdEnemyFile.open("Resources/enemy_param/BirdEnemy/SixMapBirdEnemy.csv");
		m_ThornObjFile.open("Resources/enemy_param/ThornObj/SixMapThornObj.csv");
	case BossMap:
		m_EnemyFile.open("Resources/enemy_param/NormalEnemy/BossMapEnemy.csv");
	case TutoRial:
		m_EnemyFile.open("Resources/enemy_param/NormalEnemy/TutorialEnemy.csv");
		m_ThornEnemyFile.open("Resources/enemy_param/ThornEnemy/TutorialThornEnemy.csv");
		m_BoundEnemyFile.open("Resources/enemy_param/BoundEnemy/TutorialBoundEnemy.csv");
		m_BirdEnemyFile.open("Resources/enemy_param/BirdEnemy/TutorialBirdEnemy.csv");
		m_ThornObjFile.open("Resources/enemy_param/ThornObj/TutorialMapThornObj.csv");
	default:
		break;
	}
	m_EnemyPopcom << m_EnemyFile.rdbuf();
	m_ThornEnemyPopcom << m_ThornEnemyFile.rdbuf();
	m_BoundEnemyPopcom << m_BoundEnemyFile.rdbuf();
	m_BirdEnemyPopcom << m_BirdEnemyFile.rdbuf();
	m_ThornObjPopcom << m_ThornObjFile.rdbuf();

	m_EnemyFile.close();
	m_ThornEnemyFile.close();
	m_BoundEnemyFile.close();
	m_BirdEnemyFile.close();
	m_ThornObjFile.close();
}
//CSV指定(普通の敵)
void BaseScene::NormalEnemySpecity(const char* vsShaderName) {
	//普通の敵
	std::ofstream normalofs(vsShaderName);  // ファイルパスを指定する
	normalofs << "Enemy_Quantity" << "," << m_Enemys.size() << std::endl;

	for (int i = 0; i < m_Enemys.size(); i++) {
		normalofs << "Wait" << "," << 120 << std::endl;
		normalofs << "POP" << "," << m_Enemys[i]->GetStartPos().x
			<< "," << m_Enemys[i]->GetPosition().y
			<< "," << m_Enemys[i]->GetStartPos().z << std::endl;

	}
	m_EnemyPosition.resize(m_Enemys.size());
}
//棘の敵
void BaseScene::ThornEnemySpecity(const char* vsShaderName) {
	//棘の敵
	std::ofstream thornofs(vsShaderName);  // ファイルパスを指定する
	thornofs << "Enemy_Quantity2" << "," << m_ThornEnemys.size() << std::endl;

	for (int i = 0; i < m_ThornEnemys.size(); i++) {
		thornofs << "Wait" << "," << 120 << std::endl;
		thornofs << "ANGLE" << "," << m_ThornEnemys[i]->GetAngle() << std::endl;
		thornofs << "POSY" << "," << m_ThornEnemys[i]->GetThornPos() << std::endl;
		thornofs << "POP" << "," << m_ThornEnemys[i]->GetPosition().x
			<< "," << m_ThornEnemys[i]->GetPosition().y
			<< "," << m_ThornEnemys[i]->GetPosition().z << std::endl;

	}
	m_ThornEnemyPosition.resize(m_ThornEnemys.size());
}
//羽の敵
void BaseScene::BoundEnemySpecity(const char* vsShaderName) {
	std::ofstream birdofs(vsShaderName);  // ファイルパスを指定する
	birdofs << "Enemy_Quantity" << "," << m_BoundEnemys.size() << std::endl;

	for (int i = 0; i < m_BoundEnemys.size(); i++) {
		birdofs << "Wait" << "," << 120 << std::endl;
		birdofs << "POP" << "," << m_BoundEnemys[i]->GetStartPos().x
			<< "," << m_BoundEnemys[i]->GetStartPos().y
			<< "," << m_BoundEnemys[i]->GetStartPos().z << std::endl;

	}
	m_BoundEnemyPosition.resize(m_BoundEnemys.size());
}
//鳥の敵
void BaseScene::BirdEnemySpecity(const char* vsShaderName) {
	std::ofstream birdofs(vsShaderName);  // ファイルパスを指定する
	birdofs << "Enemy_Quantity" << "," << m_BirdEnemys.size() << std::endl;

	for (int i = 0; i < m_BirdEnemys.size(); i++) {
		birdofs << "Wait" << "," << 120 << std::endl;
		birdofs << "POP" << "," << m_BirdEnemys[i]->GetStartPos().x
			<< "," << m_BirdEnemys[i]->GetStartPos().y
			<< "," << m_BirdEnemys[i]->GetStartPos().z << std::endl;

	}
	m_BirdEnemyPosition.resize(m_BirdEnemys.size());
}
//棘のOBJ
void BaseScene::ThornObjSpecity(const char* vsShaderName) {
	std::ofstream thornobjofs(vsShaderName);  // ファイルパスを指定する
	thornobjofs << "Enemy_Quantity2" << "," << m_ThornObjs.size() << std::endl;

	for (int i = 0; i < m_ThornObjs.size(); i++) {
		thornobjofs << "Wait" << "," << 120 << std::endl;
		thornobjofs << "Dir" << "," << m_ThornObjs[i]->GetDir() << std::endl;
		thornobjofs << "Target" << "," << m_ThornObjs[i]->GetTargetTimer() << std::endl;
		thornobjofs << "StartPos" << "," << m_ThornObjs[i]->GetThornPos().x << "," << m_ThornObjs[i]->GetThornPos().y
			<< "," << m_ThornObjs[i]->GetThornPos().z << std::endl;
	}
	m_ThornObjPosition.resize(m_ThornObjs.size());
}
//CSVに書き込んでいる
void BaseScene::SaveEnemyParam(const int& StageNumber) {
	//マップ1
	if (StageNumber == Map1) {
		//普通の敵
		NormalEnemySpecity("Resources/enemy_param/NormalEnemy/FirstMapEnemy.csv");  // ファイルパスを指定する
		//棘の敵
		ThornEnemySpecity("Resources/enemy_param/ThornEnemy/FirstMapThornEnemy.csv");  // ファイルパスを指定する
		//羽の敵
		BoundEnemySpecity("Resources/enemy_param/BoundEnemy/FirstMapBoundEnemy.csv");  // ファイルパスを指定する
		//鳥の敵
		BirdEnemySpecity("Resources/enemy_param/BirdEnemy/FirstMapBirdEnemy.csv");  // ファイルパスを指定する
		//棘のOBJ
		ThornObjSpecity("Resources/enemy_param/ThornObj/FirstMapThornObj.csv");  // ファイルパスを指定する
	}
	//マップ2
	else if (StageNumber == Map2) {
		//普通の敵
		NormalEnemySpecity("Resources/enemy_param/NormalEnemy/SecondMapEnemy.csv");  // ファイルパスを指定する
		//棘の敵
		ThornEnemySpecity("Resources/enemy_param/ThornEnemy/SecondMapThornEnemy.csv");  // ファイルパスを指定する
		//羽の敵
		BoundEnemySpecity("Resources/enemy_param/BoundEnemy/SecondMapBoundEnemy.csv");  // ファイルパスを指定する
		//鳥の敵
		BirdEnemySpecity("Resources/enemy_param/BirdEnemy/SecondMapBirdEnemy.csv");  // ファイルパスを指定する
		//棘のOBJ
		ThornObjSpecity("Resources/enemy_param/ThornObj/SecondMapThornObj.csv");  // ファイルパスを指定する
	}
	//マップ3
	else if (StageNumber == Map3) {
		//普通の敵
		NormalEnemySpecity("Resources/enemy_param/NormalEnemy/ThirdMapEnemy.csv");  // ファイルパスを指定する
		//棘の敵
		ThornEnemySpecity("Resources/enemy_param/ThornEnemy/ThirdMapThornEnemy.csv");  // ファイルパスを指定する
		//羽の敵
		BoundEnemySpecity("Resources/enemy_param/BoundEnemy/ThirdMapBoundEnemy.csv");  // ファイルパスを指定する
		//鳥の敵
		BirdEnemySpecity("Resources/enemy_param/BirdEnemy/ThirdMapBirdEnemy.csv");  // ファイルパスを指定する
		//棘のOBJ
		ThornObjSpecity("Resources/enemy_param/ThornObj/ThirdMapThornObj.csv");  // ファイルパスを指定する
	}
	//マップ4
	else if (StageNumber == Map4) {
		//普通の敵
		NormalEnemySpecity("Resources/enemy_param/NormalEnemy/FourthMapEnemy.csv");  // ファイルパスを指定する
		//棘の敵
		ThornEnemySpecity("Resources/enemy_param/ThornEnemy/FourthMapThornEnemy.csv");  // ファイルパスを指定する
		//羽の敵
		BoundEnemySpecity("Resources/enemy_param/BoundEnemy/FourthMapBoundEnemy.csv");  // ファイルパスを指定する
		//鳥の敵
		BirdEnemySpecity("Resources/enemy_param/BirdEnemy/FourthMapBirdEnemy.csv");  // ファイルパスを指定する
		//棘のOBJ
		ThornObjSpecity("Resources/enemy_param/ThornObj/FourthMapThornObj.csv");  // ファイルパスを指定する
	}
	//マップ5
	else if (StageNumber == Map5) {
		//普通の敵
		NormalEnemySpecity("Resources/enemy_param/NormalEnemy/FifthMapEnemy.csv");  // ファイルパスを指定する
		//棘の敵
		ThornEnemySpecity("Resources/enemy_param/ThornEnemy/FifthMapThornEnemy.csv");  // ファイルパスを指定する
		//羽の敵
		BoundEnemySpecity("Resources/enemy_param/BoundEnemy/FifthMapBoundEnemy.csv");  // ファイルパスを指定する
		//鳥の敵
		BirdEnemySpecity("Resources/enemy_param/BirdEnemy/FifthMapBirdEnemy.csv");  // ファイルパスを指定する
		//棘のOBJ
		ThornObjSpecity("Resources/enemy_param/ThornObj/FifthMapThornObj.csv");  // ファイルパスを指定する
	}
	//マップ6
	else if (StageNumber == Map6) {
		//普通の敵
		NormalEnemySpecity("Resources/enemy_param/NormalEnemy/SixMapEnemy.csv");  // ファイルパスを指定する
		//棘の敵
		ThornEnemySpecity("Resources/enemy_param/ThornEnemy/SixMapThornEnemy.csv");  // ファイルパスを指定する
		//羽の敵
		BoundEnemySpecity("Resources/enemy_param/BoundEnemy/SixMapBoundEnemy.csv");  // ファイルパスを指定する
		//鳥の敵
		BirdEnemySpecity("Resources/enemy_param/BirdEnemy/SixMapBirdEnemy.csv");  // ファイルパスを指定する
		//棘のOBJ
		ThornObjSpecity("Resources/enemy_param/ThornObj/SixMapThornObj.csv");  // ファイルパスを指定する
	}
	else if (StageNumber == TutoRial) {
		//普通の敵
		NormalEnemySpecity("Resources/enemy_param/NormalEnemy/TutorialEnemy.csv");  // ファイルパスを指定する
		//棘の敵
		ThornEnemySpecity("Resources/enemy_param/ThornEnemy/TutorialThornEnemy.csv");  // ファイルパスを指定する
		//棘の敵
		BoundEnemySpecity("Resources/enemy_param/BoundEnemy/TutorialBoundEnemy.csv");  // ファイルパスを指定する
		//鳥の敵
		BirdEnemySpecity("Resources/enemy_param/BirdEnemy/TutorialBirdEnemy.csv");  // ファイルパスを指定する
		//棘のOBJ
		ThornObjSpecity("Resources/enemy_param/ThornObj/TutorialMapThornObj.csv");  // ファイルパスを指定する
	}
}
//CSVから値を読み込んでいる(敵)
void BaseScene::LoadEnemyParam(const int& StageNumber) {
	OpenEnemyParam(StageNumber);
	//普通の敵
	while (std::getline(m_EnemyPopcom, m_EnemyLine)) {
		std::istringstream line_stream(m_EnemyLine);
		std::string word;
		std::getline(line_stream, word, ',');

		if (word.find("//") == 0) {
			continue;
		}
		if (word.find("Enemy_Quantity") == 0) {
			std::getline(line_stream, word, ',');
			int quantity = (int)std::atof(word.c_str());
			m_Enemy_Num = quantity;
			m_NormalEnemyCount = m_Enemy_Num;
			break;
		}
	}
	m_EnemyStartPos.resize(m_Enemy_Num);
	for (int i = 0; i < m_Enemy_Num; i++) {
		while (std::getline(m_EnemyPopcom, m_EnemyLine)) {
			std::istringstream line_stream(m_EnemyLine);
			std::string word;
			std::getline(line_stream, word, ',');

			if (word.find("//") == 0) {
				continue;
			}
			if (word.find("Number") == 0) {
				std::getline(line_stream, word, ',');
				int number = (int)std::atof(word.c_str());
			}
			else if (word.find("POP") == 0) {
				std::getline(line_stream, word, ',');
				float x = (float)std::atof(word.c_str());

				std::getline(line_stream, word, ',');
				float y = (float)std::atof(word.c_str());

				std::getline(line_stream, word, ',');
				float z = (float)std::atof(word.c_str());

				m_EnemyStartPos[i] = { x,y,z };
				break;
			}
		}
	}
	m_Enemys.resize(m_Enemy_Num);

	for (int i = 0; i < m_Enemy_Num; i++) {
		m_Enemys[i] = new Enemy();
		m_Enemys[i]->Initialize();
		m_Enemys[i]->SetPlayer(player);
		m_Enemys[i]->SetBlock(block);
		m_Enemys[i]->SetHitStop(hitstop);
		m_Enemys[i]->SetPosition(m_EnemyStartPos[i]);
		m_Enemys[i]->SetStartPos(m_EnemyStartPos[i]);
		lightGroup->SetCircleShadowActive(i + 2, true);
	}

	//棘モンスター
	while (std::getline(m_ThornEnemyPopcom, m_ThornEnemyLine)) {
		std::istringstream line_stream(m_ThornEnemyLine);
		std::string word;
		std::getline(line_stream, word, ',');

		if (word.find("//") == 0) {
			continue;
		}
		if (word.find("Enemy_Quantity2") == 0) {
			std::getline(line_stream, word, ',');
			int quantity2 = (int)std::atof(word.c_str());
			m_ThornEnemy_Num = quantity2;
			break;
		}
	}
	m_ThornEnemyStartPos.resize(m_ThornEnemy_Num);
	m_EnemyAngle.resize(m_ThornEnemy_Num);
	m_SetThornEnemyPosY.resize(m_ThornEnemy_Num);
	for (int i = 0; i < m_ThornEnemy_Num; i++) {
		while (std::getline(m_ThornEnemyPopcom, m_ThornEnemyLine)) {
			std::istringstream line_stream(m_ThornEnemyLine);
			std::string word;
			std::getline(line_stream, word, ',');

			if (word.find("//") == 0) {
				continue;
			}
			if (word.find("ANGLE") == 0) {
				std::getline(line_stream, word, ',');
				float angle = (float)std::atof(word.c_str());
				m_EnemyAngle[i] = angle;
			}
			else if (word.find("POSY") == 0) {
				std::getline(line_stream, word, ',');
				float posy = (float)std::atof(word.c_str());
				m_SetThornEnemyPosY[i] = posy;
			}
			else if (word.find("POP") == 0) {
				std::getline(line_stream, word, ',');
				float x = (float)std::atof(word.c_str());

				std::getline(line_stream, word, ',');
				float y = (float)std::atof(word.c_str());

				std::getline(line_stream, word, ',');
				float z = (float)std::atof(word.c_str());

				m_ThornEnemyStartPos[i] = { x,y,z };
				break;
			}
		}
	}
	m_ThornEnemys.resize(m_ThornEnemy_Num);

	for (int i = 0; i < m_ThornEnemy_Num; i++) {
		m_ThornEnemys[i] = new ThornEnemy();
		m_ThornEnemys[i]->Initialize();
		m_ThornEnemys[i]->SetPlayer(player);
		m_ThornEnemys[i]->SetHitStop(hitstop);
		m_ThornEnemys[i]->SetThornPos(m_SetThornEnemyPosY[i]);
		m_ThornEnemys[i]->SetAngle(m_EnemyAngle[i]);
		m_ThornEnemys[i]->SetPosition({ m_ThornEnemyStartPos[i].x,0.0f,m_ThornEnemyStartPos[i].z });
		lightGroup->SetCircleShadowActive(i + m_Enemy_Num, true);
	}

	//羽の敵
	while (std::getline(m_BoundEnemyPopcom, m_BoundEnemyLine)) {
		std::istringstream line_stream(m_BoundEnemyLine);
		std::string word;
		std::getline(line_stream, word, ',');

		if (word.find("//") == 0) {
			continue;
		}
		if (word.find("Enemy_Quantity") == 0) {
			std::getline(line_stream, word, ',');
			int quantity3 = (int)std::atof(word.c_str());
			m_BoundEnemy_Num = quantity3;
			m_BoundEnemyCount = m_BoundEnemy_Num;
			break;
		}
	}
	m_BoundEnemyStartPos.resize(m_BoundEnemy_Num);
	for (int i = 0; i < m_BoundEnemy_Num; i++) {
		while (std::getline(m_BoundEnemyPopcom, m_BoundEnemyLine)) {
			std::istringstream line_stream(m_BoundEnemyLine);
			std::string word;
			std::getline(line_stream, word, ',');

			if (word.find("//") == 0) {
				continue;
			}
			if (word.find("Number") == 0) {
				std::getline(line_stream, word, ',');
				int number = (int)std::atof(word.c_str());
			}
			else if (word.find("POP") == 0) {
				std::getline(line_stream, word, ',');
				float x = (float)std::atof(word.c_str());

				std::getline(line_stream, word, ',');
				float y = (float)std::atof(word.c_str());

				std::getline(line_stream, word, ',');
				float z = (float)std::atof(word.c_str());

				m_BoundEnemyStartPos[i] = { x,y,z };
				break;
			}
		}
	}
	m_BoundEnemys.resize(m_BoundEnemy_Num);

	for (int i = 0; i < m_BoundEnemy_Num; i++) {
		m_BoundEnemys[i] = new BoundEnemy();
		m_BoundEnemys[i]->Initialize();
		m_BoundEnemys[i]->SetPlayer(player);
		m_BoundEnemys[i]->SetBlock(block);
		m_BoundEnemys[i]->SetHitStop(hitstop);
		m_BoundEnemys[i]->SetPosition(m_BoundEnemyStartPos[i]);
		lightGroup->SetCircleShadowActive(i + (m_Enemy_Num + m_ThornEnemy_Num), true);
	}

	//飛んでる敵の敵
	while (std::getline(m_BirdEnemyPopcom, m_BirdEnemyLine)) {
		std::istringstream line_stream(m_BirdEnemyLine);
		std::string word;
		std::getline(line_stream, word, ',');

		if (word.find("//") == 0) {
			continue;
		}
		if (word.find("Enemy_Quantity") == 0) {
			std::getline(line_stream, word, ',');
			int quantity4 = (int)std::atof(word.c_str());
			m_BirdEnemy_Num = quantity4;
			m_BirdEnemyCount = m_BirdEnemy_Num;
			break;
		}
	}
	m_BirdEnemyStartPos.resize(m_BirdEnemy_Num);
	for (int i = 0; i < m_BirdEnemy_Num; i++) {
		while (std::getline(m_BirdEnemyPopcom, m_BirdEnemyLine)) {
			std::istringstream line_stream(m_BirdEnemyLine);
			std::string word;
			std::getline(line_stream, word, ',');

			if (word.find("//") == 0) {
				continue;
			}
			if (word.find("Number") == 0) {
				std::getline(line_stream, word, ',');
				int number = (int)std::atof(word.c_str());
			}
			else if (word.find("POP") == 0) {
				std::getline(line_stream, word, ',');
				float x = (float)std::atof(word.c_str());

				std::getline(line_stream, word, ',');
				float y = (float)std::atof(word.c_str());

				std::getline(line_stream, word, ',');
				float z = (float)std::atof(word.c_str());

				m_BirdEnemyStartPos[i] = { x,y,z };
				break;
			}
		}
	}
	m_BirdEnemys.resize(m_BirdEnemy_Num);

	for (int i = 0; i < m_BirdEnemy_Num; i++) {
		m_BirdEnemys[i] = new BirdEnemy();
		m_BirdEnemys[i]->Initialize();
		m_BirdEnemys[i]->SetPlayer(player);
		m_BirdEnemys[i]->SetBlock(block);
		m_BirdEnemys[i]->SetHitStop(hitstop);
		m_BirdEnemys[i]->SetPosition(m_BirdEnemyStartPos[i]);
		lightGroup->SetCircleShadowActive(i + (m_Enemy_Num + m_ThornEnemy_Num + m_BoundEnemy_Num), true);
	}

	//棘OBJ
	while (std::getline(m_ThornObjPopcom, m_ThornObjLine)) {
		std::istringstream line_stream(m_ThornObjLine);
		std::string word;
		std::getline(line_stream, word, ',');

		if (word.find("//") == 0) {
			continue;
		}
		if (word.find("Enemy_Quantity2") == 0) {
			std::getline(line_stream, word, ',');
			int quantity5 = (int)std::atof(word.c_str());
			m_ThornObj_Num = quantity5;
			break;
		}
	}
	m_SetThornObjPos.resize(m_ThornObj_Num);
	//m_ThornObjPosition.resize(m_ThornObj_Num);
	m_SetThornObjDir.resize(m_ThornObj_Num);
	m_SetThornObjTargetTimer.resize(m_ThornObj_Num);
	for (int i = 0; i < m_ThornObj_Num; i++) {
		while (std::getline(m_ThornObjPopcom, m_ThornObjLine)) {
			std::istringstream line_stream(m_ThornObjLine);
			std::string word;
			std::getline(line_stream, word, ',');

			if (word.find("//") == 0) {
				continue;
			}
			else if (word.find("Dir") == 0) {
				std::getline(line_stream, word, ',');
				int dir = (int)std::atof(word.c_str());
				m_SetThornObjDir[i] = dir;
			}
			else if (word.find("Target") == 0) {
				std::getline(line_stream, word, ',');
				int targettimer = (int)std::atof(word.c_str());
				m_SetThornObjTargetTimer[i] = targettimer;
			}
			else if (word.find("StartPos") == 0) {
				std::getline(line_stream, word, ',');
				float posx = (float)std::atof(word.c_str());
				std::getline(line_stream, word, ',');
				float posy = (float)std::atof(word.c_str());
				std::getline(line_stream, word, ',');
				float posz = (float)std::atof(word.c_str());
				m_SetThornObjPos[i] = { posx,posy,posz };
				break;
			}
		}
	}
	m_ThornObjs.resize(m_ThornObj_Num);

	for (int i = 0; i < m_ThornObj_Num; i++) {
		m_ThornObjs[i] = new ThornObj();
		m_ThornObjs[i]->Initialize();
		m_ThornObjs[i]->SetPlayer(player);
		m_ThornObjs[i]->SetTargetTimer(m_SetThornObjTargetTimer[i]);
		m_ThornObjs[i]->SetDir(m_SetThornObjDir[i]);
		m_ThornObjs[i]->SetPosition(m_SetThornObjPos[i]);
		m_ThornObjs[i]->SetThornObjPos(m_SetThornObjPos[i]);
	}
}
//CSVを開いている
void BaseScene::OpenObjParam(const int& StageNumber) {
	switch (StageNumber)
	{
	case Map1:
		m_BackObjFile.open("Resources/backobj_param/BackObj/FirstMapBackObj.csv");
	case Map2:
		m_BackObjFile.open("Resources/backobj_param/BackObj/SecondMapBackObj.csv");
	case Map3:
		m_BackObjFile.open("Resources/backobj_param/BackObj/ThirdMapBackObj.csv");
	case Map4:
		m_BackObjFile.open("Resources/backobj_param/BackObj/FourthMapBackObj.csv");
	case Map5:
		m_BackObjFile.open("Resources/backobj_param/BackObj/FifthMapBackObj.csv");
	case Map6:
		m_BackObjFile.open("Resources/backobj_param/BackObj/SixMapBackObj.csv");
	case BossMap:
		m_BackObjFile.open("Resources/backobj_param/BackObj/BossMapBackObj.csv");
	case TutoRial:
		m_BackObjFile.open("Resources/backobj_param/BackObj/TutorialBackObj.csv");
	default:
		break;
	}
	m_BackObjPopcom << m_BackObjFile.rdbuf();
	m_BackObjFile.close();
}
//CSV指定
void BaseScene::ObjSpecity(const char* vsShaderName) {
	//普通の柱
	std::ofstream normalofs(vsShaderName);  // ファイルパスを指定する
	normalofs << "RockCount" << "," << m_BackRocks.size() << std::endl;
	for (int i = 0; i < m_BackRocks.size(); i++) {
		normalofs << "RockWait" << "," << 120 << std::endl;
		normalofs << "RockPOP" << "," << m_BackRocks[i]->GetPosition().x
			<< "," << m_BackRocks[i]->GetPosition().y
			<< "," << m_BackRocks[i]->GetPosition().z << std::endl;
		normalofs << "RockROT" << "," << m_BackRocks[i]->GetRotation().x
			<< "," << m_BackRocks[i]->GetRotation().y
			<< "," << m_BackRocks[i]->GetRotation().z << std::endl;
	}
	
	//岩
	normalofs << "BoxCount" << "," << m_BackBoxs.size() << std::endl;
	for (int i = 0; i < m_BackBoxs.size(); i++) {
		normalofs << "BoxWait" << "," << 120 << std::endl;
		normalofs << "BoxPOP" << "," << m_BackBoxs[i]->GetPosition().x
			<< "," << m_BackBoxs[i]->GetPosition().y
			<< "," << m_BackBoxs[i]->GetPosition().z << std::endl;
		normalofs << "BoxROT" << "," << m_BackBoxs[i]->GetRotation().x
			<< "," << m_BackBoxs[i]->GetRotation().y
			<< "," << m_BackBoxs[i]->GetRotation().z << std::endl;
	}
	//松明
	normalofs << "TorchCount" << "," << m_BackTorchs.size() << std::endl;
	for (int i = 0; i < m_BackTorchs.size(); i++) {
		normalofs << "TorchWait" << "," << 120 << std::endl;
		normalofs << "TorchPOP" << "," << m_BackTorchs[i]->GetPosition().x
			<< "," << m_BackTorchs[i]->GetPosition().y
			<< "," << m_BackTorchs[i]->GetPosition().z << std::endl;
		normalofs << "TorchROT" << "," << m_BackTorchs[i]->GetRotation().x
			<< "," << m_BackTorchs[i]->GetRotation().y
			<< "," << m_BackTorchs[i]->GetRotation().z << std::endl;
	}
}
//CSVに書き込んでいる
void BaseScene::SaveObjParam(const int& StageNumber) {
	//マップ1
	if (StageNumber == Map1) {
		ObjSpecity("Resources/backobj_param/BackObj/FirstMapBackObj.csv");
	}
	//マップ2
	else if (StageNumber == Map2) {
		//普通の敵
		ObjSpecity("Resources/backobj_param/BackObj/SecondMapBackObj.csv");  // ファイルパスを指定する
	}
	//マップ3
	else if (StageNumber == Map3) {
		//普通の敵
		ObjSpecity("Resources/backobj_param/BackObj/ThirdMapBackObj.csv");  // ファイルパスを指定する
	}
	//マップ4
	else if (StageNumber == Map4) {
		//普通の敵
		ObjSpecity("Resources/backobj_param/BackObj/FourthMapBackObj.csv");  // ファイルパスを指定する
	}
	//マップ5
	else if (StageNumber == Map5) {
		//普通の敵
		ObjSpecity("Resources/backobj_param/BackObj/FifthMapBackObj.csv");  // ファイルパスを指定する
	}
	//マップ6
	else if (StageNumber == Map6) {
		//普通の敵
		ObjSpecity("Resources/backobj_param/BackObj/SixMapBackObj.csv");  // ファイルパスを指定する
	}
	else if (StageNumber == TutoRial) {
		//普通の敵
		ObjSpecity("Resources/backobj_param/BackObj/TutorialBackObj.csv");  // ファイルパスを指定する
	}
}
//CSVから値を読み込んでいる(Obj)
void BaseScene::LoadObjParam(const int& StageNumber) {
	OpenObjParam(StageNumber);
	//背景Obj
	//柱
	while (std::getline(m_BackObjPopcom, m_BackObjLine)) {
		std::istringstream line_stream(m_BackObjLine);
		std::string word;
		std::getline(line_stream, word, ',');

		if (word.find("//") == 0) {
			continue;
		}
		if (word.find("RockCount") == 0) {
			std::getline(line_stream, word, ',');
			int quantity = (int)std::atof(word.c_str());
			m_BackRock_Num = quantity;
			break;
		}
	}
	m_BackRockStartPos.resize(m_BackRock_Num);
	m_BackRockStartRot.resize(m_BackRock_Num);
	for (int i = 0; i < m_BackRock_Num; i++) {
		while (std::getline(m_BackObjPopcom, m_BackObjLine)) {
			std::istringstream line_stream(m_BackObjLine);
			std::string word;
			std::getline(line_stream, word, ',');

			if (word.find("//") == 0) {
				continue;
			}
			if (word.find("Number") == 0) {
				std::getline(line_stream, word, ',');
				int number = (int)std::atof(word.c_str());
			}
			else if (word.find("RockPOP") == 0) {
				std::getline(line_stream, word, ',');
				float x = (float)std::atof(word.c_str());

				std::getline(line_stream, word, ',');
				float y = (float)std::atof(word.c_str());

				std::getline(line_stream, word, ',');
				float z = (float)std::atof(word.c_str());

				m_BackRockStartPos[i] = { x,y,z };
			}
			else if (word.find("RockROT") == 0) {
				std::getline(line_stream, word, ',');
				float x = (float)std::atof(word.c_str());

				std::getline(line_stream, word, ',');
				float y = (float)std::atof(word.c_str());

				std::getline(line_stream, word, ',');
				float z = (float)std::atof(word.c_str());

				m_BackRockStartRot[i] = { x,y,z };
				break;
			}
		}
	}
	m_BackRocks.resize(m_BackRock_Num);

	for (int i = 0; i < m_BackRock_Num; i++) {
		m_BackRocks[i] = new BackRock();
		m_BackRocks[i]->Initialize();
		m_BackRocks[i]->SetPlayer(player);
		m_BackRocks[i]->SetPosition(m_BackRockStartPos[i]);
		m_BackRocks[i]->SetRotation(m_BackRockStartRot[i]);
	}
	
	//岩
	while (std::getline(m_BackObjPopcom, m_BackObjLine)) {
		std::istringstream line_stream(m_BackObjLine);
		std::string word;
		std::getline(line_stream, word, ',');

		if (word.find("//") == 0) {
			continue;
		}
		if (word.find("BoxCount") == 0) {
			std::getline(line_stream, word, ',');
			int quantity = (int)std::atof(word.c_str());
			m_BackBox_Num = quantity;
			break;
		}
	}
	m_BackBoxStartPos.resize(m_BackBox_Num);
	m_BackBoxStartRot.resize(m_BackBox_Num);
	for (int i = 0; i < m_BackBox_Num; i++) {
		while (std::getline(m_BackObjPopcom, m_BackObjLine)) {
			std::istringstream line_stream(m_BackObjLine);
			std::string word;
			std::getline(line_stream, word, ',');

			if (word.find("//") == 0) {
				continue;
			}
			if (word.find("Number") == 0) {
				std::getline(line_stream, word, ',');
				int number = (int)std::atof(word.c_str());
			}
			else if (word.find("BoxPOP") == 0) {
				std::getline(line_stream, word, ',');
				float x = (float)std::atof(word.c_str());

				std::getline(line_stream, word, ',');
				float y = (float)std::atof(word.c_str());

				std::getline(line_stream, word, ',');
				float z = (float)std::atof(word.c_str());

				m_BackBoxStartPos[i] = { x,y,z };
			}
			else if (word.find("BoxROT") == 0) {
				std::getline(line_stream, word, ',');
				float x = (float)std::atof(word.c_str());

				std::getline(line_stream, word, ',');
				float y = (float)std::atof(word.c_str());

				std::getline(line_stream, word, ',');
				float z = (float)std::atof(word.c_str());

				m_BackBoxStartRot[i] = { x,y,z };
				break;
			}
		}
	}
	m_BackBoxs.resize(m_BackBox_Num);

	for (int i = 0; i < m_BackBox_Num; i++) {
		m_BackBoxs[i] = new BackBox();
		m_BackBoxs[i]->Initialize();
		m_BackBoxs[i]->SetPlayer(player);
		m_BackBoxs[i]->SetPosition(m_BackBoxStartPos[i]);
		m_BackBoxs[i]->SetRotation(m_BackBoxStartRot[i]);
	}

	//松明
	while (std::getline(m_BackObjPopcom, m_BackObjLine)) {
		std::istringstream line_stream(m_BackObjLine);
		std::string word;
		std::getline(line_stream, word, ',');

		if (word.find("//") == 0) {
			continue;
		}
		if (word.find("TorchCount") == 0) {
			std::getline(line_stream, word, ',');
			int quantity = (int)std::atof(word.c_str());
			m_BackTorch_Num = quantity;
			break;
		}
	}
	m_BackTorchStartPos.resize(m_BackTorch_Num);
	m_BackTorchStartRot.resize(m_BackTorch_Num);
	for (int i = 0; i < m_BackTorch_Num; i++) {
		while (std::getline(m_BackObjPopcom, m_BackObjLine)) {
			std::istringstream line_stream(m_BackObjLine);
			std::string word;
			std::getline(line_stream, word, ',');

			if (word.find("//") == 0) {
				continue;
			}
			if (word.find("Number") == 0) {
				std::getline(line_stream, word, ',');
				int number = (int)std::atof(word.c_str());
			}
			else if (word.find("TorchPOP") == 0) {
				std::getline(line_stream, word, ',');
				float x = (float)std::atof(word.c_str());

				std::getline(line_stream, word, ',');
				float y = (float)std::atof(word.c_str());

				std::getline(line_stream, word, ',');
				float z = (float)std::atof(word.c_str());

				m_BackTorchStartPos[i] = { x,y,z };
			}
			else if (word.find("TorchROT") == 0) {
				std::getline(line_stream, word, ',');
				float x = (float)std::atof(word.c_str());

				std::getline(line_stream, word, ',');
				float y = (float)std::atof(word.c_str());

				std::getline(line_stream, word, ',');
				float z = (float)std::atof(word.c_str());

				m_BackTorchStartRot[i] = { x,y,z };
				break;
			}
		}
	}
	m_BackTorchs.resize(m_BackTorch_Num);

	for (int i = 0; i < m_BackTorch_Num; i++) {
		m_BackTorchs[i] = new BackTorch();
		m_BackTorchs[i]->Initialize();
		m_BackTorchs[i]->SetPlayer(player);
		m_BackTorchs[i]->SetPosition(m_BackTorchStartPos[i]);
		m_BackTorchs[i]->SetRotation(m_BackTorchStartRot[i]);
		lightGroup->SetPointLightActive(i + 2, true);
	}
}
//ゲームデータのセーブ(位置とマップ番号)
void BaseScene::SaveGame() {
	std::ofstream playerofs("Resources/game_param/gamedata.csv");  // ファイルパスを指定する
	//normalofs << "Enemy_Quantity" << "," << m_Enemys.size() << std::endl;

	playerofs << "Wait" << "," << 120 << std::endl;
	playerofs << "StageNumber" << "," << StartStage << std::endl;
	playerofs << "POP" << "," << player->GetPosition().x
		<< "," << player->GetPosition().y
		<< "," << player->GetPosition().z << std::endl;
	playerofs << "DushSkill" << "," << playerskill->GetDushSkill() << std::endl;
	playerofs << "LibraSkill" << "," << playerskill->GetLibraSkill() << std::endl;
	playerofs << "CompassSkill" << "," << playerskill->GetCompassSkill() << std::endl;
	playerofs << "HealSkill" << "," << playerskill->GetHealSkill() << std::endl;
	playerofs << "HP" << "," << player->GetHP() << std::endl;
	playerofs << "Soul" << "," << player->GetSoulCount() << std::endl;
}
//ゲームデータのロード
void BaseScene::LoadGame() {
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

			playerskill->SetDushSkill(l_startdushskill);
		}
		else if (word.find("LibraSkill") == 0) {

			std::getline(line_stream, word, ',');
			bool l_startlibraskill = (int)std::atof(word.c_str());

			playerskill->SetLibraSkill(l_startlibraskill);
		}
		else if (word.find("CompassSkill") == 0) {

			std::getline(line_stream, word, ',');
			bool l_startcompassskill = (int)std::atof(word.c_str());

			playerskill->SetCompassSkill(l_startcompassskill);
		}
		else if (word.find("HealSkill") == 0) {

			std::getline(line_stream, word, ',');
			bool l_starthealskill = (int)std::atof(word.c_str());

			playerskill->SetHealSkill(l_starthealskill);
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
//敵の更新
void BaseScene::EnemyUpdate(std::vector<InterEnemy*> m_Enemys) {
	for (InterEnemy* enemy : m_Enemys) {
		if (enemy != nullptr) {
			if (!pause->GetIsPause() && !chest->GetExplain() && !hitstop->GetHitStop() && m_MoveEnemy) {
				enemy->Update();
			}
			else {
				enemy->Pause();
			}
		}
	}
}
//敵の描画
void BaseScene::EnemyDraw(std::vector<InterEnemy*> m_Enemys, DirectXCommon* dxCommon) {
	for (InterEnemy* enemy : m_Enemys) {
		if (enemy != nullptr) {
			enemy->Draw(dxCommon);
		}
	}
}
//敵の解放
void BaseScene::EnemyFinalize(std::vector<InterEnemy*> m_Enemys) {
	for (InterEnemy* enemy : m_Enemys) {
		if (enemy != nullptr) {
			enemy->Finalize();
		}
	}
}
//背景OBjの更新
void BaseScene::BackObjUpdate(std::vector<BackObjCommon*> objs) {
	for (BackObjCommon* backobj : objs) {
		if (backobj != nullptr) {
			backobj->Update();
		}
	}
}
//背景OBjの動画
void BaseScene::BackObjDraw(std::vector<BackObjCommon*> objs, DirectXCommon* dxCommon) {
	for (BackObjCommon* backobj : objs) {
		if (backobj != nullptr) {
			backobj->Draw();
		}
	}
}