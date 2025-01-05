#if PROTOCOL_VERSION > 471 /* > 1.13.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetChunkCacheRadiusPacket : public BaseMessage<ClientboundSetChunkCacheRadiusPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Chunk Cache Radius";

        SERIALIZED_FIELD(Radius, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
