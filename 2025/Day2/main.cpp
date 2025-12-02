#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void ParseInput(std::vector<std::pair<long long, long long>>& output, std::string input)
{
	long long firstNumber = -1;
	long long currNumber = -1;
	for (char c : input)
	{
		if (c == '-')
		{
			firstNumber = currNumber;
			currNumber = -1;
		}
		else if (c == ',')
		{
			output.push_back(std::pair<long long, long long>{firstNumber, currNumber});
			firstNumber = -1;
			currNumber = -1;
		}
		else
		{
			int digit = c - '0'; //Neat little trick I saw on stackoverflow
			currNumber = (currNumber < 0) ? digit : (currNumber * 10) + digit;
		}
	}
	//Final pair
	output.push_back(std::pair<long long, long long>{firstNumber, currNumber});
}

bool isInvalid(long long id)
{
	std::string idString = std::to_string(id);
	int length = idString.length();
	int halfLength = length / 2;

	for (int i = 1; i <= halfLength; i++)
	{
		if (length % i == 0)
		{
			std::string pattern = idString.substr(0, i);
			bool isRepeating = true;
			for (int j = 1; j < length / i; j++)
			{
				if (idString.substr(j * i, i) != pattern)
				{
					isRepeating = false;
					break;
				}
			}

			if(isRepeating) return true;
		}
	}

	return false;
}

int main()
{
	std::string input;
	std::getline(std::ifstream{ "input.txt" }, input);
	
	//Parse this shit into pairs
	std::vector<std::pair<long long, long long>> ranges{};
	ParseInput(ranges, input);

	long long invalidTotal = 0;
	for (auto pair : ranges)
	{
		std::cout << "Processing pair: " << pair.first << " - " << pair.second << "...\n";
		for (long long i = pair.first; i <= pair.second; i++)
		{
			if (isInvalid(i))
			{
				std::cout << "Invalid ID: " << i << "\n";
				invalidTotal += i;
			}
		}
	}

	std::cout << "Invalid IDs sum: " << invalidTotal << "\n";

	system("pause");
}