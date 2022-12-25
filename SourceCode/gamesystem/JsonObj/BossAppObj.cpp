#include "BossAppObj.h"
#include "ModelManager.h"
#include "imgui.h"
#include "JsonLoader.h"
using namespace DirectX;
//初期化
void BossAppObj::Initialize() {
	//ステージ背景
	modelskydome = ModelManager::GetInstance()->GetModel(ModelManager::Back);
	IKEObject3d* objskydome_ = new IKEObject3d();
	objskydome_ = IKEObject3d::Create();
	objskydome_->SetModel(modelskydome);
	objskydome_->SetPosition({ 0, 0, -30 });
	objskydome_->SetScale({ 4.0f,4.0f,4.0f });
	objskydome.reset(objskydome_);

	jsonData = JsonLoader::LoadFile("Title");

	//リスポーン位置
	for (auto& objectData : jsonData->objects) {
		if (objectData.GimmickName == "NoGimmick") {
			// ファイル名から登録済みモデルを検索
			IKEModel* model = IKEModel::LoadFromOBJ(objectData.fileName, true);
			decltype(models)::iterator it = models.find(objectData.fileName);
			if (it != models.end()) {
				model = it->second;
			}

			// モデルを指定して3Dオブジェクトを生成
			IKEObject3d* newObject = IKEObject3d::Create();
			newObject->SetModel(model);
			XMFLOAT3 Startpos;

			// 座標
			DirectX::XMStoreFloat3(&Startpos, objectData.translation);

			newObject->SetPosition(Startpos);

			// 回転角
			DirectX::XMFLOAT3 rot;
			DirectX::XMStoreFloat3(&rot, objectData.rotation);
			newObject->SetRotation(rot);

			// 座標
			DirectX::XMFLOAT3 scale;
			DirectX::XMStoreFloat3(&scale, objectData.scaling);
			newObject->SetScale(scale);

			newObject->SetTiling(30.0f);
			// 配列に登録
			objects.push_back(newObject);
		}
	}
}
//更新
void BossAppObj::Update() {
	//pos = player->GetPosition();
	//ボス登場フラグが立ったらタイマーが動く
	if (m_AppStart && !m_EndApp) {
		//登場の間はtrue
		m_App = true;
		m_AppTimer++;
		//一定フレームでフラグ終了
		if (m_AppTimer == 400) {
			m_App = false;
			m_AppStart = false;
			m_EndApp = true;
		}
	}
	
	//Json用
	for (auto& object : objects) {
		object->Update();
	}

}
//前面描画
const void BossAppObj::FrontDraw() {
}
//背景描画
const void BossAppObj::BackDraw() {
	ImGui::Begin("BossApp");
	ImGui::Text("m_App:%d", m_App);
	ImGui::Text("m_AppTimer:%d", m_AppTimer);
	ImGui::Text("m_End:%d", m_EndApp);
	ImGui::Text("m_AppStart:%d", m_AppStart);
	ImGui::End();
	//Json用
	for (auto& object : objects) {
		object->Draw();
	}
	//objskydome->Draw();
}
//解放
void BossAppObj::Finalize() {

}