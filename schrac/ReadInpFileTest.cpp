#include <conio.h>
#include <cstdlib>
#include "readinpfile.h"

int main(int argc, char *argv[])
{
	if (argc != 2) {
		std::cerr << "�R�}���h���C���������ُ�ł�" << std::endl;

		return EXIT_FAILURE;
	}

	try {
		schrac::ReadInpFile rif(std::make_pair(argv[1], false));
        rif.readFile();
	} catch (std::runtime_error const & e) {
		std::cerr << e.what() << std::endl;
        
        std::cout << "�I������ɂ͉����L�[�������Ă�������...";
        ::_getch();
        return EXIT_FAILURE;
	}

    std::cout << "�I������ɂ͉����L�[�������Ă�������...";
    ::_getch();
	return EXIT_SUCCESS;
}
