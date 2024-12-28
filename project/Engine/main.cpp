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

#include "Input.h"
//#include "WinApp.h"
#include "DirectXCommon.h"
#include "D3DResorceLeakChecker.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "Object3d.h"
#include "Object3dCommon.h"
#include "Model.h"
#include "ModelManager.h"
#include "SrvManager.h"

#include "Player.h"
#include "Enemy.h"

//Windowsアプリのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	//旧WinApp
	D3DResourceLeakChecker leakCheck;

	WinApp* winApp_ = nullptr;

	winApp_ = new WinApp();
	winApp_->Initialize();

	Input* input_;
	input_ = new Input();
	//GetHInstance()GetHwnd()を入れず直接winAppのクラスのものを使える
	input_->Initialize(winApp_);


	//ShowWindow(hwnd, SW_SHOW);

	DirectXCommon* dxCommon = nullptr;

	dxCommon = new DirectXCommon();
	dxCommon->SetWinApp(winApp_);
	dxCommon->Initialize();


	SrvManager* srvManager = nullptr;
	srvManager = new SrvManager();
	srvManager->Initialize(dxCommon);




	TextureManager::GetInstance()->Initialize(dxCommon,srvManager);

	SpriteCommon* spriteCommon = nullptr;
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);


	ModelManager::GetInstance()->Initialize(dxCommon);
	ModelManager::GetInstance()->LoadModel("plane.obj");
	ModelManager::GetInstance()->LoadModel("axis.obj");
	ModelManager::GetInstance()->LoadModel("player.obj");
	ModelManager::GetInstance()->LoadModel("bullet.obj");


	Object3dCommon* object3dCommon = nullptr;
	object3dCommon = new Object3dCommon();
	object3dCommon->Initialize(dxCommon);

	Camera* camera = new Camera();
	Vector3 cameraRotate = { 0.0f,0.0f,0.0f };
	Vector3 cameraTranslate = {0.0f,0.0f,-15.0f};

	camera->SetRotate(cameraRotate);
	camera->SetTranslate(cameraTranslate);
	object3dCommon->SetDefaultCamera(camera);



	ModelCommon* modelCommon = nullptr;
	modelCommon = new ModelCommon();
	modelCommon->Initialize(dxCommon);


	//Model* model = nullptr;
	//model = new Model();
	//model->Initialize(modelCommon);


	Player* player = new Player();
	player->Initialize(object3dCommon,spriteCommon, winApp_);


	std::list<Enemy*> enemies;

	for (uint32_t i = 0; i < 2; ++i) {
		Enemy* enemy = new Enemy();
		Vector3 EnemyPos;

		if (i == 0) {
			EnemyPos = { 1.0f,0.0f,25.0f };
		}
		else{ 
			EnemyPos = { -1.0f,0.0f,20.0f }; 
		}

		enemy->Initialize(object3dCommon,EnemyPos);
		enemies.push_back(enemy);
	}


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
			
			input_->Update();
			
			if (input_->PushKey(DIK_0)) {
				OutputDebugStringA("Hit 0\n");
			}

			if (input_->TriggerKey(DIK_1)) {
				OutputDebugStringA("Hit 1\n");
			}



			camera->Update();

			player->Update();
			
			for (Enemy* enemy : enemies) {
				enemy->Update();
			}


			ImGui_ImplDX12_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();


			//開発用UIの処理
			//ImGui::ShowDemoWindow();

			//ここにテキストを入れられる
			//ImGui::Text("ImGuiText");
			
			////カメラ
			//ImGui::SliderFloat3("cameraTranslate", &cameraTranslate.x,-30.0f,30.0f);

			//ImGui::SliderFloat("cameraRotateX", &cameraRotate.x, -10.0f, 10.0f);
			//ImGui::SliderFloat("cameraRotateY", &cameraRotate.y, -10.0f, 10.0f);
			//ImGui::SliderFloat("cameraRotateZ", &cameraRotate.z, -10.0f, 10.0f);
			//camera->SetRotate(cameraRotate);
			//camera->SetTranslate(cameraTranslate);


			//if (ImGui::TreeNode("Model_1")) {
			//	ImGui::Checkbox("IsModel", &IsModel[0]);
			//	if (IsModel) {

			//		positionOBJ = objects[0]->GetTranslate();
			//		ImGui::InputFloat3("VertexModel", &positionOBJ.x);
			//		ImGui::SliderFloat3("SliderVertexModel", &positionOBJ.x, -5.0f, 5.0f);
			//		objects[0]->SetTranslate(positionOBJ);


			//		rotationOBJ = objects[0]->GetRotate();
			//		ImGui::InputFloat3("RotateModel", &rotationOBJ.x);
			//		ImGui::SliderFloat3("SliderRotateModel", &rotationOBJ.x, -10.0f, 10.0f);

			//		objects[0]->SetRotate(rotationOBJ);


			//		sizeOBJ = objects[0]->GetScale();
			//		ImGui::InputFloat3("ScaleModel", &sizeOBJ.x);
			//		ImGui::SliderFloat3("SliderScaleModel", &sizeOBJ.x, 0.5f, 5.0f);

			//		objects[0]->SetScale(sizeOBJ);

			//		//ImGui::InputFloat3("MaterialModel", *);
			//		//ImGui::SliderFloat3("SliderMaterialModel", *inputMaterialModel, 0.0f, 1.0f);
			//		//ImGui::Checkbox("ModelTexture", &textureChange2);
			//	}
			//	ImGui::TreePop();
			//}
			//

			//if (ImGui::TreeNode("Model_2")) {
			//	ImGui::Checkbox("IsModel", &IsModel[1]);
			//	if (IsModel[1]) {

			//		positionOBJ = objects[1]->GetTranslate();
			//		ImGui::InputFloat3("VertexModel", &positionOBJ.x);
			//		ImGui::SliderFloat3("SliderVertexModel", &positionOBJ.x, -5.0f, 5.0f);
			//		objects[1]->SetTranslate(positionOBJ);


			//		rotationOBJ = objects[1]->GetRotate();
			//		ImGui::InputFloat3("RotateModel", &rotationOBJ.x);
			//		ImGui::SliderFloat3("SliderRotateModel", &rotationOBJ.x, -10.0f, 10.0f);

			//		objects[1]->SetRotate(rotationOBJ);


			//		sizeOBJ = objects[1]->GetScale();
			//		ImGui::InputFloat3("ScaleModel", &sizeOBJ.x);
			//		ImGui::SliderFloat3("SliderScaleModel", &sizeOBJ.x, 0.5f, 5.0f);

			//		objects[1]->SetScale(sizeOBJ);

			//		//ImGui::InputFloat3("MaterialModel", *);
			//		//ImGui::SliderFloat3("SliderMaterialModel", *inputMaterialModel, 0.0f, 1.0f);
			//		//ImGui::Checkbox("ModelTexture", &textureChange2);
			//	}
			//	ImGui::TreePop();
			//}



			////if (ImGui::TreeNode("light")) {

			////	ImGui::InputFloat4("Materiallight", *inputMateriallight);
			////	ImGui::SliderFloat4("SliderMateriallight", *inputMateriallight, 0.0f, 1.0f);

			////	ImGui::InputFloat3("Vertexlight", *inputDirectionLight);
			////	ImGui::SliderFloat3("SliderVertexlight", *inputDirectionLight, -1.0f, 1.0f);


			////	ImGui::InputFloat("intensity", intensity);

			////	ImGui::TreePop();
			////}
			//for (Sprite* sprite : sprites) {
			//	if (ImGui::TreeNode("Sprite")) {
			//		ImGui::Checkbox("IsSprite", &IsSprite);

			//		if (IsSprite) {

			//			position = sprite->GetPosition();
			//			ImGui::InputFloat("SpriteX", &position.x);
			//			ImGui::SliderFloat("SliderSpriteX", &position.x, 0.0f, 1000.0f);
			//			ImGui::InputFloat("SpriteY", &position.y);
			//			ImGui::SliderFloat("SliderSpriteY", &position.y, 0.0f, 600.0f);
			//			sprite->SetPosition(position);

			//			ImGui::DragFloat2("UVTranlate", &position.x, 0.01f, -10.0f, 10.0f);				
			//									
			//			size = sprite->GetSize();
			//			ImGui::DragFloat2("UVScale", &size.x, 0.1f);
			//			sprite->SetSize(size);

			//			rotation = sprite->GetRotate();
			//			ImGui::SliderAngle("UVRotate", &rotation);	
			//			sprite->SetRotate(rotation);	
		

			//			color = sprite->GetColor();
			//			ImGui::SliderFloat4("color", &color.x, 0.0f, 1.0f);
			//			sprite->SetColor(color);

			//		}
			//		ImGui::TreePop();
			//	}
			//}
			//ImGuiの内部コマンド
			ImGui::Render();

			dxCommon->ProDraw();

			//モデル
			
			object3dCommon->Command();
			
			//for (Object3d* object3d : objects) {
			//	object3d->Draw();
			//}

			player->Draw();
			for (Enemy* enemy : enemies) {
				enemy->Draw();
			}

			//UI
			spriteCommon->Command();

			//for (Sprite* sprite : sprites) {
			//	sprite->Draw();
			//}

			player->Draw2D();

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
	//for (Sprite* sprite : sprites) {
	//	delete sprite;
	//}

	delete object3dCommon;
	//for (Object3d* object3d : objects) {
	//	delete object3d;
	//}

	delete modelCommon;
	//delete model;


	delete player;
	for (Enemy* enemy : enemies) {
		delete enemy;
	}

	return 0;
}