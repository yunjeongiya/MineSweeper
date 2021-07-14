#include "UnRevealedCell.h"
#include "RevealedCell.h"
#include "Map.h"
#include "MapView.h"
#include <sstream>
#include <queue>
#include <set>
using std::stringstream;
using std::set;
using std::queue;

bool UnRevealedCell::isDiscoverable()
{
    return true;
}

void UnRevealedCell::onDiscover(Map* map, const MapView& mapView)
{
    RevealedCell* newRevealedCell = new RevealedCell(this->pos.first, this->pos.second, this->adjacentMines);
    map->setCell(this->pos, newRevealedCell);
    mapView.updateView(newRevealedCell);
    delete this;
}

bool UnRevealedCell::isAdjacentMinesZero()
{
    return adjacentMines == 0;
}

string UnRevealedCell::showCell()
{
    stringstream ss;
    ss << "бс";
    return ss.str();
}

void UnRevealedCell::callUpdateVeiw(const MapView& mapView)
{
    mapView.updateView(this);
}

void UnRevealedCell::reveal(Map* map, const MapView& mapView)
{
    int revealedCount = 0;
    queue<Cell*> q;
    set<POS> visited;
    q.push(this);
    while (!q.empty())
    {
        Cell* currentCell = q.front();
        q.pop();
        revealedCount++;
        if (currentCell->isAdjacentMinesZero())
        {
            vector<Cell*> adjacentCells = map->getAdjacentDiscoverableCells(currentCell);
            for (auto v_it = adjacentCells.begin(); v_it != adjacentCells.end(); ++v_it)
            {
                auto s_it = visited.find((**v_it).getPosition());
                if (s_it == visited.end())
                {
                    visited.insert((**v_it).getPosition());
                    q.push(*v_it);
                }
            }
        }
        currentCell->onDiscover(map, mapView);
    }
    map->addRevealedCount(revealedCount);
}