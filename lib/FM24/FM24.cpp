#include <Arduino.h>
#include "FM24.h"

FM24::FM24(int id_addr) {
  id=id_addr;
}

FM24::~FM24() {}

void FM24::pack(int addr, void* data, int len) {
  Wire.beginTransmission(id);
  Wire.write((byte*)&addr,2);
  Wire.write((byte*)data,len);
  Wire.endTransmission(true);
}

int FM24::unpack(int addr, void* data, int len) {
  int rc;
  byte *p;
  Wire.beginTransmission(id);
  Wire.write((byte*)&addr,2);
  Wire.endTransmission(false);
  Wire.requestFrom(id,len);
  for (rc=0, p=(byte*)data; Wire.available() && rc < len; rc++, p++) {
    *p=Wire.read();
  }
  return(rc);
}