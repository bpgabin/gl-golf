#include "FileHandling.hpp"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>
using namespace std;

// Reads in a mini-golf level and returns a level class containing the information
Level FileHandling::ReadFile(string filename)
{
	// File reading variables
	string line;
 	stringstream ss;

	// Loaded object storage
	vector<Tile> tiles;
	Level::LevelObject tee;
	Level::LevelObject cup;

	// Open File Stream
	ifstream myfile(filename, ifstream::in);
    // TODO: Change this assert to a check and return type of function to pointer or reference.
    assert(myfile.is_open());
	// Read each line of the file.
	while (getline(myfile, line))
	{
		// Clear string stream
		ss.clear();
		// Load line into string stream
		ss.str(line);

		// Separation of data into separate strings
		string object;
		ss >> object;
		if (object == "tee")
		{
			// Read tileID
			string tileString;
			ss >> tileString;
			istringstream(tileString) >> tee.tileID;

			// Read Position
			float vert[3];
			for (int i = 0; i < 3; i++)
			{
				string num;
				ss >> num;
				istringstream(num) >> vert[i];
			}

			// Create position and store it
			glm::vec3 position(vert[0], vert[1], vert[2]);
			tee.position = position;
		}
		else if (object == "cup")
		{
			// Read tileID
			string tileString;
			ss >> tileString;
			istringstream(tileString) >> cup.tileID;
			
			// Read position
			float vert[3];
			for (int i = 0; i < 3; i++)
			{
				string num;
				ss >> num;
				istringstream(num) >> vert[i];
			}

			// Create position and store it
			glm::vec3 position(vert[0], vert[1], vert[2]);
			cup.position = position;
		}
		else
		{
			// Read tileID
			string tileString;
			ss >> tileString;
			int tileID;
			istringstream(tileString) >> tileID;
			
			// Read number of vertices
			string verts;
			ss >> verts;
			int numVerts;
			istringstream(verts) >> numVerts;

			// Read vertices
			vector<glm::vec3> vertices;
			for (int i = 0; i < numVerts; i++)
			{
				// Temp storage for vertices
				float vert[3];
				
				// Read in the vertex data
				for (int i = 0; i < 3; i++)
				{
					string nums;
					ss >> nums;
					istringstream(nums) >> vert[i];
				}

				// Create vertex and add it to list
				glm::vec3 vertex(vert[0], vert[1], vert[2]);
				vertices.push_back(vertex);
			}

			// Read neighbors
			vector<int> neighbors;
			for (int i = 0; i < numVerts; i++)
			{
				string nums;
				ss >> nums;
				int neighbor;
				istringstream(nums) >> neighbor;
				neighbors.push_back(neighbor);
			}

			Tile tile(tileID, vertices, neighbors);
			tiles.push_back(tile);
		}		
	}

	// Close File
	myfile.close();

	// Create and return level
	Level level(tiles, tee, cup);
	return level;
}



