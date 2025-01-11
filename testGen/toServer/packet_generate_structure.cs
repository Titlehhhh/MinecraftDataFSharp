namespace MinecraftDataFSharp
{
    public class GenerateStructure : IClientPacket
    {
        public Position Location { get; set; }
        public int Levels { get; set; }
        public bool KeepJigsaws { get; set; }

        public sealed class V734_769 : GenerateStructure
        {
            public override void Serialize(ref MinecraftPrimitiveWriter writer, int protocolVersion)
            {
                SerializeInternal(ref writer, protocolVersion, Location, Levels, KeepJigsaws);
            }

            internal static void SerializeInternal(ref MinecraftPrimitiveWriter writer, int protocolVersion, Position location, int levels, bool keepJigsaws)
            {
                writer.WritePosition(location, protocolVersion);
                writer.WriteVarInt(levels);
                writer.WriteBoolean(keepJigsaws);
            }

            public new static bool SupportedVersion(int protocolVersion)
            {
                return protocolVersion is >= 734 and <= 769;
            }
        }

        public static bool SupportedVersion(int protocolVersion)
        {
            return V734_769.SupportedVersion(protocolVersion);
        }

        public virtual void Serialize(ref MinecraftPrimitiveWriter writer, int protocolVersion)
        {
            if (V734_769.SupportedVersion(protocolVersion))
                V734_769.SerializeInternal(ref writer, protocolVersion, Location, Levels, KeepJigsaws);
            else
                throw new Exception();
        }
    }
}