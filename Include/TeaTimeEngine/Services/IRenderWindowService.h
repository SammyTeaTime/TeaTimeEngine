#pragma once

namespace sf
{
  class RenderWindow;
}

class IRenderWindowService
{
public:
  virtual ~IRenderWindowService() = default;

  virtual sf::RenderWindow& GetRenderWindow() = 0;
};