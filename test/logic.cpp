#include <cassert>
#include <limits>
#include "logic.h"
int main() {
  assert(isAlert(Sample{90.0f,10.0f,true})==true);
  assert(!isAlert(Sample{20.0f,80.0f,true}));
  assert(!isAlert(Sample{90.0f,10.0f,false}));
  assert(!isAlert(Sample{1.0f,0,true}));
  assert(!isAlert(Sample{201.0f,0,true}));
  assert(!isAlert(Sample{std::numeric_limits<float>::quiet_NaN(),0,true}));
}
