#include "ReadInpFile.h"

int main(int argc, char *argv[])
{
	if (argc != 2) {
		std::cerr << "�R�}���h���C���������ُ�ł�" << std::endl;

		return EXIT_FAILURE;
	}

	try {
		nummeth::ReadInpFile rif(argv[1]);
	} catch (std::domain_error & e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
