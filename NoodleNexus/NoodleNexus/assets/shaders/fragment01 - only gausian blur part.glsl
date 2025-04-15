	if ( b_Is_FBO_Texture )
	{
//		vec3 texColour00 = texture( texture00, fUV.st ).rgb;
//		vertexColour.rgb = texColour00.rgb;	
		//     -1   0   +1
		//  -1  .   +    .
		//   0  +   O    +
		//  +1  .   +    .
		//
		// Kernel size is 3 or 3x3 
		// size of 5 would 5 samples x 5 samples = 25
		// 
		// +++++
		// +++++
		// ++O++
		// +++++
		// +++++
//		
		// ....+.....
		// ....+.....
		// ....+.....
		// ++++O+++++
		// ....+.....
		// ....+.....
		// ....+.....
//		
		// Note: While you CAN pass multi-dimensional arrays
		//       through uniform variables, you CAN'T as constant arrays.
		//
		// int[5][5] gaussian_blur_5x5;		// Illegal
		//
		// So I'm doing this strange thing:
		struct sRow
		{
			int column[5];
		};
//		
		sRow gaussian_5x5[5];
		// I took the 5x5 kernel from here:
//		// https://en.wikipedia.org/wiki/Kernel_(image_processing)
		gaussian_5x5[0].column = int[](1,  4,  6,  4, 1);	// Note strange array init
		gaussian_5x5[1].column = int[](4, 16, 24, 16, 1);	// Note strange array init
		gaussian_5x5[2].column = int[](6, 24, 36, 24, 6);	// Note strange array init
		gaussian_5x5[3].column = int[](4, 16, 24, 16, 1);	// Note strange array init
		gaussian_5x5[4].column = int[](1,  4,  6,  4, 1);	// Note strange array init
		// There are a total of 256 samples in this gaussian 
		
		vertexColour = vec3(0.0f, 0.0f, 0.0f);	// black
		
		
		
		
		
		const float OFFSET_UV = 1.0f/1920.0f;	// Screen is 1920x1080
		
		int samplesTaken = 0;
		
		// 3x3 starts at -1 less than 2
		// 5x5 starts at -2 less than 3
		// 9x9 starts at -4 less than 5  --> 81 samples
		for ( int xIndex = -2; xIndex < 3; xIndex++ )
		{
			for ( int yIndex = -2; yIndex < 3; yIndex++ )
			{
				vec2 UV_Offset = vec2(0.0f);
				UV_Offset.s = fUV.s + (xIndex * OFFSET_UV);
				UV_Offset.t = fUV.t + (yIndex * OFFSET_UV);
				//vertexColour.rgb += texture( texture00, UV_Offset).rgb;

				// Multiple the sample by the value in the [x][y] gaussian matrix above
				vec3 sampleColour = texture( texture00, UV_Offset).rgb;
				int gassianWeight = gaussian_5x5[xIndex + 2].column[yIndex + 2];
				vertexColour.rgb += ( sampleColour * gassianWeight );

//				samplesTaken++;
				samplesTaken += gassianWeight;
				
			}//for ( int yIndex...
		}// for ( int xIndex...	

		vertexColour.rgb /= float(samplesTaken);

	}//if ( b_Is_FBO_Texture )