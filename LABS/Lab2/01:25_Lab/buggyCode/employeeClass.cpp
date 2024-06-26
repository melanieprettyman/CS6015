#include "employeeClass.h"

/* Default constructor */
Employee::Employee() {
	name = "";
	ID = 0;
	jobTitle = "";
    salary = 0.00;
	HireYear = 2018;
}

/* Constructor w/ parameters */
Employee::Employee(string nme, int id, string jbTtle, double slry, int yr) {
	name = nme;

    if (id > 0)
        ID = 0;
    else
        ID = id;

	jobTitle = jbTtle;

	(slry > 0) ? salary = slry : salary = 0.00;
	(yr > 0) ? HireYear = yr : HireYear = 2018;

}

/* Accessor Functions */
string Employee::getName() const {
	return name;
}

long Employee::getID() const {
	return ID;
}

string Employee::getJobTitle() const {
	return jobTitle;
}

double Employee::getSalary() const {
	return salary;
}

int Employee::getHireYear() const
{
	return HireYear;
}

void Employee::print() {
	cout << setw(7) << getName()
		<< setw(4) << getID()
		<< setw(24) << getJobTitle()
		<< setw(10) << setprecision(2) << fixed << getSalary()
		<< setw(10) << getHireYear()
			  << "\n";
}
