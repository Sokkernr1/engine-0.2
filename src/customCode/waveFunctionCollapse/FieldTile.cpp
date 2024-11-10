#include "FieldTile.h"

#include "../../classes/engine/rendering/RenderManager.h"
#include "../../classes/nodeComponents/GeometryComponent.h"
#include "../../resources/shader/ColorShader.h"

const glm::vec2 FieldTile::TILE_SIZE = glm::vec2(2.f);

FieldTile::FieldTile() : m_tilePlaced(false), m_tilePos(glm::ivec2()) { m_possibleTiles = GetAllTiles(); }

void FieldTile::updateNeighbors(const std::vector<std::vector<std::shared_ptr<FieldTile>>>& field)
{
    for(glm::ivec2 offset : GetNeighborOffsets())
    {
        offset += m_tilePos;

        if(offset.x < 0 || offset.x >= FIELD_SIZE.x || offset.y < 0 || offset.y >= FIELD_SIZE.y)
        {
            continue; // Out of bounds
        }

        field[offset.x][offset.y]->updatePossibleTiles(field);
    }
}

void FieldTile::updatePossibleTiles(const std::vector<std::vector<std::shared_ptr<FieldTile>>>& field)
{
    if(m_possibleTiles.size() == 1)
    {
        return;
    }

    std::vector<TileTypeEnum> possibleTiles = m_possibleTiles;
    for(glm::ivec2 offset : GetNeighborOffsets())
    {
        offset += m_tilePos;

        if(offset.x < 0 || offset.x >= FIELD_SIZE.x || offset.y < 0 || offset.y >= FIELD_SIZE.y)
        {
            continue; // Out of bounds
        }

        const std::vector<TileTypeEnum>& possibleTilesOfNeighborField =
                field[offset.x][offset.y]->getAllPossibleTiles();

        std::vector<TileTypeEnum> tilesToRemove;
        for(const TileTypeEnum possibleTileType : possibleTiles)
        {
            bool found = false;
            for(const TileTypeEnum possibleNeighborTileType : possibleTilesOfNeighborField)
            {
                BasicTileDataStruct possibleNeighborTileData = EnumToTileData(possibleNeighborTileType);

                auto it = std::find(
                        possibleNeighborTileData.allowedNeighbors.begin(),
                        possibleNeighborTileData.allowedNeighbors.end(),
                        possibleTileType
                );
                if(it != possibleNeighborTileData.allowedNeighbors.end())
                {
                    found = true;
                    break;
                }
            }

            if(!found)
            {
                tilesToRemove.push_back(possibleTileType);
            }

            if(possibleTiles.size() - tilesToRemove.size() == 1)
            {
                break;
            }
        }

        possibleTiles
                .erase(std::remove_if(
                               possibleTiles.begin(),
                               possibleTiles.end(),
                               [&](TileTypeEnum tileToCheck) {
                                   return std::find(tilesToRemove.begin(), tilesToRemove.end(), tileToCheck) !=
                                           tilesToRemove.end();
                               }
                       ),
                       possibleTiles.end());

        if(possibleTiles.size() == 1)
        {
            break;
        }
    }

    if(m_possibleTiles.size() != possibleTiles.size())
    {
        m_possibleTiles = possibleTiles;
        updateNeighbors(field);
    }
}

std::shared_ptr<Engine::GeometryComponent> FieldTile::setTile(
        TileTypeEnum type,
        const std::shared_ptr<Engine::RenderManager>& renderManager,
        const std::vector<std::vector<std::shared_ptr<FieldTile>>>& field
)
{
    static const float startPosX = (TILE_SIZE.x * ((float)FIELD_SIZE.x - 1.f)) / 2.f;
    static const float startPosY = (TILE_SIZE.y * ((float)FIELD_SIZE.y - 1.f)) / 2.f;

    const float posX = (m_tilePos.x * TILE_SIZE.x) - startPosX;
    const float posY = (m_tilePos.y * TILE_SIZE.y) - startPosY;

    std::shared_ptr<Engine::GeometryComponent> planeObj = std::make_shared<Engine::GeometryComponent>();
    planeObj->setObjectData(renderManager->registerObject("resources/objects/plane.obj"));
    planeObj->setShader(std::make_shared<ColorShader>(renderManager));
    planeObj->setRotation(glm::vec3(-90.f, 0.f, 0.f));
    planeObj->setPosition(glm::vec3(posX, 0.f, posY));

    std::vector<glm::vec4> g_color_buffer_data;
    for(int v = 0; v < planeObj->getObjectData()->getVertexCount(); v++)
    {
        g_color_buffer_data.emplace_back(EnumToColorValue(type), 1.f);
    }

    planeObj->setTextureBuffer(renderManager->createBuffer(g_color_buffer_data));

    m_possibleTiles.clear();
    m_possibleTiles.push_back(type);
    m_tilePlaced = true;

    updateNeighbors(field);

    return planeObj;
}
