#include "pch.h"
#include <mkl.h>
#include <mkl_spblas.h>
#include <mkl_blas.h>
#include <string.h>
#include <algorithm>
#include <math.h>

#include "cgnr_native.h"
	void cgnr_native::cgnr_for_rect(const int n, const int m, int* csrRowPtr, int* csrColInd, double* csrVal, double* b, double* x, const double threshold, const int iterationMax)
	{
		struct matrix_descr descrJac;
		descrJac.type = SPARSE_MATRIX_TYPE_GENERAL;
		sparse_matrix_t jacobian;
		sparse_status_t status = mkl_sparse_d_create_csr(&jacobian,
			SPARSE_INDEX_BASE_ZERO,
			n,
			m,
			csrRowPtr,
			csrRowPtr + 1,
			csrColInd,
			csrVal);

		mkl_sparse_optimize(jacobian);

		int iteration = 0;
		double* r = new double[n];
		double* jtr0 = new double[m];
		double* jp = new double[n];
		double* jtr1 = new double[m];
		double* pp = new double[m];
		double alpha = 0;
		double beta = 0;

		for (int i = 0; i < n; i++) r[i] = b[i];
		mkl_sparse_d_mv(SPARSE_OPERATION_NON_TRANSPOSE,
			-1.0,
			jacobian,
			descrJac,
			x,
			1.0,
			r);
		double* p = new double[m];
		mkl_sparse_d_mv(SPARSE_OPERATION_TRANSPOSE,
			1.0,
			jacobian,
			descrJac,
			r,
			0.0,
			p);
		int matSize = std::max(n, m);


		const int incX = 1;
		double residual = dnrm2(&n, r, &incX);
		while ((iteration < matSize + 1) && residual > threshold)
		{
			mkl_sparse_d_mv(SPARSE_OPERATION_TRANSPOSE,
				1.0,
				jacobian,
				descrJac,
				r,
				0.0,
				jtr0);
			mkl_sparse_d_mv(SPARSE_OPERATION_NON_TRANSPOSE,
				1.0,
				jacobian,
				descrJac,
				p,
				0.0,
				jp);
			alpha = pow(dnrm2(&m, jtr0, &incX), 2) / pow(dnrm2(&n, jp, &incX), 2);
			daxpy(&n, &alpha, p, &incX, x, &incX);
			for (int i = 0; i < n; i++) r[i] = b[i];
			mkl_sparse_d_mv(SPARSE_OPERATION_NON_TRANSPOSE,
				-1.0,
				jacobian,
				descrJac,
				x,
				1.0,
				r);
			mkl_sparse_d_mv(SPARSE_OPERATION_TRANSPOSE,
				1.0,
				jacobian,
				descrJac,
				r,
				0.0,
				jtr1);
			beta = pow(dnrm2(&m, jtr1, &incX), 2) / pow(dnrm2(&m, jtr0, &incX), 2);
			for (int i = 0; i < m; i++) pp[i] = jtr1[i];
			daxpy(&m, &beta, p, &incX, pp, &incX);
			for (int i = 0; i < m; i++) p[i] = pp[i];
			residual = dnrm2(&n, r, &incX);
			iteration++;
		}
		mkl_sparse_destroy(jacobian);
		delete[] r;
		delete[] jtr0;
		delete[] jp;
		delete[] jtr1;
		delete[] pp;
	}
