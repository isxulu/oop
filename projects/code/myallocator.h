#ifndef MY_ALLOCATOR_H
#define MY_ALLOCATOR_H
#include <cstddef>
#include <type_traits>
#include <climits>
#include <utility>
#include <new>

using namespace std;

template <typename T, size_t BlockSize = 4096>
class MyAllocator {
public:
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef const T* const_pointer;
	typedef const T& const_reference;
	typedef size_t size_type;			// unsigned long
	typedef ptrdiff_t difference_type;	// long
	typedef true_type propagate_on_container_move_assignment;
	typedef true_type is_always_equal;

	template <typename U> struct rebind {
		typedef MyAllocator<U> other;
	};

    // constructor for MyAllocator
	constexpr MyAllocator() noexcept;
	constexpr MyAllocator(const MyAllocator& myallocator) noexcept;
	MyAllocator(MyAllocator&& myallocator) noexcept;
	template <class U>MyAllocator(const MyAllocator<U>& myallocator) noexcept;

    // destructor for MyAllocator
	~MyAllocator() noexcept;
	
    // overload operator =
	MyAllocator& operator=(const MyAllocator& myallocator) = delete;
	MyAllocator& operator=(MyAllocator&& myallocator) noexcept;

	pointer address(reference x) const noexcept;
	const_pointer address(const_reference x) const noexcept;

	pointer allocate(size_type n, const void* hint = 0);
	constexpr void deallocate(pointer p, size_type n);
	
	size_type max_size() const noexcept;
	
	template <class U, class... Args> void construct(U* p, Args&&... args);
	template <class U> void destroy(U* p);

private:
	union Slot_ {
		union Slot_* next;      // in allocator free list, used as pointer to the next node
        char element[1];  		// store the data when 
	};

    enum {ALIGN = 8};				// pgraded boundaries for small blocks
    enum {MAXBYTE = 128};			// upper bytes limites for small blocks
    enum {NUMBEROFFREELISTS = 16};	// number of freelist

	typedef char* data_pointer_;
	typedef Slot_ slot_type_;
	typedef Slot_* slot_pointer_;

	slot_pointer_ volatile freeLists[NUMBEROFFREELISTS];	// freelists
	data_pointer_ start;	// the start position of the memory pool
	data_pointer_ end;		// the end position of the memory pool
	
	void allocateBlock();
	slot_pointer_ allocateChunk(int idx);
	
	static_assert(BlockSize >= 2 * sizeof(slot_type_), "Blocksize too small.");
};

//TODO
template<typename T, size_t BlockSize>
constexpr MyAllocator<T, BlockSize>::MyAllocator() noexcept {
	for ( int i = 0; i < NUMBEROFFREELISTS; i++ ) {
		freeLists[i] = nullptr;
    }
	start = nullptr;
	end = nullptr;
}

template<typename T, size_t BlockSize>
constexpr MyAllocator<T, BlockSize>::MyAllocator(const MyAllocator & myallocator) noexcept:MyAllocator() {}

//TODO
template<typename T, size_t BlockSize>
MyAllocator<T, BlockSize>::MyAllocator(MyAllocator && myallocator) noexcept {
	for ( int i = 0; i < NUMBEROFFREELISTS; i++ ) {
		freeLists[i] = myallocator.freeLists[i];
	}
	start = myallocator.start;
	end = myallocator.end;
}

template<typename T, size_t BlockSize>
template <class U>
MyAllocator<T, BlockSize>::MyAllocator(const MyAllocator<U>& myallocator) noexcept:MyAllocator() {}

//TODO
template<typename T, size_t BlockSize>
MyAllocator<T, BlockSize>::~MyAllocator() noexcept {
	for ( int i = 0; i < NUMBEROFFREELISTS; i++ ) {
		freeLists[i] = nullptr;
	}
	start = nullptr;
	end = nullptr;
}

//TODO
template<typename T, size_t BlockSize>
MyAllocator<T, BlockSize> & MyAllocator<T, BlockSize>::operator=(MyAllocator && myallocator) noexcept {
	for ( int i = 0; i < NUMBEROFFREELISTS; i++ ) {
		freeLists[i] = myallocator.freeLists[i];
	}
	start = myallocator.start;
	end = myallocator.end;
}

template<typename T, size_t BlockSize>
inline typename MyAllocator<T, BlockSize>::pointer MyAllocator<T, BlockSize>::address(reference x) const noexcept {
	return &x;
}

template <typename T, size_t BlockSize>
inline typename MyAllocator<T, BlockSize>::const_pointer MyAllocator<T, BlockSize>::address(const_reference x) const noexcept {
	return &x;
}

//TODO
template<typename T, size_t BlockSize>
void MyAllocator<T, BlockSize>::allocateBlock() {
	// Allocate space for the new block and store a pointer to the previous one
	start = reinterpret_cast<data_pointer_>(operator new(BlockSize));
	end = reinterpret_cast<data_pointer_>(start + BlockSize);
}

//TODO
template<typename T, size_t BlockSize>
inline typename MyAllocator<T, BlockSize>::pointer MyAllocator<T, BlockSize>::allocate(size_type n, const void* hint) {
	pointer res = nullptr;
	/* if the required block is larger than 128 bytes, throw an exception */
	if ( n >= max_size() ) {
		throw new std::bad_array_new_length;
	}
	/* find the corresponding free list based on the size of the application space (one of 16 free lists) */
	else {
		size_type bytes = n * sizeof(value_type);
		/* negative size, throw an exception */
		if ( bytes <= 0 ) {
			throw new std::bad_alloc;
		}
		/* need more than 128 bytes, new */
		else if ( bytes > (size_type)MAXBYTE ) {
			res = reinterpret_cast<pointer>(operator new(bytes));
		}
		/* allocate from the freelist */
		else {
			int idx = (bytes-1) / 8;					// find the corresponding freelist[idx]
			/* there is a free block, take it away */
			if ( freeLists[idx] != nullptr ) {
				res = reinterpret_cast<pointer>(freeLists[idx]);
				freeLists[idx] = freeLists[idx]->next;
			}
			/* there is no free block, need fill */
			else {
				res = reinterpret_cast<pointer>(allocateChunk(idx));
			}
		}
	}
	return res;
}

//TODO
template<typename T, size_t BlockSize>
inline typename MyAllocator<T, BlockSize>::slot_pointer_ MyAllocator<T, BlockSize>::allocateChunk(int idx) {
	slot_pointer_ currSlot, nextSlot;
	size_type bytesLeft = end - start;		// number of bytes that left in memory pool
	data_pointer_ res = nullptr;			// the return data pointer

	int defaultSlotNum = 10;								// default return block number
	size_type bytesStandard = ALIGN * (idx+1);				// round up bytes number
	size_type bytesNeed = defaultSlotNum * bytesStandard;	// total bytes needed

	/* enough memory for all defaultSlotNum's bytes */
	if ( bytesLeft >= bytesNeed ) {
		res = start;					// return address
		start += bytesNeed;				// adjust the start address in the memory pool
		freeLists[idx] = nextSlot = reinterpret_cast<slot_pointer_>(res + bytesStandard);	// let freeLists[idx] point to the next available address
		// attach all the newly allocate blocks into the corresponding freeLists
		for ( int i = 1; ; i++ ) {
			currSlot = nextSlot;
			nextSlot = (slot_pointer_)((data_pointer_)nextSlot + bytesStandard);
			if ( i == defaultSlotNum - 1 ) {
				currSlot->next = nullptr;
				break;
			}
			currSlot->next = nextSlot;
		}
		return reinterpret_cast<slot_pointer_>(res);
	}
	/* not enough memory for all defaultSlotNum but at least 1 bytesStandard */
	else if ( bytesLeft >= bytesStandard ) {
		defaultSlotNum = bytesLeft / bytesStandard;
		bytesNeed = defaultSlotNum * bytesStandard;
		// set the return address
		res = start;
		start += bytesNeed;
		if ( defaultSlotNum > 1 ) {
			freeLists[idx] = nextSlot = reinterpret_cast<slot_pointer_>(res + bytesStandard);
			for ( int i = 1; ; i++ ) {
				currSlot = nextSlot;
				nextSlot = (slot_pointer_)((data_pointer_)nextSlot + bytesStandard);
				if ( i == defaultSlotNum - 1 ) {
					currSlot->next = nullptr;
					break;
				}
				currSlot->next = nextSlot;
			}
		}
		return reinterpret_cast<slot_pointer_>(res);
	}
	/* not enough memory for even one bytesStandard */
	else {
		allocateBlock();
		return allocateChunk(idx);
	}
}

//TODO
template<typename T, size_t BlockSize>
inline constexpr void MyAllocator<T, BlockSize>::deallocate(pointer p, size_type n) {
	size_type bytes = n * sizeof(value_type);
	int idx = (bytes - 1) / 8;
	if ( bytes <= 0 ) {
		throw new std::bad_alloc;
	}
	/* free more than 128 bytes, new */
	else if ( bytes > (size_type)MAXBYTE ) {
		operator delete(p);
		return;
	}
	/* deallocate the freelist */
	else {
		slot_pointer_ q = reinterpret_cast<slot_pointer_>(p);
		q->next = freeLists[idx];
		freeLists[idx] = q;
	}
}

template<typename T, size_t BlockSize>
inline typename MyAllocator<T, BlockSize>::size_type MyAllocator<T, BlockSize>::max_size() const noexcept {
	size_type maxBlocks = -1 / BlockSize;
	return (BlockSize - sizeof(data_pointer_)) / sizeof(slot_type_)*maxBlocks;
	// return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

template<typename T, size_t BlockSize>
template<class U, class... Args>
inline void MyAllocator<T, BlockSize>::construct(U* p, Args&&... args) {
	new (p) U(forward<Args>(args)...);
}

template<typename T, size_t BlockSize>
template<class U>
inline void MyAllocator<T, BlockSize>::destroy(U* p) {
	p->~U();
}

#endif // !MY_ALLOCATOR_H
