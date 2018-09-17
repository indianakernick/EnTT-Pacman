//
//  pack.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 2/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_type_list_pack_hpp
#define engine_type_list_pack_hpp

#include <tuple>
#include "type.hpp"

namespace List {
  namespace detail {
    template <typename List, template <typename...> typename TemplateType>
    struct UnpackIntoI;
    
    template <template <typename...> typename TemplateType, typename... Types>
    struct UnpackIntoI<Type<Types...>, TemplateType> {
      using type = TemplateType<Types...>;
    };
    
    template <typename TemplateType>
    struct PackFromI;
    
    template <template <typename...> typename TemplateType, typename... Types>
    struct PackFromI<TemplateType<Types...>> {
      using type = Type<Types...>;
    };
  }
  
  /// Take the types from a type list and put them into another template
  template <typename List, template <typename...> typename TemplateType>
  using UnpackInto = typename detail::UnpackIntoI<List, TemplateType>::type;
  
  /// Take the types from a template and put them into a type list
  template <typename TemplateType>
  using PackFrom = typename detail::PackFromI<TemplateType>::type;
  
  /// Unpack a type list into a tuple
  template <typename List>
  using ToTuple = UnpackInto<List, std::tuple>;
  
  /// Pack a type list from a tuple
  template <typename Tuple>
  using FromTuple = PackFrom<Tuple>;
  
  static_assert(Same<ToTuple<Type<int, char, long>>, std::tuple<int, char, long>>);
  static_assert(Same<FromTuple<std::tuple<int, char, long>>, Type<int, char, long>>);
}

#endif
