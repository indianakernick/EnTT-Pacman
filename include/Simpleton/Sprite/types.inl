//
//  types.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 24/2/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

inline Sprite::AtlasReadError::AtlasReadError(const std::exception &exception)
  : std::runtime_error(exception.what()) {}
