#pragma once

class Graphics
{
public:
    static Graphics &Instance()
    {
        static Graphics instance;
        return instance;
    }

    void SetColor(unsigned int r, unsigned int g, unsigned int b)
    {
        mDefaultColor.r = r;
        mDefaultColor.g = g;
        mDefaultColor.b = b;
    }

    void SetAlpha(unsigned int a)
    {
        mDefaultColor.a = a;
    }

    void SetFont(unsigned int id)
    {
        mDefaultFont = AssetManager::Instance().GetFont(id);
    }

    void Circle(float x, float y, float radius, bool mIsLine)
    {
        if (!IsReady)
            return;
        if (mIsLine)
        {
            DrawCircleLines(x, y, radius, mDefaultColor);
        }
        else
        {
            DrawCircle(x, y, radius, mDefaultColor);
        }
    }

    void Line(float x1, float y1, float x2, float y2)
    {
        if (!IsReady)
            return;
        DrawLine(x1, y1, x2, y2, mDefaultColor);
    }

    void Rect(float x, float y, float width, float height, bool mIsLine)
    {
        if (!IsReady)
            return;
        if (mIsLine)
        {
            Rectangle r;
            r.x = x;
            r.y = y;
            r.width = width;
            r.height = height;
            DrawRectangleLinesEx(r, mlineThickness, mDefaultColor);
        }
        else
        {
            DrawRectangle(x, y, width, height, mDefaultColor);
        }
    }

    void Ring(float x, float y, float innerRadius, float outerRadius, float startAngle, float endAngle, bool mIsLine)
    {
        if (!IsReady)
            return;
        Vector2 center;
        center.x = x;
        center.y = y;

        if (mIsLine)
        {
            DrawRingLines(center, innerRadius, outerRadius, startAngle, endAngle, mSegments, mDefaultColor);
        }
        else
        {
            DrawRing(center, innerRadius, outerRadius, startAngle, endAngle, mSegments, mDefaultColor);
        }
    }
    void RectangleRounded(float x, float y, float width, float height, float rounding, bool mIsLine)
    {
        if (!IsReady)
            return;
        Rectangle r;
        r.x = x;
        r.y = y;
        r.width = width;
        r.height = height;

        if (mIsLine)
        {
            DrawRectangleRoundedLines(r, rounding, mSegments, mlineThickness, mDefaultColor);
        }
        else
        {
            DrawRectangleRounded(r, rounding, mSegments, mDefaultColor);
        }
    }

    // DrawEllipse

    void Ellipse(float x, float y, float radiusx, float radiusy, bool mIsLine)
    {
        if (!IsReady)
            return;
        if (mIsLine)
        {
            DrawEllipseLines(x, y, radiusx, radiusy, mDefaultColor);
        }
        else
        {
            DrawEllipse(x, y, radiusx, radiusy, mDefaultColor);
        }
    }
    void Point(float x, float y)
    {
        if (!IsReady)
            return;
        DrawPixel(x, y, mDefaultColor);
    }

    void Text(float x, float y, const char *text)
    {
        if (!IsReady)
            return;
        DrawText(text, x, y, mTextSize, mDefaultColor);
    }

    void SetLineThickness(float thickness)
    {
        if (!IsReady)
            return;
        mlineThickness = thickness;
    }

    void SetTextSize(int size)
    {
        if (!IsReady)
            return;
        mTextSize = size;
    }

    void SetSegments(int segments)
    {
        mSegments = segments;
    }

    void Begin()
    {
        if (!IsReady)
            return;
        BeginMode2D(mCamera);
    }

    void End()
    {
        if (!IsReady)
            return;
        EndMode2D();
    }
    void SetViewPosition(float x, float y)
    {
        mCamera.target.x = x;
        mCamera.target.y = y;
    }

    void SetViewZoom(float value)
    {
        mCamera.zoom = value;
    }

    void SetViewRotation(float value)
    {
        mCamera.rotation = value;
    }

    void SetViewCenter(float x, float y)
    {
        mCamera.offset.x = x;
        mCamera.offset.y = y;
    }

    void Render(unsigned int id, float x, float y)
    {
        if (!IsReady)
            return;
        Texture2D texture = AssetManager::Instance().GetTexture(id);
        DrawTexture(texture, x, y, mDefaultColor);
    }
    void Render(unsigned int id, float x, float y, float scale, float rotation)
    {
        if (!IsReady)
            return;
        Texture2D texture = AssetManager::Instance().GetTexture(id);
        Vector2 center;
        center.x = x;
        center.y = y;
        DrawTextureEx(texture, center, rotation, scale, mDefaultColor);
    }

    void ShowFPS(int x,int y)
    {
        if (!IsReady)
            return;
        DrawFPS(x,y);
    }

    void Clear(int r, int g, int b)
    {
        if (!IsReady)
            return;
        mBackgroundColor.r = r;
        mBackgroundColor.g = g;
        mBackgroundColor.b = b;

        ClearBackground(mBackgroundColor);
    }

private:
    Graphics()
    {
        mDefaultFont = GetFontDefault();
        mTextSize = mDefaultFont.baseSize;

        mCamera.target.x = 0.0f;
        mCamera.target.y = 0.0f;

        mCamera.offset.y = 0.0f;
        mCamera.offset.x = 0.0f;

        mCamera.rotation = 0.0f;
        mCamera.zoom = 1.0f;

        mDefaultColor = {255, 255, 255, 255};
    }
    ~Graphics() {}

    Graphics(const Graphics &) = delete;
    Graphics &operator=(const Graphics &) = delete;

    Color mDefaultColor;
    Font mDefaultFont;
    int mSegments = 32;
    float mlineThickness = 1.0f;
    int mTextSize;
    Camera2D mCamera;
    Color mBackgroundColor = {0, 0, 0, 255};
};

static void graphics_clear(int r, int g, int b)
{
    Graphics::Instance().Clear(r, g, b);
}

static void graphics_set_color(int r, int g, int b)
{
    Graphics::Instance().SetColor(r, g, b);
}

static void graphics_set_font(int id)
{
    Graphics::Instance().SetFont(id);
}

static void graphics_set_view_position(float x, float y)
{
    Graphics::Instance().SetViewPosition(x, y);
}

static void graphics_set_view_zoom(float value)
{
    Graphics::Instance().SetViewZoom(value);
}

static void graphics_set_view_rotation(float value)
{
    Graphics::Instance().SetViewRotation(value);
}

static void graphics_set_view_center(float x, float y)
{
    Graphics::Instance().SetViewCenter(x, y);
}

static void graphics_set_line_thickness(float thickness)
{
    Graphics::Instance().SetLineThickness(thickness);
}

static void graphics_set_text_size(int size)
{
    Graphics::Instance().SetTextSize(size);
}

static void graphics_set_segments(int segments)
{
    Graphics::Instance().SetSegments(segments);
}

static void graphics_begin_view()
{
    Graphics::Instance().Begin();
}

static void graphics_end_view()
{
    Graphics::Instance().End();
}

static void graphics_show_fps(int x, int y)
{
    Graphics::Instance().ShowFPS(x, y);
}

static void graphics_render(unsigned int id, float x, float y)
{
    Graphics::Instance().Render(id, x, y);
}

static void graphics_render_scale_rotate(unsigned int id, float x, float y, float scale, float rotation)
{
    Graphics::Instance().Render(id, x, y, scale, rotation);
}

static void graphics_rect(float x, float y, float width, float height, bool mIsLine)
{
    Graphics::Instance().Rect(x, y, width, height, mIsLine);
}

static void graphics_rectangle_rounded(float x, float y, float width, float height, float rounding, bool mIsLine)
{
    Graphics::Instance().RectangleRounded(x, y, width, height, rounding, mIsLine);
}

static void graphics_circle(float x, float y, float radius, bool mIsLine)
{
    Graphics::Instance().Circle(x, y, radius, mIsLine);
}

static void graphics_ellipse(float x, float y, float radiusx, float radiusy, bool mIsLine)
{
    Graphics::Instance().Ellipse(x, y, radiusx, radiusy, mIsLine);
}

static void graphics_ring(float x, float y, float innerRadius, float outerRadius, float startAngle, float endAngle, bool mIsLine)
{
    Graphics::Instance().Ring(x, y, innerRadius, outerRadius, startAngle, endAngle, mIsLine);
}

static void graphics_line(float x1, float y1, float x2, float y2)
{
    Graphics::Instance().Line(x1, y1, x2, y2);
}

static void graphics_text(float x, float y, const std::string &text)
{
    Graphics::Instance().Text(x, y, text.c_str());
}

static void graphics_text_int(float x, float y, int value)
{
    std::string text = std::to_string(value);
    Graphics::Instance().Text(x, y, text.c_str());
}


inline void RegisterGraphicsFunctions(asIScriptEngine *engine)
{
    int r;
    r = engine->SetDefaultNamespace("graphics"); assert(r >= 0);


    r = engine->RegisterGlobalFunction("void clear(int,int,int)", asFUNCTION(graphics_clear), asCALL_CDECL); assert(r >= 0);

    r = engine->RegisterGlobalFunction("void set_color(int,int,int)", asFUNCTION(graphics_set_color), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("void set_font(int)", asFUNCTION(graphics_set_font), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("void set_line_thickness(float)", asFUNCTION(graphics_set_line_thickness), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("void set_text_size(int)", asFUNCTION(graphics_set_text_size), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("void set_segments(int)", asFUNCTION(graphics_set_segments), asCALL_CDECL); assert(r >= 0);

    r = engine->RegisterGlobalFunction("void begin()", asFUNCTION(BeginDrawing), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("void end()", asFUNCTION(EndDrawing), asCALL_CDECL); assert(r >= 0);


    r = engine->RegisterGlobalFunction("void set_view_position(float,float)", asFUNCTION(graphics_set_view_position), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("void set_view_zoom(float)", asFUNCTION(graphics_set_view_zoom), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("void set_view_rotation(float)", asFUNCTION(graphics_set_view_rotation), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("void set_view_center(float,float)", asFUNCTION(graphics_set_view_center), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("void begin_view()", asFUNCTION(graphics_begin_view), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("void end_view()", asFUNCTION(graphics_end_view), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("void show_fps(int,int)", asFUNCTION(graphics_show_fps), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("void render( int,float,float)", asFUNCTION(graphics_render), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("void render_scale_rotate( int,float,float,float,float)", asFUNCTION(graphics_render_scale_rotate), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("void rectangle(float,float,float,float,bool)", asFUNCTION(graphics_rect), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("void rounded_rectangle(float,float,float,float,float,bool)", asFUNCTION(graphics_rectangle_rounded), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("void circle(float,float,float,bool)", asFUNCTION(graphics_circle), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("void ellipse(float,float,float,float,bool)", asFUNCTION(graphics_ellipse), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("void ring(float,float,float,float,float,float,bool)", asFUNCTION(graphics_ring), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("void line(float,float,float,float)", asFUNCTION(graphics_line), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("void text(float,float,const string &in)", asFUNCTION(graphics_text), asCALL_CDECL); assert(r >= 0);
    r = engine->RegisterGlobalFunction("void text_int(float,float,int)", asFUNCTION(graphics_text_int), asCALL_CDECL); assert(r >= 0);






   // r = engine->SetDefaultNamespace(""); assert(r >= 0);

}