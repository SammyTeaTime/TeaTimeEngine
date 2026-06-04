#pragma once

#include "Services/IDebugDrawService.h"

class SFMLDebugDrawService : public IDebugDrawService
{
private:
  std::weak_ptr<sf::RenderWindow> _renderWindow;

public:
  SFMLDebugDrawService(std::weak_ptr<sf::RenderWindow> renderWindow);
  ~SFMLDebugDrawService() = default;

  void DrawRectangle(
    const sf::Vector2f& position,
    const sf::Vector2f& size,
    const sf::Color& colour) override;

  void DrawCircle(
    const sf::Vector2f& position,
    const float& radius,
    const sf::Color& colour) override;
};