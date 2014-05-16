#include <vector>
#include <glm/glm.hpp>

// Represents a single tile in the mini-golf level
class Tile
{
public:
							Tile(int ID, std::vector<glm::vec3> vertices, std::vector<int> neighbors);
	int						getID() const;
	std::vector<glm::vec3>	getVertices() const;
	std::vector<int>		getNeighbors() const;
    glm::vec3               getNormal() const;
    void                    setNormal(glm::vec3 normal);

private:
	int						mID;
	std::vector<glm::vec3>	mVertices;
	std::vector<int>		mNeighbors;
    glm::vec3               mNormal;
};