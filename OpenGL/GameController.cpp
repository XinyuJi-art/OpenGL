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

    Load();

    /*camera = new Camera(WindowController::GetInstance().GetResolution());
	camera->LookAt({ 10, 10, 10 }, { 0, 0, 0 }, { 0, 1, 0 });*/
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

    if (document.hasKey("Lights"))
    {
        json::JSON& lightsJSON = document["Lights"];
        for (auto& lightJSON : lightsJSON.ArrayRange())
        {
            Mesh* light = new Mesh();
            light->Create(lightJSON);
			light->SetCameraPosition(camera->GetPosition());
			lights.push_back(light);
        }
    }

    if (document.hasKey("Meshes"))
    {
        json::JSON& meshesJSON = document["Meshes"];
        for (auto& meshJSON : meshesJSON.ArrayRange())
        {
            Mesh* mesh = new Mesh();
            mesh->Create(meshJSON);
			mesh->SetCameraPosition(camera->GetPosition());
			meshes.push_back(mesh);
        }
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

void GameController::RunGame()
{
	//shaderColor = new Shader();
	//shaderColor->LoadShaders("Color.vertexshader", "Color.fragmentshader");
	//shaderDiffuse = new Shader();
	//shaderDiffuse->LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");

	///*meshLight = new Mesh();
	//meshLight->Create(shaderColor);
 //   meshLight->SetPosition({ 10.0f, 0.0f, 0.0f });
	//meshLight->SetScale({ 0.5f,0.5f,0.5f });*/

 //   for(int i = 0; i < 4; i++)
 //   {
 //       Mesh* light = new Mesh();
 //       light->Create(shaderColor);
 //       light->SetPosition({ 5.0f, 0.0f, (float)i * 3.0f - 4.0f });
	//	light->SetLightDirection(glm::normalize(glm::vec3({ 0.0f, 0.0f, (float)i * 3.0f - 4.0f }) - light->GetPosition()));
 //       light->SetLightColor({ glm::linearRand(0.0f, 1.0f), glm::linearRand(0.0f, 1.0f), glm::linearRand(0.0f, 1.0f)});
 //       light->SetScale({ 0.1f,0.1f,0.1f });
 //       lights.push_back(light);
	//}

 //   for (int row = 0; row < 10; row++)
 //   {
 //       for (int col = 0; col < 10; col++)
 //       {
 //           /*Mesh* mesh = new Mesh();
 //           mesh->Create(shaderDiffuse);
 //           mesh->SetLightColor({ 1.0f, 1.0f, 1.0f });
 //           mesh->SetLightPosition(meshLight->GetPosition());
 //           mesh->SetCameraPosition(camera->GetPosition());
 //           mesh->SetScale({ 1.0f, 1.0f, 1.0f });
 //           mesh->SetPosition({ 0.0f, (float)row * 2.0f - 9.0f, (float)col * 2.0f - 9.0f});;
 //           meshes.push_back(mesh);*/
	//		Mesh* mesh = new Mesh();
	//		mesh->Create(shaderDiffuse);
	//		mesh->SetCameraPosition(camera->GetPosition());
	//		mesh->SetScale({ 1.0f, 1.0f, 1.0f });
	//		mesh->SetPosition({ 0.0f, (float)row * 2.0f - 9.0f, (float)col * 2.0f - 9.0f });
	//		meshes.push_back(mesh);
 //       }
	//}

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

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            if (currentInstanceCount < 1000)
            {
                currentInstanceCount++;
            }
        }

        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            if (currentInstanceCount > 1)
            {
                currentInstanceCount--;
            }
        }


        for (auto& light : lights)
        {
            light->Render(camera->GetProjection() * camera->GetView(), lights);
        }

        for (auto& mesh : meshes)
        {
            mesh->SetRotation(mesh->GetRotation() + glm::vec3(0.0f, mesh->GetRotationRate() * Time::Instance().DeltaTime(), 0.0f));
            mesh->Render(camera->GetProjection() * camera->GetView(), lights, currentInstanceCount);
		}   

        std::string fpsText = "FPS: " + std::to_string(Time::Instance().FPS());
        textController->RenderText(fpsText, 20, 100, 0.5f, {1.0f, 1.0f, 0.0f});

        glfwSwapBuffers(window);
        glfwPollEvents();

    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0);

    for(auto& mesh : meshes)
    {
        delete mesh;
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