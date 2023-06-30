#pragma once

template <typename T> void* PrintMatrix(T** A, int& nrows, int& ncols, int n, int& type, int& point) {
    int size = 80 / n;
    int k = 0;
    for (int km = 0; km < (ncols / size + 1); km++) {
        for (int i = 0; i < nrows; i++) {
            for (int j = k; j < (k + size); j++) {
                if (j == ncols)
                    break;
                std::cout << '\t' << std::setw(n) << A[i][j];
            }
            std::cout << '\n';
        }
        k += size;
        std::cout << '\n';
    }
}