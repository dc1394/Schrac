#ifndef _READINPUTFILE_H_
#define _READINPUTFILE_H_

#include "ci_string.h"
#include "data.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>

namespace schrac {
    //! A class.
    /*!
        �C���v�b�g�t�@�C����ǂݍ��݁AData�N���X�̃I�u�W�F�N�g�Ɋi�[����N���X    
    */
	class ReadInputFile final {
        // #region �^�G�C���A�X

        using strvec = std::vector<ci_string>;

        // #endregion �^�G�C���A�X

        // #region �R���X�g���N�^�E�f�X�g���N�^

    public:
        //! A constructor.
        /*!
            �B��̃R���X�g���N�^
        */
        ReadInputFile(std::pair<std::string, bool> const & arg);

        //! A destructor.
        /*!
        �������Ȃ��f�X�g���N�^
        */
        ~ReadInputFile()
        {
        }

        // #region �R���X�g���N�^�E�f�X�g���N�^
        
        // #region �����o�֐�

    public:
        //! A public member function.
        /*!
            �ǂݍ��񂾃f�[�^��Ԃ�
            \return �ǂݍ��񂾃f�[�^
        */
        std::shared_ptr<Data> && getpData();
        
        //! A public member function.
        /*!
            �t�@�C����ǂݍ���
            \return �ǂݍ��݂������������ǂ���
        */
        void readFile();

    private:

        //! A private member function (const).
        /*!
            �G���[��\������
            \param s �G���[�̃g�[�N��
            \return �ǂݍ��݂������������ǂ���
        */
        void errMsg(ci_string const & s) const;

        //! A private member function (const).
        /*!
            �G���[��\������
            \param line �G���[�̂���s
            \param s1 �G���[�̃g�[�N��
            \param s2 �G���[�̃g�[�N��2
        */
        void errMsg(std::int32_t line, ci_string const & s, ci_string const & s2) const;

        //! A private member function (const).
        /*!
            ��͑Ώۂ̕�������g�[�N���ɕ�������
            \param article ��͑Ώۂ̕�����
            \return �֐��������������ǂ����ƁA�g�[�N����std::pair
        */
        std::pair<std::int32_t, boost::optional<ReadInputFile::strvec>> getToken(ci_string const & article);

        //! A private member function.
        /*!
            ���q����ǂݍ���
            \return �ǂݍ��݂������������ǂ���
        */
        bool readAtom();

        //! A private member function.
        /*!
            ���������͂��āA�f�[�^�Ƃ��ēǂݍ���ŕԂ�
            \param article ��͑Ώۂ̕�����
            \return �ǂ݂��񂾕�����f�[�^
        */
        boost::optional<ci_string> readData(ci_string const &);
        
        //! A private member function.
        /*!
            �f�[�^��ǂݍ���
            \param article ��͑Ώۂ̕�����
            \param def �f�t�H���g�̕�����
            \return �ǂ݂��񂾕�����
        */
        boost::optional<ci_string> readData(ci_string const & article, ci_string const & def);
        
        //! A private member function (template function).
        /*!
            �f�[�^��ǂݍ���
            \param article ��͑Ώۂ̕�����
            \param def_val �f�t�H���g�l
            \return �ǂ݂��񂾕�����
        */
        template <typename T>
        boost::optional<T> readData(ci_string const & article, T const & def_val);
        
        //! A private member function.
        /*!
            �f�[�^��ǂݍ���
            \param article ��͑Ώۂ̕�����
            \return �ǂ݂��񂾕�����i�ǂݍ��݂Ɏ��s�����Ȃ�boost::none�j
        */
        boost::optional<ci_string> readDataAuto(ci_string const & article);

        //! A private member function.
        /*!
            ���e�덷��ǂݍ���
            \return �ǂݍ��݂������������ǂ���
        */
        bool readEps();

        //! A private member function.
        /*!
            �Ώۂ̕�������ǂݍ���
            \return �ǂݍ��݂������������ǂ���
        */
        bool readEq();

        //! A private member function.
        /*!
            ���b�V���̐ݒ��ǂݍ���
            \return �ǂݍ��݂������������ǂ���
        */
        bool readGrid();

        //! A private member function.
        /*!
            �ŗL�l�̌������n�߂�l��ǂݍ���
            \return �ǂݍ��݂������������ǂ���
        */
        bool readLowerE();

        //! A private member function.
        /*!
            ���q�ԍ��̒l��ǂݍ���
            \return �ǂݍ��݂������������ǂ���
        */
        bool readNumofp();

        //! A private member function.
        /*!
            �����������̉�@��ǂݍ���
            \return �ǂݍ��݂������������ǂ���
        */
        bool readType();

        //! A private member function.
        /*!
            �}�b�`���O�|�C���g��ǂݍ���
            \return �ǂݍ��݂������������ǂ���
        */
        bool readRatio();

        // #endregion �����o�֐�

        // #region �����o�ϐ�

        //! A private member variable (constant expression).
        /*!
            �o�b�t�@�T�C�Y
        */
        static constexpr std::streamsize BUFSIZE = 1024;

        //! A private member variable (constant).
        /*!
            �uchemical.symbol�v�̕�����
        */
        static const ci_string CHEMICAL_SYMBOL;

        //! A private member variable (constant).
        /*!
            �f�t�H���g�́ueq.type�v�̕�����
        */
        static const ci_string EQ_TYPE_DEFAULT;

        //! A private member variable (constant).
        /*!
            �ueq.type�v�̕�����
        */
        static const ci_string EQ_TYPE;

        //! A private member variable (constant).
        /*!
            �������̎�ނ̕�����̔z��
        */
        static const std::array<ci_string, 4> EQ_TYPE_ARRAY;

        //! A private member variable (constant).
        /*!
            �uorbital�v�̕�����
        */
        static const ci_string ORBITAL;

        //! A private member variable (constant).
        /*!
            �����������̐��l��@�̕�����̔z��
        */
        static const std::array<ci_string, 4> SOLVER_TYPE_ARRAY;

        //! A private member variable (constant).
        /*!
            �f�t�H���g�̔����������̐��l��@
        */
        static const ci_string SOLVER_TYPE_DEFAULT;

        //! A private member variable (constant).
        /*!
            �uspin_orbital�v�̕�����
        */
        static const ci_string SPIN_ORBITAL;

        //! A private member variable.
        /*!
            �t�@�C���ǂݍ��ݗp�̃X�g���[��
        */
        std::ifstream ifs_;
        
        //! A private member variable.
        /*!
            ���݂̍s��
        */
	    std::size_t lineindex_;

        //! A private member variable.
        /*!
            �C���v�b�g�t�@�C������ǂݍ��񂾃f�[�^
        */
		std::shared_ptr<Data> pdata_;
        	
        // #endregion �����o�ϐ�

        // #region �֎~���ꂽ�R���X�g���N�^�E�����o�֐�

        //! A private constructor (deleted).
        /*!
            �f�t�H���g�R���X�g���N�^�i�֎~�j
        */
        ReadInputFile() = delete;

        //! A private copy constructor (deleted).
        /*!
            �R�s�[�R���X�g���N�^�i�֎~�j
        */
        ReadInputFile(ReadInputFile const &) = delete;

        //! A private member function (deleted).
        /*!
            operator=()�̐錾�i�֎~�j
            \param �R�s�[���̃I�u�W�F�N�g�i���g�p�j
            \return �R�s�[���̃I�u�W�F�N�g
        */
        ReadInputFile & operator=(ReadInputFile const &) = delete;

        // #endregion �֎~���ꂽ�R���X�g���N�^�E�����o�֐�
	};

    template <typename T>
    boost::optional<T> ReadInputFile::readData(ci_string const & article, T const & def_val)
    {
        // �O���b�h��ǂݍ���
        for (; true; lineindex_++) {
            auto const ret = getToken(article);

            switch (std::get<0>(ret))
            {
            case -1:
                return nullptr;
                break;

            case 0:
            {
                auto const tokens = *(std::get<1>(ret));
                auto itr(++tokens.begin());

                lineindex_++;
                // �ǂݍ��񂾃g�[�N���̐����͂���
                switch (tokens.size()) {
                case 1:
                    // �f�t�H���g�l��Ԃ�
                    return boost::optional<T>(def_val);
                    break;

                case 2:
                    if (*(++itr) == "DEFAULT") {
                        // �f�t�H���g�l��Ԃ�
                        return boost::optional<T>(def_val);
                    }
                    else {
                        try {
                            return boost::optional<T>(boost::lexical_cast<T>(itr->c_str()));
                        }
                        catch (boost::bad_lexical_cast const &) {
                            errMsg(lineindex_ - 1, article, *itr);
                            return boost::none;
                        }
                    }

                default:
                {
                    auto val = *itr;

                    if (val == "DEFAULT" || val[0] == '#') {
                        return boost::optional<T>(def_val);
                    }
                    else if ((*(++itr))[0] != '#') {
                        errMsg(lineindex_ - 1, article, *itr);
                        return boost::none;
                    }

                    try {
                        return boost::optional<T>(boost::lexical_cast<T>(val.c_str()));
                    }
                    catch (boost::bad_lexical_cast const &) {
                        errMsg(lineindex_ - 1, article, val);
                        return boost::none;
                    }
                    break;
                }
                }
            }
            break;

            case 1:
                break;

            default:
                BOOST_ASSERT(!"��������������!");
                break;
            }
        }
    }
}

#endif	// _READINPUTFILE_H_
