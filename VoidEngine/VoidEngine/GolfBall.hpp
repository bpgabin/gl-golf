#include <vector>
#include <glm/glm.hpp>

class GolfBall
{
public:
								GolfBall( std::vector<glm::vec3> vertices, std::vector<glm::vec3> position );
		std::vector<glm::vec3>	getVertices() const;
		std::vector<glm::vec3>	getPosition() const;


private:

		std::vector<glm::vec3>	mVertices;
		std::vector<glm::vec3>	mPosition;
	
};