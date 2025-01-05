#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"

// Use map instead of unordered to avoid another include everywhere
#include <map>
#include <memory>
#include <string_view>

namespace ProtocolCraft
{
    namespace Components
    {
        enum class DataComponentTypes
        {
            None = -1,
            CustomData,
            MaxStackSize,
            MaxDamage,
            Damage,
            Unbreakable,
            CustomName,
            ItemName,
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
            ItemModel,
#endif
            Lore,
            Rarity,
            Enchantments,
            CanPlaceOn,
            CanBreak,
            AttributeModifiers,
            CustomModelData,
            HideAdditionalTooltip,
            HideTooltip,
            RepairCost,
            CreativeSlotLock,
            EnchantmentGlintOverride,
            IntangibleProjectile,
            Food,
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
            FireResistant,
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
            Consumable,
            UseRemainder,
            UseCooldown,
            DamageResistant,
#endif
            Tool,
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
            Enchantable,
            Equippable,
            Repairable,
            Glider,
            TooltipStyle,
            DeathProtection,
#endif
            StoredEnchantments,
            DyedColor,
            MapColor,
            MapId,
            MapDecorations,
            MapPostProcessing,
            ChargedProjectiles,
            BundleContents,
            PotionContents,
            SuspiciousStewEffects,
            WritableBookContent,
            WrittenBookContent,
            Trim,
            DebugStickState,
            EntityData,
            BucketEntityData,
            BlockEntityData,
            Instrument,
            OminousBottleAmplifier,
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
            JukeboxPlayable,
#endif
            Recipes,
            LodestoneTracker,
            FireworkExplosion,
            Fireworks,
            Profile,
            NoteBlockSound,
            BannerPatterns,
            BaseColor,
            PotDecorations,
            Container,
            BlockState,
            Bees,
            Lock,
            ContainerLoot,
            NUM_DATA_COMPONENT_TYPES
        };

        std::string_view DataComponentTypesToString(const DataComponentTypes type);

        class DataComponentType;

        class DataComponentPredicate : public NetworkType
        {
        public:
            virtual ~DataComponentPredicate() override;

            const std::map<DataComponentTypes, std::shared_ptr<DataComponentType>>& GetMap() const;
            DataComponentPredicate& SetMap(const std::map<DataComponentTypes, std::shared_ptr<DataComponentType>>& map_);

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override;
            virtual void WriteImpl(WriteContainer& container) const override;
            virtual Json::Value SerializeImpl() const override;

        private:
            std::map<DataComponentTypes, std::shared_ptr<DataComponentType>> map;

        };

        class DataComponentPatch : public NetworkType
        {
        public:
            virtual ~DataComponentPatch() override;

            const std::map<DataComponentTypes, std::shared_ptr<DataComponentType>>& GetMap() const;
            DataComponentPatch& SetMap(const std::map<DataComponentTypes, std::shared_ptr<DataComponentType>>& map_);

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override;
            virtual void WriteImpl(WriteContainer& container) const override;
            virtual Json::Value SerializeImpl() const override;

        private:
            std::map<DataComponentTypes, std::shared_ptr<DataComponentType>> map;

        };
    }
}
#endif
