namespace MinecraftDataFSharp
{
    public abstract class SpawnEntityPainting : IServerPacket
    {
        public int EntityId { get; set; }
        public Guid EntityUUID { get; set; }
        public Position Location { get; set; }
        public byte Direction { get; set; }

        public sealed class V340_351 : SpawnEntityPainting
        {
            public override void Deserialize(ref MinecraftPrimitiveReader reader, int protocolVersion)
            {
                EntityId = reader.ReadVarInt();
                EntityUUID = reader.ReadUUID();
                Title = reader.ReadString();
                Location = reader.ReadPosition(protocolVersion);
                Direction = reader.ReadUnsignedByte();
            }

            public new static bool SupportedVersion(int protocolVersion)
            {
                return protocolVersion is >= 340 and <= 351;
            }

            public string Title { get; set; }
        }

        public sealed class V393_758 : SpawnEntityPainting
        {
            public override void Deserialize(ref MinecraftPrimitiveReader reader, int protocolVersion)
            {
                EntityId = reader.ReadVarInt();
                EntityUUID = reader.ReadUUID();
                Title = reader.ReadVarInt();
                Location = reader.ReadPosition(protocolVersion);
                Direction = reader.ReadUnsignedByte();
            }

            public new static bool SupportedVersion(int protocolVersion)
            {
                return protocolVersion is >= 393 and <= 758;
            }

            public int Title { get; set; }
        }

        public static bool SupportedVersion(int protocolVersion)
        {
            return V340_351.SupportedVersion(protocolVersion) || V393_758.SupportedVersion(protocolVersion);
        }

        public abstract void Deserialize(ref MinecraftPrimitiveReader reader, int protocolVersion);
    }
}