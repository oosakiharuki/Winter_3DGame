//#include<Windows.h>//winapp
#include <cstdint>
//#include <string>
#include<format>

#include<cassert>

#include <dxgidebug.h>

//#include <dxcapi.h>





#include"externals/imgui/imgui.h"
#include"externals/imgui/imgui_impl_dx12.h"
#include"externals/imgui/imgui_impl_win32.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#include "MyMath.h"
using namespace MyMath;

#pragma comment(lib,"dxguid.lib")


#pragma comment(lib,"dxcompiler.lib")

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

#include"GameManager.h"

//Windowsアプリのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	//旧WinApp
	D3DResourceLeakChecker leakCheck;

	WinApp* winApp_ = nullptr;

	winApp_ = new WinApp();
	winApp_->Initialize();

	DirectXCommon* dxCommon = nullptr;

	dxCommon = new DirectXCommon();
	dxCommon->SetWinApp(winApp_);
	dxCommon->Initialize();

	Input* input_ = nullptr;
	input_ = new Input();
	input_->Initialize(winApp_);

	SrvManager* srvManager = nullptr;
	srvManager = new SrvManager();
	srvManager->Initialize(dxCommon);


	TextureManager::GetInstance()->Initialize(dxCommon, srvManager);

	SpriteCommon* spriteCommon = nullptr;
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);


	ModelManager::GetInstance()->Initialize(dxCommon);


	Object3dCommon* object3dCommon = nullptr;
	object3dCommon = new Object3dCommon();
	object3dCommon->Initialize(dxCommon);

	ModelCommon* modelCommon = nullptr;
	modelCommon = new ModelCommon();
	modelCommon->Initialize(dxCommon);



	GameManager* gameScene = nullptr;
	
	gameScene = new GameManager(spriteCommon,object3dCommon, input_);
	gameScene->Initialize();

	//描画させるもの
	bool IsSphere = true;
	bool IsModel[2] = {true,true};
	bool IsSprite = true;

	//ウィンドウの×ボタンが押されるまでループ
	while (true) {
		if (winApp_->ProcessMessage()) {
			break;//whileを抜ける
		}
		else {
			//ゲームの処理

			gameScene->Update();
			

			ImGui_ImplDX12_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();


			//開発用UIの処理
			//ImGui::ShowDemoWindow();

			//ImGuiの内部コマンド
			ImGui::Render();

			//描画開始
			dxCommon->ProDraw();
			
			gameScene->Draw();

			//描画終了
			dxCommon->PostDraw();
		}
	}



	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();


	delete input_;
	winApp_->Finalize();

	delete winApp_;
	winApp_ = nullptr;

	TextureManager::GetInstance()->Finalize();
	ModelManager::GetInstance()->Finalize();

	delete dxCommon;


	delete srvManager;

	delete spriteCommon;

	delete object3dCommon;

	delete modelCommon;

	delete gameScene;

	return 0;
}