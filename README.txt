                      Comments on Dinkum, Version 2.12                
                              30 January 1993                            

I'm releasing this version of Dinkum sooner than I should because of
the appearance of six bugs coupled with extensive revisions which I
performed on Dinkum during the Christmas holidays.  The bugs are:

1) If the player was chased by a monster for a long distance in the game and
the player survived after killing the monster then for certain random initial
configurations other monsters would have their memory locations changed. 
These changes sometimes resulted in the pointers for the other monsters being
pointed towards garbage causing an abnormal ending and core dump.  This bug
is fixed but was very difficult to locate.  This bug effected ALL earlier
public versions of Dinkum.

2) If the player shot a movable object (non-monster) in Dinkum versions made
after 1.27 then this would lead to an abnormal ending and core dump.  Version
1.27 did not have this bug. This bug has been fixed with the logic supporting
the shooting of movable objects significantly improved.

3) If the player shot off an ammunition clip, ejected it and then reloaded
the clip then all of the ammunition would be "magicly" restored.  This bug
did not occur if the clip still had some ammo left in it.  Goofy bugs of
this sort are easy to fix but hard to find.  Thanks to Byron Rakitzis for
discovering this bug and bug #2.  

4) If the user put Dinkum into its privileged mode and used some of
the privileged commands then a core dump could result for a special case.
Thanks to Per-Anders Eriksson for discovering this bug.  The privileged
mode is for maintenance and debugging use only and not recommended for
people playing Dinkum for entertainment.  I'll explain in private e-mail
the use of this mode to anyone who has won Dinkum in ordinary user mode and
is interested in hacking on the game.

5) There was a bad Ccp definition (I defined DINKUM.C instead of DINKUM)
which kept Dinkum from compiling in certain environments reducing
portability.  Thanks to Darryl O'Neill for discovering this bug.

6) There is a bug in the C compiler used in Ultrix.  This bug caused
Dinkum not to compile because structure pointers were used explicitly
in function parameters.  The fix was suggested by Christopher M. Conway.
This fix simply involved converting all structured pointer declarations
over to typedefs.

                     --------- Revisions -----------

An important revision to Dinkum can be seen in the Makefile.  By
de-commenting one line and deleting another, the user can have a prompt
for Dinkum command inputs.  This improvement was suggested by Chris Herborth.

More than one person has complained about Dinkum's time out feature.  The
argument made was Dinkum is often played on a window running in background
with the user doing constructive work in foreground. Consequently it can
be many minutes between moves resulting in the game often timing out. This
leads to an interesting design problem because I want winners of Dinkum to
have won on a uniform game (no advantages for people using special features
like script files, etc.).  My solution is to go back to my trusty "data
recorder".  If you start Dinkum with the "-s" switch then the game starts
with a data recorder appearing as an object in the game.  If you take the data
recorder and examine it then you'll find it now has an additional feature,
viz. an orange button.  If you press the orange button then Dinkum's internal
clock stops and no further play is possible.  The user is then presented
with a yes/no question.  When the user says "yes" then the game resumes
with the internal clock reset such that no time elapsed while the orange
button was engaged.  The orange button is derived from a suggestion made
by Christopher M. Conway.

                     --------- A Short Sermon -----------

I now have Dinkum revised into a form that is not overly embarrassing
(unlike before).  Something I've discovered is that all of the stories they
tell about the virtues of structured programming are absolutely true.  Dinkum
though written in C, previously had a FORTRAN coding style with the resultant
logic being so convoluted that further maintenance and debugging was almost
impossible. In the process of getting Dinkum into a proper C form, I found
many low level bugs and brought about many improvements.  The lesson which I
have learned is if I'm programming in FORTRAN, BASIC, COBOL or any of the
other old fashioned languages then I'm simply being stupid and punishing myself
needlessly.  Six years ago I would have come up with all sorts of facile
arguments why FORTRAN should be maintained but I now know these arguments are
spurious.  If you're still fighting with FORTRAN then I urge you to learn from
my experience and convert over to C.

                            Gary A. Allen, Jr.                           
