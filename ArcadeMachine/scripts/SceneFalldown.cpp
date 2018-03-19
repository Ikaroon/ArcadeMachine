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
#include "Heal.h"
#include "SpeedChanger.h"
#include "ItemController.h"

SceneFalldown::SceneFalldown()
{
	// Textures
	TextureManager::clear();
	Texture* cloudAtlas = new Texture("CloudAtlas", "textures/falldown/background/cloudAtlas.png");

	Texture* playerTexture = new Texture("PlayerTexture", "textures/falldown/player.png");

	Texture* coinTexture = new Texture("CoinTexture", "textures/falldown/coin.png");
	Texture* coinBTexture = new Texture("CoinBTexture", "textures/falldown/coinB.png");

	Texture* bombTexture = new Texture("BombTexture", "textures/falldown/bombA.png");
	Texture* bombBTexture = new Texture("BombBTexture", "textures/falldown/bombB.png");

	Texture* numbersTexture = new Texture("NumbersTexture", "textures/falldown/numbers.png", Texture::INTERPOLATION::BILINEAR);

	Texture* heartTexture = new Texture("HeartTexture", "textures/falldown/heart.png", Texture::INTERPOLATION::BILINEAR);
	Texture* heartFillMapTexture = new Texture("HeartFillmapTexture", "textures/falldown/heartFillMap.png", Texture::INTERPOLATION::BILINEAR);

	Texture* healTexture = new Texture("HealTexture", "textures/falldown/heal.png");
	Texture* speedUpTexture = new Texture("SpeedUpTexture", "textures/falldown/speedUp.png");
	Texture* slowDownTexture = new Texture("SlowDownTexture", "textures/falldown/slowDown.png");
	Texture* clearTexture = new Texture("ClearTexture", "textures/falldown/clear.png");

	// Shaders
	ShaderManager::clear();
	Shader* cloudShader = new Shader("CloudShader", "shaders/falldown/cloud");
	Shader* standardShader = new Shader("StandardShader", "shaders/falldown/standard");
	Shader* heartFillShader = new Shader("HeartFillShader", "shaders/falldown/heartFill");

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
	Material* bombBMaterial = new Material("BombBMat", standardShader);
	bombBMaterial->setTexture("_MainTex", bombBTexture);
	Material* coinMaterial = new Material("CoinMat", standardShader);
	coinMaterial->setTexture("_MainTex", coinTexture);
	Material* coinBMaterial = new Material("CoinBMat", standardShader);
	coinBMaterial->setTexture("_MainTex", coinBTexture);
	Material* healMaterial = new Material("HealMat", standardShader);
	healMaterial->setTexture("_MainTex", healTexture);
	Material* speedUpMaterial = new Material("SpeedUpMat", standardShader);
	speedUpMaterial->setTexture("_MainTex", speedUpTexture);
	Material* slowDownMaterial = new Material("SlowDownMat", standardShader);
	slowDownMaterial->setTexture("_MainTex", slowDownTexture);
	Material* clearMaterial = new Material("ClearMat", standardShader);
	clearMaterial->setTexture("_MainTex", clearTexture);

	Material* heartMaterial = new Material("HeartMat", standardShader);
	heartMaterial->setTexture("_MainTex", heartTexture);

	Material* heartFillMaterial = new Material("HeartFillMat", heartFillShader);
	heartFillMaterial->setTexture("_MainTex", heartFillMapTexture);
	heartFillMaterial->setVector("_Color", glm::vec3(1, 0, 0));
	heartFillMaterial->setVector("_Fill", glm::vec2(1, 0));

	Material* score1Material = new Material("Score1Mat", cloudShader);
	score1Material->setTexture("_MainTex", numbersTexture);
	score1Material->setVector("_TexCount", glm::vec2(4, 4));
	score1Material->setVector("_Color", glm::vec3(1, 1, 1));
	score1Material->setInt("_TexPos", 0);

	Material* score10Material = new Material("Score10Mat", cloudShader);
	score10Material->setTexture("_MainTex", numbersTexture);
	score10Material->setVector("_TexCount", glm::vec2(4, 4));
	score10Material->setVector("_Color", glm::vec3(1, 1, 1));
	score10Material->setInt("_TexPos", 0);

	Material* score100Material = new Material("Score100Mat", cloudShader);
	score100Material->setTexture("_MainTex", numbersTexture);
	score100Material->setVector("_TexCount", glm::vec2(4, 4));
	score100Material->setVector("_Color", glm::vec3(1, 1, 1));
	score100Material->setInt("_TexPos", 0);

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
	int BOMB_COUNT = 30;

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
		Bomb* bombComponent = new Bomb(0.05f);
		bombObject->add_Component(bombComponent);
		// Add to scene
		add_Component(bombComponent);
		add_Component(bombRenderer);
		add_GameObject(bombObject);
	}

	// Special Bombs
	int SPECIAL_BOMB_COUNT = 10;

	for (int b = 0; b < SPECIAL_BOMB_COUNT; b++)
	{
		// Bomb
		GameObject* bombObject = new GameObject("SpecialBomb");
		bombObject->get_Transform()->m_LocalPosition = glm::vec3(0.5f, -0.5f * b - (BOMB_COUNT * 0.5f), 0.0f);
		bombObject->get_Transform()->set_LocalEulerAngles(0.0f, 0.0f, 0.0f);
		bombObject->get_Transform()->m_LocalScale = glm::vec3(0.25f, 0.25f, 0.25f);
		// Renderer Component
		MeshRenderer* bombRenderer = new MeshRenderer(facingMesh, bombBMaterial);
		bombObject->add_Component(bombRenderer);
		// Player Component
		Bomb* bombComponent = new Bomb(0.15f);
		bombObject->add_Component(bombComponent);
		// Add to scene
		add_Component(bombComponent);
		add_Component(bombRenderer);
		add_GameObject(bombObject);
	}

	// Super Bombs
	int SUPER_BOMB_COUNT = 2;

	for (int b = 0; b < SUPER_BOMB_COUNT; b++)
	{
		// Bomb
		GameObject* bombObject = new GameObject("SuperBomb");
		bombObject->get_Transform()->m_LocalPosition = glm::vec3(0.5f, -0.5f * b - (BOMB_COUNT * 0.5f) - (SPECIAL_BOMB_COUNT * 0.5f), 0.0f);
		bombObject->get_Transform()->set_LocalEulerAngles(0.0f, 0.0f, 0.0f);
		bombObject->get_Transform()->m_LocalScale = glm::vec3(0.5f, 0.5f, 0.5f);
		// Renderer Component
		MeshRenderer* bombRenderer = new MeshRenderer(facingMesh, bombBMaterial);
		bombObject->add_Component(bombRenderer);
		// Player Component
		Bomb* bombComponent = new Bomb(0.5f);
		bombObject->add_Component(bombComponent);
		// Add to scene
		add_Component(bombComponent);
		add_Component(bombRenderer);
		add_GameObject(bombObject);
	}

	// Coins
	int COIN_COUNT = 20;

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

	// Super Coins
	int SUPER_COIN_COUNT = 5;

	for (int c = 0; c < SUPER_COIN_COUNT; c++)
	{
		// Coin
		GameObject* coinObject = new GameObject("SuperCoin");
		coinObject->get_Transform()->m_LocalPosition = glm::vec3(-0.5f, -0.5f * c - (COIN_COUNT * 0.5f), 0.0f);
		coinObject->get_Transform()->set_LocalEulerAngles(0.0f, 0.0f, 0.0f);
		coinObject->get_Transform()->m_LocalScale = glm::vec3(0.125f, 0.125f, 0.125f);
		// Renderer Component
		MeshRenderer* coinRenderer = new MeshRenderer(facingMesh, coinBMaterial);
		coinObject->add_Component(coinRenderer);
		// Player Component
		Coin* coinComponent = new Coin(5);
		coinObject->add_Component(coinComponent);
		// Add to scene
		add_Component(coinComponent);
		add_Component(coinRenderer);
		add_GameObject(coinObject);
	}

	// PowerUps

	// Heal PowerUP
	GameObject* healObject = new GameObject("Heal");
	healObject->get_Transform()->m_LocalPosition = glm::vec3(0.0f, -10.0f, 0.0f);
	healObject->get_Transform()->set_LocalEulerAngles(0.0f, 0.0f, 0.0f);
	healObject->get_Transform()->m_LocalScale = glm::vec3(0.25f, 0.25f, 0.25f);
	// Renderer Component
	MeshRenderer* healRenderer = new MeshRenderer(facingMesh, healMaterial);
	healObject->add_Component(healRenderer);
	// Player Component
	Heal* healComponent = new Heal(1.0f);
	healObject->add_Component(healComponent);
	// Add to scene
	add_Component(healComponent);
	add_Component(healRenderer);
	add_GameObject(healObject);

	// SpeedUp PowerUP
	GameObject* speedUpObject = new GameObject("SpeedUp");
	speedUpObject->get_Transform()->m_LocalPosition = glm::vec3(0.0f, -1.0f, 0.0f);
	speedUpObject->get_Transform()->set_LocalEulerAngles(0.0f, 0.0f, 0.0f);
	speedUpObject->get_Transform()->m_LocalScale = glm::vec3(0.25f, 0.25f, 0.25f);
	// Renderer Component
	MeshRenderer* speedUpRenderer = new MeshRenderer(facingMesh, speedUpMaterial);
	speedUpObject->add_Component(speedUpRenderer);
	// Player Component
	SpeedChanger* speedUpComponent = new SpeedChanger(1.75f);
	speedUpObject->add_Component(speedUpComponent);
	// Add to scene
	add_Component(speedUpComponent);
	add_Component(speedUpRenderer);
	add_GameObject(speedUpObject);

	// SlowDown PowerUP
	GameObject* slowDownObject = new GameObject("SlowDown");
	slowDownObject->get_Transform()->m_LocalPosition = glm::vec3(0.0f, -5.0f, 0.0f);
	slowDownObject->get_Transform()->set_LocalEulerAngles(0.0f, 0.0f, 0.0f);
	slowDownObject->get_Transform()->m_LocalScale = glm::vec3(0.25f, 0.25f, 0.25f);
	// Renderer Component
	MeshRenderer* slowDownRenderer = new MeshRenderer(facingMesh, slowDownMaterial);
	slowDownObject->add_Component(slowDownRenderer);
	// Player Component
	SpeedChanger* slowDownComponent = new SpeedChanger(0.8f);
	slowDownObject->add_Component(slowDownComponent);
	// Add to scene
	add_Component(slowDownComponent);
	add_Component(slowDownRenderer);
	add_GameObject(slowDownObject);


	// UI

	// Heart Background
	GameObject* heartObject = new GameObject("HeartBackground");
	heartObject->get_Transform()->m_LocalPosition = glm::vec3(0.625f, 0.35f, 0.0f);
	heartObject->get_Transform()->set_LocalEulerAngles(0.0f, 0.0f, 0.0f);
	heartObject->get_Transform()->m_LocalScale = glm::vec3(0.3f, 0.3f, 0.3f);
	// Renderer Component
	MeshRenderer* heartRenderer = new MeshRenderer(facingMesh, heartMaterial);
	heartObject->add_Component(heartRenderer);
	// Add to scene
	add_Component(heartRenderer);
	add_GameObject(heartObject);

	// Heart Filler Background
	GameObject* heartFillObject = new GameObject("HeartFillBackground");
	heartFillObject->get_Transform()->setParent(heartObject->get_Transform());
	heartFillObject->get_Transform()->m_LocalPosition = glm::vec3(0.0f, 0.0f, 0.0000001f);
	heartFillObject->get_Transform()->set_LocalEulerAngles(0.0f, 0.0f, 0.0f);
	heartFillObject->get_Transform()->m_LocalScale = glm::vec3(0.3f, 0.3f, 0.3f);
	// Renderer Component
	MeshRenderer* heartFillRenderer = new MeshRenderer(facingMesh, heartFillMaterial);
	heartFillObject->add_Component(heartFillRenderer);
	// Add to scene
	add_Component(heartFillRenderer);
	add_GameObject(heartFillObject);


	// Score 1
	GameObject* score1Object = new GameObject("Score1Object");
	score1Object->get_Transform()->m_LocalPosition = glm::vec3(-0.5985f, 0.35f, 0.0f);
	score1Object->get_Transform()->set_LocalEulerAngles(0.0f, 0.0f, 0.0f);
	score1Object->get_Transform()->m_LocalScale = glm::vec3(0.25f, 0.25f, 0.25f);
	// Renderer Component
	MeshRenderer* score1Renderer = new MeshRenderer(facingMesh, score1Material);
	score1Object->add_Component(score1Renderer);
	// Add to scene
	add_Component(score1Renderer);
	add_GameObject(score1Object);

	// Score 10
	GameObject* score10Object = new GameObject("Score10Object");
	score10Object->get_Transform()->m_LocalPosition = glm::vec3(-0.625f, 0.35f, 0.0f);
	score10Object->get_Transform()->set_LocalEulerAngles(0.0f, 0.0f, 0.0f);
	score10Object->get_Transform()->m_LocalScale = glm::vec3(0.25f, 0.25f, 0.25f);
	// Renderer Component
	MeshRenderer* score10Renderer = new MeshRenderer(facingMesh, score10Material);
	score10Object->add_Component(score10Renderer);
	// Add to scene
	add_Component(score10Renderer);
	add_GameObject(score10Object);

	// Score 100
	GameObject* score100Object = new GameObject("Score100Object");
	score100Object->get_Transform()->m_LocalPosition = glm::vec3(-0.6515f, 0.35f, 0.0f);
	score100Object->get_Transform()->set_LocalEulerAngles(0.0f, 0.0f, 0.0f);
	score100Object->get_Transform()->m_LocalScale = glm::vec3(0.25f, 0.25f, 0.25f);
	// Renderer Component
	MeshRenderer* score100Renderer = new MeshRenderer(facingMesh, score100Material);
	score100Object->add_Component(score100Renderer);
	// Add to scene
	add_Component(score100Renderer);
	add_GameObject(score100Object);

	add_System(new CloudMover());
	add_System(new PlayerController());
	add_System(new ItemController(heartFillMaterial, score1Material, score10Material, score100Material));

}