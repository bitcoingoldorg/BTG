// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_PRIMITIVES_BLOCK_H
#define BITCOIN_PRIMITIVES_BLOCK_H

#include <arith_uint256.h>
#include <primitives/transaction.h>
#include <serialize.h>
#include <uint256.h>
#include <version.h>
#include <string.h>

namespace Consensus {
    struct Params;
};

static const int SERIALIZE_BLOCK_LEGACY = 0x04000000;

/** Nodes collect new transactions into a block, hash them into a hash tree,
 * and scan through nonce values to make the block's hash satisfy proof-of-work
 * requirements.  When they solve the proof-of-work, they broadcast the block
 * to everyone and the block is added to the block chain.  The first transaction
 * in the block is a special one that creates a new coin owned by the creator
 * of the block.
 */
class CBlockHeader
{
public:
    static const size_t HEADER_SIZE = 4+32+32+4+4+4;  // Excluding Equihash solution
    // header
    int32_t nVersion;
    uint256 hashPrevBlock;
    uint256 hashMerkleRoot;
    uint32_t nHeight;
    uint32_t nReserved[7];
    uint32_t nTime;
    uint32_t nBits;
    uint256 nNonce;
    std::vector<unsigned char> nSolution;  // Equihash solution.

    CBlockHeader()
    {
        SetNull();
    }

    SERIALIZE_METHODS(CBlockHeader, obj)
    {
        bool new_format = !(s.GetVersion() & SERIALIZE_BLOCK_LEGACY);
        READWRITE(obj.nVersion);
        READWRITE(obj.hashPrevBlock);
        READWRITE(obj.hashMerkleRoot);
        if (new_format) {
            READWRITE(obj.nHeight);
            for(size_t i = 0; i < (sizeof(obj.nReserved) / sizeof(obj.nReserved[0])); i++) {
                READWRITE(obj.nReserved[i]);
            }
        }
        READWRITE(obj.nTime);
        READWRITE(obj.nBits);
        if (new_format) {
            READWRITE(obj.nNonce);
            READWRITE(obj.nSolution);
        } else {
            uint32_t legacy_nonce = (uint32_t)obj.nNonce.GetUint64(0);
            READWRITE(legacy_nonce);
            //if (ser_action.ForRead())
	    {
		CBlockHeader& obj_temp = const_cast<CBlockHeader&>(obj);
                obj_temp.nNonce = ArithToUint256(arith_uint256(legacy_nonce));
	    }
        }
    }

    void SetNull()
    {
        nVersion = 0;
        hashPrevBlock.SetNull();
        hashMerkleRoot.SetNull();
        nHeight = 0;
        memset(nReserved, 0, sizeof(nReserved));
        nTime = 0;
        nBits = 0;
        nNonce.SetNull();
        nSolution.clear();
    }

    bool IsNull() const
    {
        return (nBits == 0);
    }

    uint256 GetHash() const;
    uint256 GetHash(const Consensus::Params& params) const;

    int64_t GetBlockTime() const
    {
        return (int64_t)nTime;
    }
};


class CBlock : public CBlockHeader
{
public:
    // network and disk
    std::vector<CTransactionRef> vtx;

    // memory only
    mutable bool fChecked;

    CBlock()
    {
        SetNull();
    }

    CBlock(const CBlockHeader &header)
    {
        SetNull();
        *(static_cast<CBlockHeader*>(this)) = header;
    }

    SERIALIZE_METHODS(CBlock, obj)
    {
        READWRITEAS(CBlockHeader, obj);
        READWRITE(obj.vtx);
    }

    void SetNull()
    {
        CBlockHeader::SetNull();
        vtx.clear();
        fChecked = false;
    }

    CBlockHeader GetBlockHeader() const
    {
        CBlockHeader block;
        block.nVersion       = nVersion;
        block.hashPrevBlock  = hashPrevBlock;
        block.hashMerkleRoot = hashMerkleRoot;
        block.nHeight        = nHeight;
        memcpy(block.nReserved, nReserved, sizeof(block.nReserved));
        block.nTime          = nTime;
        block.nBits          = nBits;
        block.nNonce         = nNonce;
        block.nSolution      = nSolution;
        return block;
    }

    std::string ToString() const;
};

/**
 * Custom serializer for CBlockHeader that omits the nonce and solution, for use
 * as input to Equihash.
 */
class CEquihashInput : private CBlockHeader
{
public:
    CEquihashInput(const CBlockHeader &header)
    {
        CBlockHeader::SetNull();
        *((CBlockHeader*)this) = header;
    }

    SERIALIZE_METHODS(CEquihashInput, obj)
    {
        READWRITE(obj.nVersion);
        READWRITE(obj.hashPrevBlock);
        READWRITE(obj.hashMerkleRoot);
        READWRITE(obj.nHeight);
        for(size_t i = 0; i < (sizeof(nReserved) / sizeof(nReserved[0])); i++) {
            READWRITE(obj.nReserved[i]);
        }
        READWRITE(obj.nTime);
        READWRITE(obj.nBits);
    }
};

/** Describes a place in the block chain to another node such that if the
 * other node doesn't have the same branch, it can find a recent common trunk.
 * The further back it is, the further before the fork it may be.
 */
struct CBlockLocator
{
    std::vector<uint256> vHave;

    CBlockLocator() {}

    explicit CBlockLocator(const std::vector<uint256>& vHaveIn) : vHave(vHaveIn) {}

    SERIALIZE_METHODS(CBlockLocator, obj)
    {
        int nVersion = s.GetVersion();
        if (!(s.GetType() & SER_GETHASH))
            READWRITE(nVersion);
        READWRITE(obj.vHave);
    }

    void SetNull()
    {
        vHave.clear();
    }

    bool IsNull() const
    {
        return vHave.empty();
    }
};

#endif // BITCOIN_PRIMITIVES_BLOCK_H
