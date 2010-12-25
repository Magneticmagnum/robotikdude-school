#include "KeyValueComparator.h"

bool KeyValueComparator::operator()(const KeyValuePair& a,
                                    const KeyValuePair& b) const
{
  return (a.count < b.count);
}
