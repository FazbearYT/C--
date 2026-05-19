# Data Structures — C++20

Stack, Queue, Binary Search Tree с меню и Google Test.

## Структура

```
data_structures/
├── CMakeLists.txt
├── main.cpp
├── stack.h / stack.cpp
├── queue.h / queue.cpp
├── bst.h   / bst.cpp
└── tests/
    └── test_main.cpp
```

## Сборка

```bash
mkdir build && cd build
cmake .. -DCOVERAGE=ON -G "MinGW Makefiles"
cmake --build . --clean-first
```

## Запуск

```bash
./ds_app
```

## Тесты

```MSYS UCRT64
cd /d/developing/lab4/v2/claude/build

# Запуск тестов
./ds_tests.exe

# Сбор покрытия
lcov --capture --directory . --output-file coverage_total.info --rc lcov_branch_coverage=1

# Фильтрация
lcov --remove coverage_total.info '*/_deps/*' '*/googletest/*' '*/tests/*' --output-file coverage.info

# Генерация HTML
genhtml coverage.info --output-directory coverage_report --rc genhtml_branch_coverage=1
```

## Зависимости

- CMake >= 3.16
- GCC/Clang с поддержкой C++20
- Google Test (`sudo apt install libgtest-dev` на Ubuntu)
