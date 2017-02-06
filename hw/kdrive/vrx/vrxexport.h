#include <X11/X.h>

struct WindowHandle;

typedef void (*OnCreateWindowFunc)(struct WindowHandle *, void *arg);
typedef void (*OnDestroyWindowFunc)(struct WindowHandle *, void *arg);

typedef struct {
  short int root_x, root_y;
  short int win_x, win_y;
} QueryPointerReturn;

typedef QueryPointerReturn (*QueryPointerFunc)(struct WindowHandle *, void *arg);
typedef struct WindowHandle *(*QueryPointerWindowFunc)(void *arg);

void VRXSetCallbacks(OnCreateWindowFunc wCreate,
                     OnDestroyWindowFunc wDestroy,
                     QueryPointerFunc qPointer,
                     QueryPointerWindowFunc qPointerWindow,
                     void *arg);
void *VRXGetWindowBuffer(struct WindowHandle *w, unsigned int *wret, unsigned int *hret,
                         unsigned int *mapped);
void VRXMouseMotionEvent(int x, int y, int relative);

Window getWindowFromHandle(const struct WindowHandle *w);

