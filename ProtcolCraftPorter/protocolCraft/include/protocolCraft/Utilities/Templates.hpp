#pragma once

#include <array>
#include <bitset>
#include <map>
#include <memory>
#include <optional>
#include <tuple>
#include <utility>
#include <vector>

namespace ProtocolCraft
{
    namespace NBT
    {
        class Value;
        class UnnamedValue;
    }

    namespace Json
    {
        class Value;
    }

    template <typename T>
    struct VarType { using underlying_type = T; };


    namespace Internal
    {
        /// @brief Default case, see field_index specialization for implementation details
        template <size_t N, typename T, template <size_t, typename> typename U, typename = void>
        static constexpr size_t field_index = 0;

        /// @brief A templated size_t that counts the number of existing classes U with a "field_name" member
        /// @tparam N Current counter for recursion (user should always call it with 0)
        /// @tparam T Can be any type, must be different for each field we want to be counted later (used because we can't have a empty template<> specialization nested in a class)
        /// @tparam U The templated class that will be searched for match
        template <size_t N, typename T, template <size_t, typename> typename U>
        static constexpr size_t field_index<N, T, U, std::void_t<decltype(U<N, T>::field_name)>> = 1 + field_index<N + 1, T, U>;

        /// @brief Concat multiple tuples in one big tuple
        /// @tparam ...input_t Multiple std::tuple types to concat
        template<typename ... input_t>
        using tuple_cat_t =
            decltype(std::tuple_cat(
                std::declval<input_t>()...
            ));

        template <typename T, typename Tuple> constexpr bool tuple_contains_type = false;
        template <typename T, typename... Ts> constexpr bool tuple_contains_type<T, std::tuple<Ts...>> = std::disjunction_v<std::is_same<T, Ts>...>;

        template <typename T, typename Tuple>                   constexpr int get_tuple_index                                = 0;
        template <typename T, typename... Rest>                 constexpr int get_tuple_index<T, std::tuple<T, Rest...>>     = 0;
        template <typename T, typename First, typename... Rest> constexpr int get_tuple_index<T, std::tuple<First, Rest...>> = 1 + get_tuple_index<T, std::tuple<Rest...>>;

        // Template black magic to loop at compile time
        template<std::size_t... indices, class LoopBody>
        void loop_impl(std::index_sequence<indices...>, LoopBody&& loop_body) {
            (loop_body(std::integral_constant<std::size_t, indices>{}), ...);
        }

        template<std::size_t N, class LoopBody>
        void loop(LoopBody&& loop_body) {
            loop_impl(std::make_index_sequence<N>{}, std::forward<LoopBody>(loop_body));
        }


        /// @brief Just a simple type wrapper that will store with T1 and serialize as T2 (can be used for Enum/VarInt for example)
        /// @tparam T1 Storage type
        /// @tparam T2 Serialization type
        template <typename T1, typename T2> struct DiffType {};

        template <typename T> struct GetClassFromConditionPtr;
        template <typename C> struct GetClassFromConditionPtr<bool(C::*)() const> { using Class = C; };

        /// @brief A type wrapper to conditionally serialize a type
        /// @tparam T Underlying type, can be VarType or DiffType too
        /// @tparam Condition A condition function pointer to a non static const class member function returning a bool, i.e. ``bool(*Class::Condition)(const Class*) const``
        /// @tparam StoredAsOptional If true, T will be stored as empty std::optional when Condition is not satisfied instead of default initialized values
        template <typename T, auto Condition, bool StoredAsOptional = true>
        struct Conditioned
        {
            using type = T;
            static constexpr bool stored_as_optional = StoredAsOptional;
            // Technically we could just store Condition and use it with (this->*Conditioned::Condition)() but that's a bit ugly
            // So instead we use this simpler tu use wrapper around it
            static bool Evaluate(const typename GetClassFromConditionPtr<decltype(Condition)>::Class* t)
            {
                return (t->*Condition)();
            }
        };

        template <typename T, typename S = VarType<int>, size_t N = 0>
        struct Vector
        {
            using value_type = T;
            using size_type = S;
            static constexpr size_t size = N;
            static_assert(std::is_same_v<S, void> || N == 0, "Can't specify a size type if N > 0");
        };

        template <typename T> struct SerializedType;

        template <typename T, auto ReadFunc, auto WriteFunc, auto SerializeFunc>
        struct CustomType;

        template <typename T>                         constexpr bool IsArray                              = false;
        template <typename T, size_t N>               constexpr bool IsArray<std::array<T, N>>            = true;
        template <typename T>                         constexpr bool IsVector                             = false;
        template <typename T>                         constexpr bool IsVector<std::vector<T>>             = true;
        template <typename T>                         constexpr bool IsGenericVector                      = false;
        template <typename T, typename U, size_t N>   constexpr bool IsGenericVector<Vector<T, U, N>>     = true;
        template <typename T>                         constexpr bool IsMap                                = false;
        template <typename K, typename V>             constexpr bool IsMap<std::map<K, V>>                = true;
        template <typename T>                         constexpr bool IsVarType                            = false;
        template <typename T>                         constexpr bool IsVarType<VarType<T>>                = true;
        template <typename T>                         constexpr bool IsOptional                           = false;
        template <typename T>                         constexpr bool IsOptional<std::optional<T>>         = true;
        template <typename T>                         constexpr bool IsPair                               = false;
        template <typename T1, typename T2>           constexpr bool IsPair<std::pair<T1, T2>>            = true;
        template <typename T>                         constexpr bool IsBitset                             = false;
        template <size_t N>                           constexpr bool IsBitset<std::bitset<N>>             = true;
        template <typename T>                         constexpr bool IsConditioned                        = false;
        template <typename T, auto C, bool b>         constexpr bool IsConditioned<Conditioned<T, C, b>>  = true;
        template <typename T>                         constexpr bool IsCustomType                         = false;
        template <typename T, auto R, auto W, auto S> constexpr bool IsCustomType<CustomType<T, R, W, S>> = true;
        template <typename T>                         constexpr bool IsSharedPtr                          = false;
        template <typename T>                         constexpr bool IsSharedPtr<std::shared_ptr<T>>      = true;


        template <typename T>                         struct SerializedType                           { using storage_type = T;                                                                                               using serialization_type = T;                                                             };
        template <typename T>                         struct SerializedType<VarType<T>>               { using storage_type = T;                                                                                               using serialization_type = VarType<T>;                                                    };
        template <>                                   struct SerializedType<NBT::UnnamedValue>        { using storage_type = NBT::Value;                                                                                      using serialization_type = NBT::UnnamedValue;                                             };
        template <typename T, size_t N>               struct SerializedType<std::array<T, N>>         { using storage_type = std::array<typename SerializedType<T>::storage_type, N>;                                         using serialization_type = std::array<T, N>;                                              };
        template <typename T>                         struct SerializedType<std::vector<T>>           { using storage_type = std::vector<typename SerializedType<T>::storage_type>;                                           using serialization_type = std::vector<T>;                                                };
        template <typename T>                         struct SerializedType<Vector<T, void, 0>>       { using storage_type = std::vector<typename SerializedType<T>::storage_type>;                                           using serialization_type = Vector<T, void, 0>;                                            };
        template <typename T, size_t N>               struct SerializedType<Vector<T, void, N>>       { using storage_type = std::array<typename SerializedType<T>::storage_type, N>;                                         using serialization_type = Vector<T, void, N>;                                            };
        template <typename T, typename U>             struct SerializedType<Vector<T, U>>             { using storage_type = std::vector<typename SerializedType<T>::storage_type>;                                           using serialization_type = Vector<T, U>;                                                  };
        template <typename T>                         struct SerializedType<std::optional<T>>         { using storage_type = std::optional<typename SerializedType<T>::storage_type>;                                         using serialization_type = std::optional<T>;                                              };
        template <typename K, typename V>             struct SerializedType<std::map<K, V>>           { using storage_type = std::map<typename SerializedType<K>::storage_type, typename SerializedType<V>::storage_type>;    using serialization_type = std::map<K, V>;                                                };
        template <typename T1, typename T2>           struct SerializedType<std::pair<T1, T2>>        { using storage_type = std::pair<typename SerializedType<T1>::storage_type, typename SerializedType<T2>::storage_type>; using serialization_type = std::pair<T1, T2>;                                             };
        template <typename T1, typename T2>           struct SerializedType<DiffType<T1, T2>>         { using storage_type = T1;                                                                                              using serialization_type = T2;                                                            };
        template <typename T, auto F>                 struct SerializedType<Conditioned<T, F, true>>  { using storage_type = std::optional<typename SerializedType<T>::storage_type>;                                         using serialization_type = T;                                                             };
        template <typename T, auto F>                 struct SerializedType<Conditioned<T, F, false>> { using storage_type = typename SerializedType<T>::storage_type;                                                        using serialization_type = T;                                                             };
        template <typename T, auto R, auto W, auto S> struct SerializedType<CustomType<T, R, W, S>>   { using storage_type = typename SerializedType<T>::storage_type;                                                        using serialization_type = T;                                                             };

        /// @brief To be used in constexpr else to fail compilation in a C++ compliant way
        /// @tparam T Any type
        template <typename T> constexpr bool dependant_false = false;

#ifdef PROTOCOLCRAFT_DETAILED_PARSING
        template <typename T>                 struct OffsetType                        { using type = size_t;                                                                                     };
        template <typename T>                 struct OffsetType<std::optional<T>>      { using type = typename OffsetType<T>::type;                                                               };
        template <typename T>                 struct OffsetType<std::vector<T>>        { using type = std::pair<size_t, std::vector<typename OffsetType<T>::type>>;                               };
        template <typename T, size_t N>       struct OffsetType<std::array<T, N>>      { using type = std::pair<size_t, std::array<typename OffsetType<T>::type, N>>;                             };
        template <typename T1, typename T2>   struct OffsetType<std::pair<T1, T2>>     { using type = std::pair<size_t, std::pair<typename OffsetType<T1>::type, typename OffsetType<T2>::type>>; };
        template <typename K, typename V>     struct OffsetType<std::map<K, V>>        { using type = std::pair<size_t, std::map<K, typename OffsetType<V>::type>>;                               };
#endif
    }
}
