//
//  contact listener.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 29/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include <utility>
#include "entity id.hpp"
#include <Box2D/Dynamics/Contacts/b2Contact.h>

namespace B2::detail {
  inline ObjectTypePair getTypePair(b2Contact *const contact) {
    return {
      getObjectTypeID(contact->GetFixtureA()->GetUserData()),
      getObjectTypeID(contact->GetFixtureB()->GetUserData())
    };
  }

  inline EntityPair getEntityPair(b2Contact *const contact) {
    return {
      getEntity(contact->GetFixtureA()->GetBody()->GetUserData()),
      getEntity(contact->GetFixtureB()->GetBody()->GetUserData())
    };
  }

  inline CollisionPair getCollisionPair(b2Contact *const contact) {
    return {getTypePair(contact), getEntityPair(contact)};
  }
}

inline void B2::ContactListener::BeginContact(b2Contact *const contact) {
  if (beginListener) {
    beginListener(detail::getCollisionPair(contact));
  }
}

inline void B2::ContactListener::EndContact(b2Contact *const contact) {
  if (endListener) {
    endListener(detail::getCollisionPair(contact));
  }
}

inline void B2::ContactListener::setBeginListener(const Listener &newListener) {
  beginListener = newListener;
}

inline void B2::ContactListener::setEndListener(const Listener &newListener) {
  endListener = newListener;
}
