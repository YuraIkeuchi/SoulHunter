#pragma once
#include "IKEObject3d.h"
#include"IKEModel.h"
#include "VariableCommon.h"
#include "ObjCommon.h"
#include <memory>
//wiÌâÈÇ¤ÊwiÌNX
class BackObjAlways :
	public ObjCommon {
protected:
	// DirectX::ðÈª
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	BackObjAlways();

	bool Initialize() override;//ú»
	/// <summary>
	/// t[
	/// </summary>
	void Update() override;

	/// <summary>
	/// `æ
	/// </summary>
	void Draw(DirectXCommon* dxCommon) override;
private:
	//è
	static const int BackRock_Max = 11;//OBJÌ
private:
	
};