#include "Services/SFMLDebugDrawService.h"

SFMLDebugDrawService::SFMLDebugDrawService(
  std::weak_ptr<sf::RenderWindow> renderWindow) :
    _renderWindow(renderWindow)
{
}

void SFMLDebugDrawService::DrawRectangle(
  const sf::Vector2f& position,
  const sf::Vector2f& size,
  const sf::Color& colour)
{
  auto rectangle = sf::RectangleShape(size);
  rectangle.setOrigin(size * 0.5f);
  rectangle.setPosition(position);
  rectangle.setFillColor(sf::Color::Transparent);
  rectangle.setOutlineColor(colour);
  rectangle.setOutlineThickness(2.0f);

  _renderWindow.lock()->draw(rectangle);
}

void SFMLDebugDrawService::DrawCircle(
  const sf::Vector2f& position,
  const float& radius,
  const sf::Color& colour)
{
  auto circle = sf::CircleShape(radius);
  circle.setOrigin({ radius * 0.5f , radius * 0.5f });
  circle.setPosition(position);
  circle.setFillColor(sf::Color::Transparent);
  circle.setOutlineColor(colour);
  circle.setOutlineThickness(2.0f);

  _renderWindow.lock()->draw(circle);
}