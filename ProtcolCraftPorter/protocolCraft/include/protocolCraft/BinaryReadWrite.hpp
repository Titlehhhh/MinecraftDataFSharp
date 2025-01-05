#pragma once

#include "protocolCraft/Utilities/Templates.hpp"

#include <algorithm>
#include <array>
#include <cstring>
#include <functional>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace ProtocolCraft
{
    class NetworkType;

    using ReadIterator = std::vector<unsigned char>::const_iterator;
    using WriteContainer = std::vector<unsigned char>;

    using UUID = std::array<unsigned char, 16>;

    using VarInt = VarType<int>;
    using VarLong = VarType<long long int>;

    std::string ReadRawString(ReadIterator& iter, size_t& length, const size_t size);
    void WriteRawString(const std::string& s, WriteContainer& container);

    std::vector<unsigned char> ReadByteArray(ReadIterator& iter, size_t& length, const size_t desired_length);
    void WriteByteArray(const std::vector<unsigned char>& my_array, WriteContainer& container);
    void WriteByteArray(const unsigned char* data, const size_t length, WriteContainer& container);

    namespace Internal
    {
        template <typename T>
        T ChangeEndianness(const T& in)
        {
            T out;
            std::reverse_copy(
                reinterpret_cast<const unsigned char*>(&in),
                reinterpret_cast<const unsigned char*>(&in) + sizeof(T),
                reinterpret_cast<unsigned char*>(&out)
            );
            return out;
        }
    }

    template<typename StorageType, typename SerializationType>
    StorageType ReadData(ReadIterator& iter, size_t& length
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
        ,
        typename Internal::OffsetType<StorageType>::type* start_offset = nullptr,
        typename Internal::OffsetType<StorageType>::type* end_offset = nullptr
#endif
    )
    {
        // bool, char, short, int, long, float, double ...
        if constexpr (std::is_arithmetic_v<SerializationType>)
        {
            if (length < sizeof(SerializationType))
            {
                throw std::runtime_error("Not enough input in ReadData");
            }
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
            if (start_offset != nullptr)
            {
                *start_offset = length;
            }
#endif
            SerializationType output;
            std::memcpy(&output, &(*iter), sizeof(SerializationType));
            length -= sizeof(SerializationType);
            iter += sizeof(SerializationType);
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
            if (end_offset != nullptr)
            {
                *end_offset = length;
            }
#endif
            // Don't need to change endianess of single byte
            if constexpr (sizeof(SerializationType) > 1)
            {
                // The compiler should(?) optimize that
                // This check doesn't work if int and char
                // have the same size, but I guess this is not
                // the only thing that souldn't work in this case
                constexpr int num = 1;
                if (*(char*)&num == 1)
                {
                    // Little endian --> change endianess
                    return static_cast<StorageType>(Internal::ChangeEndianness(output));
                }
            }

            // Big endian or sizeof(1) --> endianess is good
            return static_cast<StorageType>(output);
        }
        // VarType
        else if constexpr (Internal::IsVarType<SerializationType>)
        {
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
            if (start_offset != nullptr)
            {
                *start_offset = length;
            }
#endif
            size_t num_read = 0;
            typename SerializationType::underlying_type result = 0;

            unsigned char read;

            do
            {
                if (num_read >= length)
                {
                    throw std::runtime_error("Not enough input in ReadData<VarType>");
                }
                if (num_read * 7 > sizeof(typename SerializationType::underlying_type) * 8)
                {
                    throw std::runtime_error("VarType is too big in ReadData<VarType>");
                }

                read = *(iter + num_read);

                typename SerializationType::underlying_type value = static_cast<typename SerializationType::underlying_type>(read & 127);//0b01111111
                result |= (value << (7 * num_read));

                num_read++;
            } while ((read & 128) != 0);//0b10000000

            iter += num_read;
            length -= num_read;
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
            if (end_offset != nullptr)
            {
                *end_offset = length;
            }
#endif

            return static_cast<StorageType>(result);
        }
        // std::string
        else if constexpr (std::is_same_v<SerializationType, std::string> && std::is_same_v<StorageType, std::string>)
        {
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
            if (start_offset != nullptr)
            {
                *start_offset = length;
            }
#endif
            const size_t size = ReadData<size_t, VarInt>(iter, length);
            if (length < size)
            {
                throw std::runtime_error("Not enough input in ReadData<std::string>");
            }

            iter += size;
            length -= size;
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
            if (end_offset != nullptr)
            {
                *end_offset = length;
            }
#endif

            return std::string(iter - size, iter);
        }
        // NetworkType
        else if constexpr (std::is_base_of_v<NetworkType, SerializationType> && std::is_base_of_v<NetworkType, StorageType>)
        {
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
            if (start_offset != nullptr)
            {
                *start_offset = length;
            }
#endif
            SerializationType output;
            output.Read(iter, length);
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
            if (end_offset != nullptr)
            {
                *end_offset = length;
            }
#endif
            // static_cast required for example to convert between NBT::Value and NBT::UnnamedValue
            return static_cast<StorageType>(output);
        }
        // std::vector // std::array
        else if constexpr (
            Internal::IsVector<SerializationType> ||
            Internal::IsArray<SerializationType> ||
            Internal::IsGenericVector<SerializationType>)
        {
            size_t N;
            StorageType output{};
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
            if (start_offset != nullptr)
            {
                start_offset->first = length;
            }
#endif
            // std::vector
            if constexpr (Internal::IsVector<SerializationType>)
            {
                static_assert(Internal::IsVector<StorageType>, "StorageType should be a std::vector");
                N = ReadData<size_t, VarInt>(iter, length);
                output.resize(N);
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
                if (start_offset != nullptr)
                {
                    start_offset->second.resize(N);
                }
                if (end_offset != nullptr)
                {
                    end_offset->second.resize(N);
                }
#endif
            }
            // std::array
            else if constexpr (Internal::IsArray<SerializationType>)
            {
                static_assert(Internal::IsArray<StorageType>, "StorageType should be a std::array");
                N = std::size(output);
            }
            // Internal::Vector
            else
            {
                // std::array but expressed with GenericVector
                if constexpr (SerializationType::size > 0)
                {
                    static_assert(Internal::IsArray<StorageType>, "StorageType should be a std::array");
                    N = SerializationType::size;
                }
                // Special case, "all remaining data"
                else if constexpr (std::is_same_v<typename SerializationType::size_type, void>)
                {
                    static_assert(std::is_same_v<StorageType, std::vector<unsigned char>>, "Only std::vector<unsigned char> is supported for \"all remaining data\"");
                    N = length;
                    output.resize(N);
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
                    if (start_offset != nullptr)
                    {
                        start_offset->second.resize(N);
                    }
                    if (end_offset != nullptr)
                    {
                        end_offset->second.resize(N);
                    }
#endif
                }
                // Generic case for vector prefixed with size
                else
                {
                    static_assert(Internal::IsVector<StorageType>, "StorageType should be a std::vector");
                    N = ReadData<size_t, typename SerializationType::size_type>(iter, length);
                    output.resize(N);
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
                    if (start_offset != nullptr)
                    {
                        start_offset->second.resize(N);
                    }
                    if (end_offset != nullptr)
                    {
                        end_offset->second.resize(N);
                    }
#endif
                }
            }

            // If we need to read char/unsigned char, just memcpy it
            if constexpr (sizeof(typename SerializationType::value_type) == 1 &&
                !std::is_same_v<typename SerializationType::value_type, bool> &&
                std::is_same_v<typename SerializationType::value_type, typename StorageType::value_type> &&
                !std::is_base_of_v<NetworkType, typename SerializationType::value_type>)
            {
                if (length < N)
                {
                    throw std::runtime_error("Not enough input to read vector data");
                }
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
                for (size_t i = 0; i < N; ++i)
                {
                    if (start_offset != nullptr)
                    {
                        start_offset->second[i] = length - i;
                    }
                    if (end_offset != nullptr)
                    {
                        end_offset->second[i] = length - i + 1;
                    }
                }
#endif
                std::memcpy(output.data(), &(*iter), N);
                length -= N;
                iter += N;
            }
            // else read the elements one by one
            else
            {
                for (size_t i = 0; i < N; ++i)
                {
                    output[i] = ReadData<typename StorageType::value_type, typename SerializationType::value_type>(iter, length
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
                        ,
                        start_offset != nullptr ? &start_offset->second[i] : nullptr,
                        end_offset != nullptr ? &end_offset->second[i] : nullptr
#endif
                    );
                }
            }
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
            if (end_offset != nullptr)
            {
                end_offset->first = length;
            }
#endif
            return output;
        }
        // std::optional
        else if constexpr (Internal::IsOptional<StorageType> && Internal::IsOptional<SerializationType>)
        {
            StorageType output;

            const bool has_value = ReadData<bool, bool>(iter, length);
            if (has_value)
            {
                output = ReadData<typename StorageType::value_type, typename SerializationType::value_type>(iter, length
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
                    ,
                    start_offset,
                    end_offset
#endif
                );
            }

            return output;
        }
        // std::pair
        else if constexpr (Internal::IsPair<StorageType> && Internal::IsPair<SerializationType>)
        {
            StorageType output;

#ifdef PROTOCOLCRAFT_DETAILED_PARSING
            if (start_offset != nullptr)
            {
                start_offset->first = length;
            }
#endif
            output.first = ReadData<typename StorageType::first_type, typename SerializationType::first_type>(iter, length
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
                ,
                start_offset != nullptr ? &start_offset->second.first : nullptr,
                end_offset != nullptr ? &end_offset->second.first : nullptr
#endif
            );
            output.second = ReadData<typename StorageType::second_type, typename SerializationType::second_type>(iter, length
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
                ,
                start_offset != nullptr ? &start_offset->second.second : nullptr,
                end_offset != nullptr ? &end_offset->second.second : nullptr
#endif
            );

#ifdef PROTOCOLCRAFT_DETAILED_PARSING
            if (end_offset != nullptr)
            {
                end_offset->first = length;
            }
#endif
            return output;
        }
        // std::map
        else if constexpr (Internal::IsMap<StorageType> && Internal::IsMap<SerializationType>)
        {
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
            if (start_offset != nullptr)
            {
                start_offset->first = length;
            }
#endif
            const int output_length = ReadData<int, VarInt>(iter, length);

            StorageType output;
            for (int i = 0; i < output_length; ++i)
            {
                const typename StorageType::key_type key = ReadData<typename StorageType::key_type, typename SerializationType::key_type>(iter, length);
                const typename StorageType::mapped_type val = ReadData<typename StorageType::mapped_type, typename SerializationType::mapped_type>(iter, length
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
                    ,
                    start_offset != nullptr ? &start_offset->second[key] : nullptr,
                    end_offset != nullptr ? &end_offset->second[key] : nullptr
#endif
                );
                output.insert(std::make_pair(key, val));
            }

#ifdef PROTOCOLCRAFT_DETAILED_PARSING
            if (end_offset != nullptr)
            {
                end_offset->first = length;
            }
#endif
            return output;
        }
        // std::bitset
        else if constexpr (Internal::IsBitset<StorageType> && std::is_same_v<SerializationType, StorageType>)
        {
            StorageType output;
            const size_t N = output.size();
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
            if (start_offset != nullptr)
            {
                *start_offset = length;
            }
#endif
            const std::vector<unsigned char> bytes = ReadByteArray(iter, length, N / 8 + (N % 8 != 0));
            for (size_t i = 0; i < N; ++i)
            {
                output.set(i, (bytes[i / 8] >> (i % 8)) & 0x01);
            }
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
            if (end_offset != nullptr)
            {
                *end_offset = length;
            }
#endif

            return output;
        }
        else
        {
            static_assert(Internal::dependant_false<SerializationType>, "Types not supported in ReadData");
        }
    }

    template<typename T>
    typename Internal::SerializedType<T>::storage_type ReadData(ReadIterator& iter, size_t& length
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
        ,
        typename Internal::OffsetType<typename Internal::SerializedType<T>::storage_type>::type* start_offset = nullptr,
        typename Internal::OffsetType<typename Internal::SerializedType<T>::storage_type>::type* end_offset = nullptr
#endif
    )
    {
        return ReadData<typename Internal::SerializedType<T>::storage_type, typename Internal::SerializedType<T>::serialization_type>(iter, length
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
            ,
            start_offset,
            end_offset
#endif
        );
    }

    template <typename StorageType, typename SerializationType>
    void WriteData(typename std::conditional_t<std::is_arithmetic_v<StorageType> || std::is_enum_v<StorageType>, StorageType, const StorageType&> value, WriteContainer& container)
    {
        // bool, char, short, int, long, float, double ...
        if constexpr (std::is_arithmetic_v<SerializationType>)
        {
            SerializationType val = static_cast<SerializationType>(value);

            // Don't need to change endianess of single byte
            if constexpr (sizeof(SerializationType) > 1)
            {
                // Little endian check
                // It doesn't work if int and char
                // have the same size, but I guess this is not
                // the only thing that souldn't work in this case
                constexpr int num = 1;
                if (*(char*)&num == 1)
                {
                    // Little endian
                    val = Internal::ChangeEndianness(val);
                }
            }

            // Insert bytes in the container
            container.insert(
                container.end(),
                reinterpret_cast<unsigned char*>(&val),
                reinterpret_cast<unsigned char*>(&val) + sizeof(SerializationType)
            );
        }
        // VarType
        else if constexpr (Internal::IsVarType<SerializationType>)
        {
            std::make_unsigned_t<typename SerializationType::underlying_type> val = static_cast<std::make_unsigned_t<typename SerializationType::underlying_type>>(value);
            do {
                unsigned char temp = static_cast<unsigned char>(val & 127);//0b01111111
                val >>= 7;
                if (val != 0)
                {
                    temp |= 128;//0b10000000
                }
                container.push_back(temp);
            } while (val != 0);
        }
        // std::string
        else if constexpr (std::is_same_v<SerializationType, std::string> && std::is_same_v<StorageType, std::string>)
        {
            WriteData<int, VarInt>(static_cast<int>(value.size()), container);
            container.insert(container.end(), value.begin(), value.end());
        }
        // NetworkType
        else if constexpr (std::is_base_of_v<NetworkType, SerializationType> && std::is_base_of_v<NetworkType, StorageType>)
        {
            // static_cast required for example to convert between NBT::Value and NBT::UnnamedValue
            static_cast<SerializationType>(value).Write(container);
        }
        // std::vector // std::array
        else if constexpr (
            Internal::IsVector<SerializationType> ||
            Internal::IsArray<SerializationType> ||
            Internal::IsGenericVector<SerializationType>)
        {
            // std::vector
            if constexpr (Internal::IsVector<SerializationType>)
            {
                static_assert(Internal::IsVector<StorageType>, "StorageType should be a std::vector");
                WriteData<int, VarInt>(static_cast<int>(value.size()), container);
            }
            // std::array
            else if constexpr (Internal::IsArray<SerializationType>)
            {
                static_assert(Internal::IsArray<StorageType>, "StorageType should be a std::array");
            }
            // Internal::Vector
            else
            {
                // std::array but expressed with GenericVector
                if constexpr (SerializationType::size > 0)
                {
                    static_assert(Internal::IsArray<StorageType>, "StorageType should be a std::array");
                }
                // Special case, "all remaining data"
                else if constexpr (std::is_same_v<typename SerializationType::size_type, void>)
                {
                    static_assert(std::is_same_v<StorageType, std::vector<unsigned char>>, "Only std::vector<unsigned char> is supported for \"all remaining data\"");
                }
                // Generic case for vector prefixed with size
                else
                {
                    static_assert(Internal::IsVector<StorageType>, "StorageType should be a std::vector");
                    WriteData<int, typename SerializationType::size_type>(static_cast<int>(value.size()), container);
                }
            }

            // If we need to write char/unsigned char, just copy the data
            if constexpr (sizeof(typename SerializationType::value_type) == 1 &&
                !std::is_same_v<typename SerializationType::value_type, bool> &&
                std::is_same_v<typename StorageType::value_type, typename SerializationType::value_type> &&
                !std::is_base_of_v<NetworkType, typename SerializationType::value_type>)
            {
                container.insert(container.end(), value.begin(), value.end());
            }
            else
            {
                for (const auto& e : value)
                {
                    WriteData<typename StorageType::value_type, typename SerializationType::value_type>(e, container);
                }
            }
        }
        // std::optional
        else if constexpr (Internal::IsOptional<StorageType> && Internal::IsOptional<SerializationType>)
        {
            WriteData<bool, bool>(value.has_value(), container);
            if (value.has_value())
            {
                WriteData<typename StorageType::value_type, typename SerializationType::value_type>(value.value(), container);
            }
        }
        // std::pair
        else if constexpr (Internal::IsPair<StorageType> && Internal::IsPair<SerializationType>)
        {
            WriteData<typename StorageType::first_type, typename SerializationType::first_type>(value.first, container);
            WriteData<typename StorageType::second_type, typename SerializationType::second_type>(value.second, container);
        }
        // std::map
        else if constexpr (Internal::IsMap<StorageType> && Internal::IsMap<SerializationType>)
        {
            WriteData<int, VarInt>(static_cast<int>(value.size()), container);
            for (const auto& p : value)
            {
                WriteData<typename StorageType::key_type, typename SerializationType::key_type>(p.first, container);
                WriteData<typename StorageType::mapped_type, typename SerializationType::mapped_type>(p.second, container);
            }
        }
        // std::bitset
        else if constexpr (Internal::IsBitset<StorageType> && Internal::IsBitset<SerializationType>)
        {
            const size_t N = value.size();
            std::vector<unsigned char> bytes(N / 8 + (N % 8 != 0), 0);
            for (size_t i = 0; i < N; ++i)
            {
                if (value[i])
                {
                    bytes[i / 8] |= 1 << (i % 8);
                }
            }
            WriteByteArray(bytes, container);
        }
        else
        {
            static_assert(Internal::dependant_false<SerializationType>, "Types not supported in WriteData");
        }
    }

    template <typename T>
    void WriteData(std::conditional_t<std::is_arithmetic_v<typename Internal::SerializedType<T>::storage_type> || std::is_enum_v<typename Internal::SerializedType<T>::storage_type>, typename Internal::SerializedType<T>::storage_type, const typename Internal::SerializedType<T>::storage_type&> value, WriteContainer& container)
    {
        WriteData<typename Internal::SerializedType<T>::storage_type, typename Internal::SerializedType<T>::serialization_type>(value, container);
    }
} // ProtocolCraft
