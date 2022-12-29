#pragma once
#include <string>
#include "IKEModel.h"
#include <map>
#include <IKEFBXModel.h>

class ModelManager final {
private:
	ModelManager() = default;
	~ModelManager() = default;
	ModelManager(const ModelManager& r) = default;
	ModelManager& operator= (const ModelManager& r) = default;

public:
	//OBJ�̖��O
	enum ModelName {
		ThornEnemy,
		ThornObj,
		FirstBoss,
		NormalBlock,
		InBlock,
		Toge,
		Ground,
		Skydome,
		BackRock,
		BackBox,
		BackTorch,
		StageBackRock,
		Save,
		Board,
		Particle,
		OpenChest,
		CloseChest,
		Sword,
	};
	//FBX�̖��O
	enum FBXName {
		NormalEnemy,
		BoundEnemy,
		PlayerFBX,
		BossFBX,
		BirdEnemy,
		PlayerWing,
	};

public:
	static ModelManager* GetInstance();		//�擾�p

	void Initialize();//������
	void Finalize();//���
	//�ǂݍ���
	void LoadModel(const ModelName modelName, std::string fileName);
	void LoadFBXModel(const FBXName modelName, std::string fileName);
	IKEModel* GetModel(ModelName modelName) { return model[modelName]; }
	IKEFBXModel* GetFBXModel(FBXName FBXName) { return fbxModel[FBXName]; }
private:
	static std::map<ModelName, IKEModel*> model;	//���f���i�[�}�b�v
	static std::map<FBXName, IKEFBXModel*> fbxModel;
};