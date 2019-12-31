#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
using namespace std;
class Bign{
protected:
	#define maxn 1000
	int d[maxn], len;
	void clean(){
		while(len > 1 && !d[len - 1]) len--;
	}
public:
	Bign(){
		memset(d, 0, sizeof(d));
		len = 1;
	}
	Bign(int num){*this = num;}
	Bign(char *num){*this = num;}
	Bign operator = (const char *num){
		memset(d, 0, sizeof(d));
		len = strlen(num);
		for(int i = 0; i < len; i++)
			d[i] = num[len - 1 - i] - '0';
		clean();
		return *this;
	}
	Bign operator = (int num){
		char s[20];
		sprintf(s, "%d", num);
		*this = s;
		return *this;
	}
	Bign operator + (const Bign &b){
		Bign c = *this;
		int i;
		for(i = 0; i < b.len; i++){
			c.d[i] += b.d[i];
			if(c.d[i] > 9)
				c.d[i] %= 10, c.d[i + 1]++;
		}
		while(c.d[i] > 9) c.d[i++] %= 10, c.d[i]++;
		c.len = max(len, b.len);
		if(c.d[i] && c.len <= i)
			c.len = i + 1;
		return c;
	}
	Bign operator - (const Bign &b){
		Bign c = *this;
		int i;
		for(i = 0; i < b.len; i++){
			c.d[i] -= b.d[i];
			if(c.d[i] < 0)
				c.d[i] += 10, c.d[i + 1]--;
		}
		while(c.d[i] < 0) c.d[i++] += 10, c.d[i]--;
		c.clean();
		return c;
	}
	Bign operator * (const Bign &b) const{
		int i, j;
		Bign c;
		c.len = len + b.len;
		for(j = 0; j < b.len; j++)
			for(i = 0; i < len; i++)
				c.d[i + j] += d[i] * b.d[j];
		for(i = 0; i < c.len - 1; i++)
			c.d[i + 1] += c.d[i] / 10, c.d[i] %= 10;
		c.clean();
		return c;
	}
	Bign operator / (const Bign &b){
		int i, j;
		Bign c = *this, a = 0;
		for(i = len - 1; i >= 0; i--){
			a = a * 10 + d[i];
			for(j = 0; j < 10; j++)
				if(a < b * (j + 1)) break;
			c.d[i] = j;
			a = a - b * j;
		}
		c.clean();
		return c;
	}
	Bign operator % (const Bign &b){
		int i, j;
		Bign a = 0;
		for(i = len - 1; i >= 0; i--){
			a = a * 10 + d[i];
			for(j = 0; j < 10; j++)
				if (a < b * (j + 1)) break;
			a = a - b * j;
		}
		return a;
	}
	Bign operator += (const Bign &b){*this = *this + b; return *this;}
	Bign operator *= (const Bign &b){*this = *this * b; return *this;}
	Bign operator -= (const Bign &b){*this = *this - b; return *this;}
	Bign operator /= (const Bign &b){*this = *this / b; return *this;}
	Bign operator %= (const Bign &b){*this = *this % b; return *this;}
	bool operator < (const Bign &b) const{
		if(len != b.len)
			return len < b.len;
		for(int i = len - 1; i >= 0; i--)
			if(d[i] != b.d[i])
				return d[i] < b.d[i];
		return false;
	}
	friend Bign MAX(const Bign &a, const Bign &b){
		if(a > b) return a;
		else return b;
	}
	friend Bign MIN(const Bign &a, const Bign &b){
		if(a < b) return a;
		else return b;
	}
	bool operator > (const Bign &b) const{return b < *this;}
	bool operator <= (const Bign &b) const{return !(b < *this);}
	bool operator >= (const Bign &b) const{return !(*this < b);}
	bool operator != (const Bign &b) const{return b < *this || *this < b;}
	bool operator == (const Bign &b) const{return !(b < *this) && !(b > *this);}
	string str() const{
		char s[maxn] = {};
		for(int i = 0; i < len; i++)
			s[len - 1 - i] = d[i] + '0';
		return s;
	}
	#undef maxn
};
istream &operator >> (istream &in, Bign &x){
	string s;
	in >> s;
	x = s.c_str();
	return in;
}
ostream &operator << (ostream &out, const Bign &x){
	out << x.str();
	return out;
}
int main(){
	Bign x, y;
	cin >> x >> y;

	return 0;
}