/*
solution:	raytracing
project:	system
file:		thread.h
author:		cj
*/

#pragma once

#include <Windows.h>
#include "../common/uncopyable.h"

namespace SYS {

	class Thread : public GEN::Uncopyable {
	private:
		HANDLE _handle;
	public:
		virtual ~Thread(void);

		virtual DWORD Run(void) = 0;

		void Start(void);
		void Kill(void);
		void Join(void) const;
	};

} // namespace SYS