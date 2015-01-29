#include "Bulirsch_Stoer.h"

namespace schrac {
	const double Bulirsch_Stoer::SHRINK = 0.95;
	const double Bulirsch_Stoer::GROW = 1.2;
	const array<const int, AdapStepHelper::IMAX> Bulirsch_Stoer::nseq = {2, 4, 6, 8, 12, 16, 24, 32, 48, 64, 96};

	bool Bulirsch_Stoer::odeint(const shared_ptr<AdapStepHelper> & pasa) const
	{
		AdapStepHelper::darray yscal;
		double h = (pasa->x1_ < pasa->x2_) ? std::fabs(pasa->H1) : - std::fabs(pasa->H1);
		int cnt = 0;

		for (unsigned int nstp = 0; nstp < pasa->MAXSTEP; nstp++) {					// Take at most MAXSTP steps
			derivs(pasa->xx_, pasa->y_, pasa->dydx_);

			for (std::size_t i = 0; i < AdapStepHelper::NVAR; i++)					// ���x���Ď����邽�߂̃X�P�[�����O
				yscal[i] = std::fabs(pasa->y_[i]) + std::fabs(pasa->dydx_[i] * h) + pasa->TINY;

			if (std::fabs(pasa->xx_ - (*pasa->xp_)[pasa->i_]) < pasa->TINY) {
				for (std::size_t i = 0; i < AdapStepHelper::NVAR; i++)
					(*pasa->yp_[i])[pasa->i_] = pasa->y_[i];
				
				pdiffdata_->node_count(pasa->i_, *pasa->yp_[0]);					// �m�[�h���`�F�b�N
				pasa->i_++;
			}

			if ((pasa->x1_ < pasa->x2_) && (pasa->xx_ + h) > (*pasa->xp_)[pasa->i_] ||
				(pasa->x1_ > pasa->x2_) && (pasa->xx_ + h) < (*pasa->xp_)[pasa->i_]) {
				h = (*pasa->xp_)[pasa->i_] - pasa->xx_;
			}

			const double xold = pasa->xx_;
			const AdapStepHelper::darray yold = pasa->y_;
			if (cnt || !bsstep(h, yscal, pasa)) {
				pasa->xx_ = xold;
				pasa->y_ = yold;
				cnt++;

				if (cnt == THRESHOLD)
					cnt = 0;

				if (!rkqc(0.75 * h, yscal, pasa))
					return false;
			}

			if (std::fabs(pasa->xx_ - (*pasa->xp_)[pasa->MP]) <
					pasa->TINY && pasa->i_ == pasa->MP) {	// �����������H
				for (std::size_t i = 0; i < AdapStepHelper::NVAR; i++)
					(*pasa->yp_[i])[pasa->i_] = pasa->y_[i];

				return true;														// ����I��
			}

			if (std::fabs(pasa->hnext_) <= pasa->HMIN) {
				std::cerr << "Step size too small in odeint" << std::endl;
				return false;
			}

			h = pasa->hnext_;
		}

		std::cerr << "Too many steps in routine odeint" << std::endl;
		return false;
	}

	bool Bulirsch_Stoer::bsstep(double htry, const AdapStepHelper::darray & yscal,
								const shared_ptr<AdapStepHelper> & pasa) const
	{
		AdapStepHelper::darray ynew, dynew, yseq, yerr;
		
		// �����l�̊i�[
		for (std::size_t i = 0; i < AdapStepHelper::NVAR; i++) {
			ynew[i] = pasa->y_[i];
			dynew[i] = pasa->dydx_[i];
		}

		double xnew = pasa->xx_;

		while (true) {
			for (std::size_t i = 0; i < AdapStepHelper::IMAX; i++) {				// �C�����_�̌n����v�Z
				mmid(xnew, htry, nseq[i], ynew, dynew, yseq, pasa);
				double xest = sqr<double>
									(htry / static_cast<const double>(nseq[i]));	// �덷�̋�������Ȃ̂œ�悷��
				rzextr(i, xest, yseq, yerr, pasa);									// �L���֐���O���s

				if (i > 2) {														// �����̒i�K�ł����Ƃ��炵�������������Ȃ����߂̗\�h
					double errmax = 0.0;

					for (std::size_t j = 0; j < AdapStepHelper::NVAR; j++) {		// �Ǐ��ł��؂�덷�̃`�F�b�N
						if (errmax < std::fabs(yerr[j] / yscal[j]))
							errmax = std::fabs(yerr[j] / yscal[j]);
					}

					errmax /= pasa->EPS;											// ���e�덷�ɑ΂���X�P�[��

					if (errmax < 1.0) {												// �X�e�b�v����������
						pasa->xx_ += htry;
						pasa->hdid_ = htry;

						if (i == AdapStepHelper::NUSE - 1) {
							pasa->hnext_ = htry * SHRINK;
						} else if (i == AdapStepHelper::NUSE - 2) {
							pasa->hnext_ = htry * GROW;
						} else {
							pasa->hnext_ = (htry * static_cast<const double>(nseq[AdapStepHelper::NUSE - 2])) /
										   static_cast<const double>(nseq[i]);
						}

						return true;
					}
				}
			}

			// �����܂ŗ����Ƃ��̓X�e�b�v�����܂������Ȃ������ƌ�������
			// ���ݕ������������Ă�����x���݂�
			htry *= 0.25;

			const int lim = div2(AdapStepHelper::IMAX - AdapStepHelper::NUSE);
			for (int i = 0; i < lim; i++)
				htry *= 0.5;

			if (std::fabs(htry) < pasa->TINY)
				return false;
		}
	}

	void Bulirsch_Stoer::rzextr(std::size_t iest, double xest,
								const AdapStepHelper::darray & yest,
								AdapStepHelper::darray & dy,
								const shared_ptr<AdapStepHelper> & pasa) const
	{
		array<double, AdapStepHelper::NUSE> fx;

		pasa->x_[iest] = xest;												// ���݂̓Ɨ��ϐ���ۑ�
		if (!iest) {
			for (std::size_t j = 0; j < AdapStepHelper::NVAR; j++)
				pasa->y_[j] = pasa->d_[j][0] = dy[j] = yest[j];
		} else {
			const std::size_t m1 = (iest + 1 < AdapStepHelper::NUSE) ?
				iest + 1 : AdapStepHelper::NUSE;							// �g���v�Z���ʂ͂�������NUSE��
			for (std::size_t k = 1; k < m1; k++)							// ���̑Ίp��������ۑ�
				fx[k] = pasa->x_[iest - k] / xest;

			for (std::size_t j = 0; j < AdapStepHelper::NVAR; j++) {
				double v = pasa->d_[j][0];
				double yy = yest[j];
				double c = yest[j];
				pasa->d_[j][0] = yest[j];
				double ddy = 0.0;

				for (std::size_t k = 1; k < m1; k++) {
					const double b1 = fx[k] * v;
					double b = b1 - c;

					if (std::fabs(b) > pasa->TINY) {
						b = (c - v) / b;
						ddy = c * b;
						c = b1 * b;
					} else {												// 0�Ŋ���̂������
						ddy = v;
					}

					if (k != m1 - 1)
						v = pasa->d_[j][k];

					pasa->d_[j][k] = ddy;
					yy += ddy;
				}

				dy[j] = ddy;
				pasa->y_[j] = yy;
			}
		}
	}

	void Bulirsch_Stoer::mmid(double xs, double htot,
							  int nstep,
							  AdapStepHelper::darray & y,
							  AdapStepHelper::darray & dydx,
							  AdapStepHelper::darray & yout,
							  const shared_ptr<AdapStepHelper> & pasa) const
	{
		AdapStepHelper::darray ym, yn;
		const double h = htot / static_cast<const double>(nstep);	// ���̃��\�b�h�ł̍��ݕ�

		ym[0] = y[0];
		ym[1] = y[1];
		for (std::size_t i = 0; i < AdapStepHelper::NVAR; i++) {
			yn[i] = y[i] + h * dydx[i];										// ���X�e�b�v
		}

		double x = xs + h;
		derivs(x, yn, yout);												// �����̈ꎞ�I�Ȋi�[�Ƃ���yout���g��
		const double h2 = 2.0 * h;

		for (int n = 2; n <= nstep; n++) {									// ��ʂ̃X�e�b�v
			for (std::size_t i = 0; i < AdapStepHelper::NVAR; i++) {
				const double swap = ym[i] + h2 * yout[i];
				ym[i] = yn[i];
				yn[i] = swap;
			}

			x += h;
			derivs(x, yn, yout);
		}

		for (std::size_t i = 0; i < AdapStepHelper::NVAR; i++)				// �Ō�̃X�e�b�v
			yout[i] = 0.5 * (ym[i] + yn[i] + h * yout[i]);
	}
}
