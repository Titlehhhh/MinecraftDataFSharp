﻿using System.Text.Json.Serialization;

namespace Protodef;

public sealed class ProtodefTopBitSetTerminatedArray : ProtodefType, IPathTypeEnumerable
{
    [JsonPropertyName("type")] public ProtodefType Type { get; set; }

    public IEnumerator<KeyValuePair<string, ProtodefType>> GetEnumerator()
    {
        if (Type is IPathTypeEnumerable)
            yield return new KeyValuePair<string, ProtodefType>("type", Type);
    }

    public override object Clone()
    {
        return new ProtodefTopBitSetTerminatedArray { Type = (ProtodefType)Type.Clone() };
    }
}