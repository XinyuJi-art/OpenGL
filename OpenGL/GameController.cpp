#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"
#include "Mesh.h"
#include "EngineTime.h"
#include <fstream>


void GameController::Initialize()
{
    GLFWwindow* window = WindowController::GetInstance().GetWindow();
    M_ASSERT(glewInit() == GLEW_OK, "Unable to initialize glew");
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    srand(time(0));

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

    glfwSetWindowUserPointer(window, this);

    Load();
}

void GameController::Load()
{
#pragma region Settings
	std::ifstream inputStream("../Assets/settings.json");
    std::string str((std::istreambuf_iterator<char>(inputStream)),
		std::istreambuf_iterator<char>());
	json::JSON document = json::JSON::Load(str);
#pragma endregion

#pragma region Clear Color
	glm::vec3 ClearColor = { 0.0f, 0.0f, 0.0f };
	if (document.hasKey("ClearColor"))
    {
		json::JSON& jsonClearColor = document["ClearColor"]; 
        if (jsonClearColor.hasKey("r")) ClearColor.x = jsonClearColor["r"].ToFloat();
		if (jsonClearColor.hasKey("g")) ClearColor.y = jsonClearColor["g"].ToFloat();
		if (jsonClearColor.hasKey("b")) ClearColor.z = jsonClearColor["b"].ToFloat();
	}
	glClearColor(ClearColor.r, ClearColor.g, ClearColor.b, 0.0f);
#pragma endregion

#pragma region Camera
	float _fov = 45.0f;
	float _near = 0.1f;
	float _far = 1000.0f;
	glm::vec3 CameraPosition = { 1, 0, 0 };
	glm::vec3 CameraLookAt = { 0, 0, 0 };
    if (document.hasKey("Camera"))
    {
        json::JSON& jsonCamera = document["Camera"];
        if (jsonCamera.hasKey("Position"))
        {
            json::JSON& jsonCameraObject = jsonCamera["Position"];
            if (jsonCameraObject.hasKey("x")) CameraPosition.x = jsonCameraObject["x"].ToFloat();
            if (jsonCameraObject.hasKey("y")) CameraPosition.y = jsonCameraObject["y"].ToFloat();
            if (jsonCameraObject.hasKey("z")) CameraPosition.z = jsonCameraObject["z"].ToFloat();
        }
        if (jsonCamera.hasKey("LookAt"))
        {
            json::JSON& jsonCameraObject = jsonCamera["LookAt"];
            if (jsonCameraObject.hasKey("x")) CameraLookAt.x = jsonCameraObject["x"].ToFloat();
            if (jsonCameraObject.hasKey("y")) CameraLookAt.y = jsonCameraObject["y"].ToFloat();
            if (jsonCameraObject.hasKey("z")) CameraLookAt.z = jsonCameraObject["z"].ToFloat();
        }
        if (jsonCamera.hasKey("fov")) _fov = jsonCamera["fov"].ToFloat();
        if (jsonCamera.hasKey("near")) _near = jsonCamera["near"].ToFloat();
        if (jsonCamera.hasKey("far")) _far = jsonCamera["far"].ToFloat();
    }
	camera = new Camera(WindowController::GetInstance().GetResolution(), _fov, _near, _far);
	camera->LookAt(CameraPosition, CameraLookAt, { 0, 1, 0 });
#pragma endregion

#pragma region Shader
    if (document.hasKey("Shaders"))
    {
		json::JSON& shadersJSON = document["Shaders"];
        for (auto& shaderJSON : shadersJSON.ArrayRange())
        {
            assert(shaderJSON.hasKey("name"));
			assert(shaderJSON.hasKey("vertex"));
			assert(shaderJSON.hasKey("fragment"));
			Shader* shaderColor = new Shader();
			shaderColor->LoadShaders(shaderJSON["vertex"].ToString().c_str(), shaderJSON["fragment"].ToString().c_str());
			shaders.emplace(shaderJSON["name"].ToString().c_str(), shaderColor);
        }
    }
#pragma endregion

#pragma region Scene
	M_ASSERT(document.hasKey("DefaultFile"), "Settings requires a default file.");
	std::string defaultFile = document["DefaultFile"].ToString();

	inputStream = std::ifstream(defaultFile);
    str = std::string((std::istreambuf_iterator<char>(inputStream)),
		std::istreambuf_iterator<char>());
	document = json::JSON::Load(str);

    if (document.hasKey("Light"))
    {
        json::JSON& lightJSON = document["Light"];
        Mesh* light = new Mesh();
        light->Create(lightJSON);
        light->SetCameraPosition(camera->GetPosition());
		lights.push_back(light);
    }

    if (document.hasKey("Suzanne"))
    {
        json::JSON& monkeyJSON = document["Suzanne"];
        Mesh* monkey = new Mesh();
        monkey->Create(monkeyJSON);
        monkey->SetCameraPosition(camera->GetPosition());

        meshes.emplace("Suzanne", monkey);

        suzanneMesh = monkey;
        suzannePosition = monkey->GetPosition();
    }

    if (document.hasKey("HatMonkeyBall"))
    {
        json::JSON& ballJSON = document["HatMonkeyBall"];
        Mesh* mesh = new Mesh();
        mesh->Create(ballJSON);
        mesh->SetCameraPosition(camera->GetPosition());

        meshes.emplace("Sphere", mesh);
        sphereMesh = mesh;
    }

    #pragma region Fonts
    if (document.hasKey("Fonts"))
        {
            json::JSON& fontsJSON = document["Fonts"];
            for (auto& fontJSON : fontsJSON.ArrayRange())
            {
                M_ASSERT(fontJSON.hasKey("Name"), "Font requires a name");
                std::string fontName = fontJSON["Name"].ToString();
    
                M_ASSERT(fontJSON.hasKey("Font"), "Font requires a Font node");

                Font* font = new Font();
                font->Create(fontJSON["Font"]);
                fonts.emplace(fontName, font);
            }
        }
    #pragma endregion

    #pragma region TextController
        if (document.hasKey("TextController"))
        {   
            textController = new TextController();
            textController->Create(document["TextController"]);
        }
    #pragma endregion
#pragma endregion

}


void GameController::HandleResetRequests()
{
    if (OpenGL::ToolWindow::ConsumeResetLight())
    {
        Mesh* light = lights.front();
        glm::vec3 currentLightPos = light->GetPosition();
        light->SetPosition(glm::vec3(0, 0, 0));
    }

    if (OpenGL::ToolWindow::ConsumeResetSuzanne())
    {
        suzanneMesh->SetPosition(glm::vec3(0.0f));
        suzannePosition = glm::vec3(0.0f);
    }
}

void GameController::RenderMesh(const std::string& meshKey)
{
    if (meshes.count(meshKey))
    {
        Mesh* currentMesh = meshes[meshKey];
        glm::vec3 currentRot = currentMesh->GetRotation();
        float rotRate = currentMesh->GetRotationRate();

        currentMesh->SetRotation(currentRot + Time::Instance().DeltaTime() * glm::vec3(0.0f, rotRate, 0.0f));

        currentMesh->Render(camera->GetProjection() * camera->GetView(), lights, 1);
    }
}

// Move Light
void GameController::HandleLightMovementScene(GLFWwindow* activeWindow)
{
    Mesh* sceneLight = GetLight();
    if (sceneLight == nullptr) return;

    Resolution screenRes = WindowController::GetInstance().GetResolution();
    double mouseX, mouseY;
    glfwGetCursorPos(activeWindow, &mouseX, &mouseY);
    glm::vec3 worldCursorMove;

    if (glfwGetMouseButton(activeWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        worldCursorMove = glm::vec3(
            (mouseX - screenRes.width / 2) * Time::Instance().DeltaTime() * 0.05f,
            (screenRes.height / 2 - mouseY) * Time::Instance().DeltaTime() * 0.05f,
            0.0f
        );
        sceneLight->SetPosition(sceneLight->GetPosition() + worldCursorMove);
    }
    else if (glfwGetMouseButton(activeWindow, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
    {
        worldCursorMove = glm::vec3(0.0f, 0.0f, (screenRes.height / 2 - mouseY) * Time::Instance().DeltaTime() * -0.01f);
        sceneLight->SetPosition(sceneLight->GetPosition() + worldCursorMove);
    }

    sceneLight->Render(camera->GetProjection() * camera->GetView(), lights);

    Shader* diffShader = shaders["Diffuse"];
    Mesh* suzanne = meshes["Suzanne"];

    if (suzanne != nullptr) {
        suzanne->SetShader(diffShader);
        RenderMesh("Suzanne");
    }

    glm::vec3 posDisplay = sceneLight->GetPosition();
    std::string outputText = "Light Position: X=" +
        std::to_string(posDisplay.x) + ", Y=" +
        std::to_string(posDisplay.y) + ", Z=" +
        std::to_string(posDisplay.z);

    textController->RenderText(outputText, 20, 60, 0.4f, { 1.0f, 1.0f, 0.0f });
}

// Color By Position
void GameController::HandlePositionColorScene(GLFWwindow* activeWindow)
{
    Mesh* suzanneTarget = meshes["Suzanne"];
    if (suzanneTarget == nullptr) return;

    Resolution screenRes = WindowController::GetInstance().GetResolution();
    double mouseX, mouseY;
    glfwGetCursorPos(activeWindow, &mouseX, &mouseY);
    glm::vec3 worldCursorMove;


    if (glfwGetMouseButton(activeWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        worldCursorMove = glm::vec3(
            (mouseX - screenRes.width / 2) * Time::Instance().DeltaTime() * 0.05f,
            (screenRes.height / 2 - mouseY) * Time::Instance().DeltaTime() * 0.05f,
            0.0f
        );
        suzanneTarget->SetPosition(suzanneTarget->GetPosition() + worldCursorMove);
    }
    else if (glfwGetMouseButton(activeWindow, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
    {
        worldCursorMove = glm::vec3(0.0f, 0.0f, (screenRes.height / 2 - mouseY) * Time::Instance().DeltaTime() * -0.01f);
        suzanneTarget->SetPosition(suzanneTarget->GetPosition() + worldCursorMove);
    }

    Shader* posColorShader = shaders["PositionColor"];

    suzanneTarget->SetShader(posColorShader);
    RenderMesh("Suzanne");

    glm::vec3 posDisplay = suzanneTarget->GetPosition();
    std::string outputText = "Suzanne Position: X=" +
        std::to_string(posDisplay.x) + ", Y=" +
        std::to_string(posDisplay.y) + ", Z=" +
        std::to_string(posDisplay.z);

    textController->RenderText(outputText, 20, 60, 0.4f, { 1.0f, 1.0f, 0.0f });
}

// Move Cubes to Sphere(Not finished)
void GameController::HandleCubesToSphereScene(GLFWwindow* activeWindow)
{
    Mesh* ballTarget = meshes["Sphere"];
    if (ballTarget == nullptr) return;

    Shader* diffShader = shaders["Diffuse"];
    sphereMesh->SetShader(diffShader);

    RenderMesh("Sphere");

    if (meshes.count("Light"))
    {
        RenderMesh("Light");
    }

    glDisable(GL_DEPTH_TEST);
    std::string messageOutput = "Total Cubes: " + std::to_string(cubeMeshes.size());
    textController->RenderText(messageOutput, 20, 60, 0.5f, { 1.0f, 1.0f, 0.0f });
    glEnable(GL_DEPTH_TEST);
}

void GameController::RunGame()
{
    OpenGL::ToolWindow^ toolWindow = gcnew OpenGL::ToolWindow();
    toolWindow->Show();

    GLFWwindow* window = WindowController::GetInstance().GetWindow();

    Time::Instance().Initialize();

    int currentInstanceCount = 100;
    bool upKeyPressed = false;
    bool downKeyPressed = false;

    do
    {
        Time::Instance().Update();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        HandleResetRequests();

        if (toolWindow->moveLight)
        {
            HandleLightMovementScene(window);
        }
        else if (toolWindow->colorPos)
        {
            HandlePositionColorScene(window);
        }
        else if (toolWindow->moveCubes)
        {
            HandleCubesToSphereScene(window);

            std::string messageOutput = "Total Cubes: " + std::to_string(cubeMeshes.size());
            textController->RenderText(messageOutput, 20, 60, 0.5f, { 1.0f, 1.0f, 0.0f });
        }

        /*std::string fpsText = "FPS: " + std::to_string(Time::Instance().FPS());
        textController->RenderText(fpsText, 20, 100, 0.5f, { 1.0f, 1.0f, 0.0f });*/

        glfwSwapBuffers(window);
        glfwPollEvents();

    } while (
        glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0
        );

        for (auto& mesh : meshes)
        {
            delete mesh.second;
        }
        for (auto& light : lights)
        {
            delete light;
        }
        for (auto& shader : shaders)
        {
            delete shader.second;
        }
        for (auto& font : fonts)
        {
            delete font.second;
        }
        if (textController != nullptr)
        {
            delete textController;
        }
        delete camera;

    }
