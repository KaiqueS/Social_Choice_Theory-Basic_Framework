# Social Choice Theory - A Toolbox

A Social Choice Theory software. Intended to be used as a study companion, it is comprised by data structures and algorithms that represents some known findings of <a href="https://plato.stanford.edu/entries/social-choice/#Aca">Axiomatic SCT</a>. With this software, one will be able to follow, step-by-step, and in many ways, Social Choice models and its results, along with a set of tools that will help visualizing the latter.

# About: Data Structures & Properties

<p><li><strong>PREAMBLE: </strong></li>
  
<br>&emsp; According to <a href="https://plato.stanford.edu/entries/social-choice/#Aca">List( 2013 )</a>, Social Choice Theory is, actually, a collection of models, each of which represents decision procedures involving a collectity. Common to a cathegory of those procedures, are Individuals, Alternatives, and a decision mechanism, i.e., social function, that maps every individual profiles of alternatives into a social profile or decision.<br>

In order to represent the above definitions, the following data structures were implemented:

ID and Preferences may be obvious. In SCT, for a set X of alternatives and an indexed set S of agents, ID represents any agent s<sub> i </sub> of S, while Preferences represents s<sub> i </sub>'s ranking of every x <span>&#8714;</span> X..

Preferences will be externaly given, i.e, agents cannot propose "new alternatives", but [ the agents ] will be able to modify them.

<p><li><strong>Options</strong></li>

<p><li><strong>Preference Matrix</strong></li>

<p><li><strong>Pairwise Rank</strong></li>

<p><li><strong>Social Preference Node</strong></li>

# About: Algorithms

# Progress

Implement Indifference relation: done.

Implement Condorcert Paradox - almost done, needs cycle-checking algorithm 

Implement Arrow's Impossibility Theorem - working on it

Implement GUI - working on it

Implement Gibbard-Sattertwaite Theorem - after GUI.

# For later:

Add to this README file an visual representation of the Preferences Matrix Structure.

# Bibliography

<br>GAERTNER, Wulf - A Primer In Social Choice<br>
<br>TAYLOR, Michael - Graph-theoretic approaches to the theory of social choice<br>
<br>List, Christian, "Social Choice Theory", The Stanford Encyclopedia of Philosophy (Winter 2013 Edition), Edward N. Zalta (ed.), URL = <https://plato.stanford.edu/archives/win2013/entries/social-choice/>.<br>
