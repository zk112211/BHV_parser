#include<fstream>
#include"bvh_parser.h"
#include<iostream>
#include"stack.h"
#include<assert.h>

// a naive bvh parser

using std::ifstream;

int main(int argc, char** argv) {
    META meta_data;
    ifstream file(argv[1]);
    joint *root,*p,*q;
    double x,y,z;
    root = new joint;
    string str;
    Stack<joint*> s;
    int t,n=0,i,j;
    vector<double> m;
    while(file>>str)
    {
        if(str == "HIERARCHY") continue;
        else if(str == "ROOT")
        {
            file>>str;
            root->name = str;
            p = root;
            root->joint_type = "ROOT";
        }
        else if(str == "{")
        {
            s.Push(p);
        }
        else if(str == "OFFSET")
        {
            file>>x>>y>>z;
            p->offset_x = x;
            p->offset_y = y;
            p->offset_z = z;
        }
        else if(str == "CHANNELS")
        {
            file>>n;
            for(i=0;i<n;i++)
            {
                file>>str;
                p->channels.push_back(str);
            }
            t+=n;
        }
        else if(str == "JOINT")
        {
            file>>str;
            q = new joint;
            q->name = str;
            q->joint_type = "JOINT";
            p->children.push_back(q);
            p = q;
        }
        else if(str == "END")
        {
            for(i=0;i<7;i++) file>>str;
            continue;
        }
        else if(str == "}")
        {
            s.Pop(p);
            s.getTop(p);
        }
        else if(str == "MOTION") break;
    }
    s.makeEmpty();
    file>>str>>meta_data.frame;
    file>>str>>str>>meta_data.frame_time;
    for(i=0;i<n;i++)
    {
        s.Push(root);
        while(s.IsEmpty() == false)
        {
            s.Pop(p);
            n = p->children.size();
            for(j=n-1;j>=0;j++)
            {
                s.Push(p->children[j]);
            }
            n = p->channels.size();
            m.clear();
            for(j=0;j<n;j++)
            {
                file>>x;
                m.push_back(x);
            }
            p->motion.push_back(m);
        }
    }
    jsonify(*root, meta_data);
    file.close();
    return 0;
}
