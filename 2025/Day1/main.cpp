#include <iostream>
#include <fstream>
#include <string>

int main()
{
	std::string filePath = "input.txt";
	std::ifstream readStream{ filePath };
	std::string currLine;

	int dial = 50;
	const int dialMax = 100;
	int nrZeroes = 0;

	if (readStream.is_open())
	{
		while (std::getline(readStream, currLine))
		{
			char direction = currLine[0];
			currLine.erase(0, 1);
			int amount = std::stoi(currLine);

			if (direction == 'L')
			{
				bool skipZero = false;
				if (dial == 0)
				{
					skipZero = true;
				}
				dial -= amount;
				while (dial < 0)
				{
					if (!skipZero)
					{
						nrZeroes++;
					}
					else
					{
						skipZero = false;
					}
					dial = dial + dialMax;
				}
			}
			else if (direction == 'R')
			{
				dial += amount;
				while (dial >= dialMax)
				{
					nrZeroes++;
					dial = dial - dialMax;
				}
			}
			else
			{
				std::cout << "Chat we're cooked";
			}
			if (dial == 0 && direction == 'L')
			{
				nrZeroes++;
			}
		}
		readStream.close();
	}

	std::cout << "Nr zeroes: " << nrZeroes << std::endl;

	system("pause");
}