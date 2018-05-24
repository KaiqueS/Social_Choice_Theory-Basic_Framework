# Social Choice Theory - A Toolbox

The purpose is the following: to create an Agent Class with properties that reflect those from the agents, and its respective properties, in Axiomatic Social Choice Theory. This base class will be used on programs of classic models of ASCT, which will be done later.

# About the properties

ID and Preferences may be obvious. In SCT, for a set X of alternatives and an indexed set S of agents, ID represents any agent s<sub> i </sub> of S, while Preferences represents s<sub> i </sub>'s ranking of every x <span>&#8714;</span> X, i.e., the property Preferences is already ordered accordingly to s<sub> i </sub>'s respective ranking of the mentioned options.

The less trivial properties, Status and Sex, were introduced in the class because I decided to proceed with the aforementioned project while programming a version of the Stable-Matching Problem. Status, in the program, represents if some agent is married or free, and, trivially, Sex represents if an agent in question is male or female.

Those properties are not used in SCT models, and, because of that, they were coded in a separate class, where it is not necessary for one to use them for some program/model to work/run. Their use is entirelly optional.

# In progress

Implement Indifference relation: remodel the whole Preferences structure. Think about a data-structure to represent it properly.

Preferences will be externaly given, but agents will be able to modify them.

The data structure used will be a Bidimensional Matrix, composed by three elements, i.e., Agents, Alternatives/Options, and a Value which will be representing the ranking of an alternative/option in an agent ordering.

How will indifference be represented? 

  For any two x and y preferences in an agent's ordering, if x and y have both the same value, then one may say that the agent is indifferent between both of them, and, trivially, for any two options a and b, if the values of a and b are different, the option with a higher value will come, obviously, first in the ordering, being, thus, preferred by the agent.

How will the agents have access to their preferences?

  Each agent will have access to one, and only one, row of the matrix. This will prevent having access, at least at the beginning, to other agent's preferences. 

Why are preferences external?
 
  To be simple: it easier to implement and it saves memory.

# For later:

Add to this README file an visual representation of the Preferences Matrix Structure.

The plan is to add canonical models, for example, Arrow's Impossíbility Theorem, when I start studying, for real, Social Choice Theory. I will be using Wulf Gaertner's A Primer On Social Choice Theory( 2006 ) as textbook, and every program of model will be based on the books presentation of the respective model.
