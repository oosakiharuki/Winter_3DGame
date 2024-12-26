#pragma once
#include "MyMath.h"
#include "ModelCommon.h"

class Model{
public:

	void Initialize(ModelCommon* modelCommon,const std::string& directorypath,const std::string& fileName);
	void Draw();
	static MaterialData LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename);
	static ModelData LoadObjFile(const std::string& directoryPath, const std::string& filename);

private:
	ModelCommon* modelCommon = nullptr;

	ModelData modelData;

	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource;
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource;


	VertexData* vertexData = nullptr;
	Material* materialData = nullptr;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
};