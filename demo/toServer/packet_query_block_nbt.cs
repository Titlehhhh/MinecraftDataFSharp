namespace MinecraftDataFSharp
{
    public class QueryBlockNbt : IClientPacket
    {
        public int TransactionId { get; set; }
        public Position Location { get; set; }

        public sealed class V393_769 : QueryBlockNbt
        {
            public override void Serialize(ref MinecraftPrimitiveWriter writer, int protocolVersion)
            {
                SerializeInternal(ref writer, protocolVersion, TransactionId, Location);
            }

            internal static void SerializeInternal(ref MinecraftPrimitiveWriter writer, int protocolVersion, int transactionId, Position location)
            {
                writer.WriteVarInt(transactionId);
                writer.WritePosition(location, protocolVersion);
            }

            public new static bool SupportedVersion(int protocolVersion)
            {
                return protocolVersion is >= 393 and <= 769;
            }
        }

        public static bool SupportedVersion(int protocolVersion)
        {
            return V393_769.SupportedVersion(protocolVersion);
        }

        public virtual void Serialize(ref MinecraftPrimitiveWriter writer, int protocolVersion)
        {
            if (V393_769.SupportedVersion(protocolVersion))
                V393_769.SerializeInternal(ref writer, protocolVersion, TransactionId, Location);
            else
                throw new Exception();
        }
    }
}