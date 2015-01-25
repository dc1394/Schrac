#include "my_getopt.h"
//#include "WF_Save.h"
//#include "ChkPoint.h"

/*namespace HydroSchDirac {
	void showomp(const HydroSchDirac::My_getOpt & go);
}*/

int main(int argc, char * argv[])
{
}
/*#if (_MSC_VER >= 1600)
	using std::tie;
#else
	using boost::tie;
#endif

	CheckPoint::ChkPoint cp("�����J�n", __LINE__);
	
	HydroSchDirac::My_getOpt go;
	switch (go.getOpt(argc, argv)) {
		case -1:
			return EXIT_FAILURE;
		break;

		case 1:
			return EXIT_SUCCESS;
		break;

		case 0:
		break;

		default:
			BOOST_ASSERT(!"���������������I�I");
		break;
	}

	cp.checkpoint("�R�}���h���C���I�v�V������͏���", __LINE__);

	boost::optional<HydroSchDirac::EigenValueSearch> pevs;

	try {
		pevs = boost::in_place(go.getpData());
	} catch (const std::runtime_error & e) {
		std::cerr << e.what() << std::endl;

		return EXIT_FAILURE;
	}

	cp.checkpoint("���̓t�@�C���ǂݍ��ݏ���", __LINE__);

	if (!pevs->search()) {
		std::cerr << "�ŗL�l��������܂���ł����B�I�����܂��B" << std::endl;
		return EXIT_FAILURE;
	}
	
	cp.checkpoint("�����������̐ϕ��ƌŗL�l�T������", __LINE__);

	HydroSchDirac::WF_Normalize wfn(pevs->getpDiff());

	cp.checkpoint("�g���֐��̃R�s�[����", __LINE__);

	wfn();
	
	cp.checkpoint("�g���֐��̐��K������", __LINE__);
	
	HydroSchDirac::WF_Save wfs;
	if (!wfs(pevs->getpData(), wfn.getptup())) {
		std::cerr << "�t�@�C�����쐬�ł��܂���ł����B�I�����܂��B" << std::endl;
		return EXIT_FAILURE;
	}
	cp.checkpoint("�t�@�C���������ݏ���", __LINE__);

	pevs = boost::none;

	cp.checkpoint("�I������", __LINE__);

	std::cout << "����ɏI�����܂����B" << std::endl << std::endl;
	HydroSchDirac::showomp(go);

	cp.checkpoint_print();
	long double cpu, real;
	tie(cpu, real) = cp.totalpassageoftime();

	std::cout << "���������ԁF CPU:" << boost::format("%.4f") % cpu
			  << " (msec), ������:" << boost::format("%.4f") % real
			  << " (msec), ���񉻌���:" << boost::format("%.4f") % (cpu / real)
			  << "�i�{�j" << std::endl << std::endl;

#if defined(_WIN32) || defined(_WIN64)
	CheckPoint::usedmem();
#endif

	std::cout << "�I������ɂ͉����L�[�������Ă�������..." << std::endl;

#if defined(_WIN32) || defined(_WIN64)
	::_getch();
#else
	std::getchar();
#endif

	return EXIT_SUCCESS;
}

namespace HydroSchDirac {
	void showomp(const HydroSchDirac::My_getOpt & go)
	{
		std::cout << "OpenMP: ";

		const int nthread = go.getOmpThread();
		if (nthread) {
			std::cout << "�g�p" << std::endl;
			std::cout << "�g�p�X���b�h��: " << nthread
					  << '\n' << std::endl;
		} else {
			std::cout << "���g�p\n" << std::endl;
		}
	}
}*/
