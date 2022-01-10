#pragma once

#include "cgnr_native.h"

using namespace System;
using namespace System::Runtime::InteropServices;


namespace CGNR {
	public ref class CGNRWrapper {
	public:
		CGNRWrapper();
		~CGNRWrapper();
		!CGNRWrapper();
		cli::array<double>^ CGNRForRect(int n, int m, cli::array<int>^ csrRowPtr, cli::array<int>^ csrColInd, cli::array<double>^ csrVal,
			cli::array<double>^ b, cli::array<double>^ x, double threshold, int iterationMax);

	internal:
		cgnr_native* cgnrNative;
	};
}

// add headers that you want to pre-compile here

