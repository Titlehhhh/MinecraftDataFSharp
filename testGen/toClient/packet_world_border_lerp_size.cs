namespace MinecraftDataFSharp
{
    public abstract class WorldBorderLerpSize : IServerPacket
    {
        public double OldDiameter { get; set; }
        public double NewDiameter { get; set; }

        public sealed class V755_758 : WorldBorderLerpSize
        {
            public override void Deserialize(ref MinecraftPrimitiveReader reader, int protocolVersion)
            {
                OldDiameter = reader.ReadDouble();
                NewDiameter = reader.ReadDouble();
                Speed = reader.ReadVarLong();
            }

            public new static bool SupportedVersion(int protocolVersion)
            {
                return protocolVersion is >= 755 and <= 758;
            }

            public long Speed { get; set; }
        }

        public sealed class V759_769 : WorldBorderLerpSize
        {
            public override void Deserialize(ref MinecraftPrimitiveReader reader, int protocolVersion)
            {
                OldDiameter = reader.ReadDouble();
                NewDiameter = reader.ReadDouble();
                Speed = reader.ReadVarInt();
            }

            public new static bool SupportedVersion(int protocolVersion)
            {
                return protocolVersion is >= 759 and <= 769;
            }

            public int Speed { get; set; }
        }

        public static bool SupportedVersion(int protocolVersion)
        {
            return V755_758.SupportedVersion(protocolVersion) || V759_769.SupportedVersion(protocolVersion);
        }

        public abstract void Deserialize(ref MinecraftPrimitiveReader reader, int protocolVersion);
    }
}