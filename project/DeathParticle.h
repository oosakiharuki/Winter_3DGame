#pragma once
#include "MyMath.h"
#include "Object3d.h"

class DeathParticle{
public:
	~DeathParticle();
	void Initialize(Object3dCommon* object3dCommon,Vector3 position);
	void Update();
	void Draw();
	
	Vector3 GetPosition() { return position; }
	void SetPosition(Vector3 position) { this->position = position; }

	float GetTimer() { return timer; }
	AABB GetAABB();

private:
	Object3d* object3d = nullptr;

	Vector3 position;
	Vector3 rotation;
	Vector3 size;

	float timer = 0.7f;

	Object3dCommon* ObjCommon = nullptr;
};