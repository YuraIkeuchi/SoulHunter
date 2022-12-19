#include"ModelManager.h"
#include "IKEFbxLoader.h"

std::map<ModelManager::ModelName, IKEModel*> ModelManager::model;
std::map<ModelManager::FBXName, IKEFBXModel*>  ModelManager::fbxModel;

ModelManager* ModelManager::GetInstance() {
	static ModelManager instans;
	return &instans;
}
//ƒ‚ƒfƒ‹“Ç‚Ýž‚Ý
void ModelManager::Initialize() {
	LoadModel(ThornEnemy, "thornenemy");
	LoadModel(ThornObj, "thornobj");
	LoadModel(FirstBoss, "firstboss");
	LoadModel(NormalBlock, "RockBlock");
	LoadModel(InBlock, "RockBlock2");
	LoadModel(Toge, "Toge");
	LoadModel(Back, "skydome");
	LoadModel(Ground, "ground");
	LoadModel(Skydome, "skydome");
	LoadModel(BackRock, "CaveRock");
	LoadModel(BackBox, "BackBox");
	LoadModel(BackTorch, "Torch");
	LoadModel(StageBackRock, "BackRock");
	LoadModel(Save, "Save");
	LoadModel(Board, "kannbann");
	LoadModel(Particle, "UVSphere");
	LoadModel(OpenChest, "OpenChest");
	LoadModel(CloseChest, "CloseChest");
	LoadModel(Sword, "Sword");
	LoadFBXModel(NormalEnemy, "MooshEnemy");
	LoadFBXModel(BirdEnemy, "bat_move");
	LoadFBXModel(WingEnemy, "RabbitFBX");
	LoadFBXModel(PlayerFBX, "PlayerFBXNew");
	LoadFBXModel(PlayerWing, "WingFBX");
}

void ModelManager::Finalize() {
	model.clear();
	fbxModel.clear();
}

void ModelManager::LoadModel(const ModelName modelName, std::string fileName) {
	model[modelName] = new IKEModel();
	model[modelName] = IKEModel::LoadFromOBJ(fileName, true);
}
void ModelManager::LoadFBXModel(const FBXName modelName, std::string fileName) {
	fbxModel[modelName] = new IKEFBXModel();
	fbxModel[modelName] = IKEFbxLoader::GetInstance()->LoadModelFromFile(fileName);
}

