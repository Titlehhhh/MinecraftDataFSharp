namespace MinecraftDataFSharp
{
    public class SelectBundleItem : IClientPacket
    {
        public int SlotId { get; set; }
        public int SelectedItemIndex { get; set; }

        public sealed class V768_769 : SelectBundleItem
        {
            public override void Serialize(ref MinecraftPrimitiveWriter writer, int protocolVersion)
            {
                SerializeInternal(ref writer, protocolVersion, SlotId, SelectedItemIndex);
            }

            internal static void SerializeInternal(ref MinecraftPrimitiveWriter writer, int protocolVersion, int slotId, int selectedItemIndex)
            {
                writer.WriteVarInt(slotId);
                writer.WriteVarInt(selectedItemIndex);
            }

            public new static bool SupportedVersion(int protocolVersion)
            {
                return protocolVersion is >= 768 and <= 769;
            }
        }

        public static bool SupportedVersion(int protocolVersion)
        {
            return V768_769.SupportedVersion(protocolVersion);
        }

        public virtual void Serialize(ref MinecraftPrimitiveWriter writer, int protocolVersion)
        {
            if (V768_769.SupportedVersion(protocolVersion))
                V768_769.SerializeInternal(ref writer, protocolVersion, SlotId, SelectedItemIndex);
            else
                throw new Exception();
        }
    }
}