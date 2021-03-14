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

/*
   Force between particle:
   \overline{F}_{ij} = G \frac{m_i m_j}{|r|^2} \frac{\overline{r}}{|r|}
   Force over one particle:
   F_i = sum_j F_ij
   Acceleration:
   a_i = F_i / m_i
   Velocity
   v_i = v_i + a_i Dt
   Position
   x_i = x_i + v_i Dt
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <random>

#include "util.hpp"

int main(int argc, char *argv[])
{

	const int nTimeSteps = 10;
	const int nParticles = (argc > 1) ? atoi(argv[1]) : 100;

	bool enable_compare = false;
	bool enable_write = false;

	for (int i = 0; i < argc; i++) {
		if (std::string(argv[i]) == "-compare") {
			enable_compare = true;
		}
		if (std::string(argv[i]) == "-write") {
			enable_write = true;
		}
	}

	const double G = 6.674e-11;
	const double M = 5.972e24;
	const double M2 = M * M;
	const double GM2 = G * M2;
	const double Dt = 1.0e0;
	const int Xmax = 1.0e9;
	const int Vmax = 1.0e2;
	
	double *x = new double[nParticles * 3];
	double *v = new double[nParticles * 3];

	/* Initialize x and v */
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution(0, 1);
	for (int i = 0; i < nParticles * 3; i++) {
		x[i] = distribution(generator) * Xmax;
		v[i] = distribution(generator) * Vmax;
	}
	
	// Integrate in time
	for (int t = 0; t < nTimeSteps; t++) {
		
		for (int i = 0; i < nParticles; i++) {

			// F_i = sum_j F_ij
			double F[3] = {};
			for (int j = 0; j < nParticles; j++) {
				if (j != i) {
					// F_ij = G m_i m_j / |r|^2 
					const double dx = x[j * 3 + 0] - x[i * 3 + 0];
					const double dy = x[j * 3 + 1] - x[i * 3 + 1];
					const double dz = x[j * 3 + 2] - x[i * 3 + 2];
					const double r2 = dx * dx + dy * dy + dz * dz;
					const double rinv = 1 / sqrt(r2);
					const double rinv3 = rinv * rinv * rinv;
					const double Fmod = GM2 * rinv3;
					F[0] += Fmod * dx;
					F[1] += Fmod * dy;
					F[2] += Fmod * dz;
				}
			}
			//Acceleration:
			//a_i = F_i / m_i
			//Velocity
			//v_i = v_i + a_i Dt
			v[i * 3 + 0] += F[0] * Dt / M;
			v[i * 3 + 1] += F[1] * Dt / M;
			v[i * 3 + 2] += F[2] * Dt / M;
			//Position
			//x_i = x_i + v_i Dt
			x[i * 3 + 0] += v[i * 3 + 0] * Dt;
			x[i * 3 + 1] += v[i * 3 + 1] * Dt;
			x[i * 3 + 2] += v[i * 3 + 2] * Dt;
		}
		if (enable_write) {
			writeSolution(x, v, t, nParticles);
		}
		if (enable_compare) {
			compareSolution(x, v, t, nParticles);
		}
	}

	return 0;
}
