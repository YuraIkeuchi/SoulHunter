#pragma once
#include "IKEObject3d.h"
#include "IKEModel.h"
#include <memory>
#include <list> // ヘッダファイルインクルード
#include <map>
#include "ParticleTex.h"
#include "IKESprite.h"
struct JsonData;

using namespace std;         //  名前空間指定
class BossEndObj {
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
	void Update();
	void Finalize();
	const void BackDraw();
	const void FrontDraw();

public:
	//gettersetter
	bool GetEnd() { return  m_End; }
	//gettersetter
	int GetEndTimer() { return  m_EndTimer; }

	void SetEnd(bool m_End) { this->m_End = m_End; }
	void SetEndEnd(bool m_EndEnd) { this->m_EndEnd = m_EndEnd; }
	void SetEndStart(bool m_EndStart) { this->m_EndStart = m_EndStart; }
	void SetEndTimer(bool m_EndTimer) { this->m_EndTimer = m_EndTimer; }
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
	//その他変数
	bool m_EndStart = false;//登場スタート
	int m_EndTimer = 0;//時間
	bool m_EndEnd = false;//登場終了
	bool m_End = false;//登場の間はtrue

};