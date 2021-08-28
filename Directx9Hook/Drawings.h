#include "dx.h"

LPD3DXLINE m_Line;

int GetHeightInPixels(LPD3DXFONT Font)
{
    TEXTMETRICW txtmet;
    Font->GetTextMetrics(&txtmet);
    return  txtmet.tmHeight;
}

int GetLengthInPixels(LPCSTR TextToDraw, LPD3DXFONT Font)
{
    TEXTMETRICW txtmet;

    Font->GetTextMetrics(&txtmet);

    int size = 0;

    for (int i = 0; TextToDraw[i] != '\0'; i++) {
        size++;
    }

    return size * (txtmet.tmAveCharWidth + 1);
}


void DrawFilledRectangle(float x, float y, float w, float h, int a, int r, int g, int b)
{
    D3DCOLOR color = D3DCOLOR_ARGB(a, r, g, b);
    D3DRECT rect = { x, y,x + w,y + h };
    pDevice->Clear(1, &rect, D3DCLEAR_TARGET, color, 1, 0);
}

void DrawString(char* String, int x, int y, int r, int g, int b, LPD3DXFONT pfont, bool Centered = false, bool Shadow = false)
{
    int w = GetLengthInPixels(String, pfont);
    int h = GetHeightInPixels(pfont);

    int centerx = Centered ? x - (w / 2) : x;
    int centery = Centered ? y - h : y;

    RECT Font;
    Font.bottom = 0;
    Font.left = centerx;
    Font.top = centery;
    Font.right = 0;

    RECT Fonts;
    Fonts.bottom = 0;
    Fonts.left = centerx + 1;
    Fonts.top = centery + 1;
    Fonts.right = 0;

    if (Shadow)
        pfont->DrawTextA(0, String, strlen(String), &Fonts, DT_NOCLIP, D3DCOLOR_ARGB(255, 1, 1, 1));

    pfont->DrawTextA(0, String, strlen(String), &Font, DT_NOCLIP, D3DCOLOR_ARGB(255, r, g, b));
}

void DrawBorderBox(int x, int y, int w, int h, int thickness, int a, int r, int g, int b)
{
    DrawFilledRectangle(x, y, thickness, h, a, r, g, b);//|left
    DrawFilledRectangle(x + w, y, thickness, h, a, r, g, b);//  |right
    DrawFilledRectangle(x, y, w, thickness, a, r, g, b);// ---top
    DrawFilledRectangle(x, y + h, w + thickness, thickness, a, r, g, b);// ___bottom
}

void DrawLine(int x1, int y1, int x2, int y2, int thickness, D3DCOLOR color)
{
    D3DXVECTOR2 Line[2];
    Line[0] = D3DXVECTOR2(x1, y1);
    Line[1] = D3DXVECTOR2(x2, y2);

    m_Line[0].SetGLLines(0);
    m_Line[0].SetAntialias(1);

    m_Line[0].SetWidth(thickness);
    m_Line[0].SetAntialias(true);
    m_Line[0].Begin();
    m_Line[0].Draw(Line, 2, color);
    m_Line[0].End();
}