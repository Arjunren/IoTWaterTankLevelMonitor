#pragma once
#include <math.h>
struct Sample { float value; float aux; bool valid; };
inline bool isAlert(const Sample &s) {
  if (!s.valid || !isfinite(s.value) || !isfinite(s.aux)) return false;
  if (s.value < 2.0f || s.value > 200.0f) return false;
  return s.aux < 15.0f;
}
