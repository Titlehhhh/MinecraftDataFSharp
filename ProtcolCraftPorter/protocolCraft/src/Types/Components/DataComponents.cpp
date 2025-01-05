#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponents.hpp"
#include "protocolCraft/Types/Components/DataComponentType.hpp"

#include "protocolCraft/Types/Components/DataComponentTypeAdventureModePredicate.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeArmorTrim.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeBannerPatternLayers.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeBlockItemStateProperties.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeBoolean.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeBundleContents.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeChargedProjectiles.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeComponent.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeCustomData.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeCustomModelData.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeDefault.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeDyeColor.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeDyedItemColor.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeFireworkExplosion.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeFireworks.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeFoodProperties.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeHolderInstrument.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeInteger.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeItemAttributeModifiers.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeItemContainerContents.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeItemEnchantments.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeItemLore.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeListBeehiveBlockEntityOccupant.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeLodestoneTracker.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeMapId.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeMapItemColor.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeMapPostProcessing.hpp"
#include "protocolCraft/Types/Components/DataComponentTypePotDecorations.hpp"
#include "protocolCraft/Types/Components/DataComponentTypePotionContents.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeRarity.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeResolvableProfile.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeResourceLocation.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeSuspiciousStewEffects.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeTool.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeUnbreakable.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeUnit.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeWritableBookContent.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeWrittenBookContent.hpp"
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#include "protocolCraft/Types/Components/DataComponentTypeJukeboxPlayable.hpp"
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "protocolCraft/Types/Components/DataComponentTypeConsumable.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeDeathProtection.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeEquippable.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeRepairable.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeUseCooldown.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeUseRemainder.hpp"
#endif

#include "protocolCraft/Utilities/AutoSerializedToJson.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        DEFINE_NETWORK_TYPE(ExactMatcher);
        DEFINE_NETWORK_TYPE(RangedMatcher);
        DEFINE_NETWORK_TYPE(AttributeModifier);
        DEFINE_NETWORK_TYPE(BannerPatternLayer);
        DEFINE_NETWORK_TYPE(BlockPredicate);
        DEFINE_NETWORK_TYPE(ItemAttributeModifiersEntry);
        DEFINE_NETWORK_TYPE(MobEffectInstance);
        DEFINE_NETWORK_TYPE(MobEffectInstanceDetails);
        DEFINE_NETWORK_TYPE(PossibleEffect);
        DEFINE_NETWORK_TYPE(StatePropertiesPredicate);
        DEFINE_NETWORK_TYPE(SuspiciousStewEntry);
        DEFINE_NETWORK_TYPE(ToolRule);
        DEFINE_NETWORK_TYPE(PropertyMatcher);

        DEFINE_NETWORK_TYPE(DataComponentTypeAdventureModePredicate);
        DEFINE_NETWORK_TYPE(DataComponentTypeArmorTrim);
        DEFINE_NETWORK_TYPE(DataComponentTypeBannerPatternLayers);
        DEFINE_NETWORK_TYPE(DataComponentTypeBlockItemStateProperties);
        DEFINE_NETWORK_TYPE(DataComponentTypeBoolean);
        DEFINE_NETWORK_TYPE(DataComponentTypeBundleContents);
        DEFINE_NETWORK_TYPE(DataComponentTypeChargedProjectiles);
        DEFINE_NETWORK_TYPE(DataComponentTypeComponent);
        DEFINE_NETWORK_TYPE(DataComponentTypeCustomData);
        DEFINE_NETWORK_TYPE(DataComponentTypeCustomModelData);
        DEFINE_NETWORK_TYPE(DataComponentTypeDefault);
        DEFINE_NETWORK_TYPE(DataComponentTypeDyeColor);
        DEFINE_NETWORK_TYPE(DataComponentTypeDyedItemColor);
        DEFINE_NETWORK_TYPE(DataComponentTypeFireworkExplosion);
        DEFINE_NETWORK_TYPE(DataComponentTypeFireworks);
        DEFINE_NETWORK_TYPE(DataComponentTypeFoodProperties);
        DEFINE_NETWORK_TYPE(DataComponentTypeHolderInstrument);
        DEFINE_NETWORK_TYPE(DataComponentTypeInteger);
        DEFINE_NETWORK_TYPE(DataComponentTypeItemAttributeModifiers);
        DEFINE_NETWORK_TYPE(DataComponentTypeItemContainerContents);
        DEFINE_NETWORK_TYPE(DataComponentTypeItemEnchantments);
        DEFINE_NETWORK_TYPE(DataComponentTypeItemLore);
        DEFINE_NETWORK_TYPE(DataComponentTypeListBeehiveBlockEntityOccupant);
        DEFINE_NETWORK_TYPE(DataComponentTypeLodestoneTracker);
        DEFINE_NETWORK_TYPE(DataComponentTypeMapId);
        DEFINE_NETWORK_TYPE(DataComponentTypeMapItemColor);
        DEFINE_NETWORK_TYPE(DataComponentTypeMapPostProcessing);
        DEFINE_NETWORK_TYPE(DataComponentTypePotDecorations);
        DEFINE_NETWORK_TYPE(DataComponentTypePotionContents);
        DEFINE_NETWORK_TYPE(DataComponentTypeRarity);
        DEFINE_NETWORK_TYPE(DataComponentTypeResolvableProfile);
        DEFINE_NETWORK_TYPE(DataComponentTypeResourceLocation);
        DEFINE_NETWORK_TYPE(DataComponentTypeSuspiciousStewEffects);
        DEFINE_NETWORK_TYPE(DataComponentTypeTool);
        DEFINE_NETWORK_TYPE(DataComponentTypeUnbreakable);
        DEFINE_NETWORK_TYPE(DataComponentTypeUnit);
        DEFINE_NETWORK_TYPE(DataComponentTypeWritableBookContent);
        DEFINE_NETWORK_TYPE(DataComponentTypeWrittenBookContent);
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
        DEFINE_NETWORK_TYPE(DataComponentTypeJukeboxPlayable);
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        DEFINE_NETWORK_TYPE(DataComponentTypeConsumable);
        DEFINE_NETWORK_TYPE(DataComponentTypeDeathProtection);
        DEFINE_NETWORK_TYPE(DataComponentTypeEquippable);
        DEFINE_NETWORK_TYPE(DataComponentTypeRepairable);
        DEFINE_NETWORK_TYPE(DataComponentTypeUseCooldown);
        DEFINE_NETWORK_TYPE(DataComponentTypeUseRemainder);
#endif

        std::string_view DataComponentTypesToString(const DataComponentTypes type)
        {
            static constexpr std::array<std::string_view, static_cast<size_t>(DataComponentTypes::NUM_DATA_COMPONENT_TYPES)> names = {
                "custom_data",
                "max_stack_size",
                "max_damage",
                "damage",
                "unbreakable",
                "custom_name",
                "item_name",
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
                "item_model",
#endif
                "lore",
                "rarity",
                "enchantments",
                "can_place_on",
                "can_break",
                "attribute_modifiers",
                "custom_model_data",
                "hide_additional_tooltip",
                "hide_tooltip",
                "repair_cost",
                "creative_slot_lock",
                "enchantment_glint_override",
                "intangible_projectile",
                "food",
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
                "fire_resistant",
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
                "consumable",
                "use_remainder",
                "use_cooldown",
                "damage_resistant",
#endif
                "tool",
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
                "enchantable",
                "equippable",
                "repairable",
                "glider",
                "tooltip_style",
                "death_protection",
#endif
                "stored_enchantments",
                "dyed_color",
                "map_color",
                "map_id",
                "map_decorations",
                "map_post_processing",
                "charged_projectiles",
                "bundle_contents",
                "potion_contents",
                "suspicious_stew_effects",
                "writable_book_content",
                "written_book_content",
                "trim",
                "debug_stick_state",
                "entity_data",
                "bucket_entity_data",
                "block_entity_data",
                "instrument",
                "ominous_bottle_amplifier",
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
                "jukebox_playable",
#endif
                "recipes",
                "lodestone_tracker",
                "firework_explosion",
                "fireworks",
                "profile",
                "note_block_sound",
                "banner_patterns",
                "base_color",
                "pot_decorations",
                "container",
                "block_state",
                "bees",
                "lock",
                "container_loot",
            };
            if (type <= DataComponentTypes::None || type >= DataComponentTypes::NUM_DATA_COMPONENT_TYPES)
            {
                return "";
            }
            return names[static_cast<size_t>(type)];
        }

        std::shared_ptr<DataComponentType> CreateComponentType(const DataComponentTypes type)
        {
            if (type <= DataComponentTypes::None || type >= DataComponentTypes::NUM_DATA_COMPONENT_TYPES)
            {
                throw std::runtime_error("Unable to create data component with id: " + std::to_string(static_cast<int>(type)) + ".");
            }

            switch (type)
            {
            case DataComponentTypes::CanPlaceOn:
            case DataComponentTypes::CanBreak:
                return std::make_shared<DataComponentTypeAdventureModePredicate>();
            case DataComponentTypes::Trim:
                return std::make_shared<DataComponentTypeArmorTrim>();
            case DataComponentTypes::BannerPatterns:
                return std::make_shared<DataComponentTypeBannerPatternLayers>();
            case DataComponentTypes::BlockState:
                return std::make_shared<DataComponentTypeBlockItemStateProperties>();
            case DataComponentTypes::EnchantmentGlintOverride:
                return std::make_shared<DataComponentTypeBoolean>();
            case DataComponentTypes::BundleContents:
                return std::make_shared<DataComponentTypeBundleContents>();
            case DataComponentTypes::ChargedProjectiles:
                return std::make_shared<DataComponentTypeChargedProjectiles>();
            case DataComponentTypes::CustomName:
            case DataComponentTypes::ItemName:
                return std::make_shared<DataComponentTypeComponent>();
            case DataComponentTypes::BlockEntityData:
            case DataComponentTypes::BucketEntityData:
            case DataComponentTypes::EntityData:
                return std::make_shared<DataComponentTypeCustomData>();
            case DataComponentTypes::CustomModelData:
                return std::make_shared<DataComponentTypeCustomModelData>();
            case DataComponentTypes::CustomData:
            case DataComponentTypes::IntangibleProjectile:
            case DataComponentTypes::MapDecorations:
            case DataComponentTypes::DebugStickState:
            case DataComponentTypes::Recipes:
            case DataComponentTypes::Lock:
            case DataComponentTypes::ContainerLoot:
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
            case DataComponentTypes::Glider:
#endif
                // Component with no network serializer specified fallback to NBT
                return std::make_shared<DataComponentTypeDefault>();
            case DataComponentTypes::BaseColor:
                return std::make_shared<DataComponentTypeDyeColor>();
            case DataComponentTypes::DyedColor:
                return std::make_shared<DataComponentTypeDyedItemColor>();
            case DataComponentTypes::FireworkExplosion:
                return std::make_shared<DataComponentTypeFireworkExplosion>();
            case DataComponentTypes::Fireworks:
                return std::make_shared<DataComponentTypeFireworks>();
            case DataComponentTypes::Food:
                return std::make_shared<DataComponentTypeFoodProperties>();
            case DataComponentTypes::Instrument:
                return std::make_shared<DataComponentTypeHolderInstrument>();
            case DataComponentTypes::MaxStackSize:
            case DataComponentTypes::MaxDamage:
            case DataComponentTypes::Damage:
            case DataComponentTypes::RepairCost:
            case DataComponentTypes::OminousBottleAmplifier:
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
            case DataComponentTypes::Enchantable:
#endif
                return std::make_shared<DataComponentTypeInteger>();
            case DataComponentTypes::AttributeModifiers:
                return std::make_shared<DataComponentTypeItemAttributeModifiers>();
            case DataComponentTypes::Container:
                return std::make_shared<DataComponentTypeItemContainerContents>();
            case DataComponentTypes::Enchantments:
            case DataComponentTypes::StoredEnchantments:
                return std::make_shared<DataComponentTypeItemEnchantments>();
            case DataComponentTypes::Lore:
                return std::make_shared<DataComponentTypeItemLore>();
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
            case DataComponentTypes::JukeboxPlayable:
                return std::make_shared<DataComponentTypeJukeboxPlayable>();
#endif
            case DataComponentTypes::Bees:
                return std::make_shared<DataComponentTypeListBeehiveBlockEntityOccupant>();
            case DataComponentTypes::LodestoneTracker:
                return std::make_shared<DataComponentTypeLodestoneTracker>();
            case DataComponentTypes::MapId:
                return std::make_shared<DataComponentTypeMapId>();
            case DataComponentTypes::MapColor:
                return std::make_shared<DataComponentTypeMapItemColor>();
            case DataComponentTypes::MapPostProcessing:
                return std::make_shared<DataComponentTypeMapPostProcessing>();
            case DataComponentTypes::PotDecorations:
                return std::make_shared<DataComponentTypePotDecorations>();
            case DataComponentTypes::PotionContents:
                return std::make_shared<DataComponentTypePotionContents>();
            case DataComponentTypes::Rarity:
                return std::make_shared<DataComponentTypeRarity>();
            case DataComponentTypes::Profile:
                return std::make_shared<DataComponentTypeResolvableProfile>();
            case DataComponentTypes::NoteBlockSound:
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
            case DataComponentTypes::DamageResistant:
            case DataComponentTypes::ItemModel:
            case DataComponentTypes::TooltipStyle:
#endif
                return std::make_shared<DataComponentTypeResourceLocation>();
            case DataComponentTypes::SuspiciousStewEffects:
                return std::make_shared<DataComponentTypeSuspiciousStewEffects>();
            case DataComponentTypes::Tool:
                return std::make_shared<DataComponentTypeTool>();
            case DataComponentTypes::Unbreakable:
                return std::make_shared<DataComponentTypeUnbreakable>();
            case DataComponentTypes::HideAdditionalTooltip:
            case DataComponentTypes::HideTooltip:
            case DataComponentTypes::CreativeSlotLock:
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
            case DataComponentTypes::FireResistant:
#endif
                return std::make_shared<DataComponentTypeUnit>();
            case DataComponentTypes::WritableBookContent:
                return std::make_shared<DataComponentTypeWritableBookContent>();
            case DataComponentTypes::WrittenBookContent:
                return std::make_shared<DataComponentTypeWrittenBookContent>();
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
            case DataComponentTypes::Consumable:
                return std::make_shared<DataComponentTypeConsumable>();
            case DataComponentTypes::DeathProtection:
                return std::make_shared<DataComponentTypeDeathProtection>();
            case DataComponentTypes::Equippable:
                return std::make_shared<DataComponentTypeEquippable>();
            case DataComponentTypes::Repairable:
                return std::make_shared<DataComponentTypeRepairable>();
            case DataComponentTypes::UseCooldown:
                return std::make_shared<DataComponentTypeUseCooldown>();
            case DataComponentTypes::UseRemainder:
                return std::make_shared<DataComponentTypeUseRemainder>();
#endif
            default:
                // Should never happen but will make the compilers happy
                throw std::runtime_error("Unable to create data component with id: " + std::to_string(static_cast<int>(type)) + ".");
            }
        }

        DataComponentPredicate::~DataComponentPredicate()
        {

        }

        const std::map<DataComponentTypes, std::shared_ptr<DataComponentType>>& DataComponentPredicate::GetMap() const
        {
            return map;
        }

        DataComponentPredicate& DataComponentPredicate::SetMap(const std::map<DataComponentTypes, std::shared_ptr<DataComponentType>>& map_)
        {
            map = map_;
            return *this;
        }

        void DataComponentPredicate::ReadImpl(ReadIterator& iter, size_t& length)
        {
            // special case, dynamic factory
            const int map_size = ReadData<VarInt>(iter, length);
            map.clear();
            for (int i = 0; i < map_size; ++i)
            {
                const DataComponentTypes k = ReadData<DataComponentTypes, VarInt>(iter, length);
                std::shared_ptr<DataComponentType> v = CreateComponentType(k);
                if (v != nullptr)
                {
                    v->Read(iter, length);
                }
                map[k] = v;
            }
        }

        void DataComponentPredicate::WriteImpl(WriteContainer& container) const
        {
            // special case, dynamic factory
            WriteData<VarInt>(static_cast<int>(map.size()), container);
            for (const auto& [k, v] : map)
            {
                WriteData<DataComponentTypes, VarInt>(k, container);
                if (v != nullptr)
                {
                    v->Write(container);
                }
            }
        }

        Json::Value DataComponentPredicate::SerializeImpl() const
        {
            Json::Value output;

            output["map"] = Json::Array();
            for (const auto& p : map)
            {
                output["map"].push_back({
                    { "name", DataComponentTypesToString(p.first) },
                    { "data", p.second == nullptr ? nullptr : p.second->Serialize() }
                });
            }

            return output;
        }


        DataComponentPatch::~DataComponentPatch()
        {

        }

        const std::map<DataComponentTypes, std::shared_ptr<DataComponentType>>& DataComponentPatch::GetMap() const
        {
            return map;
        }

        DataComponentPatch& DataComponentPatch::SetMap(const std::map<DataComponentTypes, std::shared_ptr<DataComponentType>>& map_)
        {
            map = map_;
            return *this;
        }

        void DataComponentPatch::ReadImpl(ReadIterator& iter, size_t& length)
        {
            const int num_data = ReadData<VarInt>(iter, length);
            const int num_void = ReadData<VarInt>(iter, length);

            map.clear();

            for (int i = 0; i < num_data; ++i)
            {
                const DataComponentTypes type = ReadData<DataComponentTypes, VarInt>(iter, length);
                std::shared_ptr<DataComponentType> data = CreateComponentType(type);

                if (data != nullptr)
                {
                    data->Read(iter, length);
                }
                map.insert({ type, data });
            }

            for (int i = 0; i < num_void; ++i)
            {
                const DataComponentTypes type = ReadData<DataComponentTypes, VarInt>(iter, length);
                map.insert({ type, nullptr });
            }
        }

        void DataComponentPatch::WriteImpl(WriteContainer& container) const
        {
            int num_data = 0;
            for (const auto& p : map)
            {
                num_data += p.second != nullptr;
            }
            const int num_void = static_cast<int>(map.size()) - num_data;

            WriteData<VarInt>(num_data, container);
            WriteData<VarInt>(num_void, container);

            for (const auto& p : map)
            {
                if (p.second == nullptr)
                {
                    continue;
                }
                WriteData<DataComponentTypes, VarInt>(p.first, container);
                p.second->Write(container);
            }

            for (const auto& p : map)
            {
                if (p.second != nullptr)
                {
                    continue;
                }
                WriteData<DataComponentTypes, VarInt>(p.first, container);
            }
        }

        Json::Value DataComponentPatch::SerializeImpl() const
        {
            Json::Value output;

            output["map"] = Json::Array();
            for (const auto& p : map)
            {
                output["map"].push_back({
                    { "name", DataComponentTypesToString(p.first) },
                    { "data", p.second == nullptr ? nullptr : p.second->Serialize() }
                });
            }

            return output;
        }
    }
}
#endif
