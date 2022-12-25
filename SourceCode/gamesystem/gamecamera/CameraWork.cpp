#include "CameraWork.h"
#include <Easing.h>
#include  "imgui.h"
CameraWork::CameraWork() {
	m_eyePos = { 0.0f,15.0f,-10.0f };
	m_targetPos = { 0.0f,0.0f,0.0f };
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
	else {
		AppCamera();
	}
	camera->SetEye(m_eyePos);
	camera->SetTarget(m_targetPos);
	camera->Update();
}
//タイトル時のカメラ(回転するような動き)
void CameraWork::TitleCamera() {
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
	//XMFLOAT3 m_PlayerPos = player->GetPosition();
	//XMFLOAT3 bossPos = interboss->GetPosition();
	////フレームでカメラの目標を変更する
	//m_Timer++;
	//if (m_Timer == 10) {
	//	m_Frame = 0.0f;
	//	m_AppCameraNumber = Camera1;
	//}
	////最初のカメラ
	//if (m_AppCameraNumber == No) {
	//	//カメラの位置調整
	//	if (m_PlayerPos.x >= 27.0f && m_PlayerPos.x <= 270.0f) {
	//		m_eyePos.x = m_PlayerPos.x;
	//		m_targetPos.x = m_PlayerPos.x;
	//	}
	//	else {
	//		if (m_PlayerPos.x < 27.0f) {
	//			m_eyePos.x = 27.0f;
	//			m_targetPos.x = 27.0f;
	//		}
	//		else if (m_PlayerPos.x > 270.0f) {
	//			m_eyePos.x = 270.0f;
	//			m_targetPos.x = 270.0f;
	//		}
	//	}
	//	if (m_PlayerPos.y >= -280.0f && m_PlayerPos.y <= -13.5f) {
	//		m_targetPos.y = m_PlayerPos.y;
	//		m_eyePos.y = m_PlayerPos.y;
	//	}
	//	else {
	//		/*	if (m_PlayerPos.y < -280.0f) {
	//				m_targetPos.y = -280.0f;
	//				m_eyePos.y = -280.0f;
	//			}
	//			else if (m_PlayerPos.y > -13.5f) {
	//				m_targetPos.y = -13.5f;
	//				m_eyePos.y = -13.5f;
	//			}*/
	//	}
	//	m_eyePos.z = m_PlayerPos.z - (30.0f - player->GetCameraDistance());
	//	m_targetPos.z = m_PlayerPos.z;
	//}
	////まず左上
	//else if (m_AppCameraNumber == Camera1) {
	//	AppCameraMove({ 158.0f, -100.0f,player->GetPosition().z - 30.0f },
	//		{ 158.0f, -100.0f,player->GetPosition().z },0.008f);
	//}
	////まず右上
	//else if (m_AppCameraNumber == Camera2) {
	//	AppCameraMove({ 240.0f, -100.0f,m_PlayerPos.z - 30.0f },
	//		{ 240.0f, -100.0f,m_PlayerPos.z }, 0.008f);
	//}
	////まず右下
	//else if (m_AppCameraNumber == Camera3) {
	//	AppCameraMove({ 240.0f, -152.0f,m_PlayerPos.z - 30.0f },
	//		{ 240.0f, -152.0f,m_PlayerPos.z }, 0.008f);
	//}
	////真ん中による
	//else if (m_AppCameraNumber == Camera4) {
	//	AppCameraMove({ bossPos.x,  bossPos.y,0.0f },
	//		{ bossPos.x,  bossPos.y,30.0f }, 0.008f);
	//}
	////真ん中引き
	//else if (m_AppCameraNumber == Camera5) {
	//	AppCameraMove({bossPos.x, bossPos.y, m_PlayerPos.z - 30.0f },
	//		{ bossPos.x,  bossPos.y,m_PlayerPos.z }, 0.008f);
	//}
	////ボスを見る
	//else if (m_AppCameraNumber == Camera6) {
	//	AppCameraMove({ m_PlayerPos.x,m_PlayerPos.y,m_PlayerPos.z - 30.0f },
	//		{ m_PlayerPos.x,m_PlayerPos.y,m_PlayerPos.z }, 0.008f);
	//}
	////カメラが戻る
	//else {
	//	m_Frame = 0.0f;
	//	m_AppCameraNumber = No;
	//	m_EndApp = true;
	//}

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
//ImGuiの描画
void CameraWork::ImGuiDraw() {
	ImGui::Begin("CameraWork");
	ImGui::SliderFloat("eyeX", &m_eyePos.x, 360, 0);
	ImGui::SliderFloat("eyeY", &m_eyePos.y, 360, 0);
	ImGui::SliderFloat("eyeZ", &m_eyePos.z, 360, 0);
	ImGui::SliderFloat("targetX", &m_targetPos.x, 360, 0);
	ImGui::SliderFloat("targetY", &m_targetPos.y, 360, 0);
	ImGui::SliderFloat("targetZ", &m_targetPos.z, 360, 0);
	ImGui::Text("%d", m_CameraType);
	ImGui::End();
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
		m_AfterEye = AfterEye;
		m_AfterTarget = AfterTarget;
		m_AppCameraNumber++;
		m_Frame = 0.0f;
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