// CTAD
#include "task_program.hpp"

// FMT
#include "fmt/format.h"

int f() {
    return 0;
}

struct foo {
    int internal{};

    bool operator()(char& a, float& f) {
        internal = static_cast<int>(a) + static_cast<int>(f);

        a = 'a';
        f = 6.f;

        return internal != 0;
    }
};

double bar(int i) {
    return i * 2.;
}

int main() {
    {
        int result{ 1 };
        auto task = task_program(result, f);
        task.execute();
        fmt::print("Task 0 : [ result: {} ]\n", result);
    }

    {
        int result{};
        auto task = task_program(result, [] { return 42; });
        task.execute();
        fmt::print("Task 1 : [ result: {} ]\n", result);
    }

    {
        double result{};
        int i{ 42 };
        auto task = task_program(result, &bar, i);
        task.execute();
        fmt::print("Task 2 : [ result: {}, i : {} ]\n", result, i);
    }

    {
        long result{};
        auto task = task_program(result, [](int i) -> long { return i * i; }, 42);
        task.execute();
        fmt::print("Task 3 : [ result: {}]\n", result);
    }
    
    {
        bool result{};
        char a = 'A';
        float f = 42.f;
        foo fighters;
        auto task = task_program(result, fighters, std::ref(a), std::ref(f));
        task.execute();
        fmt::print("Task 4 : [ result: {}, a: {}, f: {}, internal: {} ]\n", result, a, f, fighters.internal);
    }
}