#ifndef _DIFFDATA_H_
#define _DIFFDATA_H_

#pragma once

#include "data.h"
#include <memory>
#include <vector>

namespace schrac {
    using dvectpr = std::vector < double > ;

	struct DiffData {
        // #region �R���X�g���N�^�E�f�X�g���N�^

        //! A constructor.
        /*!
            �B��̃R���X�g���N�^
            \param E �G�l���M�[�ŗL�l 
            \param pdata �f�[�^�I�u�W�F�N�g
            \param TINY ��Βl������������臒l
        */
        DiffData(double E, std::shared_ptr<Data> const & pdata, double TINY);

        //! A destructor.
        /*!
            �������Ȃ��f�X�g���N�^
        */
        ~DiffData()
        {
        }

        // #endregion �R���X�g���N�^�E�f�X�g���N�^

        // #region �����o�ϐ�

    private:
        //!  A private static member variable (constant expression).
        /*!
            �s��A�̃T�C�Y
        */
		static std::size_t constexpr AVECSIZE = 3;
		
        //!  A private static member variable (constant expression).
        /*!
            �s��B�̃T�C�Y
        */
        static std::size_t constexpr BVECSIZE = 5;
        
        //!  A private member variable (constant).
        /*!
            �߂̐�
        */
        std::int32_t const node_;

        //!  A private static member variable (constant expression).
        /*!
            �s��B�̃T�C�Y
        */
        double E_;

		const std::shared_ptr<const Data> pdata_;

		
		int thisnode;

		std::size_t MP_O;
		std::size_t MP_I;
		int OSIZE;
		int ISIZE;

		const double TINY_;

		double Z;
		double DX;
		


		array<double, AVECSIZE> V_A;
		array<double, BVECSIZE> V_B;

		ldvector XV_I;
		ldvector XV_O;
		ldvector RV_I;
		ldvector RV_O;
		ldvector VP_I;
		ldvector VP_O;
		ldvector LO;
		ldvector MO;
		ldvector LI;
		ldvector MI;

		
	};

    double fnc_V(double x);
    void node_count(int i, const ldvector & WF);

	inline double DiffData::fnc_V(double x) const
	{
		return - Z * std::exp(- x);
	}

	inline void DiffData::node_count(int i, const ldvector & WF)
	{
		if (WF[i] * WF[i - 1] < 0.0)
			thisnode++;
	}
}

#endif	// _DIFFDATA_H_
