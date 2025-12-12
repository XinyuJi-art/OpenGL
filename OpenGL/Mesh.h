#pragma once
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "Shader.h"
#include "Texture.h"
#include "StandardIncludes.h"
#include "GameController.h"
#include "OBJ_Loader.h"

enum LightType {
    DIRECTIONAL_LIGHT = 1,
    POINT_LIGHT = 2,
    SPOT_LIGHT = 3,
    NONE = 0
};

class Mesh
{

public:
	~Mesh();

	void SetPosition(glm::vec3 _position) { position = _position; }
	glm::vec3 GetPosition() { return position; }
	void SetScale(glm::vec3 _scale) { scale = _scale; }
	glm::vec3 GetScale() { return scale; }
	void SetRotation(glm::vec3 _rotation) { rotation = _rotation; }
	glm::vec3 GetRotation() { return rotation; }
	float GetRotationRate() { return rotationRate; }
	void SetRotationRate(float _rotation) { rotationRate = _rotation; }
	void SetSpecularStrength(float _strength) { specularStrength = _strength; }
	void SetSpecularColor(float _r, float _g, float _b) { specularColor = glm::vec3(_r, _g, _b); }
	void SetLightDirection(glm::vec3 _lightDirection) { lightDirection = _lightDirection; }
	glm::vec3 GetLightDirection() { return lightDirection; }
	void SetLightColor(glm::vec3 _lightColor) { lightColor = _lightColor; }
	glm::vec3 GetLightColor() { return lightColor; }

	glm::vec3 GetAmbientColor() { return ambientColor; }
	glm::vec3 GetSpecularColor() { return specularColor; }
	float GetSpecularStrength() { return specularStrength; }

	float GetPointLightConstant() { return pointLightconstant; }
	float GetPointLightLinear() { return pointLightlinear; }
	float GetPointLightQuadratic() { return pointLightquadratic; }

	float GetConeAngle() { return spotLightconeAngle; }
	float GetFalloff() { return spotLightfalloff; }

	void SetCameraPosition(glm::vec3 _cameraPosition) { cameraPosition = _cameraPosition; }

	void Create(json::JSON& jsonData);
	void CalculateTransform();
	void Render(glm::mat4 _pv, const std::list<Mesh*>& _lights);

private:
	void LoadOBJ(const std::string& _file);
	void LoadASE(const std::string& _file);


	void SetShaderVariables(glm::mat4 _pv, const std::list<Mesh*>& _lights);
	void BindAttributes();
	std::string Concat(const std::string& _s1, int _index, const std::string& _s2);
	std::string RemoveFolder(std::string& _map);
	void LoadVec3(json::JSON& jsonData, const char* name, glm::vec3& vec);
	void CalculateTangents(std::vector<objl::Vertex> _vertices, objl::Vector3& _tangent, objl::Vector3& _bitangent);
	bool EndsWith(const std::string& _str, const std::string& _suffix);


private:
	Shader* shader = nullptr;

	std::string diffuseMap;
	Texture* diffuseTexture = nullptr;
	std::string specularMap;
	Texture* specularTexture = nullptr;
	std::string normalMap;
	Texture* normalTexture = nullptr;

	GLuint vertexBuffer = 0;
	GLuint indexBuffer = 0;
	GLuint instanceBuffer = 0;

	std::vector<GLfloat> vertexData;
	std::vector<GLbyte> indexData;

	int vertexStride = 8;
	bool enableNormalMaps = false;
	int instanceCount = 0;
	bool enableInstancing = false;
	glm::mat4* instanceData;


	glm::mat4 world = glm::mat4(1);
	glm::vec3 position{ 0.0f,0.0f,0.0f };
	glm::vec3 rotation{ 0.0f,0.0f,0.0f };
	glm::vec3 scale{ 1.0f,1.0f,1.0f };

	glm::vec3 lightDirection{ 0.0f,0.0f,0.0f };
	glm::vec3 lightColor{ 1.0f,1.0f,1.0f };
	glm::vec3 ambientColor{ 0.1f,0.1f,0.1f };
	glm::vec3 specularColor{ 1.0f,1.0f,1.0f };
	float specularStrength = 1.0f;
	float rotationRate = 0.0f;

	float pointLightconstant = 1.0f;
	float pointLightlinear = 1.0f;
	float pointLightquadratic = 1.0f;

	float spotLightconeAngle = 1.0f;
	float spotLightfalloff = 1.0f;




	glm::vec3 cameraPosition{ 0.0f,0.0f,0.0f };


};