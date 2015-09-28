/*
solution:	glib
project:	common
file:		pointer.h
author:		cj
*/

#pragma once

#ifndef NULL
#define NULL 0
#endif

namespace GEN {

	template<typename TYPE>
	class Pointer {
		template<typename IMPLICIT>
		friend class Pointer;
	private:
		mutable unsigned* _count;
		TYPE* _native;
	public:
		Pointer(void) : _native(NULL), _count(NULL) { }
		
		Pointer(TYPE* const native) : _native(NULL), _count(NULL) {
			_count = new unsigned(1);
			_native = native;
		}

		template<typename IMPLICIT>
		Pointer(IMPLICIT* const native) : _native(NULL), _count(NULL) {
			_count = new unsigned(1);
			_native = native;
		}

		Pointer(const Pointer& other) : _native(other._native), _count(other._count) {
			if(_count) _count++;
		}

		template<typename IMPLICIT>
		Pointer(const Pointer<IMPLICIT>& other) : _native(other._native), _count(other._count) {
			if(_count) _count++;
		}

		~Pointer(void) { Drop(); }

		void Drop(void) {
		}

		TYPE& operator*(void) { return *_native; }
		const TYPE& operator*(void) const { return *_native; }
		TYPE* operator->(void) { return _native; }
		const TYPE* operator->(void) const { return _native; }
	};

} // namespace GEN