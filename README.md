**Notice: all non-GUI related code is being uploaded to SCT_Test branch, while the GUI related code is being uploaded to TestBranch( yeah, I know the naming is awful, will fix it later, though ).**

# Social Choice Theory - A Toolbox

A Social Choice Theory educational software. Intended to be used as a study companion, it is comprised by data structures and algorithms that represents some known findings of <a href="https://plato.stanford.edu/entries/social-choice/#Aca">Axiomatic SCT</a>. With this software, one will be able to follow, step-by-step, and in many ways, Social Choice models and its results, along with a set of tools that will help visualizing and analyzing the latter.

# About: Data Structures & Properties

<strong>PREAMBLE: </strong>
  
According to <a href="https://plato.stanford.edu/entries/social-choice/#Aca">List( 2013 )</a>, Social Choice Theory is a collection of models, where each of which represents decision procedures involving a collectity. Common to a cathegory of those procedures, are Individuals, Alternatives, and a decision mechanism, i.e., social function, that maps every individual profile of alternatives into a social profile or decision.

In order to represent the above elements, the following data structures were implemented:

<p><li><strong>Profiles</strong></li>

Higher-level abstraction of the class ***Options***, a ***Profile*** is a container of the latter.

Each *Option* in its respective *Profile* represents the alternatives which will be passed as arguments to the Social Decision Procedures. To guarantee ***Universal Domain***, they( the alternatives ) are randomly generated, without any restriction.

<p><li><strong>Preference Matrix</strong></li>

This class represents a Social Matrix of *Profiles*.

The matrix has order ***M x N***, where each line in *M* represents an individual profile of preferences, and each column *N* represents an Option within the respective profile, as well as the *value*, or weight, of that Option for the corresponding profile.

This value, or weight, makes it possible to order those preferences, where, for any alternatives x, y, and for any integers A, B, ( x, A ) and ( y, B ) are pairs s.t. A is the value of x in the ordering, and B of y.

If A > B, then x is preferred to y, since it is higher valued in the ordering. If there is a case where A = B, then x = y, which expresses *Indifference* between x and y.

Those values/weights should be taken as a purely ***ordinal*** way of ordering preferences. They are meaningless when taken for its cardinality.

<p><li><strong>Social Choice Rank</strong></li>

A generic Ranking generated through a *pairwise* comparison of each possible combination of pairs of *Options*.

To guarantee Completeness, each pair of Options in the Preference Matrix will be compaired, so that every possible combination of pairs, without repetition, are considered. Along with that, the Rank will also show how many votes, i.e., in how many profiles one alternative beats its adversary, or if it is socially equal( read Indifferent ) to its adversary option.

<p><li><strong>Social Choice Graph</strong></li>

Higher-level abstraction of ***Social Preference Nodes***, a ***Social Choice Graph*** is made of the latter.

First, each *Social Pref Node* represents an *Option*.

But, why a graph?
The answer is simple: it will make things easier to be visualized.

How?

To begin, let one introduce how the graph is created.

There are two ways to create a graph:

* first, by taking a *Social Profile*, which is the result of aggregating all the profiles of preferences with a given aggregation procedure, and, then, relating each pair *x* and *y* of node accordingly to their relation, which is the result of the aggregation procedure.

* second, by creating *edges* between nodes according to wether one alternative beats its adversary or not in the Rank. I.e., if, for any pair *( a, b )* in the **Social Ranking**, if *a* beats *b*, then, one edge ***from*** *a* to *b* will be created.

Also, each node in the graph will hold information of how many and which nodes it beats, it is beaten by, and it is equal to.

Graphs can show more directly how are alternatives related to each other, also, cycles are easier to spot with graphs!

# About: Algorithms

Simple Majority

Qualified Majority

Borda Count

Two-Rounds( simple and qualified majorities )

List-based methods( work in progress )

# Progress

Implement Indifference relation: done.

Implement Condorcert Paradox - done, but needs improvement. 

Implement Arrow's Impossibility Theorem - under revision.

Implement Social Choice Graph Algorithms( only majorities are implemented until now )

Implement GUI - almost done, adding analytical features.

Release ver 1.0 - after GUI and Arrow

Implement Gibbard-Sattertwaite Theorem - after GUI.

# For later:

Add to this README file a visual representation of the Preferences Matrix Structure.

Add GUI images of Social Choice Graphs

# Bibliography

<br>AUSTEN-SMITH, David; BANKS, Jeffrey S. - Positive Political Theory I<br>
<br>ENDRISS, Ulle - Graph Aggregation<br>
<br>GAERTNER, Wulf - A Primer In Social Choice<br>
<br>List, Christian, "Social Choice Theory", The Stanford Encyclopedia of Philosophy (Winter 2013 Edition), Edward N. Zalta (ed.), URL = <https://plato.stanford.edu/archives/win2013/entries/social-choice/>.<br>
<br>TAYLOR, Michael - Graph-theoretic approaches to the theory of social choice<br>
