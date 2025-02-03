#include <vector>
#include <string>
#include <fstream>
#include <iostream> 

bool loadNamesIntoVector(std::string filename, std::vector<std::string>& vecNames);

// This won't work because we have too many conflicts (collisions)
// i.e. different values generate the same hash function
unsigned int calcHash_1(std::string theName)
{
	// Take each letter and get the ASCII (unicode) value
	//	and sum them up

	unsigned int hashValue = 0;

//	std::cout << "Hash for >" << theName << "< is:" << std::endl;
	for (char curCharacter : theName)
	{
//		std::cout << "\t"
//			<< curCharacter << " = " << (unsigned int)curCharacter << std::endl;

		hashValue += (unsigned int)curCharacter;

	}
//	std::cout << "hashValue: " << hashValue << std::endl;

	return hashValue;
}

// Do the same as calcHash_1 in that we take each character
//	and get the ASCII (Unicode) code for it,
//	but this time, we multiple the value by 10 x the column number
// 
// SMITH:
//	S = 83 --> 83		= 83
//	M = 77 --> 77 * 10	= 770
//	I = 73 --> 73 * 100 = 7300
// ...and so on...
//
// The hash values will be VERY large, much larger than 
//	the size of our vector, so we could:
// a) Make the vector really large, too
//    (but we have empty space)
// b) Adjust it to fit the size of our array
// 
unsigned int calcHash_2(std::string theName, unsigned int vectorSize)
{
	// Take each letter and get the ASCII (unicode) value
	//	and sum them up

	unsigned int hashValue = 0;

//	std::cout << "Hash for >" << theName << "< is:" << std::endl;
	for (unsigned int charIndex = 0; charIndex < theName.length(); charIndex++ )
	{
		char curCharacter = theName[charIndex];

		unsigned int ASCII_Value = (unsigned int)curCharacter;

//		std::cout << "\t"
//			<< curCharacter << " = " << ASCII_Value << std::endl;

		unsigned int curCharHashValue = ASCII_Value * std::pow(10, charIndex);

		hashValue += curCharHashValue;
	}
//	std::cout << "hashValue: " << hashValue << std::endl;

	// Adjust the hash value to match our vector
	hashValue = hashValue % vectorSize;

	return hashValue;
}


int main()
{
	std::vector<std::string> vecLastNames;

	loadNamesIntoVector("USCen/US_LastNames.txt", vecLastNames);

	// This has the same data, BUT
	//	the index now has some connection to the data.
	std::vector< std::vector<std::string> > vecHashNames;

	// Load empty locations in this vector
//	unsigned int sizeOfHashTable = vecLastNames.size();
//	unsigned int sizeOfHashTable = 1000;
	unsigned int sizeOfHashTable = 1'000'000;

	for (unsigned int count = 0; count != sizeOfHashTable; count++)
	{
		std::vector<std::string> vecEmpty;
		vecHashNames.push_back(vecEmpty);
	}
	// At this point, vecHashNames 88,799 location 
	// (The same number as the number of names)


	for (std::string currentName : vecLastNames)
	{
		//		unsigned int nameHashIndex = calcHash_1(currentName);
		unsigned int nameHashIndex = calcHash_2(currentName, sizeOfHashTable);

		// Place that name at that hash location
		vecHashNames[nameHashIndex].push_back(currentName);
	}

	// Find "SMITH"
	unsigned int SMITH_hashIndex = calcHash_2("SMITH", sizeOfHashTable);
	// 
	std::vector<std::string> &vecAtThisHash = vecHashNames[SMITH_hashIndex];


	// Some stats
	unsigned int numEmptySlots = 0;
	unsigned int numCollisions = 0;
	unsigned int highestNumCollisions = 0;

	for (unsigned int index = 0; index != vecHashNames.size(); index++)
	{
		if (vecHashNames[index].size() == 0)
		{
			numEmptySlots++;
		}
		if (vecHashNames[index].size() > 1)
		{
			numCollisions++;

			if (vecHashNames[index].size() > highestNumCollisions)
			{
				highestNumCollisions = vecHashNames[index].size();
			}
		}
	}//for (unsigned int index

	std::cout << "Summary: " << std::endl
		<< "Table size: " << vecHashNames.size() << std::endl
		<< "\tnumEmptySlots = " << numEmptySlots << std::endl
		<< "\tnumCollisions = " << numCollisions << std::endl
		<< "\thighestNumCollisions = " << highestNumCollisions << std::endl;


	return 0;
}



int main_2()
{
	std::vector<std::string> vecLastNames;

	loadNamesIntoVector("USCen/US_LastNames.txt", vecLastNames);

	// find "TURNER"

	// This has the same data, BUT
	//	the index now has some connection to the data.
	std::vector<std::string> vecHashNames;
	// Load empty locations in this vector
	for (unsigned int count = 0; count != vecLastNames.size(); count++)
	{
		vecHashNames.push_back("");
	}
	// At this point, vecHashNames 88,799 location 
	// (The same number as the number of names)

	unsigned int vectorSize = vecLastNames.size();

	for (std::string currentName : vecLastNames)
	{
//		unsigned int nameHashIndex = calcHash_1(currentName);
		unsigned int nameHashIndex = calcHash_2(currentName, vectorSize);

		// Check for collisions:
		if (vecHashNames[nameHashIndex] != "")
		{
			// There is a collision!!
			std::cout << "A collision!" << std::endl
				<< "Data already at [" << nameHashIndex << "] = "
				<< vecHashNames[nameHashIndex] << std::endl
				<< "when loading " << currentName << std::endl;
		}

		// Place that name at that hash location
		vecHashNames[nameHashIndex] = currentName;
	}

	// Find "SMITH"
	unsigned int SMITH_hashIndex = calcHash_2("SMITH", vectorSize);
	// 
	std::cout << vecHashNames[SMITH_hashIndex] << std::endl;

	return 0;
}














bool loadNamesIntoVector(std::string filename, std::vector<std::string>& vecNames)
{
	std::fstream lastNameFile(filename.c_str());

	if ( ! lastNameFile.is_open() )
	{
		return false;
	}

	std::string nextName;
	while (lastNameFile >> nextName)	// //SMITH   
	{
		// Add it
		vecNames.push_back(nextName);

		float discardThis;
		lastNameFile >> discardThis >> discardThis >> discardThis; // 1.006  1.006      1
	}

	return true;
}