#include <iostream>
#include<cmath>
using namespace std;
void showPopulation(int day, int susceptibile, int infected, int recovered);
bool checkPopulation(int susceptible, int infected, int recovered);
void changeParametrs(double &infectionRate, double &recoveryRate);
void ShowHistory(int day, int populationHistory[][3], int dailyNewInfections[], int dailyRecoveries[]);
void simulateDay(int& day, int& susceptible, int& infected, int& recovered, double infectionRate, double recoveryRate, int populationHistory[][3],
	 int dailyNewInfections[], int dailyRecoveries[], int MAX_DAYS);
int main() {
	int populationHistory[101][3];
	 populationHistory[0][0] = 80;//susceptible
	 populationHistory[0][1] = 10;//infected
	 populationHistory[0][2]= 10;//recovered
	 const int MAX_DAYS = 100;
	 int dailyNewInfections[MAX_DAYS] = {};
	 int dailyRecoveries[MAX_DAYS] = {};
	int susceptible = 80;
	int infected = 10;
	int recovered = 10;
	int day = 0;
	int choice;
	double infectionRate = 0.20;
	double recoveryRate = 0.10;
	showPopulation(day, susceptible, infected, recovered);
	while (1) {
		cout << endl;
		cout << "=== Epidemic Simulator ===" << endl;
		cout << "1.Simulate next day" << endl;
		cout << "2.Change model parametrs" << endl;
		cout << "3.Show simulation history" << endl;
		cout << "4.Exit" << endl;
		cout << "Your choice: ";
		cin >> choice;
		switch (choice) {
		case 1: 
			simulateDay(day,susceptible,infected,recovered, infectionRate, recoveryRate, populationHistory,  dailyNewInfections, dailyRecoveries, MAX_DAYS);
				break;
		case 2:
			changeParametrs(infectionRate, recoveryRate);
				break;
		case 3:
			 ShowHistory(day, populationHistory, dailyNewInfections, dailyRecoveries);
				break;
		case 4:
			return 0;
		default:
			cout << "Wrong option chosen. Try again." << endl;
		}

	}
}
void showPopulation(int day, int susceptible, int infected, int recovered) {
	int total = susceptible + infected + recovered;
	cout << "Current world population: " << endl;
	cout << "Day: " << day << endl;
	cout << "Susceptible: " << susceptible << endl;
	cout << "Infected: " << infected << endl;
	cout << "Recovered: " << recovered << endl;
	cout << "Total: " << total << endl;
	
}
void simulateDay(int& day, int& susceptible, int& infected, int& recovered, double infectionRate, double recoveryRate, int populationHistory[][3],
	int dailyNewInfections[], int dailyRecoveries[], int MAX_DAYS) {
	int initially = infected;
	int newinfected = floor(initially * infectionRate);
	int newrecovered = floor(initially * recoveryRate);
	if (newinfected > susceptible) {
		newinfected = susceptible;
	}
	if (newrecovered > infected) {
		newrecovered = infected;
	}
	susceptible = susceptible - newinfected;
	infected = infected + newinfected - newrecovered;
	recovered = recovered + newrecovered;
	day++;

	if (day >= MAX_DAYS) {
		cout << "You reached the limit of simulation.";
		return;
	}

	cout << endl;
	cout << "Day: " << day << endl;
	cout << "Susceptible: " << susceptible << endl;
	cout << "Infected: " << infected << endl;
	cout << "Recovered: " << recovered << endl;
	cout << endl;

	if (checkPopulation(susceptible, infected, recovered)) {
		if (day >= 0 && day <= MAX_DAYS) {
		populationHistory[day][0] = susceptible;//susceptible
		populationHistory[day][1] = infected;//infected
		populationHistory[day][2] = recovered;//recovered
		}
		else {
			cout << "Something went wrong. You can't save history." << endl;
			return;
		}
		if (day >= 0 && day < MAX_DAYS) {
			dailyNewInfections[day] = newinfected;
			dailyRecoveries[day] = newrecovered;
		}
		else {
			cout << "Something went wrong. You can't save history." << endl;
			return;
		}
	}
}
	
	
bool checkPopulation(int susceptible, int infected, int recovered) {
	int suma = susceptible + infected + recovered;
	if (suma == 100 && susceptible>=0 && infected>=0 && recovered>=0) {
		return true;
	}
	else {
		cout << "Something went wrong. You can't continue simulation." << endl;
		return false;
	}

}
void changeParametrs(double &infectionRate, double &recoveryRate) {
	double newinfRate;
	double newrecRate;
	cout << endl;
	cout << "Enter infection rate (0-1): ";
	cin >> newinfRate;
	if (newinfRate >= 0 && newinfRate <= 1) {
		infectionRate = newinfRate;
		cout << "Parameter updated." << endl;
	}
	else {
		cout << "Incorrect value entered. The infection rate remains the same." << endl;
	}
	cout << endl;
	cout << "Enter recovery rate (0-1): ";
	cin >> newrecRate;
	if (newrecRate >= 0 && newrecRate <= 1) {
		recoveryRate = newrecRate;
		cout << "Parameter updated." << endl;
	}
	else {
		cout << "Incorrect value entered. The recovery rate remains the same." << endl;
	}
}
void ShowHistory(int day, int populationHistory[][3], int dailyNewInfections[], int dailyRecoveries[]) {
	for (int i = 0; i <= day;i++) {
		cout << endl;
		cout << "Day: " << i << endl;
		cout << "Susceptible: " << populationHistory[i][0] << endl;
		cout << "Infected: " << populationHistory[i][1] << endl;
		cout << "Recovered: " << populationHistory[i][2] << endl;
		if (day == 0) {
			cout << "----------------" << endl;
			cout << "----------------" << endl;
		}
		else {
			cout << "New infections: " << dailyNewInfections[i] << endl;
			cout << "New recoveries: " << dailyRecoveries[i] << endl;
		}
		cout << endl;
	}
}