﻿namespace Protodef;

public sealed class ProtodefOption : ProtodefType
{
    public ProtodefOption(ProtodefType type)
    {
        ArgumentNullException.ThrowIfNull(type);
        Type = type;
    }

    public ProtodefType Type { get; }

    public IEnumerator<KeyValuePair<string?, ProtodefType>> GetEnumerator()
    {
        yield return new KeyValuePair<string?, ProtodefType>("type", Type);
    }

    public override object Clone()
    {
        var owner = new ProtodefOption((ProtodefType)Type.Clone());
        owner.Type.Parent = owner;
        return owner;
    }

    public override string? GetNetType()
    {
        var netType = Type.GetNetType();
        if (netType is not null) return netType + "?";
        return null;
    }

    private bool Equals(ProtodefOption other)
    {
        return Type.Equals(other.Type);
    }

    public override bool Equals(object? obj)
    {
        return ReferenceEquals(this, obj) || (obj is ProtodefOption other && Equals(other));
    }

    public override int GetHashCode()
    {
        return Type.GetHashCode();
    }
}