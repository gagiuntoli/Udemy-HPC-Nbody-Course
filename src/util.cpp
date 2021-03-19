/*
   MIT License

   Copyright (c) 2020 Guido Giuntoli

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <random>

void writeSolution(const double *x, const double *v, const int t, const int nParticles)
{
	std::stringstream ss;
	ss << "particles_" << t << ".csv";
	std::ofstream outFile;
	outFile.open(ss.str());

	outFile << std::scientific ;
	for (int i = 0; i < nParticles * 3; i++) {
		outFile << x[i] << std::endl
			<< v[i] << std::endl; 
	}
	outFile.close();
}

void compareSolution(const double *x, const double *v, const int t,
		const int nParticles,
		bool printComparison = false)
{
	const double tol = 1.0e-5;
	std::stringstream ss;
	ss << "reference/" << nParticles << "/particles_" << t << ".csv";
	std::ifstream compFile;
	compFile.open(ss.str());
	std::cout << std::scientific;

	if (compFile.fail()) {
		std::cout << "error: file name " << ss.str()
			<< " not found for comparison"
			<< std::endl;
	}

	int i = 0;
	std::string line;

	while (compFile >> line) {

		double val = std::stod(line);

		if (printComparison) {
			std::cout << "comparing : " << x[i] << " " << val << std::endl;
		}

		if (std::abs(x[i] - val) > std::abs(x[i] * tol)) {
			std::cout << "error in the solution: "
				<< x[i] << "->" << val << std::endl;
		}

		if(compFile >> line) {
			double val = std::stod(line);
			if (std::abs(v[i] - val) > std::abs(v[i] * tol)) {
				std::cout << "error in the solution: "
					<< v[i] << "->" << val << std::endl;
			}
		} else {
			std::cout << "error: file " << ss.str() << "has not enought lines"
				<< std::endl;
			break;
			
		}
		i += 1;
	}
	
	compFile.close();
}
