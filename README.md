# Croissant
## Description
It is a C++20 header only library make comparaisons more intuitives by chaining it like this :
* `x == y == z`
* `5 < x < 25`
* `x == y != 12`

But you can only chain comparaisons of the same category (more explanation in the __Limitations__ part). I define 3 categories:
* Equality : __==__
* Less : __<__ and __<=__
* More : __>__ and __>=__

## Example
```Cpp
using Int = Croissant::Value<Int>;
Int x(3);
Int y(4);
Int z(4);
if ((y == z == 4) && ( 5 > x >= 1))
{
	std::cout << "z and y equal 4. x is between 1 and 5 (1 included)" << std::endl;
}
```


## Why ?
Sometimes I write stuff like the snippet below and even if it does not often happen I don't find it elegant.
```Cpp
if (5 < x && x < 25)
	; // do stuff
else (y == x && x == 15)
	// do other stuff
```
Also I wanted to experiment to see if could find a synxtax I like better.

## Limitations
* `x == y > 15` : does not work because it is not readable and error prone and my goal is to make less error prone. __==__ is not of the same type as __>__
* `15 > x < 12` : is not easy to read and __>__ and __<__ are not part of the same catergories.
* `5 > (x > 1)` : because the the goal is to assemble comparaison you instinctively have in your mind as only one instruction (like x is between 5 and 1, or x, y and same are the same) but if you use parenthèsis like this, it looks like these are separate comparaisons.
* `x == 15 != z` : we don't really know if __z__ must be different from __15__ and from __x__ or if __z__ must be different from __15__ only.

## Why is it named "Croissant" ?
I wanted an appetizing name and as a French I can assure you that a croissant is the best thing to eat ever.

## Todo
* Implement >= and >
* Implement < and <=
* Make it usable in real use case
* Add user defined literals for numbers, and string_view types
* More tests
* More examples
* Doc about how it works

## Maybe todo
* Make something to be able to write stuff lile that : `x != y != 15` meaning that the 3 values must be different
