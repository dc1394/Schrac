#ifndef _EIGENVALUESEARCH_H_
#define _EIGENVALUESEARCH_H_

#include "Diff.h"
#include "ReadInputFile.h"

namespace schrac {
	class EigenValueSearch final {
        // #region �R���X�g���N�^�E�f�X�g���N�^

    public:

        //! A constructor.
        /*!
            �B��̃R���X�g���N�^
            \param arg �C���v�b�g�t�@�C������TBB���g�p���邩�ǂ�����std::pair
        */
        explicit EigenValueSearch(std::pair<std::string, bool> const & arg);

        //! A destructor.
        /*!
            �������Ȃ��f�X�g���N�^
        */
        ~EigenValueSearch()
        {
        }

        // #endregion �R���X�g���N�^�E�f�X�g���N�^

        // #region �����o�֐�

    public:
        //! A public member function.
        /*!
            �f�[�^�I�u�W�F�N�g�𓾂�
            \return �f�[�^�I�u�W�F�N�g
        */
        const std::shared_ptr<Data> & getpData() const;
        
        //! A public member function.
        /*!
            �����������I�u�W�F�N�g�𓾂�
            \return �����������I�u�W�F�N�g
        */
        const std::shared_ptr<Diff> & getpDiff() const;

        //! A public member function.
        /*!
            �ŗL�l����������
            \return �ŗL�l�������������ǂ���
        */
        bool search();

    private:
        //! A private member function.
        /*!
            �֐�D�̒l��Ԃ�
            \return �֐�D�̒l�i����������������ɉ����Ȃ������Ƃ���boost::none�j
        */
        boost::optional<double> fnc_D();

        //! A private member function (const).
        /*!
            ���݂̃��[�v�����b�Z�[�W�ŕ񍐂���
        */
        void info() const;

        //! A private member function (const).
        /*!
            �ŗL�l�������������Ƃ����b�Z�[�W�ŕ񍐂���
        */
        void info(double E) const;

        //! A private member function (const).
        /*!
            �ŗL�l�������������Ƃ����b�Z�[�W�ŕ񍐂���
            \param b �֐�D�̈���b
            \param fb �֐�D�̈���fb
        */
        void info(double b, double fb) const;

        //! A private member function (const).
        /*!
            ��Ԃ̏��������s��
        */
        void init();

        //! A private member function (const).
        /*!
            ���������������ɂ��ă��b�Z�[�W��\������
        */
        void msg() const;

        //! A private member function.
        /*!
            �ŗL�l�����������ςɌ�������
            \return �ŗL�l�������������ǂ���
        */
        bool rough_search();

        //! A private member function (const).
        /*!
            �\�����镂�������_�̌���ݒ肷��
        */
        void setoutstream() const;

        // #endregion �����o�֐�

        // #region �����o�ϐ�

        //! A private member variable (constant expression).
        /*!
            �G�l���M�[�ŗL�l�T���̍ő�̃��[�v��
        */
		static constexpr auto EVALSEARCHMAX = 1000;

        //! A private member variable (constant expression).
        /*!
            臒l�i��Βl�̑傫�����j
        */
        static constexpr auto HUGE = 1.0E+7;

        //! A private member variable (constant expression).
        /*!
            臒l�i��Βl�̏��������j
        */
		static constexpr auto TINY = 1.0E-30;
        
        //! A private member variable (constant).
        /*!
            ���e�덷
        */
		double eps_;

        //! A private member variable (constant).
        /*!
            ���e�덷�ieps * 10.0�j
        */
        double tol_;

        //! A private member variable.
        /*!
            Brent�@�ɂ�����֐�D�̑傫����
        */
        double Dmax;

        //! A private member variable.
        /*!
            Brent�@�ɂ�����֐�D�̏�������
        */
        double Dmin;

        //! A private member variable.
        /*!
            �O�̃��[�v�ƍ��̃G�l���M�[�ŗL�l�̍�
        */
        double DE;

        //! A private member variable.
        /*!
            �G�l���M�[�ŗL�l
        */
        double E;

        //! A private member variable.
        /*!
            Brent�@�ɂ�����G�l���M�[�ŗL�l�̑傫����
        */
        double Emax;

        //! A private member variable.
        /*!
            Brent�@�ɂ�����G�l���M�[�ŗL�l�̏�������
        */
        double Emin;

        //! A private member variable.
        /*!
            �G�l���M�[�ŗL�l�̑�̂̒l
        */
        double Erough_exact_;

        //! A private member variable.
        /*!
            �֐�D�̌Â��l
        */
        double Dold;
		
        //! A private member variable.
        /*!
            �G�l���M�[�ŗL�l�T���̃��[�v��
        */
        std::int32_t loop_;

        //! A private member variable.
        /*!
            �ŗL�֐��̃m�[�h����v���Ă��邩�ǂ���
        */
        bool noden_;

        //! A private member variable.
        /*!
            �C���v�b�g�t�@�C���̃f�[�^�I�u�W�F�N�g
        */
		std::shared_ptr<Data> pdata_;

        //! A private member variable.
        /*!
            �����������I�u�W�F�N�g
        */
		std::shared_ptr<Diff> pdiff_;

        //! A private member variable.
        /*!
            �����������f�[�^�̃I�u�W�F�N�g
        */
		std::shared_ptr<DiffData> pdiffdata_;
        
        // #endregion �����o�֐�
		
		bool zbrent();

    private:
        // #region �֎~���ꂽ�R���X�g���N�^�E�����o�֐�

        //! A private constructor (deleted).
        /*!
        �f�t�H���g�R���X�g���N�^�i�֎~�j
        */
        EigenValueSearch() = delete;

        //! A private copy constructor (deleted).
        /*!
        �R�s�[�R���X�g���N�^�i�֎~�j
        */
        EigenValueSearch(EigenValueSearch const &) = delete;

        //! A private member function (deleted).
        /*!
        operator=()�̐錾�i�֎~�j
        \param �R�s�[���̃I�u�W�F�N�g�i���g�p�j
        \return �R�s�[���̃I�u�W�F�N�g
        */
        EigenValueSearch & operator=(EigenValueSearch const &) = delete;

        // #endregion �֎~���ꂽ�R���X�g���N�^�E�����o�֐�
	};

    // #region �񃁃��o�֐�

    //! A function.
    /*!
        �Ώۂ̕�������Dirac�������̏ꍇ�ɁA�G�l���M�[�ŗL�l�̉������T�Z����
        \param pdata �f�[�^�I�u�W�F�N�g
        \return ��̂̃G�l���M�[�ŗL�l
    */
    double Eexact_dirac(std::shared_ptr<Data> const & pdata);
    
    //! A function.
    /*!
        �Ώۂ̕�������Sch�������̏ꍇ�ɁA�G�l���M�[�ŗL�l�̉������T�Z����
        \param pdata �f�[�^�I�u�W�F�N�g
        \return ��̂̃G�l���M�[�ŗL�l
    */
    double Eexact_sch(std::shared_ptr<Data> const & pdata);

    //! A function.
    /*!
        �Ώۂ̕�������scalar Dirac�������̏ꍇ�ɁA�G�l���M�[�ŗL�l�̉������T�Z����
        \param pdata �f�[�^�I�u�W�F�N�g
        \return ��̂̃G�l���M�[�ŗL�l
    */
    double Eexact_sdirac(std::shared_ptr<Data> const & pdata);

	template <typename T>
    //! A function (template function).
    /*!
        b�����̒l�̏ꍇ��a�̐�Βl���Ab�����̒l�̏ꍇ��a�̐�Βl��-���������l��Ԃ�
        \param a �Ώۂ̒l
        \param b �����𔻒f���邽�߂̒l
        \return b�����̒l�̏ꍇ��a�̐�Βl�Ab�����̒l�̏ꍇ��a�̐�Βl��-���������l
    */
	T sign(T a, T b)
	{
		return (b >= 0.0) ? std::fabs(a) : - std::fabs(a);
	}

    // #endregion �񃁃��o�֐�
}

#endif // _EIGENVALUESEARCH_H_