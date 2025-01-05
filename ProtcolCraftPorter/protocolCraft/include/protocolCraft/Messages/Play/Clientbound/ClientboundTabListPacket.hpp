#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundTabListPacket : public BaseMessage<ClientboundTabListPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Tab List";

        SERIALIZED_FIELD(Header, Chat);
        SERIALIZED_FIELD(Footer, Chat);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
