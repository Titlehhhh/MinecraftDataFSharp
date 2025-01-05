#if PROTOCOL_VERSION < 476 /* < 1.14 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundEnchantItemPacket : public BaseMessage<ServerboundEnchantItemPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Enchant item";

        SERIALIZED_FIELD(ContainerId, char);
        SERIALIZED_FIELD(Enchantment, char);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
