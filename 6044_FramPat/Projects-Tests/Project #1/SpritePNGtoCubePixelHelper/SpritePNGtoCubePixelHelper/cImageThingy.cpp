#include "cImageThingy.h"
#include "lodepng.h"

// See: https://lodev.org/lodepng/
// for more information about how to use the png loader
// Looked here for most of it: 
// https://raw.githubusercontent.com/lvandeve/lodepng/master/examples/example_decode.cpp


cImageThingy::cImageThingy()
{
	this->m_height = this->m_width = 0;
}

bool cImageThingy::loadImage(std::string filename)
{
	//std::vector<unsigned char> image; //the raw pixels
	//unsigned width, height;

	//decode
	unsigned error = lodepng::decode(this->m_image, this->m_width, this->m_height, filename);

	if (error)
	{
		this->m_lastError.append(lodepng_error_text(error));
		return false;
	}

	// Convert this stream of RGBA chars into a 1D pixel array
	// +4 because it's in RGBA format (4 chars per pixel)
	for (unsigned int charIndex = 0; charIndex < this->m_image.size(); charIndex += 4)
	{
		sPixelRGBA curPixel;
		curPixel.R = this->m_image[charIndex];
		curPixel.G = this->m_image[charIndex + 1];
		curPixel.B = this->m_image[charIndex + 2];
		curPixel.A = this->m_image[charIndex + 3];
		this->m_1D_pixels.push_back(curPixel);
	}

	// Make the 2D image from the 1D one
	for (unsigned int rowCount = 0; rowCount != this->m_height; rowCount++)
	{
		std::vector<sPixelRGBA> vecNewRow;
		for (unsigned int colIndex = 0; colIndex != this->m_width; colIndex++)
		{
			unsigned int pixelIndex = (rowCount * this->m_width) + colIndex;
			vecNewRow.push_back(this->getPixel(pixelIndex));
		}

		this->m_2D_image.push_back(vecNewRow);
	}

	return true;
}

std::string cImageThingy::getLastError(bool bClearErrorOnRead /*=true*/)
{
	std::string theError = this->m_lastError;
	if (bClearErrorOnRead)
	{
		this->m_lastError = "";
	}
	return theError;
}


// Height and width of loaded image
unsigned int cImageThingy::getHeight(void)
{
	return this->m_height;
}

unsigned int cImageThingy::getWidth(void)
{
	return this->m_width;
}

// Goes through the original loaded image and 
//	makes a new, scaled image with the average colours
//	of all the pixels
void cImageThingy::setPixelSizeAndProcess(unsigned int pixelSize)
{
	this->m_pixelSize = pixelSize;

	// Like above, but the pixels are scaled based on the pixel size
	std::vector< std::vector< sPixelRGBA > > m_2D_ScaledImage;

	// Calculate this based on the size of the loaded image
	this->m_scaled_height = this->m_height / pixelSize;
	this->m_scaled_width = this->m_width / pixelSize;


	// make an empty SCALED 2D array of pixels
	for (unsigned int rowCount = 0; rowCount != this->m_scaled_height; rowCount++)
	{
		std::vector<sPixelRGBA> vecNewRow;
		for (unsigned int colIndex = 0; colIndex != this->m_scaled_width; colIndex++)
		{
			sPixelRGBA scaledPixel = this->m_getAveragePixelColour(rowCount, colIndex);
			vecNewRow.push_back(scaledPixel);
		}

		this->m_2D_ScaledImage.push_back(vecNewRow);
	}

	return;
}

sPixelRGBA cImageThingy::m_getAveragePixelColour(unsigned int scaledRowIndex, unsigned int scaledColIndex)
{
	// Calculate the corners of the original pixel area
	unsigned int rowStart = scaledRowIndex * this->m_pixelSize;
	unsigned int rowEnd = rowStart + this->m_pixelSize;
	unsigned int columnStart = scaledColIndex * this->m_pixelSize;
	unsigned int columnEnd = columnStart + this->m_pixelSize;

	// The sum of all the colours (R, B, G, A)
	unsigned int pixelTotals[4] = { 0 };

	unsigned int totalPixelsRead = 0;

	for (unsigned int rowIndex = rowStart; rowIndex != rowEnd; rowIndex++)
	{
		for (unsigned int colIndex = columnStart; colIndex != columnEnd; colIndex++)
		{
			sPixelRGBA curPixel = this->getPixel(rowIndex, colIndex);

			pixelTotals[0] += curPixel.R;
			pixelTotals[1] += curPixel.G;
			pixelTotals[2] += curPixel.B;
			pixelTotals[3] += curPixel.A;

			totalPixelsRead++;
		}//for (unsigned int colIndex
	}//for (unsigned int rowIndex

	// Calculate average
	sPixelRGBA averagePixel;
	averagePixel.R = pixelTotals[0] /= totalPixelsRead;
	averagePixel.G = pixelTotals[1] /= totalPixelsRead;
	averagePixel.B = pixelTotals[2] /= totalPixelsRead;
	averagePixel.A = pixelTotals[3] /= totalPixelsRead;

	return averagePixel;
}


unsigned int cImageThingy::getScaledHeight(void)
{
	return this->m_scaled_height;
}

unsigned int cImageThingy::getScaledWidth(void)
{
	return this->m_scaled_width;
}

unsigned int cImageThingy::getTotalRawPixels(void)
{
	return this->m_totalPixels;
}

unsigned int cImageThingy::getPixelSize(void)
{
	return this->m_pixelSize;
}


// Returns false if it can't figure it out
unsigned int cImageThingy::guessPixelSize(void)
{
	// TODO: For now, just return 1
	return 1;
}

sPixelRGBA cImageThingy::getPixel(unsigned int raw1DIndex)
{
	if (raw1DIndex >= this->m_1D_pixels.size())
	{
		// Invalid pixel
		return sPixelRGBA();
	}
	return this->m_1D_pixels[raw1DIndex];
}

// Row is from the width
// Column is from the height
// 0, 0 is index 0 of the 1D image
sPixelRGBA cImageThingy::getPixel(unsigned int row, unsigned int column)
{
	if (row > this->m_height || column > this->m_width)
	{
		return sPixelRGBA();
	}

	return this->m_2D_image[row][column];
}

// Same but uses the pixel size to offset
sPixelRGBA cImageThingy::getPixelScaled(unsigned int row, unsigned int column)
{
	if (row > this->m_scaled_height || column > this->m_scaled_width)
	{
		return sPixelRGBA();
	}
	return this->m_2D_ScaledImage[row][column];
}



