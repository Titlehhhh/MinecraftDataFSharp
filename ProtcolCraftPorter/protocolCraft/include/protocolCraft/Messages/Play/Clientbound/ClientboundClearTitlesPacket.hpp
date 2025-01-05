#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundClearTitlesPacket : public BaseMessage<ClientboundClearTitlesPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Clear Titles";

        SERIALIZED_FIELD(ResetTimes, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
