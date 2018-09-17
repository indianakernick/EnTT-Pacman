//
//  profiler.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 12/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include <vector>

inline Utils::Profiler::TreeNode *Utils::Profiler::current = &tree;
inline Utils::Profiler::TreeNode Utils::Profiler::tree;
inline char Utils::Profiler::spaces[Utils::Profiler::MAX_DEPTH * Utils::Profiler::NAME_INDENT];
inline bool Utils::Profiler::initSpaces = false;
inline bool Utils::Profiler::oddLine = false;

inline Utils::Profiler::Profiler(const char *name) {
  TreeNode *prevCurrent = current;
  current = &current->children[name];
  current->parent = prevCurrent;
  current->name = name;
  start = std::chrono::high_resolution_clock::now();
}

inline Utils::Profiler::~Profiler() {
  current->time += (std::chrono::high_resolution_clock::now() - start).count();
  ++current->calls;
  current = current->parent;
}

inline void Utils::Profiler::formatInfo(std::FILE *stream) {
  std::fprintf(stream, "%-*s", NAME_WIDTH, "Name");
  std::fprintf(stream, "%-*s", REST_WIDTH, "Total Count");
  std::fprintf(stream, "%-*s", REST_WIDTH, "Avg Count per parent");
  std::fprintf(stream, "%-*s", REST_WIDTH, "Total Time (ms)");
  std::fprintf(stream, "%-*s", REST_WIDTH, "Average Time (ms)");
  std::fprintf(stream, "%-*s", REST_WIDTH, "Percent of parent time");
  std::fprintf(stream, "\n");

  tree.name = "ROOT";
  recFormatInfo(stream, &tree, 0);
  /*
  The Xcode console doesn't support ANSI escape codes
  if (stream == stdout || stream == stderr) {
    Term::defaultBackColor();
  }*/
}

inline void Utils::Profiler::resetInfo() {
  current = &tree;
  tree.calls = 0;
  tree.time = 0;
  tree.children.clear();
  tree.parent = nullptr;
}

inline void Utils::Profiler::recFormatInfo(std::FILE *stream, TreeNode *node, int depth) {
  int newDepth;
  if (node->parent) {
    newDepth = depth + 1;
    
    if (!initSpaces) {
      std::memset(spaces, ' ', sizeof(spaces));
      initSpaces = true;
    }
    /*
    The Xcode console doesn't support ANSI escape codes
    if (stream == stdout || stream == stderr) {
      if (oddLine) {
        Term::backColor(Term::Color::BLUE);
        oddLine = false;
      } else {
        //Term::defaultBackColor();
        oddLine = true;
      }
    }*/
    
    std::fprintf(stream, "%.*s", depth * NAME_INDENT, spaces);
    std::fprintf(stream, "%-*s", NAME_WIDTH - depth * NAME_INDENT, node->name);
    
    std::fprintf(stream, "%-*llu", REST_WIDTH, node->calls);
    
    //not child of root
    if (node->parent->parent) {
      const float avgParentCalls = static_cast<float>(node->calls) / node->parent->calls;
      std::fprintf(stream, "%-*.*g", REST_WIDTH, NUM_PREC, avgParentCalls);
    } else {
      std::fprintf(stream, "%-*llu", REST_WIDTH, node->calls);
    }

    const float totalTime = node->time * 1e-6f;
    std::fprintf(stream, "%-*.*g", REST_WIDTH, NUM_PREC, totalTime);

    if (node->calls) {
      std::fprintf(stream, "%-*.*g", REST_WIDTH, NUM_PREC, totalTime / node->calls);
    } else {
      std::fprintf(stream, "%-*i", REST_WIDTH, 0);
    }
    
    //not child of root
    if (node->parent->parent) {
      const float percent = (static_cast<float>(node->time) / node->parent->time);
      std::fprintf(stream, "%.*g%%", NUM_PREC, percent * 100.0f);
    }
    
    /*
    The Xcode console doesn't support ANSI escape codes
    if (stream == stdout || stream == stderr) {
      Term::defaultBackColor();
    }*/
    
    std::fprintf(stream, "\n");
  } else {
    newDepth = 0;
  }
  
  //copy children into a vector
  std::vector<TreeNode *> children;
  children.reserve(node->children.size());
  for (auto i = node->children.begin(); i != node->children.end(); ++i) {
    children.push_back(&(i->second));
  }
  
  //sort by total time in accending order
  std::sort(children.begin(), children.end(), [](TreeNode *a, TreeNode *b) {
    return a->time > b->time;
  });
  
  for (auto i = children.begin(); i != children.end(); ++i) {
    recFormatInfo(stream, *i, newDepth);
  }
}
