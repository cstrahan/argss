#if defined(__cplusplus)
extern "C" {
#endif

#define HAVE_RUBY_ZLIB
#define HAVE_RUBY_WIN32API

void Init_zlib();

void Init_Win32API();

#if defined(__cplusplus)
}
#endif
