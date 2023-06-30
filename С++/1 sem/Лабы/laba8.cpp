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

    auto num_of_keys = find_file_len(file_to_encode);

    char option = 0;
    unsigned char* keys = nullptr;

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
                    encode_file(file_to_encode, encoded_file, keys);
                }
            }

            case '4': {
                if (keys) {
                    decode_file(encoded_file, decoded_file, keys);
                }
            }

            default:
                continue;
        }
    }

    delete[] keys;

    return 0;
}
