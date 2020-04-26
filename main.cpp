//
//  main.cpp
//  CodeCraft
//
//  Created by 郑晓鹏 on 2020/4/23.
//  Copyright © 2020年 郑晓鹏. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <cstdio>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;
const int MAX_Vertex_Num = 570000;
const long int mysize=570000;//预设数组长度
set<long int>s;//所有顶点
set<long int>s2;//入度大于1的顶点
//const int MAX_Vertex_Num = 20480;
//const long int mysize=20480;//预设数组长度
long int setsize;
long int (*DG)[MAX_Vertex_Num];
long int lengthmap;
//long int *mapping1;//设定映射表 下标为顺位 值为用户账号
//long int *mapping2;//设定映射表 下标为用户账号 值为顺位
map<long int, long int> thismap1;//设定映射表 顺位 值为用户账号
map<long int, long int> thismap2;//设定映射表 用户账号 值为顺位
long int (*p)[4];
//long int mapping3[MAX_Vertex_Num];//设定映射表 下标为用户账号 值为是否有入度
set<set<long int> >set_circle_element;
set<long int>set_circle;
vector<long int>vector_circle;
vector<vector<long int> >vector_circle_element;
queue<long int> q;
long int *stack;
bool *inStack;
bool *visited;
//重载对比函数用于vector<vector>排序
bool cmp(vector<long int>x,vector<long int>y)
{
    vector<long int>::iterator it1;
    vector<long int>::iterator it2;
    if(x.size()<y.size())
        return true;
    else if(x.size()>y.size())
        return false;
    else
    {
        long int length=x.size();
        it1=x.begin();
        it2=y.begin();
        for(long int i=0;i<length;i++)
        {
        if((*(it1+i))<(*(it2+i)))
        {
            return true;
        }
        else if(*(it1+i)>*(it2+i))
        {
            return false;
        }
        else
        {
            continue;
        }
        }
    }
    return false;
}


//分割字符串
void split(string &s, vector<string> &list1)
{
    istringstream tmp_string(s);
    string ss;
    while (getline(tmp_string, ss, ','))
    {
        list1.push_back(ss);
    }
    
}

//字符串转数字
template <class Type> Type stringToNum(const string& str)
{
    istringstream iss(str);
    Type num;
    iss >> num;
    return num;
}

//读取txt文件
void readTxt(string file,long int (*p)[4],long int& count)
{
    ifstream infile;
    infile.open(file.data());   //将文件流对象与文件连接起来
    assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行
    
    string s;
    while(getline(infile,s))
    {
        count++;
        vector<string> list1;
        split(s, list1);
        int column=1;
        for (vector<string>::iterator ele=list1.begin();ele!=list1.end();ele++)
        {
            
            p[count][column]=stringToNum<long int>(*ele);
            //            cout<<p[count][column]<<',';
            column++;
        }
        //        cout<<endl;
    }
    //    cout<<count<<endl;
    infile.close();             //关闭文件输入流
}

//写txt文件
void writeTxt(string file,vector<vector<long int> >data)
{
    ofstream infile(file);
//    infile.open(file.data());   //将文件流对象与文件连接起来
    vector<vector<long int> >::iterator it1;
    vector<long int>::iterator it2;
    infile<<data.size()<<endl;
    for(it1=data.begin();it1!=data.end();it1++)
    {
        for(it2=(*it1).begin();it2!=(*it1).end();it2++)
        {
            
            infile<<(*it2);
            if((it2+1)!=(*it1).end())
                infile<<',';
        }
        infile<<endl;
    }
    infile.close();             //关闭文件输入流
}


//深度搜索
void DFS(long int x,bool visited[MAX_Vertex_Num],long int stack[MAX_Vertex_Num],long int& top,bool inStack[MAX_Vertex_Num],long int& count,int deep)
{
    visited[x]=true;
    stack[++top]=x;
    inStack[x]=true;
    deep++;
    if(deep>7)
    {
        top--;
        deep--;
        inStack[x]=false;
        return;
    }
    for (int i=1;i<=setsize;i++)
    {
        if (DG[x][i]==1)//有边
        {
            if (!inStack[i])
            {
                DFS(i,visited,stack,top,inStack,count,deep);
            }
            else //条件成立，表示下标为x的顶点到 下标为i的顶点有环
            {
                //从i到x是一个环，top的位置是x，下标为i的顶点在栈中的位置要寻找一下
                //寻找起始顶点下标在栈中的位置
                long int t;
                for (t=top;stack[t]!=i;t--);
                //输出环中顶点
                for (long int j=t;j<=top;j++)
                {
                    q.push(thismap1.at(stack[j]));
                }
//                cout<<"t1:"<<(top-t+1)<<endl;
//                cout<<"t2:"<<q.size()<<endl;
                if(q.size()>=3&&q.size()<=7)
//                if(top-t+1==4)
                {
                
                int judge=0;
                long int mark;
                mark=t;
                long int duibi=thismap1.at(stack[t]);
                for (long int j=t+1;j<=top;j++)
                {
                    if(duibi>thismap1.at(stack[j]))
                    {
                        mark=j;
                        duibi=thismap1.at(stack[j]);
                    }
                }
                for(long int j=t;j<mark;j++)
                {
                    long int del=q.front();
                    q.pop();
                    q.push(del);
                }
//                long int test=q.front();
//                q.pop();
//                q.push(test);
//                for(long int j=2;j<=q.size();j++)
//                {
//                    long int test2=q.front();
//                    q.pop();
//                    q.push(test2);
//                    if (test==test2)
//                    {
//                        judge=1;
//                        break;
//                    }
//
//                }
                if(judge==0)
                {
                count++;
//                cout<<"第"<<count<<"环为:";
                for (long int j=t;j<=top;j++)
                {
//                    cout<<mapping1[stack[j]]<<" ";
                    set_circle.insert(q.front());
                    vector_circle.push_back(q.front());
                    q.pop();
                }
                if(set_circle_element.find(set_circle)==set_circle_element.end() )
                {
                    set_circle_element.insert(set_circle);//添加新的元素组合
                    vector_circle_element.push_back(vector_circle);
                }
                
                vector_circle.clear();
                set_circle.clear();
//                cout<<endl;
                }
                }
                while (!q.empty()) q.pop();
            }
        }
    }
    //处理完结点后，退栈
    top--;
    deep--;
    inStack[x]=false;
}

//vexnum账号个数
void CheckCircle(int deep)
{
    long int countcircle=0;//环的个数
    long int top=0;
    stack=new long int [MAX_Vertex_Num];
    inStack=new bool[MAX_Vertex_Num];
    visited=new bool [MAX_Vertex_Num];
    for (long int i=1;i<=setsize;i++)
    {
        cout<<i<<'/'<<setsize<<endl;
//        if (!visited[i])
        {
            DFS(i,visited,stack,top,inStack,countcircle,deep);
        }
    }
}



int main() {
    long int countall=0;//输入数据条数
    p=new long int [mysize][4];//输入数组
    DG=new long int [MAX_Vertex_Num][MAX_Vertex_Num];
    int deep=0;
//    string infile="/Users/zhengxiaopeng/Downloads/2020HuaweiCodecraft-TestData-master/58284/test_data.txt";//输入文件地址
//    string outfile="/Users/zhengxiaopeng/Downloads/outtest.txt";//输出文件地址
    string infile="/data/test_data.txt";//输入文件地址
    string outfile="/projects/student/result.txt";
    readTxt(infile,p,countall);//读入数据
    //测试输入内容是否正常
    //    for(long int i=1;i<=count;i++)
    //    {
    //        for(int j=1;j<=3;j++)
    //            cout<<p[i][j]<<',';
    //        cout<<endl;
    //    }
    
    
    for(long int i=1;i<=countall;i++)
    {
        s.insert (p[i][1]);
        s.insert (p[i][2]);
    }
    
    
    for(long int i=1;i<=countall;i++)
    {
        s2.insert (p[i][2]);
    }
    //测试set是否正常
    //    set<long int>::iterator it;
    //    for(it=s.begin ();it!=s.end ();it++)
    //    {
    //        cout<<*it<<endl;
    //    }
    
    setsize=s.size();//计算账户数目
    lengthmap=*(s.end())+1;
    set<long int>::iterator it;
    long int countmap=0;
    for(it=s.begin ();it!=s.end ();it++)
    {
        countmap++;
        thismap1.insert(pair<long int, long int>(countmap, *it));
        thismap2.insert(pair<long int, long int>(*it,countmap));
    }
    
//    for(it=s2.begin ();it!=s2.end ();it++)
//    {
//        mapping3[*it]=1;
//    }
    
    //测试mapping是否正常
    //    for(long int i=0;i<=setsize;i++)
    //        cout<<mapping[i]<<endl;
    
    
    
    //构建图
    for(long int i=1;i<=countall;i++)
    {
        long int transferout=p[i][1];
        long int transferin=p[i][2];
        long int maptransferout=thismap2.at(transferout);
        long int maptransferin=thismap2.at(transferin);
        DG[maptransferout][maptransferin]=1;
//        cout<<i<<endl;
    }
    CheckCircle(deep);
    vector<vector<long int> >::iterator it1;
    vector<long int>::iterator it2;
    cout<<vector_circle_element.size()<<endl;
    
    sort(vector_circle_element.begin(),vector_circle_element.end(),cmp);
    writeTxt(outfile,vector_circle_element);
//    delete DG;
    return 0;
}

