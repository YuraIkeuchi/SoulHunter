#pragma once
#include "IKEObject3d.h"
#include "IKEModel.h"
#include <map>
#include <array>   
#include <memory>
#include <list>
#include "IKESprite.h"
#include "ParticleTex.h"
struct JsonData;

using namespace std;         //  名前空間指定
class BossStagObj {
public:
protected:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void Initialize();
	void AppUpdate();
	void EndUpdate();
	void Finalize();
	const void BackDraw();
	const void FrontDraw();

public:
	//gettersetter
	bool GetApp() { return  m_App; }

	int GetAppTimer() { return  m_AppTimer; }
	int GetEndTimer() { return  m_EndTimer; }

	void SetApp(bool m_App) { this->m_App = m_App; }
	void SetEndApp(bool m_EndApp) { this->m_EndApp = m_EndApp; }
	void SetAppStart(bool m_AppStart) { this->m_AppStart = m_AppStart; }
	void SetAppTimer(bool m_AppTimer) { this->m_AppTimer = m_AppTimer; }
private:
	//絶対に必要なOBJ
	IKEModel* modelskydome = nullptr;
	unique_ptr <IKEObject3d> objskydome;
	//Json用
	JsonData* jsonData = nullptr;
	std::map<std::string, IKEModel*> models;
	std::vector<IKEObject3d*> objects;
	//スプライト
	array<unique_ptr<IKESprite>, 2> CurtainSprite;
	unique_ptr<IKESprite> SkipSprite;
	unique_ptr<ParticleTex> particletex = nullptr;
	//その他変数
	bool m_AppStart = false;//登場スタート
	int m_AppTimer = 0;//時間
	int m_EndTimer = 0;//時間
	bool m_EndApp = false;//登場終了
	bool m_App = false;//登場の間はtrue
	int m_ParticleCount = 0;//パーティクルの生成までのフレーム
	
};