﻿using System.Text.Json.Serialization;

namespace Protodef.Enumerable;

public class ProtodefSwitch : ProtodefType
{
    //TODO path parser
    [JsonPropertyName("compareTo")] public string CompareTo { get; set; }

    [JsonPropertyName("compareToValue")] public string? CompareToValue { get; set; }

    [JsonPropertyName("fields")] public Dictionary<string, ProtodefType> Fields { get; set; } = new();

    [JsonPropertyName("default")] public ProtodefType? Default { get; set; }

   
    public override IEnumerable<KeyValuePair<string?, ProtodefType>> Children
    {
        get
        {
            foreach (var item in Fields)
                yield return new KeyValuePair<string?, ProtodefType>(item.Key, item.Value);
            if (Default is not null)
                yield return new KeyValuePair<string?, ProtodefType>("default", Default);
        }
    }

    public override object Clone()
    {
        var owner = new ProtodefSwitch
        {
            CompareToValue = CompareToValue,
            Fields = Fields.Select(x => new KeyValuePair<string, ProtodefType>(x.Key, (ProtodefType)x.Value.Clone()))
                .ToDictionary(),
            Default = Default?.Clone() as ProtodefType
        };

        foreach (var keyValuePair in owner.Fields) keyValuePair.Value.Parent = owner;

        return owner;
    }
}