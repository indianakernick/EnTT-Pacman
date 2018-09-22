//
//  a star.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 13/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "dir.hpp"
#include "distance.hpp"

template <typename Tile, Grid::Coord Width, Grid::Coord Height, typename Function>
std::vector<Grid::Pos> Grid::astar(
  const Grid<Tile, Width, Height> &grid,
  Function &&notPath,
  const Pos start,
  const Pos end
) {
  if (grid.outOfRange(start) || grid.outOfRange(end)) {
    return {};
  }
  
  // this algorithm searchs from the end and finds the start
  // this is to avoid std::reversing the final path vector

  struct Node {
    Pos pos;
    Pos prevPos;        // position of previous node
    Coord pathCost;     // number of tiles from end
    float combinedCost; // pathCost + distance to start
  };
  
  // sort the priority queue by the combined cost
  // small costs at the top
  const auto comp = [] (const Node &a, const Node &b) {
    return a.combinedCost > b.combinedCost;
  };
  std::vector<Node> queue;
  std::vector<Node> popped;
  
  queue.push_back({end, end, 0, euclid(start, end)});
  
  do {
    if (queue.empty()) {
      // there is no path
      return {};
    } else if (queue.front().pos == start) {
      // the shortest path has been found
      std::vector<Pos> path;
      path.push_back(start);
      const Node *topNode = &queue.front();
      
      for (auto n = popped.rbegin(); n != popped.rend(); ++n) {
        const Node &node = *n;
        if (node.pos == topNode->prevPos) {
          path.push_back(node.pos);
          topNode = &node;
        }
      }
      
      return path;
    }
    
    // grab the top node
    const Node topNode = queue.front();
    std::pop_heap(queue.begin(), queue.end(), comp);
    queue.pop_back();
    popped.push_back(topNode);
    const Coord neighPathCost = topNode.pathCost + 1;
    
    // look at all of the tiles around the top node
    for (const Dir dir : dir_range) {
      const Pos neighPos = topNode.pos + toVec<Coord>(dir);
      if (neighPos == topNode.prevPos || grid.outOfRange(neighPos) || notPath(grid[neighPos])) {
        continue;
      }
      const Node neighNode {
        neighPos,
        topNode.pos,
        neighPathCost,
        neighPathCost + euclid(neighPos, start)
      };
      
      // check if the current neighbor is already in the queue
      bool assigned = false;
      for (auto n = queue.cbegin(); n != queue.cend(); ++n) {
        const Node &node = *n;
        if (node.pos == neighPos) {
          assigned = true;
          // if we've found a shorter path to the same node,
          // replace the existing node with a new one
          if (neighNode.pathCost < node.pathCost) {
            queue.erase(n);
            queue.push_back(node);
            std::push_heap(queue.begin(), queue.end(), comp);
          }
          break;
        }
      }
      if (!assigned) {
        // push if the node hasn't replaced an existing node
        queue.push_back(neighNode);
        std::push_heap(queue.begin(), queue.end(), comp);
      }
    }
  } while (true);
}
