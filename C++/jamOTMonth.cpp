// Jam of the Month club
/*
	There are three packages. Each package has a unique monthly rate, count of free jams, and additional jam jar rate.

	Ask the user which package they subscribe to.
	Ask the user how many jams they ordered that month. 

	Total the cost of a monthly subscription and the count of jams purchased. 
	Determine whether the count of jams ordered exceeds the count of jams included in the subscription.
	Display:
		- the monthly fee
		- the number of jams purchased against the number covered
		- the amount owed for jams purchased
		- the total amount owed
*/

#include <iostream>
#include <string>
struct Package {
	float monthlyRate;
	float extraJamCost;
	int jamCount;
};

void main() {
	std::string packageName;
	int jamsOrdered = 0, jamsBeyondContract = 0;
	float extraOwed = 0, packageCost = 0;
	std::cout << "To which package do you subscribe?\n";
	std::getline(std::cin, packageName);

	std::cout << "How many jams did you order this month?\n";
	std::cin >> jamsOrdered;


	if (packageName=="lite") {
		Package lite{ 10,8,2 };
		packageCost = lite.monthlyRate;
		//	compute the extra monthly cost of jam
		if (jamsOrdered - lite.jamCount > 0) {
			jamsBeyondContract = jamsOrdered - lite.jamCount;
			extraOwed = jamsBeyondContract * lite.extraJamCost;
		}
	} 
	else if (packageName=="jammer"){
		Package jammer{ 15,6,3 };
		packageCost = jammer.monthlyRate;
		//	compute the extra monthly cost of jam
		if (jamsOrdered - jammer.jamCount > 0) {
			jamsBeyondContract = jamsOrdered - jammer.jamCount;
			extraOwed = jamsBeyondContract * jammer.extraJamCost;
		}
	}
	else {
		Package jamStar{ 20,5,4 };
		packageCost = jamStar.monthlyRate;
		//	compute the extra monthly cost of jam
		if (jamsOrdered - jamStar.jamCount > 0) {
			jamsBeyondContract = jamsOrdered - jamStar.jamCount;
			extraOwed = jamsBeyondContract * jamStar.extraJamCost;
		}
	}


	//	user output
	std::cout << "You owe\n" << packageCost << "\tfor the " << packageName << " subscription\n";
	if (extraOwed > 0) {
		std::cout << extraOwed << "\tfor the "<< jamsBeyondContract <<" extra jams you ordered this month\n";
	}
	std::cout << "Your total is\t" << extraOwed + packageCost ;
}



//
//class Package {
//
//public:
//	Package();
//	Package(float monthlyRate,int jamCount, float extraJamCost);
//	float getMonthlyRate() const;
//	int getJamCount() const;
//	float getExtraJamCost() const;
//	Virtual ~Package();
//}