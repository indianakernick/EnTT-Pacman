//
//  contact listener.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 29/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_box2d_contact_listener_hpp
#define engine_box2d_contact_listener_hpp

#include <functional>
#include "object types.hpp"
#include "../ECS/registry.hpp"
#include "collision pairs.hpp"
#include <Box2D/Dynamics/b2WorldCallbacks.h>

namespace B2 {
  class ContactListener final : public b2ContactListener {
  public:
    using Listener = std::function<void (B2::CollisionPair)>;

    ContactListener() = default;
    
    void BeginContact(b2Contact *) override;
    void EndContact(b2Contact *) override;
    
    void setBeginListener(const Listener &);
    void setEndListener(const Listener &);
    
  private:
    Listener beginListener;
    Listener endListener;
  };
}

#include "contact listener.inl"

#endif
