﻿namespace SandBoxLib;

public enum ClientPacket
{
    TeleportConfirm = 0,
    TabComplete = 1,
    Chat = 2,
    ClientCommand = 3,
    Settings = 4,
    Transaction = 5,
    EnchantItem = 6,
    WindowClick = 7,
    CloseWindow = 8,
    CustomPayload = 9,
    UseEntity = 10,
    KeepAlive = 11,
    Flying = 12,
    Position = 13,
    PositionLook = 14,
    Look = 15,
    VehicleMove = 16,
    SteerBoat = 17,
    CraftRecipeRequest = 18,
    Abilities = 19,
    BlockDig = 20,
    EntityAction = 21,
    SteerVehicle = 22,
    CraftingBookData = 23,
    ResourcePackReceive = 24,
    AdvancementTab = 25,
    HeldItemSlot = 26,
    SetCreativeSlot = 27,
    UpdateSign = 28,
    ArmAnimation = 29,
    Spectate = 30,
    BlockPlace = 31,
    UseItem = 32,
    QueryBlockNbt = 33,
    EditBook = 34,
    QueryEntityNbt = 35,
    PickItem = 36,
    NameItem = 37,
    SelectTrade = 38,
    SetBeaconEffect = 39,
    UpdateCommandBlock = 40,
    UpdateCommandBlockMinecart = 41,
    UpdateStructureBlock = 42,
    SetDifficulty = 43,
    LockDifficulty = 44,
    UpdateJigsawBlock = 45,
    GenerateStructure = 46,
    RecipeBook = 47,
    DisplayedRecipe = 48,
    Pong = 49,
    ChatCommand = 50,
    ChatMessage = 51,
    ChatPreview = 52,
    MessageAcknowledgement = 53,
    ChatSessionUpdate = 54,
    ChunkBatchReceived = 55,
    ConfigurationAcknowledged = 56,
    PingRequest = 57,
    SetSlotState = 58,
    ChatCommandSigned = 59,
    CookieResponse = 60,
    DebugSampleSubscription = 61
}