#include "Services/SFMLDebugDrawService.h"

#include "Application.h"

void SFMLDebugDrawService::DrawRectangle(
  const sf::Vector2f& position,
  const sf::Vector2f& size,
  const sf::Color& colour)
{
  auto rectangle = sf::RectangleShape(size);
  rectangle.setOrigin(size * 0.5f);
  rectangle.setPosition(position);
  rectangle.setOutlineColor(colour);
  rectangle.setOutlineThickness(2.0f);

  GetRenderWindow().draw(rectangle);
}

void SFMLDebugDrawService::DrawCircle(
  const sf::Vector2f& position,
  const float& radius,
  const sf::Color& colour)
{
  auto circle = sf::CircleShape(radius);
  circle.setOrigin({ radius * 0.5f , radius * 0.5f });
  circle.setPosition(position);
  circle.setOutlineColor(colour);
  circle.setOutlineThickness(2.0f);

  GetRenderWindow().draw(circle);
}

sf::RenderWindow& SFMLDebugDrawService::GetRenderWindow()
{
  if (_renderWindow != nullptr)
  {
    return *_renderWindow;
  }

  _renderWindow = &Application::GetInstance()->GetRenderWindow();
  return *_renderWindow;
}