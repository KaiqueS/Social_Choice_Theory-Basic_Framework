# Social Choice Theory - A Toolbox

A Social Choice Theory educational software. Intended to be used as a study companion, it is comprised by data structures and algorithms that represents some known findings of <a href="https://plato.stanford.edu/entries/social-choice/#Aca">Axiomatic SCT</a>. With this software, one will be able to follow, step-by-step, and in many ways, Social Choice models and its results, along with a set of tools that will help visualizing and analyzing the latter.

# About: Data Structures & Properties

<strong>PREAMBLE: </strong>
  
<br> According to <a href="https://plato.stanford.edu/entries/social-choice/#Aca">List( 2013 )</a>, Social Choice Theory is, actually, a collection of models, each of which represents decision procedures involving a collectity. Common to a cathegory of those procedures, are Individuals, Alternatives, and a decision mechanism, i.e., social function, that maps every individual profiles of alternatives into a social profile or decision.<br>

In order to represent the above definitions, the following data structures were implemented:

<p><li><strong>Options</strong></li>

Those are the alternatives which will be passed as arguments to the Social Decision Procedures. To guarantee Universal Domain,
they are randomly generated, without any previous restriction interferring with the generation.

<p><li><strong>Preference Matrix</strong></li>

This class represents a Social Matrix. Composed by the Options above, each line of this matrix is an individual profile of
preferences, and each column an Option with the respective value of that Option for the corresponding profile. This value,
or weight, makes possible representing an ordering of those preferences, where, for any alternatives x, y, and for any integers A, B, ( x, A ) and ( y, B ) are pairs s.t. A is the value of x in the ordering, and B of y. If A > B, then, one can conclude that
x is preferred to y, since it is higher valued in the ordering. If there is a case where A = B, then, one can infer that, for the
respective profile, x = y, which can be interpreted as: the agent i is Indifferent between x and y.

<p><li><strong>Pairwise Rank</strong></li>

To guarantee Completeness, each Option in the Preference Matrix will be compaired, pairwise, against every other option, so that
every possible combination of pairs, without repetition, is considered. Along with that, the Rank will also show how many votes,
i.e., in how many profiles one alternative beats its adversary, or if it is socially equal( read Indifferent ) to its adversary
option.

<p><li><strong>Social Preference Node</strong></li>

Why nodes?
The answer is simple: it will make things easier to be visualized.

How?
With a Directed Graph. The nodes will make possible the creation of a Social Preference Graph, where the relations between the nodes, taken from how one node is ranked in respect with the others on the Pairwise Rank, are represented by edges. For any nodes
x and y, if it is true that x is socially preferred to y, then, there is an Directed Edge e from x to y, i.e., e = ( x, y ). If 
it is the case that in the Social Profile x is indifferent to y, then, a bidirectional edge will link x and y, i.e., e = ( x, y )
and e' = ( y, x ).

Bonus: cycles are easily spotted with graphs!

# About: Algorithms

# Progress

Implement Indifference relation: done.

Implement Condorcert Paradox - almost done, needs cycle-checking algorithm 

Implement Arrow's Impossibility Theorem - nearly done, needs revision.

Implement GUI - almost there

Release ver 1.0 - after GUI and Arrow

Implement Gibbard-Sattertwaite Theorem - after GUI.

# For later:

Add to this README file an visual representation of the Preferences Matrix Structure.

# Bibliography

<br>GAERTNER, Wulf - A Primer In Social Choice<br>
<br>TAYLOR, Michael - Graph-theoretic approaches to the theory of social choice<br>
<br>List, Christian, "Social Choice Theory", The Stanford Encyclopedia of Philosophy (Winter 2013 Edition), Edward N. Zalta (ed.), URL = <https://plato.stanford.edu/archives/win2013/entries/social-choice/>.<br>
