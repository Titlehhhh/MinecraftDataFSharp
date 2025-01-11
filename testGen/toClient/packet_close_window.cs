namespace MinecraftDataFSharp
{
    public abstract class CloseWindow : IServerPacket
    {
        public sealed class V340_767 : CloseWindow
        {
            public override void Deserialize(ref MinecraftPrimitiveReader reader, int protocolVersion)
            {
                WindowId = reader.ReadUnsignedByte();
            }

            public new static bool SupportedVersion(int protocolVersion)
            {
                return protocolVersion is >= 340 and <= 767;
            }

            public byte WindowId { get; set; }
        }

        public sealed class V768_769 : CloseWindow
        {
            public override void Deserialize(ref MinecraftPrimitiveReader reader, int protocolVersion)
            {
                WindowId = reader.ReadVarInt();
            }

            public new static bool SupportedVersion(int protocolVersion)
            {
                return protocolVersion is >= 768 and <= 769;
            }

            public int WindowId { get; set; }
        }

        public static bool SupportedVersion(int protocolVersion)
        {
            return V340_767.SupportedVersion(protocolVersion) || V768_769.SupportedVersion(protocolVersion);
        }

        public abstract void Deserialize(ref MinecraftPrimitiveReader reader, int protocolVersion);
    }
}