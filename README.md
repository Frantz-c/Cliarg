# Cliarg
get and check arguments from the command line interface

cliarg get arguments to the format "-\[a-zA-Z](=[^\s]\+)?" or "--[a-zA-Z]{2-40}(=[^\s]\+)?"
Example : prog -a -d="~/directory" --max=10

For explain to the program what are expected arguments and it's types, create an string array like this : 
\- "short argument", "long argument", NULL.

example : 
  char \*expect[] = 
  {
    "a"  , "all",
    "v:+", "values",
    NULL
  };
. = integer expected
: = string expected
\+ = one or more arguments expected

(open example.c file for more info)


Compile library and example file:

Go to "library" directory and run make.
The "cliarg.a" library and the "example" executable are created in the parent directory.
Try to run "../example [arguments]"


Error's codes info : 

"\[\d](argument)\*"

'0' = syntax error (invalid name)
      exemples : -long, --c, -, a, ...

'1' = type error (bool expected)
      exemple : "r" => -r=truc

'2' = value error (value expected)
      exemples : "d:" => -d [ou] -d=

'3' = argument error (argument not expected)
      exemple : "b", "bool", "s.", "size"; => ./prog -a --truc=machin

'4' = type error (int expected)
      exemple : "s." => --size="int"

'5' = argument length error (max 40=80)

'6' = comma error
      exemple : "s:+" => -s="str1,str2,,str4"

'7' = no argument error
