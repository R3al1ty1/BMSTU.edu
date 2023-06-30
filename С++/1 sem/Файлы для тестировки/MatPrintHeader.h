#pragma once
template <typename T> void* PrintMatrix(T** a, int& nrow, int& ncol, int n) {
    int i, j, w;
    if (n != 0) {
        w = 2 * ncol + n;
    }
    else {
        w = 8;
    }

    std::cout << "\n\n   ";
    for (j = 0; j < ncol; j++)
        std::cout << std::setw(w) << j + 1;
    std::cout << "\n";
    std::cout << "   ";
    for (j = 0; j < ncol; j++)
        std::cout << std::setw(w) << "_";
    std::cout << "\n\n\n";

    for (i = 0; i < nrow; i++)
    {
        std::cout << i + 1 << "| ";
        for (j = 0; j < ncol; j++)
        {
            std::cout << std::setw(w) << std::fixed << std::setprecision(n) << a[i][j];
        }
        std::cout << "\n\n";
    }
    return 0;
}