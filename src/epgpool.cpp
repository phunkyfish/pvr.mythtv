
#include "epgpool.h"

#include "client.h"
#include "taskhandler.h"

#define DELAY_PURGE 30000 // delay in milliseconds to purge an inactive pool

EPGPool::EPGPool(Myth::Control *control, TaskHandler *taskHandler)
: m_control(control)
, m_taskHandler(taskHandler)
, m_start(0)
, m_end(0)
, m_pool()
, m_lock()
, m_pinned(0)
{
}

class PurgeEPGPool : public Task
{
public:
  PurgeEPGPool(EPGPool* pool, unsigned mark)
  : Task()
  , m_pool(pool)
  , m_mark(mark) { }

  virtual void Execute()
  {
    m_pool->Purge(m_mark);
  }

  EPGPool *m_pool;
  unsigned m_mark;
};

Myth::ProgramMapPtr EPGPool::GetProgramGuide(uint32_t chanId, time_t startTime, time_t endTime)
{
  P8PLATFORM::CLockObject lock(m_lock);
  if (m_pinned == 0)
    SchedulePurge();
  ++m_pinned;

  // Is data loaded for the requested period ?
  if (m_start <= startTime && m_end >= endTime)
  {
    // Find the set for this channel and return
    epg_t::iterator it = m_pool.find(chanId);
    if (it != m_pool.end())
      return it->second;
    return Myth::ProgramMapPtr();
  }

  // Clear data before start the new batch
  XBMC->Log(ADDON::LOG_DEBUG, "%s: Clear EPG data", __FUNCTION__);
  m_pool.clear();
  m_start = startTime;
  m_end = endTime;

  if (m_control->IsOpen())
  {
    XBMC->Log(ADDON::LOG_NOTICE, "%s: Start BULK loading for period [%s,%s]", __FUNCTION__, Myth::TimeToString(m_start).c_str(), Myth::TimeToString(m_end).c_str());
    epg_t epg = m_control->GetProgramGuide(m_start, m_end);
    epg_t::iterator rit = epg.end();
    size_t c = 0;
    for (epg_t::iterator it = epg.begin(); it != epg.end(); ++it)
    {
      m_pool.insert(*it);
      if (it->first == chanId)
        rit = it;
      if (g_bExtraDebug)
        XBMC->Log(ADDON::LOG_DEBUG, "%s: Channel %u is loaded (%lu)", __FUNCTION__, it->first, it->second->size());
      c += it->second->size();
    }
    XBMC->Log(ADDON::LOG_NOTICE, "%s: End loading (%lu,%lu)", __FUNCTION__, epg.size(), c);
    if (rit != epg.end())
      return rit->second;
  }
  return Myth::ProgramMapPtr(new Myth::ProgramMap);
}

void EPGPool::Purge(unsigned mark)
{
  P8PLATFORM::CLockObject lock(m_lock);
  // delay the purge when the pool has been requested
  if (m_pinned > mark)
    SchedulePurge();
  else
  {
    // Purge the pool now
    m_pinned = 0;
    m_start = m_end = 0;
    m_pool.clear();
    XBMC->Log(ADDON::LOG_NOTICE, "%s: EPG data purged", __FUNCTION__);
  }
}

void EPGPool::SchedulePurge()
{
  m_taskHandler->ScheduleTask(new PurgeEPGPool(this, m_pinned), DELAY_PURGE);
  XBMC->Log(ADDON::LOG_INFO, "%s: Purge of EPG data is delayed", __FUNCTION__);
}
