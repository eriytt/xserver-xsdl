INCLUDES = 					\
	@KDRIVE_PURE_INCS@				\
	@KDRIVE_CFLAGS@	\
	@VRX_INCS@

bin_PROGRAMS = vrx

vrx_SOURCES = android_main.c vrx.c vrxinit.c kbd.c mouse.c os.c fake.h

vrx_LDADD = \
	@KDRIVE_LIBS@\
	@VRX_LIBS@

vrx_DEPENDENCIES =  @KDRIVE_LOCAL_LIBS@

vrx_LDFLAGS = $(LD_EXPORT_SYMBOLS_FLAG)

noinst_LIBRARIES = libvrx.a

libvrx_a_SOURCES = vrx.c vrxinit.c kbd.c mouse.c os.c fake.h

relink:
	rm -f $(bin_PROGRAMS) && make $(bin_PROGRAMS)
