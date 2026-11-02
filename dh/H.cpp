#include <iostream>
#include <string>
#include <bits/stdc++.h>
using namespace std;
int main() {
	int L = 0;
	int R = 0;

	std::string s;
	while(std::cin >> s) {
		int count = 0;

		unordered_set<char> s_star(s.begin(), s.end());

		vector<unordered_map<char, int>> d;

		unordered_set<string> included;

		// init i==0

		// fill in
		for(int i=0; i<s.size(); i++) {
			d.push_back({});

			for(auto& c: s_star) {
				d[i][c] = (i == 0) ? 0 : d[i-1][c];
			}

			d[i][s[i]]++;


			//cout << "DBG ";
			//for(auto& c: s_star) {
			//	cout << c << " " << d[i][c] << " ";
			//}
			//cout << endl;

		}

		int L = 0;
		int R = 0;

		while(R<s.size()) {
			//cout << L << "*" << R << endl;
			
			bool valid = true;
			for(auto& c : s_star) {
				if(d[R][c] == 0) {
					valid = false;
					break;
				}
			}
			if(valid) {
				break;
			} else {
				R++;
			}
		}
		if(R==s.size()) {
			std::cout << 0 << std::endl;
			return 0;
		} else {
//			string sub = s.substr(L, R+1);
			//if(included.count(sub) == 0) {
			//	count++;
			//}
//			cout << "++" <<endl;


//			included.insert(sub);

			//count++;
		}

		bool beginning = true;
		bool prev_op_was_R = false;
		while(R<s.size()) {
			//cout << L << " " << R << endl;

			bool duplicates = false;
//			for(auto& c : s_star) {
//				if(d[R][c]-d[L][c] > 1) {
//					duplicates = true;
//					break;
//				}
//			}

			if((d[R][s[L]]-d[L][s[L]])>0) {
				duplicates = true;
			}

			if(duplicates) {
				L++;

				//if(prev_op_was_R) {
				//	cout << "++" <<endl;
				//	count++;
				//}


				prev_op_was_R = false;
			} else {
				if(!prev_op_was_R || beginning) {
					string sub = s.substr(L, R-L+1);
					//if(included.count(sub) == 0) {
					//	count++;
					//}
					//cout << "++" <<endl;

					included.insert(sub);
				}

				R++;

				prev_op_was_R = true;
			}

			beginning = false;
		}

		if(!prev_op_was_R) {
			string sub = s.substr(L,R-L+1);
			//if(included.count(sub) == 0) {
			//	count++;
			//}

			//cout << "++" <<endl;

			included.insert(sub);

			
		}

		count = 0;
		for(auto& included_s : included) {
			if(included_s != s) {
				count++;
			}
		}

		//std::cout << included.size() << std::endl;

		//cout << "S ";
		//for(auto& substrs : included) {
		//	cout << substrs << " ";
		//}
		//cout << endl;

		std::cout << count << std::endl;
		//std::cout << s_star.size() << std::endl;
		s = "";
	}
	return 0;
}
