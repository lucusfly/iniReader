/*
 *  File:   ini.h
 *  Author: jiazhiwei
 * 
 *  Created on 2014��8��8��
 *	Modify to add template on 2014��8��29 
 * */


#ifndef _INI_H
#define _INI_H

#include <string>
#include <map>
#include <vector>
#include <set>
#include "stringCommon.h"

#define ANNOTATION '#'
#define VECTORSPLIT ','
#define SECTIONSTART '['
#define SECTIONEND ']'

using namespace std;

template<typename Key>
inline Key transform(const string &str) {
    return (Key)atoll(str.c_str());
}

template<>
inline double transform<double>(const string &str) {
    return atof(str.c_str());
}

template<>
inline float transform<float>(const string &str) {
    return (float)atof(str.c_str());
}

template<>
inline string transform<string>(const string &str) {
    return str;
}

class Ini{
public:
    Ini();
    //����ini file
    bool loadFile(const string &filename);
    //���¼��������ļ�
    bool reloadFile();
    //����ini stream
    bool loadStream(istream &in);
    //���������Ϣ
    string getString(const string &section, const string &key, string ignore="");
    //��vector�ṹ����������Ϣ,Ĭ��ʹ��VECTORSPLIT(,)�ָ�vector
    template<typename Key>
    vector<Key> &getContainer(const string &section, const string &key, vector<Key> &elems);
    //��hash_set�Ľṹ����������Ϣ,Ĭ��ʹ��VECTORSPLIT(,)�ָ�vector
    template<typename Key>
    set<Key> &getContainer(const string &section, const string &key, set<Key> &elems);
    //����ֵ���ͽ���������Ϣ,����bool,int,long,long long,double,float
    template<typename Key>
    Key getValue(const string &section, const string &key, Key ignore = 0);
    //��ӡ����������Ϣ
    friend ostream &operator<<(ostream &os, const Ini &ini);
private:
    map<string, map<string, string> > m_tree;
    string filename;
    bool error;//ȡ������ʱ�Ƿ����
};


template<typename Key>
vector<Key> &Ini::getContainer(const string &section, const string &key, vector<Key> &elems) {
    string value = getString(section, key);
    
    vector<string> splitRes;
    if (!value.empty() && !error)
        split(value, splitRes, VECTORSPLIT);
    
    elems.clear();
    for (size_t i = 0; i < splitRes.size(); ++i) {
        elems.push_back(transform<Key>(splitRes[i]));
    }
    return elems;
}

template<typename Key>
set<Key> &Ini::getContainer(const string &section, const string &key, set<Key> &elems) {
    string value = getString(section, key);
    
    vector<string> splitRes;
    if (!value.empty() && !error)
        split(value, splitRes, VECTORSPLIT);
    
    elems.clear();
    for (size_t i = 0; i < splitRes.size(); ++i) {
        elems.insert(transform<Key>(splitRes[i]));
    }
    return elems;
}

template<typename Key>
Key Ini::getValue(const string &section, const string &key, Key ignore) {
    string value = getString(section, key);

    if (error || value.empty()) 
        return ignore;
    else
        return transform<Key>(value);
}

#endif 
