#include "ci_string.h"
#include <cstring>

#ifndef _MSC_VER
    #include <algorithm>    // std::mismatch
#endif

namespace schrac {
    //! A public static member function.
    /*!
        2�̃o�b�t�@�[ (�啶���Ə���������ʂ��Ȃ�) ���r����֐��̎���
        \param s1 ��ڂ̕�����
        \param s2 ��ڂ̕�����
        \param ������̒���
        \return std::strcmp�̖߂�l�Ɠ��l
    */
	int ci_char_traits::compare(char const * s1, char const * s2, std::size_t n)
	{
#ifdef _MSC_VER
		return _memicmp(s1, s2, n);
#else
		return memIcmp(s1, s2, n);
#endif
	}

#ifndef _MSC_VER
    //! A function.
    /*!
        2�̃o�b�t�@�[ (�啶���Ə���������ʂ��Ȃ�) ���r����֐��̎���
        \param s1 ��ڂ̕�����
        \param s2 ��ڂ̕�����
        \param ������̒���
        \return std::strcmp�̖߂�l�Ɠ��l
    */
    int memIcmp(char const * s1, char const * s2, size_t n)
    {
        typedef std::pair<char const*, char const*> ci_diff_pair;

        auto p = std::mismatch(p1, p1 + n, p2, [](char left, char right) {
            return std::toupper(left) == std::toupper(right);
        });

        // both characters match exactly (case insensitive)
        if (p.first == p1 + n && p.second == p2 + n) {
            return 0;
        }

        return *(p.first) < *(p.second) ? -1 : 1;
    }
#endif

    //! A function.
    /*!
        ci_string�ɑ΂���operator<<�̎���
        \param os �Ώۂ�std::ostream
        \param s �Ώۂ́i�啶������������ʂ��Ȃ��j������
        \return ���ʂ̎Q��
    */
	std::ostream & operator<<(std::ostream & os, const ci_string & s)
	{
		os << s.c_str();

		return os;
	}
}
