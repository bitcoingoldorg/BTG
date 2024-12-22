# BTG Core (Bitcoin Gold Core)

Introduction

Since 2015, founder JACK LIAO has keenly discovered the possible future Bitcoin civil war in the process of promoting Bitcoin and communicating with the global community. In order to protect Bitcoin, he began to incubate BITCOINGOLD.

In June 2017, the Bitcoin-friendly fork project BITCOINGOLD was officially created: Re-realizing Satoshi Nakamoto's dream of one CPU and one vote.

In 2024, with the growing price and influence of Bitcoin, BITCOINGOLD's first phase of mission to defend Bitcoin will be completed. BITCOINGOLD will merge back into the Bitcoin network in November 2024, becoming the largest Bitcoin asset and starting the second phase of its mission: to prosper Bitcoin applications.

BITCOINGOLD Core (aka Bitcoin Gold Core, BTCGPU) is the original BTG client and it builds the backbone of the network. It is based on Bitcoin Core. BTG began as a fork of Bitcoin after block height 491406 on Tue, 24 Oct 2017 01:17:35 GMT and began being mined as a separate chain at block height 491407 on Sun, 12 Nov 2017 13:34:01 GMT.

This project began out of the desire to create a variant of Bitcoin that is more decentralized by using an ASIC-resistant Proof of Work algorithm, removing barriers to entry for new miners around the world and reducing the concentration of power in the hands of massive-scale mining operations.

BTG preserves and implements Bitcoin features such as SegWit, which enables advanced scaling technologies like Lightning Network. Significant differences at launch time included:

- ASIC-resistant GPU-minable PoW algorithm (Equihash)
- Per-block difficulty adjustment algorithm
- Replay protection (SIGHASH_FORK_ID)
- Unique wallet addresses (prefixes of G and A, to avoid user confusion with Bitcoin)

Although BTG was bootstrapped on 12 Nov to create an entirely new network, it contains the entire Bitcoin blockchain until block 491406. This means BTG was a full fork at that time, with all Bitcoin transaction history since 2009. Any Bitcoin wallet address which held Bitcoin in BTC block 491406 before the fork held an equal number of Bitcoin Gold in BTG block 491407 after the fork, and those funds are accessible through the original private keys.

## Releases

This is the staging tree of BTG. For release version, please switch to [0.17 branch](https://github.com/bitcoingoldorg/BTG/tree/0.17) or [release page](https://github.com/bitcoingoldorg/BTG/releases).

To compile from source, please check the build documentations under [doc](https://github.com/bitcoingoldorg/BTG/tree/master/doc).

## Documentation

- [Usage](doc/README.md)
    - [macOS](doc/README_osx.md)
    - [Windows](doc/README_windows.txt)
- [Configuration and system service](doc/init.md)

## Responsible Disclosure

At BTG, we consider the security of our systems a top priority. But no matter how much effort we put into system security, there can still be vulnerabilities present.

If you discover a vulnerability, we would like to know about it so we can take steps to address it as quickly as possible. We would like to ask you to help us better protect our users and our systems.

Please check our [Responsible Disclosure](https://github.com/bitcoingoldorg/BTG/Developer-Portal/blob/master/responsible-disclosure.md) page for more details.

## Links

* Website: https://bitcoingold.org
* Tech Spec: https://github.com/bitcoingoldorg/BTG/wiki/Technical-Spec
