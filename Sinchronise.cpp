#include<iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;


class CSet
{
    public:
        int N;
        int* set;
        CSet(int a_N):N(a_N){set = new int[N]; for(int i = 0; i<N; ++i){this->set[i] = -1;};};

        bool is_in(int I)
        { bool flag = false;
            for(int i = 0; i<this->N;++i){if(this->set[i] == I){flag = true;};};
            return flag;
        };

        int is_in_i(int I)
        { int flag = 0;
            for(int i = 0; i<this->N;++i){if(this->set[i] == I){flag = 1;};};
            return flag;
        };

        void fill(map<int, int> M)
        {
            int current = 0;
        for(int i = 0; i<this->N;++i)
            {
                if(this->is_in(M[i]))
                {
                    continue;
                }else{
                    this->set[current] = M[i];
                    ++current;
                };
                
            };
        };


        void fill(vector<int> V)
        {
            int current = 0;
        for(int i = 0; i<this->N;++i)
            {
                if(this->is_in(V[i]))
                {
                    continue;
                }else{
                    this->set[current] = V[i];
                    ++current;
                };
                
            };
        };

        void print_set()
        {for(int i = 0; i<this->N;++i)
        {
            cout<<set[i]<<endl;

        }; 
        
        };
        ~CSet(){delete set;}


};

void sinchronise(map<int, int> &M, vector<int>& V, int N_m, int N_v)
{
CSet S_1(N_m);
S_1.fill(M);

CSet S_2(N_v);
S_2.fill(V);


//cout << "S1"<<endl;
//S_1.print_set();

//cout << "S2"<<endl;
//S_2.print_set();


for(int i = 0; i<N_v; ++i)
{
    if(S_1.is_in(V[i]))  
    {}
    else{ V[i] = -1;};
    
};

for(int i = 0; i<N_m; ++i)
{
        if(S_2.is_in(M[i])) 
    {}
    else{ M[i] = -1;};
};
//auto it = remove(V.begin(), V.end(), -1);
V.erase(remove(V.begin(),V.end(),-1),V.end());

for (auto it = M.begin(); it!=M.end();)
{
  if(it->second == -1)
  {
    it = M.erase(it); 
  }
  else
  {
    ++it;
};
};

};


int main(void)
{
vector <int> V = {4, 4, 5, 2, 5, 6};
map <int,int> M;
M[0] = 4;
M[1] = 3;
M[2] = 6;
M[3] = 6;
M[4] = 3;
M[5] = 128;
M[6] = 2;
int N = 6;
int N_1 = 7;

CSet S(N);
S.fill(V);
//S.print_set();


//cout<<S.is_in_i(5)<<endl<<S.is_in_i(123)<<endl;

sinchronise(M,V,7,6);

for (auto it = M.begin(); it!=M.end();it++)
{
    cout<< it->second<<endl;
}
    return 0;
};