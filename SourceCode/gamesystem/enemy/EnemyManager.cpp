#include "EnemyManager.h"
#include "VariableCommon.h"
EnemyManager::EnemyManager() {
	enemyedit = new EnemyEdit();
}
void EnemyManager::SoulSet(Player* player, Block* block) {
	//魂
	for (int i = 0; i < Soul_Max; i++) {
		for (int j = 0; j < Enemy_Max; j++) {
			normalplayersoul[i][j] = new PlayerSoul();
			normalplayersoul[i][j]->Initialize();
			normalplayersoul[i][j]->SetBlock(block);
			normalplayersoul[i][j]->SetPlayer(player);

			boundplayersoul[i][j] = new PlayerSoul();
			boundplayersoul[i][j]->Initialize();
			boundplayersoul[i][j]->SetBlock(block);
			boundplayersoul[i][j]->SetPlayer(player);

			birdplayersoul[i][j] = new PlayerSoul();
			birdplayersoul[i][j]->Initialize();
			birdplayersoul[i][j]->SetBlock(block);
			birdplayersoul[i][j]->SetPlayer(player);

			followplayersoul[i][j] = new PlayerSoul();
			followplayersoul[i][j]->Initialize();
			followplayersoul[i][j]->SetBlock(block);
			followplayersoul[i][j]->SetPlayer(player);

			chestplayersoul[i][j] = new PlayerSoul();
			chestplayersoul[i][j]->Initialize();
			chestplayersoul[i][j]->SetBlock(block);
			chestplayersoul[i][j]->SetPlayer(player);
		}
	}
}
//CSVを開いている(敵)
void EnemyManager::OpenEnemyParam(const int StageNumber) {
	switch (StageNumber)
	{
	case Map1:
		m_EnemyFile.open("Resources/enemy_param/NormalEnemy/FirstMapEnemy.csv");
		m_ThornEnemyFile.open("Resources/enemy_param/ThornEnemy/FirstMapThornEnemy.csv");
		m_BoundEnemyFile.open("Resources/enemy_param/BoundEnemy/FirstMapBoundEnemy.csv");
		m_BirdEnemyFile.open("Resources/enemy_param/BirdEnemy/FirstMapBirdEnemy.csv");
		m_FollowEnemyFile.open("Resources/enemy_param/FollowEnemy/FirstMapFollowEnemy.csv");
		m_ChestEnemyFile.open("Resources/enemy_param/ChestEnemy/FirstMapChestEnemy.csv");
		m_ThornObjFile.open("Resources/enemy_param/ThornObj/FirstMapThornObj.csv");
	case Map2:
		m_EnemyFile.open("Resources/enemy_param/NormalEnemy/SecondMapEnemy.csv");
		m_ThornEnemyFile.open("Resources/enemy_param/ThornEnemy/SecondMapThornEnemy.csv");
		m_BoundEnemyFile.open("Resources/enemy_param/BoundEnemy/SecondMapBoundEnemy.csv");
		m_BirdEnemyFile.open("Resources/enemy_param/BirdEnemy/SecondMapBirdEnemy.csv");
		m_FollowEnemyFile.open("Resources/enemy_param/FollowEnemy/SecondMapFollowEnemy.csv");
		m_ChestEnemyFile.open("Resources/enemy_param/ChestEnemy/SecondMapChestEnemy.csv");
		m_ThornObjFile.open("Resources/enemy_param/ThornObj/SecondMapThornObj.csv");
	case Map3:
		m_EnemyFile.open("Resources/enemy_param/NormalEnemy/ThirdMapEnemy.csv");
		m_ThornEnemyFile.open("Resources/enemy_param/ThornEnemy/ThirdMapThornEnemy.csv");
		m_BoundEnemyFile.open("Resources/enemy_param/BoundEnemy/ThirdMapBoundEnemy.csv");
		m_BirdEnemyFile.open("Resources/enemy_param/BirdEnemy/ThridMapBirdEnemy.csv");
		m_FollowEnemyFile.open("Resources/enemy_param/FollowEnemy/ThirdMapFollowEnemy.csv");
		m_ChestEnemyFile.open("Resources/enemy_param/ChestEnemy/ThirdMapChestEnemy.csv");
		m_ThornObjFile.open("Resources/enemy_param/ThornObj/ThirdMapThornObj.csv");
	case Map4:
		m_EnemyFile.open("Resources/enemy_param/NormalEnemy/FourthMapEnemy.csv");
		m_ThornEnemyFile.open("Resources/enemy_param/ThornEnemy/FourthMapThornEnemy.csv");
		m_BoundEnemyFile.open("Resources/enemy_param/BoundEnemy/FourthMapBoundEnemy.csv");
		m_BirdEnemyFile.open("Resources/enemy_param/BirdEnemy/FourthMapBirdEnemy.csv");
		m_FollowEnemyFile.open("Resources/enemy_param/FollowEnemy/FourthMapFollowEnemy.csv");
		m_ChestEnemyFile.open("Resources/enemy_param/ChestEnemy/FourthMapChestEnemy.csv");
		m_ThornObjFile.open("Resources/enemy_param/ThornObj/FourthMapThornObj.csv");
	case Map5:
		m_EnemyFile.open("Resources/enemy_param/NormalEnemy/FifthMapEnemy.csv");
		m_ThornEnemyFile.open("Resources/enemy_param/ThornEnemy/FifthMapThornEnemy.csv");
		m_BoundEnemyFile.open("Resources/enemy_param/BoundEnemy/FifthMapBoundEnemy.csv");
		m_BirdEnemyFile.open("Resources/enemy_param/BirdEnemy/FifthMapBirdEnemy.csv");
		m_FollowEnemyFile.open("Resources/enemy_param/FollowEnemy/FifthMapFollowEnemy.csv");
		m_ChestEnemyFile.open("Resources/enemy_param/ChestEnemy/FifthMapChestEnemy.csv");
		m_ThornObjFile.open("Resources/enemy_param/ThornObj/FifthMapThornObj.csv");
	case Map6:
		m_EnemyFile.open("Resources/enemy_param/NormalEnemy/SixMapEnemy.csv");
		m_ThornEnemyFile.open("Resources/enemy_param/ThornEnemy/SixMapThornEnemy.csv");
		m_BoundEnemyFile.open("Resources/enemy_param/BoundEnemy/SixMapBoundEnemy.csv");
		m_BirdEnemyFile.open("Resources/enemy_param/BirdEnemy/SixMapBirdEnemy.csv");
		m_FollowEnemyFile.open("Resources/enemy_param/FollowEnemy/SixMapFollowEnemy.csv");
		m_ChestEnemyFile.open("Resources/enemy_param/ChestEnemy/SixMapChestEnemy.csv");
		m_ThornObjFile.open("Resources/enemy_param/ThornObj/SixMapThornObj.csv");
	case BossMap:
		m_EnemyFile.open("Resources/enemy_param/NormalEnemy/BossMapEnemy.csv");
		m_ThornEnemyFile.open("Resources/enemy_param/NormalEnemy/BossMapEnemy.csv");
		m_BoundEnemyFile.open("Resources/enemy_param/NormalEnemy/BossMapEnemy.csv");
		m_BirdEnemyFile.open("Resources/enemy_param/NormalEnemy/BossMapEnemy.csv");
		m_FollowEnemyFile.open("Resources/enemy_param/NormalEnemy/BossMapEnemy.csv");
		m_ChestEnemyFile.open("Resources/enemy_param/NormalEnemy/BossMapEnemy.csv");
	case TutoRial:
		m_EnemyFile.open("Resources/enemy_param/NormalEnemy/TutorialEnemy.csv");
		m_ThornEnemyFile.open("Resources/enemy_param/ThornEnemy/TutorialThornEnemy.csv");
		m_BoundEnemyFile.open("Resources/enemy_param/BoundEnemy/TutorialBoundEnemy.csv");
		m_BirdEnemyFile.open("Resources/enemy_param/BirdEnemy/TutorialBirdEnemy.csv");
		m_FollowEnemyFile.open("Resources/enemy_param/FollowEnemy/TutorialFollowEnemy.csv");
		m_ChestEnemyFile.open("Resources/enemy_param/ChestEnemy/TutorialChestEnemy.csv");
		m_ThornObjFile.open("Resources/enemy_param/ThornObj/TutorialMapThornObj.csv");
	default:
		break;
	}
	m_EnemyPopcom << m_EnemyFile.rdbuf();
	m_ThornEnemyPopcom << m_ThornEnemyFile.rdbuf();
	m_BoundEnemyPopcom << m_BoundEnemyFile.rdbuf();
	m_BirdEnemyPopcom << m_BirdEnemyFile.rdbuf();
	m_FollowEnemyPopcom << m_FollowEnemyFile.rdbuf();
	m_ChestEnemyPopcom << m_ChestEnemyFile.rdbuf();
	m_ThornObjPopcom << m_ThornObjFile.rdbuf();

	m_EnemyFile.close();
	m_ThornEnemyFile.close();
	m_BoundEnemyFile.close();
	m_BirdEnemyFile.close();
	m_FollowEnemyFile.close();
	m_ChestEnemyFile.close();
	m_ThornObjFile.close();
}
//CSV指定(普通の敵)
void EnemyManager::NormalEnemySpecity(const char* vsShaderName) {
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
void EnemyManager::ThornEnemySpecity(const char* vsShaderName) {
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
void EnemyManager::BoundEnemySpecity(const char* vsShaderName) {
	std::ofstream birdofs(vsShaderName);  // ファイルパスを指定する
	birdofs << "Enemy_Quantity" << "," << m_BoundEnemys.size() << std::endl;

	for (int i = 0; i < m_BoundEnemys.size(); i++) {
		birdofs << "Wait" << "," << 120 << std::endl;
		birdofs << "POP" << "," << m_BoundEnemys[i]->GetStartPos().x
			<< "," << m_BoundEnemys[i]->GetPosition().y
			<< "," << m_BoundEnemys[i]->GetStartPos().z << std::endl;

	}
	m_BoundEnemyPosition.resize(m_BoundEnemys.size());
}
//鳥の敵
void EnemyManager::BirdEnemySpecity(const char* vsShaderName) {
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
//追従の敵
void EnemyManager::FollowEnemySpecity(const char* vsShaderName) {
	//棘の敵
	std::ofstream followofs(vsShaderName);  // ファイルパスを指定する
	followofs << "Enemy_Quantity2" << "," << m_FollowEnemys.size() << std::endl;
	for (int i = 0; i < m_FollowEnemys.size(); i++) {
		followofs << "Wait" << "," << 120 << std::endl;
		followofs << "POP" << "," << m_FollowEnemys[i]->GetPosition().x
			<< "," << m_FollowEnemys[i]->GetPosition().y
			<< "," << m_FollowEnemys[i]->GetPosition().z << std::endl;
	}
	m_FollowEnemyPosition.resize(m_FollowEnemys.size());
}
//宝箱
void EnemyManager::ChestEnemySpecity(const char* vsShaderName) {
	//普通の敵
	std::ofstream normalofs(vsShaderName);  // ファイルパスを指定する
	normalofs << "Enemy_Quantity" << "," << m_ChestEnemys.size() << std::endl;

	for (int i = 0; i < m_ChestEnemys.size(); i++) {
		normalofs << "Wait" << "," << 120 << std::endl;
		normalofs << "POP" << "," << m_ChestEnemys[i]->GetStartPos().x
			<< "," << m_ChestEnemys[i]->GetStartPos().y
			<< "," << m_ChestEnemys[i]->GetStartPos().z << std::endl;

	}
	m_ChestEnemyPosition.resize(m_ChestEnemys.size());
}
//棘のOBJ
void EnemyManager::ThornObjSpecity(const char* vsShaderName) {
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
void EnemyManager::SaveEnemyParam(const int StageNumber) {
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
		//追従の敵
		FollowEnemySpecity("Resources/enemy_param/FollowEnemy/FirstMapFollowEnemy.csv");  // ファイルパスを指定する
		//宝箱
		ChestEnemySpecity("Resources/enemy_param/ChestEnemy/FirstMapChestEnemy.csv");  // ファイルパスを指定する
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
		//追従の敵
		FollowEnemySpecity("Resources/enemy_param/FollowEnemy/SecondMapFollowEnemy.csv");  // ファイルパスを指定する
		//宝箱
		ChestEnemySpecity("Resources/enemy_param/ChestEnemy/SecondMapChestEnemy.csv");  // ファイルパスを指定する
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
		//追従の敵
		FollowEnemySpecity("Resources/enemy_param/FollowEnemy/ThirdMapFollowEnemy.csv");  // ファイルパスを指定する
		//宝箱
		ChestEnemySpecity("Resources/enemy_param/ChestEnemy/ThirdMapChestEnemy.csv");  // ファイルパスを指定する
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
		//追従の敵
		FollowEnemySpecity("Resources/enemy_param/FollowEnemy/FourthMapFollowEnemy.csv");  // ファイルパスを指定する
		//宝箱
		ChestEnemySpecity("Resources/enemy_param/ChestEnemy/FourthMapChestEnemy.csv");  // ファイルパスを指定する
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
		//追従の敵
		FollowEnemySpecity("Resources/enemy_param/FollowEnemy/FifthMapFollowEnemy.csv");  // ファイルパスを指定する
		//宝箱
		ChestEnemySpecity("Resources/enemy_param/ChestEnemy/FifthMapChestEnemy.csv");  // ファイルパスを指定する
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
		//追従の敵
		FollowEnemySpecity("Resources/enemy_param/FollowEnemy/SixMapFollowEnemy.csv");  // ファイルパスを指定する
		//宝箱
		ChestEnemySpecity("Resources/enemy_param/ChestEnemy/SixMapChestEnemy.csv");  // ファイルパスを指定する
		//棘のOBJ
		ThornObjSpecity("Resources/enemy_param/ThornObj/SixMapThornObj.csv");  // ファイルパスを指定する
	}
	//チュートリアル
	else if (StageNumber == TutoRial) {
		//普通の敵
		NormalEnemySpecity("Resources/enemy_param/NormalEnemy/TutorialEnemy.csv");  // ファイルパスを指定する
		//棘の敵
		ThornEnemySpecity("Resources/enemy_param/ThornEnemy/TutorialThornEnemy.csv");  // ファイルパスを指定する
		//棘の敵
		BoundEnemySpecity("Resources/enemy_param/BoundEnemy/TutorialBoundEnemy.csv");  // ファイルパスを指定する
		//鳥の敵
		BirdEnemySpecity("Resources/enemy_param/BirdEnemy/TutorialBirdEnemy.csv");  // ファイルパスを指定する
		//追従の敵
		FollowEnemySpecity("Resources/enemy_param/FollowEnemy/TutorialFollowEnemy.csv");  // ファイルパスを指定する
		//宝箱
		ChestEnemySpecity("Resources/enemy_param/ChestEnemy/TutorialChestEnemy.csv");  // ファイルパスを指定する
		//棘のOBJ
		ThornObjSpecity("Resources/enemy_param/ThornObj/TutorialMapThornObj.csv");  // ファイルパスを指定する
	}
}
//CSVから値を読み込んでいる(敵)
void EnemyManager::LoadEnemyParam(const int StageNumber, Player* player, Block* block, LightGroup* light) {
	lightgroup = light;
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
		m_Enemys[i]->SetPosition(m_EnemyStartPos[i]);
		m_Enemys[i]->SetStartPos(m_EnemyStartPos[i]);
		lightgroup->SetCircleShadowActive(i + 2, true);
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
		m_ThornEnemys[i]->SetThornPos(m_SetThornEnemyPosY[i]);
		m_ThornEnemys[i]->SetAngle(m_EnemyAngle[i]);
		m_ThornEnemys[i]->SetPosition({ m_ThornEnemyStartPos[i].x,0.0f,m_ThornEnemyStartPos[i].z });
		lightgroup->SetCircleShadowActive(i + m_Enemy_Num, true);
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
		m_BoundEnemys[i]->SetPosition(m_BoundEnemyStartPos[i]);
		m_BoundEnemys[i]->SetStartPos(m_BoundEnemyStartPos[i]);
		lightgroup->SetCircleShadowActive(i + (m_Enemy_Num + m_ThornEnemy_Num), true);
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
		m_BirdEnemys[i]->SetPosition(m_BirdEnemyStartPos[i]);
		m_BirdEnemys[i]->SetStartPos(m_BirdEnemyStartPos[i]);
		lightgroup->SetCircleShadowActive(i + (m_Enemy_Num + m_ThornEnemy_Num + m_BoundEnemy_Num), true);
	}

	//追従の敵
	while (std::getline(m_FollowEnemyPopcom, m_FollowEnemyLine)) {
		std::istringstream line_stream(m_FollowEnemyLine);
		std::string word;
		std::getline(line_stream, word, ',');

		if (word.find("//") == 0) {
			continue;
		}
		if (word.find("Enemy_Quantity2") == 0) {
			std::getline(line_stream, word, ',');
			int quantity = (int)std::atof(word.c_str());
			m_FollowEnemy_Num = quantity;
			m_FollowEnemyCount = m_FollowEnemy_Num;
			break;
		}
	}
	m_FollowEnemyStartPos.resize(m_FollowEnemy_Num);
	for (int i = 0; i < m_FollowEnemy_Num; i++) {
		while (std::getline(m_FollowEnemyPopcom, m_FollowEnemyLine)) {
			std::istringstream line_stream(m_FollowEnemyLine);
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

				m_FollowEnemyStartPos[i] = { x,y,z };
				break;
			}
		}
	}
	m_FollowEnemys.resize(m_FollowEnemy_Num);

	for (int i = 0; i < m_FollowEnemy_Num; i++) {
		m_FollowEnemys[i] = new FollowEnemy();
		m_FollowEnemys[i]->Initialize();
		m_FollowEnemys[i]->SetPlayer(player);
		m_FollowEnemys[i]->SetBlock(block);
		m_FollowEnemys[i]->SetPosition(m_FollowEnemyStartPos[i]);
		m_FollowEnemys[i]->SetStartPos(m_FollowEnemyStartPos[i]);
	}

	//宝箱の敵
	while (std::getline(m_ChestEnemyPopcom, m_ChestEnemyLine)) {
		std::istringstream line_stream(m_ChestEnemyLine);
		std::string word;
		std::getline(line_stream, word, ',');

		if (word.find("//") == 0) {
			continue;
		}
		if (word.find("Enemy_Quantity") == 0) {
			std::getline(line_stream, word, ',');
			int quantity = (int)std::atof(word.c_str());
			m_ChestEnemy_Num = quantity;
			m_ChestEnemyCount = m_ChestEnemy_Num;
			break;
		}
	}
	m_ChestEnemyStartPos.resize(m_ChestEnemy_Num);
	for (int i = 0; i < m_ChestEnemy_Num; i++) {
		while (std::getline(m_ChestEnemyPopcom, m_ChestEnemyLine)) {
			std::istringstream line_stream(m_ChestEnemyLine);
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

				m_ChestEnemyStartPos[i] = { x,y,z };
				break;
			}
		}
	}
	m_ChestEnemys.resize(m_ChestEnemy_Num);

	for (int i = 0; i < m_ChestEnemy_Num; i++) {
		m_ChestEnemys[i] = new ChestEnemy();
		m_ChestEnemys[i]->Initialize();
		m_ChestEnemys[i]->SetPlayer(player);
		m_ChestEnemys[i]->SetBlock(block);
		m_ChestEnemys[i]->SetPosition(m_ChestEnemyStartPos[i]);
		m_ChestEnemys[i]->SetStartPos(m_ChestEnemyStartPos[i]);
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
//更新
void EnemyManager::Update(bool Move) {
	//普通の敵
	EnemyUpdate(m_Enemys, Move);
	//棘の敵
	EnemyUpdate(m_ThornEnemys, Move);
	//羽の敵
	EnemyUpdate(m_BoundEnemys, Move);
	//鳥の敵
	EnemyUpdate(m_BirdEnemys, Move);
	//追従の敵
	EnemyUpdate(m_FollowEnemys, Move);
	//宝箱の敵
	EnemyUpdate(m_ChestEnemys, Move);
	//棘のOBJ
	for (ThornObj* thornobj : m_ThornObjs) {
		if (thornobj != nullptr) {
			if (!pause->GetIsPause() && !chest->GetExplain()) {
				thornobj->Update();
			}
			else {
				thornobj->Pause();
			}
		}
	}
}
//描画
void EnemyManager::Draw(DirectXCommon* dxCommon) {
	EnemyDraw(m_Enemys, dxCommon);
	EnemyDraw(m_ThornEnemys, dxCommon);
	EnemyDraw(m_BoundEnemys, dxCommon);
	EnemyDraw(m_BirdEnemys, dxCommon);
	EnemyDraw(m_FollowEnemys, dxCommon);
	EnemyDraw(m_ChestEnemys, dxCommon);
	//棘のOBJ
	for (ThornObj* thornobj : m_ThornObjs) {
		if (thornobj != nullptr) {
			thornobj->Draw(dxCommon);
		}
	}
}
//ImGui
void EnemyManager::ImGuiDraw() {
	EnemyImguiDraw(m_Enemys);
	EnemyImguiDraw(m_ThornEnemys);
	EnemyImguiDraw(m_BoundEnemys);
	EnemyImguiDraw(m_BirdEnemys);
	EnemyImguiDraw(m_FollowEnemys);
	EnemyImguiDraw(m_ChestEnemys);
}
//マップの描画
void EnemyManager::MapDraw(int MapType, XMFLOAT4 MapColor) {
	EnemyMapDraw(m_Enemys,MapType,MapColor);
	EnemyMapDraw(m_ThornEnemys, MapType, MapColor);
	EnemyMapDraw(m_BoundEnemys, MapType, MapColor);
	EnemyMapDraw(m_BirdEnemys, MapType, MapColor);
	EnemyMapDraw(m_FollowEnemys, MapType, MapColor);
	EnemyMapDraw(m_ChestEnemys, MapType, MapColor);
}
//敵の更新
void EnemyManager::EnemyUpdate(std::vector<InterEnemy*> m_Enemys, bool Move) {
	for (InterEnemy* enemy : m_Enemys) {
		if (enemy != nullptr) {
			if (!pause->GetIsPause() && !chest->GetExplain() && Move) {
				enemy->Update();
			}
			else {
				enemy->Pause();
			}
		}
	}
}
//敵の描画
void EnemyManager::EnemyDraw(std::vector<InterEnemy*> m_Enemys, DirectXCommon* dxCommon) {
	for (InterEnemy* enemy : m_Enemys) {
		if (enemy != nullptr) {
			enemy->Draw(dxCommon);
		}
	}
}
//Imgui
void EnemyManager::EnemyImguiDraw(std::vector<InterEnemy*> m_Enemys) {
	for (InterEnemy* enemy : m_Enemys) {
		if (enemy != nullptr) {
			enemy->ImGuiDraw();
		}
	}
}
//敵のミニマップ描画
void EnemyManager::EnemyMapDraw(std::vector<InterEnemy*> m_Enemys, int MapType, XMFLOAT4 MapColor) {
	for (InterEnemy* enemy : m_Enemys) {
		if (enemy != nullptr && pause->GetPauseNumber() == 1 && pause->GetIsPause() && MapType == 1) {
			enemy->MapDraw(MapColor);
		}
	}
}
//敵の解放
void EnemyManager::EnemyFinalize(std::vector<InterEnemy*> m_Enemys) {
	for (InterEnemy* enemy : m_Enemys) {
		if (enemy != nullptr) {
			enemy->Finalize();
		}
	}
}
//要素の数合わせ
void EnemyManager::SaveNum() {
	m_Enemy_Num = m_NormalEnemyCount;
	m_BoundEnemy_Num = m_BoundEnemyCount;
	m_BirdEnemy_Num = m_BirdEnemyCount;
	m_FollowEnemy_Num = m_FollowEnemyCount;
	m_ChestEnemy_Num = m_ChestEnemyCount;
	m_ThornObj_Num = m_ThornObjCount;
}
//敵削除
void EnemyManager::DeleteEnemy() {
	m_Enemys.clear();
	m_ThornEnemys.clear();
	m_BoundEnemys.clear();
	m_BirdEnemys.clear();
	m_FollowEnemys.clear();
	m_ChestEnemys.clear();
	m_ThornObjs.clear();
	m_NormalEnemyCount = 0;
	m_ThornObjCount = 0;
	m_BoundEnemyCount = 0;
	m_FollowEnemyCount = 0;
	m_ChestEnemyCount = 0;
	m_EnemyCount = 0;
}
//生成
void EnemyManager::EnemyBirth(int EnemyType, Player* player, Block* block) {
	//普通
	if (EnemyType == Normal) {
		enemyedit->NormalEnemyArgment(m_Enemys, player, block);
		m_NormalEnemyCount++;
	}
	//棘のやつ
	else if (EnemyType == Thorn) {
		enemyedit->ThornEnemyArgment(m_ThornEnemys, player);
	}
	//羽の敵
	else if (EnemyType == Bound) {
		enemyedit->BoundEnemyArgment(m_BoundEnemys, player, block);
		m_BoundEnemyCount++;
	}
	//鳥の敵
	else if(EnemyType == Bird) {
		enemyedit->BirdEnemyArgment(m_BirdEnemys, player, block);
		m_BirdEnemyCount++;
	}
	//追従の敵
	else if(EnemyType == Follow) {
		enemyedit->FollowEnemyArgment(m_FollowEnemys, player,block);
		m_FollowEnemyCount++;
	}
	else {
		enemyedit->ChestEnemyArgment(m_ChestEnemys, player, block);
		m_ChestEnemyCount++;
	}
}
//棘生成
void EnemyManager::ThornBirth(bool Argment, Player* player, int Dir) {
	ThornObj* newThornObj;
	newThornObj = new ThornObj();
	newThornObj->Initialize();
	newThornObj->SetPlayer(player);
	newThornObj->SetDir(Dir);
	newThornObj->SetThornObjPos(player->GetPosition());
	newThornObj->SetPosition(player->GetPosition());
	m_ThornObjs.push_back(newThornObj);
	m_ThornObjCount++;
}
//一要素の削除
void EnemyManager::DeleteEnemyPop(int Type) {
	if (Type == Normal && m_Enemys.size() > 0) {
		m_Enemys.pop_back();
		m_NormalEnemyCount--;
	}
	//とげ
	else if (Type == Thorn && m_ThornEnemys.size() > 0) {
		m_ThornEnemys.pop_back();
	}
	//羽
	else if (Type == Bound && m_BoundEnemys.size() > 0) {
		m_BoundEnemys.pop_back();
		m_BoundEnemyCount--;
	}
	//鳥
	else if (Type == Bird && m_BirdEnemys.size() > 0) {
		m_BirdEnemys.pop_back();
		m_BirdEnemyCount--;
	}
	//追従
	else if (Type == Follow && m_FollowEnemys.size() > 0) {
		m_FollowEnemys.pop_back();
		m_FollowEnemyCount--;
	}
	//宝箱
	else if (Type == FakeChest && m_ChestEnemys.size() > 0) {
		m_ChestEnemys.pop_back();
		m_ChestEnemyCount--;
	}
}
//棘の敵の一要素削除
void EnemyManager::DeleteThornPop() {
	if (m_ThornObjs.size() > 0) {
		m_ThornObjs.pop_back();
		m_ThornObjCount--;
	}
}
//ライトセット
void EnemyManager::LightSet(const int StageNumber, LightGroup* light) {
	lightgroup = light;
	for (InterEnemy* enemy : m_Enemys) {
		for (int i = 0; i < m_Enemy_Num; i++) {
			if (enemy != nullptr && enemy->GetAlive()) {
				lightgroup->SetCircleShadowDir(i + 2, XMVECTOR({ circleShadowDir[0], circleShadowDir[1], circleShadowDir[2], 0 }));
				lightgroup->SetCircleShadowCasterPos(i + 2, XMFLOAT3({ m_Enemys[i]->GetPosition().x, m_Enemys[i]->GetPosition().y, m_Enemys[i]->GetPosition().z }));
				lightgroup->SetCircleShadowAtten(i + 2, XMFLOAT3(circleShadowAtten));
				lightgroup->SetCircleShadowFactorAngle(i + 2, XMFLOAT2(circleShadowFactorAngle));
			}
			else {
				lightgroup->SetCircleShadowActive(i + 2, false);
			}
		}
	}

	for (InterEnemy* enemy : m_ThornEnemys) {
		for (int i = 0; i < m_ThornEnemy_Num; i++) {
			if (enemy != nullptr && enemy->GetAlive()) {
				lightgroup->SetCircleShadowDir(i + m_Enemy_Num, XMVECTOR({ circleShadowDir[0], circleShadowDir[1], circleShadowDir[2], 0 }));
				lightgroup->SetCircleShadowCasterPos(i + m_Enemy_Num, XMFLOAT3({ m_ThornEnemys[i]->GetPosition().x,  m_ThornEnemys[i]->GetPosition().y,  m_ThornEnemys[i]->GetPosition().z }));
				lightgroup->SetCircleShadowAtten(i + m_Enemy_Num, XMFLOAT3(circleShadowAtten));
				lightgroup->SetCircleShadowFactorAngle(i + m_Enemy_Num, XMFLOAT2(circleShadowFactorAngle));
			}
			else {
				lightgroup->SetCircleShadowActive(i + m_Enemy_Num, false);
			}
		}
	}

	for (InterEnemy* enemy : m_BoundEnemys) {
		for (int i = 0; i < m_BoundEnemy_Num; i++) {
			if (enemy != nullptr && enemy->GetAlive()) {
				lightgroup->SetCircleShadowDir(i + (m_Enemy_Num + m_ThornEnemy_Num), XMVECTOR({ circleShadowDir[0], circleShadowDir[1], circleShadowDir[2], 0 }));
				lightgroup->SetCircleShadowCasterPos(i + (m_Enemy_Num + m_ThornEnemy_Num), XMFLOAT3({ m_BoundEnemys[i]->GetPosition().x,  m_BoundEnemys[i]->GetPosition().y,  m_BoundEnemys[i]->GetPosition().z }));
				lightgroup->SetCircleShadowAtten(i + (m_Enemy_Num + m_ThornEnemy_Num), XMFLOAT3(circleShadowAtten));
				lightgroup->SetCircleShadowFactorAngle(i + (m_Enemy_Num + m_ThornEnemy_Num), XMFLOAT2(circleShadowFactorAngle));
			}
			else {
				lightgroup->SetCircleShadowActive(i + (m_Enemy_Num + m_ThornEnemy_Num), false);
			}
		}
	}

	for (InterEnemy* enemy : m_BirdEnemys) {
		for (int i = 0; i < m_BirdEnemy_Num; i++) {
			if (enemy != nullptr && enemy->GetAlive()) {
				lightgroup->SetCircleShadowDir(i + (m_Enemy_Num + m_ThornEnemy_Num + m_BoundEnemy_Num), XMVECTOR({ circleShadowDir[0], circleShadowDir[1], circleShadowDir[2], 0 }));
				lightgroup->SetCircleShadowCasterPos(i + (m_Enemy_Num + m_ThornEnemy_Num + m_BoundEnemy_Num), XMFLOAT3({ m_BirdEnemys[i]->GetPosition().x, m_BirdEnemys[i]->GetPosition().y,  m_BirdEnemys[i]->GetPosition().z }));
				lightgroup->SetCircleShadowAtten(i + (m_Enemy_Num + m_ThornEnemy_Num + m_BoundEnemy_Num), XMFLOAT3(circleShadowAtten));
				lightgroup->SetCircleShadowFactorAngle(i + (m_Enemy_Num + m_ThornEnemy_Num + m_BoundEnemy_Num), XMFLOAT2(circleShadowFactorAngle));
			}
			else {
				lightgroup->SetCircleShadowActive(i + (m_Enemy_Num + m_ThornEnemy_Num + m_BoundEnemy_Num), false);
			}
		}
	}


	lightgroup->Update();
}
//魂の更新
void EnemyManager::SoulUpdate() {
	//魂関係
	for (int i = 0; i < Soul_Max; i++) {
		for (int j = 0; j < m_NormalEnemyCount; j++) {
			normalplayersoul[i][j]->Update(m_Enemys[j]);
		}
	}
	for (int i = 0; i < Soul_Max; i++) {
		for (int j = 0; j < m_BoundEnemyCount; j++) {
			boundplayersoul[i][j]->Update(m_BoundEnemys[j]);
		}
	}

	for (int i = 0; i < Soul_Max; i++) {
		for (int j = 0; j < m_BirdEnemyCount; j++) {
			birdplayersoul[i][j]->Update(m_BirdEnemys[j]);
		}
	}

	for (int i = 0; i < Soul_Max; i++) {
		for (int j = 0; j < m_FollowEnemyCount; j++) {
			followplayersoul[i][j]->Update(m_FollowEnemys[j]);
		}
	}

	for (int i = 0; i < Soul_Max; i++) {
		for (int j = 0; j < m_ChestEnemyCount; j++) {
			chestplayersoul[i][j]->Update(m_ChestEnemys[j]);
		}
	}
}
//魂の描画
void EnemyManager::SoulDraw() {
	//魂関係
	for (int i = 0; i < Soul_Max; i++) {
		for (int j = 0; j < m_NormalEnemyCount; j++) {
			normalplayersoul[i][j]->Draw();
		}
	}

	for (int i = 0; i < Soul_Max; i++) {
		for (int j = 0; j < m_BoundEnemyCount; j++) {
			boundplayersoul[i][j]->Draw();
		}
	}

	for (int i = 0; i < Soul_Max; i++) {
		for (int j = 0; j < m_BirdEnemyCount; j++) {
			birdplayersoul[i][j]->Draw();
		}
	}

	for (int i = 0; i < Soul_Max; i++) {
		for (int j = 0; j < m_FollowEnemyCount; j++) {
			followplayersoul[i][j]->Draw();
		}
	}

	for (int i = 0; i < Soul_Max; i++) {
		for (int j = 0; j < m_ChestEnemyCount; j++) {
			chestplayersoul[i][j]->Draw();
		}
	}
}