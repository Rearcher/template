template<typename Int, int D>
class BigInt {
private:
    vector<Int> _r;
    static const int M = pow(10, D);
public:
    BigInt() {}
    BigInt(const string& s) {
    	int n = (int)s.size();
   		_r.reserve(n / D + 1);
    	for (int i = n; i > 0; i -= D) {
    		Int d = 0;
       	 	for (int j = std::max(0, i-D); j < i; j++)
            	d = 10 * d + s[j] - '0';
            _r.push_back(d);
        }
        while (_r.size()>1 && _r.back()==0)
        	_r.pop_back();
    }
        
	string toString() {
        stringstream ss;
        int n = (int)_r.size();
        for (int i = n-1; i >= 0; i--) {
            if (i != n-1)
                ss << setw(D) << setfill('0');
            ss << _r[i];
        }
        return ss.str();
    }
        
	static BigInt multiply(const BigInt& a, const BigInt& b) {
        BigInt result;
        int n = (int)a._r.size(), m = (int)b._r.size();
        if (n == 0 || m == 0) return result;
        result._r = vector<Int>(n+m, 0);
        for (int i = 0; i < n; i++) 
        	for (int j = 0; j < m; j++) {
                result._r[i+j] += a._r[i] * b._r[j];
                result._r[i+j+1] += result._r[i+j] / M;
                result._r[i+j] = result._r[i+j] % M;
            }
        while (result._r.size()>1 && result._r.back()==0)
            result._r.pop_back();
        return result;
    }
};
