#include "EditorScene.h"
#include "Audio.h"
#include "SceneManager.h"
#include "imgui.h"
#include "VariableCommon.h"
#include "PlayerSkill.h"
#include "ParticleEmitter.h"
//‰Šú‰»
void EditorScene::Initialize(DirectXCommon* dxCommon)
{
	dxCommon->SetFullScreen(false);
	//‹¤’Ê‚Ì‰Šú‰»
	BaseInitialize(dxCommon);
	actor = new EditorSceneActor();
	actor->Initialize(dxCommon,camera,lightGroup);
}
//XV
void EditorScene::Update(DirectXCommon* dxCommon)
{
	actor->Update(dxCommon, camera, lightGroup);
}
//•`‰æ
void EditorScene::Draw(DirectXCommon* dxCommon)
{
	actor->Draw(dxCommon);
}
//‰ð•ú
void EditorScene::Finalize()
{
	actor->Finalize();
}
