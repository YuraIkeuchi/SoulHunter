#include "BackObjManager.h"
#include "VariableCommon.h"
BackObjManager::BackObjManager() {
	backlight = new BackLight();
	//�w�iobj
	backlight->Initialize();
}
//CSV���J���Ă���(�w�iOBJ)
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
//CSV�w��
void BackObjManager::ObjSpecity(const char* vsShaderName) {
	//���ʂ̒�
	std::ofstream normalofs(vsShaderName);  // �t�@�C���p�X���w�肷��
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

	//��
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
	//����
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
//CSV�ɏ�������ł���
void BackObjManager::SaveObjParam(const int StageNumber) {
	//�}�b�v1
	if (StageNumber == Map1) {
		ObjSpecity("Resources/backobj_param/BackObj/FirstMapBackObj.csv");
	}
	//�}�b�v2
	else if (StageNumber == Map2) {
		//���ʂ̓G
		ObjSpecity("Resources/backobj_param/BackObj/SecondMapBackObj.csv");  // �t�@�C���p�X���w�肷��
	}
	//�}�b�v3
	else if (StageNumber == Map3) {
		//���ʂ̓G
		ObjSpecity("Resources/backobj_param/BackObj/ThirdMapBackObj.csv");  // �t�@�C���p�X���w�肷��
	}
	//�}�b�v4
	else if (StageNumber == Map4) {
		//���ʂ̓G
		ObjSpecity("Resources/backobj_param/BackObj/FourthMapBackObj.csv");  // �t�@�C���p�X���w�肷��
	}
	//�}�b�v5
	else if (StageNumber == Map5) {
		//���ʂ̓G
		ObjSpecity("Resources/backobj_param/BackObj/FifthMapBackObj.csv");  // �t�@�C���p�X���w�肷��
	}
	//�}�b�v6
	else if (StageNumber == Map6) {
		//���ʂ̓G
		ObjSpecity("Resources/backobj_param/BackObj/SixMapBackObj.csv");  // �t�@�C���p�X���w�肷��
	}
	else if (StageNumber == TutoRial) {
		//���ʂ̓G
		ObjSpecity("Resources/backobj_param/BackObj/TutorialBackObj.csv");  // �t�@�C���p�X���w�肷��
	}
}
//CSV����l��ǂݍ���ł���(Obj)
void BackObjManager::LoadObjParam(const int StageNumber, Player* player,LightGroup* light) {
	lightgroup = light;
	OpenObjParam(StageNumber);
	//�w�iObj
	//��
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

	//��
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

	//����
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
//CSV���J���Ă���(���ʂ�OBJ)
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
//�Ăяo��
void BackObjManager::LoadBackObjAlways(const int StageNumber) {
	OpenBackObjAlwaysParam(StageNumber);
	//��
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
			//���p�X�y�[�X��؂�ōs�̐擪��������擾
			getline(line_stream, word, ',');
			if (word.find("//") == 0) {
				continue;
			}
			//�e�R�}���h
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
//�X�V
void BackObjManager::Update() {
	backlight->Update();
	//��
	BackObjUpdate(m_BackRocks);
	//��
	BackObjUpdate(m_BackBoxs);
	//����
	BackObjUpdate(m_BackTorchs);
	//�w�i�̊�
	for (BackObjAlways* newalways : m_BackObjAlways) {
		if (newalways != nullptr) {
			newalways->Update();
		}
	}
}
//�`��
void BackObjManager::Draw(DirectXCommon* dxCommon) {
	BackObjDraw(m_BackRocks, dxCommon);
	BackObjDraw(m_BackBoxs, dxCommon);
	BackObjDraw(m_BackTorchs, dxCommon);
}
//�w�iOBj�̍X�V
void BackObjManager::BackObjUpdate(std::vector<BackObjCommon*> objs) {
	for (BackObjCommon* backobj : objs) {
		if (backobj != nullptr) {
			backobj->Update();
		}
	}
}
//����OBj�̍X�V
void BackObjManager::AlwaysDraw(DirectXCommon* dxCommon) {
	backlight->Draw();
	//�X�e�[�W�̕`��
	for (BackObjAlways* newalways : m_BackObjAlways) {
		if (newalways != nullptr) {
			newalways->Draw(dxCommon);
		}
	}
}
//�w�iOBj�̕`��
void BackObjManager::BackObjDraw(std::vector<BackObjCommon*> objs, DirectXCommon* dxCommon) {
	for (BackObjCommon* backobj : objs) {
		if (backobj != nullptr) {
			backobj->Draw(dxCommon);
		}
	}
}
//�w�iOBJ�̐ݒu
void BackObjManager::ObjBirth(int Type, Player* player, XMFLOAT3 pos, XMFLOAT3 rot) {
	//��
	if (Type == Rock) {
		m_BackObjCount++;
		objedit->RockArgment(m_BackRocks, player, pos, rot);
	}
	//��
	else if (Type == Box) {
		m_BackObjCount++;
		objedit->BoxArgment(m_BackBoxs, player, pos, rot);
	}
	//����
	else {
		m_BackObjCount++;
		objedit->TorchArgment(m_BackTorchs, player, pos, rot);
	}
}
//�폜
void BackObjManager::DeleteObjPop(int Type) {
	//��
	if (Type == Rock && m_BackRocks.size() > 0) {
		m_BackRocks.pop_back();
		m_BackObjCount--;
	}
	//��
	if (Type == Box && m_BackBoxs.size() > 0) {
		m_BackBoxs.pop_back();
		m_BackObjCount--;
	}
	//����
	if (Type == Torch && m_BackTorchs.size() > 0) {
		m_BackTorchs.pop_back();
		m_BackObjCount--;
	}
}
//�v�f�S�폜(�w�iOBJ)
void BackObjManager::ObjDelete() {
	for (int i = 0; i < m_BackTorch_Num; i++) {
		lightgroup->SetPointLightActive(i + 2, false);
	}
	m_BackRocks.clear();
	m_BackBoxs.clear();
	m_BackTorchs.clear();
	m_BackObjCount = 0;
}
//�v�f�̐����킹
void BackObjManager::SaveNum() {
	m_BackObj_Num = m_BackObjCount;
}
//���C�g�̃Z�b�g
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