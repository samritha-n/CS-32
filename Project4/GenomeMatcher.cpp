#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Trie.h"
#include <algorithm>
using namespace std;



class GenomeMatcherImpl
{
public:
    GenomeMatcherImpl(int minSearchLength);
    void addGenome(const Genome& genome);
    int minimumSearchLength() const;
    bool findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const;
    bool findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const;
private:
    int m_minLength;
    vector<Genome> m_genomes;

    struct DNAFragment
    {

        DNAFragment(const Genome* gn, int pos)
        :genome(gn), position(pos)
        {}
        DNAFragment& operator= (const DNAFragment& other)
        {
            if(this != &other)
            {
                delete &genome;
                genome = new Genome(*other.genome);
                position = other.position;
            }
            return *this;
        }
        const Genome* genome;
        int position;
        
    };
    
    Trie<DNAFragment> m_trie;
};


GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
{
    m_minLength = minSearchLength;
}

void GenomeMatcherImpl::addGenome(const Genome& genome)
{
    m_genomes.push_back(genome);
    for(int i=0; i <= genome.length()-minimumSearchLength(); i++)
    {
        string subseq = "";
        genome.extract(i,m_minLength,subseq);
        Genome* gn = new Genome(genome);
         DNAFragment fr(gn, i);
//        fr.genome = genome;
//        fr.position = i;
        m_trie.insert(subseq,fr);
        
    }
    
}

int GenomeMatcherImpl::minimumSearchLength() const
{
    return m_minLength;
}

bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    if(fragment.length() < minimumLength || minimumLength < m_minLength)
        return false;
    vector<DNAFragment> dnaFR = m_trie.find(fragment.substr(0,m_minLength),exactMatchOnly);
    if(exactMatchOnly == false)
    {
        vector<DNAFragment> exactMatches = m_trie.find(fragment.substr(0,m_minLength),true);
        for(vector<DNAFragment>::iterator it = exactMatches.begin(); it != exactMatches.end(); it++)
        {
            string fr;
            if((*it).genome->extract((*it).position + m_minLength, fragment.length() - m_minLength, fr) == false)
                continue;
            int notIdentical=0;
            bool stop = false;
            int longestMatch = m_minLength;
            for(int i=0; i<fragment.length() - m_minLength; i++)
            {
                if(fr[i] != fragment[m_minLength+i])
                {
                    if(i == 0)
                        return false;
                    notIdentical++;
                }
                if(notIdentical > 1)
                {
                    stop = true;
                    break;
                }
                longestMatch++;
            }
            if(!stop)
            {
                DNAMatch m;
                m.genomeName = (*it).genome->name();
                m.position = (*it).position;
                m.length = longestMatch;
                matches.push_back(m);
            }
        }
    }
    
    return false;  // This compiles, but may not be correct
}

bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    return false;  // This compiles, but may not be correct
}

//******************** GenomeMatcher functions ********************************

// These functions simply delegate to GenomeMatcherImpl's functions.
// You probably don't want to change any of this code.

GenomeMatcher::GenomeMatcher(int minSearchLength)
{
    m_impl = new GenomeMatcherImpl(minSearchLength);
}

GenomeMatcher::~GenomeMatcher()
{
    delete m_impl;
}

void GenomeMatcher::addGenome(const Genome& genome)
{
    m_impl->addGenome(genome);
}

int GenomeMatcher::minimumSearchLength() const
{
    return m_impl->minimumSearchLength();
}

bool GenomeMatcher::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    return m_impl->findGenomesWithThisDNA(fragment, minimumLength, exactMatchOnly, matches);
}

bool GenomeMatcher::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    return m_impl->findRelatedGenomes(query, fragmentMatchLength, exactMatchOnly, matchPercentThreshold, results);
}
