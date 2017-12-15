# Social Choice Theory - A Toolbox

The purpose is the following: to create an Agent Class with properties that reflect those from the agents, and its respective properties, in Axiomatic Social Choice Theory. This base class will be used on programs of classic models of ASCT, which will be done later.

For now: Creating an Agent Class with the following properties -> ID
                                                                  Status
                                                                  Preference
                                                                  Sex

# About the properties

ID and Preferences may be obvious. In SCT, for a set X of alternatives and an indexed set S of agents, ID represents any agent s_i of S, while Preferences represents s_i's ranking of every x in X, i.e., the property Preferences is already ordered accordingly to s_i's respective ranking of the mentioned options.

The less trivial properties, Status and Sex, were introduced in the class because I decided to proceed with the aforementioned project while programming a version of the Stable-Matching Problem. Status, in the program, represents if some agent is married or free, and, trivially, Sex represents if an agent in question is male or female.

Those properties are not used in SCT models, and, because of that, they were coded in a way where it is not necessary for one to use them for some program/model to work/run. Their use is entirelly optional.

# For later:

The plan is to add canon models, for example, Arrow's Impossíbility Theorem, when I start to study, for real, Social Choice Theory. I will be using Wulf Gaertner's A Primer On Social Choice Theory( 2006 ) as textbook, and every program of model will be based on the books presentation of the respective model.
