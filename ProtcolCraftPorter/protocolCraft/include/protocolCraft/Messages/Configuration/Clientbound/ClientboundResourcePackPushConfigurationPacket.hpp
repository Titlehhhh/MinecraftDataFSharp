#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundResourcePackPushConfigurationPacket : public BaseMessage<ClientboundResourcePackPushConfigurationPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Resource Pack Push (Configuration)";

        SERIALIZED_FIELD(Uuid, UUID);
        SERIALIZED_FIELD(Url, std::string);
        SERIALIZED_FIELD(Hash, std::string);
        SERIALIZED_FIELD(Required, bool);
        SERIALIZED_FIELD(Prompt, std::optional<Chat>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
