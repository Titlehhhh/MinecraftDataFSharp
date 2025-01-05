﻿public static class Ext
{
    public static int GetServerboundPlayPacket(int version, string packet)
    {
        return Ext.ServerboundPlayPackets(version).IndexOf("Serverbound" + packet);
    }

    public static int GetClientboundPlayPacket(int version, string packet)
    {
        return Ext.ClientboundPlayPackets(version).IndexOf("Clientbound" + packet);
    }

    public static int GetClientboundConfigPacket(int version, string packet)
    {
        return Ext.ClientboundConfigurationPackets(version).IndexOf("Clientbound" + packet);
    }

    public static int GetServerboundConfigPacket(int version, string packet)
    {
        return Ext.ServerboundConfigurationPackets(version).IndexOf("Serverbound" + packet);
    }

    public static int GetClientboundLoginPacket(int version, string packet)
    {
        return Ext.ClientboundLoginPackets(version).IndexOf("Clientbound" + packet);
    }

    public static int GetServerboundLoginPacket(int version, string packet)
    {
        return Ext.ServerboundLoginPackets(version).IndexOf("Serverbound" + packet);
    }
    
    public static List<string> ServerboundPlayPackets(int protocolVersion)
    {
        List<string> result = new();

        result.Add("ServerboundAcceptTeleportationPacket");
        if (protocolVersion > 340 /* > 1.12.2 */)
        {
            result.Add("ServerboundBlockEntityTagQueryPacket");
        }

        if (protocolVersion > 767 /* > 1.21.1 */)
        {
            result.Add("ServerboundSelectBundleItemPacket");
        }

        if (protocolVersion < 393 /* < 1.13 */)
        {
            result.Add("ServerboundCommandSuggestionPacket");
        }

        if (protocolVersion > 404 /* > 1.13.2 */)
        {
            result.Add("ServerboundChangeDifficultyPacket");
        }

        if (protocolVersion > 759 /* > 1.19 */)
        {
            result.Add("ServerboundChatAckPacket");
        }

        if (protocolVersion > 758 /* > 1.18.2 */)
        {
            result.Add("ServerboundChatCommandPacket");
        }

        if (protocolVersion > 765 /* > 1.20.4 */)
        {
            result.Add("ServerboundChatCommandSignedPacket");
        }

        result.Add("ServerboundChatPacket");
        if (protocolVersion > 758 /* > 1.18.2 */ && protocolVersion < 761 /* < 1.19.3 */)
        {
            result.Add("ServerboundChatPreviewPacket");
        }

        if (protocolVersion > 761 /* > 1.19.3 */)
        {
            result.Add("ServerboundChatSessionUpdatePacket");
        }

        if (protocolVersion > 763 /* > 1.20.1 */)
        {
            result.Add("ServerboundChunkBatchReceivedPacket");
        }

        result.Add("ServerboundClientCommandPacket");
        if (protocolVersion > 767 /* > 1.21.1 */)
        {
            result.Add("ServerboundClientTickEndPacket");
        }

        result.Add("ServerboundClientInformationPacket");
        if (protocolVersion > 340 /* > 1.12.2 */)
        {
            result.Add("ServerboundCommandSuggestionPacket");
        }

        if (protocolVersion > 763 /* > 1.20.1 */)
        {
            result.Add("ServerboundConfigurationAcknowledgedPacket");
        }

        if (protocolVersion < 755 /* < 1.17 */)
        {
            result.Add("ServerboundContainerAckPacket");
        }

        if (protocolVersion > 404 /* > 1.13.2 */)
        {
            result.Add("ServerboundContainerButtonClickPacket");
        }

        if (protocolVersion < 477 /* < 1.14 */)
        {
            result.Add("ServerboundEnchantItemPacket");
        }

        result.Add("ServerboundContainerClickPacket");
        result.Add("ServerboundContainerClosePacket");
        if (protocolVersion > 764 /* > 1.20.2 */)
        {
            result.Add("ServerboundContainerSlotStateChangedPacket");
        }

        if (protocolVersion > 765 /* > 1.20.4 */)
        {
            result.Add("ServerboundCookieResponsePacket");
        }

        result.Add("ServerboundCustomPayloadPacket");
        if (protocolVersion > 765 /* > 1.20.4 */)
        {
            result.Add("ServerboundDebugSampleSubscriptionPacket");
        }

        if (protocolVersion > 340 /* > 1.12.2 */)
        {
            result.Add("ServerboundEditBookPacket");
            result.Add("ServerboundEntityTagQueryPacket");
        }

        result.Add("ServerboundInteractPacket");
        if (protocolVersion > 578 /* > 1.15.2 */)
        {
            result.Add("ServerboundJigsawGeneratePacket");
        }

        result.Add("ServerboundKeepAlivePacket");
        if (protocolVersion > 404 /* > 1.13.2 */)
        {
            result.Add("ServerboundLockDifficultyPacket");
        }

        if (protocolVersion < 477 /* < 1.14 */)
        {
            result.Add("ServerboundMovePlayerPacket");
        }

        result.Add("ServerboundMovePlayerPacketPos");
        result.Add("ServerboundMovePlayerPacketPosRot");
        result.Add("ServerboundMovePlayerPacketRot");
        if (protocolVersion > 404 /* > 1.13.2 */ && protocolVersion < 755 /* < 1.17 */)
        {
            result.Add("ServerboundMovePlayerPacket");
        }

        if (protocolVersion > 754 /* > 1.16.5 */)
        {
            result.Add("ServerboundMovePlayerPacketStatusOnly");
        }

        result.Add("ServerboundMoveVehiclePacket");
        result.Add("ServerboundPaddleBoatPacket");
        if (protocolVersion > 768 /* > 1.21.3 */)
        {
            result.Add("ServerboundPickItemFromBlockPacket");
            result.Add("ServerboundPickItemFromEntityPacket");
        }

        if (protocolVersion > 340 /* > 1.12.2 */ && protocolVersion < 769 /* < 1.21.4 */)
        {
            result.Add("ServerboundPickItemPacket");
        }

        if (protocolVersion > 763 /* > 1.20.1 */)
        {
            result.Add("ServerboundPingRequestPacket");
        }

        result.Add("ServerboundPlaceRecipePacket");
        result.Add("ServerboundPlayerAbilitiesPacket");
        result.Add("ServerboundPlayerActionPacket");
        result.Add("ServerboundPlayerCommandPacket");
        result.Add("ServerboundPlayerInputPacket");
        if (protocolVersion > 768 /* > 1.21.3 */)
        {
            result.Add("ServerboundPlayerLoadedPacket");
        }

        if (protocolVersion > 754 /* > 1.16.5 */)
        {
            result.Add("ServerboundPongPacket");
        }

        if (protocolVersion > 760 /* > 1.19.2 */ && protocolVersion < 762 /* < 1.19.4 */)
        {
            result.Add("ServerboundChatSessionUpdatePacket");
        }

        if (protocolVersion < 751 /* < 1.16.2 */)
        {
            result.Add("ServerboundRecipeBookUpdatePacket");
        }

        if (protocolVersion > 736 /* > 1.16.1 */)
        {
            result.Add("ServerboundRecipeBookChangeSettingsPacket");
            result.Add("ServerboundRecipeBookSeenRecipePacket");
        }

        if (protocolVersion > 340 /* > 1.12.2 */)
        {
            result.Add("ServerboundRenameItemPacket");
        }

        result.Add("ServerboundResourcePackPacket");
        result.Add("ServerboundSeenAdvancementsPacket");
        if (protocolVersion > 340 /* > 1.12.2 */)
        {
            result.Add("ServerboundSelectTradePacket");
            result.Add("ServerboundSetBeaconPacket");
        }

        result.Add("ServerboundSetCarriedItemPacket");
        if (protocolVersion > 340 /* > 1.12.2 */)
        {
            result.Add("ServerboundSetCommandBlockPacket");
            result.Add("ServerboundSetCommandMinecartPacket");
        }

        result.Add("ServerboundSetCreativeModeSlotPacket");
        if (protocolVersion > 404 /* > 1.13.2 */)
        {
            result.Add("ServerboundSetJigsawBlockPacket");
        }

        if (protocolVersion > 340 /* > 1.12.2 */)
        {
            result.Add("ServerboundSetStructureBlockPacket");
        }

        result.Add("ServerboundSignUpdatePacket");
        result.Add("ServerboundSwingPacket");
        result.Add("ServerboundTeleportToEntityPacket");
        result.Add("ServerboundUseItemOnPacket");
        result.Add("ServerboundUseItemPacket");
        return result;
    }

    public static List<string> ClientboundPlayPackets(int protocolVersion)
    {
        List<string> result = new();
        if (protocolVersion > 761 /* > 1.19.3 */)
        {
            result.Add("ClientboundBundlePacket");
        }

        result.Add("ClientboundAddEntityPacket");
        result.Add("ClientboundAddExperienceOrbPacket");
        if (protocolVersion < 735 /* < 1.16 */)
        {
            result.Add("ClientboundAddGlobalEntityPacket");
        }

        if (protocolVersion < 759 /* < 1.19 */)
        {
            result.Add("ClientboundAddMobPacket");
            result.Add("ClientboundAddPaintingPacket");
        }

        if (protocolVersion < 764 /* < 1.20.2 */)
        {
            result.Add("ClientboundAddPlayerPacket");
        }

        if (protocolVersion > 754 /* > 1.16.5 */ && protocolVersion < 759 /* < 1.19 */)
        {
            result.Add("ClientboundAddVibrationSignalPacket");
        }

        result.Add("ClientboundAnimatePacket");
        result.Add("ClientboundAwardStatsPacket");
        if (protocolVersion > 758 /* > 1.18.2 */)
        {
            result.Add("ClientboundBlockChangedAckPacket");
        }

        if (protocolVersion > 498 /* > 1.14.4 */ && protocolVersion < 759 /* < 1.19 */)
        {
            result.Add("ClientboundBlockBreakAckPacket");
        }

        result.Add("ClientboundBlockDestructionPacket");
        result.Add("ClientboundBlockEntityDataPacket");
        result.Add("ClientboundBlockEventPacket");
        result.Add("ClientboundBlockUpdatePacket");
        result.Add("ClientboundBossEventPacket");
        result.Add("ClientboundChangeDifficultyPacket");
        if (protocolVersion > 763 /* > 1.20.1 */)
        {
            result.Add("ClientboundChunkBatchFinishedPacket");
            result.Add("ClientboundChunkBatchStartPacket");
        }

        if (protocolVersion > 761 /* > 1.19.3 */)
        {
            result.Add("ClientboundChunksBiomesPacket");
        }

        if (protocolVersion > 758 /* > 1.18.2 */ && protocolVersion < 761 /* < 1.19.3 */)
        {
            result.Add("ClientboundChatPreviewPacket");
        }

        if (protocolVersion < 393 /* < 1.13 */)
        {
            result.Add("ClientboundCommandSuggestionsPacket");
        }

        if (protocolVersion < 759 /* < 1.19 */)
        {
            result.Add("ClientboundChatPacket");
        }

        if (protocolVersion > 754 /* > 1.16.5 */)
        {
            result.Add("ClientboundClearTitlesPacket");
        }

        if (protocolVersion < 751 /* < 1.16.2 */)
        {
            result.Add("ClientboundSectionBlocksUpdatePacket");
        }

        if (protocolVersion > 340 /* > 1.12.2 */)
        {
            result.Add("ClientboundCommandSuggestionsPacket");
            result.Add("ClientboundCommandsPacket");
        }

        if (protocolVersion < 755 /* < 1.17 */)
        {
            result.Add("ClientboundContainerAckPacket");
        }

        result.Add("ClientboundContainerClosePacket");
        if (protocolVersion < 477 /* < 1.14 */)
        {
            result.Add("ClientboundOpenScreenPacket");
        }

        result.Add("ClientboundContainerSetContentPacket");
        result.Add("ClientboundContainerSetDataPacket");
        result.Add("ClientboundContainerSetSlotPacket");
        if (protocolVersion > 765 /* > 1.20.4 */)
        {
            result.Add("ClientboundCookieRequestPacket");
        }

        result.Add("ClientboundCooldownPacket");
        if (protocolVersion > 759 /* > 1.19 */)
        {
            result.Add("ClientboundCustomChatCompletionsPacket");
        }

        result.Add("ClientboundCustomPayloadPacket");
        if (protocolVersion > 761 /* > 1.19.3 */)
        {
            result.Add("ClientboundDamageEventPacket");
        }

        if (protocolVersion > 765 /* > 1.20.4 */)
        {
            result.Add("ClientboundDebugSamplePacket");
        }

        if (protocolVersion < 761 /* < 1.19.3 */)
        {
            result.Add("ClientboundCustomSoundPacket");
        }

        if (protocolVersion > 759 /* > 1.19 */)
        {
            result.Add("ClientboundDeleteChatPacket");
        }

        result.Add("ClientboundDisconnectPacket");
        if (protocolVersion > 760 /* > 1.19.2 */)
        {
            result.Add("ClientboundDisguisedChatPacket");
        }

        result.Add("ClientboundEntityEventPacket");
        if (protocolVersion > 767 /* > 1.21.1 */)
        {
            result.Add("ClientboundEntityPositionSyncPacket");
        }

        if (protocolVersion > 340 /* > 1.12.2 */ && protocolVersion < 477 /* < 1.14 */)
        {
            result.Add("ClientboundTagQueryPacket");
        }

        result.Add("ClientboundExplodePacket");
        result.Add("ClientboundForgetLevelChunkPacket");
        result.Add("ClientboundGameEventPacket");
        if (protocolVersion > 404 /* > 1.13.2 */)
        {
            result.Add("ClientboundHorseScreenOpenPacket");
        }

        if (protocolVersion > 761 /* > 1.19.3 */)
        {
            result.Add("ClientboundHurtAnimationPacket");
        }

        if (protocolVersion > 754 /* > 1.16.5 */)
        {
            result.Add("ClientboundInitializeBorderPacket");
        }

        result.Add("ClientboundKeepAlivePacket");
        if (protocolVersion < 757 /* < 1.18 */)
        {
            result.Add("ClientboundLevelChunkPacket");
        }

        if (protocolVersion > 756 /* > 1.17.1 */)
        {
            result.Add("ClientboundLevelChunkWithLightPacket");
        }

        result.Add("ClientboundLevelEventPacket");
        result.Add("ClientboundLevelParticlesPacket");
        if (protocolVersion > 404 /* > 1.13.2 */)
        {
            result.Add("ClientboundLightUpdatePacket");
        }

        result.Add("ClientboundLoginPacket");
        result.Add("ClientboundMapItemDataPacket");
        if (protocolVersion > 404 /* > 1.13.2 */)
        {
            result.Add("ClientboundMerchantOffersPacket");
        }

        if (protocolVersion < 477 /* < 1.14 */)
        {
            result.Add("ClientboundMoveEntityPacket");
        }

        result.Add("ClientboundMoveEntityPacketPos");
        result.Add("ClientboundMoveEntityPacketPosRot");
        if (protocolVersion > 767 /* > 1.21.1 */)
        {
            result.Add("ClientboundMoveMinecartPacket");
        }

        result.Add("ClientboundMoveEntityPacketRot");
        if (protocolVersion > 404 /* > 1.13.2 */ && protocolVersion < 755 /* < 1.17 */)
        {
            result.Add("ClientboundMoveEntityPacket");
        }

        result.Add("ClientboundMoveVehiclePacket");
        if (protocolVersion > 404 /* > 1.13.2 */)
        {
            result.Add("ClientboundOpenBookPacket");
            result.Add("ClientboundOpenScreenPacket");
        }

        result.Add("ClientboundOpenSignEditorPacket");
        if (protocolVersion > 754 /* > 1.16.5 */)
        {
            result.Add("ClientboundPingPacket");
        }

        if (protocolVersion > 763 /* > 1.20.1 */)
        {
            result.Add("ClientboundPongResponsePacket");
        }

        result.Add("ClientboundPlaceGhostRecipePacket");
        result.Add("ClientboundPlayerAbilitiesPacket");
        if (protocolVersion > 759 /* > 1.19 */ && protocolVersion < 761 /* < 1.19.3 */)
        {
            result.Add("ClientboundPlayerChatHeaderPacket");
        }

        if (protocolVersion > 758 /* > 1.18.2 */)
        {
            result.Add("ClientboundPlayerChatPacket");
        }

        if (protocolVersion > 754 /* > 1.16.5 */)
        {
            result.Add("ClientboundPlayerCombatEndPacket");
            result.Add("ClientboundPlayerCombatEnterPacket");
            result.Add("ClientboundPlayerCombatKillPacket");
        }

        if (protocolVersion > 760 /* > 1.19.2 */)
        {
            result.Add("ClientboundPlayerInfoRemovePacket");
            result.Add("ClientboundPlayerInfoUpdatePacket");
        }

        if (protocolVersion < 755 /* < 1.17 */)
        {
            result.Add("ClientboundPlayerCombatPacket");
        }

        if (protocolVersion < 761 /* < 1.19.3 */)
        {
            result.Add("ClientboundPlayerInfoPacket");
        }

        if (protocolVersion > 340 /* > 1.12.2 */)
        {
            result.Add("ClientboundPlayerLookAtPacket");
        }

        result.Add("ClientboundPlayerPositionPacket");
        if (protocolVersion > 767 /* > 1.21.1 */)
        {
            result.Add("ClientboundPlayerRotationPacket");
        }

        if (protocolVersion > 767 /* > 1.21.1 */)
        {
            result.Add("ClientboundRecipeBookAddPacket");
            result.Add("ClientboundRecipeBookRemovePacket");
            result.Add("ClientboundRecipeBookSettingsPacket");
        }

        if (protocolVersion < 477 /* < 1.14 */)
        {
            result.Add("ClientboundUseBedPacket");
        }

        if (protocolVersion < 768 /* < 1.21.2 */)
        {
            result.Add("ClientboundRecipePacket");
        }

        if (protocolVersion > 754 /* > 1.16.5 */ && protocolVersion < 756 /* < 1.17.1 */)
        {
            result.Add("ClientboundRemoveEntityPacket");
        }

        if (protocolVersion < 755 /* < 1.17 */ || protocolVersion > 755 /* > 1.17 */)
        {
            result.Add("ClientboundRemoveEntitiesPacket");
        }

        result.Add("ClientboundRemoveMobEffectPacket");
        if (protocolVersion > 764 /* > 1.20.2 */)
        {
            result.Add("ClientboundResetScorePacket");
            result.Add("ClientboundResourcePackPopPacket");
            result.Add("ClientboundResourcePackPushPacket");
        }

        if (protocolVersion < 765 /* < 1.20.3 */)
        {
            result.Add("ClientboundResourcePackPacket");
        }

        result.Add("ClientboundRespawnPacket");
        result.Add("ClientboundRotateHeadPacket");
        if (protocolVersion > 736 /* > 1.16.1 */)
        {
            result.Add("ClientboundSectionBlocksUpdatePacket");
        }

        result.Add("ClientboundSelectAdvancementsTabPacket");
        if (protocolVersion > 758 /* > 1.18.2 */)
        {
            result.Add("ClientboundServerDataPacket");
        }

        if (protocolVersion > 754 /* > 1.16.5 */)
        {
            result.Add("ClientboundSetActionBarTextPacket");
            result.Add("ClientboundSetBorderCenterPacket");
            result.Add("ClientboundSetBorderLerpSizePacket");
            result.Add("ClientboundSetBorderSizePacket");
            result.Add("ClientboundSetBorderWarningDelayPacket");
            result.Add("ClientboundSetBorderWarningDistancePacket");
        }

        if (protocolVersion < 755 /* < 1.17 */)
        {
            result.Add("ClientboundSetBorderPacket");
        }

        result.Add("ClientboundSetCameraPacket");
        if (protocolVersion < 768 /* < 1.21.2 */)
        {
            result.Add("ClientboundSetCarriedItemPacket");
        }

        if (protocolVersion > 404 /* > 1.13.2 */)
        {
            result.Add("ClientboundSetChunkCacheCenterPacket");
            result.Add("ClientboundSetChunkCacheRadiusPacket");
        }

        if (protocolVersion > 767 /* > 1.21.1 */)
        {
            result.Add("ClientboundSetCursorItemPacket");
        }

        if (protocolVersion > 578 /* > 1.15.2 */)
        {
            result.Add("ClientboundSetDefaultSpawnPositionPacket");
        }

        if (protocolVersion > 758 /* > 1.18.2 */ && protocolVersion < 761 /* < 1.19.3 */)
        {
            result.Add("ClientboundSetDisplayChatPreviewPacket");
        }

        result.Add("ClientboundSetDisplayObjectivePacket");
        result.Add("ClientboundSetEntityDataPacket");
        result.Add("ClientboundSetEntityLinkPacket");
        result.Add("ClientboundSetEntityMotionPacket");
        result.Add("ClientboundSetEquipmentPacket");
        result.Add("ClientboundSetExperiencePacket");
        result.Add("ClientboundSetHealthPacket");
        if (protocolVersion > 767 /* > 1.21.1 */)
        {
            result.Add("ClientboundSetHeldSlotPacket");
        }

        result.Add("ClientboundSetObjectivePacket");
        result.Add("ClientboundSetPassengersPacket");
        if (protocolVersion > 767 /* > 1.21.1 */)
        {
            result.Add("ClientboundSetPlayerInventoryPacket");
        }

        result.Add("ClientboundSetPlayerTeamPacket");
        result.Add("ClientboundSetScorePacket");
        if (protocolVersion > 756 /* > 1.17.1 */)
        {
            result.Add("ClientboundSetSimulationDistancePacket");
        }

        if (protocolVersion > 754 /* > 1.16.5 */)
        {
            result.Add("ClientboundSetSubtitleTextPacket");
        }

        if (protocolVersion < 735 /* < 1.16 */)
        {
            result.Add("ClientboundSetDefaultSpawnPositionPacket");
        }

        result.Add("ClientboundSetTimePacket");
        if (protocolVersion > 754 /* > 1.16.5 */)
        {
            result.Add("ClientboundSetTitleTextPacket");
            result.Add("ClientboundSetTitlesAnimationPacket");
        }

        if (protocolVersion < 755 /* < 1.17 */)
        {
            result.Add("ClientboundSetTitlesPacket");
        }

        if (protocolVersion > 404 /* > 1.13.2 */)
        {
            result.Add("ClientboundSoundEntityPacket");
        }

        if (protocolVersion > 340 /* > 1.12.2 */ && protocolVersion < 477 /* < 1.14 */)
        {
            result.Add("ClientboundStopSoundPacket");
        }

        result.Add("ClientboundSoundPacket");
        if (protocolVersion > 763 /* > 1.20.1 */)
        {
            result.Add("ClientboundStartConfigurationPacket");
        }

        if (protocolVersion > 404 /* > 1.13.2 */)
        {
            result.Add("ClientboundStopSoundPacket");
        }

        if (protocolVersion > 765 /* > 1.20.4 */)
        {
            result.Add("ClientboundStoreCookiePacket");
        }

        if (protocolVersion > 758 /* > 1.18.2 */)
        {
            result.Add("ClientboundSystemChatPacket");
        }

        result.Add("ClientboundTabListPacket");
        if (protocolVersion > 404 /* > 1.13.2 */)
        {
            result.Add("ClientboundTagQueryPacket");
        }

        result.Add("ClientboundTakeItemEntityPacket");
        result.Add("ClientboundTeleportEntityPacket");
        if (protocolVersion > 764 /* > 1.20.2 */)
        {
            result.Add("ClientboundTickingStatePacket");
            result.Add("ClientboundTickingStepPacket");
        }

        if (protocolVersion > 765 /* > 1.20.4 */)
        {
            result.Add("ClientboundTransferPacket");
        }

        result.Add("ClientboundUpdateAdvancementsPacket");
        result.Add("ClientboundUpdateAttributesPacket");
        if (protocolVersion > 760 /* > 1.19.2 */ && protocolVersion < 764 /* < 1.20.2 */)
        {
            result.Add("ClientboundUpdateEnabledFeaturesPacket");
        }

        result.Add("ClientboundUpdateMobEffectPacket");
        if (protocolVersion > 340 /* > 1.12.2 */)
        {
            result.Add("ClientboundUpdateRecipesPacket");
            result.Add("ClientboundUpdateTagsPacket");
        }

        if (protocolVersion > 490 /* > 1.14.3 */ && protocolVersion < 573 /* < 1.15 */)
        {
            result.Add("ClientboundBlockBreakAckPacket");
        }

        if (protocolVersion > 765 /* > 1.20.4 */)
        {
            result.Add("ClientboundProjectilePowerPacket");
        }

        if (protocolVersion > 766 /* > 1.20.6 */)
        {
            result.Add("ClientboundCustomReportDetailsPacket");
            result.Add("ClientboundServerLinksPacket");
        }

        return result;
    }

    public static List<string> ClientboundConfigurationPackets(int protocolVersion)
    {
        List<string> result = new();
        if (protocolVersion > 765 /* > 1.20.4 */)
        {
            result.Add("ClientboundCookieRequestConfigurationPacket");
        }

        result.Add("ClientboundCustomPayloadConfigurationPacket");
        result.Add("ClientboundDisconnectConfigurationPacket");
        result.Add("ClientboundFinishConfigurationPacket");
        result.Add("ClientboundKeepAliveConfigurationPacket");
        result.Add("ClientboundPingConfigurationPacket");
        if (protocolVersion > 765 /* > 1.20.4 */)
        {
            result.Add("ClientboundResetChatPacket");
        }

        result.Add("ClientboundRegistryDataPacket");
        if (protocolVersion > 764 /* > 1.20.2 */)
        {
            result.Add("ClientboundResourcePackPopConfigurationPacket");
            result.Add("ClientboundResourcePackPushConfigurationPacket");
        }

        if (protocolVersion > 765 /* > 1.20.4 */)
        {
            result.Add("ClientboundStoreCookieConfigurationPacket");
            result.Add("ClientboundTransferConfigurationPacket");
        }

        if (protocolVersion < 765 /* < 1.20.3 */)
        {
            result.Add("ClientboundResourcePackConfigurationPacket");
        }

        result.Add("ClientboundUpdateEnabledFeaturesPacket");
        result.Add("ClientboundUpdateTagsConfigurationPacket");
        if (protocolVersion > 765 /* > 1.20.4 */)
        {
            result.Add("ClientboundSelectKnownPacksPacket");
        }

        if (protocolVersion > 766 /* > 1.20.6 */)
        {
            result.Add("ClientboundCustomReportDetailsConfigurationPacket");
            result.Add("ClientboundServerLinksConfigurationPacket");
        }

        return result;
    }

    public static List<string> ServerboundConfigurationPackets(int protocolVersion)
    {
        List<string> result = new();
        result.Add("ServerboundClientInformationConfigurationPacket");
        if (protocolVersion > 765 /* > 1.20.4 */)
        {
            result.Add("ServerboundCookieResponseConfigurationPacket");
        }

        result.Add("ServerboundCustomPayloadConfigurationPacket");
        result.Add("ServerboundFinishConfigurationPacket");
        result.Add("ServerboundKeepAliveConfigurationPacket");
        result.Add("ServerboundPongConfigurationPacket");
        result.Add("ServerboundResourcePackConfigurationPacket");
        if (protocolVersion > 765 /* > 1.20.4 */)
        {
            result.Add("ServerboundSelectKnownPacksPacket");
        }

        return result;
    }

    public static List<string> ServerboundLoginPackets(int protocolVersion)
    {
        List<string> result = new();
        result.Add("ServerboundHelloPacket");
        result.Add("ServerboundKeyPacket");
        if (protocolVersion > 340 /* > 1.12.2 */ && protocolVersion < 764 /* < 1.20.2 */)
        {
            result.Add("ServerboundCustomQueryPacket");
        }

        if (protocolVersion > 763 /* > 1.20.1 */)
        {
            result.Add("ServerboundCustomQueryAnswerPacket");
            result.Add("ServerboundLoginAcknowledgedPacket");
        }

        if (protocolVersion > 765 /* > 1.20.4 */)
        {
            result.Add("ServerboundCookieResponseLoginPacket");
        }

        return result;
    }

    public static List<string> ClientboundLoginPackets(int protocolVersion)
    {
        List<string> result = new();

        result.Add("ClientboundLoginDisconnectPacket");
        result.Add("ClientboundHelloPacket");
        result.Add("ClientboundGameProfilePacket");
        result.Add("ClientboundLoginCompressionPacket");
        if (protocolVersion > 340 /* > 1.12.2 */)
        {
            result.Add("ClientboundCustomQueryPacket");
        }

        if (protocolVersion > 765 /* > 1.20.4 */)
        {
            result.Add("ClientboundCookieRequestLoginPacket");
        }

        return result;
    }

    public class GroupOfAdjacent<TSource, TKey> : IEnumerable<TSource>, IGrouping<TKey, TSource>
    {
        public TKey Key { get; set; }
        private List<TSource> GroupList { get; set; }

        System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
        {
            return ((System.Collections.Generic.IEnumerable<TSource>)this).GetEnumerator();
        }

        System.Collections.Generic.IEnumerator<TSource> System.Collections.Generic.IEnumerable<TSource>.GetEnumerator()
        {
            foreach (var s in GroupList)
                yield return s;
        }

        public GroupOfAdjacent(List<TSource> source, TKey key)
        {
            GroupList = source;
            Key = key;
        }
    }

    public static IEnumerable<IGrouping<TKey, TSource>> GroupAdjacent<TSource, TKey>(
        this IEnumerable<TSource> source,
        Func<TSource, TKey> keySelector)
    {
        TKey last = default(TKey);
        bool haveLast = false;
        List<TSource> list = new List<TSource>();
        foreach (TSource s in source)
        {
            TKey k = keySelector(s);
            if (haveLast)
            {
                if (!k.Equals(last))
                {
                    yield return new GroupOfAdjacent<TSource, TKey>(list, last);
                    list = new List<TSource>();
                    list.Add(s);
                    last = k;
                }
                else
                {
                    list.Add(s);
                    last = k;
                }
            }
            else
            {
                list.Add(s);
                last = k;
                haveLast = true;
            }
        }

        if (haveLast)
            yield return new GroupOfAdjacent<TSource, TKey>(list, last);
    }
}