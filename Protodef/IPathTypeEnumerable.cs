﻿namespace Protodef;

public interface IPathTypeEnumerable
{
    IEnumerator<KeyValuePair<string, ProtodefType>> GetEnumerator();
}