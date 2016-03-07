#include <vector>
using namespace std;

class MoveStoneEasy
{
  public:
	int get(vector <int> a, vector <int> b){
		int ans = 0;
		int sum = 0;
		int n = a.size();
		
		for(int i = 0; i < n; i++)    sum += a[i];
		for(int i = 0; i < n; i++)    sum -= b[i];
		if(sum != 0) return -1;
		
		int tmp = 0;
		int ret = 0;
		
		for(int i = 0; i < n; i++){
			tmp += a[i] - b[i];
			ret = abs(tmp);	
		}	
		return ret;
	}	
	
	
};