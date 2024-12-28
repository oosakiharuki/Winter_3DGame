#pragma once
#include "MyMath.h"
#include "Object3d.h"

enum Action {
	move,//動く
	stop//自爆
};

class Enemy {
public:	
	~Enemy();
	void Initialize(Object3dCommon* object3dCommon,const Vector3& position);
	void Update();
	void Draw();

private:
	Transform tarnsform;

	Object3d* object3d = nullptr;

	Vector3 position;
	Vector3 rotation;
	Vector3 size;

	Action action;

	Object3dCommon* ObjCommon = nullptr;
	std::stringstream enemyPopCommands;
};