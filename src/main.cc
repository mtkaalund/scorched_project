#include <list>
#include <memory>
#include <string>
#include <vector>

#include <OneLoneCoder/olcPixelGameEngine.h>

#include "cPhysicObject.h"
#include "cParticle.h"
#include "Generic.h"

class Scorched_project : public olc::PixelGameEngine
{
private:
	std::list<std::unique_ptr<cPhysicsObject>> list_of_objects;

	const int nMapWidth = 1024;
	const int nMapHeight = ScreenHeight();

	std::vector<unsigned char> map;

	olc::vf2d fCameraPos = {0.0f, 0.0f};
	float fCameraSpeed = 200.0f;

public:
	// Constructor
	Scorched_project()
	{
		sAppName = "Scorched project";
	}

	bool OnUserCreate()
	{
		std::cout << "OnUserCreate" << std::endl;
		map.resize(nMapWidth*nMapHeight);
		std::cout << "\tmap.resize" << std::endl;
		for(int i = 0; i < map.size(); i++ )
		{
			map[i] = 0;
		}

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

			if (GetKey(olc::Key::ENTER).bReleased)
			{
				std::cout << "Enter has been released" << std::endl;
				float *n = new float[nMapWidth];
				float *out = new float[nMapWidth];

				for (int i = 0; i < 10; i++)
				{
					n[i] = randf(1.0f, 0.0f);
				}

				n[0] = 0.8;

				PerlinNoise1D(nMapWidth, n, 8, 2.0f, out);

				for( int x = 0; x < nMapWidth; x++ )
				{
					for( int y = 0; y < nMapHeight; y++ )
					{
						if( y >= out[x] * nMapHeight )
						{
							map[ y * nMapWidth + x ] = 1;
						} else {
							map[ y * nMapWidth + x ] = 0;
						}
					}
				}

				delete[] n;
				delete[] out;
			}


		}

			// Handle camera position
			if (GetMouseX() < 5)
				fCameraPos.x -= fCameraSpeed * fElapsedTime;
			if (GetMouseX() > ScreenWidth() - 5)
				fCameraPos.x += fCameraSpeed * fElapsedTime;
			if (GetMouseY() < 5)
				fCameraPos.y -= fCameraSpeed * fElapsedTime;
			if (GetMouseY() > ScreenHeight() - 5)
				fCameraPos.y += fCameraSpeed * fElapsedTime;
			// Clamp camera boundaries
			if (fCameraPos.x < 0)
				fCameraPos.x = 0;
			if (fCameraPos.y < 0)
				fCameraPos.y = 0;
			if (fCameraPos.x >= nMapWidth - ScreenWidth())
				fCameraPos.x = nMapWidth - ScreenWidth();
			// if (fCameraPos.y > nMapHeight - ScreenHeight())
			// 	fCameraPos.y = nMapHeight - ScreenHeight();

		// Run through the list of object and update it
		for (auto &p : list_of_objects)
		{
			p->Update(fElapsedTime);
		}

		// Remove dead objects from list
		list_of_objects.remove_if([](std::unique_ptr<cPhysicsObject> &p) { return p->bIsDead; });

		// // Draw landscape
		for( int x = 0; x < ScreenWidth(); x++ )
		{
			for( int y = 0; y < ScreenHeight(); y++ )
			{
				
				// Offset screen coordinates into world coordinates
				switch( map[( y + (int)fCameraPos.y ) * nMapWidth + (x + (int)fCameraPos.x)])
				{
					case 0:
						Draw(x, y, olc::CYAN);
						break;
					case 1:
						Draw(x, y, olc::GREEN);
						break;
				}
			}
		}


		// Runthrough the list and displays the objects
		for (auto &p : list_of_objects)
		{
			p->Display(this);
		}

		// Debug information
		DrawString({0, 0}, "Game Objects: " + std::to_string(list_of_objects.size()));
		DrawString({0, 8}, "Camera: " + std::to_string((int)fCameraPos.x) + "," + std::to_string((int)fCameraPos.y));
		DrawString({0, 16}, "Mouse: " + std::to_string(GetMouseX()) + "," + std::to_string(GetMouseY()));
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
