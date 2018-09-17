//
//  manager.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 11/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_event_manager_hpp
#define engine_event_manager_hpp

#include <deque>
#include <iostream>
#include "event.hpp"
#include "../Utils/profiler.hpp"
#include "../Time/stopwatch.hpp"
#include "../Utils/dispatcher.hpp"
#include "../Utils/safe down cast.hpp"
#include "../Utils/function traits.hpp"

namespace Game {
  class EventManager {
  private:
    using DispatcherImpl = Utils::GroupDispatcher<void (const Event::Ptr), void, Event::Type, uint32_t>;
    
  public:
    using Listener = DispatcherImpl::Listener;
    using ListenerID = DispatcherImpl::ListenerID;

    explicit EventManager(Time::Rep = std::numeric_limits<Time::Rep>::max());
    ~EventManager() = default;
    
    ///Write the names of all events in the queue to the given stream
    void printQueue(std::ostream &, char = '\n') const;
    
    ///Call the event listeners for each event. Never takes longer than
    ///timeLimit nanoseconds to process.
    void update();
    
    ///Emit an event
    void emit(Event::Ptr);
    ///Emit an event immediately
    void emitNow(Event::Ptr);
    
    ///Add a event listener
    ListenerID addListener(Event::Type, const Listener &);
    ///Remove a event listener
    void remListener(ListenerID);
    
    ///Add a universal event listener. A listener for any event
    ListenerID addAnyListener(const Listener &);
    
    ///Emit an event
    template <typename EventClass, typename ...Args>
    void emit(Args &&...);
    
    ///Emit an event immediately
    template <typename EventClass, typename ...Args>
    void emitNow(Args &&...);
    
    ///Emit an event immediately
    template <typename EventClass>
    void emitNow(std::shared_ptr<EventClass>);
    
    ///Add an event listener
    template <typename Function>
    ListenerID addListener(Function &&);
    
  private:
    //the type of an event listener listening to any event
    static const Event::Type ANY_TYPE;
  
    DispatcherImpl dispatcher;
    std::deque<Event::Ptr> queue[2];
    Time::Rep timeLimit;
    size_t currentQueue = 0;
  };
  
  inline std::unique_ptr<Game::EventManager> evtMan = nullptr;
}

#include "manager.inl"

#endif
