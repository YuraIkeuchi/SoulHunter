#pragma once
#include "Player.h"
#include "InterBoss.h"
#include "DebugCamera.h"
#include "Camera.h"
#include <memory>
#include <list> // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
//ゲームのカメラの動き
class CameraWork {
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	CameraWork();
	void Update(DebugCamera* camera);//更新
	void TitleCamera();//タイトルのカメラ
	void IntroductionCamera();//導入のカメラ
	void NormalCamera();//普通のカメラ(プレイヤーに追従)
	void RightStickCamera();//右スティックで動かすカメラ
	void AppCamera();//ボス登場時のカメラ
	void AppCameraMove(XMFLOAT3 m_AfterEye, XMFLOAT3 m_AfterTarget,float AddFrame);//上のやつの動き
	void ImGuiDraw();//ImGui

	void SetPlayer(Player* player) { this->player.reset(player); }
	void SetInterBoss(InterBoss* interboss) { this->interboss.reset(interboss); }
public:
	//getter setter
	void SetCameraType(int m_CameraType) { this->m_CameraType = m_CameraType; }
	void SetIntroTimer(int m_IntroTimer) { this->m_IntroTimer = m_IntroTimer; }
	int GetCameraNumber() { return  m_AppCameraNumber; }
	bool GetEndApp() { return  m_EndApp; }
	float GetFrame() { return  m_Frame; }
private:
	//クラス
	unique_ptr<Player> player;
	unique_ptr<InterBoss> interboss;
	//イージングの変数
	float m_Frame = 0.0f;
	XMFLOAT3 m_AfterEye = { 0.0f,0.0f,0.0f };
	XMFLOAT3 m_AfterTarget = { 0.0f,0.0f,0.0f };
	//視点座標
	XMFLOAT3 m_eyePos = { 0.0f,0.0f,0.0f };
	//注視点座標
	XMFLOAT3 m_targetPos = { 0.0f,0.0f,0.0f };
	//タイトルのカメラの変数
	//円運動のため
	float m_PI = 3.14f;
	float m_TitleCameraRadius = 0.0f;
	float m_TitleCameraSpeed = 0.0f;
	float m_TitleCameraScale = 80.0f;// LaneNumと一緒に変えること
	float m_TitleCameraCircleX = 0.0f;
	float m_TitleCameraCircleZ = 0.0f;
	//ボスシーンのカメラの動き
	int m_AppCameraNumber = 0;//登場シーンのカメラ番号
	int m_Timer = 0;//タイマー
	bool m_EndApp = false;//登場シーンが終わったか

	//右スティックで動かす物
	float m_MoveCameraY = 0.0f;//カメラの移動量
	float m_AfterMoveCameraY = 0.0f;//カメラの移動量の終着点
	float m_Rightframe = 0.0f;//フレーム
	int m_MoveDir = 0;//動く方向
	bool m_MoveCamera = false;//カメラを動かしているか
	enum MoveDir {
		NoCamera,
		UpCamera,
		DownCamera,
	};
	enum AppCamera {
		No,
		Camera1,
		Camera2,
		Camera3,
		Camera4,
		Camera5,
		Camera6,
		Camera7,
	};
	//カメラのタイプ
	int m_CameraType = 0;
	enum CameraType {
		Title,
		Introduction,
		Normal,
		BossAPP,
	};

	//導入シーン
	int m_IntroTimer = 0;
	bool m_IntEyeStart = false;
	bool m_IntTargetStart = false;
};