#pragma once

class Actor;


class Component
{
public:

	Component( Actor* owner,int updateOrder = 100 );

	virtual ~Component();

	virtual void update( float deltaTime ) noexcept;

	virtual void processInput( const uint8_t* keyState ) noexcept {}

	int getUpdateOrder() const noexcept { return _updateOrder; }

protected:

	Actor* _owner;
	int _updateOrder;
};