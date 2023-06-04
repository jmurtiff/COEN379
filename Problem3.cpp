#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <string>
using namespace std;

//Compute Z value, same as given in class.
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

//Compute K' value, same as given in class.
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

//Compute K value, same as given in class.
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

//Compute N value, same as given in class.
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

//Compute L' value, same as given in class.
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

//Compute l' value, same as given in class.
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

//Algorithim for Question #3 for Homework #9.
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

//Helper function used to print out Vector Objects.
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

//Main function
int main()
{
    string str ("abcabcabcd");

    vector <int> ans(str.size(),0);
    //ans = compute_lp(str);
    ans = compute_z(str);
    using_index(ans);

    string test = p3(str);
    cout << test << endl;
}