#pragma once

#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include<wrl.h>
#include <d3dx12.h>
#include<cstdlib>
#include <imgui.h>
#include "WinApp.h"

//DirectX汎用
class DirectXCommon
{
	//定数
public:
	static const int normalwindow_width = 1280;
	static const int normalwindow_height = 720;

	static const int smallwindow_width = 1000;
	static const int smallwindow_height = 500;
private:
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	static DirectXCommon* GetInstance();
	void ClearDepthBuffer();
	void Finalize();
	//初期化
	void Initialize(WinApp* winApp);

	//描画前処理
	void PreDraw();

	//描画後処理
	void PostDraw();

	//デバイスの初期化
	bool InitializeDevice();


	//スワップチェーンの生成
	bool CreateSwapChain();


	//コマンド関連の初期化
	bool InitializeCommand();

	//レンダーターゲット生成
	bool InitializeRenderTargetView();

	//深度バッファ生成
	bool InitializeDepthBuffer();

	//フェンス生成
	bool CreateFence();
	//Imgui初期化
	bool InitImgui();

	void WindowImGuiDraw();

	ID3D12Device* GetDev() { return dev.Get(); }

	ID3D12GraphicsCommandList* GetCmdList() { return cmdList.Get(); }
public:
	const bool& GetFullScreen() { return  FullScreen; }

	void SetFullScreen(const bool& FullScreen) { this->FullScreen = FullScreen; }
private:
	//メンバ変数
		// Direct3D関連
	ComPtr<IDXGIFactory6> dxgiFactory;
	ComPtr<ID3D12Device> dev;
	ComPtr<ID3D12GraphicsCommandList> cmdList;
	ComPtr<ID3D12CommandAllocator> cmdAllocator;
	ComPtr<ID3D12CommandQueue> cmdQueue;
	ComPtr<IDXGISwapChain4> swapchain;
	std::vector<ComPtr<ID3D12Resource>> backBuffers;
	ComPtr<ID3D12Resource> depthBuffer;
	ComPtr<ID3D12DescriptorHeap> rtvHeaps;
	ComPtr<ID3D12DescriptorHeap> dsvHeap;
	ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;
	WinApp* winApp = nullptr;
	ComPtr<ID3D12DescriptorHeap> imguiHeap;
	FLOAT m_This_Like_window_x = 1280;
	FLOAT m_This_Like_window_y = 720;
	FLOAT m_This_Like_save_x = 1000;
	FLOAT m_This_Like_save_y = 500;
	bool FullScreen = true;
};