#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundContainerClosePacket : public BaseMessage<ClientboundContainerClosePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Container Close";

#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        SERIALIZED_FIELD(ContainerId, unsigned char);
#else
        SERIALIZED_FIELD(ContainerId, VarInt);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
