#include "IScene.h"

int IScene::sceneNo = GAME;

IScene::~IScene(){}

int IScene::GetSceneNo() { return sceneNo; }