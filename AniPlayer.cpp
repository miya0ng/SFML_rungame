#include "stdafx.h"
#include "AniPlayer.h"

AniPlayer::AniPlayer(const std::string& name)
	: GameObject(name)
{
}

void AniPlayer::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void AniPlayer::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void AniPlayer::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void AniPlayer::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		Utils::SetOrigin(body, originPreset);
	}
}

void AniPlayer::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = Utils::SetOrigin(body, originPreset);
}

bool AniPlayer::BufferCheck(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isBuffed)
	{
		//std::cout << "버프" << std::endl;
		isBuffed = true;
	}
	if (isBuffed)
	{
		buffTimer -= dt;
		SetSpeed(2000);
	}
	if (buffTimer <= 0.f)
	{
		buffTimer = 0.f;
		//std::cout << "버프 종료!!!" << std::endl;
		isBuffed = false;
		SetSpeed(100);
	}
	
	return false;
}

bool  AniPlayer::cookieJump(float dt)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		return true;
	}
	return false;
}

void AniPlayer::Init()
{
	animator.SetTarget(&body);

	animator.AddEvent("Idle", 0,
		[]()
		{
			std::cout << "!!" << std::endl;
		}
	);

	animator.AddEvent("Run", 0,
		[]()
		{
			std::cout << "??" << std::endl;
		}
	);
}

void AniPlayer::Release()
{
}

void AniPlayer::Reset()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	SetPosition({ -300.f, -280.f });//cookie position have to be changed because of the ground and viewoption
	std::cout << GetPosition().x << GetPosition().y << std::endl;
	animator.Play("animations/idle.csv");
	SetOrigin(Origins::BC);
}

void AniPlayer::Update(float dt)
{
	animator.Update(dt);
	BufferCheck(dt);

	float h = 0.f;
	//if (isGrounded)
	//{
		//h = InputMgr::GetAxis(Axis::Horizontal);
	h = dt;
		velocity.x = h * speed;
	//}
	if (isGrounded && InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		isGrounded = false;
		velocity.y = -500.f;
		//animator.Play("animations/cookiejump.csv");
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

	if (h != 0.f)
	{
		SetScale(h > 0.f ? sf::Vector2f(1.0f, 1.0) : sf::Vector2f(- 1.f, 1.0f));
	}

	// Ani
	if (animator.GetCurrentClipId() == "Idle")
	{
		if (h != 0.f)
		{
			animator.Play("animations/cookierun.csv");
		}
	}
	else if (animator.GetCurrentClipId() == "Run")
	{
		if (h == 0.f)
		{
			animator.Play("animations/idle.csv");
		}
	}
	else if (animator.GetCurrentClipId() == "Jump" && isGrounded)
	{
		if (h == 0.f)
		{
			animator.Play("animations/idle.csv");
		}
		else
		{
			animator.Play("animations/cookierun.csv");
		}
	}
}

void AniPlayer::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
