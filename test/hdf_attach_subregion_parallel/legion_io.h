#ifndef __LEGION_IO_H__
#define __LEGION_IO_H__


#include "legion.h"

void current_utc_time(struct timespec *ts);

enum TaskIDs {
  TOP_LEVEL_TASK_ID,
  INIT_FIELD_TASK_ID,
  STENCIL_TASK_ID,
  CHECK_TASK_ID,
  COPY_VALUES_TASK_ID,
#ifdef TESTERIO_PHASER_TIMERS
  TIMER_TASK_ID,
#endif
};

enum FieldIDs {
  FID_TEMP,
  //  FID_SAL,
  //  FID_KE,
  //  FID_VOR,
  //  FID_PERS,
};



using namespace LegionRuntime::HighLevel;
using namespace LegionRuntime::Accessor;

struct Piece {
public: 
  LogicalRegion parent_lr;
  LogicalRegion child_lr;
  PhysicalRegion pr;
  DomainPoint dp;
  char shard_name[40];
private:
  
}; 


void PersistentRegion_init();

class PersistentRegion {
 public:
    PersistentRegion(HighLevelRuntime * runtime);
    
    void create_persistent_subregions(Context ctx, const char *name, LogicalRegion parent_lr,
                                      LogicalPartition lp,
                                      Domain dom, std::map<FieldID, std::string> &field_map); 

    void write_persistent_subregions(Context ctx, LogicalRegion src_lr, LogicalPartition src_lp);
    
    void read_persistent_subregions(Context ctx, LogicalRegion src_lr, LogicalPartition src_lp);


    LogicalRegion get_logical_region() { return parent_lr; }
    LogicalPartition get_logical_partition() { return lp; }
    
 private:
    //LogicalRegion get_subregion(LogicalPartition lp, Color c);
    std::vector<Piece> pieces; 
    HighLevelRuntime * runtime;
    LogicalPartition  lp;
    LogicalRegion parent_lr;
    Domain dom;
  std::map<FieldID, std::string> field_map;
#ifdef TESTERIO_SERIALIZE
  void * field_map_serial;
  size_t field_map_size; 
#endif
#ifdef TESTERIO_PHASER_TIMERS
  PhaseBarrier pb_write;
  PhaseBarrier pb_timer; 
  PhaseBarrier pb_read;
#endif
    
};

#endif
