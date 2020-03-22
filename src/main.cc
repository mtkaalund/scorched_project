#include <list>
#include <memory>
#include <string>

#include <OneLoneCoder/olcPixelGameEngine.h>

#include "cPhysicObject.h"
#include "cParticle.h"
#include "Generic.h"

class Scorched_project : public olc::PixelGameEngine
{
	std::list<std::unique_ptr<cPhysicsObject>> list_of_objects;

	int nMapWidth = 1024;
	int nMapHeight = ScreenHeight();
	
	olc::vf2d fCamera = {0.0f, 0.0f};
	float fCameraSpeed = 200.0f;

public:
	// Constructor
	Scorched_project()
	{
		sAppName = "Scorched project";
	}

	bool OnUserCreate()
	{
		for (int i = 0; i < 2; i++)
		{
			list_of_objects.push_back(
				std::unique_ptr<cParticle>(
					new cParticle(
						{randf(0.0f, (float)ScreenWidth()),
						 randf(0.0f, 100.0f)})));
		}

		return true;
	}

	bool OnUserUpdate(float fElapsedTime)
	{
		// Game main loop
		Clear(olc::BLUE);

		// Before handling inputs, we'll need to check if window has focus
		if (IsFocused())
		{
			// Putting mouse position in a vector
			olc::vf2d mouse_pos = {(float)GetMouseX(), (float)GetMouseY()};

			if (GetKey(olc::Key::ENTER).bReleased)
			{
				std::cout << "Enter has been released" << std::endl;
			}

			// Handle camera position
			if( mouse_pos.x < 5 ) fCamera.x -= fCameraSpeed * fElapsedTime;
			if( mouse_pos.x > ScreenWidth() - 5 ) fCamera.x += fCameraSpeed * fElapsedTime;
			if( mouse_pos.y < 5 ) fCamera.y -= fCameraSpeed * fElapsedTime;
			if( mouse_pos.y > ScreenHeight() - 5 ) fCamera.y += fCameraSpeed * fElapsedTime;
			// Clamp camera boundaries
			if( fCamera.x < 0 )	fCamera.x = 0;
			if( fCamera.y < 0 ) fCamera.y = 0;
			if( fCamera.x >= nMapWidth - ScreenWidth() ) fCamera.x = nMapWidth - ScreenWidth();
			if( fCamera.y >= nMapHeight - ScreenHeight() ) fCamera.y = nMapHeight - ScreenHeight();

		}

		// Run through the list of object and update it
		for (auto &p : list_of_objects)
		{
			p->Update(fElapsedTime);
		}

		// Remove dead objects from list
		list_of_objects.remove_if([](std::unique_ptr<cPhysicsObject> &p){ return p->bIsDead;});
		// Runthrough the list and displays the objects
		for (auto &p : list_of_objects)
		{
			p->Display(this);
		}

		DrawString({0, 0}, "Game Objects: " + std::to_string(list_of_objects.size()));
		DrawString({0, 8}, "Camera: " + std::to_string(fCamera.x) + "," + std::to_string(fCamera.y));
		return true;
	}

	bool OnUserDestroy()
	{
		// Only use if need to destroy some thing
		list_of_objects.clear();

		return true;
	}
};

int main(int argc, char *argv[])
{
	Scorched_project game;
	if (game.Construct(640, 480, 2, 2))
	{
		game.Start();
	}
	else
	{
		std::cerr << "Could'nt create PixelGameEngine" << std::endl;
		return 1;
	}

	return 0;
}
