# Introduction

Apollo Cyber RT is an open source, high performance runtime framework designed
specifically for autonomous driving (AD) scenarios. Based on a centralized
computing model, it is greatly optimized for high concurrency, low latency, and
high throughput in autonomous driving.

During the last few years of development of AD technologies, we have learned a
lot from our previous experience with Apollo. The industry is evolving and so is
Apollo. Going forward, Apollo has already moved from development to production.
With volume deployment in real world, we see demands for the highest level of
robustness and performance. That’s why we spent years building and perfecting
Apollo Cyber RT, which addresses those requirements of AD solutions.

Key benefits of using Apollo Cyber RT:

- Accelerate development
  - Well defined task interface with data fusion
  - Array of development tools
  - Large set of sensor drivers
- Simplify deployment
  - Efficient and adaptive message communication
  - Configurable user level scheduler with resource awareness
  - Portable with fewer dependencies
- Empower your own autonomous vehicles
  - The default open source runtime framework
  - Building blocks specifically designed for AD scenarios
  - Plug and play your own AD system

# Build/Installation

## Dependencies

You can run the following command to install CyberRT pre-requisites:

```
bash tools/install/install_prereqs.sh
```

`sudo` privilege is needed, and by default Fast-DDS is installed under
`/usr/local/fast-rtps/`.

## Release Build

Binary releases for CyberRT is still a Work-In-Progress. Contribution is highly
appreciated.

# Documents

- **_New!!_**
  [How to Develop Cyber RT inside Docker Environment on Both x86 and ARM Platform](https://github.com/ApolloAuto/apollo/tree/master/docs/cyber/CyberRT_Docker.md):
  Official docker image for Cyber RT development, which is easiest way to build
  and play with Cyber RT. On top of that, we officially support development of
  Cyber RT on both x86 and ARM platform.

- [Apollo Cyber RT Quick Start](https://github.com/ApolloAuto/apollo/tree/master/docs/cyber/CyberRT_Quick_Start.md):
  Everything you need to know about how to start developing your first
  application module on top of Apollo Cyber RT.

- [Apollo Cyber RT Developer Tools](https://github.com/ApolloAuto/apollo/tree/master/docs/cyber/CyberRT_Developer_Tools.md):
  Detailed guidance on how to use the developer tools from Apollo Cyber RT.

- [Apollo Cyber RT API for Developers](https://github.com/ApolloAuto/apollo/tree/master/docs/cyber/CyberRT_API_for_Developers.md):
  A comprehensive guide to explore all the APIs of Apollo Cyber RT, with many
  concrete examples in source code.

- [Apollo Cyber RT FAQs](https://github.com/ApolloAuto/apollo/tree/master/docs/cyber/CyberRT_FAQs.md):
  Answers to the most frequently asked questions about Apollo Cyber RT.

- [Apollo Cyber RT Terms](https://github.com/ApolloAuto/apollo/tree/master/docs/cyber/CyberRT_Terms.md):
  Commonly used terminologies in Cyber RT documentation and code.

- [Apollo Cyber RT Python Wrapper](python/README.md): Develop projects in
  Python.

More documents to come soon!
