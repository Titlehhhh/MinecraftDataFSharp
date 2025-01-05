#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundSwingPacket : public BaseMessage<ServerboundSwingPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Swing";

        SERIALIZED_FIELD(Hand, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
