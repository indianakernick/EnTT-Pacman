//
//  camera.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 15/11/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

inline void Cam2D::Camera::setPos(const glm::vec2 pos) {
  props.pos = pos;
}

inline void Cam2D::Camera::setZoom(const float scale) {
  props.scale = scale;
}

inline void Cam2D::Camera::setAngle(const float angle) {
  props.angle = angle;
}

namespace Cam2D::detail {
  // http://stackoverflow.com/a/48741208

  template <PropID PROP>
  constexpr std::true_type isTarget(const Target<PROP> &) {
    return {};
  }
  
  template <PropID PROP>
  constexpr std::false_type isTarget(const Animate<PROP> &) {
    return {};
  }
  
  template <typename T>
  constexpr bool is_target_v = decltype(isTarget(std::declval<T>()))::value;
  
  template <typename, typename, typename, size_t I = 0>
  struct Split;
  
  template <
    size_t... TARGET_IDX,
    size_t... ANIM_IDX,
    size_t N
  >
  struct Split<
    std::index_sequence<TARGET_IDX...>,
    std::index_sequence<ANIM_IDX...>,
    std::tuple<>,
    N
  > {
    using Targets = std::index_sequence<TARGET_IDX...>;
    using Anims = std::index_sequence<ANIM_IDX...>;
  };
  
  template <
    size_t... TARGET_IDX,
    size_t... ANIM_IDX,
    size_t I,
    typename T,
    typename... Tail
  >
  struct Split<
    std::index_sequence<TARGET_IDX...>,
    std::index_sequence<ANIM_IDX...>,
    std::tuple<T, Tail...>,
    I
  > : std::conditional_t<
    is_target_v<T>,
    Split<
      std::index_sequence<TARGET_IDX..., I>,
      std::index_sequence<ANIM_IDX...>,
      std::tuple<Tail...>,
      I + 1
    >,
    Split<
      std::index_sequence<TARGET_IDX...>,
      std::index_sequence<ANIM_IDX..., I>,
      std::tuple<Tail...>,
      I + 1
    >
  > {};
}

template <typename... Args>
void Cam2D::Camera::update(const Params params, Args &&... args) {
  using Split = detail::Split<
    std::index_sequence<>,
    std::index_sequence<>,
    std::tuple<std::decay_t<Args>...>
  >;
  updateImpl(
    params,
    typename Split::Targets{},
    typename Split::Anims{},
    std::forward_as_tuple(args...)
  );
}

template <size_t... TARGET_IDX, size_t... ANIM_IDX, typename Tuple>
void Cam2D::Camera::updateImpl(
  const Params params,
  std::index_sequence<TARGET_IDX...>,
  std::index_sequence<ANIM_IDX...>,
  const Tuple &tuple
) {
  Props targetProps = props;
  ((
    getProp<std::decay_t<std::tuple_element_t<TARGET_IDX, Tuple>>::PROP>(targetProps)
    = std::get<TARGET_IDX>(tuple).calcTarget(props, params)
  ), ...);
  ((
    getProp<std::decay_t<std::tuple_element_t<ANIM_IDX, Tuple>>::PROP>(targetProps)
    = std::get<ANIM_IDX>(tuple).calculate(props, params, getProp<std::decay_t<std::tuple_element_t<ANIM_IDX, Tuple>>::PROP>(targetProps))
  ), ...);
  props = targetProps;
  transform.calculate(props, params);
}
