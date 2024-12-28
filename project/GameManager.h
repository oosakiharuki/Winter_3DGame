#pragma once

#include <memory>
#include "IScene.h"
#include "GameScene.h"//geme
//title
//clear
//gameover


class GameManager {
public:
	GameManager(SpriteCommon* spriteCommon, Object3dCommon* objCommon, Input* input);
	~GameManager();

	void Initialize();
	void Update();
	void Draw();

private:

	std::unique_ptr<IScene> sceneArr_[1];

	int currentSceneNo_;//現在シーン
	int prevSceneNo_;//前シーン

	SpriteCommon* spriteCommon_;
	Object3dCommon* objCommon_;
	Input* input_;
};