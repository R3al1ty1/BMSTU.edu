#include <iostream>
#include <iomanip>
using namespace std;

struct Matrix {
    int size; // size of matrix
    double det; // determinant of matrix
    double **arr_init_matrix; // array of initial matrix
    double **arr_elem_matrix; // array of elemetary matrix
    double **arr_rev_matrix; // array of reverse matrix
    friend std::ostream &operator<<(std::ostream &out, const Matrix &m_out) {
        out << "Initial matrix is\n";
        for (int i = 0; i < m_out.size; i++) {
            out << "|";
            for (int j = 0; j < m_out.size; j++) {
                out << m_out.arr_init_matrix[i][j] << ' ';
            }
            out << "|" << endl;
        }
        out << "Determinant is " << m_out.det;
        if (m_out.det) {
            out << "\nReverse marix is\n";
            for (int i = 0; i < m_out.size; i++) {
                out << "|";
                for (int j = 0; j < m_out.size; j++) {
                    out << m_out.arr_rev_matrix[i][j] << ' ';
                }
                out << "|" << endl;
            }
            out << "Elementary matrix is\n";
            for (int i = 0; i < m_out.size; i++) {
                out << "|";
                for (int j = 0; j < m_out.size; j++) {
                    out << m_out.arr_elem_matrix[i][j] << ' ';
                }
                out << "|" << endl;
            }
        } else {
            out << ", reverse matrix does not exist\n";
        }
        return out;
    }
};
void take_stepped_view(Matrix*); // converts to step matrix
bool check_zero_row_col(Matrix*); // checking for availability zero-col or zero-row
void change_col(Matrix*, int); // changing rows if on main diagonal zero element
void calculate_stage(Matrix*, int, int); // calculating stage (row - row)
void take_elem_matrix_unit(Matrix*); // converts values on the main diagonal to unit(single) //bool find_best_row(Matrix*) // finding minimal count in rows (in developing)

int main() {
