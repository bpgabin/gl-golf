#include "FileHandler.h"

Level FileHandler::ReadFile(string filename)
{
	string line;
	stringstream ss;
	string object, tile, edges, points, neibors, nums;
	int temp;
	float temp2;
	int tileID;
	float vert[3];
	list<float> vertices;
	list<int> neighbors;
	list<Tile> tiles;
	Level::LevelObject tee;
	Level::LevelObject cup;
	ifstream myfile(filename);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{

			ss.clear();
			ss.str(line);


			// separation of data into separate strings
			ss >> object;
			if (object == "tee")
			{
				ss >> tile;
				istringstream(tile) >> tileID;
				for (int i = 0; i < 3; i++)
				{
					ss >> nums;
					points.append(nums);
					istringstream(nums) >> temp2;
					vert[i] = temp2;
					
				}
				
				tee.position[0] = vert[0];
				tee.position[1] = vert[1];
				tee.position[2] = vert[2];
				tee.tileID = tileID;

				
			}
			else if (object == "cup")
			{
				ss >> tile;
				istringstream(tile) >> tileID;
				for (int i = 0; i < 3; i++)
				{
					ss >> nums;
					points.append(nums);
					istringstream(nums) >> temp2;
					vert[i] = temp2;
				}
				
				cup.position[0] = vert[0];
				cup.position[1] = vert[1];
				cup.position[2] = vert[2];
				cup.tileID = tileID;
			}
			else
			{
				ss >> tile;
				istringstream(tile) >> tileID;
				ss >> edges;
				// caculates how many points current tile has for reading correct number of points from data file
				int numEdges;
				istringstream(edges) >> numEdges;
				for (int i = 0; i < numEdges; i++)
				{
					for (int i = 0; i < 3; i++)
					{
						ss >> nums;
						points.append(nums);
						istringstream(nums) >> temp2;
						vert[i] = temp2;
					}
					vertices.push_back(vert);
				}
				// same as above but this time for edges
				for (int i = 0; i < numEdges; i++)
				{
					ss >> nums;
					neibors.append(nums);
					istringstream(nums) >> temp;
					neighbors.push_back(temp);
				}
				// output of strings for testing
				//cout << "object: " << object << endl;
				//cout << "tileID:" << tile << endl;
				//cout << "edges:" << edges << endl;
				//cout << "points:" << points << endl;
				//cout << "neighbors:" << neibors << endl;
				//points.clear();
				//neibors.clear();

				Tile *newtile = new Tile(tileID, vertices, neighbors);
				tiles.push_back(*newtile);
			}
			return Level(tiles,tee,cup);

				
		}
		myfile.close();
	}
	else cout << "Unable to open file";
}



