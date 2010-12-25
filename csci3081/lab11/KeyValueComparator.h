#include "KeyValuePair.h"

class KeyValueComparator
{
  public:
    bool operator()(const KeyValuePair& a, const KeyValuePair& b) const;
};
