#include "pch.h"
#include "CGNR.h"
#include "cgnr_native.h"

namespace CGNR {
	CGNRWrapper::CGNRWrapper() { cgnrNative = new cgnr_native(); }
	CGNRWrapper::~CGNRWrapper() { this->!CGNRWrapper(); }
	CGNRWrapper::!CGNRWrapper() { delete this->cgnrNative; }
	cli::array<double>^ CGNRWrapper::CGNRForRect(int n, int m, cli::array<int>^ csrRowPtr, cli::array<int>^ csrColInd, cli::array<double>^ csrVal,
			cli::array<double>^ b, cli::array<double>^ x, double threshold, int iterationMax) {
			pin_ptr<int> csrRowPtr_ptr{ &csrRowPtr[0] };
			pin_ptr<int> csrColInd_ptr{ &csrColInd[0] };
			pin_ptr<double> csrVal_ptr{ &csrVal[0] };
			pin_ptr<double> b_ptr{ &b[0] };
			pin_ptr<double> x_ptr{ &x[0] };

		    cgnrNative->cgnr_for_rect(n, m, csrRowPtr_ptr, csrColInd_ptr, csrVal_ptr, b_ptr, x_ptr, threshold, iterationMax);

			cli::array<double>^ answer = gcnew cli::array<double>(m);
			for (int i = 0; i < m; i++) answer[i] = x[i];

			csrRowPtr_ptr = nullptr;
			csrColInd_ptr = nullptr;
			csrVal_ptr = nullptr;
			b_ptr = nullptr;
			x_ptr = nullptr;

			return answer;
		}
		// TODO: Add your methods for this class here.
}


