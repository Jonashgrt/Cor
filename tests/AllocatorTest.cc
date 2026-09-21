#include <Cor/Allocator.hh>

#include <stdio.h>

#include <Cor/Allocators/SystemAllocator.hh>


struct FSysEventCallback
{
	U32 i = 0;
};

COR_DECLARE_ALLOCATOR_CALLBACK(SysEventCallback)
{
	if (pEvent->Type == cor::EAllocatorEventType::Allocate && pEvent->NewNumBytes == 1024)
		printf("Penis");

	printf("%u", ((U32)(((FSysEventCallback*)pContext)->i)));
}

int main(void)
{
	cor::FAllocator SysAlloc{ };

	cor::FAllocatorCallbacks SysCallbacks{ };
	
	FSysEventCallback SysEventCallbackContext { 69 };
	SysCallbacks.pContext = (void*)&SysEventCallbackContext;
	SysCallbacks.pfnEvent = SysEventCallback;

	cor::InitializeSystemAllocator(&SysAlloc, &SysCallbacks);

	void* pMem = cor::Allocate(&SysAlloc, 1024, 64);

	return 88;
}