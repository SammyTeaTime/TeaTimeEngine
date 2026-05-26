#pragma once

#include "IEvent.h"

class GenericEvent : public IEvent
{
private:
  std::string _eventName;

public:
  GenericEvent(const std::string& eventName) : _eventName(eventName) {}
  ~GenericEvent() = default;

  std::string GetName() const override
  {
    return _eventName;
  }
};