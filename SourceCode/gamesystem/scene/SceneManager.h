#pragma once
#include "BaseScene.h"
#include "AbstractSceneFactory.h"
#include <string>

//�V�[���Ǘ�
class SceneManager
{
public:
	static SceneManager* GetInstance();
	//�X�V
	void Update(DirectXCommon* dxCommon);
	/// �`��
	void Draw(DirectXCommon* dxCommon);
	//�J��
	void Finalize();

public:
	//���V�[���\��
	void ChangeScene(const std::string& sceneName);

	void SetSceneFactory(AbstractSceneFactory* sceneFactory) { sceneFactory_ = sceneFactory; }

private:
	//���̃V�[��
	BaseScene* scene_ = nullptr;
	//���̃V�[��
	BaseScene* nextScene_ = nullptr;

	AbstractSceneFactory* sceneFactory_ = nullptr;

	~SceneManager() = default;
	SceneManager() = default;
	SceneManager(const SceneManager&) = delete;
	void operator =(const SceneManager&) = delete;
};