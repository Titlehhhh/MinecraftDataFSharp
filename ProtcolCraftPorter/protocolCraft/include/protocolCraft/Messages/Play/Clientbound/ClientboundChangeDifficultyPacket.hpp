#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundChangeDifficultyPacket : public BaseMessage<ClientboundChangeDifficultyPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Change Difficulty";

        SERIALIZED_FIELD(Difficulty, unsigned char);
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        SERIALIZED_FIELD(Locked, bool);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
