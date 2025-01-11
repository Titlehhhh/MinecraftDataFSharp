namespace MinecraftDataFSharp
{
    public abstract class OpenHorseWindow : IServerPacket
    {
        public int NbSlots { get; set; }
        public int EntityId { get; set; }

        public sealed class V477_767 : OpenHorseWindow
        {
            public override void Deserialize(ref MinecraftPrimitiveReader reader, int protocolVersion)
            {
                WindowId = reader.ReadUnsignedByte();
                NbSlots = reader.ReadVarInt();
                EntityId = reader.ReadSignedInt();
            }

            public new static bool SupportedVersion(int protocolVersion)
            {
                return protocolVersion is >= 477 and <= 767;
            }

            public byte WindowId { get; set; }
        }

        public sealed class V768_769 : OpenHorseWindow
        {
            public override void Deserialize(ref MinecraftPrimitiveReader reader, int protocolVersion)
            {
                WindowId = reader.ReadVarInt();
                NbSlots = reader.ReadVarInt();
                EntityId = reader.ReadSignedInt();
            }

            public new static bool SupportedVersion(int protocolVersion)
            {
                return protocolVersion is >= 768 and <= 769;
            }

            public int WindowId { get; set; }
        }

        public static bool SupportedVersion(int protocolVersion)
        {
            return V477_767.SupportedVersion(protocolVersion) || V768_769.SupportedVersion(protocolVersion);
        }

        public abstract void Deserialize(ref MinecraftPrimitiveReader reader, int protocolVersion);
    }
}