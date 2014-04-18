#include "kheap.h"
#include "monitor.h"

extern u32 end;
u32 place = 0;
u32 malloc_f(){
  u32 ret=0;
  if( place == 0 )
    place = (u32)&end;

  if( ( place & 0x00000FFF ) ){
    place +=0x1000;
    place &=0xFFFFF000;
  }

  ret = place;
  m_write("malloc frame:", INFO);
  m_putint(ret);
  m_write("\n", INFO);
  place +=0x1000;

  return ret;
    
}
