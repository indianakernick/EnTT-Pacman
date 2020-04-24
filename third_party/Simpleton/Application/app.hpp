//
//  app.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_application_app_hpp
#define engine_application_app_hpp

#include "../Time/main loop.hpp"
#include "../Utils/member function.hpp"

namespace Game {
  template <typename Duration>
  class App {
  private:
    using Rep = typename Duration::rep;
    
  public:
    App() = default;
    virtual ~App() = default;
    
    void mainLoop(const Rep step, const uint32_t maxSteps) {
      if (!init()) {
        return;
      }
      
      Time::Mainloop<Duration>::fixedWithVarPrePost(
        Utils::memFunWrap(this, &App::input),
        Utils::memFunWrap(this, &App::update),
        Utils::memFunWrap(this, &App::render),
        step,
        maxSteps
      );
      
      quit();
    }
    
  private:
    virtual bool init() = 0;
    virtual void quit() = 0;
    virtual bool input(Rep) = 0;
    virtual bool update(Rep) = 0;
    virtual void render(Rep) = 0;
  };
}

#endif
