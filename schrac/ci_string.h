#ifndef _CI_STRING_H_
#define _CI_STRING_H_

#pragma once

#include <string>
#include <cctype>

namespace schrac {
    //! A class.
    /*!
        �啶������������ʂ��Ȃ�������N���X
    */
	struct ci_char_traits : public std::char_traits<char> {
        // #region static�����o�֐�

        //! A public static member function.
        /*!
            2�̃o�b�t�@�[ (�啶���Ə���������ʂ��Ȃ�) ���r����
            \param s1 ��ڂ̕�����
            \param s2 ��ڂ̕�����
            \param ������̒���
            \return std::strcmp�̖߂�l�Ɠ��l
        */
        static int compare(char const * s1, char const * s2, std::size_t n);

        //! A public static member function.
        /*!
            �����ŗ^����ꂽ��̕��������������ǂ����𔻕ʂ���Ǝ���
            \param lhs ��ڂ̕���
            \param rhs ��ڂ̕���
            \return ��̕��������������ǂ���
        */
		static bool eq(char lhs, char rhs) {
			return std::toupper(lhs) == std::toupper(rhs);
		}
		
        //! A public static member function.
        /*!
            �����ŗ^����ꂽ��̕����̑召�֌W�𔻕ʂ���Ǝ���
            \param lhs ��ڂ̕���
            \param rhs ��ڂ̕���
            \return ��̕����̑召�֌W
        */
        static bool lt(char lhs, char rhs) {
			return std::toupper(lhs) < std::toupper(rhs);
		}

        // #endregion static�����o�֐�
	};

    // #region �^�G�C���A�X

    using ci_string = std::basic_string < char, ci_char_traits >;

    // #endregion �^�G�C���A�X

    // #region �񃁃��o�֐�

#ifndef _MSC_VER
    //! A function.
    /*!
        2�̃o�b�t�@�[ (�啶���Ə���������ʂ��Ȃ�) ���r����
        \param s1 ��ڂ̕�����
        \param s2 ��ڂ̕�����
        \param ������̒���
        \return std::strcmp�̖߂�l�Ɠ��l
    */
    int memIcmp(char const * s1, char const * s2, std::size_t n);
#endif

    //! A function.
    /*!
        ci_string�ɑ΂���operator<<�̐錾
        \param os �Ώۂ�std::ostream
        \param s �Ώۂ́i�啶������������ʂ��Ȃ��j������
        \return ���ʂ̎Q��
    */
    std::ostream & operator<<(std::ostream & os, ci_string const & s);

    // #endregion �񃁃��o�֐�
}

#endif	// _CISTRING_H_
