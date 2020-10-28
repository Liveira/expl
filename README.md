# Expl

Expl stands for EXPression Language, it was ELPL before,
But it is too obscure to be called "English Like
Programming Language"


## Compiling from source
You will need gcc/clang to compile the C file,
Try: gcc excc.c -o excc
If you get some weird error you can always create 
a new issue.

### how to expl
###### [H]ello world
Ok, you now have two files, main.exc and the 
Interpreter, your code must have a main.exc file,
Why? Because i'm lazy, delete the example main.exc
And create another one, now, on it, type:

    >H
    N

Save the file as main.exc and run excc.
if you did everything alright you will see this:

> H

But here is the sad part, you can only print
__one__ character a time.

###### Variables
First of all, they are not the same variables that
you may know from other languages, they are what you
call dictionaries in Python, but they have a fixed 
amount of keys, they have I_VAL(INT) and C_VAL(CHAR), 
you need to specify both when creating a variable, 
look at this example:

    #a h 1234
    >#/-xa
    N

again, save it as main.exc and run excc, you will see
this:

> h 1234

I have a few things to explain here, first, the '#'
is for indicating a variable, like '$' in php. Next,
we have the declaration of the variable, we used two
values, h(char) and 1234(int), they must follow that
model: #c c i...i, where c is CHAR and i is INT. And
last, we have the /-xa thing, we can break this to:

    / <--- access only the value specified after it
    - <--- this can be anything except a whitespace
    x <--- we specify -x to get both the INT and CHAR values

We have some variations, such as /D- and /d- that mean
respectively non-digit and digit, or CHAR and INT.
