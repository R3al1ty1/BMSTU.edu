#include <fstream>
#include <iomanip>
#include <iostream>

unsigned char* create_keys(const char* code_file_name, size_t length) {
    if (!code_file_name) {
        return nullptr;
    }

    std::ifstream code_file(code_file_name, std::ios::in | std::ios::binary);

    if (!code_file) {
        return nullptr;
    }

    unsigned char* keys = new unsigned char[length];
    int current_key = 0;

    const int max_byte_value = 256;

    for (size_t i = 0; i < length; ++i) {
        while ((current_key = code_file.get()) != (int)' ') {
            if (current_key == EOF) {
                code_file.clear();
                code_file.seekg(0);
                break;
            }

            keys[i] = (keys[i] + current_key) % max_byte_value;
        }
    }

    return keys;
}

void encode_file(const char* input_file_name, const char* output_file_name, const unsigned char* keys) {
    if (!input_file_name || !output_file_name || !keys) {
        return;
    }

    std::fstream input_file(input_file_name, std::ios::in | std::ios::binary);

    if (!input_file) {
        return;
    }

    std::fstream output_file(output_file_name, std::ios::out | std::ios::binary);

    if (!output_file) {
        return;
    }

    int current_symbol = 0;
    for (size_t i = 0; (current_symbol = input_file.get()) != EOF; ++i) {
        output_file << (unsigned char)((unsigned char)current_symbol ^ keys[i]);
    }
}

void decode_file(const char* input_file_name, const char* output_file_name, const unsigned char* keys) {
    encode_file(input_file_name, output_file_name, keys);
}

void show_keys(const unsigned char* keys, size_t length) {
    const int num_of_byte_digits = 3;
    const int num_of_index_digits = [length]() mutable {
        int num_of_digits = 1;
        while (length /= 10) {
            ++num_of_digits;
        }
        return num_of_digits;
    }();

    for (size_t i = 0; i < length; ++i) {
        std::cout << "key: (index) " << std::setw(num_of_index_digits) << i <<
                  " (int value) " << std::setw(num_of_byte_digits) << (int)keys[i] << '\n';
    }
}

size_t find_file_len(const char* file_name) {
    if (!file_name) {
        return 0;
    }

    std::fstream file(file_name, std::ios::in | std::ios::binary);

    if (!file) {
        return 0;
    }

    std::streampos file_size = file.tellg();
    file.seekg(0, std::ios::end);
    file_size = file.tellg() - file_size;

    return file_size;
}

void find_stat(const char* encoded_file_name, const char* input_file_name, int* stat_array, char sym) {
    if (!encoded_file_name || !input_file_name || !stat_array) {
        return;
    }

    std::fstream encoded_file(encoded_file_name, std::ios::in | std::ios::binary);
    if (!encoded_file) {
        return;
    }

    std::fstream input_file(input_file_name, std::ios::in | std::ios::binary);
    if (!input_file) {
        return;
    }

    int current_symbol = 0;
    for (size_t i = 0; (current_symbol = input_file.get()) != EOF; ++i) {
        if (current_symbol != (int)sym) {
            continue;
        }

        stat_array[encoded_file.seekg(input_file.tellg()).get()]++;
    }
}

int main(int argc, char** argv) {
    if (argc < 5) {
        std::cout << "Недостаточно аргументов командной строки." << std::endl;
        return -1;
    }

    // argv[1] - кодовый блокнот
    // argv[2] - шифруемый файл
    // argv[3] - файл, куда будет записан зашифрованный файл
    // argv[4] - файл, куда будет записан дешифрованный файл

    const char* code_note = argv[1];
    const char* file_to_encode = argv[2];
    const char* encoded_file = argv[3];
    const char* decoded_file = argv[4];

    const size_t num_of_keys = find_file_len(file_to_encode);

    char option = 0;
    unsigned char* keys = nullptr;
    bool is_encoded = false;
    bool is_decoded = false;

    while (option != 'q') {
        std::cout << "Команды:\n" <<
                  "  1 - Создать массив ключей\n" <<
                  "  2 - Просмотреть массив ключей\n" <<
                  "  3 - Кодировать файл\n" <<
                  "  4 - Декодировать файл\n" <<
                  "  5 - Показать статистику\n" <<
                  "  q - Выйти" << std::endl;

        std::cin >> option;

        switch (option) {
            case '1': {
                if (!keys) {
                    keys = create_keys(code_note, num_of_keys);
                }

                std::cout << "Success!" << std::endl;
                break;
            }

            case '2': {
                if (keys) {
                    show_keys(keys, num_of_keys);
                }
                break;
            }

            case '3': {
                if (keys) {
                    if (!is_encoded) {
                        encode_file(file_to_encode, encoded_file, keys);
                        is_encoded = true;
                    }

                    std::cout << "Success!" << std::endl;
                }
                break;
            }

            case '4': {
                if (keys && is_encoded) {
                    if (!is_decoded) {
                        decode_file(encoded_file, decoded_file, keys);
                        is_decoded = true;
                    }

                    std::cout << "Success!" << std::endl;
                }
                break;
            }

            case '5': {
                if (is_encoded) {
                    int stat[256] = {0};

                    char sym = 0;
                    std::cout << "Введите символ для которого нужно показать статистику" << std::endl;
                    std::cin >> sym;

                    find_stat(encoded_file, file_to_encode, stat, sym);

                    for (int i = 0; i < 16; ++i) {
                        for (int j = 0; j < 16; ++j) {
                            std::cout << std::setw(3) << stat[i * 16 + j] << ' ';
                        }

                        std::cout << '\n';
                    }
                }
            }

            default:
                continue;
        }
    }

    delete[] keys;

    return 0;
}
