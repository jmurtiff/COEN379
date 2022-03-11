#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

#include <string>

//vector <int> Z[15];

vector <int> compute_z(string s)
{
    int l(0), r(1), n(s.size());

    vector <int> z(n,0);

    for(int k = 1; k < n; ++k)
    {
        int x;
        if (r <= k)
        {
            for (x = 0; k + x < n && s[x] == s[k + x]; ++x)
            ;
            z[k] = x; l = k; r = k + z[k];
        }
        else if (k + z[k-l] < r)
            z[k] = z[k-l];
        else
        {
            for(x = r - k; k + x < n && s[x] == s[k + x]; ++x)
            ;
            z[k] = x; l = k; r = k + z[k];
        }
    }
    return z;
}

/* 
// Fills Z array for given string str[]
vector <int> getZarr(string str)
{
    int n = str.length();
    vector <int> z (n,0);

    int L, R, k;
 
    // [L,R] make a window which matches with prefix of s
    L = R = 0;
    for (int i = 1; i < n; ++i)
    {
        // if i>R nothing matches so we will calculate.
        // Z[i] using naive way.
        if (i > R)
        {
            L = R = i;
 
            // R-L = 0 in starting, so it will start
            // checking from 0'th index. For example,
            // for "ababab" and i = 1, the value of R
            // remains 0 and Z[i] becomes 0. For string
            // "aaaaaa" and i = 1, Z[i] and R become 5
            while (R<n && str[R-L] == str[R])
                R++;
            Z[i] = R-L;
            R--;
        }
        else
        {
            // k = i-L so k corresponds to number which
            // matches in [L,R] interval.
            k = i-L;
 
            // if Z[k] is less than remaining interval
            // then Z[i] will be equal to Z[k].
            // For example, str = "ababab", i = 3, R = 5
            // and L = 2
            if (Z[k] < R-i+1)
                Z[i] = Z[k];
 
            // For example str = "aaaaaa" and i = 2, R is 5,
            // L is 0
            else
            {
                // else start from R and check manually
                L = i;
                while (R<n && str[R-L] == str[R])
                    R++;
                Z[i] = R-L;
                R--;
            }
        }
    }
    return z;
}
*/
/*
vector <int> compute_longestPrefix(const string &s, const string &t)
{
	int size_s = s.size();
	int size_type = t.size();
    string test_1 = s;
    string test_2 = t;
	int total_size = size_s + size_type;
	test_1.append(test_2);
    vector <int> ans(total_size,0);
	getZarr(test_1, Z);
	for (int i = total_size - 1; i > 0; --i)
	{
		ans[i + Z[i] - 1] = Z[i];
	}
	return ans;
}

*/




vector <int> compute_Kp(const string &s)
{
    int n = s.size();
    vector <int> ans(n,0); 

    vector <int> z;
    
    z = compute_z(s);

    for (int i = n-1; i > 0; --i)
    {
        ans[i + z[i] -1] = z[i];
    }
    return ans;
}

vector <int> compute_K(string &s)
{
    int n = s.size();

    vector <int> Kp;
    vector <int> ans(n,0); Kp = compute_Kp(s);

    ans[n-1] = Kp[n-1]; 
    for (int i = n-2; i > 0; --i)
    {
        ans[i] = max(Kp[i], ans[i+1]-1);
    }
    return ans;
}


//N value
vector <int> compute_N(const string & s)
{
    int n = s.size();
    string t = s;
    reverse (t.begin(), t.end());
    vector <int> ans(n,0);
    vector <int> z;
    z = compute_z(t);
    //getZarr(t, Z);
    for(int i = 0; i < n; ++i)
    {
        ans[i] = z[n - 1 - i];
    }
    return ans;
}



//L' value
vector <int> compute_Lp(const string & s)
{
    int n = s.size();

    vector <int> N = compute_N(s);
    vector <int> ans(n, -1);

    for(int k = 0; k < n; ++k)
        if (N[k] > 0)
            ans[n-1-N[k]] = k;
    
    return ans;
}

//l'p value
vector <int> compute_lp(const string & s)
{
    int n = s.size();

    vector <int> N = compute_N(s);
    vector <int> ans(n, 0);

    int last(0);
    ans[n-1] = 0;

    for (int i = n - 2; i >= 0; i--)
    {
        int k = n - 1 - i;
        if (N[k-1] == k)
        {
            ans[i] = k;
            last = k;
        }
        else
            ans[i] = last;
    }
    return ans;
}

string p3(string s)
{
    vector <int> Z = compute_z(s);
    int n = s.size();

    vector <int> lp = compute_lp(s);
    int lp_size = lp.size();
    int final_value = 0;

    for (int i = 1; i < n; ++i)
    {
        if(Z[i]+i == n && n % i == 0)
        {
            //Return the pattern here, but we need to know the length of it.
            //Use Alex's solution, use l' value to calculate m (length of t) and print it out.
            //Since we only print it out when the case is true.
            for (int j = 0; j < lp_size; j++)
            {
                int larger_value = lp[j];
                int smaller_value = lp[j+1];
                if(larger_value != smaller_value)
                {
                    final_value = larger_value - smaller_value;
                    break;
                }
            }
            return s.substr(0,final_value);
        }
    }
    //Return false and return empty string here
    return "";
}


template <typename S>
void using_index(const vector<S>& vector,
                 string sep = " ")
{
    // Iterating vector by using index
    for (int i = 0; i < vector.size(); i++) {
        // Printing the element at
        // index 'i' of vector
        cout << vector[i] << sep;
    }
    cout << endl;
}

template<typename T, size_t n>
void print_array(T const(& arr)[n])
{
    for (size_t i = 0; i < n; i++) {
        std::cout << arr[i] << ' ';
    }
}

int main()
{
    //compute_N(str);
    //string str ("aaabbbaaabbbaaa");
    string str ("abcdeabcdeabcde");
    vector <int> ans(str.size(),0);
    ans = compute_lp(str);
    string test = p3(str);
    //using_index(ans);

    cout << test << endl;
    
    
    //getZarr(str,Z);
    //ans = compute_N(str);
    //print_array(Z);
}



