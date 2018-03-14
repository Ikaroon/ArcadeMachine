#include "SceneFalldown.h"

#include "TextureManager.h"
#include "ShaderManager.h"
#include "MaterialManager.h"
#include "MeshManager.h"

#include "Camera.h"
#include "MeshRenderer.h"

#include "TurnTable.h"
#include "Time.h"

#include "Cloud.h"
#include "CloudMover.h"

#include "Player.h"
#include "PlayerController.h"

#include "Bomb.h"
#include "Coin.h"
#include "ItemController.h"

SceneFalldown::SceneFalldown()
{
	// Textures
	TextureManager::clear();
	Texture* cloudAtlas = new Texture("CloudAtlas", "textures/falldown/background/cloudAtlas.png");
	Texture* playerTexture = new Texture("PlayerTexture", "textures/falldown/player.png");
	Texture* coinTexture = new Texture("CoinTexture", "textures/falldown/coin.png");
	Texture* bombTexture = new Texture("BombTexture", "textures/falldown/bombA.png");

	// Shaders
	ShaderManager::clear();
	Shader* cloudShader = new Shader("CloudShader", "shaders/falldown/cloud");
	Shader* standardShader = new Shader("StandardShader", "shaders/falldown/standard");

	// Materials
	MaterialManager::clear();

	// Clouds
	int CLOUD_COUNT = 9;
	for (int c = 0; c < CLOUD_COUNT; c++)
	{
		Material* cloudMaterial = new Material("CloudMat" + std::to_string(c), cloudShader);
		cloudMaterial->setTexture("_MainTex", cloudAtlas);
		cloudMaterial->setVector("_TexCount", glm::vec2(8, 8));
		cloudMaterial->setVector("_Color", glm::vec3(1, 1, 1));
		srand(time(0) + c);
		cloudMaterial->setInt("_TexPos", rand() % 64);
	}

	Material* playerMaterial = new Material("PlayerMat", standardShader);
	playerMaterial->setTexture("_MainTex", playerTexture);
	Material* bombMaterial = new Material("BombMat", standardShader);
	bombMaterial->setTexture("_MainTex", bombTexture);
	Material* coinMaterial = new Material("CoinMat", standardShader);
	coinMaterial->setTexture("_MainTex", coinTexture);

	// Meshes
	MeshManager::clear();
	Mesh* cloudMesh = new Mesh("CloudMesh", "models/falldown/facingPlane.obj");
	Mesh* facingMesh = new Mesh("FacingMesh", "models/falldown/facingPlane.obj");


	// Scene \\

	// Camera GO
	GameObject* cameraObject = new GameObject("Camera Obj");
	cameraObject->get_Transform()->m_LocalPosition = glm::vec3(0.0f, 0.0f, 1.0f);
	cameraObject->get_Transform()->set_LocalEulerAngles(0.0f, 180.0f, 0.0f);
	// Camera Component
	Camera* cameraComponent = new Camera(45.0f, 0.1f, 100.0f, glm::vec3(100.0f / 255.0f, 180.0f / 255.0f, 200.0f / 255.0f));
	cameraObject->add_Component(cameraComponent);
	// Add to scene
	add_Component(cameraComponent);
	add_GameObject(cameraObject);

	// Clouds
	for (int c = 0; c < CLOUD_COUNT; c++)
	{
		GameObject* cloudObject = new GameObject("Cloud");
		// Transformated
		srand(time(0) + c * 2);
		float y = ((rand() % 81) - 40) * 0.1f;
		srand(time(0) + c * 5);
		float z = ((rand() % 51) * 0.1f + 1.0f);
		z = -(z * z);
		srand(time(0) + c);
		float x = ((rand() % (int)(41 + abs(z) * 10)) - (20 + (abs(z) * 5))) * 0.1f;

		Material* cloudMaterial = MaterialManager::getMaterial("CloudMat" + std::to_string(c));
		glm::vec3 color = glm::mix(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(100.0f / 255.0f, 180.0f / 255.0f, 200.0f / 255.0f), abs(z + 1.0f) / 25 * 0.7f);
		cloudMaterial->setVector("_Color", color);

		cloudObject->get_Transform()->m_LocalPosition = glm::vec3(x, y, z);
		cloudObject->get_Transform()->set_LocalEulerAngles(0.0f, 0.0f, 0.0f);
		cloudObject->get_Transform()->m_LocalScale = glm::vec3(10.0f, 10.0f, 10.0f);
		// Renderer Component
		MeshRenderer* cloudRenderer = new MeshRenderer(cloudMesh, cloudMaterial);
		cloudObject->add_Component(cloudRenderer);
		// Clouds
		Cloud* cloudComponent = new Cloud(cloudMaterial);
		cloudObject->add_Component(cloudComponent);
		// Add to scene
		add_Component(cloudComponent);
		add_Component(cloudRenderer);
		add_GameObject(cloudObject);
	}

	// Player
	GameObject* playerObject = new GameObject("Player");
	playerObject->get_Transform()->m_LocalPosition = glm::vec3(0.0f, 0.3f, 0.0f);
	playerObject->get_Transform()->set_LocalEulerAngles(0.0f, 0.0f, 0.0f);
	playerObject->get_Transform()->m_LocalScale = glm::vec3(0.25f, 0.25f, 0.25f);
	// Renderer Component
	MeshRenderer* playerRenderer = new MeshRenderer(facingMesh, playerMaterial);
	playerObject->add_Component(playerRenderer);
	// Player Component
	Player* playerComponent = new Player();
	playerObject->add_Component(playerComponent);
	// Add to scene
	add_Component(playerComponent);
	add_Component(playerRenderer);
	add_GameObject(playerObject);

	// Bombs
	int BOMB_COUNT = 10;

	for (int b = 0; b < BOMB_COUNT; b++)
	{
		// Bomb
		GameObject* bombObject = new GameObject("Bomb");
		bombObject->get_Transform()->m_LocalPosition = glm::vec3(0.5f, -0.5f * b, 0.0f);
		bombObject->get_Transform()->set_LocalEulerAngles(0.0f, 0.0f, 0.0f);
		bombObject->get_Transform()->m_LocalScale = glm::vec3(0.25f, 0.25f, 0.25f);
		// Renderer Component
		MeshRenderer* bombRenderer = new MeshRenderer(facingMesh, bombMaterial);
		bombObject->add_Component(bombRenderer);
		// Player Component
		Bomb* bombComponent = new Bomb(1.5f);
		bombObject->add_Component(bombComponent);
		// Add to scene
		add_Component(bombComponent);
		add_Component(bombRenderer);
		add_GameObject(bombObject);
	}

	// Coins
	int COIN_COUNT = 4;

	for (int c = 0; c < COIN_COUNT; c++)
	{
		// Coin
		GameObject* coinObject = new GameObject("Coin");
		coinObject->get_Transform()->m_LocalPosition = glm::vec3(-0.5f, -0.5f * c, 0.0f);
		coinObject->get_Transform()->set_LocalEulerAngles(0.0f, 0.0f, 0.0f);
		coinObject->get_Transform()->m_LocalScale = glm::vec3(0.125f, 0.125f, 0.125f);
		// Renderer Component
		MeshRenderer* coinRenderer = new MeshRenderer(facingMesh, coinMaterial);
		coinObject->add_Component(coinRenderer);
		// Player Component
		Coin* coinComponent = new Coin(1);
		coinObject->add_Component(coinComponent);
		// Add to scene
		add_Component(coinComponent);
		add_Component(coinRenderer);
		add_GameObject(coinObject);
	}

	add_System(new CloudMover());
	add_System(new PlayerController());
	add_System(new ItemController());

}