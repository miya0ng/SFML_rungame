#include "stdafx.h"
#include "Cookie.h"
#include "SpriteGo.h"

Cookie::Cookie(const std::string& texId, const std::string& name)
	: GameObject(name),texId(texId)
{
}

void Cookie::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	cookieOrigin.setPosition(pos);
}

void Cookie::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	cookieOrigin.setRotation(rot);
}

void Cookie::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	cookieOrigin.setScale(s);
}

void Cookie::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	cookieOrigin.setOrigin(o);
}

void Cookie::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(cookieOrigin, preset);
	}
}

bool Cookie::BufferCheck(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isBuffed)
	{
		std::cout << "버프" << std::endl;
		isBuffed = true;
	}
	if (isBuffed)
	{
		buffTimer -= dt;
		SetSpeed(2000);
	}
	if (buffTimer <= 0.f)
	{
		std::cout << "버프 종료!!!" << std::endl;
		isBuffed = false;
		SetSpeed(100);
	}
	std::cout << buffTimer << std::endl;

	return false;
}

bool Cookie::cookieJump(float dt)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		return true;
	}
	return false;
}

void Cookie::Init()
{
	texId = "img/cookieimg/cookie1/player_attack.png";
	/*
	animator.SetTarget(&body);

	animator.AddEvent("Idle", 0,
		[]()
		{
			std::cout << "!!" << std::endl;
		}
	);
	*/
}

void Cookie::Release()
{
	
}

void Cookie::Reset()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	SetOrigin(Origins::MC);
	cookieOrigin.setTexture(TEXTURE_MGR.Get(texId));
	SetPosition({ 50.f, 20.f });

	/*
	animator.Play("animations/idle.csv");
	*/
}

void Cookie::Update(float dt)
{
	BufferCheck(dt);

	/* ddddddddddddddddddddddddddddddddddddddddddddd
	if (isGrounded && InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		isGrounded = false;
		velocity.y = -500.f;
		animator.Play("animations/jump.csv");
	}
	if (!isGrounded)
	{
		velocity += gravity * dt;
	}
	position += velocity * dt;
	if (position.y > 0.f)
	{
		velocity.y = 0.f;
		position.y = 0.f;
		isGrounded = true;
	}
	SetPosition(position);

	*/

	/* ddddddddddddddddddddddddddddddddddddddddddddd
		animator.SetTarget(&body);

	animator.AddEvent("Idle", 0,
		[]()
		{
			std::cout << "!!" << std::endl;
		}
	);
	*/

	/*
	 else if (animator.GetCurrentClipId()=="jump"&&isGrounded)
	 {
		if(h==0.f)
		{
		   animator.Play("animations/idle.csv");
		}
		else
		{
			animator.Play("animations/run/csv");
	   }
	 }
	*/

}

void Cookie::Draw(sf::RenderWindow& window)
{
	//window.clear(isBuffed ? sf::Color::Cyan : sf::Color::Black);
	window.draw(cookieOrigin);
}