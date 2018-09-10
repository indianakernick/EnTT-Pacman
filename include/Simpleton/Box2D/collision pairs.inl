//
//  collision pairs.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 29/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

inline void B2::CollisionPairs::addPair(const CollisionPair pair) {
  pairs.push_back(sort(pair));
}

inline void B2::CollisionPairs::remPair(const CollisionPair pair) {
  const auto iter = std::find(pairs.cbegin(), pairs.cend(), sort(pair));
  if (iter != pairs.cend()) {
    pairs.erase(iter);
  }
}

inline bool B2::CollisionPairs::hasPair(const ObjectTypePair type) const {
  return find(type) != pairs.cend();
}

inline bool B2::CollisionPairs::hasHalfPair(const ObjectTypeID type) const {
  return find(type) != pairs.cend();
}

inline bool B2::CollisionPairs::hasAny() const {
  return !pairs.empty();
}

inline B2::EntityPair B2::CollisionPairs::getPair(const ObjectTypePair type) const {
  const auto iter = find(type);
  if (iter == pairs.cend()) {
    return NULL_ENTITY_PAIR;
  } else {
    return iter->entity;
  }
}

inline ECS::EntityID B2::CollisionPairs::getHalfPair(const ObjectTypeID type) const {
  const auto iter = find(type);
  if (iter == pairs.cend()) {
    return entt::null;
  } else {
    if (iter->type.first == type) {
      return iter->entity.first;
    } else {
      return iter->entity.second;
    }
  }
}

inline auto B2::CollisionPairs::searchPred(const ObjectTypePair type) {
  return [type = sort(type)] (const CollisionPair pair) {
    return pair.type == type;
  };
}

inline auto B2::CollisionPairs::searchPred(const ObjectTypeID type) {
  return [type] (const CollisionPair pair) {
    return pair.type.first == type || pair.type.second == type;
  };
}

inline B2::CollisionPairs::Iter B2::CollisionPairs::find(const ObjectTypePair type) const {
  return std::find_if(pairs.cbegin(), pairs.cend(), searchPred(type));
}

inline B2::CollisionPairs::Iter B2::CollisionPairs::find(const ObjectTypeID type) const {
  return std::find_if(pairs.cbegin(), pairs.cend(), searchPred(type));
}

inline B2::ObjectTypePair B2::CollisionPairs::sort(const ObjectTypePair pair) {
  if (pair.first < pair.second) {
    return pair;
  } else {
    return {pair.second, pair.first};
  }
}

inline B2::CollisionPair B2::CollisionPairs::sort(const CollisionPair pair) {
  if (pair.type.first < pair.type.second) {
    return pair;
  } else {
    return {
      {pair.type.second, pair.type.first},
      {pair.entity.second, pair.entity.first}
    };
  }
}
