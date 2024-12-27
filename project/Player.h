#pragma once
#include "MyMath.h"
#include "Object3d.h"
#include "Sprite.h"
#include "Input.h"


class Player{
public:
	~Player();
	void Initialize(Object3dCommon* object3dCommon, SpriteCommon* spriteCommon,WinApp* winApp);
	void Update();
	void Draw();
	void Draw2D();
	
private:
	Transform tarnsform;
	uint32_t textureHandle = 0u;

	Object3d* object3d = nullptr;

	Vector3 position;
	Vector3 rotation;
	Vector3 size;

	Sprite* sprite = nullptr;

	Input* input_ = nullptr;
	WinApp* winApp_ = nullptr;
};