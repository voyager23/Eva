/*
 * swaptest.cpp
 * 
 * Copyright 2015 mike <mike@Eva>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <iostream>
#include <cstdint>
#include <vector>
#include <iomanip>
#include <algorithm>

struct cuNode {
	uint32_t p[4];
	
	void print_cuNode() {
		for(int x=0;x<4;++x) std::cout << std::setw(3) << p[x] << " ";
		std::cout << std::endl;
	}
	
};

// compare all primes.
bool compare4primes(cuNode l, cuNode r) {
	// return TRUE if left comes before right
	if ( l.p[0] < r.p[0] ) return true;
	if ( l.p[0] > r.p[0] ) return false;
	// first entries equal
	if ( l.p[1] < r.p[1] ) return true;
	if ( l.p[1] > r.p[1] ) return false;
	// first 2 entries equal
	if ( l.p[2] < r.p[2] ) return true;
	if ( l.p[2] > r.p[2] ) return false;
	// first 3 entries equal
	if ( l.p[3] < r.p[3] ) return true;
	if ( l.p[3] > r.p[3] ) return false;
	return false;
}

int main(int argc, char **argv)
{
	cuNode a = {1,2,3,4};
	cuNode b = {5,6,7,8};
	cuNode c = {9,10,7,8};
	cuNode d = {9,6,11,88};
	
	std::vector<cuNode> nl = {d,c,b,a};
	// print the base nodelist
	std::cout << "Unsorted\n";
	for(auto p = nl.begin(); p != nl.end(); ++p) (*p).print_cuNode();
	
	std::sort(nl.begin(), nl.end(), compare4primes);
	
	std::cout << "\nSorted\n";
	for(auto p = nl.begin(); p != nl.end(); ++p) (*p).print_cuNode();
	
	std::cout << "comparing c and d\n";
	std::cout << compare4primes(c,d) << std::endl;
	
	std::cout << "\ncomparing d and c\n";
	std::cout << compare4primes(d,c) << std::endl;
	
	return 0;
}

