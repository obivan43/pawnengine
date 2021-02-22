#pragma once

#if defined(DEBUG) | defined(_DEBUG)

void OpenglCallDebug(const char* file, unsigned int line, const char* expression);

#ifndef OpenglCall
#define OpenglCall(x) do { x; OpenglCallDebug(__FILE__, __LINE__, #x); } while(false);
#endif
#else
#ifndef OpenglCall
#define OpenglCall(x) (x);
#endif
#endif
