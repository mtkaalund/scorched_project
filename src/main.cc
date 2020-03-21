#include <vector>
#include <memory>

#include <OneLoneCoder/olcPixelGameEngine.h>

#include "cPhysicObject.h"
#include "cParticle.h"

class Scorched_project : public olc::PixelGameEngine
{
	std::vector<std::unique_ptr<cPhysicsObject>> list_of_objects;

public:
	// Constructor
	Scorched_project()
	{
		sAppName = "Scorched project";
	}

	bool OnUserCreate()
	{
		for( int i = 0; i < 2; i++ )
		{
			list_of_objects.push_back(
				std::unique_ptr<cParticle>(
					new cParticle(
					{
					(float)(rand() % ScreenWidth()),
					(float)(rand() % 100)
					}
				)
				)
			);
		}

		return true;
	}

	bool OnUserUpdate( float fElapsedTime )
	{
		// Game main loop

		Clear(olc::BLUE);

		DrawString({ScreenWidth()/2, ScreenHeight()/2}, "Hello, TF!!!", olc::GREEN);

		for( auto &p : list_of_objects )
		{
			p->Update( fElapsedTime );
			p->Display(this);
		}

		return true;
	}

	bool OnUserDestroy()
	{
		// Only use if need to destroy some thing

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
