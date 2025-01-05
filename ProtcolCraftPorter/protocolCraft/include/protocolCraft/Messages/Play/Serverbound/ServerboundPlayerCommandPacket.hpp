#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPlayerCommandPacket : public BaseMessage<ServerboundPlayerCommandPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Player Command";

        SERIALIZED_FIELD(Id_, VarInt);
        SERIALIZED_FIELD(Action, VarInt);
        SERIALIZED_FIELD(Data, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
