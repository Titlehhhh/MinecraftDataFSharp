module MinecraftDataFSharp.CodeGeneration.CodeGeneratorWrite

open System
open System.Collections.Generic
open System.Diagnostics
open System.IO
open Humanizer
open Microsoft.CodeAnalysis
open Microsoft.CodeAnalysis.CSharp
open Microsoft.CodeAnalysis.CSharp.Syntax
open Microsoft.FSharp.Collections
open MinecraftDataFSharp.Models
open Protodef
open Protodef.Enumerable
open Protodef.Primitive
open Shared


let private TypeToWriteMethodMap =
    Map
        [ "bool", "WriteBoolean"
          "i8", "WriteSignedByte"
          "u8", "WriteUnsignedByte"
          "i16", "WriteSignedShort"
          "u16", "WriteUnsignedShort"
          "i32", "WriteSignedInt"
          "u32", "WriteUnsignedInt"
          "i64", "WriteSignedLong"
          "u64", "WriteUnsignedLong"
          "f32", "WriteFloat"
          "f64", "WriteDouble"
          "UUID", "WriteUUID"
          "restBuffer", "WriteBuffer"
          "varint", "WriteVarInt"
          "varlong", "WriteVarLong"
          "string", "WriteString"
          "pstring", "WriteString" ]

let private generateInstructionForField (field: ProtodefContainerField) =
    let argName = field.Name.Camelize()

    let list = List<StatementSyntax>()

    let add (m: string) =
        SyntaxFactory.ParseStatement(m) |> list.Add

    let wi (m: string) (a: string) =
        SyntaxFactory.ParseStatement($"writer.{a}({m});") |> list.Add

    let wiP (m: string) (a: string) =
        SyntaxFactory.ParseStatement($"writer.{a}({m}, protocolVersion);") |> list.Add



    let rec generateWriteInstruction (t: ProtodefType) (name: string) : unit =
        match t with
        | :? ProtodefNumericType as p -> TypeToWriteMethodMap[p.OriginalName] |> wi name
        | :? ProtodefVarInt -> TypeToWriteMethodMap["varint"] |> wi name
        | :? ProtodefVarLong -> TypeToWriteMethodMap["varlong"] |> wi name
        | :? ProtodefString -> TypeToWriteMethodMap["string"] |> wi name
        | :? ProtodefPrefixedString -> TypeToWriteMethodMap["pstring"] |> wi name
        | :? ProtodefBool -> TypeToWriteMethodMap["bool"] |> wi name
        | :? ProtodefBuffer as b ->
            if b.Rest = true then
                TypeToWriteMethodMap["restBuffer"] |> wi name
            else
                "WriteVarInt" |> wi $"{argName}.Length"
                "WriteBuffer" |> wi name
        | :? ProtodefArray as a ->
            "WriteVarInt" |> wi $"{argName}.Length"

            $"foreach (var {argName}_item in {argName})" |> add
            generateWriteInstruction a.Type $"{argName}_item"
        | :? ProtodefOption as o ->
            "WriteBoolean" |> wi $"{argName} is not null"
            $"if ({argName} is not null)" |> add
            generateWriteInstruction o.Type $"{argName}!"
        | :? ProtodefCustomType as custom ->
            match custom.Name with
            | "vec2f" -> "WriteVector2" |> wiP name
            | "vec3f" -> "WriteVector3" |> wiP name
            | "vec3f64" -> "WriteVector364" |> wiP name
            | "vec4f" -> "WriteVector4" |> wiP name
            | "uuid" -> "WriteUUID" |> wi name
            | "position" -> "WritePosition" |> wiP name
            | "ByteArray" ->
                "WriteVarInt" |> wi $"{argName}.Length"
                "WriteBuffer" |> wi name
            | "slot" -> "WriteSlot" |> wiP name
            | "Slot" -> "WriteSlot" |> wiP name
            | "restBuffer" -> "WriteBuffer" |> wi name
            | "UUID" -> "WriteUUID" |> wi name
            | "MovementFlags" -> "WriteUnsignedByte" |> wi name
            | "PositionUpdateRelatives" -> "WriteUnsignedInt" |> wi name
            | "ContainerID" -> "WriteVarInt" |> wi name
            | _ -> failwith $"unknown custom type: {custom.Name}"
        | _ -> failwith $"Unknown type {t}"

    generateWriteInstruction field.Type argName

    list

let private generateSerializationInstructions (container: ProtodefContainer) =
    container.Fields |> Seq.collect generateInstructionForField |> Array.ofSeq



let private writerParameter =
    SyntaxFactory
        .Parameter(SyntaxFactory.Identifier("writer"))
        .AddModifiers(SyntaxFactory.Token(SyntaxKind.RefKeyword))
        .WithType(SyntaxFactory.ParseTypeName("MinecraftPrimitiveWriter"))



let private generateSerializeInternalMethod (container: ProtodefContainer) =
    let parameters =
        container.Fields
        |> Seq.map (fun x ->
            let pascalCase = x.Name.Camelize()
            let csharpType = protodefTypeToCSharpType x.Type

            SyntaxFactory
                .Parameter(SyntaxFactory.Identifier(pascalCase))
                .WithType(SyntaxFactory.ParseTypeName(csharpType)))
        |> Seq.toList




    let parameters =
        (writerParameter :: protocolVersionParameter :: parameters) |> Seq.toArray

    let identifier = SyntaxFactory.Identifier("SerializeInternal")


    let ser = generateSerializationInstructions container

    let blockSyntax = SyntaxFactory.Block(ser)

    SyntaxFactory
        .MethodDeclaration(SyntaxFactory.ParseTypeName("void"), identifier)
        .AddModifiers(SyntaxFactory.Token(SyntaxKind.InternalKeyword), SyntaxFactory.Token(SyntaxKind.StaticKeyword))
        .AddParameterListParameters(parameters)
        .WithBody(blockSyntax)

let private generateSerializeMethod (containers: (VersionRange * ProtodefContainer) list) =
    if (containers.Length = 1) then
        let container = snd containers.Head

        let parameters =
            container.Fields |> Seq.map _.Name.Pascalize() |> String.concat ", "


        let body = $"SerializeInternal(ref writer, protocolVersion, {parameters});"

        let serializeInternal =
            (generateSerializeInternalMethod container) :> MemberDeclarationSyntax

        [ SyntaxFactory
              .MethodDeclaration(SyntaxFactory.ParseTypeName("void"), "Serialize")
              .AddModifiers(
                  SyntaxFactory.Token(SyntaxKind.PublicKeyword),
                  SyntaxFactory.Token(SyntaxKind.OverrideKeyword)
              )
              .AddParameterListParameters(writerParameter, protocolVersionParameter)
              .WithBody(SyntaxFactory.Block(SyntaxFactory.ParseStatement(body)))
          :> MemberDeclarationSyntax
          serializeInternal ]
    else
        []










let private generateArgumentListForConcrete (generalProps: string seq, protodef: ProtodefContainer) =
    protodef.Fields
    |> Seq.map (fun f ->
        let pascalCase = f.Name.Pascalize()

        if generalProps |> Seq.contains pascalCase then
            pascalCase
        else
            getDefaultValue f.Type)
    |> Seq.toArray

let private generateBodyForBase (generalProps: string seq, containers: Dictionary<VersionRange, ProtodefContainer>) =
    let rec generateIfElse (remaining: (VersionRange * ProtodefContainer) list) =
        match remaining with
        | [] -> Some(SyntaxFactory.ParseStatement("throw new Exception();"))
        | (k, v) :: tail ->
            let arguments =
                generateArgumentListForConcrete (generalProps, v) |> String.concat ", "

            let className = $"V{k.ToString()}".Replace("-", "_")

            let condition =
                SyntaxFactory
                    .InvocationExpression(
                        SyntaxFactory.MemberAccessExpression(
                            SyntaxKind.SimpleMemberAccessExpression,
                            SyntaxFactory.IdentifierName(className),
                            SyntaxFactory.IdentifierName("SupportedVersion")
                        )
                    )
                    .WithArgumentList(
                        SyntaxFactory.ArgumentList(
                            SyntaxFactory.SingletonSeparatedList(
                                SyntaxFactory.Argument(SyntaxFactory.IdentifierName("protocolVersion"))
                            )
                        )
                    )

            let thenStatement =
                SyntaxFactory.ParseStatement(
                    if String.IsNullOrWhiteSpace(arguments) then
                        $"{className}.SerializeInternal(ref writer,protocolVersion);"
                    else
                        $"{className}.SerializeInternal(ref writer,protocolVersion,{arguments});"
                )

            let elseClause = generateIfElse tail


            Some(
                SyntaxFactory
                    .IfStatement(condition, thenStatement)
                    .WithElse(SyntaxFactory.ElseClause(elseClause.Value))
            )

    let containerList = containers |> Seq.map (fun x -> x.Key, x.Value) |> Seq.toList
    (generateIfElse containerList).Value



let private generateSerializeMethodForBase (generalProps: string seq, packet: Packet) =

    let identifier = SyntaxFactory.Identifier("Serialize")
    let containers = packet.Structure

    let blockSyntax =
        SyntaxFactory.Block(generateBodyForBase (generalProps, containers))

    [ SyntaxFactory
          .MethodDeclaration(SyntaxFactory.ParseTypeName("void"), identifier)
          .AddModifiers(SyntaxFactory.Token(SyntaxKind.PublicKeyword), SyntaxFactory.Token(SyntaxKind.VirtualKeyword))
          .AddParameterListParameters(writerParameter, protocolVersionParameter)
          .WithBody(blockSyntax)
      :> MemberDeclarationSyntax ]

let private containsProperty (cl: ClassDeclarationSyntax) =
    cl.Members |> Seq.exists (fun x -> x :? PropertyDeclarationSyntax)

let private allClassesEmpty (classes: ClassDeclarationSyntax array) =
    classes |> Array.forall containsProperty

let private optimization (cl: ClassDeclarationSyntax, packet: Packet) : ClassDeclarationSyntax =
    if packet.PacketName.ToLower().Contains("unload") then
        Debugger.Break()

    let internalClasses = ResizeArray()

    for m in cl.Members do
        match m with
        | :? ClassDeclarationSyntax as c -> internalClasses.Add(c)
        | _ -> ()

    if internalClasses.Count = 0 then
        cl
    else if allClassesEmpty (internalClasses.ToArray()) then
        cl
    else
        let newMembers =
            cl.Members
            |> Seq.map (fun m ->
                match m with
                | :? ClassDeclarationSyntax as c ->
                    c.WithModifiers(
                        SyntaxFactory.TokenList(
                            SyntaxFactory.Token(SyntaxKind.InternalKeyword),
                            SyntaxFactory.Token(SyntaxKind.SealedKeyword)
                        )
                    )
                    :> MemberDeclarationSyntax
                | _ -> m)

        let newMembers = newMembers |> Seq.toArray

        cl
            .WithMembers(SyntaxList<MemberDeclarationSyntax> newMembers)
            .WithModifiers(SyntaxFactory.TokenList(SyntaxFactory.Token(SyntaxKind.PublicKeyword)))



let generatePrimitive (packets: PacketMetadata list, folder: string) =
    let protodefPackets = packets |> Seq.map packetMetadataToProtodefPacket

    Directory.CreateDirectory(Path.Combine("packets", folder, "generated"))
    |> ignore

    for p in protodefPackets do
        let members =
            (generateClasses (
                p,
                [| SyntaxKind.PublicKeyword |],
                "IClientPacket",
                generateSerializeMethod,
                generateSerializeMethodForBase
            ))
            |> Seq.cast<MemberDeclarationSyntax>
            |> Seq.toArray

        let cl = (members |> Array.head) :?> ClassDeclarationSyntax

        optimization (cl, p)

        let packetName = p.PacketName

        let filePath = Path.Combine("packets", folder, "generated", $"{packetName}.cs")


        let ns =
            SyntaxFactory
                .NamespaceDeclaration(SyntaxFactory.ParseName("MinecraftDataFSharp"))
                .AddMembers(members)

        File.WriteAllText(filePath, ns.NormalizeWhitespace().ToFullString())

    ignore
