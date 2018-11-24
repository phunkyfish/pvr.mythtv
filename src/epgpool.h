#pragma once
/*
 * File:   MythEPGPool.h
 * Author: jlb
 *
 * Created on November 18, 2018, 8:57 PM
 */

#include <mythcontrol.h>
#include <p8-platform/threads/mutex.h>

#include <map>

#include "taskhandler.h"

class EPGPool
{
public:
  EPGPool(Myth::Control *control, TaskHandler *taskHandler);
  virtual ~EPGPool() { }

  Myth::ProgramMapPtr GetProgramGuide(uint32_t chanId, time_t startTime, time_t endTime);
  void Purge(unsigned mark);

private:
  Myth::Control *m_control;
  TaskHandler *m_taskHandler;
  time_t m_start;
  time_t m_end;
  typedef std::map<uint32_t, Myth::ProgramMapPtr> epg_t;
  epg_t m_pool;
  mutable P8PLATFORM::CMutex m_lock;   ///< protect the pool during change
  unsigned m_pinned;                   ///< count request

  void SchedulePurge();
};