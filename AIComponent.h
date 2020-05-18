#pragma once

#include "Component.h"
#include <unordered_map>
#include <string>

class Actor;
class AIState;


class AIComponent : public Component
{
public:
	AIComponent( Actor* owner );

	void update( float deltaTime ) noexcept override;
	void changeState( const std::string& name );

	void registerState( AIState* state ) noexcept;

private:
	std::unordered_map<std::string, AIState*> _stateMap;
	AIState* _currentState;
};