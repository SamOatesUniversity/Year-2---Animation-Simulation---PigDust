#pragma once
#ifndef __TWM_CORE_TIMER__
#define __TWM_CORE_TIMER__

namespace twm
{
  class Timer //(be sure windows timer is set to 1ms accuracy
  {
  public:
    unsigned int GetTime() const;
    void Sleep( unsigned int duration );
  };
}

#endif
