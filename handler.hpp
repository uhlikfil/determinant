//
// Created by uhlikf on 1/19/2019.
//

#ifndef DETERMINANT_HANDLER_HPP
#define DETERMINANT_HANDLER_HPP

#include <chrono>
#include <vector>
#include "matrix.hpp"
#include <math.h>
#include <future>


template <typename TimePoint>
std::chrono::milliseconds to_ms(TimePoint tp) {
	return std::chrono::duration_cast<std::chrono::milliseconds>(tp);
}

static int PRINTABLE_MATRIX_SIZE = 10;

class handler {
private:
    int m_count, m_size;
    std::vector<matrix> matrices;
    bool multithread;

	void print_determinant(long double & det) const;
	void check_output(long double & out) const;

    void proccess_matrices_singlethread();
    void proccess_matrices_multithread();

public:
    handler(int matrix_count, int matrix_size, bool multithreaded) : m_count(matrix_count), m_size(matrix_size), multithread(multithreaded) {
        matrices.reserve(m_count);

        for (int i = 0; i < m_count; ++i) {
            matrices.emplace_back(matrix(m_size, false));
        }
    }

    handler(int matrix_size) : m_count(1), m_size(matrix_size), multithread(false) {
        matrices.emplace_back(matrix(matrix_size, true));
    }

    void proccess_matrices();
};



#endif //DETERMINANT_HANDLER_HPP
