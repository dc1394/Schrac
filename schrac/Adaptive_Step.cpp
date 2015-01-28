#include "Adaptive_Step.h"

namespace schrac {
	void Adaptive_Step::RungeKutta()
	{
		long double k1[2], k2[2], k3[2], k4[2];

		for (std::size_t i = 0; i < DiffData::AVECSIZE - 1; i++) {
			k1[0] = pdiffdata_->DX * dL_dx(pdiffdata_->MO[i]);
			k1[1] = pdiffdata_->DX * Diff::dM_dx(pdiffdata_->XV_O[i], pdiffdata_->LO[i],
												 pdiffdata_->MO[i], pdiffdata_);

			k2[0] = pdiffdata_->DX * dL_dx(pdiffdata_->MO[i] + k1[1] / 2.0);
			k2[1] = pdiffdata_->DX * Diff::dM_dx(pdiffdata_->XV_O[i] + pdiffdata_->DX / 2.0,
												 pdiffdata_->LO[i] + k1[0] / 2.0,
												 pdiffdata_->MO[i] + k1[1] / 2.0,
												 pdiffdata_);

			k3[0] = pdiffdata_->DX * dL_dx(pdiffdata_->MO[i] + k2[1] / 2.0);
			k3[1] = pdiffdata_->DX * Diff::dM_dx(pdiffdata_->XV_O[i] + pdiffdata_->DX / 2.0,
												 pdiffdata_->LO[i] + k2[0] / 2.0,
												 pdiffdata_->MO[i] + k2[1] / 2.0,
												 pdiffdata_);

			k4[0] = pdiffdata_->DX * dL_dx(pdiffdata_->MO[i] + k3[1]);
			k4[1] = pdiffdata_->DX * Diff::dM_dx(pdiffdata_->XV_O[i] + pdiffdata_->DX,
												 pdiffdata_->LO[i] + k3[0],
												 pdiffdata_->MO[i] + k3[1],
												 pdiffdata_);
		
			pdiffdata_->LO[i + 1] = pdiffdata_->LO[i] + 
									(k1[0] + 2.0 * k2[0] + 2.0 * k3[0] + k4[0]) / 6.0;
			pdiffdata_->MO[i + 1] = pdiffdata_->MO[i] +
									(k1[1] + 2.0 * k2[1] + 2.0 * k3[1] + k4[1]) / 6.0;
		}
	}

	bool Adaptive_Step::rkqc(long double htry,
							 const AdapStepHelper::darray & yscal,
							 const shared_ptr<AdapStepHelper> & pasa) const
	{
		AdapStepHelper::darray yold, dyold, ytemp;
		long double xold = pasa->xx_;						// �����l�̊i�[

		for (std::size_t i = 0; i < AdapStepHelper::NVAR; i++) {
			yold[i] = pasa->y_[i];
			dyold[i] = pasa->dydx_[i];
		}

		long double h = htry;								// ���ݕ��������̉��̒l�ɐݒ�

		while (true) {
			const long double hh = 0.5 * h;					// 2�̔��X�e�b�v�����

			rk4(xold, hh, yold, dyold, ytemp);

			pasa->xx_ = xold + hh;
			derivs(pasa->xx_, ytemp, pasa->dydx_);

			rk4(pasa->xx_, hh, ytemp, pasa->dydx_, pasa->y_);

			pasa->xx_ = xold + h;

			if (std::fabs(pasa->xx_ - xold) <= pasa->TINY) {
				std::cerr << "Step size too small in method rkqc" << std::endl;
				return false;
			}

			rk4(xold, h, yold, dyold, ytemp);				// �S�X�e�b�v�����
			long double errmax = 0.0;						// ���x�̌v�Z

			for (std::size_t i = 0; i < AdapStepHelper::NVAR; i++) {
				ytemp[i] = pasa->y_[i] - ytemp[i];			// �����ŕ]���덷��ytemp�ɓ������
				const long double temp = std::fabs(ytemp[i] / yscal[i]);

				if (errmax < temp)
					errmax = temp;
			}

			errmax /= pasa->EPS;							// ���e�덷�ɑ΂��ăX�P�[��

			if (errmax <= 1.0) {							// �X�e�b�v�����܂��������̂ŁA���̌덷���v�Z
				pasa->hdid_ = h;
				pasa->hnext_ = 
					(errmax > AdapStepHelper::ERRCON ?
					AdapStepHelper::SAFETY * h * std::exp(
					AdapStepHelper::PGROW * std::log(errmax)) : 4.0 * h);
				break;
			}

			h = AdapStepHelper::SAFETY * h *
				std::exp(AdapStepHelper::PSHRNK * std::log(errmax));// �ł��؂�덷���傫������Ƃ��A���ݕ�������
		}

		for (std::size_t i = 0; i < AdapStepHelper::NVAR; i++)
			pasa->y_[i] += ytemp[i] * AdapStepHelper::FCOR;			// 5���̑ł��؂�덷�̌�n��

		return true;
	}

	void Adaptive_Step::rk4(long double x, long double h,
							 const AdapStepHelper::darray & y,
							 const AdapStepHelper::darray & dydx,
							 AdapStepHelper::darray & yout) const
	{
		AdapStepHelper::darray yt, dyt, dym;
		const long double hh = h * 0.5;
		const long double h6 = h / 6.0;
		const long double xh = x + hh;

		for (std::size_t i = 0; i < AdapStepHelper::NVAR; i++)
			yt[i] = y[i] + hh * dydx[i];					// First step

		derivs(xh, yt, dyt);								// Second step

		for (std::size_t i = 0; i < AdapStepHelper::NVAR; i++)
			yt[i] = y[i] + hh * dyt[i];

		derivs(xh, yt, dym);								// Third step

		for (std::size_t i = 0; i < AdapStepHelper::NVAR; i++) {
			yt[i] = y[i] + h * dym[i];
			dym[i] += dyt[i];
		}

		derivs(x + h, yt, dyt);								// Fourth step

		for (std::size_t i = 0; i < AdapStepHelper::NVAR; i++)	// �d�݂����đ��a�����
			yout[i] = y[i] + h6 * (dydx[i] + dyt[i] + 2.0 * dym[i]);
	}

	bool Adaptive_Step::solve_diff_equ_O()
	{
		// �ŏ��̎O���̂ݒʏ�̃����Q�E�N�b�^�@�Ōv�Z
		RungeKutta();
		boost::mpl::int_<AdapStepHelper::OO> o;
		const shared_ptr<AdapStepHelper> pasa(
			make_shared<AdapStepHelper>(pdiffdata_, o));	

		return odeint(pasa);
	}

	bool Adaptive_Step::solve_diff_equ_I()
	{
		boost::mpl::int_<AdapStepHelper::INFINITY> inf;
		const shared_ptr<AdapStepHelper> pasa(
			make_shared<AdapStepHelper>(pdiffdata_, inf));	

		return odeint(pasa);
	}

	bool Adaptive_Step::solve_diff_equ()
	{
#ifdef _OPENMP
		if (pdata_->ompthread_) {
			volatile bool bRet = true;
			bool bRet2 = false;

			#pragma omp parallel sections
			{
				#pragma omp section
				{
					bRet = solve_diff_equ_O();
				}

				#pragma omp section
				{
					if (bRet)
						bRet2 = solve_diff_equ_I();
				}
			}

			return (bRet && bRet2);
		} else {
			return (solve_diff_equ_O() && solve_diff_equ_I());
		}
#else
		BOOST_STAIC_ASSERT(false);

		return false;
#endif
	}

}
