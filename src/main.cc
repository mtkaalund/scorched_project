#include <list>
#include <memory>
#include <string>
#include <vector>

#include <OneLoneCoder/olcPixelGameEngine.h>

#include "cPhysicObject.h"
#include "cParticle.h"
#include "Generic.h"
#include "cNoise.h"

class Scorched_project : public olc::PixelGameEngine
{
private:
	std::list<std::unique_ptr<cPhysicsObject>> list_of_objects;

	int nMapWidth;
	int nMapHeight;

	std::vector<unsigned char> map;

	olc::vf2d fCameraPos = {0.0f, 0.0f};
	float fCameraSpeed = 200.0f;

	// Angle for pointing
	float fAngle = 0.0f;

	// For use with perlin noise
	float fBiasMap = 0.001f;
	// int nOctaveMap = 4;

	enum NoiseType {
		PERLINNOISE,
		SIMPLEXNOISE,
		VALUENOISE,
		ENDNOISE
	};
	int CurrentNoise = PERLINNOISE;

public:
	// Constructor
	Scorched_project()
	{
		sAppName = "Scorched project";
	}

	bool OnUserCreate()
	{
		nMapWidth = ScreenWidth() * 2;
		nMapHeight = ScreenHeight();

		map.resize(nMapWidth * nMapHeight);

		for (int i = 0; i < map.size(); i++)
		{
			map[i] = 0;
		}

		for (int i = 0; i < 1; i++)
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
		//Clear(olc::BLUE);

		// Before handling inputs, we'll need to check if window has focus
		if (IsFocused())
		{
			if (GetKey(olc::Key::M).bReleased)
			{
				GenerateMap();
			}

			if( GetKey(olc::Key::C).bReleased)
			{
				CurrentNoise++;
				if( CurrentNoise == ENDNOISE)
				{
					CurrentNoise = PERLINNOISE;
				}
			}

			if (GetKey(olc::Key::Q).bReleased)
			{
				fBiasMap += 0.001f;
			}

			if (GetKey(olc::Key::W).bReleased)
			{
				fBiasMap -= 0.001f;
				if (fBiasMap < 0.001f)
					fBiasMap = 0.001f;
			}

			if( GetKey(olc::Key::UP).bHeld )
			{
				fAngle -= 0.5f;
			}

			if( GetKey(olc::Key::DOWN).bHeld )
			{
				fAngle += 0.5f;
			}
		}

		// Handle camera position
		if (GetMouseX() < 15)
			fCameraPos.x -= fCameraSpeed * fElapsedTime;
		if (GetMouseX() > ScreenWidth() - 15)
			fCameraPos.x += fCameraSpeed * fElapsedTime;
		if (GetMouseY() < 15)
			fCameraPos.y -= fCameraSpeed * fElapsedTime;
		if (GetMouseY() > ScreenHeight() - 15)
			fCameraPos.y += fCameraSpeed * fElapsedTime;
		// Clamp camera boundaries
		if (fCameraPos.x < 0)
			fCameraPos.x = 0;
		if (fCameraPos.y < 0)
			fCameraPos.y = 0;
		if (fCameraPos.x >= nMapWidth - ScreenWidth())
			fCameraPos.x = nMapWidth - ScreenWidth();
		if (fCameraPos.y > nMapHeight - ScreenHeight())
			fCameraPos.y = nMapHeight - ScreenHeight();

		// Run through the list of object and update it
		for (auto &p : list_of_objects)
		{
			p->fAngle = fAngle;
			p->Update(fElapsedTime);
		}

		// Remove dead objects from list
		list_of_objects.remove_if([](std::unique_ptr<cPhysicsObject> &p) { return p->bIsDead; });

		// // Draw landscape
		for (int x = 0; x < ScreenWidth(); x++)
		{
			for (int y = 0; y < ScreenHeight(); y++)
			{
				// Offset screen coordinates into world coordinates
				switch (map[(y + (int)fCameraPos.y) * nMapWidth + (x + (int)fCameraPos.x)])
				{
				case 0:
					Draw(x, y, olc::CYAN);
					break;
				case 1:
					Draw(x, y, olc::VERY_DARK_GREEN);
					break;
				}
			}
		}

		// Runthrough the list and displays the objects
		for (auto &p : list_of_objects)
		{
			p->Display(this, fCameraPos);
		}

		// Debug information
		DrawString({0, 0}, "Game Objects: " + std::to_string(list_of_objects.size()));
		DrawString({0, 8}, "Camera: " + std::to_string((int)fCameraPos.x) + "," + std::to_string((int)fCameraPos.y));
		DrawString({0, 16}, "Mouse: " + std::to_string(GetMouseX()) + "," + std::to_string(GetMouseY()));
		DrawString({0, 24}, "Map Bias: " + std::to_string(fBiasMap));
		DrawString({0, 32}, "Angle: " + std::to_string(fAngle));
		std::string str_map = "Map Engine: ";
		switch(CurrentNoise)
		{
			case PERLINNOISE:
			str_map += "Perlin";
			break;
			case SIMPLEXNOISE:
			str_map += "Simplex";
			break;
			case VALUENOISE:
			str_map += "Value";
			break;

		}
	
		DrawString({0, 40}, str_map);
		return true;
	}

	bool OnUserDestroy()
	{
		// Only use if need to destroy some thing
		list_of_objects.clear();

		return true;
	}

	void GenerateMap()
	{
		float *fSurface = new float[nMapWidth];
		Noise *n = new Noise( nMapWidth );

		for( int i = 0; i < nMapWidth; i++ )
		{
			switch(CurrentNoise)
			{
				case PERLINNOISE:
					fSurface[i] = std::abs(n->Perlin1D(i, fBiasMap));
					break;
				case SIMPLEXNOISE:
					fSurface[i] = std::abs(n->Simplex1D(i, fBiasMap)) * 1.10;
					break;
				case VALUENOISE:
					fSurface[i] = std::abs(n->Value1D(i,fBiasMap));
					break;
				default:
					fSurface[i] = std::abs(n->Perlin1D(i, fBiasMap));
					break;
			}
		}
		
		ClearMap();
		
		for (int x = 0; x < nMapWidth; x++)
		{
			for (int y = 0; y < nMapHeight; y++)
			{
				if (y >= (1.0f - fSurface[x]) * nMapHeight)
				{
					map[y * nMapWidth + x] = 1;
				}
				else
				{
					map[y * nMapWidth + x] = 0;
				}
			}
		}

		delete[] fSurface;
		delete n;
	}

	// // More or less taken from https://github.com/OneLoneCoder/videos/blob/master/worms/OneLoneCoder_Worms1.cpp
	// void GenerateMapPerlin()
	// {
	// 	float *fNoiseSeed = new float[nMapWidth];
	// 	float *fSurface = new float[nMapWidth];

	// 	for (int i = 0; i < nMapWidth; i++)
	// 	{
	// 		fNoiseSeed[i] = randf(0.0f, 1.0f);
	// 	}

	// 	fNoiseSeed[0] = randf(0.3f, 0.6f); //0.5;

	// 	// fBiasMap should not be lower that 1.3
	// 	// nOctaveMap 4 and fBiasMap 1.1 is an interesting map
	// 	PerlinNoise1D(nMapWidth, fNoiseSeed, nOctaveMap, fBiasMap, fSurface);
	// 	ClearMap();

	// 	for (int x = 0; x < nMapWidth; x++)
	// 	{
	// 		for (int y = 0; y < nMapHeight; y++)
	// 		{
	// 			if (y >= fSurface[x] * nMapHeight)
	// 			{
	// 				map[y * nMapWidth + x] = 1;
	// 			}
	// 			else
	// 			{
	// 				map[y * nMapWidth + x] = 0;
	// 			}
	// 		}
	// 	}

	// 	delete[] fNoiseSeed;
	// 	delete[] fSurface;
	// }

	void ClearMap()
	{
		for(int i = 0; i < map.size(); i++ )
		{
			map[i] = 0;
		}
	}
};

int main(int argc, char *argv[])
{
	Scorched_project game;
	if (game.Construct(640, 480, 1, 1))
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
