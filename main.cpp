#include<iostream>
#include<cstring>
#include<string>
#include <fstream>

using namespace std;


string mat[100][100];
string prod[100];
string CYK[100][100];
int p,nr_prod;

 string cat( string a, string b)
{
    int i;
    string s=a;
    for(i=0;i<b.length();i++)
        if(s.find(b[i]) > s.length())
            s+=b[i];
    return s;
}

///functie care imi separa partea dreapta a productiilor de partea stanga
void separare(string a)
{
    int i;
    p=0;
    while(a.length())
    {
        i=a.find("|");
        if(i>a.length())
        {
            prod[p++] = a;
            a="";
        }
        else
        {
            prod[p++] = a.substr(0,i);
            a=a.substr(i+1,a.length());
        }
    }
}

///functie care returneaza siruri concatenate care pot produce sirul p
 string cauta(string p)
{
    int j,k;
    string s="";
    for(j=0;j<nr_prod;j++)
    {
        k=1;
        while(mat[j][k] != "")
        {
            if(mat[j][k] == p)
            {
                s=cat(s,mat[j][0]);
            }
            k++;
        }
    }
    return s;
}

///functie care creeaza toate variantele posibile

 string reuniune(string a, string b)
{
    int i,j;
    string s=a,ss="";
    for(i=0;i<a.length();i++)
        for(j=0;j<b.length();j++)
        {
            s="";
            s=s+a[i]+b[j];
            ss=ss+cauta(s);
        }
    return ss;
}

int main()
{

    ifstream f("input.in");
    int i,aux,j,l,k;
    string a,str,r,pr,start="S";
    f >> nr_prod;
    for(i=0;i<nr_prod;i++)
    {
        f >> a;
        aux=a.find("->");
        mat[i][0] = a.substr(0,aux);
        a = a.substr(aux+2, a.length());
        separare(a);
        for(j=0;j<p;j++)
        {
            mat[i][j+1]=prod[j];

        }

    }

   /* for(i=0;i<nr_prod;i++)
    {
        for(j=0;j<p;j++)
            cout<<mat[i][j+1];
        cout<<endl;
    }
    cout<<endl;*/

    string st;

    f >> str;

    ///creez diagonala "principala"
    for(i=0;i<str.length();i++)
    {
        r="";
        st = "";
        st+=str[i];
        for(j=0;j<nr_prod;j++)
        {
            k=1;
            while(mat[j][k] != "")
            {
                if(mat[j][k] == st)
                {
                    r=cat(r,mat[j][0]);
                }
                k++;
            }
        }
        CYK[i][i]=r;
    }

    ///creez restul matricei
    for(k=1;k<str.length();k++)
    {
        for(j=k;j<str.length();j++)
        {
            r="";
            for(l=j-k;l<j;l++)
            {
                pr = reuniune(CYK[j-k][l],CYK[l+1][j]);
                r = cat(r,pr);
            }
            CYK[j-k][j] = r;
        }
    }

    for(i=0;i<str.length();i++)
    {
        k=0;
        l=str.length()-i-1;
        for(j=l;j<str.length();j++)
        {
            cout<<CYK[k++][j]<<" ";
        }
        cout<<endl;
    }



    return 0;
}
