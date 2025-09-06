﻿using System.Text.Json.Serialization;

namespace Protodef;

public sealed class ProtodefPrefixedString : ProtodefType
{
    [JsonConstructor]
    public ProtodefPrefixedString(ProtodefType countType)
    {
        ArgumentNullException.ThrowIfNull(countType);
        CountType = countType;
    }

    [JsonPropertyName("countType")] public ProtodefType CountType { get; }

    public override string? GetNetType()
    {
        return "string";
    }

    public override object Clone()
    {
        var owner = new ProtodefPrefixedString((ProtodefType)CountType.Clone());
        owner.CountType.Parent = owner;
        return owner;
    }

    private bool Equals(ProtodefPrefixedString other)
    {
        return CountType.Equals(other.CountType);
    }

    public override bool Equals(object? obj)
    {
        return ReferenceEquals(this, obj) || (obj is ProtodefPrefixedString other && Equals(other));
    }

    public override IEnumerable<KeyValuePair<string?, ProtodefType>> Children
    {
        get
        {
            yield return new KeyValuePair<string?, ProtodefType>("countType", CountType);
        }
    }


    public override int GetHashCode()
    {
        return CountType.GetHashCode();
    }
    public override string ToString() => "pstring";
}
