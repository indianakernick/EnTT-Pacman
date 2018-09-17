//
//  function traits.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 4/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_function_traits_hpp
#define engine_utils_function_traits_hpp

#include <functional>
#include "../Type List/index.hpp"

namespace Utils {
  template <typename Function>
  struct function_traits;

  template <typename Function>
  using function_ret = typename function_traits<Function>::ret;

  template <typename Function, size_t I>
  using function_arg = typename function_traits<Function>::template arg<I>;
  
  template <typename Function>
  constexpr size_t function_arity = function_traits<Function>::arity;

  template <typename Function>
  constexpr bool is_mem_var = function_traits<Function>::is_mem_var;

  template <typename Function>
  constexpr bool is_mem_fun = function_traits<Function>::is_mem_fun;

  //function
  template <bool NOEXCEPT, typename Return, typename ...Args>
  struct function_traits<Return (Args...) noexcept(NOEXCEPT)> {
    using ret = Return;
    
    static constexpr size_t arity = sizeof...(Args);
    using args = List::Type<Args...>;
    template <size_t I>
    using arg = List::AtIndex<args, I>;
    
    static constexpr bool is_noexcept = NOEXCEPT;
    
    static constexpr bool is_mem_fun = false;
    static constexpr bool is_mem_var = false;
    
    using mem_class_type = void;
    using mem_var_type = void;
    
    static constexpr bool is_const_mem_fun = false;
    static constexpr bool is_lvalue_mem_fun = false;
    static constexpr bool is_rvalue_mem_fun = false;
  };

  //member function
  template <typename Function, typename Class, bool CONST, bool LVALUE, bool RVALUE>
  struct member_function : function_traits<Function> {
    static constexpr bool is_mem_fun = true;
    
    using mem_class_type = Class;
    
    static constexpr bool is_const_mem_fun = CONST;
    static constexpr bool is_lvalue_mem_fun = LVALUE;
    static constexpr bool is_rvalue_mem_fun = RVALUE;
  };

  //member variable
  template <typename Function, typename Class>
  struct member_variable : function_traits<Function> {
    static constexpr bool is_mem_var = true;
    
    using mem_class_type = Class;
    using mem_var_type = typename function_traits<Function>::ret;
  };

  //pointer to member function
  template <bool NOEXCEPT, typename Class, typename Return, typename ...Args>
  struct function_traits<Return (Class::*) (Args...) noexcept(NOEXCEPT)> :
    member_function<Return (Args...) noexcept(NOEXCEPT), Class, false, true, true> {};

  //pointer to const member function
  template <bool NOEXCEPT, typename Class, typename Return, typename ...Args>
  struct function_traits<Return (Class::*) (Args...) const noexcept(NOEXCEPT)> :
    member_function<Return (Args...) noexcept(NOEXCEPT), Class, true, true, true> {};

  //pointer to lvalue member function
  template <bool NOEXCEPT, typename Class, typename Return, typename ...Args>
  struct function_traits<Return (Class::*) (Args...) & noexcept(NOEXCEPT)> :
    member_function<Return (Args...) noexcept(NOEXCEPT), Class, false, true, false> {};

  //pointer to const lvalue member function
  template <bool NOEXCEPT, typename Class, typename Return, typename ...Args>
  struct function_traits<Return (Class::*) (Args...) const & noexcept(NOEXCEPT)> :
    member_function<Return (Args...) noexcept(NOEXCEPT), Class, true, true, false> {};

  //pointer to rvalue member function
  template <bool NOEXCEPT, typename Class, typename Return, typename ...Args>
  struct function_traits<Return (Class::*) (Args...) && noexcept(NOEXCEPT)> :
    member_function<Return (Args...) noexcept(NOEXCEPT), Class, false, false, true> {};

  //pointer to const rvalue member function
  template <bool NOEXCEPT, typename Class, typename Return, typename ...Args>
  struct function_traits<Return (Class::*) (Args...) const && noexcept(NOEXCEPT)> :
    member_function<Return (Args...) noexcept(NOEXCEPT), Class, true, false, true> {};

  //pointer to member variable
  template <typename Class, typename Type>
  struct function_traits<Type (Class::*)> :
    member_variable<Type (), Class> {};

  //std::function
  template <bool NOEXCEPT, typename Return, typename ...Args>
  struct function_traits<std::function<Return (Args...) noexcept(NOEXCEPT)>> :
    function_traits<Return (Args...) noexcept(NOEXCEPT)> {};

  //functor
  template <typename Functor>
  struct function_traits :
    //use member function pointer specialization
    function_traits<decltype(&Functor::operator())> {};

  //const function
  template <typename Function>
  struct function_traits<const Function> : function_traits<Function> {};

  //lvalue reference to function
  template <typename Function>
  struct function_traits<Function &> : function_traits<Function> {};

  //rvalue reference to function
  template <typename Function>
  struct function_traits<Function &&> : function_traits<Function> {};
  
  //pointer to function
  template <typename Function>
  struct function_traits<Function *> : function_traits<Function> {};
}

#endif
