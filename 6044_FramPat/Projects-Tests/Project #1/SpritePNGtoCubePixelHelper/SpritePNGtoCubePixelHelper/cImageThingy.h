#pragma once

#include <string>
#include <vector>

//  This is to help load the sprite sheets and 
//	get the pixel information out.


struct sPixelRGBA
{
	unsigned char R = 0;
	unsigned char G = 0;
	unsigned char B = 0;
	unsigned char A = 0;

	sPixelRGBA()
	{
		this->R = this->G = this->B = 0;
		this->A = 255;
	}

	sPixelRGBA(unsigned char R_, unsigned char G_, unsigned char B_)
	{
		this->R = R_;
		this->G = G_;
		this->B = B_;
		this->A = 255;
	}
	sPixelRGBA(unsigned char R_, unsigned char G_, unsigned char B_, unsigned char A_)
	{
		this->R = R_;
		this->G = G_;
		this->B = B_;
		this->A = A_;
	}



	void setBlackThreshold(unsigned char minRed, unsigned char minGreen, unsigned minBlue)
	{
		this->isBlackColourThreshold[0] = minRed;
		this->isBlackColourThreshold[1] = minGreen;
		this->isBlackColourThreshold[2] = minBlue;
		return;
	}
	bool isBlack(void)
	{
		if (R > this->isBlackColourThreshold[0]) { return false; }
		if (G > this->isBlackColourThreshold[1]) { return false; }
		if (B > this->isBlackColourThreshold[2]) { return false; }
		// It's "black" coloured
		return true;
	}

private:
	// Default "black" colour is 0 (Actually black)
	unsigned char isBlackColourThreshold[3] = { 0 };
};



bool operator==(const sPixelRGBA& lhs, const sPixelRGBA& rhs);
bool operator!=(const sPixelRGBA& lhs, const sPixelRGBA& rhs);

class cImageThingy
{
public:
	cImageThingy();


	bool loadImage(std::string filename);

	// NOTE: This uses the m_2D_image (from loadImage() to crop)
	// It will then update:
	//	- the m_2D_image
	//	- the width and height or the original
	//  - the m_image vector
	// In other words, it should change it to be AS IF it loaded the cropped image
	void cropOutBackground(sPixelRGBA backgroundColour);
	void cropOutBackgroundWithTransparency(void);

	// Height and width of loaded image
	unsigned int getHeight(void);
	unsigned int getWidth(void);

	// returns a "black" pixel if out of bounds
	sPixelRGBA getPixel(unsigned int raw1DIndex);
	// Row is from the width
	// Column is from the height
	// 0, 0 is index 0 of the 1D image
	// Returns a "black" pixel if out of bounds
	sPixelRGBA getPixel(unsigned int row, unsigned int column);	// From 2D array
	// Same but uses the pixel size to offset
	sPixelRGBA getPixelScaled(unsigned int row, unsigned int column);
	sPixelRGBA getPixelScaled(unsigned int index1D);
	//
	unsigned int getScaledHeight(void);
	unsigned int getScaledWidth(void);

	// Returns 0 if it can't figure it out
	unsigned int guessPixelSize(void);

	unsigned int getTotalRawPixels(void);
	unsigned int getPixelSize(void);


	// Goes through the original loaded image and 
	//	makes a new, scaled image with the average colours
	//	of all the pixels
	void setPixelSizeAndProcess(unsigned int pixelSize);

	std::string getLastError(bool bClearErrorOnRead = true);

private:
	unsigned int m_height = 0;
	unsigned int m_width = 0;
	// Width x Height
	unsigned int m_totalPixels = 0;
	unsigned int m_pixelSize = 1;
	//
	unsigned int m_scaled_height = 0;
	unsigned int m_scaled_width = 0;

	sPixelRGBA m_getAveragePixelColour(unsigned int scaledRowIndex, unsigned int scaledColIndex);

	//the raw pixels in 4 bytes per pixel, ordered RGBARGBA.
	// The one that png::decode() generates
	std::vector<unsigned char> m_image;
	// Like above, but organized by pixels (not raw chars)
	std::vector<sPixelRGBA> m_1D_pixels;
	// This in a more helpsul 2D array
	std::vector< std::vector< sPixelRGBA > > m_2D_pixels;

	// Like above, but the pixels are scaled based on the pixel size
	std::vector< std::vector< sPixelRGBA > > m_2D_ScaledPixels;

	std::string m_lastError;

	// Top row is index 0
	void m_removeRow(unsigned int rowIndex);
	bool m_bIsRowThisColour(unsigned int rowIndex, sPixelRGBA thisColour);
	bool m_bIsRowTransparent(unsigned int rowIndex);
	// Left column is index 0
	void m_removeColumn(unsigned int colIndex);
	bool m_bIsColumnThisColour(unsigned int colIndex, sPixelRGBA thisColour);
	bool m_bIsColumnTransparent(unsigned int colIndex);

	// This is done after any of the "remove" methods above
	void m_resetLoadedDataToMatch2DPixelArray(void);

};
