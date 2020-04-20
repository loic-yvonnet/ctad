#pragma once

// STL
#include <functional>
#include <tuple>
#include <type_traits>

template <typename TFunctor, typename... TArgs>
class task_program final {
public:
    using functor_type = TFunctor;
    using result_type = std::invoke_result_t<functor_type, TArgs...>;
    using tuple_type = std::tuple<TArgs...>;
    template <std::size_t index>
    using argument_type = std::tuple_element_t<index, tuple_type>;

    constexpr task_program(result_type& result, functor_type functor, TArgs&&... args) noexcept :
        result{ result }, functor{ functor }, arguments{ std::forward<TArgs>(args)... }
    {}

    constexpr void execute() {
        result = std::apply(functor, arguments);
    }

    constexpr result_type& get() noexcept { return result; }

    constexpr const result_type& get() const noexcept { return result; }

private:
    result_type& result;
    functor_type functor;
    tuple_type arguments;
};

// CTAD (C++17 style)
template <typename TResult, typename TFunctor, typename... TArgs>
task_program(TResult&, TFunctor, TArgs&&...) ->
    task_program<
        TFunctor,
        TArgs...
    >;

// Function template argument deduction (C++14 style)
template <typename TResult, typename TFunctor, typename... TArgs>
auto make_task_program(TResult& result, TFunctor functor, TArgs&&... args) {
    return task_program(result, functor, std::forward<TArgs>(args)...);
}