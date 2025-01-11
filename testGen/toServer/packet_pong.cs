namespace MinecraftDataFSharp
{
    public class Pong : IClientPacket
    {
        public int Id { get; set; }

        public sealed class V755_769 : Pong
        {
            public override void Serialize(ref MinecraftPrimitiveWriter writer, int protocolVersion)
            {
                SerializeInternal(ref writer, protocolVersion, Id);
            }

            internal static void SerializeInternal(ref MinecraftPrimitiveWriter writer, int protocolVersion, int id)
            {
                writer.WriteSignedInt(id);
            }

            public new static bool SupportedVersion(int protocolVersion)
            {
                return protocolVersion is >= 755 and <= 769;
            }
        }

        public static bool SupportedVersion(int protocolVersion)
        {
            return V755_769.SupportedVersion(protocolVersion);
        }

        public virtual void Serialize(ref MinecraftPrimitiveWriter writer, int protocolVersion)
        {
            if (V755_769.SupportedVersion(protocolVersion))
                V755_769.SerializeInternal(ref writer, protocolVersion, Id);
            else
                throw new Exception();
        }
    }
}