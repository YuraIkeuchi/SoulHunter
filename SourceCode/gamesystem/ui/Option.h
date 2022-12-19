#pragma once
#include "IKESprite.h"
#include "VolumManager.h"
#include "Audio.h"
#include "AllArray.h"
#include <array>   
#include <memory> 
#include <list> // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
//オプション画面のクラス
class Option {
public:
	Option();
	void Initialize();//初期化
	void Update();//更新
	void Finalize();//解放
	const void Draw();//描画
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	//getter
	bool GetReturnOption() { return m_ReturnOption; }
	bool GetVolumChange() { return m_VolumChange; }
	//setter
	void SetReturnOption(bool m_ReturnOption) { this->m_ReturnOption = m_ReturnOption; }
	void SetVolumChange(bool m_VolumChange) { this->m_VolumChange = m_VolumChange; }
	void SetChangeColorType(int m_ColorChangeType) { this->m_ColorChangeType = m_ColorChangeType; }
private:
	//クラス
	//スプライト
	array<unique_ptr<IKESprite>, Option_Max> OptionSprite;
	array<unique_ptr<IKESprite>, Option_Max> VolumBarSprite;
	//変数
	bool m_ReturnOption = false;//オプションメニューを閉じる
	int VolumSelect = 0;//SEかBGMか
	enum VolumSelect {
		BGM,
		SE,
	};
	//音量
	float m_BGMVolum;
	float m_SEVolum;
	bool m_VolumChange = false;
	
	//スプライトの変数
	array<XMFLOAT2,Option_Max> VolumSpriteSize;
	XMFLOAT4 m_OptionColor = { 1.0f,1.0f,1.0f,0.0f };
	int m_ColorChangeType = 0;
	enum ChangeType {
		No,
		Add,
		Sub,
	};
};