namespace MinecraftDataFSharp
{
    public class LockDifficulty : IClientPacket
    {
        public bool Locked { get; set; }

        public sealed class V477_769 : LockDifficulty
        {
            public override void Serialize(ref MinecraftPrimitiveWriter writer, int protocolVersion)
            {
                SerializeInternal(ref writer, protocolVersion, Locked);
            }

            internal static void SerializeInternal(ref MinecraftPrimitiveWriter writer, int protocolVersion, bool locked)
            {
                writer.WriteBoolean(locked);
            }

            public new static bool SupportedVersion(int protocolVersion)
            {
                return protocolVersion is >= 477 and <= 769;
            }
        }

        public static bool SupportedVersion(int protocolVersion)
        {
            return V477_769.SupportedVersion(protocolVersion);
        }

        public virtual void Serialize(ref MinecraftPrimitiveWriter writer, int protocolVersion)
        {
            if (V477_769.SupportedVersion(protocolVersion))
                V477_769.SerializeInternal(ref writer, protocolVersion, Locked);
            else
                throw new Exception();
        }
    }
}