#include "RE/H/hkArray.h"

namespace RE
{
	namespace hkArrayUtil
	{
		void _reduce(hkMemoryAllocator& allocator, void* _array, int32_t sizeElem, void* inplaceMem, int32_t requestedCapacity)
		{
			hkArray<uint64_t>* array = static_cast<hkArray<uint64_t>*>(_array);
			if (inplaceMem && array->size() < requestedCapacity) {
				std::memcpy(inplaceMem, array->data(), static_cast<size_t>(sizeElem * array->size()));
				allocator.BufFree(array->data(), sizeElem * array->capacity());
				array->_data = static_cast<uint64_t*>(inplaceMem);
				array->_capacityAndFlags = requestedCapacity | array->kDontDeallocFlag;
			} else {
				assert(array->shouldDeallocate());
				int32_t oldNumBytes = array->_capacityAndFlags * sizeElem;
				int32_t reqNumBytes = requestedCapacity * sizeElem;
				array->_data = static_cast<uint64_t*>(allocator.BufRealloc(array->data(), oldNumBytes, reqNumBytes));
				array->_capacityAndFlags = reqNumBytes / sizeElem;
			}
		}

		void _reserveMore(hkMemoryAllocator& allocator, void* _array, int32_t sizeElem)
		{
			hkArray<uint64_t>* array = static_cast<hkArray<uint64_t>*>(_array);

			int32_t new_array_cap = array->size() ? 2 * array->size() : 1;
			int32_t reqNumBytes = sizeElem * new_array_cap;

			if (!array->shouldDeallocate()) {
				void* new_data = allocator.BufAlloc(reqNumBytes);
				std::memcpy(new_data, array->_data, static_cast<size_t>(sizeElem * array->size()));
				array->_data = static_cast<uint64_t*>(new_data);
			} else {
				array->_data = static_cast<uint64_t*>(allocator.BufRealloc(array->data(), sizeElem * array->capacity(), reqNumBytes));
			}

			array->_capacityAndFlags = reqNumBytes / sizeElem;
		}

		void _reserve(hkMemoryAllocator& allocator, void* _array, int32_t reqElem, int32_t sizeElem)
		{
			hkArray<uint64_t>* array = static_cast<hkArray<uint64_t>*>(_array);

			int32_t reqNumBytes = sizeElem * reqElem;

			if (!array->shouldDeallocate()) {
				void* new_data = allocator.BufAlloc(reqNumBytes);
				std::memcpy(new_data, array->data(), static_cast<size_t>(sizeElem * array->size()));
				array->_data = static_cast<uint64_t*>(new_data);
			} else {
				array->_data = static_cast<uint64_t*>(allocator.BufRealloc(array->data(), sizeElem * array->capacity(), reqNumBytes));
			}

			array->_capacityAndFlags = reqNumBytes / sizeElem;
		}
	}
}
