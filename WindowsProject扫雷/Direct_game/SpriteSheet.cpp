#include"SpriteSheet.h"

SpriteSheet::SpriteSheet(LPCWSTR filename, Graphics * gfx)
{
	graphics = gfx;
	bmp = NULL;
	HRESULT hr;
	IWICImagingFactory * wicFactory = NULL;

	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicFactory);


	IWICBitmapDecoder * wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
		filename,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&wicDecoder);

	if (hr != S_OK)
		return;

	IWICBitmapFrameDecode * wicFrame = NULL;
	hr = wicDecoder -> GetFrame(0, &wicFrame);


	IWICFormatConverter * wicCoverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicCoverter);


	hr = wicCoverter->Initialize(
		wicFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0,
		WICBitmapPaletteTypeCustom);


	graphics->GetRenderTarget()->CreateBitmapFromWicBitmap(
		wicCoverter,
		NULL,
		&bmp);

	if (wicFactory)wicFactory->Release();
	if (wicDecoder)wicDecoder->Release();
	if (wicCoverter)wicCoverter->Release();
	if (wicFrame)wicFrame->Release();

	if (bmp != NULL) 
	{
		spriteWidth = (int)bmp->GetSize().width;
		spriteHeight = (int)bmp->GetSize().height;
	}
	spriteAccross = 1;
}

SpriteSheet::SpriteSheet(LPCWSTR filename, Graphics * gfx, int width, int height) :
	SpriteSheet(filename, gfx)
{
	spriteWidth = width;
	spriteHeight = height;
	spriteAccross = (int)((bmp->GetSize().width / spriteWidth)*(bmp->GetSize().height / spriteHeight));
}

SpriteSheet::~SpriteSheet()
{
	if (bmp)bmp->Release();
}

void SpriteSheet::Draw()//完整尺寸
{
	graphics->GetRenderTarget()->DrawBitmap(
		bmp,
		D2D1::RectF(0.0f, 0.0f,
			bmp->GetSize().width, bmp->GetSize().height),//目标
		1.0f,//透明度

		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,//最临近插值
		D2D1::RectF(0.0f, 0.0f,
			bmp->GetSize().width, bmp->GetSize().height));//源
}

void SpriteSheet::Draw(int index, int x, int y, float zoom)
{
	D2D_RECT_F src = D2D1::RectF(
		(float)((index%spriteAccross)*spriteWidth),
		(float)((index/spriteAccross)*spriteHeight),
		(float)((index%spriteAccross)*spriteWidth) + spriteWidth,
		(float)((index / spriteAccross)*spriteHeight) + spriteHeight);

	D2D_RECT_F dest = D2D1::RectF(
		(float)x,
		(float)y,
		(float)(x + spriteWidth * zoom),
		(float)(y + spriteHeight * zoom)
	);

	graphics->GetRenderTarget()->DrawBitmap(
		bmp,
		dest,//目标
		1.0f,//透明度

		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,//最临近插值
		src);//源
}
