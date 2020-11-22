#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab7.3(rec).cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest73
{
	TEST_CLASS(UnitTest73)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int t;
			int rowCount = 0;
			int colCount = 0;

			int** P = new int* [rowCount];
			for (int i = 0; i < rowCount; i++)
				P[i] = new int[colCount];

			t = matrixFirstPlus(P, rowCount, colCount, 0, 0);

			Assert::AreEqual(t, -1);

		}
	};
}
