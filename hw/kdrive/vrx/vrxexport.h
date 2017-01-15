struct WindowHandle;

typedef void (*OnCreateWindowFunc)(struct WindowHandle *, void *arg);
typedef void (*OnDestroyWindowFunc)(struct WindowHandle *, void *arg);

typedef struct {
  int root_x, root_y;
  int win_x, win_y;
  int inside;
} QueryPointerReturn;

typedef QueryPointerReturn (*QueryPointerFunc)(struct WindowHandle *, void *arg);

void VRXSetCallbacks(OnCreateWindowFunc wCreate,
		     OnDestroyWindowFunc wDestroy,
		     QueryPointerFunc qPointer,
		     void *arg);
void *VRXGetWindowBuffer(struct WindowHandle *w, unsigned int *wret, unsigned int *hret,
			 unsigned int *mapped);
