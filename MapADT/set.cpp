
#include "set.h"


bool set:: simp_insert (const std:: string &s) {
	size_t hash_of_s = hash (s);
	size_t pos = hash_of_s % buckets.size();
	for (auto it : buckets[pos]) 
		if (it == s) return false;
	buckets[pos].insert (buckets[pos].end (), s);
	set_size ++;
	return true;			
}

std::ostream& set::print (std::ostream& out) const {
	for (size_t i = 0;i < buckets.size();i ++) {
		out << "buckets[ " << i << " ] = { ";
		bool comma = 0;
		for (auto it = buckets[i].begin ();it != buckets[i].end ();it ++) {
			if (comma) {
				out << ", " << *it;											
			} else {
				comma = 1;
				out << *it;
			}			
		}
		out << " }" << std::endl; 
	}	
	return out;
} 

bool set:: contains (const std:: string &s) const {
	size_t hash_of_s = hash (s);
	size_t pos = hash_of_s % buckets.size();
	for (auto it : buckets[pos]) 
		if (it == s) return true;
	return false;
}

bool set:: remove (const std:: string &s) {
	size_t hash_of_s = hash (s);
	size_t pos = hash_of_s % buckets.size();
	auto it = buckets[pos].begin ();
	while (it != buckets[pos].end ()) {
		if (*it == s) {
			it = buckets[pos].erase (it);
			set_size --;
			return true; 
		} else it ++;
	}		
	return false;
}

void set:: clear () {
	for (size_t i = 0;i < buckets.size();i ++)
		buckets[i].clear ();
	set_size = 0;
}

void set:: rehash (size_t newbucketsize) {
	if (newbucketsize < 4) 
		newbucketsize = 4;
	std::vector<std::list<std::string > > newbuckets = std::vector<std::list<std::string > > (newbucketsize);
	size_t hash_of_s, pos;
	for (size_t i = 0;i < buckets.size();i ++) {
		for (auto it : buckets[i]) {
			hash_of_s = hash (it);
			pos = hash_of_s % newbucketsize; 			
			newbuckets[pos].insert (newbuckets[pos].end(), it);
		}
	}
	std:: swap (buckets, newbuckets);
}

bool set::insert (const std:: string &s) {
	bool done = simp_insert (s);
	if (loadfactor () >= max_load_factor) 
		rehash (buckets.size() * 2);
	if (done == 1) return true;
	return false; 
}

std::ostream& set::printstatistics( std::ostream& out ) const
{
   out << "set size =            " << size( ) << "\n";
   out << "load factor =         " << loadfactor( ) << " ( max = " << max_load_factor << " )\n";
   out << "standard deviation =  " << standarddev( ) << "\n";
   return out;
}


