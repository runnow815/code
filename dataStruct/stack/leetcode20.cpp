#include<bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;


bool match(char a,char b){
    bool m=false;

    
    if(a=='('&&b==')')m=true;

    if(a=='{'&&b=='}')m=true;

    if(a=='['&&b==']')m=true;

    return m;

}

bool isValid(string s) {
    

    char stack[10005];
    int top=-1;



    for (int i = 0; i < s.length(); i++)
    {   
        //栈空直接进去
        //当前的元素和栈顶元素比 不匹配 入栈找下一个匹配的
        if(top==-1||match(stack[top],s[i])==0)stack[++top]=s[i];


        //匹配就出栈
        if(top!=-1&&match(stack[top],s[i]))top--;
    }
    
    return top==-1;
}

int main(){
    string s;
    cin>>s;

    bool res=isValid(s);

    if(res==true){
        cout<<"Valid"<<endl;
    }else{
        cout<<"Invalid"<<endl;
    }
}