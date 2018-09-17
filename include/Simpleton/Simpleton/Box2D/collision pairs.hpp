//
//  collision pairs.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 29/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_box2d_collision_pairs_hpp
#define engine_box2d_collision_pairs_hpp

#include <vector>
#include <utility>
#include "object types.hpp"
#include "../ECS/registry.hpp"

namespace B2 {
  using ObjectTypePair = std::pair<ObjectTypeID, ObjectTypeID>;
  using EntityPair = std::pair<ECS::EntityID, ECS::EntityID>;

  struct CollisionPair {
    ObjectTypePair type;
    EntityPair entity;
  };

  inline bool operator==(const CollisionPair left, const CollisionPair right) {
    return left.type == right.type && left.entity == right.entity;
  }

  constexpr EntityPair NULL_ENTITY_PAIR = {entt::null, entt::null};

  class CollisionPairs {
  public:
    CollisionPairs() = default;

    void addPair(CollisionPair);
    void remPair(CollisionPair);
    
    bool hasPair(ObjectTypePair) const;
    bool hasHalfPair(ObjectTypeID) const;
    bool hasAny() const;
    
    EntityPair getPair(ObjectTypePair) const;
    ECS::EntityID getHalfPair(ObjectTypeID) const;
    
    template <typename Type0, typename Type1>
    bool hasPair() const {
      return hasPair({getObjectTypeID<Type0>(), getObjectTypeID<Type1>()});
    }
    
    template <typename Type>
    bool hasHalfPair() const {
      return hasHalfPair(getObjectTypeID<Type>());
    }
    
    template <typename Type0, typename Type1>
    EntityPair getPair() const {
      return getPair({getObjectTypeID<Type0>(), getObjectTypeID<Type1>()});
    }
    
    template <typename Type>
    ECS::EntityID getHalfPair() const {
      return getHalfPair(getObjectTypeID<Type>());
    }
    
  private:
    using Pairs = std::vector<CollisionPair>;
    using Iter = Pairs::const_iterator;
    Pairs pairs;
    
    static auto searchPred(ObjectTypePair);
    static auto searchPred(ObjectTypeID);
    
    Iter find(ObjectTypePair) const;
    Iter find(ObjectTypeID) const;
    
    static ObjectTypePair sort(ObjectTypePair);
    static CollisionPair sort(CollisionPair);
  };
}

#include "collision pairs.inl"

#endif
