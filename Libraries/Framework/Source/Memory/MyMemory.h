#ifndef __MyMemory_H__
#define __MyMemory_H__

#if _DEBUG

void MyMemory_ForgetAllPreviousAllocations();
void MyMemory_ValidateAllocations(bool breakIfThereAreLeaks);

void* operator new(size_t size, const char* file, unsigned long line);
void* operator new[](size_t size, const char* file, unsigned long line);
void operator delete(void* ptr, const char* file, unsigned long line);
void operator delete[](void* ptr, const char* file, unsigned long line);

void* operator new(size_t size);
void* operator new[](size_t size);
void operator delete(void* ptr);
void operator delete[](void* ptr);

#define new new(__FILE__, __LINE__)

#endif //_DEBUG

#endif //__MyMemory_H__
