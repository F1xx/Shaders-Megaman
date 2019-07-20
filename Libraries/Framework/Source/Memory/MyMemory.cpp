#include "FrameworkPCH.h"

#include "Utility/CPPList.h"

#if _DEBUG

// Undefine the 'new' defined by '#define new new(__FILE__, __LINE__)' in Memory.h.
// So 'new' simply means 'new' in this file.
#undef new

#define newtype_regular     1
#define newtype_array       2

// Assert when 'new' has been called this many times.
#define CountToAssertOn     UINT_MAX

class MemObject : public CPPListNode
{
public:
    const char* m_file;
    unsigned long m_line;
    unsigned int m_type;
    unsigned int m_size;
    unsigned int m_count;

    MemObject() :
        m_file(0),
        m_line(0),
        m_type(0),
        m_size(0),
        m_count(0)
    {
    }
};

CPPListHead g_Allocations;
unsigned int g_AllocationCount = 0;
size_t g_AllocationBytes = 0;

void MyMemory_ForgetAllPreviousAllocations()
{
    while( g_Allocations.GetHead() )
    {
        g_Allocations.RemHead();
    }
}

void MyMemory_ValidateAllocations(bool breakIfThereAreLeaks)
{
    OutputMessage( " \\/\\/\\/\\/\\/\\/ Start of memory leak dump \\/\\/\\/\\/\\/\\/ \n" );
    CPPListNode* pNode;
    for( pNode = g_Allocations.HeadNode.Next; pNode->Next; pNode = pNode->Next )
    {
        MemObject* obj = (MemObject*)pNode;
        assert( obj->m_type == newtype_regular || obj->m_type == newtype_array );
        assert( obj->Next != 0 );
        assert( obj->Prev != 0 );

        OutputMessage( "%s(%d): %d bytes unreleased. Count(%d) %s\n", obj->m_file, obj->m_line, obj->m_size, obj->m_count, obj->m_type == newtype_regular ? "" : "Array Allocation" );
    }
    OutputMessage( " /\\/\\/\\/\\/\\/\\ End of memory leak dump /\\/\\/\\/\\/\\/\\ \n" );

    if( breakIfThereAreLeaks && g_Allocations.GetHead() != 0 )
        __debugbreak();
}

//===========================================================================================
// Overrides for new/delete with file/line numbers.
//===========================================================================================

void* operator new(size_t size, const char* file, unsigned long line)
{
    assert( CountToAssertOn == UINT_MAX || g_AllocationCount != CountToAssertOn );
    assert( size > 0 );

    MemObject* mo = (MemObject*)malloc( size + sizeof(MemObject) );
    mo->m_file = file;
    mo->m_line = line;
    mo->m_type = newtype_regular;
    mo->m_size = size;
    mo->m_count = g_AllocationCount++;
    g_AllocationBytes += size;

    g_Allocations.AddTail( mo );

    return ((char*)mo) + sizeof(MemObject);
}

void* operator new[](size_t size, const char* file, unsigned long line)
{
    assert( CountToAssertOn == UINT_MAX || g_AllocationCount != CountToAssertOn );
    assert( size > 0 );

    MemObject* mo = (MemObject*)malloc( size + sizeof(MemObject) );
    mo->m_file = file;
    mo->m_line = line;
    mo->m_type = newtype_array;
    mo->m_size = size;
    mo->m_count = g_AllocationCount++;
    g_AllocationBytes += size;

    g_Allocations.AddTail( mo );

    return ((char*)mo) + sizeof( MemObject );
}

void operator delete(void* ptr, const char* file, unsigned long line)
{
    if( ptr == 0 )
        return;

    MemObject* mo = (MemObject*)( ((char*)ptr) - sizeof(MemObject) );
    assert( mo->m_type == newtype_regular );
    g_AllocationBytes -= mo->m_size;
    mo->Remove();

    free( mo );
}

void operator delete[](void* ptr, const char* file, unsigned long line)
{
    if( ptr == 0 )
        return;

    MemObject* mo = (MemObject*)( ((char*)ptr) - sizeof(MemObject) );
    assert( mo->m_type == newtype_array );
    g_AllocationBytes -= mo->m_size;
    mo->Remove();

    free( mo );
}

//===========================================================================================
// Overrides for global new/delete.
//===========================================================================================

void* operator new(size_t size)
{
    return operator new( size, "File not defined", 0 );
}

void* operator new[](size_t size)
{
    return operator new[]( size, "File not defined", 0 );
}

void operator delete(void* ptr)
{
    operator delete( ptr, 0, 0 );
}

void operator delete[](void* ptr)
{
    operator delete[]( ptr, 0, 0 );
}

#endif //_DEBUG
