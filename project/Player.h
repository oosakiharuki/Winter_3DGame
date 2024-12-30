#pragma once
#include "MyMath.h"
#include "Object3d.h"
#include "Sprite.h"
#include "Input.h"
#include "PlayerBullet.h"

//#include <list>

class Player{
public:
	~Player();
	void Initialize(Object3dCommon* object3dCommon, SpriteCommon* spriteCommon,Input* input);
	void Update();
	void Attack();
	void Draw();
	void Draw2D();
	
	void OnCollision();
	std::list<PlayerBullet*> GetBullets() { return bullets_; }
	Vector3 GetPosition() { return position; };

	bool FinishWin() const { return isClear_; }
	bool FinishLoze() const { return isGameOver_; }

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
	Object3dCommon* ObjCommon = nullptr;
	std::list<PlayerBullet*> bullets_;

	bool isClear_ = false;
	bool isGameOver_ = false;
};