#ifndef foo_h__
#define foo_h__
#include <string>
#include <cstring>

using namespace std;
typedef struct {
    string label;
    float prob;
} pred_t;

extern pred_t* libaudioAPI(const char* audio, pred_t* predd);
 
#endif  // foo_h__
