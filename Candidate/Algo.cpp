#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define q 200
#define Null -200
//General Boundary where gb[i] is the General Bound for Target Class i [1-7]
vector<vector<int> > gb[8]; 
//Specific Boundary where sb[i] is the Specific Bound for Target Class i [1-7]
vector<int> sb[8];
vector<int> v1(16,Null);
vector<int> v2(16,q);
vector<vector<int> > v;
vector<int> target;
string row,item,t;
char sep=',';
//Prototypes for the functions
void printfull(vector<vector<int> >);
void printtarget(vector<int>);
void collect();
void printfull(vector<vector<int> > v){
	unsigned int i,j;
	for(i=0;i<v.size();i++){
		cout<<i<<' ';
		for(j=0;j<v[i].size();j++){
			cout<<v[i][j]<<' ';
		}
		cout<<'\n';
	}
}
void printtarget(vector<int> v){
	size_t i;
	for(i=0;i<v.size();i++){
		cout<<i<<' '<<v[i]<<'\n';
	}
}
void collect()
{
	fstream inp("/media/bharatrlinux/LinuxSecondary/GitHubRepos/ML-assignments/Candidate/Dataset/inputdatafinal.csv",std::fstream::in);
	fstream inpt("/media/bharatrlinux/LinuxSecondary/GitHubRepos/ML-assignments/Candidate/Dataset/target.csv",std::fstream::in);
	if(!inp){
		cout<<"Failed to open!";
		return;
	}
	if(!inpt){
		cout<<"Target failed to open!";
		return;
	}
    while(getline(inpt,t)){
		stringstream tar(t);
		int tr=0;
		tar>>tr;
		target.push_back(tr);
	}
	while(getline(inp,row)){
		stringstream ss(row);
		vector<int> res;
		while(getline(ss,item,sep)){
			stringstream s(item);
			int r=0;
			s>>r;
			res.push_back(r);
        }
		v.push_back(res);
	    res.clear();
	}
	inp.close();
	inpt.close();
	//printtarget(target);
    //printfull(v);
}
bool is_general_than_equal_to(vector<int> &v1,vector<int> &v2){ 
	//Returns true if v1 is strictly general than v2, false otherwise
	unsigned int flag=0,i;
	for(i=0;i<v1.size();i++){
		if( ( (v1[i]!=q&&v1[i]!=Null)&&
			  (v1[i]!=v2[i]&&v2[i]!=Null) ) ||
			(v1[i]==Null&&v2[i]!=Null) )
		{ 
			flag=1; break; 
		}	
	}
	if(flag) return false;
	else return true;
}
bool is_specific_than_equal_to(vector<int> &v1,vector<int> &v2){ 
	//Returns true if v1 is strictly general than v2, false otherwise
	unsigned int flag=0,i;
	for(i=0;i<v1.size();i++){
		if( ( (v1[i]!=q&&v1[i]!=Null)&&
			  (v1[i]!=v2[i]&&v2[i]!=q) ) ||
			(v1[i]==q&&v2[i]!=q) )
		{ 
			flag=1; break; 
		}	
	}
	if(flag) return false;
	else return true;
}
bool is_general_than(vector<int> &v1,vector<int> &v2)
{
	return (is_general_than_equal_to(v1,v2))&&(!is_specific_than_equal_to(v1,v2));
}
bool is_specific_than(vector<int> &v1,vector<int> &v2)
{
	return (is_specific_than_equal_to(v1,v2))&&(!is_general_than_equal_to(v1,v2));
}
int main(int argc, char const *argv[])
{
    ll i;
    //Initializes General and Specific Boundary of ALL 7 Version Spaces 
    for(i=1;i<=7;i++){           
        gb[i].push_back(v2);

    }
    for(i=1;i<=7;i++){
        sb[i] = v1;
    }
    vector<vector<int> > lists = {{0,1},
                                  {0,1},
                                  {0,1},
                                  {0,1},
                                  {0,1},
                                  {0,1},
                                  {0,1},
                                  {0,1},
                                  {0,1},
                                  {0,1},
                                  {0,1},
                                  {0,1},
                                  {0,2,4,5,6,8},
                                  {0,1},
                                  {0,1},
                                  {0,1}};
	ll j,k,m;

    //Function that collects training examples
    collect();
    for(i=1;i<=7;i++)
    {
        //Algorithm begins here
        vector<int> temphyp,res,temp;
        //Hypothesis object
        for(j=0;j<=100;j++)
        {
            //Positive Example for Version Space gb[i] and sb[i]
            if(target[j]==i)	                             
            { 
                //Negative Example for ALL other gb[m] and sb[m],m!=i,m=[1-7]
                //Iterates through ALL the attributes
                for(k=0;k<16;k++)					  
                {
                    if(sb[i][k]==Null)
                    {
                        sb[i][k]=v[j][k];
                    }
                    else if(sb[i][k]!=v[j][k])
                    {
                        sb[i][k]=q;
                    }
                }
            }
        }    
        /*for(j=0;j<=100;j++)
        {
            for(m=1;m<=7;m++)
            {
                //Negative Examples only for m!=i
                if((target[j]==i)&&(m==i)) continue;						
                for(auto gbiterator=gb[m].begin();gbiterator<gb[m].end();gbiterator++)
                {
                	res = *gbiterator;
                	temp = *gbiterator;
                	if(is_general_than_equal_to(*gbiterator,v[j]))
                	{
                		gb[m].erase(gbiterator);
                	}
                    //Iterates through ALL the attributes
                    for(k=0;k<16;k++)
                    {
						vector<int> res1 = res;
						cout<<'\n';
                        if(temp[k]==q)
                        {		
                    		for(unsigned ll listiterator=0;listiterator<lists[k].size();listiterator++)
                    		{	
                    			if(lists[k][listiterator]==v[j][k]) {;}
                    			else
                    			{
                    				res1[k]=lists[k][listiterator];
                    				for(auto m:res1)
                    				{
                    					if(m==200)
                    						cout<<"? ";
                    					else
                    						cout<<m<<' ';
                    				}
                    				gb[m].push_back(res1);
                    				res1.clear();
                    			}
                    		}
                    		cout<<'\n';
                        }
                        else if(temp[k]==v[j][k])
                        {
							res[k]=Null;
							gb[m].push_back(res);
                        }
                    }
                }
                res.clear();
                temp.clear();
            }
                ll sbflag=0;
					//Remove any hypothesis in gb[i] which is NOT general than sb 
                    for(gbiterator=0;gbiterator<gb[m].size();gbiterator++)
                    {
                        if(is_general_than(gb[m][gbiterator],sb[m]))
                        {
                            sbflag++; break; 
                        }

                        //If this is true, there is NO specific hypothesis more specific than gb, hence it must be reverted
                        if(!sbflag) gb[m][gbiterator] = temphyp;
                    }
        }*/
        /*for(gbiterator=0;gbiterator<gb[i].size();gbiterator++)
        {
        	if(!is_general_than(gb[i][gbiterator],sb[i]))
        	{
        		gb[i].erase(gb[i].begin()+gbiterator);
        	}
        }*/
	}    
    for(i=1;i<=7;i++)
    {
    	unsigned ll gbiterator;
		cout<<"Version Space "<<i<<":- ";
		/*cout<<"\nGB: ";
    	for(gbiterator=0;gbiterator<gb[i].size();gbiterator++)
    	{
    		cout<<"\n-------------------------\n";
    		for(j=0;j<16;j++)
    		{
    			if(gb[i][gbiterator][j]==200)
    				cout<<'?'<<' ';
    			else if(gb[i][gbiterator][j]==-200)
    				cout<<"Null ";
    			else
    				cout<<gb[i][gbiterator][j]<<' ';
    		}
    		cout<<"\n------------------------\n";
    	}*/
    	cout<<"SB: \n";
    	cout<<"\n-------------------------\n";
    	for(k=0;k<16;k++)
    	{
    		if(sb[i][k]==-200)
    			cout<<"Null ";
    		else if(sb[i][k]==200)
    			cout<<"? ";
    		else
    			cout<<sb[i][k]<<' ';
    	}
    	cout<<"\n-------------------------\n";
    }
    return 0;
}