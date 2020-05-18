#pragma once

class AIComponent;


class AIState
{
public:
	AIState( AIComponent* owner )
		: _owner( owner )
	{
	
	}

	virtual void update( float deltaTime ) noexcept = 0;
	virtual void onEnter( void ) noexcept = 0;
	virtual void onExit( void ) noexcept = 0;

	virtual const char* getName( void ) const noexcept = 0;

protected:
	AIComponent* _owner;
};

class AIPatrol : public AIState
{
	AIPatrol( AIComponent* owner )
		: AIState( owner )
	{
	
	}

	void update( float deltaTime ) noexcept override;
	void onEnter( void ) noexcept override;
	void onExit( void ) noexcept override;
	const char* getName( void ) const noexcept override
	{
		return "Patrol";
	}
};

class AIDeath : public AIState
{
	AIDeath( AIComponent* owner )
		:AIState( owner )
	{

	}

	void update( float deltaTime ) noexcept override;
	void onEnter( void ) noexcept override;
	void onExit( void ) noexcept override;
	const char* getName( void ) const noexcept override
	{
		return "Death";
	}
};

class AIAttack : public AIState
{
public:
	AIAttack( AIComponent* owner )
		:AIState( owner )
	{
	
	}

	void update( float deltaTime ) noexcept override;
	void onEnter( void ) noexcept override;
	void onExit( void ) noexcept override;
	const char* getName( void ) const noexcept override
	{
		return "Attach";
	}
};