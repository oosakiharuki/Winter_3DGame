#pragma once

#include <memory>
#include "IScene.h"
#include "GameScene.h"//geme
#include "TitleScene.h"//title
//clear
//gameover


class GameManager {
public:
	GameManager(SpriteCommon* spriteCommon, Object3dCommon* objCommon, Input* input);
	~GameManager();


	void Update();
	void Draw();

private:
	
	void SceneChange(int prev,int current);//シーン入れ替え

	IScene* sceneArr_[2];
	uint32_t SceneNum = 2;


	int currentSceneNo_;//現在シーン
	int prevSceneNo_;//前シーン

	SpriteCommon* spriteCommon_;
	Object3dCommon* objCommon_;
	Input* input_;
};