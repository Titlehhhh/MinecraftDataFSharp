#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Identifier.hpp"
#include "protocolCraft/Types/Holder.hpp"
#include "protocolCraft/Types/Sound/SoundEvent.hpp"
#include "protocolCraft/Types/HolderSet.hpp"

#include <optional>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeEquippable : public DataComponentType
        {
            SERIALIZED_FIELD(Slot, VarInt);
            SERIALIZED_FIELD(EquipSound, Holder<SoundEvent>);
            SERIALIZED_FIELD(Model, std::optional<Identifier>);
            SERIALIZED_FIELD(CameraOverlay, std::optional<Identifier>);
            SERIALIZED_FIELD(AllowedEntities, std::optional<HolderSet>);
            SERIALIZED_FIELD(Dispensable, bool);
            SERIALIZED_FIELD(Swappable, bool);
            SERIALIZED_FIELD(DamageOnHurt, bool);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
