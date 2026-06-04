#include "Application.h"

#include <filesystem>
#include <fstream>

#include <nlohmann/json.hpp>
using Json = nlohmann::json;

#include "Entities/EntityFactories.h"
#include "Entities/IGameEntity.h"
#include "Services/FontService.h"
#include "Services/ParticlesService.h"
#include "Services/RandomService.h"
#include "Services/RenderWindowService.h"
#include "Services/ServiceLocator.h"
#include "Services/SceneLoaderService.h"
#include "Services/ScenesService.h"
#include "Services/SFMLDebugDrawService.h"
#include "Services/SynchronousEventService.h"
#include "Scene.h"

Application::Application()
{
  _renderWindow = std::make_shared<sf::RenderWindow>
    (sf::VideoMode({ 800, 600 }), "Tea Time Application");
  _renderWindow->setKeyRepeatEnabled(false);
  _serviceLocator = std::make_shared<ServiceLocator>();
}

bool Application::IsWindowOpen()
{
  return _renderWindow->isOpen();
}

void Application::ProcessEvents()
{
  _renderWindow->handleEvents([this](const auto& type)
    {
      this->HandleEvent(type);
    });
}

void Application::Setup()
{
  ApplyApplicationConfig();
  CreateAndStartServices();
}

void Application::Update()
{
  float dt = _clock.restart().asSeconds();
  dt = fminf(dt, _frameDeltaTimeLimit);

  auto scenes = _scenesService.lock()->GetScenes();

  for (auto& scene : scenes)
  {
    scene.lock()->Update(dt);
  }
}

void Application::Render()
{
  _renderWindow->clear();

  auto scenes = _scenesService.lock()->GetScenes();

  for (auto& scene : scenes)
  {
    scene.lock()->Render(*_renderWindow);
  }

  _renderWindow->display();
}

void Application::Destroy()
{
  auto scenes = _scenesService.lock()->GetScenes();

  for (auto& scene : scenes)
  {
    scene.lock()->Destroy();
  }
}

void Application::LoadStartupScene()
{
  _scenesService.lock()->LoadScene(_startupScenePath);
}

#pragma region System Event Handling
void Application::HandleEvent(const sf::Event::KeyPressed& event)
{
}

void Application::HandleEvent(const sf::Event::KeyReleased& event)
{
  if (event.code == sf::Keyboard::Key::Escape)
  {
    _renderWindow->close();
  }
}

void Application::HandleEvent(const sf::Event::Closed& event)
{
  _renderWindow->close();
}
#pragma endregion

void Application::ApplyApplicationConfig()
{
  const std::string configPath = "Config/Application.json";
  const std::string engineFallbackScene = 
    "Assets/Scenes/EngineFallbackScene.json";

  if (!std::filesystem::exists(configPath))
  {
    _startupScenePath = engineFallbackScene;
    return;
  }

  std::ifstream fileStream = std::ifstream(configPath);
  Json configJson = Json::parse(fileStream);

  if (configJson.contains("startupScene") == false || 
    configJson["startupScene"] == "")
  {
    _startupScenePath = engineFallbackScene;
  }
  else
  {
    _startupScenePath = configJson["startupScene"];
  }
  
  if (configJson.contains("window") && configJson["window"].is_object())
  {
    auto& windowConfig = configJson["window"];

    if (windowConfig.contains("title") && windowConfig["title"].is_string())
    {
      std::string title = windowConfig["title"];
      _renderWindow->setTitle(title);
    }

    if (windowConfig.contains("width") && windowConfig.contains("height") &&
      windowConfig["width"].is_number() && windowConfig["height"].is_number())
    {
      unsigned int width = windowConfig["width"];
      unsigned int height = windowConfig["height"];
      _renderWindow->setSize({ width, height });
    }

    if (windowConfig.contains("vsync") && windowConfig["vsync"].is_boolean())
    {
      bool vsync = windowConfig["vsync"];
      _renderWindow->setVerticalSyncEnabled(vsync);
    }
  }

  if (configJson.contains("fpsLimit") && 
    configJson["fpsLimit"].is_number())
  {
    float fpsLimit = configJson["fpsLimit"];
    _frameDeltaTimeLimit = 1.0f / fpsLimit;
  }
}

void Application::CreateAndStartServices()
{
  auto eventService = std::make_shared<SynchronousEventService>();
  _serviceLocator->RegisterService<IEventService>(eventService);

  auto debugDrawService =
    std::make_shared<SFMLDebugDrawService>(_renderWindow);
  _serviceLocator->RegisterService<IDebugDrawService>(debugDrawService);

  auto fontService = std::make_shared<FontService>();
  _serviceLocator->RegisterService<IFontService>(fontService);

  auto particlesService = std::make_shared<ParticlesService>();
  _serviceLocator->RegisterService<IParticlesService>(particlesService);

  auto randomService = std::make_shared<RandomService>();
  _serviceLocator->RegisterService<IRandomService>(randomService);

  auto renderWindowService =
    std::make_shared<RenderWindowService>(_renderWindow);
  _serviceLocator->RegisterService<IRenderWindowService>(renderWindowService);

  auto sceneLoaderService =
    std::make_shared<SceneLoaderService>(_serviceLocator);
  _serviceLocator->RegisterService<ISceneLoaderService>(sceneLoaderService);

  auto scenesService = std::make_shared<ScenesService>(sceneLoaderService);
  _serviceLocator->RegisterService<IScenesService>(scenesService);
  _scenesService = scenesService;

  fontService->LoadFonts();
  sceneLoaderService->RegisterFactory("TextEntity",
    std::make_shared<TextEntityFactory>());
  sceneLoaderService->RegisterFactory("FPSDisplayEntity",
    std::make_shared<FPSDisplayEntityFactory>());
}