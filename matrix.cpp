//
// Created by uhlikf on 1/18/2019.
//

#include <random>
#include <math.h>
#include "matrix.hpp"
#include <iomanip>



double read_double() {
	double d;
	std::cin >> d;

	if (std::cin.good()) {
		return d;
	} else if (std::cin.bad() || std::cin.eof()) {
		throw std::runtime_error("read_int() failed");
	} else {
		std::cin.clear();
		std::cin.ignore(1, '\n');
		return read_double();
	}
}


double get_random_double() {
    static std::mt19937 mt{ std::random_device{}() };
    static std::uniform_int_distribution<> dist(LOWER_ELEMENT_BOUND, UPPER_ELEMENT_BOUND);
    return dist(mt);
}

void matrix::fill_matrix_random() {
    for (int i = 0; i < m_size; ++i) {
        for (int j = 0; j < m_size; ++j) {
            at(i, j) = get_random_double();
        }
    }
}

void matrix::fill_matrix_from_input() {
    for (int i = 0; i < m_size; ++i) {
        for (int j = 0; j < m_size; ++j) {
            std::cout << "Element at [" << i << "," << j << "]: " ;
			at(i, j) = read_double();
        }
    }
}

void matrix::subtract_rows(const int & subtracted_row, const int & subtractor_row, const double& multiplier) {
    for (int col = 0; col < m_size; ++col) {
        at(subtracted_row, col) -= at(subtractor_row, col) * multiplier;
    }
}

void matrix::swap_rows(const int & row_a, const int & row_b) {
    for (int col = 0; col < m_size; ++col) {
        std::swap(at(row_a, col), at(row_b, col));
    }
}

int matrix::find_pivot(const int & col, const int & starting_row) const {
	int pivot_row = -1;
    for (int row = starting_row; row < m_size; ++row) {
        if (at(row, col) != 0 && (pivot_row == -1 || abs(at(row, col)) > abs(at(pivot_row, col)))) {
			pivot_row = row;
        }
    }
    return pivot_row;
}


long double matrix::multiply_diagonal() const {
    long double result = 1.00L;
    for (int k = 0; k < m_size; ++k) {
        result *= at(k, k);
    }
    return result;
}

int matrix::upper_triangulate() {
    int sign = 1;

    for (int col = 0; col < m_size; ++col) {
        int starting_row = col;
        int non_zero_row = find_pivot(col, starting_row);

        if (non_zero_row == -1) {
            throw determinant_is_zero_exception();
        } else if (starting_row != non_zero_row) {
            swap_rows(starting_row, non_zero_row);
            sign *= -1;
        }

        for (int row = starting_row + 1; row < m_size; ++row) {
            const double current_element = at(row, col);
            if (current_element != 0) {
                subtract_rows(row, starting_row, current_element/at(starting_row, col));
            }
        }
    }

    return sign;
}


long double matrix::get_determinant() {
    int sign;
    try {
        sign = upper_triangulate();
    } catch (determinant_is_zero_exception&) {
        return 0;
    }

    return multiply_diagonal() * sign;
}

// accessing elements
double & matrix::at(int i, int j) {
    return m_contents.at(i*m_size+j);
}

double matrix::at(int i, int j) const {
    return m_contents.at(i*m_size+j);
}

// printing stuff
void matrix::print_matrix(std::ostream& os) const {
	os << std::endl;
    for (int row = 0; row < m_size; ++row) {
        os << "| ";
        for (int col = 0; col < m_size; ++col) {
            os << std::setw(4) << at(row, col) << " ";
        }
        os << "|" << std::endl;
    }
}

std::ostream &operator<<(std::ostream &os, const matrix &matrix) {
        matrix.print_matrix(os);
        return os;
}