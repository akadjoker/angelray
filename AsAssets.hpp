#pragma once



class AssetManager
{
public:
    static AssetManager &Instance()
    {
        static AssetManager instance;
        return instance;
    }

    bool ImageLoad(int id, const char *filename)
    {
        if (id == 0)
        {
            id = mLastImageId + 1;
        }
        if (images.find(id) != images.end())
        {
            Log(1,"Image ID already exists");
            return false;
        }

        Image image = LoadImage(filename);
        if (image.data == nullptr)
        {
           // Log(1,"Failed to load image");
            return false;
        }
        images[id] = image;

        mLastImageId++;

        return true;
    }

    bool ImageExists(int id) const
    {
        return images.find(id) != images.end();
    }

    Image &GetImage(int id)
    {
        if (images.find(id) == images.end())
        {
           Log(2,"Image ID not found");

           return mImageDefault;
        }
        return images[id];
    }

    void UnloadAllImages()
    {
        for (auto &pair : images)
        {
            UnloadImage(pair.second);
        }
        images.clear();
    }
    void FreeImage(int id)
    {
        if (images.find(id) == images.end())
        {
            Log(2,"Image ID not found");
            return;
        }
        UnloadImage(images[id]);
        images.erase(id);
    }

    bool TextureLoad(int id, const char *filename)
    {
        if (!IsReady) return false;
        if (id == 0)
        {
            id = mLastTextureId + 1;
        }
        if (textures.find(id) != textures.end())
        {
            Log(1,"Texture ID already exists");
            return false;
        }

        Texture2D texture = LoadTexture(filename);
        if (texture.id == 0)
        {
        //    Log(2,"Failed to load texture");
            return false;
        }
        textures[id] = texture;
        mLastTextureId++;
        

        return true;
    }

    bool TextureExists(int id) const
    {
        return textures.find(id) != textures.end();
    }

    Texture2D &GetTexture(int id)
    {
        if (textures.find(id) == textures.end())
        {
            Log(1,"Texture ID not found");
            return mTextureDefault;
        }
        return textures[id];
    }

    void UnloadAllTextures()
    {
        for (auto &pair : textures)
        {
            UnloadTexture(pair.second);
        }
        textures.clear();
    }
    void FreeTexture(int id)
    {
        if (!IsReady) return ;
        if (textures.find(id) == textures.end())
        {
            Log(2,"Texture ID not found");
            return;
        }
        UnloadTexture(textures[id]);
        textures.erase(id);
    }

    bool FontLoad(int id, const char *filename)
    {
        if (!IsReady) return false;
        if (id == 0)
        {
            id = mLastFontId + 1;
        }
        if (fonts.find(id) != fonts.end())
        {
            Log(1,"Font ID already exists");
            return false;
        }

        Font font = LoadFont(filename);
        if (font.baseSize == 0)
        {
         //   Log(2,"Failed to load font");
            return false;
        }
        fonts[id] = font;
        mLastFontId++;  

        return true;
    }

    bool FontExists(int id) const
    {
        return fonts.find(id) != fonts.end();
    }

    Font &GetFont(int id)
    {
        if (fonts.find(id) == fonts.end())
        {
            Log(1,"Font ID not found");
            return mFontDefault;
        }
        return fonts[id];
    }

    void UnloadAllFonts()
    {
        for (auto &pair : fonts)
        {
            UnloadFont(pair.second);
        }
        fonts.clear();
    }
    void FreeFont(int id)
    {
        if (fonts.find(id) == fonts.end())
        {
            Log(2,"Font ID not found");
            return;
        }
        UnloadFont(fonts[id]);
        fonts.erase(id);
    }

    void Clear()
    {
       Log(1,"Clearing all assets");
       UnloadAllImages();
       UnloadAllTextures();
       UnloadAllFonts();

    }

    void Free()
    {
            
         if (IsReady) 
        {
       
            UnloadTexture(mTextureDefault);
        }
    }

private:
    AssetManager() 
    {
        mImageDefault = GenImageColor(32, 32, MAGENTA);
        if (IsReady) 
        {
        mFontDefault = GetFontDefault();
        mTextureDefault = LoadTextureFromImage(mImageDefault);
        }
    }
    ~AssetManager()    
    { UnloadImage(mImageDefault);          }

    AssetManager(const AssetManager &) = delete;
    AssetManager &operator=(const AssetManager &) = delete;

    std::map<int, Image> images;
    std::map<int, Texture2D> textures;
    std::map<int, Font> fonts;


    long mLastImageId = 0;
    long mLastTextureId = 0;
    long mLastFontId = 0;
    Image mImageDefault;
    Texture2D mTextureDefault;
    Font mFontDefault;
};

static void assets_clear()
{
    AssetManager::Instance().Clear();
}

static bool assets_load_image(int id, const std::string &filename)
{

    return AssetManager::Instance().ImageLoad(id, filename.c_str());
}

static bool assets_texture_load(int id, const std::string &filename)
{
    return AssetManager::Instance().TextureLoad(id, filename.c_str());
}

static bool assets_font_load(int id, const std::string &filename)
{
    return AssetManager::Instance().FontLoad(id, filename.c_str());
}


static bool assets_image_exists(int id)
{
    return AssetManager::Instance().ImageExists(id);
}

static bool assets_texture_exists(int id)
{
    return AssetManager::Instance().TextureExists(id);
}

static bool assets_font_exists(int id)
{
    return AssetManager::Instance().FontExists(id);
}

static void assets_free_image(int id)
{
    AssetManager::Instance().FreeImage(id);
}

static void assets_free_texture(int id)
{
    AssetManager::Instance().FreeTexture(id);
}

static void assets_free_font(int id)
{
    AssetManager::Instance().FreeFont(id);
}




static void RegisterAssetsFunctions(asIScriptEngine *engine)
{
    int r;
    r = engine->SetDefaultNamespace("assets"); assert(r >= 0);

    r = engine->RegisterGlobalFunction("void clear()", asFUNCTION(assets_clear), asCALL_CDECL); assert(r >= 0);

    r = engine->RegisterGlobalFunction("bool load_image(int, const string &in)", asFUNCTION(assets_load_image), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("bool load_texture(int, const string &in)", asFUNCTION(assets_texture_load), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("bool load_font(int, const string &in)", asFUNCTION(assets_font_load), asCALL_CDECL); assert(r >= 0);

    r = engine->RegisterGlobalFunction("bool image_exists(int)", asFUNCTION(assets_image_exists), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("bool texture_exists(int)", asFUNCTION(assets_texture_exists), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("bool font_exists(int)", asFUNCTION(assets_font_exists), asCALL_CDECL); assert(r >= 0);
  

    r = engine->RegisterGlobalFunction("void free_image(int)", asFUNCTION(assets_free_image), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("void free_texture(int)", asFUNCTION(assets_free_texture), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("void free_font(int)", asFUNCTION(assets_free_font), asCALL_CDECL); assert(r >= 0);
    


  //  r = engine->SetDefaultNamespace(""); assert(r >= 0);
}