namespace MinecraftDataFSharp
{
    public class VehicleMove : IClientPacket
    {
        public double X { get; set; }
        public double Y { get; set; }
        public double Z { get; set; }
        public float Yaw { get; set; }
        public float Pitch { get; set; }

        public sealed class V340_768 : VehicleMove
        {
            public override void Serialize(ref MinecraftPrimitiveWriter writer, int protocolVersion)
            {
                SerializeInternal(ref writer, protocolVersion, X, Y, Z, Yaw, Pitch);
            }

            internal static void SerializeInternal(ref MinecraftPrimitiveWriter writer, int protocolVersion, double x, double y, double z, float yaw, float pitch)
            {
                writer.WriteDouble(x);
                writer.WriteDouble(y);
                writer.WriteDouble(z);
                writer.WriteFloat(yaw);
                writer.WriteFloat(pitch);
            }

            public new static bool SupportedVersion(int protocolVersion)
            {
                return protocolVersion is >= 340 and <= 768;
            }
        }

        public sealed class V769 : VehicleMove
        {
            public override void Serialize(ref MinecraftPrimitiveWriter writer, int protocolVersion)
            {
                SerializeInternal(ref writer, protocolVersion, X, Y, Z, Yaw, Pitch, OnGround);
            }

            internal static void SerializeInternal(ref MinecraftPrimitiveWriter writer, int protocolVersion, double x, double y, double z, float yaw, float pitch, bool onGround)
            {
                writer.WriteDouble(x);
                writer.WriteDouble(y);
                writer.WriteDouble(z);
                writer.WriteFloat(yaw);
                writer.WriteFloat(pitch);
                writer.WriteBoolean(onGround);
            }

            public new static bool SupportedVersion(int protocolVersion)
            {
                return protocolVersion == 769;
            }

            public bool OnGround { get; set; }
        }

        public static bool SupportedVersion(int protocolVersion)
        {
            return V340_768.SupportedVersion(protocolVersion) || V769.SupportedVersion(protocolVersion);
        }

        public virtual void Serialize(ref MinecraftPrimitiveWriter writer, int protocolVersion)
        {
            if (V340_768.SupportedVersion(protocolVersion))
                V340_768.SerializeInternal(ref writer, protocolVersion, X, Y, Z, Yaw, Pitch);
            else if (V769.SupportedVersion(protocolVersion))
                V769.SerializeInternal(ref writer, protocolVersion, X, Y, Z, Yaw, Pitch, default);
            else
                throw new Exception();
        }
    }
}