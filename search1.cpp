/*
 * search1.cpp
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

struct cuNode {
	uint32_t p[4];
	
	void print_cuNode() {
		for(int x=0;x<4;++x) std::cout << p[x] << " ";
		std::cout << std::endl;
	}
};

struct cuConfig {
	uint32_t idx[4];
};

struct cuTocta {
	
	cuNode ws[4];
	
	uint32_t matches(int rows) {
		
		if((rows<2)||(rows>4)) return 999999;
		// parameter indicates number of rows to check
		
		uint32_t count = 0, *p, *q, *end;
		// treat workspace as contiguous array of uint32_t
		end = (uint32_t*)&(ws[rows-1].p[3]); // pointer to last value
		
		for(p = (uint32_t*)&(ws[0].p[0]); p < end; ++p)
			for(q = p+1; q <= end; ++q) if(*p == *q) count += 1;
		
		return count;
	}
	bool a1_pair() { return (ws[0].p[1] == ws[1].p[0]); }
	bool b1_pair() { return (ws[1].p[1] == ws[2].p[0]); }
	bool c1_quad() { return ((ws[2].p[1] == ws[3].p[0])&&(ws[3].p[1] == ws[0].p[0])); }
	bool col2_sum(uint32_t target) { return (target == (ws[0].p[2]+ws[1].p[2]+ws[2].p[2]+ws[3].p[2])); }
	bool col3_sum(uint32_t target) { return (target == (ws[0].p[3]+ws[1].p[3]+ws[2].p[3]+ws[3].p[3])); }
		
};	

int main(int argc, char **argv)
{
	const uint32_t Target = 84;
	
	std::vector<uint32_t> primes 
	{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 
	67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 
	139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 
	223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 
	293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 
	383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 
	463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 
	569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 
	647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 
	743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 
	839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 
	941, 947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013, 1019, 1021};
	
	std::vector<uint32_t> primelist;
	for(auto a = primes.begin(); a != primes.end(); ++a) {
		if(*a < (Target-10)) {
			primelist.push_back(*a);
		} else {
			break;
		}
	}
	
	std::vector<cuNode> nodelist;
	for(auto a = primelist.begin(); a != primelist.end(); ++a) {
		for(auto b = primelist.begin(); b != primelist.end(); ++b) {
			if(b==a) continue;
			
			for(auto c = primelist.begin(); c != primelist.end(); ++c) {
				if((c==a)||(c==b)) continue;
				
				for(auto d = primelist.begin(); d != primelist.end(); ++d) {
					if((d==a)||(d==b)||(d==c)) continue;
					if((*a+*b+*c+*d)==Target) nodelist.push_back( cuNode{*a,*b,*c,*d} );
				}
			}
		}
	}
	
#if(0)	
	for(auto a = nodelist.begin(); a != nodelist.end(); ++a) {
		std::cout << (*a).p[0] << "," << (*a).p[1] << "," << (*a).p[2] << "," << (*a).p[3] << std::endl;
	}
	std::cout << "Found " << nodelist.size() << " nodes." << std::endl;
#endif

	// Establish a list of configurations for triples
	
	cuTocta wspace;
	std::vector<cuConfig> configs;
	uint32_t count, solutions=0;
	uint32_t nl_size = nodelist.size();
	for(int a = 0; a < nl_size; ++a) {
		wspace.ws[0] = nodelist[a];
		for(int b = 0; b < nl_size; ++b) {
			wspace.ws[1] = nodelist[b];
			count = wspace.matches(2);
			// just checking...
			if((count==1)&&wspace.a1_pair()) {
				//std::cout << count << std::endl;
				//wspace.ws[0].print_cuNode();
				//wspace.ws[1].print_cuNode();
				//solutions+=1;
				// Do triple search with this result...
				for(int c = 0; c < nl_size; ++c) {
					wspace.ws[2] = nodelist[c];
					count = wspace.matches(3);
					if((count==2)&&(wspace.b1_pair())) {
						//std::cout << count << std::endl;
						//wspace.ws[0].print_cuNode();
						//wspace.ws[1].print_cuNode();
						//wspace.ws[2].print_cuNode();
						//solutions+=1;
						// Do final solution search with this result...
						for(int d = 0; d < nl_size; ++d) {
							wspace.ws[3] = nodelist[d];
							count = wspace.matches(4);
							if( (count==4) && (wspace.c1_quad()) && (wspace.col2_sum(Target) && (wspace.col3_sum(Target)) ) ) {
								std::cout << count << std::endl;
								wspace.ws[0].print_cuNode();
								wspace.ws[1].print_cuNode();
								wspace.ws[2].print_cuNode();
								wspace.ws[3].print_cuNode();
								solutions+=1;
							}							
						}
					}
				}
			}
		}
	}
	std::cout << "Triples:" << solutions << std::endl;	
	return 0;
}

