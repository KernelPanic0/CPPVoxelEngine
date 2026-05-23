#include "Tree.hpp"

Tree::Tree(glm::vec3 position)
{
    // main branch
    for (int y = 0; y < 4; y++)
    {
        objects.emplace_back(glm::vec3(position.x, position.y + y, position.z), "./assets/wood.png");
    }

    // leaves
    for (int x = -2; x < 3; x++)
    {
        for (int z = -2; z < 3; z++)
        {
            for (int y = 2; y < 5; y++)
            {
                if (x == 0 && z == 0 && y != 4)
                    continue;

                // remove corners. Probably some better way to do this
                if ((y == 3 || y == 4) && (x == -2 && z == -2 || x == 2 && z == 2 || x == 2 && z == -2 || x == -2 && z == 2))
                    continue;

                // sorry
                if (y == 4 && (x == -1 && z == -2 || x == 1 && z == -2 || x == 2 && z == -1 || x == 2 && z == 1 || x == 1 && z == 2 || x == -1 && z == 2 || x == -2 && z == 1 || x == -2 && z == -1))
                    continue;

                objects.emplace_back(glm::vec3(position.x + x, position.y + y, position.z + z), "./assets/leaves.png");
            }
        }
    }
}