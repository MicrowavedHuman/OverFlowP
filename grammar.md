# The Grammar Tree Itself
program     -> statement_list  
statement   -> "exit" "(" expression ")" ";"  
expression  -> term (("+" | "-") term)*  
term        -> factor(("\*" | "/") factor)\*   
factor      -> INTEGER | "(" expression ")"

# Writing the Language
OverFlow-P written in an example format would look something like the following examples: 
## Basic Grammar:
```
int ident = 0;
bool ident = True;
print("Something something text");
print(int);
exit(int);
// Comments look like this
```

## Functions:
```
int func_ident(arguments)
{
    int value = argument_1 + argument_2;
    return(value);
}
```
