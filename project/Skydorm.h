#pragma once
#include "Object3dCommon.h"
#include "Object3d.h"

class Skydorm{
public:
	~Skydorm();
	void Initialize(Object3dCommon* object3dCommon, Camera* camera, std::string objFile);
	void Update();
	void Draw();

private:
	Object3d* object3d = nullptr;
	Object3dCommon* object3dCommon_ = nullptr;
	Camera* camera_ = nullptr;
};