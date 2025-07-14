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
		SetSpeed(1500);
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

bool AniPlayer::cookieJump()
{
	if (InputMgr::GetKeyDown(sf::Keyboard::W)&&isGrounded)
	{
		jumpCount++;
		velocity.y = -500.f;
		animator.Play("animations/cookiejump.csv");
		isGrounded = false;
		return true;
	}
	return false;
}

bool AniPlayer::cookieDoubleJump()
{
	if (InputMgr::GetKeyDown(sf::Keyboard::W) && jumpCount == 1)
	{
		jumpCount = 0;
		velocity.y = -500.f;
		animator.Play("animations/doublejump.csv");
		return true;
	}
	return false;
}

bool  AniPlayer::cookieSlide()
{
	
	if (InputMgr::GetKeyDown(sf::Keyboard::S))
	{
		animator.Play("animations/cookieslide.csv");
		if (InputMgr::GetKeyUp(sf::Keyboard::S))
		{
			animator.Play("animations/cookierun.csv");
		}
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
			//std::cout << "!!" << std::endl;
		}
	);

	animator.AddEvent("Run", 0,
		[]()
		{
			//std::cout << "??" << std::endl;
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
	SetPosition({ -300.f, -280.f });
	animator.Play("animations/cookierun.csv");
	SetOrigin(Origins::BC);
	SetScale({ 0.7f, 0.7f });
}

void AniPlayer::Update(float dt)
{
	animator.Update(dt);
	BufferCheck(dt);
	SetOrigin(Origins::BC);

	velocity.x = dt * speed;

	cookieDoubleJump();
	cookieJump();
	cookieSlide();	
	if (InputMgr::GetKeyUp(sf::Keyboard::S))
	{
		animator.Play("animations/cookierun.csv");
	}
	if (position.y > -280.f) 
	{
		velocity.y = 0.f;
		position.y = -280.f;
		isGrounded = true;
	}

	if (!isGrounded)
	{
		velocity += gravity * dt;
	}
	position += velocity * dt;
	SetPosition(position);

	// Ani
	if (animator.GetCurrentClipId() == "Idle")
	{
		if (dt != 0.f)
		{
			animator.Play("animations/cookierun.csv");
		}
	}
	else if (animator.GetCurrentClipId() == "Run")
	{
		if (dt == 0.f)
		{
			animator.Play("animations/idle.csv");
		}
	}
	else if (animator.GetCurrentClipId() == "Jump" && isGrounded
		|| animator.GetCurrentClipId() == "DoubleJump"&& isGrounded)
	{
		animator.Play("animations/cookierun.csv");
	}
}

void AniPlayer::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
