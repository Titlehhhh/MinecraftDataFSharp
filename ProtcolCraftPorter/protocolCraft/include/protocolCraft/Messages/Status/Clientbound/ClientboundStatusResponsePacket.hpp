#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundStatusResponsePacket : public BaseMessage<ClientboundStatusResponsePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Status Response";

        SERIALIZED_FIELD(Status, std::string);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
