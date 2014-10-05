// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Copyright (c) 2013 Royalcoin Developers

// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
            boost::assign::map_list_of
            (     0, uint256("0xfa8893f50b342d6b21190cac6d0189f932fdde7b8564abf916a840bae78103c8"))
            (     5, uint256("0xdf241f0476126d4506744595ccdce132328df9dd1a8ae875664aba338c26275a"))
            (  1000, uint256("0x8a7e1e6979694f4c4cc5ddb248dc1ffade2b98aa506520ebb94b617219f92259"))
            (  2500, uint256("0x759a5b60cc7c9bede906ab6a0d3cc1b59c97e77f5ab5201c145e40dbf687d229"))
            ( 12000, uint256("0x145efa9c50cdcfa4ed20eb2e0806b6f04642a7d98194211cf3b3affcfc18b8e3"))
            ( 25000, unit256("0xf8cc89f1a44cb7d3046ad78a8f66f6cf14c86ad0aa0e371de26c1849cd2111e2"))
            ( 55000, uint256("0xc88d5149ad07907f39cfb3a62acefeb034f4d8e11a56997149e9f5122a26dc52"))
            ;


    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
