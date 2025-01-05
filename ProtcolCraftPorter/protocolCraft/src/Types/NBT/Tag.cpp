#include "protocolCraft/Types/NBT/Tag.hpp"

namespace ProtocolCraft
{
    using namespace Internal;

    namespace NBT
    {
        enum class TagType : char
        {
            TagEnd = 0,
            TagByte,
            TagShort,
            TagInt,
            TagLong,
            TagFloat,
            TagDouble,
            TagByteArray,
            TagString,
            TagList,
            TagCompound,
            TagIntArray,
            TagLongArray
        };

        std::string ReadNBTString(ReadIterator& iter, size_t& length);
        void WriteNBTString(const std::string& s, WriteContainer& container);

        template<typename T>
        constexpr std::string_view GetTagName()
        {
            if constexpr (std::is_same_v<T, TagEnd>)
            {
                return "TagEnd";
            }
            else if constexpr (std::is_same_v<T, TagByte>)
            {
                return "TagByte";
            }
            else if constexpr (std::is_same_v<T, TagShort>)
            {
                return "TagShort";
            }
            else if constexpr (std::is_same_v<T, TagInt>)
            {
                return "TagInt";
            }
            else if constexpr (std::is_same_v<T, TagLong>)
            {
                return "TagLong";
            }
            else if constexpr (std::is_same_v<T, TagFloat>)
            {
                return "TagFloat";
            }
            else if constexpr (std::is_same_v<T, TagDouble>)
            {
                return "TagDouble";
            }
            else if constexpr (std::is_same_v<T, TagByteArray>)
            {
                return "TagByteArray";
            }
            else if constexpr (std::is_same_v<T, TagString>)
            {
                return "TagString";
            }
            else if constexpr (std::is_same_v<T, TagList>)
            {
                return "TagList";
            }
            else if constexpr (std::is_same_v<T, TagCompound>)
            {
                return "TagCompound";
            }
            else if constexpr (std::is_same_v<T, TagIntArray>)
            {
                return "TagIntArray";
            }
            else if constexpr (std::is_same_v<T, TagLongArray>)
            {
                return "TagLongArray";
            }

            return "Unknown tag";
        }


        const std::string& Tag::GetName() const
        {
            return name;
        }

        void Tag::ReadUnnamedImpl(ReadIterator& iter, size_t& length)
        {
            const TagType type = static_cast<TagType>(ReadData<char>(iter, length));

            if (type == TagType::TagEnd)
            {
                val = Internal::TagVariant();
                return;
            }

#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
            // Name is read but ignored
            name = ReadNBTString(iter, length);
#endif
            name = "";

            switch (type)
            {
            case TagType::TagEnd:
                // Should not happen but for completeness
                break;
            case TagType::TagByte:
                val = ReadData<char>(iter, length);
                break;
            case TagType::TagShort:
                val = ReadData<short>(iter, length);
                break;
            case TagType::TagInt:
                val = ReadData<int>(iter, length);
                break;
            case TagType::TagLong:
                val = ReadData<long long int>(iter, length);
                break;
            case TagType::TagFloat:
                val = ReadData<float>(iter, length);
                break;
            case TagType::TagDouble:
                val = ReadData<double>(iter, length);
                break;
            case TagType::TagByteArray:
                // Special case, use int as size instead of varint
                val = ReadData<Vector<char, int>>(iter, length);
                break;
            case TagType::TagString:
                val = ReadNBTString(iter, length);
                break;
            case TagType::TagList:
                val = ReadData<TagList>(iter, length);
                break;
            case TagType::TagCompound:
                val = ReadData<TagCompound>(iter, length);
                break;
            case TagType::TagIntArray:
                // Special case, use int as size instead of varint
                val = ReadData<Vector<int, int>>(iter, length);
                break;
            case TagType::TagLongArray:
                // Special case, use int as size instead of varint
                val = ReadData<Vector<long long int, int>>(iter, length);
                break;
            default:
                break;
            }
        }

        void Tag::WriteUnnamedImpl(WriteContainer& container) const
        {
            WriteData<char>(static_cast<char>(val.index()), container);

            if (std::holds_alternative<TagEnd>(val))
            {
                return;
            }

#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
            // Always empty string is written as this is unnamed
            WriteNBTString("", container);
#endif

            std::visit([&](auto&& arg)
                {
                    using T = std::decay_t<decltype(arg)>;

                    if constexpr (std::is_same_v<T, TagEnd>)
                    {
                        return;
                    }
                    else if constexpr (std::is_same_v<T, TagByteArray>)
                    {
                        // Special case, use int as size instead of varint
                        WriteData<Vector<char, int>>(arg, container);
                    }
                    else if constexpr (std::is_same_v<T, TagString>)
                    {
                        WriteNBTString(arg, container);
                    }
                    else if constexpr (std::is_same_v<T, RecursiveWrapper<TagList>>)
                    {
                        WriteData<TagList>(arg.get(), container);
                    }
                    else if constexpr (std::is_same_v<T, RecursiveWrapper<TagCompound>>)
                    {
                        WriteData<TagCompound>(arg.get(), container);
                    }
                    else if constexpr (std::is_same_v<T, TagIntArray>)
                    {
                        // Special case, use int as size instead of varint
                        WriteData<Vector<int, int>>(arg, container);
                    }
                    else if constexpr (std::is_same_v<T, TagLongArray>)
                    {
                        // Special case, use int as size instead of varint
                        WriteData<Vector<long long int, int>>(arg, container);
                    }
                    else
                    {
                        WriteData<T>(arg, container);
                    }
                }, val);
        }

        void Tag::ReadImpl(ReadIterator& iter, size_t& length)
        {
            const TagType type = static_cast<TagType>(ReadData<char>(iter, length));

            if (type == TagType::TagEnd)
            {
                val = Internal::TagVariant();
                return;
            }

            name = ReadNBTString(iter, length);

            switch (type)
            {
            case TagType::TagEnd:
                // Should not happen but for completeness
                break;
            case TagType::TagByte:
                val = ReadData<char>(iter, length);
                break;
            case TagType::TagShort:
                val = ReadData<short>(iter, length);
                break;
            case TagType::TagInt:
                val = ReadData<int>(iter, length);
                break;
            case TagType::TagLong:
                val = ReadData<long long int>(iter, length);
                break;
            case TagType::TagFloat:
                val = ReadData<float>(iter, length);
                break;
            case TagType::TagDouble:
                val = ReadData<double>(iter, length);
                break;
            case TagType::TagByteArray:
                // Special case, use int as size instead of varint
                val = ReadData<Vector<char, int>>(iter, length);
                break;
            case TagType::TagString:
                val = ReadNBTString(iter, length);
                break;
            case TagType::TagList:
                val = ReadData<TagList>(iter, length);
                break;
            case TagType::TagCompound:
                val = ReadData<TagCompound>(iter, length);
                break;
            case TagType::TagIntArray:
                // Special case, use int as size instead of varint
                val = ReadData<Vector<int, int>>(iter, length);
                break;
            case TagType::TagLongArray:
                // Special case, use int as size instead of varint
                val = ReadData<Vector<long long int, int>>(iter, length);
                break;
            default:
                break;
            }
        }

        void Tag::WriteImpl(WriteContainer& container) const
        {
            WriteData<char>(static_cast<char>(val.index()), container);

            if (std::holds_alternative<TagEnd>(val))
            {
                return;
            }

            WriteNBTString(name, container);

            std::visit([&](auto&& arg)
                {
                    using T = std::decay_t<decltype(arg)>;

                    if constexpr (std::is_same_v<T, TagEnd>)
                    {
                        return;
                    }
                    else if constexpr (std::is_same_v<T, TagByteArray>)
                    {
                        // Special case, use int as size instead of varint
                        WriteData<Vector<char, int>>(arg, container);
                    }
                    else if constexpr (std::is_same_v<T, TagString>)
                    {
                        WriteNBTString(arg, container);
                    }
                    else if constexpr (std::is_same_v<T, RecursiveWrapper<TagList>>)
                    {
                        WriteData<TagList>(arg.get(), container);
                    }
                    else if constexpr (std::is_same_v<T, RecursiveWrapper<TagCompound>>)
                    {
                        WriteData<TagCompound>(arg.get(), container);
                    }
                    else if constexpr (std::is_same_v<T, TagIntArray>)
                    {
                        // Special case, use int as size instead of varint
                        WriteData<Vector<int, int>>(arg, container);
                    }
                    else if constexpr (std::is_same_v<T, TagLongArray>)
                    {
                        // Special case, use int as size instead of varint
                        WriteData<Vector<long long int, int>>(arg, container);
                    }
                    else
                    {
                        WriteData<T>(arg, container);
                    }
                }, val);
        }

        Json::Value Tag::SerializeImpl() const
        {
            Json::Value output;

            std::visit([&](auto&& arg)
                {
                    using T = std::decay_t<decltype(arg)>;

                    if constexpr (std::is_same_v<T, TagEnd>)
                    {
                        output["type"] = GetTagName<T>();
                    }
                    else if constexpr (std::is_same_v<T, RecursiveWrapper<TagList>>)
                    {
                        output["type"] = GetTagName<TagList>();
                        output["content"] = arg.get();
                        output["name"] = GetName();
                    }
                    else if constexpr (std::is_same_v<T, RecursiveWrapper<TagCompound>>)
                    {
                        output["type"] = GetTagName<TagCompound>();
                        output["content"] = arg.get();
                        output["name"] = GetName();
                    }
                    else
                    {
                        output["type"] = GetTagName<T>();
                        output["content"] = arg;
                        output["name"] = GetName();
                    }
                }, val);

            return output;
        }

        const Tag& Tag::operator[](const std::string& s) const
        {
            if (!std::holds_alternative<RecursiveWrapper<TagCompound>>(val))
            {
                throw std::runtime_error("NBT::Tag is not a TagCompound");
            }

            return get<TagCompound>().at(s);
        }

        size_t Tag::size() const
        {
            size_t output;

            std::visit([&](auto&& arg)
                {
                    using T = std::decay_t<decltype(arg)>;

                    if constexpr (std::is_same_v<T, RecursiveWrapper<TagList>> ||
                        std::is_same_v<T, RecursiveWrapper<TagCompound>>)
                    {
                        output = arg.get().size();
                    }
                    else if constexpr (
                        std::is_same_v<T, TagByteArray> ||
                        std::is_same_v<T, TagIntArray> ||
                        std::is_same_v<T, TagLongArray>
                    )
                    {
                        output = arg.size();
                    }
                    else
                    {
                        throw std::runtime_error("NBT::Tag is not a container, no size() method implemented");
                    }
                }, val);

            return output;
        }

        bool Tag::contains(const std::string& s) const
        {
            return is<TagCompound>() && get<TagCompound>().count(s);
        }


        void TagList::ReadImpl(ReadIterator& iter, size_t& length)
        {
            const TagType tags_type = static_cast<TagType>(ReadData<char>(iter, length));

            switch (tags_type)
            {
            case TagType::TagEnd:
            {
                const int vector_size = ReadData<int>(iter, length);
                vals = std::vector<TagEnd>(vector_size);
                break;
            }
            case TagType::TagByte:
                // Special case, use int as size instead of varint
                vals = ReadData<Vector<char, int>>(iter, length);
                break;
            case TagType::TagShort:
                // Special case, use int as size instead of varint
                vals = ReadData<Vector<short, int>>(iter, length);
                break;
            case TagType::TagInt:
                // Special case, use int as size instead of varint
                vals = ReadData<Vector<int, int>>(iter, length);
                break;
            case TagType::TagLong:
                // Special case, use int as size instead of varint
                vals = ReadData<Vector<long long int, int>>(iter, length);
                break;
            case TagType::TagFloat:
                // Special case, use int as size instead of varint
                vals = ReadData<Vector<float, int>>(iter, length);
                break;
            case TagType::TagDouble:
                // Special case, use int as size instead of varint
                vals = ReadData<Vector<double, int>>(iter, length);
                break;
            case TagType::TagByteArray:
                // Special case, use int as size instead of varint
                vals = ReadData<Vector<Vector<char, int>, int>>(iter, length);
                break;
            case TagType::TagString:
            {
                std::vector<std::string> values = std::vector<std::string>(ReadData<int>(iter, length));
                for (size_t i = 0; i < values.size(); ++i)
                {
                    values[i] = ReadNBTString(iter, length);
                }
                vals = values;
                break;
            }
            case TagType::TagList:
                // Special case, use int as size instead of varint
                vals = ReadData<Vector<TagList, int>>(iter, length);
                break;
            case TagType::TagCompound:
                // Special case, use int as size instead of varint
                vals = ReadData<Vector<TagCompound, int>>(iter, length);
                break;
            case TagType::TagIntArray:
                // Special case, use int as size instead of varint
                vals = ReadData<Vector<Vector<int, int>, int>>(iter, length);
                break;
            case TagType::TagLongArray:
                // Special case, use int as size instead of varint
                vals = ReadData<Vector<Vector<long long int, int>, int>>(iter, length);
                break;
            default:
                break;
            }
        }

        void TagList::WriteImpl(WriteContainer& container) const
        {
            WriteData<char>(static_cast<char>(vals.index()), container);

            std::visit([&](auto&& arg)
                {
                    using T = std::decay_t<decltype(arg)>;

                    if constexpr (std::is_same_v<T, std::vector<TagEnd>>)
                    {
                        WriteData<int>(static_cast<int>(arg.size()), container);
                    }
                    else if constexpr (std::is_same_v<T, std::vector<TagByteArray>>)
                    {
                        // Special case, use int as size instead of varint
                        WriteData<Vector<Vector<char, int>, int>>(arg, container);
                    }
                    else if constexpr (std::is_same_v<T, std::vector<TagString>>)
                    {
                        WriteData<int>(static_cast<int>(arg.size()), container);
                        for (size_t i = 0; i < arg.size(); ++i)
                        {
                            WriteNBTString(arg[i], container);
                        }
                    }
                    else if constexpr (std::is_same_v<T, std::vector<TagIntArray>>)
                    {
                        // Special case, use int as size instead of varint
                        WriteData<Vector<Vector<int, int>, int>>(arg, container);
                    }
                    else if constexpr (std::is_same_v<T, std::vector<TagLongArray>>)
                    {
                        // Special case, use int as size instead of varint
                        WriteData<Vector<Vector<long long int, int>, int>>(arg, container);
                    }
                    else
                    {
                        // Special case, use int as size instead of varint
                        WriteData<Vector<typename T::value_type, int>>(arg, container);
                    }
                }, vals);
        }

        Json::Value TagList::SerializeImpl() const
        {
            Json::Value output;

            std::visit([&](auto&& arg)
                {
                    using T = std::decay_t<decltype(arg)>;

                    if constexpr (std::is_same_v<T, std::vector<TagEnd>>)
                    {
                        output = Json::Array();
                        for (size_t i = 0; i < arg.size(); ++i)
                        {
                            output.push_back({});
                        }
                    }
                    else
                    {
                        output = arg;
                    }
                }, vals);

            return output;
        }

        size_t TagList::size() const
        {
            size_t output;

            std::visit([&](auto&& arg)
                {
                    output = arg.size();
                }, vals);

            return output;
        }


        const Tag& TagCompound::operator[](const std::string& s) const
        {
            return at(s);
        }

        bool TagCompound::contains(const std::string& s) const
        {
            return count(s) > 0;
        }

        void TagCompound::ReadImpl(ReadIterator& iter, size_t& length)
        {
            while (true)
            {
                const Tag tag = ReadData<Tag>(iter, length);

                // If it's a TagEnd, stop reading data
                if (tag.is<TagEnd>())
                {
                    break;
                }

                // Else insert it
                insert({ tag.GetName(), tag });
            }
        }

        void TagCompound::WriteImpl(WriteContainer& container) const
        {
            // Write each named tag
            for (const auto& p : *this)
            {
                WriteData<Tag>(p.second, container);
            }

            // Add additional end tag
            WriteData<char>(static_cast<char>(TagType::TagEnd), container);
        }

        Json::Value TagCompound::SerializeImpl() const
        {
            // std::map<std::string, Tag> is directly convertible to Json::Value
            // Tag.name will be duplicated as both keys and part of value though
            return *static_cast<const std::map<std::string, Tag>*>(this);
        }


        std::string ReadNBTString(ReadIterator& iter, size_t& length)
        {
            const unsigned short size = ReadData<unsigned short>(iter, length);

            return ReadRawString(iter, length, size);
        }

        void WriteNBTString(const std::string& s, WriteContainer& container)
        {
            WriteData<unsigned short>(static_cast<unsigned short>(s.size()), container);
            WriteRawString(s, container);
        }
    }
}
