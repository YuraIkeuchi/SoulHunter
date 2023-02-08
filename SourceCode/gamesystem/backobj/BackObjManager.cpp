#include "BackObjManager.h"
#include "VariableCommon.h"
BackObjManager::BackObjManager() {
	backlight = new BackLight();
	//背景obj
	backlight->Initialize();
}
//CSVを開いている(背景OBJ)
void BackObjManager::OpenObjParam(const int StageNumber) {
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
void BackObjManager::ObjSpecity(const char* vsShaderName) {
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
void BackObjManager::SaveObjParam(const int StageNumber) {
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
void BackObjManager::LoadObjParam(const int StageNumber, Player* player,LightGroup* light) {
	lightgroup = light;
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
		m_BackTorchs[i]->ParticleCheck(StageNumber);
		lightgroup->SetPointLightActive(i + 2, true);
	}
}
//CSVを開いている(共通のOBJ)
void BackObjManager::OpenBackObjAlwaysParam(const int StageNumber) {
	switch (StageNumber)
	{
	case Map1:
		m_AlwaysFile.open("Resources/backalways_param/NormalBackRock.csv");
	case Map2:
		m_AlwaysFile.open("Resources/backalways_param/NormalBackRock.csv");
	case Map3:
		m_AlwaysFile.open("Resources/backalways_param/NormalBackRock.csv");
	case Map4:
		m_AlwaysFile.open("Resources/backalways_param/NormalBackRock.csv");
	case Map5:
		m_AlwaysFile.open("Resources/backalways_param/NormalBackRock.csv");
	case Map6:
		m_AlwaysFile.open("Resources/backalways_param/NormalBackRock.csv");
	case BossMap:
		m_AlwaysFile.open("Resources/backalways_param/BossMapBackRock.csv");
	case TutoRial:
		m_AlwaysFile.open("Resources/backalways_param/NormalBackRock.csv");
	default:
		break;
	}

	m_AlwaysPopcom << m_AlwaysFile.rdbuf();
	m_AlwaysFile.close();
}
//呼び出し
void BackObjManager::LoadBackObjAlways(const int StageNumber) {
	OpenBackObjAlwaysParam(StageNumber);
	//柱
	while (std::getline(m_AlwaysPopcom, m_AlwaysLine)) {
		std::istringstream line_stream(m_AlwaysLine);
		std::string word;
		std::getline(line_stream, word, ',');

		if (word.find("//") == 0) {
			continue;
		}
		if (word.find("BackCount") == 0) {
			std::getline(line_stream, word, ',');
			int quantity = (int)std::atof(word.c_str());
			m_BackAlways_Num = quantity;
			break;
		}
	}

	m_BackAlwaysStartPos.resize(m_BackAlways_Num);
	for (int i = 0; i < m_BackAlways_Num; i++) {
		while (getline(m_AlwaysPopcom, m_AlwaysLine)) {
			std::istringstream line_stream(m_AlwaysLine);

			std::string word;
			//半角スペース区切りで行の先頭文字列を取得
			getline(line_stream, word, ',');
			if (word.find("//") == 0) {
				continue;
			}
			//各コマンド
			if (word.find("POP") == 0) {

				getline(line_stream, word, ',');
				float x = (float)std::atof(word.c_str());
				getline(line_stream, word, ',');
				float y = (float)std::atof(word.c_str());
				getline(line_stream, word, ',');
				float z = (float)std::atof(word.c_str());
				getline(line_stream, word, ',');
				m_BackAlwaysStartPos[i] = { x,y,z };
				break;
			}
		}
	}

	m_BackObjAlways.resize(m_BackAlways_Num);
	for (int i = 0; i < m_BackAlways_Num; i++) {
		m_BackObjAlways[i] = new BackObjAlways();
		m_BackObjAlways[i]->Initialize();
		m_BackObjAlways[i]->SetPosition(m_BackAlwaysStartPos[i]);
	}
}
//更新
void BackObjManager::Update() {
	backlight->Update();
	//柱
	BackObjUpdate(m_BackRocks);
	//岩
	BackObjUpdate(m_BackBoxs);
	//松明
	BackObjUpdate(m_BackTorchs);
	//背景の岩
	for (BackObjAlways* newalways : m_BackObjAlways) {
		if (newalways != nullptr) {
			newalways->Update();
		}
	}
}
//描画
void BackObjManager::Draw(DirectXCommon* dxCommon) {
	BackObjDraw(m_BackRocks, dxCommon);
	BackObjDraw(m_BackBoxs, dxCommon);
	BackObjDraw(m_BackTorchs, dxCommon);
}
//背景OBjの更新
void BackObjManager::BackObjUpdate(std::vector<BackObjCommon*> objs) {
	for (BackObjCommon* backobj : objs) {
		if (backobj != nullptr) {
			backobj->Update();
		}
	}
}
//共通OBjの更新
void BackObjManager::AlwaysDraw(DirectXCommon* dxCommon) {
	backlight->Draw();
	//ステージの描画
	for (BackObjAlways* newalways : m_BackObjAlways) {
		if (newalways != nullptr) {
			newalways->Draw(dxCommon);
		}
	}
}
//背景OBjの描画
void BackObjManager::BackObjDraw(std::vector<BackObjCommon*> objs, DirectXCommon* dxCommon) {
	for (BackObjCommon* backobj : objs) {
		if (backobj != nullptr) {
			backobj->Draw(dxCommon);
		}
	}
}
//背景OBJの設置
void BackObjManager::ObjBirth(int Type, Player* player, XMFLOAT3 pos, XMFLOAT3 rot) {
	//柱
	if (Type == Rock) {
		m_BackObjCount++;
		objedit->RockArgment(m_BackRocks, player, pos, rot);
	}
	//岩
	else if (Type == Box) {
		m_BackObjCount++;
		objedit->BoxArgment(m_BackBoxs, player, pos, rot);
	}
	//松明
	else {
		m_BackObjCount++;
		objedit->TorchArgment(m_BackTorchs, player, pos, rot);
	}
}
//削除
void BackObjManager::DeleteObjPop(int Type) {
	//柱
	if (Type == Rock && m_BackRocks.size() > 0) {
		m_BackRocks.pop_back();
		m_BackObjCount--;
	}
	//岩
	if (Type == Box && m_BackBoxs.size() > 0) {
		m_BackBoxs.pop_back();
		m_BackObjCount--;
	}
	//松明
	if (Type == Torch && m_BackTorchs.size() > 0) {
		m_BackTorchs.pop_back();
		m_BackObjCount--;
	}
}
//要素全削除(背景OBJ)
void BackObjManager::ObjDelete() {
	for (int i = 0; i < m_BackTorch_Num; i++) {
		lightgroup->SetPointLightActive(i + 2, false);
	}
	m_BackRocks.clear();
	m_BackBoxs.clear();
	m_BackTorchs.clear();
	m_BackObjCount = 0;
}
//要素の数合わせ
void BackObjManager::SaveNum() {
	m_BackObj_Num = m_BackObjCount;
}
//ライトのセット
void BackObjManager::LightSet(const int StageNumber, LightGroup* light) {
	lightgroup = light;
	for (BackObjCommon* torch : m_BackTorchs) {
		for (int i = 0; i < m_BackTorch_Num; i++) {
			if (StageNumber != BossMap) {
				lightgroup->SetPointLightActive(i + 2, true);
			}
			else {
				lightgroup->SetPointLightActive(i + 2, false);
			}
			if (torch != nullptr) {
				lightgroup->SetPointLightPos(i + 2, XMFLOAT3({ m_BackTorchs[i]->GetPosition().x, m_BackTorchs[i]->GetPosition().y + 3.0f, m_BackTorchs[i]->GetPosition().z + 3.0f }));
				lightgroup->SetPointLightColor(i + 2, XMFLOAT3(pointLightColor));
				lightgroup->SetPointLightAtten(i + 2, XMFLOAT3(pointLightAtten));
			}
		}
	}

	lightgroup->Update();
}