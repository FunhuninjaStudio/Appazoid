#pragma once
#include<memory>
#include<Logging/Log.h>

#ifndef APPAZOID_DISABLE_MEMORY_TRACKING

namespace az
{
	class MemoryTracker
	{
	public:
		static unsigned int total_allocations_count;
		static unsigned int total_deallocations_count;

		static unsigned int total_allocated_memory;
		static unsigned int total_deallocated_memory;


		static unsigned int allocated_memory;

		MemoryTracker(const MemoryTracker& ) = delete;
		void operator=(const MemoryTracker&) = delete;

		static void Print()
		{
			GetInst().m_Print();
		}
		static MemoryTracker& GetInst()
		{
			static MemoryTracker inst;
			return inst;
		}
	private:
		void m_Print()
		{
			APPAZOID_CORE_INFO("MemoryTracker::total_allocations_count = {0}",total_allocations_count);
			APPAZOID_CORE_INFO("MemoryTracker::total_deallocations_count = {0}",total_deallocations_count);

			APPAZOID_CORE_INFO("MemoryTracker::total_allocations_count = {0}", total_allocated_memory);
			APPAZOID_CORE_INFO("MemoryTracker::total_deallocations_count = {0}", total_deallocated_memory);

			APPAZOID_CORE_INFO("MemoryTracker::allocated_memory = {0}", allocated_memory);
		}
		MemoryTracker()
		{
			//total_allocations_count=(0);
			//total_deallocations_count=(0);
			//total_allocated_memory=(0);
			//total_deallocated_memory=(0);
			//allocated_memory=(0);
		}
	}; 
	unsigned int MemoryTracker::total_allocations_count		=	0;
	unsigned int MemoryTracker::total_deallocations_count	=	0;
	unsigned int MemoryTracker::total_allocated_memory		=	0;
	unsigned int MemoryTracker::total_deallocated_memory	=	0;
	unsigned int MemoryTracker::allocated_memory			=	0;

}

void* operator new(size_t size)
{
	void* ptr = malloc(size);
	az::MemoryTracker::total_allocations_count += 1;
	az::MemoryTracker::total_allocated_memory += size;
	az::MemoryTracker::allocated_memory += size;
	return ptr;
}

void operator delete(void* memory, size_t size)
{
	az::MemoryTracker::total_deallocations_count += 1;
	az::MemoryTracker::total_deallocated_memory += size;
	az::MemoryTracker::allocated_memory -= size;
	free(memory);
}
#endif