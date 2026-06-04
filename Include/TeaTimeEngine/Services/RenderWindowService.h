#pragma once

#include "Services/IRenderWindowService.h"

#include <memory>

class RenderWindowService : public IRenderWindowService
{
private:
  std::weak_ptr<sf::RenderWindow> _renderWindow;

public:
  RenderWindowService(std::weak_ptr<sf::RenderWindow> renderWindow) :
    _renderWindow(renderWindow) {}
  ~RenderWindowService() = default;

  sf::RenderWindow& GetRenderWindow() override 
  { 
    return *(_renderWindow.lock());
  }
};