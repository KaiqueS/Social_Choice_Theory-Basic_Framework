# Social Choice Theory - A Toolbox

&emsp;The purpose is the following: to create a library of Axiomatic Social Choice Theory canonical models, e.g., Arrow's impossibility theorem. The library is intended to help, aid, newcomers to the area of Social Choice Theory.
Those will be able to follow, step-by-step, the theorems implemented here and its results, along with additional information.

# About the properties

&emsp;ID and Preferences may be obvious. In SCT, for a set X of alternatives and an indexed set S of agents, ID represents any agent s<sub> i </sub> of S, while Preferences represents s<sub> i </sub>'s ranking of every x <span>&#8714;</span> X..

Preferences will be externaly given, i.e, agents cannot propose "new alternatives", but [ the agents ] will be able to modify them.

<p><li><strong>Data Structures</strong></li>

Options

PairsOfOpts

PreferenceMatrix

PairWiseRank

SocialPrefNode

# In progress

Implement Indifference relation: done.

Implement Condorcert Paradox - almost done, needs cycle-checking algorithm 

Implement Arrow's Impossibility Theorem - working on it

Implement GUI - after Arrow

Implement Gibbard-Sattertwaite Theorem - after GUI.


<ul type="circle">
  
<p><li><strong>How will indifference be represented?</strong></li>

&emsp;For any two x and y preferences in an agent's ordering, if x and y have both the same value, then one may say that the agent is indifferent between both of them, and, trivially, for any two options a and b, if the values of a and b are different, the option with a higher value will be preferred by the agent.<\p>

<p><li><strong>How will the agents have access to the preferences?</strong></li>

&emsp;Each agent will have access to one, and only one, row of the matrix. This will prevent having access, at least at the beginning, to other agent's preferences. <\p>

<p><li><strong>Why are preferences external?</strong></li>
 
&emsp;To be simple: it is easier to implement and it saves memory.<\p>

</ul>

# For later:

Add to this README file an visual representation of the Preferences Matrix Structure.

# Bibliography

GAERTNER, Wulf - A Primer In Social Choice
TAYLOR, Michael - Graph-theoretic approaches to the theory of social choice
