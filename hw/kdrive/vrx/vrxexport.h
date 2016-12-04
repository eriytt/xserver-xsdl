struct WindowHandle;

typedef void (*OnCreateWindowFunc)(struct WindowHandle *, void *arg);
typedef void (*OnDestroyWindowFunc)(struct WindowHandle *, void *arg);

void VRXSetCallbacks(OnCreateWindowFunc wCreate,
		     OnDestroyWindowFunc wDestroy,
		     void *arg);
void *VRXGetWindowBuffer(struct WindowHandle *w, unsigned int *wret, unsigned int *hret);
