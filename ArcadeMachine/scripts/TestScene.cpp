#include "TestScene.h"

#include "TextureManager.h"
#include "ShaderManager.h"
#include "MaterialManager.h"
#include "MeshManager.h"

#include "Camera.h"
#include "MeshRenderer.h"

#include "TurnTable.h"

TestScene::TestScene()
{
	// Textures
	TextureManager::clear();
	Texture* testTexture = new Texture("Test", "textures/testCheckerboard.bmp");
	Texture* testTexture2 = new Texture("Test2", "textures/blue_64_text.bmp");

	// Shaders
	ShaderManager::clear();
	Shader* testShader = new Shader("Test", "shaders/test");

	// Materials
	MaterialManager::clear();
	Material* testMaterial = new Material("Test", testShader);
	testMaterial->setTexture("myTextureSampler", testTexture);
	testMaterial->setTexture("myTextureSampler2", testTexture2);

	Material* testMaterial2 = new Material("Test2", testShader);
	testMaterial2->setTexture("myTextureSampler", testTexture2);
	testMaterial2->setTexture("myTextureSampler2", testTexture);

	// Meshes
	MeshManager::clear();
	Mesh* mesh = new Mesh("Test");
	// An array of 3 vectors which represents 3 vertices
	std::vector<glm::vec3> verts;
	verts.push_back(glm::vec3(1.0f, -1.0f, -1.0f));
	verts.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
	verts.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

	verts.push_back(glm::vec3(1.0f, -1.0f, 1.0f));
	verts.push_back(glm::vec3(1.0f, -1.0f, -1.0f));
	verts.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

	verts.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));
	verts.push_back(glm::vec3(1.0f, -1.0f, 1.0f));
	verts.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

	verts.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
	verts.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));
	verts.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	mesh->set_Vertices(verts);

	std::vector<glm::vec3> colors;
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	mesh->set_Colors(colors);

	std::vector<glm::vec2> uvs;
	uvs.push_back(glm::vec2(0.0f, 0.0f));
	uvs.push_back(glm::vec2(1.0f, 0.0f));
	uvs.push_back(glm::vec2(0.5f, 1.0f));

	uvs.push_back(glm::vec2(0.0f, 0.0f));
	uvs.push_back(glm::vec2(1.0f, 0.0f));
	uvs.push_back(glm::vec2(0.5f, 1.0f));

	uvs.push_back(glm::vec2(0.0f, 0.0f));
	uvs.push_back(glm::vec2(1.0f, 0.0f));
	uvs.push_back(glm::vec2(0.5f, 1.0f));

	uvs.push_back(glm::vec2(0.0f, 0.0f));
	uvs.push_back(glm::vec2(1.0f, 0.0f));
	uvs.push_back(glm::vec2(0.5f, 1.0f));
	mesh->set_UVs(uvs);

	// >> Scene Stuff

	GameObject* testGameObjectRoot = new GameObject("Camera Obj Root");
	testGameObjectRoot->get_Transform()->set_LocalEulerAngles(0.0f, 0.0f, 0.0f);
	add_GameObject(testGameObjectRoot);

	// Camera GO
	GameObject* testGameObject = new GameObject("Camera Obj");
	testGameObject->get_Transform()->setParent(testGameObjectRoot->get_Transform());
	testGameObject->get_Transform()->m_LocalPosition = glm::vec3(0.0f, -0.5f, 10.0f);
	testGameObject->get_Transform()->set_LocalEulerAngles(0.0f, 180.0f, 0.0f);
	//testGameObject->get_Transform()->rotateLocal(0.0f, 0.0f, 45.0f);
	//testGameObject->get_Transform()->m_LocalScale = glm::vec3(1.0f, -1.0f, 1.0f);
	// Camera Component
	Camera* testCameraComp = new Camera(45.0f, 0.1f, 100.0f);
	testGameObject->add_Component(testCameraComp);
	// Add to scene
	add_Component(testCameraComp);
	add_GameObject(testGameObject);

	// Triangle GO
	GameObject* testGameObject2 = new GameObject("Test Renderer");
	testGameObject2->get_Transform()->m_LocalPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	testGameObject2->get_Transform()->set_LocalEulerAngles(0.0f, 0.0f, 0.0f);
	testGameObject2->get_Transform()->m_LocalScale = glm::vec3(2.0f, 2.0f, 2.0f);
	// Renderer Component
	MeshRenderer* meshRenderer = new MeshRenderer(mesh, testMaterial);
	testGameObject2->add_Component(meshRenderer);
	// Add to scene
	add_Component(meshRenderer);
	add_GameObject(testGameObject2);

	// Triangle GO2
	GameObject* testGameObject3 = new GameObject("Test Renderer");
	testGameObject3->get_Transform()->m_LocalPosition = glm::vec3(2.0f, 0.0f, 0.0f);
	testGameObject3->get_Transform()->set_LocalEulerAngles(0.0f, 0.0f, 0.0f);
	testGameObject3->get_Transform()->m_LocalScale = glm::vec3(1.5f, 1.5f, 1.5f);
	// Renderer Component
	MeshRenderer* meshRenderer2 = new MeshRenderer(mesh, testMaterial2);
	testGameObject3->add_Component(meshRenderer2);
	// Add to scene
	add_Component(meshRenderer2);
	add_GameObject(testGameObject3);

	// Add Systems to scene
	add_System(new TurnTable());
}


TestScene::~TestScene()
{
}
