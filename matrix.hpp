//
// Created by uhlikf on 1/18/2019.
//

#ifndef DETERMINANT_MATRIX_HPP
#define DETERMINANT_MATRIX_HPP


#include <vector>
#include <iostream>
#include <sstream>

static int LOWER_ELEMENT_BOUND = -9;
static int UPPER_ELEMENT_BOUND = 10;


class matrix {
private:
    const int m_size;
    std::vector<double> m_contents;

    double& at(int i, int j);
    double at(int i, int j) const;

    // subtracts subtractor row multiplied by multiplier from the subtracted row
    void subtract_rows(const int & subtracted_row, const int & subtractor_row, const double & multiplier);

    // classic swap
    void swap_rows(const int & row_a, const int & row_b);

    void print_matrix(std::ostream& os) const;

    // returns determinant sign and changes the matrix to upper triangular form
    int upper_triangulate();

    // returns index of the row with pivot in given column
    int find_pivot(const int & col, const int & starting_row) const;

    long double multiply_diagonal() const;

    // fill matrix with random numbers
    void fill_matrix_random();

    void fill_matrix_from_input();

public:
    matrix(int size, bool custom) : m_size(size) {
        m_contents.resize(m_size*m_size);

        if (custom) {
            fill_matrix_from_input();
        } else {
            fill_matrix_random();
        }
    }

	// returns determinant value
	long double get_determinant();

    friend std::ostream& operator<<(std::ostream& os, const matrix& matrix);
};



// exception
class determinant_is_zero_exception :public std::exception {
private:
    std::string message;
public:
    determinant_is_zero_exception() {
        std::ostringstream out;
        out << "This matrix is singular! Its determinant is 0!";
        message = out.str();
    }
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //DETERMINANT_MATRIX_HPP