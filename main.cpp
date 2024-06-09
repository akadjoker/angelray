
#include "pch.hpp"
#include <angelscript.h>
#include <scriptstdstring.h>
#include <scriptarray.h>

static bool IsReady = false;

#include "AsUtils.hpp"

#include "AsInput.hpp"

#include "AsAssets.hpp"

 #include "AsGraphics.hpp"
#include "AsCore.hpp"


void MessageCallback(const asSMessageInfo *msg, void *)
{
    const char *type = "ERROR";
    if (msg->type == asMSGTYPE_WARNING)
        type = "WARNING";
    else if (msg->type == asMSGTYPE_INFORMATION)
        type = "INFO";

    std::cout << msg->section << " (" << msg->row << ", " << msg->col << ") : " << type << " : " << msg->message << std::endl;
}


void print(const std::string &msg)
{
    std::cout << msg << std::endl;
}


std::string LoadScript(const char *filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Falha ao abrir o script." << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main()
{
   
    asIScriptEngine *engine = asCreateScriptEngine();
    if (!engine)
    {
        std::cerr << "Falha ao criar a engine do AngelScript." << std::endl;
        return -1;
    }

    engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);

    RegisterStdString(engine);
    RegisterScriptArray(engine, true);


    RegisterWindowFunctions(engine);
    RegisterCoreFunctions(engine);
    RegisterMouseFunctions(engine);
    RegisterKeysFunctions(engine);
    RegisterGraphicsFunctions(engine);
    RegisterAssetsFunctions(engine);

    
    engine->SetDefaultNamespace("");

    engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(print), asCALL_CDECL);


   
    std::string script = LoadScript("main.as");
    if (script.empty())
    {
        std::cerr << "Script vazio ou não encontrado." << std::endl;
        engine->Release();
        return -1;
    }

  
    asIScriptModule *mod = engine->GetModule("Main", asGM_ALWAYS_CREATE);
    mod->AddScriptSection("script", script.c_str());

 
    int r = mod->Build();
    if (r < 0)
    {
        std::cerr << "Falha ao compilar o script." << std::endl;
        engine->Release();
        return -1;
    }


    asIScriptContext *ctx = engine->CreateContext();
    if (!ctx)
    {
        std::cerr << "Falha ao criar o contexto." << std::endl;
        engine->Release();
        return -1;
    }

    r = ctx->Prepare(mod->GetFunctionByDecl("void main()"));
    if (r < 0)
    {
        std::cerr << "Function main nao encontrada." << std::endl;
        ctx->Release();
        engine->Release();
        return -1;
    }

    r = ctx->Execute();
    if (r != asEXECUTION_FINISHED)
    {
        std::cerr << "Falha ao executar o script." << std::endl;
        ctx->Release();
        engine->Release();
        return -1;
    }

    ctx->Release();

    engine->Release();
    return 0;
}
