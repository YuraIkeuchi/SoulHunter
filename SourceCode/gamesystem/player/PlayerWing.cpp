#include "PlayerWing.h"
#include "ModelManager.h"
#include "Easing.h"
#include "imgui.h"
//ƒ‚ƒfƒ‹“Ç‚Ýž‚Ý
PlayerWing::PlayerWing() {
	m_fbxModel = ModelManager::GetInstance()->GetFBXModel(ModelManager::PlayerWing);
	IKEFBXObject3d* objwing_ = new IKEFBXObject3d();
	objwing_->Initialize();
	objwing_->SetModel(m_fbxModel);
	objwing_->SetShadeSet(false);
	objwing_->LoadAnimation();
	m_fbxObject.reset(objwing_);

}
//‰Šú‰»
bool PlayerWing::Initialize() {
	m_ChangeColor = true;
	m_AddDisolve = 0.8f;
	m_Scale = { 0.000f,0.000f,0.000f };
	m_Color = { 1.0f,1.0f,0.0f,1.0f };
	return true;
}
//XV
void PlayerWing::Update() {
	//‰H‚Ì“®‚«
	WingMove();
	//‰H‚ÌoŒ»ˆ—
	WingBirth();
	
	m_fbxObject->Update(false, 2,m_Stop);
	m_fbxObject->SetPosition(m_Position);
	m_fbxObject->SetRotation(m_Rotation);
	m_fbxObject->SetScale(m_Scale);
	m_fbxObject->SetColor(m_Color);
	//Fbx_SetParam();
}
//•`‰æ
void PlayerWing::Draw(DirectXCommon* dxCommon) {
	//ImGui::Begin("playerWing");
	//ImGui::Text("X:%f", m_Position.x);
	//ImGui::Text("Y;:%f", m_Position.y);
	//ImGui::Text("Z:%f", m_Position.z);
	////ImGui::SliderFloat("Disolve", &m_Frame, 0.0f, 1.0f);
	//ImGui::End();
	Fbx_Draw(dxCommon);
}
//‰H‚Ì“®‚«
void PlayerWing::WingMove() {
	if (m_WingDir == LeftWing) {
		m_Rotation = { 0.0f,270.0f,0.0f };
	}
	else {
		m_Rotation = { 0.0f,90.0f,0.0f };
	}

	if (m_Animation) {
		m_fbxObject->PlayAnimation(0);
		m_Animation = false;
	}
}
//‰H‚ÌƒfƒBƒ]ƒ‹ƒu
void PlayerWing::WingBirth() {
	if (m_EaseStart) {
		if (m_Frame < m_FrameMax) {
			m_Frame += 0.08f;
		}
		else {
			m_EaseStart = false;
			m_Frame = 0.0f;
		}
	}
	
	m_Scale = {
		Ease(In,Cubic,m_Frame,m_Scale.x,m_AfterScale.x),
		Ease(In,Cubic,m_Frame,m_Scale.y,m_AfterScale.y),
		Ease(In,Cubic,m_Frame,m_Scale.z,m_AfterScale.z)
	};
}
