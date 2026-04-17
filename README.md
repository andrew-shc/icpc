Personal checklist:
- @= && no more ideas ? stop : stop within @<-20
- Know your MODs
- Understanding a problem correctly and quickly is as important as solving the problem for god sake
- Don't pigeonhole on strategy of any problem (esp. easier ones just because they're easy)
  - Don't spend extra time thinking elegant solutions in A since many As have very lax constraint that allows brute-forcing
- Don't pigeonhole on interpretation of any problem (esp. if you have strong prior bias on the setting/context of the problem)
- Stuck? Pattern deduction by exploration of select existing difficult test cases (think eps-greedy exploration)
  - Don't just focus on the easier test cases; they don't provide a lot of info
- WA on test >1 (i.e., edge cases)? Start validating your own solution with your own test case before the first submission (esp. if it's easier to verify).

A back-analysis on the poor effective solve rate on C (4/16/26):

Goal:
* Solving ABC as fast as possible to allow time to solve D in the future (in the current deflated rating for non-cheaters, should yield specialist)
* And reach to that position as soon as possible (<1 mo. / this is going to backfire so much)

Problem:
* From eyeballing, it seems like the solve rate for C varies from 80% to 50% on a 7-day window (recently hit a bunch of C's that are >1400s :shock:)
* Even if <=1400s, the solve rate is not good
* It's been 1.5 months and still stuck on C => it doesn't seem like whatever I'm currently doing is going to change the trajectory
* Timing C restricts when I can do C while the solve rate is terrible (do un-timed C and focus on C solve rate)

Analysis:
| Problem (Oldest to Latest)                     | Rating | Tags                | Submission Status     | Key Insights                                                                                                                                                                                                                                 |
| ---------------------------------------------- | ------ | ------------------- | --------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| https://codeforces.com/contest/2202/problem/C1 | 1300   | DS,DSU,G            | Checked editorial     | Missed invariance: max of previous subseg. does not matter (more restrictive)                                                                                                                                                                |
| https://codeforces.com/contest/2192/problem/C  | 1300   | BS,G,M              | Checked editorial     | Missed observation: linear check **over answer** and find the smallest *i* that sat. for the opt. ans.                                                                                                                                       |
| https://codeforces.com/contest/2205/problem/C  | 1500   | G,S                 | Solved (memorable)    | Key elegance: iirc, you reverse the overall vll in terms smaller component (blogs) then sort within each comp. and dedup. after first/before last occur.                                                                                     |
| https://codeforces.com/contest/2203/problem/C  | 1500   | BS,BitM,G,M         | Checked editorial     | Missed observation: binary search **over answer** (min. length *n*); Overall idea: given *n*, can you flatten the max to within *n* and is valid?                                                                                            |
| https://codeforces.com/contest/2197/problem/C  | 1200   | games,G,M           | Checked editorial     | Missed obs.: you can *min* over two/multi. factors; Found obs.: the comparison works in some intrinsic factor sep. from 2,3                                                                                                                  |
| https://codeforces.com/contest/2194/problem/C  | 1300   | BitM,BF,DP,M,NumT   | Solved                | Missed obs.: we only check over integer divisors of *n* and 26 letters only (instead of dynamic sets); Found obs.: used sets across strips at the same idx.                                                                                  |
| https://codeforces.com/contest/2207/problem/C  | 1600   | DS,D&Q,DP,M         | Upsolved (memorable)  | Key obs.: break the problem into individual fundamental pieces & and use these small pieces to find the final answer with some indirect method (i.e., sub. the intersection); Unused obs.: D&Q on max (confused on multi. of the same maxes) |
| https://codeforces.com/contest/2189/problem/C1 | 1300   | BitM,C,M            | Checked editorial     | Missed obs.: if the Q asks for *there exists*, we can, by construction, find a simplified case (if possible); Found obs.: re-formulating conditional expr.                                                                                   |
| https://codeforces.com/contest/2183/problem/C  | 1500   | BS,G,M,2Ptr         | Checked editorial     | Key obs.: two pointer **on answer** with variable constraints & with some proof on greedy to transfer the answer space to constraint space                                                                                                   |
| https://codeforces.com/contest/2178/problem/C  | 1200   | DP,G,Impl           | Checked editorial     | Missed obs.: a decision now prepares a decision for the future (i.e., delayed; prev. pos. el. is linked to current pos el.; take a positive of previous el. when found a new positive el.) => abstracted to simplify the problem             |
| https://codeforces.com/contest/2176/problem/C  | 1300   | G,S                 | Solved                |                                                                                                                                                                                                                                              |
| https://codeforces.com/contest/2173/problem/C  | 1400   | BF,C,G,NumT         | Checked editorial (?) | Miscomprehended                                                                                                                                                                                                                              |
| https://codeforces.com/contest/2170/problem/C  | 1300   | BS,G,2Ptr           | Solved                | Visualization with complex cases helped (i.e., r-cone)                                                                                                                                                                                       |
| https://codeforces.com/contest/2208/problem/C  | 1300   | DP,G,M              | Solved (memorable)    | Key obs.: decision depends on the future where it affects the fraction backwards; First indirect backwards "DP" solved                                                                                                                       |
| https://codeforces.com/contest/1760/problem/C  | 800    | DS,Impl,S           | --                    | ????                                                                                                                                                                                                                                         |
| https://codeforces.com/contest/2204/problem/C  | 1000   | M,NumT              | Checked editorial     | LCM cycles!                                                                                                                                                                                                                                  |
| https://codeforces.com/contest/2163/problem/C  | 1500   | BF,Comb,DP,M,2Ptr   | Checked editorial     | Stuck: counting unique valid intervals; Found obs.: bidirectional interval-ed DPs and linearly find the subset valid interval; Missed obs.: order by L then R and find **min. right per left endpoint** (weird indirect DP)                  |
| https://codeforces.com/contest/2161/problem/C  | 1200   | C,G,S,2Ptr          | Solved                | Key invariance: we always reach the same "levels", but re-arranging elements allows us to maximize                                                                                                                                           |
| https://codeforces.com/contest/2154/problem/C1 | 1400   | G,Impl,M,NumT       | Solved                |                                                                                                                                                                                                                                              |
| https://codeforces.com/contest/2153/problem/C  | 1500   | C,Geom,G,Impl,S     | Solved                | Tested edge cases without looking at test case #2                                                                                                                                                                                            |
| https://codeforces.com/contest/2155/problem/C  | 1500   | BF,G,Impl           | **Skipped**           | (need to be reviewed)                                                                                                                                                                                                                        |
| https://codeforces.com/contest/2151/problem/C  | 1400   | G,Impl,M            | Solved                |                                                                                                                                                                                                                                              |
| https://codeforces.com/contest/2144/problem/C  | 1300   | Comb,DP,M           | Solved                |                                                                                                                                                                                                                                              |
| https://codeforces.com/contest/2139/problem/C  | 1100   | BitM,C,G            | Checked editorial     | Missed obs.: "backtracking", we already know what's the final result but we want the ops. the path to reach it; we can find invariance if we look from the end to the beginning                                                              |
| https://codeforces.com/contest/2134/problem/C  | 1200   | BF,G,Impl           | Checked editorial     | Don't tunnel on elegant, analytical formulas; Missed obs.: when a local decision effects dominos/cascades globally, understand which single local decision best optimize the global prob. at hand                                            |
| https://codeforces.com/contest/2127/problem/C  | 1400   | games,G,S           | Checked editorial     |                                                                                                                                                                                                                                              |
| https://codeforces.com/contest/2211/problem/C1 | 1300   | BS,BF,G,2Ptr        | Solved                |                                                                                                                                                                                                                                              |
| https://codeforces.com/contest/2210/problem/C1 | 1200   | G,NumT              | Checked editorial     | Miscomprehended; lcm(gcd,gcd)                                                                                                                                                                                                                |
| https://codeforces.com/contest/2128/problem/C  | 1200   | G,M                 | Solved                |                                                                                                                                                                                                                                              |
| https://codeforces.com/contest/2122/problem/C  | 1700   | C, Geom, G, M, S    | Checked editorial     | Elegant obs.: partition the points into quadrants and pair them from both halves                                                                                                                                                             |
| https://codeforces.com/contest/2119/problem/C  | 1300   | BitM, C, M          | Solved                |                                                                                                                                                                                                                                              |
| https://codeforces.com/contest/2120/problem/C  | 1400   | C, G, M, S, trees   | Solved                |                                                                                                                                                                                                                                              |
| https://codeforces.com/contest/2118/problem/C  | 1300   | BitM, DS, G, M      | Solved                |                                                                                                                                                                                                                                              |
| https://codeforces.com/contest/2109/problem/C1 | 1500   | BitM, C, I, M, NumT | Checked editorial     | Missed obs.: *x* is at most 16 after applying `digit` twice, sometimes you don't have to care the small things, sometimes you have to such as here on finding the final range of values of *x*                                               |
| https://codeforces.com/contest/2107/problem/C  | 1500   | BS, C, DP, Impl, M  | Checked editorial     | Missed obs.: max DP @i can be thought of as keep the previous accumulation (grow the subarray sum) or restart anew (new subarray sum)                                                                                                        |
| https://codeforces.com/contest/2104/problem/C  | 1100   | BF, C, games, G, M  | Solved                |                                                                                                                                                                                                                                              |
| https://codeforces.com/contest/2103/problem/C  | 1600   | BS,G,Impl,S         | Checked editorial     | Key obs.: we can use `max` and comparators as a way to check for existence (and we only care about existence b/c answer only cares about existence)                                                                                          |
| https://codeforces.com/contest/2084/problem/C  | 1400   | C,DS,G,Impl         | Checked editorial     | Key obs.: instead of swapping from the current index, given the current index, swap 2 *other later half* indices (don't always focus on the present)                                                                                         |
| https://codeforces.com/contest/2092/problem/C  | 1200   | C,G,M               | Solved                |                                                                                                                                                                                                                                              |
| https://codeforces.com/contest/2085/problem/C  | 1600   | BitM, C, DP, G      | Solved                |                                                                                                                                                                                                                                              |
| https://codeforces.com/contest/2078/problem/C  | 1500   | C,G,M,prob,S        | Checked editorial     | Missed obs.: automatically did not think of re-ordering or checking deeply on the condition because thought any extra constraints next to the trivial constraints has nothing to be analyzed (sim. to misreading)                            |
| https://codeforces.com/contest/2070/problem/C  | 1500   | BS, G               | Checked editorial     | Missed obs.: binary search **over answer** (and checking if the given answer satisfies the constraint on # of ops.)                                                                                                                          |

| Rating | % Solved |
| ------ | -------- |
| 1000   | 0/1      |
| 1100   | 1/2      |
| 1200   | 3/7      |
| 1300   | 8/11     |
| 1400   | 3/6      |
| 1500   | 2/10     |
| 1600   | 1/3      |
| 1700   | 0/1      |

| Tag            | % Solved |
| -------------- | -------- |
| G(reedy)       | 15/32    |
| C(onstructive) | 7/16     |
| DS             | 1/4      |
| BS             | 2/8      |
| M(ath)         | 11/23    |
| S(orting)      | 5/10     |
| 2Ptr           | 3/5      |
| BitM           | 4/8      |
| games          | 1/3      |
| NumT           | 2/6      |
| BF             | 3/7      |
| Impl           | 3/10     |
| Comb           | 1/2      |
| Geom           | 1/2      |
| DSU            | --       |
| D&Q            | --       |
| I(nteractive)  | --       |
| trees          | --       |

Potential Solution (on top of generalized advice from online):
* Claude suggestions
  * Solving only Cs will not regress solve rate on A,B, but may regress the speed A,B which can rebound quickly after some warm-up (that's a relief?)
  * Improve specifically on binary search + implementation (?)
* Analysis
  * Tags tells me nothing (I equally suck at all front; I am equally good (?) at all front)
  * Need to focus on C with >=1500 (and seems to be as hard as C gets)
  * Additional note: the only unsolved 1300s are the first three
* Plan:
  * **Just solve 2 1400-1700C (Div.2) everyday** *untimed/flexible* until effectively full solve rate


\*: (accidentally?) checked tags & ratings (i.e., significantly influenced the process of problem solving *especially in the beginning*)  
⁑: checked the hidden judging test cases (for WA on 2 or more)  
⁂: checked editorial / unsolved   
†: WA on 1st (sample test case)  
‡: WA after 1st  
⹋: TLE / MLE  
✥: slept through (included in the time)  
x: queued for a long time  
y: misunderstood/miscomprehended the problem  

Speed solving history (II)
| Contest | A (=5)      | B (=25)      | C (=60)       |
| ------- | ----------- | ------------ | ------------- |
| 2122    | -8:29‡‡     | +7:27        | ⁂             |
| 2119    | -26:52‡‡‡   | +0:22‡       | -31:20‡⁑      |
| 2120    | -17:18      | -13:44✥      | +3:58‡        |
| 2118    | -10:47‡     | -12:41††     | -19:18✥       |
| 2116    | <-60:00‡†‡‡ | <-120:00‡‡‡⁑ | ⁂ (<-60:00)   |
| 2109    | -8:03       | <-60:00†‡✥⁑  | ⁂ (<-30:00)   |
| 2107    | -3:13       | -61:20✥‡     | ⁂ (<-20:00)   |
| 2104    | -5:37       | +6:01        | +9:03✥        |
| 2103    | -2:00       | -32:57       | <-60:00       |
| 2084    | -20:39      | -22:05       | ⁂ (<-120:00)  |
| 2092    | --          | +12:30       | +24:29        |
| 2085    | -18:54✥     | -15:28✥††    | +31:53        |
| 2078    | -6:17       | +9:51        | y⁂ (<-120:00) |
| 2070    | -3:44       | -1:30        | y⁂ (<-50:00)  |


Speed solving history
| Contest     | A (=5) | B (=25)                              | Notes                                                                                                                                                                                  |
| ----------- | ------ | ------------------------------------ | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 2178        | +0:40  | +12:01 (easier round?)               | *A: (pretty luck ig?)                                                                                                                                                                  |
| 2176        | +0:49  | -32:38 (misunderstood problem)       |                                                                                                                                                                                        |
| 2173        | +0:07  | -32:40 (after checking editorial)    |                                                                                                                                                                                        |
| 2170        | -7:36  | -11:41                               |                                                                                                                                                                                        |
| 2166        | +2:03  | +7:34 (900 B / easier B)             |                                                                                                                                                                                        |
| 2208 (live) | -26:00 | -50:00                               | 太粗心了; be open-minded even for easier problems                                                                                                                                      |
| 2204 (live) | +2:00  | +21:00                               | *C: know the LCM cycles                                                                                                                                                                |
| 2163        | -1:38  | <0; (checked editorial)              | Find the tricks; don't even spend a second finding an elegant solution                                                                                                                 |
| 2161        | -37:56 | <0; (1200 B / harder)                | Pigeonholed the *interpretation* of A (=> never pigeonhole on interpretation and strat of any problems, esp when you have a strong prior bias on one context/setting of a problem)     |
| 2154        | -18:07 | -8:59                                | weird I/O bug happened on A (I accidentally wrote A code in C1 code... very sloppy today); super sloppy today for some reason?? (greedy w/o proofs increasingly more uncomfortable :/) |
| 2153        | +0:51  | +10:42                               |                                                                                                                                                                                        |
| 2155        | <-10   | -4:24                                | *A: took a long time to queue, but notice these invariances asap                                                                                                                       |
| 2144        | <-30   | <-30                                 | practice # theory.                                                                                                                                                                     |
| 2139        | +2:00  | <-10                                 |                                                                                                                                                                                        |
| 2134        | -0:59  | -19:39 (most beautiful problem ever) |                                                                                                                                                                                        |
| 2127        | -23:07 | -38:23                               | A: annoying to implement; elegant deduction. Custom manual edge case validation helped a lot => need to do it more often.                                                              |
| 2211 (live) | -1:00  | <-60:00                              |                                                                                                                                                                                        |
| 2210 (live) | -2:00  | -8:00                                |                                                                                                                                                                                        |
| 2128        | -3:42  | -23:06                               |                                                                                                                                                                                        |
