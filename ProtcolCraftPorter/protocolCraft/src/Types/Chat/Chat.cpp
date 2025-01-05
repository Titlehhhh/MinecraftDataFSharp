#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
    std::string Chat::ParseChat(const Json::Value& raw_json)
    {
        if (raw_json.is_object())
        {
            std::string output = "";

            if (raw_json.contains("text"))
            {
                // It should always be text but just in case
                if (raw_json["text"].is_string())
                {
                    output += raw_json["text"].get_string();
                }
            }
            // TODO: deal with other translate types for completeness
            else if (raw_json.contains("translate") && raw_json["translate"].is_string() && raw_json["translate"].get_string() == "chat.type.text")
            {
                // It *should* be <%s> %s, so we only need with[1]
                if (raw_json.contains("with") && raw_json["with"].is_array() && raw_json["with"].size() > 1)
                {
                    output += ParseChat(raw_json["with"][1]);
                }
            }
            else
            {
                // TODO: deal with other type of content (NBT, scoreboard, selector, keybind)
            }

            // Add extra
            if (raw_json.contains("extra") && raw_json["extra"].is_array())
            {
                output += ParseChat(raw_json["extra"]);
            }

            return output;
        }

        if (raw_json.is_null())
        {
            return "";
        }

        if (raw_json.is_string())
        {
            return raw_json.get_string();
        }

        if (raw_json.is_bool())
        {
            return raw_json.get<bool>() ? "true" : "false";
        }

        if (raw_json.is_number())
        {
            return std::to_string(raw_json.get_number());
        }

        if (raw_json.is_array())
        {
            std::string output = "";

            for (const auto& s : raw_json.get_array())
            {
                output += ParseChat(s);
            }
            return output;
        }

        return "";
    }
#else
    std::string Chat::ParseChat(const NBT::TagCompound& raw)
    {
        std::string output = "";

        if (raw.contains("text") && raw["text"].is<NBT::TagString>())
        {
            output += raw["text"].get<NBT::TagString>();
        }
        else if (raw.size() == 1 && raw.contains("") && raw[""].is<NBT::TagString>())
        {
            output += raw[""].get<NBT::TagString>();
        }
        else
        {
            // TODO: do we need to process other types of items to get parsed text?
        }

        // Add extra
        if (raw.contains("extra") && raw["extra"].is_list_of<NBT::TagCompound>())
        {
            for (const auto& t : raw["extra"].as_list_of<NBT::TagCompound>())
            output += ParseChat(t);
        }

        return output;
    }
#endif
}
