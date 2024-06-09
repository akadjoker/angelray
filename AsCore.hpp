#pragma once




inline void RegisterCoreFunctions(asIScriptEngine *engine)
{
    int r;
    r = engine->SetDefaultNamespace("core"); assert(r >= 0);

    
    r = engine->RegisterGlobalFunction("int random(int,int)", asFUNCTION(GetRandomValue), asCALL_CDECL); assert(r >= 0);




    // Retorna ao namespace global
   // r = engine->SetDefaultNamespace(""); assert(r >= 0);
}

static void windwo_init(int w, int h, const std::string &title)
{
    if (IsReady) return ;
    InitWindow(w, h, title.c_str());
    IsReady = true;
}

static void window_close()
{
    if (!IsReady) return;
    AssetManager::Instance().Clear();
    AssetManager::Instance().Free();
    CloseWindow();
    IsReady = false;
}
static void windwo_title(const std::string &title)
{
    SetWindowTitle(title.c_str());
}


inline void RegisterWindowFunctions(asIScriptEngine *engine)
{
    int r;
    r = engine->SetDefaultNamespace("window"); assert(r >= 0);

    
    r = engine->RegisterGlobalFunction("void init( int, int, const string &in)", asFUNCTION(windwo_init), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("void close()", asFUNCTION(window_close), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("bool should_close()", asFUNCTION(WindowShouldClose), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("int get_width()", asFUNCTION(GetScreenWidth), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("int get_height()", asFUNCTION(GetScreenHeight), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("void set_title(const string &in)", asFUNCTION(windwo_title), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("void set_position(int, int)", asFUNCTION(SetWindowPosition), asCALL_CDECL); assert(r >= 0);


   // r = engine->SetDefaultNamespace(""); assert(r >= 0);
}