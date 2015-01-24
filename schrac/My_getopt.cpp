#include "My_getopt.h"

namespace HydroSchDirac {
#ifdef _OPENMP
	const std::string My_getOpt::DEFINPNAME("input.inp");
	
	int My_getOpt::getOpt(int argc, char * const argv[])
	{
		using namespace boost::program_options;

		options_description opt("�I�v�V����");
		// �����̏������`
		opt.add_options()
			("help,h", "�w���v��\��")
			("inputfile,I", value<std::string>()->default_value(DEFINPNAME), "�C���v�b�g�t�@�C����")
			("openmp,O", value<int>()->implicit_value(defompthread),
			 "OpenMP�Ŏg�p����X���b�h���i0���I�v�V�����ȗ��Ŗ��g�p�A�f�t�H���g�̓v���Z�b�T���j");

		// �����̏����ɏ]���Ď��ۂɎw�肳�ꂽ�R�}���h���C�����������
		variables_map vm;
		try {
			store(parse_command_line(argc, argv, opt), vm);
		} catch (const std::exception & e) {
			std::cerr << e.what()
					  << ". �R�}���h���C���������ُ�ł��B�I�����܂��B" << std::endl;

			return -1;
		}
		notify(vm);

		// �w���v�\���w�肪����ꍇ�A�w���v�\�����ďI��
		if (vm.count("help")) {
			std::cout << opt << std::endl;

			return 1;
		}

		// �C���v�b�g�t�@�C�����w�肪����ꍇ
		if (vm.count("inputfile")) {
			inpname_ = vm["inputfile"].as<std::string>();
		}

		// OpenMP�w�肪����ꍇ
		if (vm.count("openmp")) {
			ompthread_ = vm["openmp"].as<int>();
			if (ompthread_ < 0) {
				std::cerr << "�g�p�X���b�h���̎w�肪�ُ�ł��B"
						  << "�R�}���h���C���������ُ�ł��B�I�����܂��B" << std::endl;

				return -1;
			}
		} else {
			ompthread_ = 0;
		}

		return 0;
	}
#else
	BOOST_STATIC_ASSERT(false);
#endif
}
