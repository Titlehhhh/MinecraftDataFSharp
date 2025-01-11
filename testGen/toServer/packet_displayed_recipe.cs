namespace MinecraftDataFSharp
{
    public class DisplayedRecipe : IClientPacket
    {
        public sealed class V751_767 : DisplayedRecipe
        {
            public override void Serialize(ref MinecraftPrimitiveWriter writer, int protocolVersion)
            {
                SerializeInternal(ref writer, protocolVersion, RecipeId);
            }

            internal static void SerializeInternal(ref MinecraftPrimitiveWriter writer, int protocolVersion, string recipeId)
            {
                writer.WriteString(recipeId);
            }

            public new static bool SupportedVersion(int protocolVersion)
            {
                return protocolVersion is >= 751 and <= 767;
            }

            public string RecipeId { get; set; }
        }

        public sealed class V768_769 : DisplayedRecipe
        {
            public override void Serialize(ref MinecraftPrimitiveWriter writer, int protocolVersion)
            {
                SerializeInternal(ref writer, protocolVersion, RecipeId);
            }

            internal static void SerializeInternal(ref MinecraftPrimitiveWriter writer, int protocolVersion, int recipeId)
            {
                writer.WriteVarInt(recipeId);
            }

            public new static bool SupportedVersion(int protocolVersion)
            {
                return protocolVersion is >= 768 and <= 769;
            }

            public int RecipeId { get; set; }
        }

        public static bool SupportedVersion(int protocolVersion)
        {
            return V751_767.SupportedVersion(protocolVersion) || V768_769.SupportedVersion(protocolVersion);
        }

        public virtual void Serialize(ref MinecraftPrimitiveWriter writer, int protocolVersion)
        {
            if (V751_767.SupportedVersion(protocolVersion))
                V751_767.SerializeInternal(ref writer, protocolVersion, default);
            else if (V768_769.SupportedVersion(protocolVersion))
                V768_769.SerializeInternal(ref writer, protocolVersion, default);
            else
                throw new Exception();
        }
    }
}