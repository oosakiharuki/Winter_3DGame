#pragma once
#include "Input.h"
//#include "WinApp.h"
#include "DirectXCommon.h"
#include "D3DResorceLeakChecker.h"
#include "GameManager.h"

#include "IScene.h"
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

class GameScene : public IScene{
public:
	~GameScene() override;
	void Initialize(SpriteCommon* spriteCommon, Object3dCommon* objCommon, Input* input) override;
	void Update() override;
	void Draw() override;

private:
	Input* input_ = nullptr;
	Object3dCommon* object3dCommon_ = nullptr;
	SpriteCommon* spriteCommon_ = nullptr
		;
	Camera* camera = nullptr;
	
	Player* player = nullptr;
	std::list<Enemy*> enemies;
};