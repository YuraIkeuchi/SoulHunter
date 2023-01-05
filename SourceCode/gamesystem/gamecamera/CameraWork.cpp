#include "CameraWork.h"
#include <Easing.h>
#include  "imgui.h"
CameraWork::CameraWork() {
	m_eyePos = { 0.0f,15.0f,-10.0f };
	m_targetPos = { 0.0f,0.0f,0.0f };
	BossEndParticle* endparticle_;
	endparticle_ = new BossEndParticle();
	endparticle_->Initialize();
	endparticle.reset(endparticle_);
}
//更新
void CameraWork::Update(DebugCamera* camera) {
	//カメラがどの動きをするか
	if (m_CameraType == Title) {
		TitleCamera();
	}
	else if (m_CameraType == Introduction) {
		IntroductionCamera();
	}
	else if (m_CameraType == Normal) {
		NormalCamera();
	}
	else if(m_CameraType == BossApp) {
		AppCamera();
	}
	else if(m_CameraType == BossEnd) {
		EndCamera();
	}
	else {
		ClearCamera();
	}
	camera->SetEye(m_eyePos);
	camera->SetTarget(m_targetPos);
	camera->Update();
}
//タイトル時のカメラ(回転するような動き)
void CameraWork::TitleCamera() {
	m_TitleCameraScale = 80.0f;
	m_TitleCameraSpeed += 0.1f;
	//円運動の計算
	m_TitleCameraRadius = m_TitleCameraSpeed * m_PI / 180.0f;
	m_TitleCameraCircleX = cosf(m_TitleCameraRadius) * m_TitleCameraScale;
	m_TitleCameraCircleZ = sinf(m_TitleCameraRadius) * m_TitleCameraScale;
	m_eyePos.x = m_TitleCameraCircleX;
	m_eyePos.z = m_TitleCameraCircleZ;
	m_eyePos.y = 50.0f;
	m_targetPos = { 0.0f,30.0f,0.0f };
}
//導入シーン
void CameraWork::IntroductionCamera() {

	//カメラの位置の処理
	if (m_IntroTimer <= 119) {
		m_eyePos = { 5.0f,10.0f,20.0f };
	}
	else {
		if (m_IntroTimer == 120) {
			m_Frame = 0.0f;
			m_AfterEye = { 0.0f,2.0f,m_eyePos.z };
			m_IntEyeStart = true;
		}

		if (m_IntEyeStart) {
			if (m_Frame < m_FrameMax) {
				m_Frame += 0.005f;
			}
			else {
				m_IntEyeStart = false;
				m_Frame = 0.0f;
			}

			m_eyePos = {
	Ease(In,Cubic,m_Frame,m_eyePos.x,m_AfterEye.x),
	Ease(In,Cubic,m_Frame,m_eyePos.y,m_AfterEye.y),
		Ease(In,Cubic,m_Frame,m_eyePos.z,m_AfterEye.z)
			};
		}
	}

	//注視点の位置
	//最後は見上げる感じになる
	if (m_IntroTimer <= 359) {
		m_targetPos = player->GetPosition();
	}
	else {
		if (m_IntroTimer == 360) {
			m_IntTargetStart = true;
			m_AfterTarget.y = 60.0f;
			m_Frame = 0.0f;
		}

		if (m_IntTargetStart) {
			if (m_Frame < m_FrameMax) {
				m_Frame += 0.005f;
			}
			else {
				m_IntTargetStart = false;
				m_Frame = 0.0f;
			}

			m_targetPos.y = Ease(In, Cubic, m_Frame, m_targetPos.y, m_AfterTarget.y);
		}
	}
}
//通常時のカメラ(プレイヤーについてくる)
void CameraWork::NormalCamera() {
	RightStickCamera();
	XMFLOAT3 m_PlayerPos = player->GetPosition();
	//カメラの位置調整(端まで行くとカメラが止まる)
	if (m_PlayerPos.x >= 27.0f && m_PlayerPos.x <= 270.0f) {
		m_eyePos.x = m_PlayerPos.x;
		m_targetPos.x = m_PlayerPos.x;
	}
	else {
		if (m_PlayerPos.x < 27.0f) {
			m_eyePos.x = 27.0f;
			m_targetPos.x = 27.0f;
		}
		else if (m_PlayerPos.x > 270.0f) {
			m_eyePos.x = 270.0f;
			m_targetPos.x = 270.0f;
		}
	}
	if (m_PlayerPos.y >= -280.0f && m_PlayerPos.y <= -13.5f) {
		m_targetPos.y = m_PlayerPos.y + m_MoveCameraY;
		m_eyePos.y = m_PlayerPos.y + m_MoveCameraY;
	}
	else {
		if (m_PlayerPos.y < -280.0f) {
			m_targetPos.y = -280.0f + m_MoveCameraY;
			m_eyePos.y = -280.0f + m_MoveCameraY;
		}
		else if (m_PlayerPos.y > -13.5f) {
			m_targetPos.y = -13.5f + m_MoveCameraY;
			m_eyePos.y = -13.5f + m_MoveCameraY;
		}
	}
	
	m_eyePos.z = m_PlayerPos.z - (30.0f - player->GetCameraDistance());
	m_targetPos.z = m_PlayerPos.z;
}
//ボス登場時のカメラ
void CameraWork::AppCamera() {
	if (m_AppTimer <= 710) {
		m_AppTimer++;
	}
	//カメラを移動する
	if (m_AppCameraNumber == AppNo) {
		if (m_AppTimer == 1) {
			m_eyePos = { 10.0f,20.0f,10.0f };
			m_targetPos = { 0.0f,5.0f,0.0f };
		}

		if (m_AppTimer == 10) {
			m_Frame = 0.0f;
			m_AppCameraNumber = AppCamera1;
		}
	}
	else if (m_AppCameraNumber == AppCamera1) {
		AppCameraMove({ -10.0f, 20.0f,10.0f },
					{ 0.0f,5.0f,0.0f },0.0025f);

		if (m_AppTimer == 200) {
			m_Frame = 0.0f;
			m_AppCameraNumber = AppCamera2;
		}
	}

	else if (m_AppCameraNumber == AppCamera2) {
		AppCameraMove({ 0.0f, 10.0f,-20.0f },
			{ 0.0f,18.0f,0.0f }, 0.0025f);

		if (m_AppTimer == 700) {
			m_Frame = 0.0f;
			m_AppCameraNumber = AppCamera3;
		}
	}
	else if (m_AppCameraNumber == AppCamera3) {
		AppCameraMove({ 0.0f, 22.0f,0.0f },
			{ 0.0f,27.0f,20.0f }, 0.008f);
	}
}
//ボス終了時のカメラ(回転するような動き)
void CameraWork::EndCamera() {
	if (m_EndTimer <= 800) {
		m_EndTimer++;
	}

	if (m_EndCameraNumber == EndNo) {
		if (m_EndTimer == 1) {
			m_EndCameraSpeed = 300.0f;
			m_EndCameraScale = 25.0f;
			m_AfterEndCameraSpeed = 635.0f;
			m_AfterEndCameraScale = m_EndCameraScale;
			m_Frame = 0.0f;
			m_EndCameraNumber = EndCamera1;
		}
	}
	else if (m_EndCameraNumber == EndCamera1) {
		EndCameraMove(m_AfterEndCameraSpeed, m_AfterEndCameraScale, 0.001f);
		if (m_EndTimer == 520) {
			m_AfterEndCameraSpeed = m_EndCameraSpeed;
			m_AfterEndCameraScale = 80.0f;
			m_Frame = 0.0f;
			m_EndCameraNumber = EndCamera2;
		}
	}
	else if (m_EndCameraNumber == EndCamera2) {
		m_ParticleCount++;
		//徐々にパーティクルを出す
		if (m_EndCameraScale < 50.0f) {
			m_TargetCount = 6;
			if (m_ParticleCount > 6) {
				m_ParticleCount = 0;
			}
		}
		else {
			m_TargetCount = 2;
			if (m_ParticleCount > 2) {
				m_ParticleCount = 0;
			}
		}
	
		EndCameraMove(m_AfterEndCameraSpeed, m_AfterEndCameraScale, 0.0025f);
	}
	//円運動の計算
	m_EndCameraRadius = m_EndCameraSpeed * m_PI / 180.0f;
	m_EndCameraCircleX = cosf(m_EndCameraRadius) * m_EndCameraScale;
	m_EndCameraCircleZ = sinf(m_EndCameraRadius) * m_EndCameraScale;
	m_eyePos.x = m_EndCameraCircleX;
	m_eyePos.z = m_EndCameraCircleZ + 20.0f;
	m_eyePos.y = 10.0f;
	m_targetPos = {0.0f,8.0f,20.0f};

	endparticle->ObjUpdate({ m_eyePos.x,m_eyePos.y + 2.0f,m_eyePos.z + 3.0f }, m_ParticleCount, m_TargetCount);
}
//クリア時のカメラ
void CameraWork::ClearCamera() {
	m_ClearTimer++;
	//if (m_ClearTimer == 1) {
	//
	//}

	//if (m_ClearTimer <= 200 && m_ClearTimer >= 2) {
	//	m_eyePos.z += 0.2f;
	//}
	m_eyePos = { 5.0f,player->GetPosition().y + 5.0f,player->GetPosition().z + 7.0f };
	m_targetPos = player->GetPosition();
}
//ImGuiの描画
void CameraWork::ImGuiDraw() {
	ImGui::Begin("CameraWork");
	ImGui::SliderFloat("m_eyePos.x", &m_eyePos.x, 360, -360);
	ImGui::SliderFloat("m_eyePos.y", &m_eyePos.y, 360, -360);
	ImGui::SliderFloat("m_eyePos.z", &m_eyePos.z, 360, -360);
	ImGui::SliderFloat("m_targetPos.x", &m_targetPos.x, 360, -360);
	ImGui::SliderFloat("m_targetPos.y", &m_targetPos.y, 360, -360);
	ImGui::SliderFloat("m_targetPos.z", &m_targetPos.z, 360, -360);
	ImGui::End();
}
void CameraWork::EndDraw() {
	endparticle->Draw();
}
//右のスティック
void CameraWork::RightStickCamera() {
	Input* input = Input::GetInstance();
	//右スティックでカメラの上下移動を可能にする
	if ((input->RightTiltStick(input->Up) || input->RightTiltStick(input->Down)) && (player->GetAddPower() == 0.0f) && (player->GetVelosity() == 0.0f)) {
		if (input->RightTiltStick(input->Up)) {
			if (m_MoveDir == NoCamera) {
				m_MoveCamera = true;
				m_Rightframe = 0.0f;
				m_AfterMoveCameraY = 15.0f;
				m_MoveDir = UpCamera;
			}
		}
		if (input->RightTiltStick(input->Down)) {
			if (m_MoveDir == NoCamera) {
				m_MoveCamera = true;
				m_Rightframe = 0.0f;
				m_AfterMoveCameraY = -15.0f;
				m_MoveDir = DownCamera;
			}
		}
	}
	else {
		if (m_MoveDir != NoCamera) {
			m_MoveCamera = true;
			m_Rightframe = 0.0f;
			m_AfterMoveCameraY = 0.0f;
			m_MoveDir = NoCamera;
		}
	}

	if (m_MoveCamera) {
		if (m_Rightframe < 1.0f) {
			m_Rightframe += 0.05f;
		}
		else {
			m_Rightframe = 0.0f;
			m_MoveCamera = false;
		}
		m_MoveCameraY = Ease(In, Cubic, m_Rightframe, m_MoveCameraY, m_AfterMoveCameraY);
	}
}
//ボスシーンカメラの動き
void CameraWork::AppCameraMove(XMFLOAT3 AfterEye, XMFLOAT3 AfterTarget, float AddFrame) {
	if (m_Frame < 1.0f)
	{
		m_Frame += AddFrame;
	}
	else {
		m_Frame = 1.0f;
	}

	m_eyePos = {
Ease(In,Cubic,m_Frame,m_eyePos.x,AfterEye.x),
Ease(In,Cubic,m_Frame,m_eyePos.y,AfterEye.y),
	Ease(In,Cubic,m_Frame,m_eyePos.z,AfterEye.z)
	};

	m_targetPos = {
Ease(In,Cubic,m_Frame,m_targetPos.x,AfterTarget.x),
Ease(In,Cubic,m_Frame,m_targetPos.y,AfterTarget.y),
	Ease(In,Cubic,m_Frame,m_targetPos.z,AfterTarget.z)
	};
}
//ボス終了シーンのカメラの動き
void CameraWork::EndCameraMove(float AfterSpeed, float AfterScale, float AddFrame) {
	if (m_Frame < 1.0f)
	{
		m_Frame += AddFrame;
	}
	else {
		m_AfterEndCameraSpeed = AfterSpeed;
		m_AfterEndCameraScale = AfterScale;
		m_Frame = 1.0f;
	}

	m_EndCameraSpeed = Ease(In, Cubic, m_Frame, m_EndCameraSpeed, m_AfterEndCameraSpeed);
	m_EndCameraScale = Ease(In, Cubic, m_Frame, m_EndCameraScale, m_AfterEndCameraScale);
}