## RFinder

---

### Grammar

```
equation    = expression , [ "=" , expression ] ;
expression  = term , { ("+" | "-") , term } ;
term        = factor , { (("*" | "/" | ε) , factor) } ;
factor      = number
             | variable
             | func , "(" , expression , ")"
             | "(" , expression , ")" ;
func        = "sin" | "cos" | "tan" | "mod" | "log" | "ln" | "sqrt" ;
number      = digit , { digit | "." , digit } ;
variable    = "x" ;
```