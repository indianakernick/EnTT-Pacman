//
//  meta glm.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 19/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_meta_glm_hpp
#define engine_utils_meta_glm_hpp

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/type_trait.hpp>
#undef GLM_ENABLE_EXPERIMENTAL

namespace Utils {
  template <typename Vec>
  constexpr bool is_vec = glm::type<Vec>::is_vec;
  
  template <typename Vec>
  constexpr size_t vec_size = glm::type<Vec>::components;
  
  template <typename Vec>
  using vec_value_type = typename Vec::value_type;
  
  template <typename Mat>
  constexpr bool is_mat = glm::type<Mat>::is_mat;
  
  template <typename Mat>
  constexpr size_t mat_rows = glm::type<Mat>::rows;
  
  template <typename Mat>
  constexpr size_t mat_cols = glm::type<Mat>::cols;
  
  template <typename Mat>
  constexpr size_t mat_cells = mat_rows<Mat> * mat_cols<Mat>;
  
  template <typename Mat>
  using mat_value_type = typename Mat::value_type;
}

#endif
