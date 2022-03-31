#pragma once

#include"Windows.h"
#include<d2d1_3.h>
//d2d1.lib;
class Graphics
{
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;
	ID2D1SolidColorBrush* brush;
public:
	Graphics();
	~Graphics();

	bool Init(HWND windowHandle);

	ID2D1RenderTarget* GetRenderTarget() 
	{
		return renderTarget;
	}

	void BeginDraw()
	{
		renderTarget->BeginDraw();
	}
	void EndDraw()
	{
		renderTarget->EndDraw();
	}
	bool ResizeRenderTarget(HWND windowHandle);
	void ClearScreen(float r, float g, float b);
	void DrawCircle(float x, float y, float radius, float r,float g, float b,float a);
	void DrawEllipse(float x, float y, float radiusX, float radiusY, float r, float g, float b, float a);
	void DrawLine(float x1, float y1, float x2, float y2, float r, float g, float b, float a);
	void DrawRectangle(float x1, float y1, float x2, float y2, float r, float g, float b, float a);

};