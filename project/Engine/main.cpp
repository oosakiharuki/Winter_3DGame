#include <cstdint>
#include<format>

#include<cassert>

#include <dxgidebug.h>

#include"externals/imgui/imgui.h"
#include"externals/imgui/imgui_impl_dx12.h"
#include"externals/imgui/imgui_impl_win32.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#pragma comment(lib,"dxguid.lib")


#pragma comment(lib,"dxcompiler.lib")

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

#include"GameManager.h"

#include <xaudio2.h>

#pragma comment(lib,"xaudio2.lib")

#include <fstream>

struct ChunkHeader {
	char id[4];//チャンク毎ID
	int32_t size;//サイズ
};

struct RiffHeader {
	ChunkHeader chunk;//RIFF
	char type[4];//WAVE
};

struct FormatChunk {
	ChunkHeader chunk;
	WAVEFORMATEX fmt;
};

struct SoundData {
	//波形フォーマット
	WAVEFORMATEX wfex;
	//バッファ先頭
	BYTE* pBuffer;
	//サイズ
	unsigned int byfferSize;
};

SoundData SoundLoadWave(const char* filename)//string?
{
	//HRESULT result;

	//ファイルオープン
	//file入力ストリームのインスタンス
	std::ifstream file;
	//wavファイルをバイナリモードで開く
	file.open(filename, std::ios_base::binary);

	assert(file.is_open());

	//wavデータ読み込み
	//RIFFヘッダー読み込み
	RiffHeader riff;
	file.read((char*)&riff, sizeof(riff));

	//ファイルがRIFFであるか
	if (strncmp(riff.chunk.id, "RIFF", 4) != 0) {
		assert(0);
	}

	//パスがWAVEであるか
	if (strncmp(riff.type, "WAVE", 4) != 0) {
		assert(0);
	}

	//Formatチャンク読み込み
	FormatChunk format = {};

	//チャンクヘッダー確認
	file.read((char*)&format, sizeof(ChunkHeader));
	if (strncmp(format.chunk.id, "fmt ", 4) != 0) {
		assert(0);
	}

	//チャンク本体読み込み
	assert(format.chunk.size <= sizeof(format.fmt));
	file.read((char*)&format.fmt, format.chunk.size);

	//Dataチャンク読み込み
	ChunkHeader data;
	file.read((char*)&data, sizeof(data));

	//JUNKチャンクの場合
	if (strncmp(data.id, "JUNK", 4) == 0) {
		file.seekg(data.size, std::ios_base::cur);
		file.read((char*)&data, sizeof(data));
	}


	data.size = mmioFOURCC('d', 'a', 't', 'a');

	if (strncmp(data.id, "data", 4) != 0) {
		if (strncmp(data.id, "LIST", 4) != 0) {
			assert(0);
		}
	}

	//波形データ読み込み
	char* pBuffer = new char[data.size];
	file.read(pBuffer, data.size);

	//Waveファイルを閉じる
	file.close();


	//全てまとめる
	SoundData soundData = {};

	soundData.wfex = format.fmt;
	soundData.pBuffer = reinterpret_cast<BYTE*>(pBuffer);
	soundData.byfferSize = data.size;

	return soundData;
}

//音声データの解放 delete
void SoundUnload(SoundData* soundData) {
	delete[] soundData->pBuffer; //newしたため（波形データ読み込み）

	soundData->pBuffer = 0;
	soundData->byfferSize = 0;
	soundData->wfex = {};
}

//音声再生
void SoundPlayWave(IXAudio2* xAudio2, const SoundData& soundData) {

	HRESULT result;

	IXAudio2SourceVoice* pSourceVoice = nullptr;
	result = xAudio2->CreateSourceVoice(&pSourceVoice, &soundData.wfex);
	assert(SUCCEEDED(result));

	XAUDIO2_BUFFER buf{};
	buf.pAudioData = soundData.pBuffer;
	buf.AudioBytes = soundData.byfferSize;
	buf.Flags = XAUDIO2_END_OF_STREAM;

	result = pSourceVoice->SubmitSourceBuffer(&buf);
	result = pSourceVoice->Start();
	

}

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

	//audio
	Microsoft::WRL::ComPtr<IXAudio2> xAudio2;

	IXAudio2MasteringVoice* masterVoice;

	HRESULT result = XAudio2Create(&xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	result = xAudio2->CreateMasteringVoice(&masterVoice);

	SoundData soundData1 = SoundLoadWave("resource/damage.wav");
	SoundData soundData2 = SoundLoadWave("resource/Alarm01.wav");




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

	ModelManager::GetInstance()->LoadModel("enemy.obj");
	ModelManager::GetInstance()->LoadModel("player.obj");
	ModelManager::GetInstance()->LoadModel("bullet.obj");
	ModelManager::GetInstance()->LoadModel("wall.obj");
	ModelManager::GetInstance()->LoadModel("bom.obj");

	int a = -1;

	//ウィンドウの×ボタンが押されるまでループ
	while (true) {
		if (winApp_->ProcessMessage()) {
			break;//whileを抜ける
		}
		else {
			//ゲームの処理

			if (a < 0) {

				SoundPlayWave(xAudio2.Get(), soundData1);
				SoundPlayWave(xAudio2.Get(), soundData2);
				a++;
			}

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

	xAudio2.Reset();
	SoundUnload(&soundData1);
	SoundUnload(&soundData2);


	return 0;
}