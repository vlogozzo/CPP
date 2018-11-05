#pragma once
#include <fstream>    
#include <vector>
#include <utility>
#include <sstream>
#include <iostream>   
#include <iomanip>
#include <numeric>    
#include <algorithm>
namespace w8
{
	template<class T>

	class DataTable
	{
	private:
		std::vector<T> x, y;
		int width = 0, decimals = 0;
	public:
		DataTable(std::ifstream& file, int width, int decimals)
		{
			this->width = width;
			this->decimals = decimals;

			std::string line;

			while (getline(file, line))
			{
				std::stringstream ss;

				ss.str(line);

				T tempX, tempY;

				ss >> tempX >> tempY;

				x.push_back(tempX);
				y.push_back(tempY);
			}
		}

		T mean() const// - returns the mean value of the dependent coordinate
		{
			T yTotal = std::accumulate(y.begin(), y.end(), 0.0);

			return (yTotal / y.size());
		}

		T sigma() const // - returns the standard deviation of the dependent coordinates
		{
			T meanValue = mean(), totDeviation = 0;

			for (auto e : y)
			{
				totDeviation += pow((e - meanValue), 2);
			}
			if (y.size() - 1)
			{
				totDeviation = sqrt(totDeviation / (y.size() - 1));
			}
			return totDeviation;
		}
		T median() const // - returns the median value of the dependent coordinate
		{
			std::vector<T> copy = y;

			std::sort(copy.begin(), copy.end());
			T median = copy[copy.size() / 2];

			return median;
		}
		void regression(T& slope, T& y_intercept) const // - returns the slope and intercept for the data set
		{
			T averageX = std::accumulate(x.begin(), x.end(), 0.0) / x.size();
			T averageY = std::accumulate(y.begin(), y.end(), 0.0) / y.size();

			T numer = 0.0, denom = 0.0;

			for (size_t i = 0; i < x.size(); i++)
			{
				numer += (x[i] - averageX) * (y[i] - averageY);
				denom += (x[i] - averageX) * (x[i] - averageX);
			}

			slope = numer / denom;
			y_intercept = averageY - (slope * averageX);
		}
		void display(std::ostream& os) const // - displays the data pairs as shown below
		{
			os << std::setw(width) << "x" << std::setw(width) << "y" << std::endl;

			for (int i = 0; i < x.size(); i++)
			{
				os << std::setw(width) << std::fixed << std::setprecision(decimals) << x[i]
					<< std::setw(width) << std::fixed << std::setprecision(decimals) << y[i] << std::endl;
			}
		}
	};
		template<class T>
		std::ostream& operator<<(std::ostream& os, const DataTable<T>& dt) // - inserts the data generated by display() into the output stream
		{
			dt.display(os);
			return os;
		}
}