namespace MinecraftDataFSharp
{
    public abstract class HeldItemSlot : IServerPacket
    {
        public sealed class V340_768 : HeldItemSlot
        {
            public override void Deserialize(ref MinecraftPrimitiveReader reader, int protocolVersion)
            {
                Slot = reader.ReadSignedByte();
            }

            public new static bool SupportedVersion(int protocolVersion)
            {
                return protocolVersion is >= 340 and <= 768;
            }

            public sbyte Slot { get; set; }
        }

        public sealed class V769 : HeldItemSlot
        {
            public override void Deserialize(ref MinecraftPrimitiveReader reader, int protocolVersion)
            {
                Slot = reader.ReadVarInt();
            }

            public new static bool SupportedVersion(int protocolVersion)
            {
                return protocolVersion == 769;
            }

            public int Slot { get; set; }
        }

        public static bool SupportedVersion(int protocolVersion)
        {
            return V340_768.SupportedVersion(protocolVersion) || V769.SupportedVersion(protocolVersion);
        }

        public abstract void Deserialize(ref MinecraftPrimitiveReader reader, int protocolVersion);
    }
}