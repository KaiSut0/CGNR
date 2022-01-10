#pragma once

	class cgnr_native {
	public:
		void cgnr_for_rect(const int n, const int m, int* csrRowPtr, int* csrColInd, double* csrVal, double* b, double* x, const double threshold, const int iterationMax);
	};
