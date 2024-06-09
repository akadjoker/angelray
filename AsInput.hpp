#pragma once

inline void RegisterKeysFunctions(asIScriptEngine *engine)
{
    int r;
    r = engine->SetDefaultNamespace("keyboard"); assert(r >= 0);

    r = engine->RegisterGlobalFunction("bool pressed(int)", asFUNCTION(IsKeyPressed), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("bool released(int)", asFUNCTION(IsKeyReleased), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("bool down(int)", asFUNCTION(IsKeyDown), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("bool up(int)", asFUNCTION(IsKeyUp), asCALL_CDECL); assert(r >= 0);


  //  r = engine->SetDefaultNamespace(""); assert(r >= 0);
}

inline void RegisterMouseFunctions(asIScriptEngine *engine)
{
    int r;
    r = engine->SetDefaultNamespace("mouse"); assert(r >= 0);

    r = engine->RegisterGlobalFunction("bool pressed(int)", asFUNCTION(IsMouseButtonPressed), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("bool released(int)", asFUNCTION(IsMouseButtonReleased), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("bool down(int)", asFUNCTION(IsMouseButtonDown), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("bool up(int)", asFUNCTION(IsMouseButtonUp), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("int x()", asFUNCTION(GetMouseX), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("int y()", asFUNCTION(GetMouseY), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("float wheel()", asFUNCTION(GetMouseWheelMove), asCALL_CDECL); assert(r >= 0);


    //r = engine->SetDefaultNamespace(""); assert(r >= 0);
}