//
// Created by uhlikf on 1/19/2019.
//

#include "handler.hpp"


void handler::proccess_matrices() {
	if (m_size <= PRINTABLE_MATRIX_SIZE) {
		for (matrix& m : matrices) {
			std::cout << m << std::endl;
		}
	}

    if (multithread) {
        proccess_matrices_multithread();
    } else {
        proccess_matrices_singlethread();
    }

	if (m_size <= PRINTABLE_MATRIX_SIZE) {
		for (matrix& m : matrices) {
			std::cout << m << std::endl;
		}
	}
}

void handler::proccess_matrices_singlethread() {
    std::cout << "Let's check the time on " << m_count << " " << m_size << "x" << m_size << " matrices in one thread!" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
	long double det;
    for (auto &m : matrices) {
		det = m.get_determinant();
		print_determinant(det);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Needed " << to_ms(end - start).count() << " ms to calculate the determinants.\n";
}

void handler::proccess_matrices_multithread() {
	std::vector<std::future<long double>> futures;
	futures.reserve(m_count);

	std::cout << "Let's check the time on " << m_count << " " << m_size << "x" << m_size << " matrices in more threads!" << std::endl;
	auto start = std::chrono::high_resolution_clock::now();
	for (matrix& m : matrices) {
		futures.emplace_back(std::async(std::launch::async, [&m]() { return m.get_determinant(); }));
	}
	long double det;
	for (auto & f : futures) {
		f.wait();
		det = f.get();
		print_determinant(det);
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "Needed " << to_ms(end - start).count() << " ms to calculate the determinants.\n";
}

void handler::print_determinant(long double & det) const {
	check_output(det);
	std::cout << "Determinant is: " << det << std::endl;
	std::cout << std::fixed;
}


void handler::check_output(long double & out) const {
	if (abs(out) > std::pow(10, 6)) {
		std::cout << std::scientific;
	}
}