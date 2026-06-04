// Application.h
// Wraps an SFML window and provides core game engine functions
#pragma once

#include <memory>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

class IScenesService;
class ServiceLocator;

class Application
{
private:
  sf::Clock _clock;
  std::shared_ptr<sf::RenderWindow> _renderWindow = nullptr;
  std::shared_ptr<ServiceLocator> _serviceLocator = nullptr;
  std::weak_ptr<IScenesService> _scenesService;

  std::string _startupScenePath = "";
  float _frameDeltaTimeLimit = 1.0f / 120.0f;

public:
  Application();
  ~Application() = default;

  bool IsWindowOpen();
  void ProcessEvents();

  void Setup();
  void Update();
  void Render();
  void Destroy();

  void LoadStartupScene();

  std::weak_ptr<ServiceLocator> GetServiceLocator() const
  {
    return _serviceLocator;
  }

private:
  void HandleEvent(const sf::Event::KeyPressed& event);
  void HandleEvent(const sf::Event::KeyReleased& event);
  void HandleEvent(const sf::Event::Closed& event);
  void HandleEvent(const auto&) {}

  void ApplyApplicationConfig();
  void CreateAndStartServices();
};
