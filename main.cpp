#include <iostream>
#include <future>
#include <iomanip>
#include "argparse.hpp"


int read_int() {
	int d;
	std::cin >> d;

	if (std::cin.good()) {
		return d;
	} else if (std::cin.bad() || std::cin.eof()) {
		throw std::runtime_error("read_int() failed");
	} else {
		std::cin.clear();
		std::cin.ignore(1, '\n');
		return read_int();
	}
}

int main(int argc, char *argv[]) {

	std::cout << std::fixed << std::setprecision(1);



    argument a = parse_arguments(argc, argv);

    switch (a) {
        case HELP: {
            std::cout << "Run with one argument 'custom' to calculate determinant of the matrices you input.\n"
						 "\nOR\n\n"
						 "Run with these three arguments to generate random matrices.\n"
                         "First argument: number of matrices to be determinanted\n"
                         "Second argument: size of the matrices\n"
                         "Third argument: '0' for singlethreaded calculation / '1' for multithreaded calculation\n"
                         "\nThe matrices are randomly generated with integers ranging from " << LOWER_ELEMENT_BOUND << " to " << UPPER_ELEMENT_BOUND << "\n"
                         "\nI will show you the matrices if they are " << PRINTABLE_MATRIX_SIZE << "x" << PRINTABLE_MATRIX_SIZE <<" or smaller. :)\n";
            break;
        }
        case CUSTOM: {
            int size;
            while (!std::cin.fail()) {
            	std::cout << "Enter matrix size: ";
				size = read_int();
				if (size == 0) {
					std::cout << "Bye!";
					exit(0);
				}

            	handler h(size);
            	h.proccess_matrices();
            }
            break;
        }
        case SINGLE: {
            handler h(std::stoi(argv[1]), std::stoi(argv[2]), false);
            h.proccess_matrices();
            break;
        }
        case MULTI: {
            handler h(std::stoi(argv[1]), std::stoi(argv[2]), true);
            h.proccess_matrices();
            break;
        }
        case INVALID: {
            std::cout << "Invalid arguments!";
            break;
        }
    }

	char i;
	std::cin >> i;

    return 0;
}