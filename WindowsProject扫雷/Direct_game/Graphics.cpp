#include"Graphics.h"

Graphics::Graphics()
{
	factory = NULL;
	renderTarget = NULL;
	brush = NULL;
}

Graphics::~Graphics()
{
	if (factory)factory->Release();

	if (renderTarget)renderTarget->Release();

	if (brush)brush->Release();
}

bool Graphics::Init(HWND windowHandle)
{
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (res != S_OK) return false;

	RECT rect;

	GetClientRect(windowHandle, &rect);
	factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			windowHandle, 
			D2D1::SizeU(rect.right, rect.bottom)),
		&renderTarget);

	if (res != S_OK) return false;
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0), &brush);
	if (res != S_OK) return false;

	return true;
}

bool Graphics::ResizeRenderTarget(HWND windowHandle)
{
	RECT rect;
	GetClientRect(windowHandle, &rect);
	
	if (S_OK == renderTarget->Resize(D2D1::SizeU(rect.right, rect.bottom)))
		return false;

	return true;
}

void Graphics::ClearScreen(float r, float g, float b)
{
	renderTarget->Clear(D2D1::ColorF(r, g, b));
}

void Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b,float a)
{
	brush->SetColor(D2D1::ColorF(r, g, b));
	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 3.0f);
}

void Graphics::DrawEllipse(float x, float y, float radiusX, float radiusY, float r, float g, float b, float a)
{
	brush->SetColor(D2D1::ColorF(r, g, b));
	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radiusX, radiusY), brush);
}

void Graphics::DrawLine(float x1, float y1, float x2, float y2, float r, float g, float b, float a)
{
	brush->SetColor(D2D1::ColorF(r, g, b));
	renderTarget->DrawLine(D2D1::Point2F(x1, y1), D2D1::Point2F(x2, y2), brush);
}

void Graphics::DrawRectangle(float x1, float y1, float x2, float y2, float r, float g, float b, float a)
{
	brush->SetColor(D2D1::ColorF(r, g, b));
	renderTarget->DrawRectangle(D2D1::RectF(x1, y1, x2, y2), brush);
}
