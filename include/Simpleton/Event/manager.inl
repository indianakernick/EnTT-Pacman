//
//  manager.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 11/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

inline const Game::Event::Type Game::EventManager::ANY_TYPE = GetEventType<EventManager>::get();

inline Game::EventManager::EventManager(const Time::Rep timeLimit)
  : timeLimit(timeLimit) {
  dispatcher.createGroup(ANY_TYPE);
}

inline void Game::EventManager::printQueue(std::ostream &stream, const char sep) const {
  const auto begin = queue[currentQueue].cbegin();
  const auto end = queue[currentQueue].cend();
  for (auto e = begin; e != end; ++e) {
    stream << (*e)->getName() << sep;
  }
}

inline void Game::EventManager::update() {
  PROFILE(Game::EventManager::update);
  
  Time::StopWatch<std::chrono::nanoseconds> stopwatch(true);
  const size_t processingQueue = currentQueue;
  currentQueue = (currentQueue + 1) % 2;
  
  while (!queue[processingQueue].empty()) {
    const Event::Ptr event = queue[processingQueue].front();
    queue[processingQueue].pop_front();
    emitNow(event);
    if (stopwatch.get() >= timeLimit) {
      break;
    }
  }
  
  if (!queue[processingQueue].empty()) {
    queue[currentQueue].insert(
      queue[currentQueue].begin(),
      queue[processingQueue].cbegin(),
      queue[processingQueue].cend()
    );
    queue[processingQueue].clear();
  }
}

inline void Game::EventManager::emit(const Event::Ptr msg) {
  assert(msg);
  PROFILE(Game::EventManager::emit);
  
  queue[currentQueue].push_back(msg);
}

inline void Game::EventManager::emitNow(const Event::Ptr msg) {
  assert(msg);
  PROFILE(Game::EventManager::emitNow);
  
  dispatcher.dispatch(msg->getType(), msg);
  dispatcher.dispatch(ANY_TYPE, msg);
}

inline Game::EventManager::ListenerID Game::EventManager::addListener(
  const Event::Type type,
  const Listener &listener
) {
  PROFILE(Game::EventManager::addListener);
  return dispatcher.addListenerAndCreateGroup(type, listener);
}

inline void Game::EventManager::remListener(const ListenerID id) {
  PROFILE(Game::EventManager::remListener);
  dispatcher.remListener(id);
}

inline Game::EventManager::ListenerID Game::EventManager::addAnyListener(const Listener &listener) {
  PROFILE(Game::EventManager::addAnyListener);
  return dispatcher.addListener(ANY_TYPE, listener);
}

template <typename EventClass, typename ...Args>
void Game::EventManager::emit(Args &&... args) {
  PROFILE(Game::EventManager::emit);

  emit(std::make_shared<EventClass>(std::forward<Args>(args)...));
}

template <typename EventClass, typename ...Args>
void Game::EventManager::emitNow(Args &&... args) {
  PROFILE(Game::EventManager::emitNow);
  
  const std::shared_ptr<EventClass> event = std::make_shared<EventClass>(std::forward<Args>(args)...);
  
  dispatcher.dispatch(GetEventType<EventClass>::get(), event);
  dispatcher.dispatch(ANY_TYPE, event);
}

template <typename EventClass>
void Game::EventManager::emitNow(const std::shared_ptr<EventClass> event) {
  assert(event);
  PROFILE(Game::EventManager::emitNow);
  
  dispatcher.dispatch(GetEventType<EventClass>::get(), event);
  dispatcher.dispatch(ANY_TYPE, event);
}

template <typename Function>
Game::EventManager::ListenerID Game::EventManager::addListener(Function &&listener) {
  PROFILE(Game::EventManager::addListener);

  using EventClass = typename Utils::function_arg<Function, 0>::element_type;
  return addListener(
    GetEventType<EventClass>::get(),
    [listener = std::forward<Function>(listener)] (const Event::Ptr event) {
      listener(Utils::safeDownCast<EventClass>(event));
    }
  );
}
