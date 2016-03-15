#include "Twin.h"

typedef std::vector<double> vec;
typedef std::vector<vec> mat;

vec gvec(Twin&);
void dvec(Twin&, const vec&);
void newtonpoly(const vec&, const vec&, const double&, Twin&);
void dmat(Twin& t, const mat& mat);

int main() {

	Twin t("Newton Polynomial Interpolation");

	vec x, y;
	double xi;

	do {

		t.println("Enter the first element of the vector x.");
		t.println("Example: 2.5");
		t.display();

		x = gvec(t);

		t.println("Enter the first element of the vector y.");
		t.println("Example: 1.2");
		t.display();

		y = gvec(t);

		if (x.size() != y.size()) {
			t.println("Vectors must have the same dimension.");
			t.println();
		}

	} while (x.size() != y.size());

	while (true) {

		t.println("Enter xi.");
		t.display();

		std::string input;
		std::getline(std::cin, input);
		std::stringstream iss(input);
		iss >> xi;

		t.println("xi:");
		t.println();
		t.println(xi);
		t.println();
		t.println("Enter 'x' to save and continue.");
		t.display();

		std::getline(std::cin, input);
		iss >> xi;

		if (input == "x" || input == "X") break;
	}

	newtonpoly(x, y, xi, t);

	return EXIT_SUCCESS;
}

void newtonpoly(const vec& x, const vec& y, const double& xi, Twin& t) {

	mat f;

	for (int i = 0; i < y.size(); i++) f.push_back(vec(1, y[i]));

	for (int j = 1; j < x.size(); j++)
		for (int i = 0; i < x.size() - j; i++)
			f[i].push_back((f[i + 1][j - 1] - f[i][j - 1]) / (x[i + j] - x[i]));

	double xterm = 1;
	vec yint;
	vec ea(x.size()-1);
	yint.push_back(f[0][0]);

	for (int i = 1; i < x.size(); i++) {

		xterm *= (xi - x[i - 1]);
		double yint2 = yint[i - 1] + f[0][i] * xterm;
		ea[i - 1] = yint2 - yint[i - 1];
		yint.push_back(yint2);

	}

	t.println("Vector yint:");
	t.println();
	dvec(t, yint);
	t.println();
	t.println("Press enter to continue.");
	t.display();
	std::cin.ignore(1000, '\n');
	std::cin.clear();

	t.println("Vector ea:");
	t.println();
	dvec(t, ea);
	t.println();
	t.println("Press enter to continue.");
	t.display();
	std::cin.ignore(1000, '\n');
	std::cin.clear();

}

vec gvec(Twin& t) {

	vec b;
	double in;
	std::string input;

	std::getline(std::cin, input);
	std::stringstream iss(input);
	iss >> in;
	b.push_back(in);

	while (true) {

		t.println("Vector:");
		t.println();
		dvec(t, b);
		t.println("Enter the next element.");
		t.println("Enter 'x' to save and continue.");
		t.display();

		std::getline(std::cin, input);
		std::stringstream iss(input);
		iss >> in;

		if (input == "x" || input == "X") return b;
		else b.push_back(in);

	}
}

void dvec(Twin& t, const vec& vec) {

	for (auto&& i : vec) {
		t.println("[ ");
		t.print(i);
		t.print(" ]");
	}

	t.println();
}

void dmat(Twin& t, const mat& mat) {

	t.println();

	for (int i = 0; i < int(mat.size()); i++) {

		t.print("[ ");

		for (int j = 0; j < int(mat[0].size()); j++) {
			t.print(mat[i][j]);
			if (j < int(mat[0].size()) - 1) t.print(",");
			t.print(" ");
		}

		t.print("]");
		t.println();

	}
}