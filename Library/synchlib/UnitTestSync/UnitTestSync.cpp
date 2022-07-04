#include "pch.h"
#include "CppUnitTest.h"
#include "../synchlib/synchlib.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestSync
{
	TEST_CLASS(UnitTestSync)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			synchlib::synch_CreateSharedMemory();
		}
	};
}
