#pragma once
namespace synchlib {

	typedef void* synhandle;
	synhandle synch_CreateSharedMemory(const char* shmname, int size) 
	{
		
	};

	void PrintMessage();

	//gcc -o synchlib synchlib.c

	/*synhandle synch_OpenSharedMemory(const char* shmname, int size)
	{
		if ( shmname)
	}
	int synch_WriteSharedMemory(synhandle handle, int pos, char* value, int vsz)
	{
	}
	int synch_ReadSharedMemory(synhandle handle, int pos, char* value, int vsz)
	{
	}
	int synch_CloseSharedMemory(synhandle handle)
	{
	}
	synhandle synch_CreateMutex(const char* mtxname)
	{
	}
	int synch_DestroyMutex(synhandle handle)
	{
	}*/
};