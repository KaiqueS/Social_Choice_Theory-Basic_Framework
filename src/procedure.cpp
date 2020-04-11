#include "/Projetos/SocialChoice_VS/Include/procedure.hpp"

/* Desired behavior: if Procedure = Majority_rule, then, when receveing
 * an appropriate argument, Procedure will behave just as if it was a M
 * ajority_rule
 *
 * So, instead of doing Procedure::operator( ), it will, in turn, perfo
 * rm a Majority_rule::operator( ).
 *
 * Procedure must PRESERVE an acquired rule and perform its computation
 * when needed
*/

SCT::Procedure::~Procedure( ){ }
