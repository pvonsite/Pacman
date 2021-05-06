#include "Map.h"
#include <queue>

typedef std::pair<int, int> II;

bool firstInit = true;
int premanMap[31][28];
int color[31][28];

Map::Map() {
    if (firstInit) {
        std::ifstream file(mapFile);
        if (file) {
            for (int i = 0; i < MAP_HEIGHT; ++i) {
                for (int j = 0; j < MAP_WIDTH; ++j) {
                    file >> premanMap[i][j];
                    if (premanMap[i][j] > 31 || premanMap[i][j] < 0) {
                        Console->Status("Wrong Tile!");
                        return;
                    }
                }
            }

            Console->Status("Map read successfully!");
        }
        else Console->Status("Error reading file!");
    }

    for (int i = 0; i < MAP_HEIGHT; ++i)
        for (int j = 0; j < MAP_WIDTH; ++j)
            tile[i][j] = premanMap[i][j];

    findingCrossRoad();
    NextCrossTileID();
    calculateDistance();
}

int Map::getTileID(int x, int y) {
    return tile[y][x];
}

std::pair<int, int> Map::getnextCrossID(int x, int y, int dir) {
    return nextCrossID[y][x][dir];
}

bool Map::isWall(std::pair<int, int> tileID) {
    if (tileID == II(0, 14) || tileID == II(27, 14)) return false;
    if (tileID.first < 1 || tileID.first > 26) return true;
    if (tileID.second < 1 || tileID.second > 29) return true;
    return tile[tileID.second][tileID.first] != 26 && tile[tileID.second][tileID.first] != 30 && tile[tileID.second][tileID.first] != 27;
}

bool Map::iscrossRoad(int x, int y) {
    int cnt = 0;
    if (markCross[y][x][UP]) ++cnt;
    if (markCross[y][x][RIGHT]) ++cnt;
    if (markCross[y][x][DOWN]) ++cnt;
    if (markCross[y][x][LEFT]) ++cnt;
    if (cnt >= 3) return true;
    if (cnt == 2) {
        if (markCross[y][x][UP] && markCross[y][x][DOWN]) return false;
        if (markCross[y][x][LEFT] && markCross[y][x][RIGHT]) return false;
        return true;
    }
    return false;
}

bool Map::canChangeDir(int x, int y, int newDir) {
    return markCross[y][x][newDir];
}

bool Map::besideCrossIsWall(std::pair<int, int> Cross, int newDir) {
    if (newDir == UP) Cross.second -= 1;
    else if (newDir == DOWN) Cross.second += 1;
    else if (newDir == RIGHT) Cross.first += 1;
    else Cross.first -= 1;
    return isWall(Cross);
}

void Map::findingCrossRoad() {
    for (int x = 0; x < MAP_WIDTH; ++x) {
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            for (int dir = 0; dir < 4; ++dir) markCross[y][x][dir] = false;

            if (tile[y][x] != 26 && tile[y][x] != 27 && tile[y][x] != 30) continue;

            if (y > 0  && (tile[y - 1][x] == 26 || tile[y - 1][x] == 27 || tile[y - 1][x] == 30)) markCross[y][x][0] = true;
            if (y < 30 && (tile[y + 1][x] == 26 || tile[y + 1][x] == 27 || tile[y + 1][x] == 30)) markCross[y][x][2] = true;
            if (x > 0  && (tile[y][x - 1] == 26 || tile[y][x - 1] == 27 || tile[y][x - 1] == 30)) markCross[y][x][3] = true;
            if (x < 27 && (tile[y][x + 1] == 26 || tile[y][x + 1] == 27 || tile[y][x + 1] == 30)) markCross[y][x][1] = true;
        }
    }
}

void Map::NextCrossTileID() {
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        nextCrossID[y][0][LEFT] = II(-1, -1);
        for (int x = 1; x < MAP_WIDTH; ++x) {
            nextCrossID[y][x][LEFT] = II(-1, -1);

            if ( !isWall(std::pair<int, int> (x, y)) ) {
                if (nextCrossID[y][x - 1][LEFT] != II(-1, -1)) nextCrossID[y][x][LEFT] = nextCrossID[y][x - 1][LEFT];
                if (iscrossRoad(x - 1, y)) nextCrossID[y][x][LEFT] = II(x - 1, y);
            }
        }

        nextCrossID[y][MAP_WIDTH - 1][RIGHT] = II(-1, -1);
        for (int x = MAP_WIDTH - 2; x >= 0; --x) {
            nextCrossID[y][x][RIGHT] = II(-1, -1);

            if ( !isWall(std::pair<int, int> (x, y)) ) {
                if (nextCrossID[y][x + 1][RIGHT] != II(-1, -1)) nextCrossID[y][x][RIGHT] = nextCrossID[y][x + 1][RIGHT];
                if (iscrossRoad(x + 1, y)) nextCrossID[y][x][RIGHT] = II(x + 1, y);
            }
        }
    }

    for (int x = 0; x < MAP_WIDTH; ++x) {
        nextCrossID[0][x][UP] = II(-1, -1);
        for (int y = 1; y < MAP_HEIGHT; ++y) {
            nextCrossID[y][x][UP] = II(-1, -1);

            if ( !isWall(std::pair<int, int> (x, y)) ) {
                if (nextCrossID[y - 1][x][UP] != II(-1, -1)) nextCrossID[y][x][UP] = nextCrossID[y - 1][x][UP];
                if (iscrossRoad(x, y - 1)) nextCrossID[y][x][UP] = II(x, y - 1);
            }
        }

        nextCrossID[MAP_HEIGHT - 1][x][DOWN] = II(-1, -1);
        for (int y = MAP_HEIGHT - 2; y >= 0; --y) {
            nextCrossID[y][x][DOWN] = II(-1, -1);

            if ( !isWall(std::pair<int, int> (x, y)) ) {
                if (nextCrossID[y + 1][x][DOWN] != II(-1, -1)) nextCrossID[y][x][DOWN] = nextCrossID[y + 1][x][DOWN];
                if (iscrossRoad(x, y + 1)) nextCrossID[y][x][DOWN] = II(x, y + 1);
            }
        }
    }
}

void Map::calculateDistance() {
    for (int x = 0; x < MAP_WIDTH; ++x)
        for (int y = 0; y < MAP_HEIGHT; ++y)
            for (int u = 0; u < MAP_WIDTH; ++u)
                for (int v = 0; v < MAP_HEIGHT; ++v)
                    for (int dir = 0; dir < 4; ++dir)
                        dist[x * MAP_HEIGHT + y][u * MAP_HEIGHT + v][dir] = -1;
    //std::cout << 1;
    int id = 0;
    int dh[4] = { 0, 1, 0, -1};
    int dc[4] = {-1, 0, 1,  0};
    int dis[MAP_WIDTH * MAP_HEIGHT];
    std::queue< std::pair<int, int> > visitNode;
    for (int x = 0; x < MAP_WIDTH; ++x) {
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            if (isWall(std::pair<int, int> (x, y))) continue;
            if (y == 14 && (x == 0 || x == 27)) continue;

            for (int startDir = 0; startDir < 4; ++ startDir) {
                int xn = x + dh[startDir], yn = y + dc[startDir];
                if (isWall(std::pair<int, int> (xn, yn))) continue;
                for (int i = 0; i < MAP_HEIGHT * MAP_WIDTH; ++i) dis[i] = -1;
                ++id;
                color[yn][xn] = id;
                dis[xn * MAP_HEIGHT + yn] = 0;
                visitNode.push(std::pair<int, int> (yn * MAP_WIDTH + xn, startDir));
                while (!visitNode.empty()) {
                    int curx = visitNode.front().first % MAP_WIDTH,
                        cury = visitNode.front().first / MAP_WIDTH,
                        lasDir = visitNode.front().second;
                    visitNode.pop();
                    if (cury == 14 && (curx == 0 || curx == 27)) continue;
                    for (int dir = 0; dir < 4; ++dir) {
                        int u = curx + dh[dir], v = cury + dc[dir];
                        if (lasDir % 2 == dir % 2 && dir != lasDir) continue;
                        if (isWall(std::pair<int, int> (u, v))) continue;
                        if (color[v][u] != id) {
                            color[v][u] = id;
                            dis[u * MAP_HEIGHT + v] = dis[curx * MAP_HEIGHT + cury] + 1;
                            visitNode.push(std::pair<int, int> (v * MAP_WIDTH + u, dir));
                        }
                    }
                }
                for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; ++i)
                    dist[xn * MAP_HEIGHT + yn][i][startDir] = dis[i];
            }
        }
    }
    std::cout << "Done!";
}

int Map::eatCoins(const int &pacmanTileX, const int &pacmanTileY) {
    if (tile[pacmanTileY][pacmanTileX] == 26) {
        tile[pacmanTileY][pacmanTileX] = 30;
        return 26;
    }
    if (tile[pacmanTileY][pacmanTileX] == 27) {
        tile[pacmanTileY][pacmanTileX] = 30;
        return 27;
    }
    return 0;
}

int Map::getDist(std::pair<int, int> start, std::pair<int, int> end, int startDir) {
    if (isWall(end)) return (start.first - end.first) * (start.first - end.first) + (start.second - end.second) * (start.second - end.second);
    else {
        if (dist[start.first * MAP_HEIGHT + start.second][end.first * MAP_HEIGHT + end.second][startDir] == -1)
            return (start.first - end.first) * (start.first - end.first) + (start.second - end.second) * (start.second - end.second);
        else return dist[start.first * MAP_HEIGHT + start.second][end.first * MAP_HEIGHT + end.second][startDir];
    }
}

void Map::reset() {
    for (int i = 0; i < MAP_HEIGHT; ++i)
        for (int j = 0; j < MAP_WIDTH; ++j)
            tile[i][j] = premanMap[i][j];
}
