//
// Created by prokoseb on 9.5.23.
//

#include "regular.h"
#include <deque>
#include <stack>

std::deque<position> regular::findPath(const tileMap &m, const position &pos) const {
    std::deque<position> path;
    position start = pos;
    position end = m._basePosition;

    std::vector<std::vector<bool>> visited(m._height, std::vector<bool>(m._width, false));
    std::vector<std::vector<position>> parent(m._height, std::vector<position>(m._width));
    std::stack<position> q;
    q.push(start);
    visited[start.y][start.x] = true;

    while (!q.empty()) {
        position v = q.top();
        q.pop();
        if (v == end) {
            position u = end;
            while (u != start) {
                path.push_front(u);
                u = parent[u.y][u.x];
            }
            path.push_front(start);
            return path;
        }
        for (const auto &w: m.getNeighbours(v)) {
            if (!visited[w.y][w.x]) {
                visited[w.y][w.x] = true;
                q.push(w);
                parent[w.y][w.x] = v;
            }
        }
    }
    throw std::runtime_error("The path to the base does not exist");
}

std::unique_ptr<passage> regular::clone() const {
    return std::make_unique<regular>();
}
