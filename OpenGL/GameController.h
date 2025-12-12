#pragma once
#include "Camera.h"
#include "Shader.h"
#include "Font.h"
#include <GLFW/glfw3.h>
#include "StandardIncludes.h"
#include "TextController.h"

enum class SceneMode {
    MOVE_LIGHT = 0,
    MOVE_SHIP = 1,
    MOVE_FISH = 2,
	MOVE_SPACE = 3
};

class Mesh;

class GameController
{
public:
    static GameController& GetInstance()
    {
        static GameController instance;
        return instance;
	}

    void Initialize();
    void RunGame();
    void Load();
    Shader* GetShader(const char* shaderName)
    {
		auto itr = shaders.find(shaderName);
        assert(itr != shaders.end());
		return itr->second;
    }

    Font* GetFont(const char* fontName)
    {
		auto itr = fonts.find(fontName);
		assert(itr != fonts.end());
        return itr->second;
	}

private:
    void HandleResetRequests();
    void RenderMesh(const std::string& meshKey);
    void HandleLightMovementScene(GLFWwindow* activeWindow);
    void HandlePositionColorScene(GLFWwindow* activeWindow);
    void HandleCubesToSphereScene(GLFWwindow* activeWindow);

    Mesh* GetLight() {
        if (!lights.empty()) return lights.front();
        return nullptr;
    }
private:
	std::map<std::string, Font*> fonts;
    std::map<std::string, Mesh*> meshes;
    std::map<std::string, Shader*> shaders;
    std::list<Mesh*> lights;
    std::list<Mesh*> cubeMeshes;
	Camera* camera = nullptr;
	TextController* textController = nullptr;
    Mesh* sphereMesh = nullptr;
    const float CUBE_SPEED = 2.0f;
    const float DELETE_DISTANCE = 0.5f;
    Mesh* suzanneMesh = nullptr;
    Mesh* spaceShip = nullptr;
    Mesh* fish = nullptr;
    Mesh* fishInstance = nullptr;
    glm::vec3 suzannePosition = glm::vec3(0.0f);

    GLuint vao;

private:
	inline explicit GameController() = default;
	inline ~GameController() = default;
	inline explicit GameController(const GameController&) = delete;
	inline GameController& operator=(const GameController&) = delete;
};
