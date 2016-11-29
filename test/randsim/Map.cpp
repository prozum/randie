#include "Map.h"

#include <iostream>
#include <fstream>
#include <memory>

using namespace std;

Map::Map() {}

void Map::loadMap(string Path) {
    ifstream File(Path, ifstream::in);
    auto lastRow = make_unique<vector<Block>>();

    char c;
    while ((c = File.get()) != EOF) {
        switch (c) {
            case AIR_CHAR:
                lastRow->push_back(Block::Air);
                break;
            case WALL_CHAR:
                lastRow->push_back(Block::Wall);
                break;
            case WINDOW_CHAR:
                lastRow->push_back(Block::Window);
                break;
            case '\n':
                MapBlocks.push_back(move(lastRow));
                lastRow = make_unique<vector<Block>>();
                break;
            default:
                cout << "Wrong character in file:" << c;
                return;
        }
    }
    MapBlocks.push_back(move(lastRow));

    Width = MapBlocks.size();
    Height = MapBlocks[0]->size();
}

void Map::printMap() {
    for(auto &Row : MapBlocks) {
        for (auto &Block : *Row) {
            switch (Block) {
                case Block::Air:
                    cout << AIR_CHAR;
                    break;
                case Block::Wall:
                    cout << WALL_CHAR;
                    break;
                case Block::Window:
                    cout << WINDOW_CHAR;
                    break;
            }
        }
        cout << endl;
    }
}

void Map::draw(Renderer &R) {
    int X = 0;
    int Y = 0;
    for(auto &Row : MapBlocks) {
        for (auto &Block : *Row) {
            switch (Block) {
                case Block::Air:
                    R.setColor({255, 255, 255});
                    break;
                case Block::Wall:
                    R.setColor({0, 0, 0});
                    break;
                case Block::Window:
                    R.setColor({0, 0, 255});
                    break;
            }
            R.drawRect({X,Y}, 20, 20);
            X+=21;
        }
        Y+=21;
        X=0;
    }
}
