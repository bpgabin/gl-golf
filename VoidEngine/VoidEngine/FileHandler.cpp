#include "FileHandler.h"

void FileHandler() {
	string line;
	stringstream ss;
	string object, tile, edges, points, neibors, nums;
	int temp;
	int tileID;
	float vert[3];
	list<float> vertices;
	list<int> neighbors;
	ifstream myfile("hole.00.db");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{

			ss.clear();
			ss.str(line);

			// separation of data into separate strings
			ss >> object;
			ss >> tile;
			istringstream(tile) >> tileID;
			ss >> edges;
			// caculates how many points current tile has for reading correct number of points from data file
			int numEdges;
			istringstream(edges) >> numEdges;
			//int numPoints = numEdges * 3;
			//adds point to list of floats
			for (int i = 0; i < numEdges; i++)
			{
				
				//vertices.push_back(temp);
				for (int i = 0; i < 3; i++)
				{
					ss >> nums;
					points.append(nums);
					istringstream(nums) >> temp;
					
					vert[i] = temp;

				}
					vertices.push_back(vert[3]);

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
			cout << "object: " << object << endl;
			cout << "tileID:" << tile << endl;
			cout << "edges:" << edges << endl;
			cout << "points:" << points << endl;
			cout << "neighbors:" << neibors << endl;
			points.clear();
			neibors.clear();



		}

		myfile.close();
	}

	else cout << "Unable to open file";

	//return 0;
}

