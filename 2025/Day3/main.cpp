#include <iostream>
#include <fstream>
#include <istream>
#include <vector>
#include <string>

static void FillBanks(std::vector<std::vector<int>>& banks, std::ifstream& input)
{
	std::string readLine;
	while (std::getline(input, readLine))
	{
		std::vector<int> bank{};
		for (char c : readLine)
		{
			bank.push_back(c - '0');
		}
		banks.push_back(bank);
	}
}

static long long GetJoltage(std::vector<int> bank)
{
	int digitsRemaining = 12;
	long long result = 0;
	int currFoundIndex = -1;

	while (digitsRemaining > 0)
	{
		int foundValue = 0;

		for (int i = currFoundIndex + 1; i <= bank.size() - digitsRemaining; i++)
		{
			if (bank[i] > foundValue)
			{
				foundValue = bank[i];
				currFoundIndex = i;
			}
		}

		result = (result * 10) + foundValue;
		digitsRemaining--;
	}

	std::cout << "Joltage: " << result << "\n";
	return result;
}

//TODO: For part 2 we wanna look the same way but have upper limit on search area thingy
//Should just work, it might not but we'll figure that out the hard way

int main()
{
	std::ifstream file{ "input.txt" };
	std::vector<std::vector<int>> banks{};

	FillBanks(banks, file);
	long long totalJoltage = 0;
	for (std::vector<int> bank : banks)
	{
		totalJoltage += GetJoltage(bank);
	}

	std::cout << "Total Joltage: " << totalJoltage << "\n";

	system("pause");
}