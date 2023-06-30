#pragma once

template <typename T> void* PrintMatrix(T** a, int& nrow, int& ncol, int n) {
    int i, j, w, fl;
    if (ncol != nrow) {
        w = 6 + n;
        fl = 1;
    }
    else {
        w = 8 + n;
        fl = 0;
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
            if (fl == 1)
                if (j == (ncol / 2) - 1)
                    std::cout << std::setw(w) << std::fixed << std::setprecision(n) << a[i][j] << " | ";
                else
                    std::cout << std::setw(w) << std::fixed << std::setprecision(n) << a[i][j];
            else
                std::cout << std::setw(w) << std::fixed << std::setprecision(n) << a[i][j];
        }
        std::cout << "\n\n";
    }
    return 0;
}