#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <istream>
using namespace std;

class GenomeImpl
{
public:
    GenomeImpl(const string& nm, const string& sequence);
    GenomeImpl(const GenomeImpl& other); //added copy constructor
    GenomeImpl& operator=(const GenomeImpl& other); //added assignment operator
    static bool load(istream& genomeSource, vector<Genome>& genomes);
    int length() const;
    string name() const;
    bool extract(int position, int length, string& fragment) const;
private:
    string m_name = "";
    string m_seq = "";
};

GenomeImpl::GenomeImpl(const string& nm, const string& sequence)
{
    m_name = nm;
    m_seq = sequence;
}
GenomeImpl& GenomeImpl::operator=(const GenomeImpl& other)
{
    m_name = other.m_name;
    m_seq = other.m_seq;
    return *this;
}
GenomeImpl::GenomeImpl(const GenomeImpl& other)
{
    m_name = other.m_name;
    m_seq = other.m_seq;
}
bool GenomeImpl::load(istream& genomeSource, vector<Genome>& genomes)
{
    string name;
    string seq;
    char ch;
    bool char0 = true;
    while(genomeSource.get(ch))
    {
        ch = toupper(ch);
        switch(ch)
        {
            case '>':
                if (name == "")
                {
                    getline(genomeSource,name);
                }
                break;
            case 'A':
            case 'C':
            case 'G':
            case 'T':
            case 'N':
                seq += ch;
                break;
            case '\n':
                continue;
        }
    }
    if(seq == "" || name == "")
    {
        return false;
    }
    genomes.push_back(Genome(name,seq));
    return true;
}

int GenomeImpl::length() const
{
    return m_seq.size();
}

string GenomeImpl::name() const
{
    return m_name;
}

bool GenomeImpl::extract(int position, int length, string& fragment) const
{
    if(position + length > m_seq.size() || position < 0 || length < 0)
        return false;
    fragment = m_seq.substr(position,length);
    return true; 
}

//******************** Genome functions ************************************

// These functions simply delegate to GenomeImpl's functions.
// You probably don't want to change any of this code.

Genome::Genome(const string& nm, const string& sequence)
{
    m_impl = new GenomeImpl(nm, sequence);
}

Genome::~Genome()
{
    delete m_impl;
}

Genome::Genome(const Genome& other)
{
    m_impl = new GenomeImpl(*other.m_impl);
}

Genome& Genome::operator=(const Genome& rhs)
{
    GenomeImpl* newImpl = new GenomeImpl(*rhs.m_impl);
    delete m_impl;
    m_impl = newImpl;
    return *this;
}

bool Genome::load(istream& genomeSource, vector<Genome>& genomes)
{
    return GenomeImpl::load(genomeSource, genomes);
}

int Genome::length() const
{
    return m_impl->length();
}

string Genome::name() const
{
    return m_impl->name();
}

bool Genome::extract(int position, int length, string& fragment) const
{
    return m_impl->extract(position, length, fragment);
}
