#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetSimulationDistancePacket : public BaseMessage<ClientboundSetSimulationDistancePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Simulation Distance";

        SERIALIZED_FIELD(SimulationDistance, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
