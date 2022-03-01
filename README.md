**NOTICE: all non-GUI related code goes to SCT_Test branch, while the GUI related code goes to TestBranch**

**Also, code in master branch has a previous( and working ) version of the GUI. Feel free to test it!**

# Social Choice Theory - A Toolbox

A Social Choice Theory educational software. Intended to be used as a study companion, it is comprised by data structures and algorithms that represents some known findings of <a href="https://plato.stanford.edu/entries/social-choice/#Aca">Axiomatic SCT</a>. With this software, one will be able to follow, step-by-step, and in many ways, Social Choice models and its results, along with a set of tools that will help visualizing and analyzing the latter. Procedures, or aggregation rules, here, are binary in nature. I.e., first find the orderings of each pair, then compose from that and create an ordering over all alternatives.

# About: Data Structures & Properties

<strong>PREAMBLE: </strong>
  
According to <a href="https://plato.stanford.edu/entries/social-choice/#Aca">List( 2013 )</a>, Social Choice Theory is a collection of models, where each of which represents decision procedures involving a collectity. Common to a category of those procedures, are Individuals, Alternatives, and a decision mechanism, i.e., social welfare functions or aggregation procedures, mapping every individual profile of alternatives into a social profile or decision.

In order to represent the above elements, the following data structures were implemented:

<p><li><strong>Profiles</strong></li>

Higher-level abstraction of the class ***Options***, a ***Profile*** is a container of the latter.

Each *Option* in its respective *Profile* represents the alternatives which will be passed as arguments to the Social Decision Procedures. To guarantee ***Universal Domain***, they( the alternatives ) are generated over an alphabet, without any restriction over any alternative in the latter. Every *Option* is a pair ( alternative, value ), where the value informs the position of the alternative in one's individual profile.

<p><li><strong>Preference Matrix</strong></li>

This class represents a Social Matrix of *Profiles*.

The matrix has order ***M x N***, where each line in *M* represents an individual profile of preferences, and each column *N* represents an Option within the respective profile, as well as the *value* of that Option for the corresponding profile.

This value makes it possible to order those preferences, where, for any alternatives x, y, and for any integers A, B, ( x, A ) and ( y, B ) are pairs s.t. A is the value of x in the ordering, and B of y.

If A > B, then x is preferred to y, since it is higher valued in the ordering. If there is a case where A = B, then x = y, which expresses *Indifference* between x and y.

Those values should be taken as a purely ***ordinal*** way of ordering preferences. They are meaningless when taken for its cardinality, i.e., they do not represent how much one prefers an alternative over another. There is no intention of representing cardinality or intensitiy of preferences here.

<p><li><strong>Social Choice Rank</strong></li>

A generic Ranking generated through a *pairwise* comparison of each possible combination of pairs of *Options* for every *Profile* in a *PreferenceMatrix*.

To guarantee Completeness, each pair of Options in the Preference Matrix will be compared, so as to consider every possible combination of pairs, without repetition. Along with that, the Rank will also show how many profiles one alternative beats its adversary, or if it is socially equal( read Indifferent ) to its adversary option.

<p><li><strong>Decisive Sets</strong></li>

Simply put: shows which alternative a, b is preferred to the other under an aggregation rule, and in which *Profile* we can observe the given ordering.
  
<p><li><strong>Social Choice Graph</strong></li>

A graph structured container of ***Social Preference Nodes***, where each *Social Pref Node* represents an *Option*.

But, why a graph?
The answer is simple: it will make things easier to be visualized.

How?

To begin, let me describe how the graph is created.

There are two ways to create a graph:

* first, by taking a *Social Profile*, which is the result of aggregating all the profiles of preferences with a given aggregation procedure, and, then, connecting each pair *x* and *y* of node accordingly to their relation, which is determined by the aggregation procedure.

* second, by creating *edges* between nodes according to wether one alternative beats its adversary or not in the Rank. I.e., if, for any pair *( a, b )* in the **Social Ranking**, if *a* beats *b*, then create an edge ***from*** *a* to *b*.

Also, each node in the graph will hold information of how many and which nodes it beats, it is beaten by, and it is equal to.

Graphs can show more directly how are alternatives related to each other, also, cycles are easier to spot!

# About: Algorithms

Majority Rule 50% + 1

Borda Count
  
# Progress

Implement Indifference relation: done.

Implement Condorcert Paradox - done, but needs improvement. 

Implement Arrow's Impossibility Theorem - under revision.
|
|-> Pareto: done. Generate a SCRank, check if any alternative that is unanimously chosen beats every other alternative in the Social Ordering generated through the procedure
    
 -> IIA:         
 
1. ALTERNATIVE IMPLEMENTATION: first, check for transitivity on a *PreferenceMatrix* under an aggregation procedure. Then, if the resulting ordering is transitive, get any two pairs m = ( a, b ), n = ( b, c ). Without directly checking for ( a, c ), check if a > b and b > c. By transitivity, we must have a > c. But, then, ( a, b ) is determined by b, thus violating IIA. 
 
-> Non-Dictatorship: 
        
--> first attempt of implementation: Sen's proof. Find, recursively, decisive sets, until one of cardinality = 1 is found. This will be the dictator.
 
--> second attempt of implementation: find ALL decisive sets. Check whether the smallest of those has cardinality equal to 1. If not, then there is no dictator.

Implement Social Choice Graph Algorithms( only majorities are implemented until now )

Implement GUI - needs rework. Adjust to new codebase under SCT_Test branch.

Release ver 1.0 - after GUI and Arrow

Implement Gibbard-Sattertwaite Theorem - after GUI. This will be interesting. I will follow from Bartholdi(1989).

# For later:

Images!
  
# Bibliography

<br>AUSTEN-SMITH, David; BANKS, Jeffrey S. - Positive Political Theory I<br>
<br>Bartholdi, J., Tovey, C.A. & Trick, M.A. Voting schemes for which it can be difficult to tell who won the election. Soc Choice Welfare 6, 157–165 (1989). https://doi.org/10.1007/BF00303169<br>
<br>ENDRISS, Ulle - Graph Aggregation<br>
<br>GAERTNER, Wulf - A Primer In Social Choice<br>
<br>List, Christian, "Social Choice Theory", The Stanford Encyclopedia of Philosophy (Winter 2013 Edition), Edward N. Zalta (ed.), URL = <https://plato.stanford.edu/archives/win2013/entries/social-choice/>.<br>
<br>TAYLOR, Michael - Graph-theoretic approaches to the theory of social choice<br>
