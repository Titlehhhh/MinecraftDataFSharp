namespace MinecraftDataFSharp
{
    public class RecipeBook : IClientPacket
    {
        public int BookId { get; set; }
        public bool BookOpen { get; set; }
        public bool FilterActive { get; set; }

        public sealed class V751_769 : RecipeBook
        {
            public override void Serialize(ref MinecraftPrimitiveWriter writer, int protocolVersion)
            {
                SerializeInternal(ref writer, protocolVersion, BookId, BookOpen, FilterActive);
            }

            internal static void SerializeInternal(ref MinecraftPrimitiveWriter writer, int protocolVersion, int bookId, bool bookOpen, bool filterActive)
            {
                writer.WriteVarInt(bookId);
                writer.WriteBoolean(bookOpen);
                writer.WriteBoolean(filterActive);
            }

            public new static bool SupportedVersion(int protocolVersion)
            {
                return protocolVersion is >= 751 and <= 769;
            }
        }

        public static bool SupportedVersion(int protocolVersion)
        {
            return V751_769.SupportedVersion(protocolVersion);
        }

        public virtual void Serialize(ref MinecraftPrimitiveWriter writer, int protocolVersion)
        {
            if (V751_769.SupportedVersion(protocolVersion))
                V751_769.SerializeInternal(ref writer, protocolVersion, BookId, BookOpen, FilterActive);
            else
                throw new Exception();
        }
    }
}