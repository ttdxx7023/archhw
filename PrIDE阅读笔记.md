# PrIDE阅读笔记

### 解决的问题

设计一种安全、低成本的In-DRAM跟踪器

### 文章贡献

- 低成本跟踪器的设计必须以所有模式的故障率有限为目标
- 观察到低成本 DRAM 跟踪器脆弱性的根本原因是它们的反驱动策略决策，这使得很难限制故障率。  
- 提出了 PrIDE，一种简单的概率 4 条目跟踪器，可保证所有模式的低失败率。  PrIDE 可容忍 1.9K 的 Rowhammer 阈值。  
- 与 RFM 共同设计 PrIDE，以容忍更低的阈值 (400)，且速度仅下降 1.6%。

### 主要思路

> 主要见解是，可以通过独立于访问模式（不受访问地址的影响）的策略决策来确保低成本跟踪器的安全，从而可以确定最坏情况下的故障时间。 本文的目标是开发一种低成本安全的 DRAM 跟踪器，保证所有访问模式的故障率（故障时间在数年范围内）可忽略不计。

PrIDE（Probabilistic In-DRAM Tracker）的插入策略、逐出策略和缓解策略如下：

1. **插入策略（Insertion Policy）**：
   - PrIDE的插入策略是基于概率抽样的。在每次DRAM行激活时，PrIDE会以一定的概率p决定是否将该行插入到FIFO缓冲区中。这个概率是固定的，并且与访问模式无关，这意味着每个激活的行都有相同的机会被插入到跟踪器中，而不管之前或之后访问了哪些地址。这种设计使得插入决策不受特定访问模式的影响，从而提高了安全性。
2. **逐出策略（Eviction Policy）**：
   - PrIDE的逐出策略是FIFO（先进先出）。当FIFO缓冲区满时，最旧的条目（即最先插入的行）会被驱逐出去，为新插入的行腾出空间。这个逐出决策仅基于条目的插入顺序，与行的地址或访问模式无关。
3. **缓解策略（Mitigation Policy）**：
   - PrIDE的缓解策略同样是FIFO。在每个刷新周期tREFI，如果FIFO缓冲区中存在条目，PrIDE会选择最旧的条目进行缓解操作（即刷新其相邻的受害行）。这个缓解决策也仅基于条目的插入顺序，与行的地址或访问模式无关。

PrIDE的设计目标是确保所有政策决策都不依赖于访问模式，这样可以计算出在最坏情况下的失效时间，并且能够保证在所有访问模式下的安全性。

### 专有名词

- TRH：the Rowhammer threshold
- `TRH*`：我们将关键 Rowhammer 阈值 (`TRH*`) 定义为设计满足 TargetTTF 的最低 TRH
- tREFI：Time between successive REF Commands 连续 REF 命令之间的时间
- PRF：回合失败概率 (PRF) 是攻击回合导致失败的概率
- TTF：Time-to-Fail
- TIF：Tracker Insertion Failure
- TRF：Tracker Retention Failure
- Tardiness

### 什么是故障？

故障率涉及以下几个方面：

1. **跟踪器插入失败（Tracker Insertion Failure, TIF）**：
   - 这是指攻击者尝试激活的行（aggressor row）在达到Rowhammer阈值（TRH）之前，从未被插入到跟踪器中的情况。如果一个行没有被跟踪器跟踪，它就无法得到适当的缓解（如刷新），从而可能发生比特翻转。
2. **跟踪器保留失败（Tracker Retention Failure, TRF）**：
   - 这是指已经插入跟踪器的行，在得到缓解之前被驱逐出跟踪器的情况。如果一个行的条目在没有进行缓解的情况下被移出跟踪器，那么这个行就不会得到应有的保护。
3. **延迟（Tardiness）**：
   - 这是指一个行在被插入到跟踪器和实际被缓解之间的时间内，额外接收的激活次数。如果一个行在等待缓解时接收了过多的激活，它可能会在得到缓解之前达到Rowhammer阈值，从而发生比特翻转。

故障率是这些失败模式的综合体现，它衡量了跟踪器在给定时间内（例如，论文中提到的目标失效时间Target Time-to-Fail，TTF）预期会发生故障的次数。一个低故障率意味着跟踪器能够可靠地跟踪并缓解潜在的Rowhammer攻击，而高故障率则意味着跟踪器可能无法有效地保护系统免受Rowhammer攻击的影响。

#### 什么是无效条目?

在文章中提到的“无效条目”（invalid entries）是指在DRAM跟踪器（如PrIDE）的FIFO缓冲区中已经不再代表有效侵略行的条目。这些条目可能是因为以下几种情况而变得无效：

1. **已缓解的条目**：
   - 如果跟踪器对某个条目代表的侵略行进行了缓解操作（例如刷新相邻的受害者行），那么这个条目可能就不再需要跟踪，因此被标记为无效。

2. **被驱逐的条目**：
   - 在FIFO缓冲区中，如果新条目加入时缓冲区已满，最老的条目（即最早插入的条目）会被驱逐出去。如果这个被驱逐的条目还没有来得及进行缓解操作，它就会变成一个无效条目。

3. **已过期的条目**：
   - 某些跟踪器设计中可能会有一个时间限制，超过这个时间限制没有被缓解的条目会被标记为无效。

4. **重复的条目**：
   - 如果跟踪器的设计允许对同一个侵略行有多个条目，那么当行被重复插入时，旧的条目可能被视为无效。

在PrIDE的设计中，无效条目是指那些因为上述原因或其他原因而不再需要跟踪的条目。这些无效条目会占用缓冲区的空间，但不参与到跟踪器的政策决策中，直到它们被新的有效条目替换或者被清除。插入策略需要确保即使在缓冲区中存在无效条目时，新的侵略行仍然以固定的概率被插入到跟踪器中，这是为了保持插入决策的独立性和随机性，从而提高跟踪器对攻击模式的抵抗力。

#### 什么是匹配条目？

“匹配条目”（matching entry）指的是在DRAM内部跟踪器中已经存在的一个条目，该条目与当前尝试插入的行地址相匹配。换句话说，如果跟踪器中已经有了一个代表特定DRAM行的条目，那么当再次尝试插入相同行地址时，就会产生一个匹配。

### 什么是In-DRAM缓解策略

In-DRAM Mitigation策略的原理如下：

1. **识别侵略行（Aggressor Rows）**：
   - In-DRAM Mitigation策略首先依赖于一个在DRAM内部的跟踪器（tracker）来识别可能导致Rowhammer问题的侵略行。这些侵略行是指那些被频繁激活，从而可能引起相邻行（受害者行）比特翻转的DRAM行。

2. **透明缓解操作**：
   - 一旦跟踪器识别出侵略行，它会在DRAM的刷新操作窗口期间透明地执行缓解操作。这通常涉及到在正常刷新周期内对相邻的受害者行进行刷新，以防止或减少比特翻转的发生。

3. **利用刷新周期**：
   - DRAM设备需要定期刷新以保持数据的完整性。In-DRAM跟踪器利用这个刷新周期来执行缓解操作，这样可以在不影响正常内存访问的情况下进行缓解。

4. **优化解决方案**：
   - DRAM制造商可以根据自己的芯片特性（例如，TRH值）优化In-DRAM缓解方案。由于他们对自己的芯片有更深入的了解，因此可以提供更有效的解决方案。

5. **避免碎片化**：
   - In-DRAM缓解策略的一个优势是它可以在DRAM芯片内部解决问题，避免了因不同内存控制器解决方案导致的硬件碎片化问题。

6. **跟踪器的条目数量**：
   - 为了确保所有侵略行都能得到缓解，理想的In-DRAM跟踪器需要有足够的条目来跟踪所有可能的侵略行。例如，如果在一个刷新间隔内可以进行大量激活，那么就需要有足够的条目来跟踪这些激活。

7. **实际限制**：
   - 由于DRAM模块内部的存储能力有限，实际的In-DRAM跟踪器通常只有有限的条目（例如，每个银行只有几个条目）。这意味着它们无法完美地跟踪所有侵略行，因此存在一定的失败率。

8. **性能和安全性的平衡**：
   - In-DRAM Mitigation策略需要在性能和安全性之间找到平衡。例如，增加跟踪器的条目数量可以提高安全性，但可能会增加存储开销和复杂性。

### 低成本追踪器失效的原因

> 任何少于最佳条目数的跟踪器对于某些访问模式总是会产生非零故障率。

TRR（Targeted Row Refresh）、DSAC（Samsung的提案）和PAT（SK Hynix的提案）这些低代价的在DRAM内部跟踪器很难先验地确定最坏情况的模式以及跟踪器在这种模式下失败的频率，主要原因如下：

1. **基于计数器的政策决策**：
   - 这些跟踪器依赖于激活计数器来驱动政策决策，例如决定哪些行插入跟踪器、哪些行被驱逐以及哪些行需要缓解。攻击者可以通过频繁访问虚拟行来操纵这些计数器，从而影响政策决策，使得攻击者可以逃避对侵略行的缓解。

2. **访问模式依赖性**：
   - 由于这些跟踪器的政策决策依赖于行的相对激活次数，因此它们的失败度量（如TIF、TRF和Tardiness）也依赖于访问模式中的行的相对访问频率。这种访问模式依赖性意味着很难事先确定最坏情况下的模式以及跟踪器在该模式下的失败频率。

3. **难以预测的失败模式**：
   - 因为失败模式依赖于具体的访问模式，而这些模式可能非常复杂和多变，所以很难预测在特定攻击模式下跟踪器的具体失败行为。这种不可预测性使得这些跟踪器在面对精心设计的攻击模式时容易受到攻击。

4. **资源限制**：
   - 这些跟踪器在DRAM内部的存储能力受到限制，通常只有少数几个条目。这意味着它们无法可靠地跟踪所有侵略行，因此在某些访问模式下注定会失败。

5. **非独立性**：
   - 由于这些跟踪器的政策决策依赖于访问模式，它们无法实现访问模式独立性。这意味着它们不能保证在所有可能的访问模式下都有相同的失败率，从而难以为最坏情况设定一个明确的失败频率。

6. **攻击者的适应性**：
   - 攻击者可以适应跟踪器的行为，通过改变访问模式来最大化跟踪器的失败概率。由于跟踪器的政策决策与访问模式紧密相关，攻击者可以利用这一点来设计能够绕过跟踪器保护的攻击模式。

 综上所述，这些低代价的在DRAM内部跟踪器由于其设计上的局限性，特别是依赖于激活计数器和访问模式，使得它们难以先验地确定最坏情况的模式和失败频率，从而在安全性上存在较大的不确定性和风险。