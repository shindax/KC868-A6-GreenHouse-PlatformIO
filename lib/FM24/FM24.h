#include "Wire.h"

#ifndef _FM24_H_
#define _FM24_H_

class FM24 
{
  private:
    int id;
  public:
    FM24(int id_addr = 0);
    ~FM24();
    void pack(int addr, void* data, int len);     // Pack data into FRAM
    int unpack(int addr, void* data, int len);    // Unpack data from FRAM. Returns number of bytes read.
    void inline writeUnsignedLong(int addr, unsigned long data) {
      pack(addr, (void*)&data, sizeof(unsigned long));
    } 
    unsigned long inline readUnsignedLong(int addr) {
      unsigned long data;
      return unpack(addr, (void*)&data, sizeof(unsigned long)) == sizeof(unsigned long) ? data : 0UL;
    }
};

#endif