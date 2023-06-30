#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>

const int l_word = 32;
const int default_dictionary_size = 10;
const int multiplication_factor = 2;

// вообще лучше не массив структур, а структура с массивом слов
struct RecordTxt {
    char engl[l_word];
    char rus[l_word];
};

struct Dictionary {
    int dict_size;
    int dict_capacity;
    RecordTxt* words;
};

void resize_dict(Dictionary* dict) {
    if (!dict) {
        return;
    }

    dict->dict_capacity *= multiplication_factor;

    RecordTxt* buffer = new RecordTxt[dict->dict_capacity];
    memcpy(buffer, dict->words, dict->dict_size * sizeof(RecordTxt));

    delete[] dict->words;
    dict->words = buffer;
}

// Бинарный поиск
int dict_find_eng_word(Dictionary* dict, const char* word) {
    if (!dict || !word) {
        return -1;
    }

    for (int left = 0, right = dict->dict_size, mid = right / 2; left <= right; mid = (left + right) / 2) {
        int compare_result = strcasecmp(dict->words[mid].engl, word);

        if (compare_result == 0) {
            return mid;
        }

        if (compare_result < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

// Метод перебора
int dict_find_rus_word(Dictionary* dict, const char* word) {
    if (!dict || !word) {
        return -1;
    }

    for (int i = 0; i < dict->dict_size; ++i) {
        const char* lhs = dict->words[i].rus;
        const char* rhs = word;

        while (*lhs && *rhs) {
            if (*lhs != *rhs) {
                break;
            }

            ++lhs;
            ++rhs;
        }

        // какой костыль господи
        if ((*lhs == '\r' || !(*lhs)) && !(*rhs)) {
            return i;
        }
    }

    return -1;
}

// Сортировка пузырьком
void dict_words_sort(RecordTxt* words, int array_length, bool (*compare)(const RecordTxt* l_word, const RecordTxt* r_word)) {
    if (!words) {
        return;
    }

    bool sorted = false;
    int top = array_length - 1;

    while (!sorted) {
        sorted = true;
        for (int i = 0; i < top; ++i) {
            if (compare(words + i, words + i + 1)) {
                RecordTxt tmp = words[i];
                words[i] = words[i + 1];
                words[i + 1] = tmp;
                sorted = false;
            }
        }
        --top;
    }
}

bool dict_filter_eng_word(const char* eng_word) {
    if (!eng_word) {
        return false;
    }

    while (*eng_word) {
        if ((*eng_word < 'A' && *eng_word != ' ') || (*eng_word > 'Z' && *eng_word < 'a') || *eng_word > 'z') {
            return false;
        }

        ++eng_word;
    }

    return true;
}

bool add_word_to_dict(Dictionary* dictionary, const char eng_word[l_word], const char rus_word[l_word]) {
    if (!dictionary) {
        return false;
    }

    if (dictionary->dict_size == dictionary->dict_capacity) {
        resize_dict(dictionary);
    }

    if (dict_find_eng_word(dictionary, eng_word) != -1) {
        return false;
    }

    strcpy(dictionary->words[dictionary->dict_size].engl, eng_word);
    strcpy(dictionary->words[dictionary->dict_size].rus, rus_word);

    ++dictionary->dict_size;

    dict_words_sort(dictionary->words, dictionary->dict_size, [](const RecordTxt* l_word, const RecordTxt* r_word) -> bool {
        return strcasecmp(l_word->engl, r_word->engl) >= 0;
    });

    return true;
}

// Неоптимально
bool remove_word_from_dict(Dictionary* dictionary, const char eng_word[l_word]) {
    if (!dictionary) {
        return false;
    }

    int word_index = dict_find_eng_word(dictionary, eng_word);
    if (word_index == -1) {
        return false;
    }

    --dictionary->dict_size;

    memmove(dictionary->words + word_index, dictionary->words + word_index + 1, (dictionary->dict_size - word_index) * sizeof(RecordTxt));

    dict_words_sort(dictionary->words, dictionary->dict_size, [](const RecordTxt* l_word, const RecordTxt* r_word) -> bool {
        return strcasecmp(l_word->engl, r_word->engl) >= 0;
    });

    return true;
}

void read_from_file(const char* file_name, Dictionary* dictionary) {
    if (!file_name || !dictionary) {
        return;
    }

    std::fstream input_file(file_name, std::ios::in | std::ios::binary);

    if (!input_file) {
        return;
    }

    char eng_word[l_word];
    char rus_word[l_word];
    while (input_file.getline(eng_word, l_word, '|')) {
        input_file.getline(rus_word, l_word);
        add_word_to_dict(dictionary, eng_word, rus_word);
    }
}

void write_to_file(const char* file_name, Dictionary* dictionary) {
    if (!file_name || !dictionary) {
        return;
    }

    std::fstream output_file(file_name, std::ios::out | std::ios::binary);

    if (!output_file) {
        return;
    }

    for (int i = 0; i < dictionary->dict_size; ++i) {
        output_file << dictionary->words[i].engl << '|' << dictionary->words[i].rus << '\n';
    }
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "ru");

    if (argc < 2) {
        std::cout << "Недостаточно аргументов командной строки." << std::endl;
        return -1;
    }

    const char* dictionary_file = argv[1];

    Dictionary dictionary{.dict_size = 0,
                          .dict_capacity = default_dictionary_size,
                          .words = new RecordTxt[default_dictionary_size]};

    char option = 0;

    while (option != 'q') {
        std::cout << "Команды:\n" <<
                  "  1 - Считать словарь из файла\n" <<
                  "  2 - Записать словарь в файл\n" <<
                  "  3 - Добавить слово в словарь\n" <<
                  "  4 - Удалить слово из словаря\n" <<
                  "  5 - Перевести слово с английского на русский\n" <<
                  "  6 - Перевести слово с русского на английский\n" <<
                  "  7 - Вывести содержимое словаря\n" <<
                  "  q - Выйти" << std::endl;

        std::cin >> option;

        switch (option) {
            case '1': {
                read_from_file(dictionary_file, &dictionary);
                std::cout << "Success!" << std::endl;
                break;
            }

            case '2': {
                write_to_file(dictionary_file, &dictionary);
                std::cout << "Success!" << std::endl;
                break;
            }

            case '3': {
                std::string eng_word;
                std::string rus_word;
                std::cin >> eng_word >> rus_word;

                if (eng_word.length() > l_word - 1 || rus_word.length() > l_word - 1) {
                    std::cout << "Некорректный размер слова." << std::endl;
                    break;
                }

                if (!dict_filter_eng_word(eng_word.data())) {
                    std::cout << "Некорректные символы" << std::endl;
                    break;
                }

                if (add_word_to_dict(&dictionary, eng_word.data(), rus_word.data())) {
                    std::cout << "Success!" << std::endl;
                } else {
                    std::cout << "Failure!" << std::endl;
                }

                break;
            }

            case '4': {
                std::string eng_word;
                std::cin >> eng_word;

                if (eng_word.length() > l_word - 1) {
                    std::cout << "Некорректный размер слова." << std::endl;
                    break;
                }

                if (!dict_filter_eng_word(eng_word.data())) {
                    std::cout << "Некорректные символы" << std::endl;
                    break;
                }

                if (remove_word_from_dict(&dictionary, eng_word.data())) {
                    std::cout << "Success!" << std::endl;
                } else {
                    std::cout << "Failure!" << std::endl;
                }

                break;
            }

            case '5': {
                std::string word;
                std::cin >> word;

                if (word.length() > l_word - 1) {
                    std::cout << "Некорректный размер слова." << std::endl;
                    break;
                }

                if (!dict_filter_eng_word(word.data())) {
                    std::cout << "Некорректные символы" << std::endl;
                    break;
                }

                int result = dict_find_eng_word(&dictionary, word.data());

                if (result == -1) {
                    std::cout << "Failure!" << std::endl;
                } else {
                    std::cout << dictionary.words[result].engl << '|' << dictionary.words[result].rus << std::endl;
                }

                break;
            }

            case '6': {
                std::string word;
                std::cin >> word;

                if (word.length() > l_word - 1) {
                    std::cout << "Некорректный размер слова." << std::endl;
                    break;
                }

                int result = dict_find_rus_word(&dictionary, word.data());

                if (result == -1) {
                    std::cout << "Failure!" << std::endl;
                } else {
                    std::cout << dictionary.words[result].engl << '|' << dictionary.words[result].rus << std::endl;
                }
                break;
            }

            case '7': {
                for (int i = 0; i < dictionary.dict_size; ++i) {
                    std::cout << dictionary.words[i].engl << '|' << dictionary.words[i].rus << '\n';
                }
                std::cout << std::endl;
                break;
            }

            default:
                continue;
        }
    }

    delete[] dictionary.words;

    return 0;
}
