#ifndef __BINARY_H__
#define __BINARY_H__

#ifndef _WIN32
#define MEDIA_START(filename, extension) _binary_##filename##_##extension##_start
#define MEDIA_END(filename, extension) _binary_##filename##_##extension##_end
#else
#define MEDIA_START(filename, extension) binary_##filename##_##extension##_start
#define MEDIA_END(filename, extension) binary_##filename##_##extension##_end
#endif
#define MEDIA_BINARY(filename, extension) \
  extern unsigned char MEDIA_START(filename, extension)[]; \
  extern unsigned char MEDIA_END(filename, extension)[];

#endif
