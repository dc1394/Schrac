/*! \file sdiracnormalize.h
    \brief Scalar Dirac�������������ē���ꂽ�g���֐��𐳋K������N���X�̐錾

    Copyright c 2015 @dc1394 All Rights Reserved.
*/

#ifndef _SDIRACNORMALIZE_H_
#define _SDIRACNORMALIZE_H_

#pragma once

#include "normalize.h"

namespace schrac {
    //! A class.
    /*!
        Scalar Dirac�������������ē���ꂽ�g���֐��𐳋K������N���X
    */
    class SDiracNormalize final : public Normalize<SDiracNormalize> {
        // #region �R���X�g���N�^�E�f�X�g���N�^

    public:
        //! A constructor.
        /*!
            �B��̃R���X�g���N�^
            \param pdiffsolver �����������̃f�[�^�I�u�W�F�N�g
        */
        SDiracNormalize(std::shared_ptr<DiffSolver> const & pdiffsolver) :
            Normalize<SDiracNormalize>(pdiffsolver)
        {
        }

        //! A destructor.
        /*!
        �f�t�H���g�f�X�g���N�^
        */
        ~SDiracNormalize() = default;

        // #endregion �R���X�g���N�^�E�f�X�g���N�^

        // #region �����o�֐�

        //! A public member function.
        /*!
        �g���֐������߂�
        */
        void evaluate();

    private:
        //! A public member function.
        /*!
        �g���֐��𐳋K������
        */
        void normalize();

    public:
        //! A public member function.
        /*!
        ���߂����ʂ�Ԃ�
        */
        Normalize<SDiracNormalize>::mymap getresult() const;

        // #endregion �����o�֐�

        // #region �����o�ϐ�

        //! A private member variable.
        /*!
        �ŗL�֐�
        */
        dvector rf_;

        //! A private member variable.
        /*!
        �p�x������r���������ŗL�֐���large����
        */
        dvector pf_large_;

        //! A private member variable.
        /*!
        �p�x������r���������ŗL�֐���small����
        */
        dvector pf_small_;

        // #endregion �����o�ϐ�

    private:
        // #region �֎~���ꂽ�R���X�g���N�^�E�����o�֐�

        //! A private constructor (deleted).
        /*!
            �f�t�H���g�R���X�g���N�^�i�֎~�j
        */
        SDiracNormalize() = delete;

        //! A private copy constructor (deleted).
        /*!
            �R�s�[�R���X�g���N�^�i�֎~�j
        */
        SDiracNormalize(SDiracNormalize const &) = delete;

        //! A private member function (deleted).
        /*!
        operator=()�̐錾�i�֎~�j
        \param �R�s�[���̃I�u�W�F�N�g�i���g�p�j
        \return �R�s�[���̃I�u�W�F�N�g
        */
        SDiracNormalize & operator=(SDiracNormalize const &) = delete;

        // #endregion �֎~���ꂽ�R���X�g���N�^�E�����o�֐�
    };
}

#endif // _SCHNORMALIZE_H_
