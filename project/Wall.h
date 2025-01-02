#pragma once
#include "Object3d.h"

class Wall {
public:
	~Wall();
	void Initialize(Object3dCommon* object3dCommon, const Vector3& position);
	void Update();
	void Draw();

	void OnCollision();
	AABB GetAABB();

	bool IsHit()const { return isHit_; }
	bool IsShake()const { return shakeTime; }
	float IsTime()const { return coolTime; }

	bool IsDead()const { return isDead_; }

private:
	Transform tarnsform;

	Object3d* object3d = nullptr;

	Vector3 position;
	Vector3 rotation;
	Vector3 size;

	Object3dCommon* ObjCommon = nullptr;

	uint32_t hp = 3;
	float coolTime;
	bool isHit_ = false;
	bool isDead_ = false;
	bool shakeTime = false;
};